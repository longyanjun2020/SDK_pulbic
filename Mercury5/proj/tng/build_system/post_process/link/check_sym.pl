#!/usr/bin/perl

use strict;
use Getopt::Std;


my $Version="v 1.1";
my $Date="Aug 2011";

##--------------------------------------------------------------------------------------------------
## Author  | Rev | Date     | Comment
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.0 | 17/05/11 | Creation
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.1 | 01/08/11 | Added %CHECK_FILE_HASH to avoid parsing same lib
##--------------------------------------------------------------------------------------------------

my $tool_chain=0;
my $out_folder=0;
my $Verbose=0;

my %opts;
getopts("c:o:v:h",\%opts);
if (exists $opts{c}) {$tool_chain=$opts{c};}    else{print"\n No tool-chain is specified!!\n\n";PrintHelp(); exit 1; }
if (exists $opts{o}) {$out_folder=$opts{o};}	else{print"\n No out folder is specified!!\n\n";PrintHelp(); exit 1; }
if (exists $opts{v}) {$Verbose=$opts{v};}
if (exists $opts{h}) {PrintHelp(); exit 1; }

print( "tool_chain=$tool_chain\n" );
print( "out_folder=$out_folder\n" );
print( "Verbose=$Verbose\n" );


#
# 1. get symbol table from each lib to $sym_file
#
my $lib_name;
my $lib_file ;
my $sym_folder = $out_folder."sym" ; 
my $sym_file = $sym_folder."/sym" ;
my $sym_file_sort = $sym_folder."/sym_sort" ;
my $line;

system("rm -fr $sym_folder");
system("mkdir $sym_folder");
system("rm -fr $sym_file");

open(SYM_BUF, "> $sym_file") or die "cannot open output \"$sym_file\"\n";

