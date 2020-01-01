#!/usr/bin/perl

use strict;
use diagnostics;
use Math::BigFloat;
use Getopt::Std;
use File::Path;

my $Version="v 1.0";
my $Date="Jun 2012";

##--------------------------------------------------------------------------------------------------
## Author  | Rev | Date     | Comment
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.0 | 06/08/12 | Creation, first version 
##--------------------------------------------------------------------------------------------------



my $LinkInfo;
my $Verbose=0;

my %opts;
getopts("l:v:h",\%opts);
if (exists $opts{h}) {PrintHelp(); exit 1; }
if (exists $opts{l}) {$LinkInfo=$opts{l};}	else{print"\n No Link Info is specified!!\n\n";PrintHelp(); exit 1; }
if (exists $opts{v}) {$Verbose=$opts{v};}




# 01
sub parsing_link_info_and_count_size()
{

	open(LINKINFFILE, "<".$LinkInfo) or die "Can't open link info file: $!";

	my $LoadRegionName;
	my $LoadRegionPreName;
	my $LoadRegionPreMaxSize=0 ;
	my $LoadRegionMaxSize;
	my $TotalExecutionRegionSize=0;

	while (<LINKINFFILE>) {
		chomp;

#	Load Region IRAM_REGION (Base: 0x0039af64, Size: 0x00004334, Max: 0xffffffff, ABSOLUTE)
#	Load Region IRAM_REGION2 (Base: 0x0039f298, Size: 0x00009c8c, Max: 0xffffffff, ABSOLUTE)
		if (m/Load Region (\S+) \(Base: 0x(\S+), Size: 0x(\S+), Max: 0x(\S+),.+/) 
		{
			$LoadRegionName = $1;
			$LoadRegionMaxSize = hex($4);


			# start check pre round 
			if( (0 < $LoadRegionPreMaxSize || 0 < $TotalExecutionRegionSize ) &&
			   ( $TotalExecutionRegionSize > $LoadRegionPreMaxSize  ) )
			{
				print "\n";
				print " error message: The total size of the execution regions in load region \n";
				print " error message: $LoadRegionPreName are larger than the size of load region \($LoadRegionPreMaxSize\) .\n";
				print " error message: Please reduce the size of execution region...    \n";
				print "\n";
				exit 1;
			}
	

			$TotalExecutionRegionSize = 0 ;

			next if ( $LoadRegionName =~ m/(SLDLM\_.+)|(EMMI\_SLDPM\_.*)/ );
			
			dbg_print("\nLoad region name=".$LoadRegionName."\tmax size=".$LoadRegionMaxSize."\n");

			$LoadRegionPreMaxSize = $LoadRegionMaxSize ;
			$LoadRegionPreName = $LoadRegionName ;
			if( $LoadRegionMaxSize == 0xffffffff ) 
			{
				dbg_print("\t no size limition!\n");
				next ;
			}
		}	
#	Execution Region IRAM_SECTION2 (Base: 0x1c001fb0, Size: 0x00009678, Max: 0xffffffff, OVERLAY)
#	Execution Region IRAM_SECTION2_ZI (Base: 0x1c00b628, Size: 0x000003ec, Max: 0xffffffff, ABSOLUTE, UNINIT)
		elsif (m/Execution Region (\S+) \(Base: 0x(\S+), Size: 0x(\S+),.+/)
		{
			my $ExecutionRegionName = $1 ;
			my $ExecutionRegionSize =hex($3);

			next if ( $ExecutionRegionName =~ m/(emmi\_sldpm.+)|(.+\.sldlm)/ ) ;
		
			dbg_print("  binary=".$1."\tbase address=0x".$2."\tsize=0x".$3."\n");

			$TotalExecutionRegionSize += $ExecutionRegionSize;
			
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

Usage:$0 [-l link.info] 
 [-b Binary file list] [-o output file] [-f folder] [-s SelectBin] 
 [-k KbSelectedBinSize] [-v verbose mode] [-h] 

  -l: link.info, we have to parse them to get load/execution information
  -h: help, show this user guide
EOF
}





####
#    code start from here !!
####
parsing_link_info_and_count_size();



