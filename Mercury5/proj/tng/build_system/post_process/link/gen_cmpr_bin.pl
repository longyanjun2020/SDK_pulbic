#!/usr/bin/perl

use strict;
use Getopt::Std;

use strict;
use diagnostics;
use Math::BigFloat;
use Getopt::Std;
use File::Path;
use List::Util qw[min max];

my $Version="v 2.4";
my $Date="May 2012";

##--------------------------------------------------------------------------------------------------
## Author  | Rev | Date     | Comment
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.0 | 10/28/11 | Creation, first version (ram text/data compression)
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.1 | 11/18/11 | add append uncompressed binary (ram text/data compression)
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.2 | 12/12/11 | add $CmprBinFolder/$ZiInfo for check log(dlchk)
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.3 | 12/28/11 | add segment load (rom RO compression)
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.4 | 01/12/12 | add option: \$CmprAlgo (compress algorithm)
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.5 | 01/31/12 | add segment load (rom RO compression [extend])
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.6 | 02/22/12 | add Dictionary to compression
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.7 | 03/05/12 | add checksum
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.8 | 03/06/12 | check KbSelectedBinSize
##--------------------------------------------------------------------------------------------------
##  Carl   | 2.0 | 03/19/12 | revise flow to make SELECTED_BIN to append after "no compress bin" 
##--------------------------------------------------------------------------------------------------
##  Carl   | 2.1 | 05/21/12 | process XRAM (0x1000:0000) for 16KB mmu table
##--------------------------------------------------------------------------------------------------
##  Carl   | 2.2 | 05/29/12 | check if RO/RW execution region in a load region are successive
##--------------------------------------------------------------------------------------------------
##  Carl   | 2.3 | 06/16/12 | fix compressed selected bin boundary case
##--------------------------------------------------------------------------------------------------
##  Carl   | 2.4 | 07/01/12 | fix compressed selected bin boundary case
##--------------------------------------------------------------------------------------------------


my $LinkInfo;
my $Output;
my $OutDir;
my $Verbose=0;
my $BinFolder;
my $CmprBinFolder;
my $BinList;
my $IsCompressed;
my $ZiInfo;
my $CmprAlgo;
my $SelectedBin=0;
my $KbSelectedBinSize=0;
my $Dictionary=0;
my $IsNand=0;
my $JumpInstrCmp=0;

my %opts;
getopts("l:b:o:f:s:v:c:k:z:d:n:i:h",\%opts);
if (exists $opts{h}) {PrintHelp(); exit 1; }
if (exists $opts{l}) {$LinkInfo=$opts{l};}	else{print"\n No Link Info is specified!!\n\n";PrintHelp(); exit 1; }
if (exists $opts{b}) {$BinList=$opts{b};}	else{print"\n No Cmpe Bin list is specified!!\n\n";PrintHelp(); exit 1; }
if (exists $opts{o}) {$Output=$opts{o};}	else{print"\n No Output file is specified!!\n\n";PrintHelp(); exit 1; }
if (exists $opts{f}) {$BinFolder=$opts{f};   $CmprBinFolder=$BinFolder."_Cmpr";   $ZiInfo="$CmprBinFolder/ZiInfo\.txt" }	else{print"\n No binary_folder is specified!!\n\n";PrintHelp(); exit 1; }
if (exists $opts{c}) {$IsCompressed=$opts{c};}else{print"\n No IsCompressed is specified!!\n\n";PrintHelp();exit 1;}
if (exists $opts{z}) {
    $CmprAlgo=$opts{z};  
    if( 0>$CmprAlgo || 2<$CmprAlgo ){ print"Wrong compress algo!\n\n"; PrintHelp(); exit 1; } 
  }
  else{print"\n No CmprAlgo is specified!!\n\n";PrintHelp();exit 1;}
if (exists $opts{s}) {$SelectedBin=$opts{s};
	if (exists $opts{k}) {$KbSelectedBinSize=$opts{k};}	else{print"\n No KbSelectedBinSize is specified!!\n\n";PrintHelp(); exit 1; }
}
if (exists $opts{d}) {$Dictionary=$opts{d};}
if (exists $opts{n}) {$IsNand=$opts{n};}
if (exists $opts{i}) {$JumpInstrCmp=$opts{i};}
if (exists $opts{v}) {$Verbose=$opts{v};}





