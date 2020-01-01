#!/usr/bin/perl

use strict;
use Getopt::Std;

use strict;
use diagnostics;
use Math::BigFloat;
use Getopt::Std;

my $Version="v 1.2";
my $Date="Mar 2012";

##--------------------------------------------------------------------------------------------------
## Author  | Rev | Date     | Comment
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.0 | 28/10/11 | Creation, first version (f:0 insert bin size to BIN_END)
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.1 | 16/01/12 | f:1 parsing link info to check is display buffer cross 8M area
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.2 | 21/03/12 | f:2 write the bin size to 0x FEC
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.3 | 17/04/12 | f:3 check if the size of un-mapping region is larger than 102KB or not
##--------------------------------------------------------------------------------------------------


my $Functionallity;
my $LinkInfo;
my $Output;
my $Verbose;
my $fl;
my $SizeOfNoMmuRegion=0;


my %opts;
getopts("f:l:o:s:w:h",\%opts);
if (exists $opts{h}) {PrintHelp(); exit 1; }
if (exists $opts{f}) {$Functionallity=$opts{f};}else{PrintHelp(); exit 1; }
if ( $Functionallity eq 0 )
{
	if (exists $opts{l}) {$LinkInfo=$opts{l};}
	else{print"\n No Link Info is specified!!\n\n";PrintHelp(); exit 1; }
	
	if (exists $opts{o}) {$Output=$opts{o};}
	else{print"\n No Output file is specified!!\n\n";PrintHelp(); exit 1; }
}
elsif( $Functionallity eq 1 )
{
	if (exists $opts{l}) {$LinkInfo=$opts{l};}
	else{print"\n No Link Info is specified!!\n\n";PrintHelp(); exit 1; }
}
elsif( $Functionallity eq 2 )
{
	if (exists $opts{o}) {$Output=$opts{o};}
	else{print"\n No Output file is specified!!\n\n";PrintHelp(); exit 1; }
}
elsif( $Functionallity eq 3 )
{
	if (exists $opts{l}) {$LinkInfo=$opts{l};}
	else{print"\n No Link Info is specified!!\n\n";PrintHelp(); exit 1; }

	if (exists $opts{w}) {$fl=$opts{w};}
	else{print"\n No function list is specified!!\n\n";PrintHelp(); exit 1; }
	
	if (exists $opts{s}) {$SizeOfNoMmuRegion=$opts{s};}
	else{print"\n No SizeOfNoMmuRegion is specified!!\n\n";PrintHelp(); exit 1; }
}
else { PrintHelp(); exit 1; }

