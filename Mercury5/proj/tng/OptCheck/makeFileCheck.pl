#!/usr/bin/perl
use strict;

my $runMode = 1; # 0: to parse file and save data, 1: check file format, 2: to get the compile option list
my $dbgOutput = 0;

my $makFile;
my $opNameFile = "d:/_opName.txt";
my $descFile = "d:/_desc.txt";
my $preVarTrueFile = "d:/_preVarTrue.txt";
my $preVarFalseFile = "d:/_preVarFalse.txt";
my $opSelFile = "d:/_opSel.txt";
my $opFile = "d:/_op.txt";
	
my $featurName;
my $dscription;
my $preVariableTrue;
my $preVariableFalse;
my $optionSelection;
my $compileOption;
my $compileOptionValue;

my @outfileData = ();
my @optionTmp = ();
my @optionValTmp = ();

my @compileOptionBlock;
my $block;
my $blankLine;
my $commentBlock;
my $c1;
my $c2;
my $c3;
my $c4;
my $c5;
my $c6;
my $type;
my $skip;
my $line;
my $found;
my @file;

if (($#ARGV+1) == 3)
{
  ## usage: perl makeFileCheck.pl get_compile_option_list inputfile outputfile

	if($ARGV[0] eq "get_compile_option_list")
	{
		$runMode = 2; # 2: to get the compile option list
	}
	else
	{
  	print "usage: perl makeFileCheck.pl get_compile_option_list inputfile outputfile\n";
		exit 1;
	}
}
elsif (($#ARGV+1) != 2)
{
  print "usage: perl makeFileCheck.pl check D:/EMMI/EMMI/mainline/proj/mak/options_8532_64_32_mb406g.mak\n";
  exit 1;
}

if($ARGV[1] eq "check")
{
	$runMode = 1; #1: check file format
}

if($ARGV[1] eq "parse")
{
	$runMode = 0; # 0: to parse file and save data
}

$makFile = $ARGV[1];

if (! -e "$makFile")
{ 
 print "File does not exist.\n";
 print "File: $makFile\n";
 exit 1;
} 


if($runMode == 0) # 0: to parse file and save data
{
	unlink $opNameFile;
	unlink $descFile;
	unlink $preVarTrueFile;
	unlink $preVarFalseFile;
	unlink $opSelFile;
	unlink $opFile;
	
	open (OPNAMEFILE,">$opNameFile") || die("Cannot Open File $opNameFile");
	open (DESCFILE,">$descFile") || die("Cannot Open File $descFile");
	open (PREVARTRUEFILE,">$preVarTrueFile") || die("Cannot Open File $preVarTrueFile");
	open (PREVARFALSEFILE,">$preVarFalseFile") || die("Cannot Open File $preVarFalseFile");
	open (OPSELFILE,">$opSelFile") || die("Cannot Open File $opSelFile");
	open (OPFILE,">$opFile") || die("Cannot Open File $opFile");
}

if($runMode == 2) # 2: to get the compile option list
{
	$opFile = $ARGV[2];
	unlink $opFile;
	open (OPFILE,">>$opFile") || die("Cannot Open File $opFile");
}

print "$makFile\n";
print "File format checking...\n";
open(FILE, "<$makFile");
@file = <FILE>;
close(FILE);

$block = 0;
$blankLine = 0;
$commentBlock = 0;
$c1 = 0;
$c2 = 0;
$c3 = 0;
$c4 = 0;
$c5 = 0;
$c6 = 0;
$type = 0;

$skip = 0;
$line = 0;

foreach (@file)
{
	$line += 1;
	chomp;
	s/\012$//;
	s/\015$//;
	
	if($skip == 1)
	{
		if($dbgOutput == 1)
		{
			print "$_\n";
		}		
		if($runMode == 2) # 2: to get the compile option list			
		{
			push @outfileData, "$_\n";
		}
		next;
	}		
	
	if(/^\s*$/ || $commentBlock == 1)
	{
		if($block == 1)
		{
			$blankLine = 0;
			foreach (@compileOptionBlock)
			{			
				if(/# ?Feature_Name\s*=\s*(.*)/)
				{				
					$featurName = $1;
					$c1 = 1;
					$type = 1;
					next;
				}
				if(/# ?Description\s*=\s*(.*)/)
				{
					$dscription = $1;
					$c2 = 1;
					$type = 2;
					if ( $c3 == 1 || $c4 == 1 || $c5 == 1 || $c6 == 1 )
					{
						print "ERROR: Format incorrect!![2] Line: $line. The tag is in disorder.\n\n";
						exit 1;
					}	
					next;
				}
				if(/# ?Pre_Variable_True\s*=\s*(.*)/)
				{
					$preVariableTrue = $1;
					$c3 = 1;
					$type = 3;
					if ( $c4 == 1 || $c5 == 1 || $c6 == 1 )
					{
						print "ERROR: Format incorrect!![3] Line: $line. The tag is in disorder.\n\n";
						exit 1;
					}							
					next;
				}
				if(/# ?Pre_Variable_False\s*=\s*(.*)/)
				{
					$preVariableFalse = $1;
					$c4 = 1;
					$type = 4;
					if ( $c5 == 1 || $c6 == 1 )
					{
						print "ERROR: Format incorrect!![4] Line: $line. The tag is in disorder.\n\n";
						exit 1;
					}						
					next;
				}
				if(/# ?Option_Selection\s*=\s*(.*)/)
				{
					$optionSelection = $1;
					$c5 = 1;
					$type = 5;
					if ( $c6 == 1 )
					{
						print "ERROR: Format incorrect!![5] Line: $line. The tag is in disorder.\n\n";
						exit 1;
					}							
					next;
				}
				
				if(/# ?Pre_Condition_On\s*=\s*(.*)/)
				{
					print "ERROR: Format incorrect!![5] Line: $line. \"Pre_Condition_On\" is no longer used.\n\n";
					exit 1;
				}
				if(/# ?Pre_Condition_Off\s*=\s*(.*)/)
				{
					print "ERROR: Format incorrect!![5] Line: $line. \"Pre_Condition_Off\" is no longer used.\n\n";
					exit 1;
				}				
				if(/(.*?)\s*=\s*(.*)/)
				{	
				    my $tmp = $1;
				    
                    if($tmp =~ /SMART_NUMBER_FILTER_SUPPORT & SMART_ALPHABET_FILTER_SUPPORT/)
				    {
				        next;
				    }		    
				    
					if($c6 == 1)
					{
						if($runMode == 2) # 2: to get the compile option list	
						{
							my @field1 = split(" ", $compileOptionValue);
							
							if(@field1 == 1)
							{
								my @field2 = split(" ", $compileOption);
								
								if(@field2 == 1)
								{
									$compileOption =~ s/#//g;
									push @optionTmp, "$compileOption";
									push @optionValTmp, "$compileOptionValue";
								}
							}
						}						
					}
					
					$compileOption = $tmp;
					$compileOptionValue = $2;
					$c6 = 1;
					next;
				}
					
				if (/^# ?(.*)/)
				{
					if($type == 1)
					{
						$featurName = $featurName . " $1";
					}						
					if($type == 2)
					{
						$dscription = $dscription . " $1";
					}
					if($type == 3)
					{
						$preVariableTrue = $preVariableTrue . " $1";							
					}
					if($type == 4)
					{
						$preVariableFalse = $preVariableFalse . " $1";
					}
					if($type == 5)
					{
						$optionSelection = $optionSelection . " $1";
					}
				}
							
			}	#foreach (@compileOptionBlock)
			
			if($dbgOutput == 1)
			{
				print "Feature_Name = $featurName\n";
				print "Description = $dscription\n";
				print "Pre_Variable_True = $preVariableTrue\n";
				print "Pre_Variable_False = $preVariableFalse\n";
				print "Option_Selection = $optionSelection\n";
				print "$compileOption = $compileOptionValue\n";
				print "\n";
			}
			if($runMode == 0)# 0: to parse file and save data
			{				
				print OPNAMEFILE "$featurName\n";
				print DESCFILE "$dscription\n";
				print PREVARTRUEFILE "$preVariableTrue\n";
				print PREVARFALSEFILE "$preVariableFalse\n";
				print OPSELFILE "$optionSelection\n";
				print OPFILE "$compileOption\n";
			}
			if($runMode == 2) # 2: to get the compile option list
			{
				foreach(@optionTmp)
				{
					print OPFILE "$_\n";
				}
				if($compileOption =~ /PP_OPT_COMMON \+/)
				{
					if($compileOptionValue ne "")
					{
						print OPFILE "$compileOptionValue\n";
						my @field = split(" ", $compileOptionValue);
							
						if(@field ne 1)
						{
							print "ERROR: unexpected error! Value = $compileOptionValue\n";
							exit 1;
						}
					}
				}
				else
				{
					my $tmp = $compileOption;
					
					$tmp =~ s/#//g;
					print OPFILE "$tmp\n";
				}
				
				push @outfileData, "# Feature_Name = $featurName\n";
				push @outfileData, "# Description = $dscription\n";
				push @outfileData, "# Pre_Variable_True = $preVariableTrue\n";
				push @outfileData, "# Pre_Variable_False = $preVariableFalse\n";
				push @outfileData, "# Option_Selection = $optionSelection\n";
				push @outfileData, "$compileOption = $compileOptionValue\n";				
			}
			if( $c1 == 0 || $c2 == 0 || $c3 == 0 || $c4 == 0 || $c5 == 0 || $c6 == 0 )
			{
				print "ERROR: Format incorrect, ";
				if($c1 == 0)
				{
					print "can not find Feature_Name tag.\n";
				}
				if($c2 == 0)
				{
					print "can not find Description tag.\n";
				}
				if($c3 == 0)
				{
					print "can not find Pre_Variable_True tag.\n";
				}
				if($c4 == 0)
				{
					print "can not find Pre_Variable_False tag.\n";
				}
				if($c5 == 0)
				{
					print "can not find Option_Selection tag.\n";
				}
				if($c6 == 0)
				{
					print "no compile opton.\n";
				}		
				print "\n";
				print "Feature_Name = $featurName\n";
				print "Description = $dscription\n";
				print "Pre_Variable_True = $preVariableTrue\n";
				print "Pre_Variable_False = $preVariableFalse\n";
				print "Option_Selection = $optionSelection\n";
				print "$compileOption = $compileOptionValue\n";
				print "\n";
				exit 1;
			}								
		}#if($block == 1)
		else
		{
			if($blankLine == 1)
			{
				print "ERROR: Format incorrect!![6] Line: $line. Please help remove the unnecessary blank line.\n\n";
				exit 1;
			}
		}#if($block == 1)
	
		if($runMode == 2) # 2: to get the compile option list		
		{
			push @outfileData, "$_\n";
		}
		
		@optionTmp = ();
		@optionValTmp = ();
		$blankLine = 1;
		$c1 = 0;
		$c2 = 0;
		$c3 = 0;
		$c4 = 0;
		$c5 = 0;
		$c6 = 0;
		$featurName = "";
		$dscription = "";
		$preVariableTrue = "";
		$preVariableFalse = "";
		$optionSelection = "";
		$compileOption = "";
		$compileOptionValue = "";
		@compileOptionBlock =();
		$block = 0;
		if($commentBlock == 1)
		{
			if(/^# Customer proprietary compile option/)
			{
				$skip = 1;
			}		
		}
		$commentBlock = 0;
		next;
		
	}#if(/^\s*$/)
	else
	{
		$blankLine = 0;
	}
	
	if($block == 1)
	{
		# Feature_Name =
		# Description = Option for EVB that has no real battery
		# Pre_Variable_True = N/A
		# Pre_Variable_False = N/A
		# Option_Selection = TRUE, FALSE
		#	EVB_WITHOUT_BATTERY_SUPPORT = FALSE
	
		if(/#===================+/)
		{
			$commentBlock = 1;
			next;
		}

		push @compileOptionBlock, "$_";
		next;
	}
	
	if (/^#/)
	{
		$found  = 0;
		
		if(/^# Customer proprietary compile option/)
		{
			$skip = 1;
			if($runMode == 2) # 2: to get the compile option list
			{
				push @outfileData, "$_\n";
			}
			next;
		}
		
		if(/^# ?Feature_Name/)
		{
			$found = 1;
		}
		
		if(/^# ?Description/)
		{
			$found = 1;
		}
		
		if(/^# ?Pre_Variable_True/)
		{
			$found = 1;
		}
		
		if(/^# ?Pre_Variable_False/)
		{
			$found = 1;
		}

		if(/^# ?Option_Selection/)
		{
			$found = 1;
		}
		
		if($found == 1)
		{
			$block = 1;
			push @compileOptionBlock, "$_";
			next;
		}	
	}
	
	if($dbgOutput == 1)
	{
		print "$_\n";
	}
	
	if($runMode == 2) # 2: to get the compile option list	
	{
		push @outfileData, "$_\n";
	}
	
}#foreach (@file)

if($runMode == 0)	# 0: to parse file and save data
{
	close OPNAMEFILE;
	close DESCFILE;
	close PREVARTRUEFILE;
	close PREVARFALSEFILE;
	close OPSELFILE;
	close OPFILE;
}
if($runMode == 2) # 2: to get the compile option list
{
	my $outFile = $opFile;
	
	$outFile .= ".mak";

	unlink $outFile;	
	close OPFILE;
	open(OUTFILE, ">$outFile");
	foreach (@outfileData)
	{
		print OUTFILE $_;
	}
	close(OUTFILE);	
}

print "Done!\n";
	
	