my %CHECK_FILE_HASH;
while( $#ARGV >= 0 )
{
	$lib_file = shift ;
	next if ( $lib_file =~ m/\/out\/.*\/out\// );
	next if( ( $CHECK_FILE_HASH{$lib_file} eq 1 ) );
	
	$CHECK_FILE_HASH{$lib_file} = 1;
	
	$lib_name = $lib_file ;
	$lib_name =~ s/([^\/]*\/)|(\.lib$)//g;

	# reserve for debug
	my $cur_sym_file = $sym_folder."/".$lib_name;
	
	if( $tool_chain eq "RVCTV22" )
	{
		system("armar --zs $lib_file > $cur_sym_file");
	}
	else
	{
	
	}
	system("dos2unix $cur_sym_file");

	open(TMP_BUF, "< $cur_sym_file") or die "cannot open output \"$cur_sym_file\"\n";
	while ($line=<TMP_BUF>)
	{
		$line =~ s/\n//g;
		print SYM_BUF $line, "\t", $lib_file, "\n" ;
	}
	close TMP_BUF;
}



#
# 2. sort $sym_file to $sym_file_sort
#
open(TMP_BUF, "< $sym_file") or die "cannot read \"$sym_file\" file\n";
my @sym_buf=<TMP_BUF>;
close(TMP_BUF);
my @sym_buf_sort = sort @sym_buf ;



#
# 3. check if there is duplicate symbol
#
open(TMP_BUF, "> $sym_file_sort") or die "cannot open output \"$sym_file_sort\"\n";
my $index = 0 ;
my $cur_symbol = 0 ;
my $pre_symbol = 0 ;
foreach $line (@sym_buf_sort)
{
	$cur_symbol = $line;
	$cur_symbol =~ s/(from\s.*)|(\s)//g;

	if( $index ne 0 )
	{		
		$pre_symbol = $sym_buf_sort[$index-1];
		$pre_symbol =~ s/(from\s.*)|(\s)//g;
		
		if( $cur_symbol eq $pre_symbol )
		{
			# reserve for dubugging
			#print TMP_BUF "2 ", check_is_dup_symbol( $line ). " :$line ";
			#print TMP_BUF "1 ", check_is_dup_symbol( $sym_buf_sort[$index-1] ), " :$sym_buf_sort[$index-1]";

			if( check_is_dup_symbol( $sym_buf_sort[$index-1] ) || check_is_dup_symbol($line )  )
			#if( check_is_dup_symbol( $line ) || check_is_dup_symbol( $sym_buf_sort[$index-1] ) )
			{
				print( "we got duplicate symbol: \n" );
				print( "\t\t $line" );
				print( "\t\t $sym_buf_sort[$index-1]" );
				print( "\n" );	 
			}
		}
	}

	#$sym_buf_sort[$index] = $cur_symbol ;
	$index++ ;
}
close TMP_BUF;


#
# check the symbol is duplicate sybmol or not
#
my %LIB_HASH;
my %I_SYM_HASH;
sub check_is_dup_symbol
{
	my $sym_info = shift ;

	$sym_info =~ m/(\w*)\s*from\s(\w*)\.o.*\.\/(.*)/;
	my $sym = $1 ;		# take sym name
	my $obj = $2 ;		# take obj name
	my $lib = "./".$3 ;	# take lib name
	dbg_print( "sym: ".$sym."\nobj: ".$obj."\nlib: ".$lib."\n" );
	
	#
	# the max length of i sym name we got from readeld is only 23
	# chech if it is 
	#
	$sym = substr( $sym, 0, 23 ) if( length($sym) >23 ) ;
	
	#
	# we can not just retutn, since there possible a duplicate symbol 
	#
	#return 0 if ( $I_SYM_HASH{$sym} eq 1 ) ;
	
	if( ( $LIB_HASH{$lib} ne 1 ) )
	{
		$LIB_HASH{$lib} = 1;
		
		if( $tool_chain eq "RVCTV22" )
		{
			system("readelf -s $lib > $out_folder\/sym\/".basename($lib)."\.sym");
			parsing_sym_RVCT22("$out_folder\/sym\/".basename($lib)."\.sym",basename($lib));
		}
		else
		{
		
		}
	}

	dbg_print( "\n" );
		
	#
	# check if it is i_sym
	#
	if( $I_SYM_HASH{basename($lib).$sym} ne 1 )
	{
		return 1 ;
	}
	else
	{
		return 0 ;
	}
	
}


#
# parsing sym info and record in I_SYM_HASH
#
sub parsing_sym_RVCT22{
	my $i_sym_file = shift ;
	my $i_lib_file = shift ;
	
	open(SYM_INFO, "< $i_sym_file") or die "cannot read \"$i_sym_file\" file\n";

	while (my $i_sym=<SYM_INFO>)
	{
		$i_sym =~ s/\n//g;
		
		next if ($i_sym =~ m/\$/);
		next if ($i_sym !~ m/i\./);
		
		if( $i_sym =~ s/.*i\.//g )
		{
			$I_SYM_HASH{$i_lib_file.$i_sym} = 1 ;
			dbg_print( "i_sym: $i_lib_file $i_sym\n" );	
		}
		else
		{
			$I_SYM_HASH{$i_lib_file.$i_sym} = 0 ;
		}
	}
	close SYM_INFO ;
}


#
# return base name
#
sub basename{
	my $file = shift ;
	$file =~ s/(.*\/)//g; 
	return $file;
}


#
# debug print
#
sub dbg_print {
  if ($Verbose >= 1) { printf shift; }
}


#
# print user guide
#
sub PrintHelp {
print <<"EOF";
Script to check multiple defined symbol
RDO - MStar Taiwan - $Date - version $Version
Usage:$0 [-c tool chain] [-o output folder] [-v verbose mode] [-h] [LIB FILES]
  -c: tool chain, specify the tool chain, only support 'RTVTV22' currently
  -o: output folder, specify the output folder to store symbol info
  -v: verbose mode, print debug messages, e.g. -v1
  -h: help, show this user guide
  [LIB FILES]: the libs u want to check if there are duplicate symbols 
EOF
exit 0;  
}