#
# 1. parsing link info to get address of BIN_END
#
my $BIN_END_addr=0;
sub parsing_link_info()
{

	open(LINKINFFILE, "<".$LinkInfo) or die "Can't open link info file: $!";
	while (<LINKINFFILE>)
	{
		chomp;

		# pattern:
		#    Execution Region BIN_END (Base: 0x000df948, Size: 0x00000000, Max: 0xffffffff, ABSOLUTE)
		if (m/Execution Region BIN_END \(Base\: 0x(\w+)\, Size.*/) 
		{
			$BIN_END_addr = hex($1);
			print("BIN_END_addr=".$BIN_END_addr." \(0x".$1."\)\n");
			last;
		}
	}
	close LINKINFFILE;

}



#
# 2. insert binary size into binary
#
sub add_header_address()
{
	if ( $BIN_END_addr eq 0 )
	{
		print "no BIN_END is found!\n";	
		return ;
	}

	my $new_byte = -s $Output;
	print "bin size = ".$new_byte."\n";

	open OUTPUT, '+<', $Output      or die "open failed: $!\n";
	binmode OUTPUT;
	seek(OUTPUT, $BIN_END_addr, 0);
	print OUTPUT pack("I", $new_byte);
	close OUTPUT                     or die "close failed: $!\n";
	
}



#
# 11. parsing link info to check is display buffer cross 8M area
#
sub parsing_link_info_to_check_is_display_buffer_cross_8M_area()
{
			
	open(LINKINFFILE, "<".$LinkInfo) or die "Can't open link info file: $!";
	while (<LINKINFFILE>)
	{
		chomp;
		
		# pattern:
		# Execution Region RAM_HIGHAREA (Base: 0x00fa9ae0, Size: 0x0004b000, Max: 0xffffffff, ABSOLUTE)
		if (m/Execution Region RAM_HIGHAREA \(Base\: 0x(\w+)\, Size: 0x(\w+).*/) 
		{
			my $RAM_HIGHAREA_END_addr = hex($1);
			my $RAM_HIGHAREA_END_size = hex($2);
			print("RAM_HIGHAREA_END_addr=$RAM_HIGHAREA_END_addr \(0x".$1."\)\n");
			print("RAM_HIGHAREA_END_size=$RAM_HIGHAREA_END_size \(0x".$2."\)\n");

			my $x8M = 0x800000;
		
			for( my $i=1; $i<5; ++$i )
			{
		
	if($RAM_HIGHAREA_END_addr <$x8M*$i && $RAM_HIGHAREA_END_addr+$RAM_HIGHAREA_END_size > $x8M*$i )
			{
					print "error message: the RAM_HIGHAREA cross 8M from $RAM_HIGHAREA_END_addr to $RAM_HIGHAREA_END_addr+$RAM_HIGHAREA_END_size\n";
					print "error message: please move RAM_HIGHAREA in scatter file to avoid crossing 8M area\n";
				exit 1;
			}
			}

			last;
		}
	}
	close LINKINFFILE;

}

sub add_info_to_bin
{
	my $addr = shift;
	my $insert_value = shift;
	print "insert $insert_value to $addr\n";

	open OUTPUT, '+<', $Output      or die "open failed: $!\n";
	binmode OUTPUT;
	seek(OUTPUT, $addr, 0);
	print OUTPUT pack("I", $insert_value);
	close OUTPUT                     or die "close failed: $!\n";
	
}








#
# 31. check if the size of un-mapping region is larger than 102KB or not
#
sub check_if_the_size_of_un_mapping_region_is_larger_than_102KB_or_not()
{
	open(LINKINFFILE, "<".$LinkInfo) or die "Can't open link info file: $!";
	while (<LINKINFFILE>)
	{
		chomp;
		
		# pattern:
		# Load Region SELECTED_BIN_LOAD (Base: 0x0001654c, Size: 0x003dc5c0, Max: 0xffffffff, ABSOLUTE)
		if (m/Load Region SELECTED_BIN_LOAD \(Base\: 0x(\w+)\, Size: 0x(\w+).*/) 
		{
			my $SELECTED_BIN_LOAD_start_addr = hex($1);
			#print("SELECTED_BIN_LOAD_addr=$SELECTED_BIN_LOAD_start_addr \(0x".$1."\)\n");
		
			if( $SELECTED_BIN_LOAD_start_addr > $SizeOfNoMmuRegion )
			{
				print "\nerror message: size limition: $SizeOfNoMmuRegion bytes\n";
				print "error message: size of un-remapping load:  $SELECTED_BIN_LOAD_start_addr bytes\n";
				print "error message: there is critical path, please check $fl to remove it !!!\n\n";			
				exit 1;
			}

			last;
		}
	}
	close LINKINFFILE;
}



sub dbg_print 
{
  if ($Verbose >= 1) { printf shift; }
}


#
# print user guide
#
sub PrintHelp {
print <<"EOF";
Script to compress bin file and append header after binary
RDO - MStar Taiwan - $Date - version $Version
Usage:$0 [-f folder] [--parameters] [-h]  [-v verbose mode]
  -h: help, show this user guide
  -f functionallity

  f=0: insert bin size to BIN_END
Usage:$0 -f 0 [-l link.info] [-o output file]
    -l: link.info, we have to parse them to get load/execution information
    -o: output file, the body of binary file L\$\(product_name\).bin

  f=1: check is display buffer cross 8M area
Usage:$0 -f 1 [-l link.info]
    -l: link.info, we have to parse them to get load/execution information

  f=2: write the bin size to 0xFEC
Usage:$0 -f 2  [-o output file]
    -o: output file, the body of binary file

EOF
exit 1;  
}



if( $Functionallity eq 0 )
{

	# 1. parsing link info to get address of BIN_END
	parsing_link_info();

	# 2. insert binary size into binary
	add_header_address();

}
elsif( $Functionallity eq 1)
{

	# 11. parsing link info to check is display buffer cross 8M area
	parsing_link_info_to_check_is_display_buffer_cross_8M_area();

}
elsif( $Functionallity eq 2)
{
	# 21. parsing link info to check is display buffer cross 8M area
	my $cur_bin_size = -s $Output;	
	#0xFEC : size of cur bin (the addr of zlib dict)
	add_info_to_bin( 0xFEC, $cur_bin_size );
}
elsif( $Functionallity eq 3)
{
	# 31. check if the size of un-mapping region is larger than 102KB or not
	check_if_the_size_of_un_mapping_region_is_larger_than_102KB_or_not();

}