#
# 1. parsing list
#
my %LoadRegionListHASH;
my %RO_RW_RegionHASH;
my %ZI_RegionHASH;
my %UNINIT_RegionHASH;
my %NO_CMPR_LOAD_RegionHASH;
my $line;
sub parsing_bin_list()
{
	open(BINLIST, "< $BinList") or die "cannot read \"$BinList\" file\n";
	
	while ($line=<BINLIST>)
	{
		last if($line =~ m/LOAD\_REGIONS\=/);
	}
	
	while ($line=<BINLIST>)
	{
		next if($line =~ m/(\#)/);
		last if($line =~ m/CMPR_\w*_REGIONS\=/);
		$line =~ s/(\s)|(\\)//g;
		if( $line ne "" )
		{
			$LoadRegionListHASH{$line} = "1";
			dbg_print("LOAD\t".$line."\n");
		}
	}
	
	while ($line=<BINLIST>)
	{
		next if($line =~ m/(\#)/);
		last if($line =~ m/CMPR_\w*_REGIONS\=/);
		$line =~ s/(\s)|(\\)//g;
		if( $line ne "" )
		{
			$RO_RW_RegionHASH{$line} = "1";
			dbg_print("RORW\t".$line."\n");
		}
	}
	while ($line=<BINLIST>)
	{
		next if($line =~ m/(\#)/);
		last if($line =~ m/CMPR_\w*_REGIONS\=/);
		$line =~ s/(\s)|(\\)//g;
		if( $line ne "" )
		{
			$ZI_RegionHASH{$line} = "1";
			dbg_print("ZI\t".$line."\n");
		}
	}
	while ($line=<BINLIST>)
	{
		next if($line =~ m/(\#)/);
		last if($line =~ m/CMPR_\w*_REGIONS\=/);
		$line =~ s/(\s)|(\\)//g;
		if( $line ne "")
		{
			$UNINIT_RegionHASH{$line} = "1";
			dbg_print("UNINIT\t".$line."\n");
		}
	}
	while ($line=<BINLIST>)
	{
		next if($line =~ m/(\#)/);
		last if($IsNand eq 1);
		$line =~ s/(\s)|(\\)//g;
		if( $line ne "")
		{
			$NO_CMPR_LOAD_RegionHASH{$line} = "1";
			dbg_print("MO_CMPR\t".$line."\n");
		}
	}
	
	close(BINLIST);
}


#
# 2. parsing link info & compress bin file
#
my @CmprBinToAppend;
sub parsing_link_info()
{

	my $LoadRegionName;
	my $LoadRegionSize;	
	my $tryToFindBaseAddress=0;

	#----- for check is RO/RW regions successive -----
	my $StartCheckIsRoRwRegionSuccessive=0;
	my $FirstExexutionRegionBaseAddress=0;
	my $LastExecutionRegionBaseAddress=0;
	my $LastExecutionRegionSize=0;
	#-------------------------------------------------

	
	my $cur_bin_size = -s $Output;	
	#0xFF0 : size of __BOOT_UNCOMPRESS__ 
	add_info_to_bin( 0xFF0, $cur_bin_size );


	# remove the element in @CmprBinToAppend
	@CmprBinToAppend = ();

	open(LINKINFFILE, "<".$LinkInfo) or die "Can't open link info file: $!";
	open(OUTPUT, ">>".$Output) or die "Can't open Output file: $!";
	unlink $ZiInfo if (-e "$ZiInfo");
	open(ZIINFO, ">".$ZiInfo) or die "Can't open ZiInfo file: $!";

	while (<LINKINFFILE>) {
		chomp;

#	Load Region IRAM_REGION (Base: 0x0039af64, Size: 0x00004334, Max: 0xffffffff, ABSOLUTE)
#	Load Region IRAM_REGION2 (Base: 0x0039f298, Size: 0x00009c8c, Max: 0xffffffff, ABSOLUTE)
		if (m/Load Region (\S+) \(Base: 0x(\S+), Size: 0x(\S+),.+/) 
		{
			next if ( !$LoadRegionListHASH{$1} || exists $NO_CMPR_LOAD_RegionHASH{$1} ) ;

			$LoadRegionName = $1;
			$LoadRegionSize = hex($3);
			
			dbg_print("Load region name=".$LoadRegionName."\tsize=0x".$LoadRegionSize."\n");
						
			$StartCheckIsRoRwRegionSuccessive=1;
			$FirstExexutionRegionBaseAddress=0;
			$LastExecutionRegionBaseAddress=0;
			$LastExecutionRegionSize=0;

			if( $LoadRegionSize eq 0 )
			{
				dbg_print("\t no content!\n");
				next ;
			}
			
			$tryToFindBaseAddress=1;
		
		}	
#	Execution Region IRAM_SECTION2_RW_RO_cmpr_bin (Base: 0x1c001fb0, Size: 0x00009678, Max: 0xffffffff, OVERLAY)
#	Execution Region IRAM_SECTION2_ZI_cmpr_bin (Base: 0x1c00b628, Size: 0x000003ec, Max: 0xffffffff, ABSOLUTE, UNINIT)
		elsif (m/Execution Region (\S+) \(Base: 0x(\S+), Size: 0x(\S+),.+/)
		{
			# check if there is any compressed execution region
			if( 1 eq $IsCompressed  )
			{
				if (m/Execution Region (\S+) \(Base: 0x(\S+), Size: 0x(\S+),.+COMPRESSED\[0x\S+\].*/) 
				{
					print "please add attribute \"NOCOMPRESS\" to execution \"$1\" in scatter file \n";
					print " <If there is any problem, please kindly contact with system team.>\n";
					exit 1 ;
				}
			}
			
			my $ExecutionRegionName = $1 ;
			my $ExecutionRegionBaseAddress =hex($2);
			my $ExecutionRegionSize =hex($3);
			my $ExecutionRegionSizeAfterCompressd=0;
			
			next if ( !$RO_RW_RegionHASH{$ExecutionRegionName} ) && ( !$ZI_RegionHASH{$ExecutionRegionName} ) ;
			
			dbg_print("binary=".$1."\tbase address=0x".$2."\tsize=0x".$3."\n");
			
			if( ( $UNINIT_RegionHASH{$ExecutionRegionName} ) )	
			{
				# do nothing !!!
			}
			elsif( ( $RO_RW_RegionHASH{$ExecutionRegionName} ) )
			{
				if( $tryToFindBaseAddress eq 1 && -e "$BinFolder/$ExecutionRegionName" )
				{				
					### note: take case the Load/Bin 
					
					my $TmpFileSize= -s "$BinFolder/$ExecutionRegionName";
					my $CheckSum = compute_DLM_checksum(0, "$BinFolder/$ExecutionRegionName", $TmpFileSize);
					
					my $CmpCmd = "tng/MSComprs.exe -f$BinFolder/$ExecutionRegionName -o$CmprBinFolder/$ExecutionRegionName"."_bin -a$CmprAlgo -s$TmpFileSize";
					$CmpCmd .= " -p$Dictionary" if( $Dictionary eq 1 );
					$CmpCmd .= " -i1" if( $JumpInstrCmp eq 1 );
					system("$CmpCmd");

					$ExecutionRegionSizeAfterCompressd = -s "$CmprBinFolder/$ExecutionRegionName"."_bin";
					dbg_print( "after Compress: ".$ExecutionRegionSizeAfterCompressd."\n" );
					push @CmprBinToAppend, "$CmprBinFolder/$ExecutionRegionName"."_bin";
					
					print OUTPUT pack("A12", "CMPR_".$LoadRegionName);
					print OUTPUT pack("I", "$ExecutionRegionBaseAddress");
					print OUTPUT pack("I", "$LoadRegionSize");  ### note: it is load size, not bin size
					$ExecutionRegionSizeAfterCompressd += 4 - ($ExecutionRegionSizeAfterCompressd%4) if ( ($ExecutionRegionSizeAfterCompressd%4) ne 0 );					
					print OUTPUT pack("I", "$ExecutionRegionSizeAfterCompressd");
					print OUTPUT pack("I", "$CheckSum");
					dbg_print( "checksum: $CheckSum \n" );
					$tryToFindBaseAddress = 0 ;
				}
				elsif( $ExecutionRegionName ne "XRAM" )
				{
					$tryToFindBaseAddress = 0 ;
				}

				if( $StartCheckIsRoRwRegionSuccessive eq "1" )
				{
					$StartCheckIsRoRwRegionSuccessive = 2 ;
					$FirstExexutionRegionBaseAddress = $ExecutionRegionBaseAddress ;
					$FirstExexutionRegionBaseAddress += 0x4000 if ( $ExecutionRegionName eq "XRAM" )
				}
				elsif( $StartCheckIsRoRwRegionSuccessive eq "3" )
				{
					print "\nerror message: There are some ZI execution regions are inserted \n";
					print "error message: bwtween RO/RW regions in load region $LoadRegionName.\n";
					print "error message: Please place the ZI region after RO/RW region\n\n";
					exit 1;
				}
				$LastExecutionRegionBaseAddress = $ExecutionRegionBaseAddress ;
				$LastExecutionRegionSize = $ExecutionRegionSize ;	



				# ---------- error handle: if we find ZI in RO/RW section, return 1 to stop build process. ----------
				my $space_line_count = 0 ;
				while ($line=<LINKINFFILE>) 
				{
					# if there is no RO/RW/ZI in this section --> break
					last if($line =~ m/(No section assigned to this execution region)/);
					# count space line
					$space_line_count+=1 if($line =~ m/^\s*$/);
					# over
					last if ($space_line_count>=3);
					if($line =~ m/(Zero   RW)/)
					{
						if($line =~ m/\.mmu_table_16/)
						{
							dbg_print("match mmu_table_16\n");
						}
						else
						{
							print " <\"".$line."\" should not be placed in ".$ExecutionRegionName." execution region !!!>\n";
							print " < please move it to a ZI execution region>\n";
							print " <If there is any problem, please kindly contact with system team.>\n";
							exit 1 ;
						}
					}
				}
				# --------------------
			}
			elsif( ( $ZI_RegionHASH{$ExecutionRegionName} ) )	
			{
				print OUTPUT pack("A12", "CMPR___ZI___");
				print OUTPUT pack("I", "$ExecutionRegionBaseAddress");
				print OUTPUT pack("I", "$ExecutionRegionSize");
				print OUTPUT pack("I", 0);
				print OUTPUT pack("I", 0);

				# write zi info to 
				print ZIINFO "$ExecutionRegionName   $ExecutionRegionSize\n";
				

				if( $StartCheckIsRoRwRegionSuccessive eq "2" )
				{
					if( $LastExecutionRegionBaseAddress + $LastExecutionRegionSize - $FirstExexutionRegionBaseAddress != $LoadRegionSize )
					{
						print "\nerror message: The start address of non-first execution region should not be\n";
						print "error message: assigned an absolute address in load region: $LoadRegionName.\n";
						print "error message: Please place the region to a dedicated load region,\n";
						print "error message: or use +0 attribute instead of using absolute address\n\n";
						exit 1;
					}
				}
				$StartCheckIsRoRwRegionSuccessive = 3 ;


				# --------- error handle: if we find RO/RW in ZI section, return 1 to stop build process. ---------
				while ($line=<LINKINFFILE>) 
				{
					# if there is no RO/RW/ZI or ZI is found in this section --> break
					last if($line =~ m/(No section assigned to this execution region)|(Zero   RW)/);
					#if RO or RW is found...  --> return error code 1!!!
					if($line =~ m/(Code   RO)|(Data   RW)/)
					{
						print " <\"".$line."\" should not be placed in ".$ExecutionRegionName." execution region !!!>\n";
						print " < please move it to a RO/RW execution region>\n";
						print " <If there is any problem, please kindly contact with system team.>\n";
						exit 1 ;
					}
				}
				# --------------------

			}
			else
			{
				print "$ExecutionRegionName !!\n";
			}
			
		}
	}

	close LINKINFFILE;
	close OUTPUT;
	close ZIINFO;

}

#
# 2-1 compute checksum
#
sub compute_DLM_checksum()
{
	my $CheckSum = shift ; # the start value 
	my $Buffer = shift ;
	my $Size = shift ;

	my $TmpBuf;

	open(FILE, $Buffer) or die "can't open $Buffer: $!"; 
	binmode(FILE);  

	while( $Size ne 0 )	{
		for( my $_i=0; $_i<=3;++$_i ){
			read(FILE, $TmpBuf, 1);
			$TmpBuf = ord($TmpBuf) ;
			$CheckSum ^= $TmpBuf*(256**$_i);
		}
		$Size-=4;
	}
  	return $CheckSum;
}



#
# 3. append binary
#

sub append_cmpr_bin()
{
	print( "There are ".($#CmprBinToAppend+1)." comp bin files\n");

	for (my $i = 0; $i <$#CmprBinToAppend+1; $i++) {
		print( $CmprBinToAppend[$i]."\n" );
		my $ExecutionRegionSizeAfterCompressd = -s $CmprBinToAppend[$i];
		open(TMP, ">>".$CmprBinToAppend[$i]) or die "Can't open Output file: $!";
		while ( ($ExecutionRegionSizeAfterCompressd%4) ne 0 )
		{
			print TMP pack("c", 1);
			$ExecutionRegionSizeAfterCompressd++;
		}
		close TMP;
		system("cat ".$CmprBinToAppend[$i]." >> ".$Output);
	}
}




# 101. only append bin
sub append_bin()
{

	open(LINKINFFILE, "<".$LinkInfo) or die "Can't open link info file: $!";
	open(OUTPUT, ">>".$Output) or die "Can't open Output file: $!";

	my $LoadRegionName;
	my $LoadRegionSize;	
	my $tryToFindBaseAddress=0;

	while (<LINKINFFILE>) {
		chomp;

#	Load Region IRAM_REGION (Base: 0x0039af64, Size: 0x00004334, Max: 0xffffffff, ABSOLUTE)
#	Load Region IRAM_REGION2 (Base: 0x0039f298, Size: 0x00009c8c, Max: 0xffffffff, ABSOLUTE)
		if (m/Load Region (\S+) \(Base: 0x(\S+), Size: 0x(\S+),.+/) 
		{
			next if ( !$LoadRegionListHASH{$1} || exists $NO_CMPR_LOAD_RegionHASH{$1} ) ;

			$LoadRegionName = $1;
			$LoadRegionSize = hex($3);
			
			dbg_print("Load region name=".$LoadRegionName."\tsize=0x".$LoadRegionSize."\n");
						
			if( $LoadRegionSize eq 0 )
			{
				dbg_print("\t no content!\n");
				next ;
			}
		
			$tryToFindBaseAddress=1;
		
		}	
#	Execution Region IRAM_SECTION2_RW_RO_cmpr_bin (Base: 0x1c001fb0, Size: 0x00009678, Max: 0xffffffff, OVERLAY)
#	Execution Region IRAM_SECTION2_ZI_cmpr_bin (Base: 0x1c00b628, Size: 0x000003ec, Max: 0xffffffff, ABSOLUTE, UNINIT)
		elsif (m/Execution Region (\S+) \(Base: 0x(\S+), Size: 0x(\S+),.+/)
		{
			next if ( $tryToFindBaseAddress eq 0 );
		
			my $ExecutionRegionName = $1 ;
			my $ExecutionRegionBaseAddress =hex($2);
			my $ExecutionRegionSize =hex($3);
			my $ExecutionRegionSizeAfterCompressd=0;
		
			next if ( !$RO_RW_RegionHASH{$ExecutionRegionName} )  ;
			
			dbg_print("  binary=".$1."\tbase address=0x".$2."\tsize=0x".$3."\n");
			
			if( ( $UNINIT_RegionHASH{$ExecutionRegionName} ) || ( $ZI_RegionHASH{$ExecutionRegionName} ) )	
			{
				# do nothing !!!
			}
			elsif( ( $RO_RW_RegionHASH{$ExecutionRegionName} ) && -e $BinFolder."/".$ExecutionRegionName )
			{
				$tryToFindBaseAddress = 0 ;
				print("    append binary=".$ExecutionRegionName."\n");
				print("      cat ".$BinFolder."/".$ExecutionRegionName." >> ".$Output."\n\n");
			
				system("cat ".$BinFolder."/".$ExecutionRegionName." >> ".$Output);
			}
		}
	}

	close LINKINFFILE;
	close OUTPUT;
}




#
# 201. parsing link info to get the address of SELECTED_BIN and SELECTED_BIN_LOAD 
#
my $FlashLoadRegionName = "SELECTED_BIN_LOAD";
my $FlashLoadRegionSize=0;	
my $FlashExecutionRegionName = "SELECTED_BIN" ;
my $FlashExecutionRegionBaseAddress=0;
my $FlashExecutionRegionSize=0;
sub parsing_link_info_for_SELECTED_BIN
{
	open(LINKINFFILE, "<".$LinkInfo) or die "Can't open link info file: $!";
	open(OUTPUT, ">>".$Output) or die "Can't open Output file: $!";


	while (<LINKINFFILE>) {
		chomp;
# pattern:
# Load Region SELECTED_BIN_LOAD (Base: 0x12345678, Size: 0x12345678, Max: 0xffffffff, ABSOLUTE)
		if (m/Load Region $FlashLoadRegionName \(Base: 0x\S+, Size: 0x(\S+),.+/) 
		{
			$FlashLoadRegionSize = hex($1);
			
			print("Load region $FlashLoadRegionName\tsize=0x$1 \($FlashLoadRegionSize\)\n");
						
			if( $FlashLoadRegionSize eq 0 )
			{
				print("\t SELECTED_BIN_LOAD no content!\n");
				exit 1 ;
			}
		}	
# pattern:
# Execution Region SELECTED_BIN (Base: 0x12345678, Size: 0x12345678, Max: 0xffffffff, ABSOLUTE, UNINIT)
		elsif (m/Execution Region $FlashExecutionRegionName \(Base: 0x(\S+), Size: 0x(\S+),.+/)
		{
			$FlashExecutionRegionBaseAddress =hex($1);
			$FlashExecutionRegionSize =hex($2);
		
			dbg_print("binary SELECTED_BIN\tbase address=0x$1 \($FlashExecutionRegionBaseAddress\)  \tsize=0x$2 \($FlashExecutionRegionSize\)\n");
			
			
				
		}
	}

	close LINKINFFILE;
}




#
# 202. insert binary size into binary
#
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
# 203. append selected binary
# parsing report to compress the file with high compress ratio
#
sub compress_select_cmpr_bin()
{

	my $FlashExecutionRegionSizeAfterCompressd=0;
	my $Cmpr_report = $CmprBinFolder."\/cmpr_report\.txt";
	my %BinBlockSizeHASH;
	my @BinBlockSizeArray;
	my @BinBlockIdArray;
	my $TotalCompressedSize = $KbSelectedBinSize*1024 ; # 640KB
#	my $CompressedBlockSize = 65536 ; # 64KB
	my $CompressedBlockSize = 4096 ; # 4KB, 4KB is batter than 64KB 
	my $NumberOfCompressedBlock = $TotalCompressedSize/$CompressedBlockSize ;
	my $AppendHeader = "";
	my $RealLoadSize = -s "$BinFolder/$FlashExecutionRegionName";
	my $Selected_bin_header= "";


	if( $KbSelectedBinSize%4 ne 0 )
	{
		print "error message: SELECTED_BIN_SIZE = $KbSelectedBinSize\n";
		print "error message: SELECTED_BIN_SIZE must be the times of 4\n";
		print "error message: please reconfig SELECTED_BIN_SIZE in options_\$\(product name\)\.mak \n";
		exit 1;
	}


	if( $FlashLoadRegionSize eq 0 || $FlashExecutionRegionName eq 0 || $FlashExecutionRegionBaseAddress eq 0 )
	{
		print "error message: \$FlashLoadRegionSize = $FlashLoadRegionSize\n";
		print "error message: \$FlashExecutionRegionName = $FlashExecutionRegionName\n";
		print "error message: \$FlashExecutionRegionBaseAddress = $FlashExecutionRegionBaseAddress\n";
		exit 1;
	}


	# remove the element in @CmprBinToAppend
	@CmprBinToAppend = ();


if( $KbSelectedBinSize ne 0 )
{

	if( $TotalCompressedSize > $RealLoadSize )
	{
		print "error message: You can place whole XRAM load to XRAM,\n";  
		print "error message: please turn off __COMPRESS_SELECTED_BIN__ and turn on __EXTRACT_BOOT_IMAGE__\n";  
		exit 1;
	}


	#
	# align to $CompressedBlockSize
	#
	# close and reopen OUTPUT because the cache would mislead the real size of bin size
	my $diff_size = -s $Output;
	open(OUTPUT, ">>".$Output) or die "Can't open Output file: $!";
	while ( ($diff_size % $CompressedBlockSize) ne 0 )
	{
		print OUTPUT pack("c", 1);
		$diff_size++;
	}
	close OUTPUT;


	my $CmpCmd = "tng/MSComprs.exe -f$BinFolder/$FlashExecutionRegionName -o./tmp.bin -a2 -s$CompressedBlockSize -r$Cmpr_report";
	$CmpCmd .= " -p$Dictionary" if( $Dictionary eq 1 );
	$CmpCmd .= " -i1" if( $JumpInstrCmp eq 1 );
	system($CmpCmd);

	
	unlink("./tmp.bin") if ( -e "./tmp.bin" );

	
	#
	# take the min X block, X = min($NumberOfCompressedBlock, smallest size blocks )
	#
	open(CMPR_REPORT, "<".$Cmpr_report) or die "Can't open file: $!";
	while ( my $line = <CMPR_REPORT>) 
	{
		# pattern:
		#block 0 input 65536 output 48183
		#block 1 input 65536 output 46874
		
		if( $line =~ m/block (\d+) input (\d+) output (\d+)/g )
		{
			my $Id = $1;
			my $InputSize = $2;
			my $OutputSize = $3;

			$BinBlockSizeHASH{$OutputSize} = $Id if ( $InputSize == $CompressedBlockSize );	
		}
		else
		{
			print "error message: unknow pattern in $Cmpr_report\n\"$line\"";
		}
		
	}
	close CMPR_REPORT;

	@BinBlockSizeArray = sort keys( %BinBlockSizeHASH );
	@BinBlockSizeArray = @BinBlockSizeArray[0..(min($NumberOfCompressedBlock-1, $#BinBlockSizeArray))];
	#print( map { $_."\n" } @BinBlockSizeArray);
	


	#
	# collect the id 
	#
	my $j=0;
	for( ; $j<$NumberOfCompressedBlock && ($#BinBlockIdArray+1) < $NumberOfCompressedBlock;$j+=1 )
	{
		open(CMPR_REPORT, "<".$Cmpr_report) or die "Can't open file: $!";
		while ( my $line = <CMPR_REPORT>) 
		{
			# pattern:
			#block 0 input 65536 output 48183
			#block 1 input 65536 output 46874
			
			if( $line =~ m/block (\d+) input (\d+) output (\d+)/g )
			{
				my $Id = $1;
				my $OutputSize = $3;
				
				if( grep{ $OutputSize eq $_ } @BinBlockSizeArray[$j..($j+0)] )
				{
					push @BinBlockIdArray, $Id ;
					last if ( ($#BinBlockIdArray+1) >= $NumberOfCompressedBlock  );
				}
			}
			
		}
		close CMPR_REPORT;
	}
#	@BinBlockIdArray = @BinBlockIdArray[0..($NumberOfCompressedBlock-1)];
#	@BinBlockIdArray = sort { $a <=> $b } @BinBlockIdArray;
	#print( map { $_."\t" } @BinBlockIdArray);






	# round 0: append file to OUTPUT
	# round 1: append header to OUTPUT
	my $round = 0 ;
	my $NoCompressedBinBuffer;
	my $NoCompressedBin;
	my $CompressedBinBuffer;
	my $CompressedBin;


GOTO_APPEDN_INFO_TO_BIN:


	if( $round ne 0 )
	{
	 	my $cur_bin_size = -s $Output;	
		#0xFFC : addr of sleceted bin header 
		add_info_to_bin( 0xFFC, $cur_bin_size );
	}

	#
	# start generated "no compressed" bin
	#
	open(CMPR_REPORT, "<".$Cmpr_report) or die "Can't open file: $!";
	open(CMPR_BIN, "<".$BinFolder."/".$FlashExecutionRegionName) or die "Can't open file: $!";
	open(OUTPUT, ">>".$Output) or die "Can't open Output file: $!";

	mkdir($CmprBinFolder."/SelectBin");
	$NoCompressedBinBuffer="";
	while ( my $line = <CMPR_REPORT>) 
	{
		$line =~ m/block (\d+) input (\d+) output (\d+)/g ;
		my $Id = $1;
		my $InputSize = $2;
		my $OutputSize = $3;
		my $OriBin = $CmprBinFolder."/SelectBin/".$Id;
		my $NewBin = $CmprBinFolder."/SelectBin/".$Id."_bin";

		# divide small bin
		my $tmp_buf;
		read CMPR_BIN, $tmp_buf, $InputSize;
			
		#no compress
		if( !grep{ $Id eq $_ } @BinBlockIdArray  )
		{
			if( $round eq 0 )
			{
				$NoCompressedBinBuffer .= $tmp_buf;
			}
			else
			{
				print OUTPUT pack("A8", "_NOCMPR_");
				print OUTPUT pack("I", "$InputSize");
				print OUTPUT pack("I", "$Id");
				print OUTPUT pack("I", "$InputSize"); 
			}
		}
	}
	close CMPR_BIN;
	close CMPR_REPORT;
	close OUTPUT;

	if( $round eq 0 )
	{
		$NoCompressedBin = $CmprBinFolder."/SelectBin/NoCompressedBin";
		open (TMP_CMPR_BIN, ">".$NoCompressedBin) or die "Can't open file: $!";
		print TMP_CMPR_BIN $NoCompressedBinBuffer;
		close TMP_CMPR_BIN;
		push @CmprBinToAppend, $NoCompressedBin;
	}


	#
	# start generated "compressed" bin
	#
	open(CMPR_REPORT, "<".$Cmpr_report) or die "Can't open file: $!";
	open(CMPR_BIN, "<".$BinFolder."/".$FlashExecutionRegionName) or die "Can't open file: $!";
	open(OUTPUT, ">>".$Output) or die "Can't open Output file: $!";

	mkdir($CmprBinFolder."/SelectBin");
	$CompressedBinBuffer="";
	while ( my $line = <CMPR_REPORT>) 
	{
		$line =~ m/block (\d+) input (\d+) output (\d+)/g ;
		my $Id = $1;
		my $InputSize = $2;
		my $OutputSize = $3;
		my $OriBin = $CmprBinFolder."/SelectBin/".$Id;
		my $NewBin = $CmprBinFolder."/SelectBin/".$Id."_bin";

		my $tmp_buf;
		read CMPR_BIN, $tmp_buf, $InputSize;
			
		if( grep{ $Id eq $_ } @BinBlockIdArray  )
		{
			#comprress;
			if( $round eq 0 )
			{
				$CompressedBinBuffer .= $tmp_buf;
			}
			else
			{
				print OUTPUT pack("A8", "__CMPR__");
				print OUTPUT pack("I", "$InputSize");
				print OUTPUT pack("I", "$Id");
				$OutputSize += 20;  # a compressed bin need a 20 byte header
				$OutputSize += 4 - ($OutputSize%4) if ( ($OutputSize%4) ne 0 ) ;
				print OUTPUT pack("I", "$OutputSize");			
			}
		}
	}
	close CMPR_BIN;
	close CMPR_REPORT;
	close OUTPUT;

	if( $round eq 0 )
	{
		$CompressedBin = $CmprBinFolder."/SelectBin/CompressedBin";
		open (TMP_CMPR_BIN, ">".$CompressedBin) or die "Can't open file: $!";
		print TMP_CMPR_BIN $CompressedBinBuffer;
		close TMP_CMPR_BIN;
	
		my $CmpCmd = "tng/MSComprs.exe -f$CompressedBin -o$CompressedBin"."_bin -a2 -s$TotalCompressedSize";
		$CmpCmd .= " -p$Dictionary" if( $Dictionary eq 1 );
		$CmpCmd .= " -i1" if( $JumpInstrCmp eq 1 );
		system("$CmpCmd");
	
		push @CmprBinToAppend, $CompressedBin."_bin";

	}

	if( $round eq 0 )
	{
		# 3. append binary
		append_cmpr_bin();

		$round = 1 ;
		goto GOTO_APPEDN_INFO_TO_BIN; 
	}


}
else
{

	#
	# no compression, only append, no align...
	#
	push @CmprBinToAppend, "$BinFolder/$FlashExecutionRegionName";
	append_cmpr_bin();

	my $cur_bin_size = -s $Output;	
	#0xFFC : size of selected bin 
	add_info_to_bin( 0xFFC, $cur_bin_size );

}


	# 202. add header address  "So that we can take the headers"

	my $tmp=$KbSelectedBinSize*1024;	
	#0xFF4 : size of selected bin 
	add_info_to_bin( 0xFF4, $tmp );
		
	#0xFF8 : size of SELECTED_BIN_LOAD (selected bin pool)
	add_info_to_bin( 0xFF8, $FlashLoadRegionSize );


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
  -b: binary file list, specify which load should be compressed. 
      And which region are RO_RW/ZI/UNINIT region
  -o: output file, the body of binary file L\$\(product_name\).bin
  -f: folder, specify the folder which contains uncompressed loads
  -c: IsCompressed, specified the binary files is compressed or not (0:NO, 1:Yes)
  -z: CmprAlgo, 1:zlib, 2:lzma
  -s: SelectBin, 0:(default) __EXTRACT_BOOT_IMAGE__, 1:__COMPRESS_SELECTED_BIN__
  -k: KbSelectedBinSize, size of selected bin in KB
  -d: Dictionary
  -v: verbose mode, print debug messages, e.g. -v1
  -h: help, show this user guide
EOF
}





####
#    code start from here !!
####
if( $IsCompressed eq 1 )
{

	# 1. parsing list
	parsing_bin_list();


	#
	# compressed selected bin 
	# we move it before '2.parsing_link_info' in order to make the SELECTED_BIN append after 'no compressed bin'
	#
	if( $SelectedBin eq 1 )
	{
		# 201. parsing link info to get the address of SELECTED_BIN_LOAD and SELECTED_BIN 
		parsing_link_info_for_SELECTED_BIN();

		# 203. compress selected binary
		compress_select_cmpr_bin();
	}


	#
	# ram text data compression
	#

	# 2. parsing link info & compress bin file
	parsing_link_info();

	# 3. append binary
	append_cmpr_bin();


}
elsif( $IsCompressed eq 0 )
{
	# 1. parsing list
	parsing_bin_list();


	# 101. only append bin
	append_bin();
}
else
{
	print "Unknow parameter: -c".$IsCompressed." !!\n";
	exit 1;
}



