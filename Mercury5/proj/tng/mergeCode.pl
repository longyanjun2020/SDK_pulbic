#!/usr/bin/perl

#####
## SYNTAX:
## perl mergeCode.pl oldFileList.xml newFileList.xml logFileList.txt false
#####

use warnings;
use strict;
use Cwd;

# use module
use XML::Simple;
use Data::Dumper;

# ceate object
my $xml = new XML::Simple;

# read XML file
my $outFile = shift(@ARGV);
my $oldXmlData = $xml->XMLin($outFile, ForceArray=>1);	
my $newXmlData = $xml->XMLin(shift(@ARGV), ForceArray=>1);
#my $outFile = shift(@ARGV);	
my $logFile = shift(@ARGV) || "fileChange.log";	
# $relValueFlag = true, default_value will be parsed
my $relValueFlag = shift(@ARGV) || "false";

my $compareMatch = undef;

if ($relValueFlag ne "true")
{
	open(OUTPUT_FILE, "> $outFile") or die "cannot write\"$outFile\" file\n";	
}
open(LOG_FILE, "> $logFile") or die "cannot write\"$logFile\" file\n";	

my $nextMakeInd = 0; 
my $prevMakeMatchInd = undef;
#get values of key "make"	of the chk xml data
my $tmpNewMakeArrayPtr = $newXmlData->{"make"};	
my @MakeArray;
my $newMakeArrayPtr;
	
#get values of key "make"		
my $oldMakeArrayPtr = $oldXmlData->{"make"};

sub filter
{
	my @filterArr = @_;
	my $makeHash;
	
	foreach (@$tmpNewMakeArrayPtr)
	{
		my $makeData = $_;	
		my $keep = 1;
		
		foreach(@filterArr)
		{
			if ($makeData->{"make_name"}->[0] =~ /^\s*$_/)
			{
				$keep = 0;
				last;
			}			
		}

		if ($keep)
		{
			push @MakeArray, $makeData;
		}
	}
	
	$newMakeArrayPtr = \@MakeArray;
}

sub main
{
	my @makeHashRefArray;
	my $pwd = cwd();
	
	foreach (@$oldMakeArrayPtr)			
	{	
		#check if reach the end of chkList
		my @newMakeArray = @$newMakeArrayPtr;
		if ($nextMakeInd == ($#newMakeArray+1))
		{
			last;
		}		
				
		if (defined(&chkXmlMake($_)))
		{		
			#this make is matched , will push in makeValueArray
			#get values of key "file"						
			my $outFileRef;	

			$outFileRef = &chkXmlFile($newMakeArrayPtr->[$nextMakeInd-1], $_);								

			if (defined($outFileRef))
			{		
				if (!defined($prevMakeMatchInd))
				{
					if ($nextMakeInd > 1)
					{
						for (0 ... ($nextMakeInd-2))
						{
							if ($relValueFlag ne "true")
							{
								print LOG_FILE "ADD MAKE - ", $newMakeArrayPtr->[$_]->{"make_name"}->[0], " is added!\n";
							}
							push @makeHashRefArray, $newMakeArrayPtr->[$_];
							$compareMatch ++;
						}
					}
				}		
				elsif (($nextMakeInd-2) > $prevMakeMatchInd)
				{
					for (($prevMakeMatchInd+1) ... ($nextMakeInd-2))
					{
						if ($relValueFlag ne "true")
						{
							print LOG_FILE "ADD MAKE - ", $newMakeArrayPtr->[$_]->{"make_name"}->[0], " is added!\n";
						}
						push @makeHashRefArray, $newMakeArrayPtr->[$_];
						$compareMatch ++;
					}
				}

				$prevMakeMatchInd = $nextMakeInd-1;	

				my $hashRef = 
				{
					'make_name' => $_->{"make_name"}->[0],
					'file' => $outFileRef
				};
				push @makeHashRefArray, $hashRef;						
			}									
		}		
		else
		{
			if ($relValueFlag ne "true")
			{
				print LOG_FILE "RMV MAKE - ", $_->{"make_name"}->[0], " is removed!\n";
			}
			$compareMatch ++;
		}
	}

	my @kjk = @$newMakeArrayPtr;

	if ($nextMakeInd <= ($#kjk -1))
	{
		for ($nextMakeInd ... ($#kjk))
		{
			my $newMakeHash = $newMakeArrayPtr->[$_];
			if ($relValueFlag ne "true")
			{
				print LOG_FILE "ADD MAKE - ", $newMakeHash->{"make_name"}->[0], " is added!\n";
			}
			push @makeHashRefArray, $newMakeArrayPtr->[$_];
			$compareMatch ++;
		}
	}
	
	if($relValueFlag ne "true")
	{
		my $outHash = 
		{
			'make' => \@makeHashRefArray
		};
	
		# create object
		$xml = new XML::Simple;
		# convert Perl array ref into XML document 
		my $outXmlData = $xml->XMLout($outHash, NoAttr=>1, NoSort=>1, RootName=>'make_info');
		# access XML data
		#print $outXmlData;	
		
		print OUTPUT_FILE $outXmlData;
		
		#print Dumper($oldMakeArrayPtr);	
		
		close (OUTPUT_FILE);
	}
	close (LOG_FILE);	
	if (!defined($compareMatch))
	{
		unlink $logFile;
	}
	chdir $pwd;
	unless (-s $logFile)
	{
		unlink $logFile;
	}
}

my $findFile = undef;
sub find
{
	my $pathname = shift;
	my $fileName = shift;

	my $filenum = 0;
	
	my @dir = <*>;
	for my $path (@dir)
	{
		if (!defined($findFile))
		{
			if (-d $path)
			{
				chdir $path;
				#print "find $pathname/$path\n";
				&find("$pathname/$path", $fileName);
				chdir "../";
			}
			elsif ($path eq $fileName)
			{
				print "match $pathname/$path\n";
				$findFile = "$pathname/$path";
				last;
			}
		}
		else
		{
			last;
		}
	}
}

#parameters: make hash reference
sub chkXmlMake
{
	my $inMakeHash = $_[0];
	my $matched = undef;	

	my @newMakeArray = @$newMakeArrayPtr;
	
	for ($nextMakeInd ... $#newMakeArray)		
	{
		my $newMakeHash = $newMakeArrayPtr->[$_];
			
		if ($newMakeHash->{"make_name"}->[0] eq $inMakeHash->{"make_name"}->[0])
		{		
			$nextMakeInd = $_+1;
			$matched = 1;
			last;	
		}								
	}
	return $matched;
}

#parameters: 1.the matched make hash reference(new), 2. file hash reference to be compared(old, i.e., released)
sub chkXmlFile
{
	my $matchMakeName = $_[0]->{"make_name"}->[0];
	my $matchFilePtr = $_[0]->{"file"};
	my $inMakeName = $_[1]->{"make_name"}->[0];
	my $inFilePtr = $_[1]->{"file"};
	my $outFileHashRef = undef;

	my @inFileArray = @$inFilePtr;

	my @matchFileArray = @$matchFilePtr;
	my @fileHashRefArray;
	my $fileMatched = undef;
	my $nextInd = 0;		
	my $relValue = "SRC_C_LIST";
	
	for (@inFileArray)
	{
		my $inFile = $_;
		$relValue = $inFile->{"default_value"}->[0];
		
		for ($nextInd ... $#matchFileArray)
		{
			if ($matchFileArray[$_]->{"file_name"}->[0] eq $inFile->{"file_name"}->[0])
			{	
				if ($relValueFlag ne "true")
				{
					&chkFileOption($inFile, $matchFileArray[$_]);
				}
				else
				{
					if ($matchFileArray[$_]->{"default_value"}->[0] ne $inFile->{"default_value"}->[0])
					{
						my $defValue = substr $matchFileArray[$_]->{"default_value"}->[0], 0, 4;
						if ($defValue eq "REL_")
						{
							my @makFolderA = split(/\//, $matchMakeName);
							pop(@makFolderA);
							my $makFolder = join "\/" , @makFolderA;
							chdir $makFolder;
							$findFile = undef;
							&find($makFolder, $matchFileArray[$_]->{"file_name"}->[0]);
							for(0 ... $#makFolderA)
							{
								chdir "../";
							}
							if (defined($findFile))
							{
								print LOG_FILE "S - $findFile in $matchMakeName!\n";
							}
							else
							{
								chdir "sc";
								&find("sc", $matchFileArray[$_]->{"file_name"}->[0]);
								chdir "../";
								if (defined($findFile))
								{
									print LOG_FILE "S - $findFile in $matchMakeName!\n";
								}
								else
								{
									print LOG_FILE "S - ERROR--can not find ", $matchFileArray[$_]->{"file_name"}->[0], "!\n";
								}
							}
						}
						else
						{
							print LOG_FILE "L - ", $matchFileArray[$_]->{"file_name"}->[0], " in $matchMakeName!\n";
						}
						$compareMatch ++;
					}
				}
						
				$nextInd = $_ + 1;		
				
				if (!defined($fileMatched))
				{					
					if ($nextInd > 1)
					{
						for (0 ... ($nextInd-2))
						{
							if ($relValueFlag ne "true")
							{
								print LOG_FILE "ADD FILE - ", $matchFileArray[$_]->{"file_name"}->[0], " in ", $matchMakeName, " is added!\n";
							}
							if ($matchFileArray[$_]->{"file_name"}->[0] =~ /\.c/)
							{
								if ($relValue =~ /_C_LIST/)
								{
									$matchFileArray[$_]->{"default_value"}->[0] = $relValue;
								}
								elsif ($relValue =~ /^REL_SRC_ASM_LIST/)
								{
									$matchFileArray[$_]->{"default_value"}->[0] = "REL_SRC_C_LIST";
								}
								elsif ($relValue =~ /^SRC_ASM_LIST/)
								{
									$matchFileArray[$_]->{"default_value"}->[0] = "SRC_C_LIST";
								}
							}
							elsif ($matchFileArray[$_]->{"file_name"}->[0] =~ /\.asm/)
							{
								if ($relValue =~ /_ASM_LIST/)
								{
									$matchFileArray[$_]->{"default_value"}->[0] = $relValue;
								}
								elsif ($relValue =~ /^REL_SRC_C_LIST/)
								{
									$matchFileArray[$_]->{"default_value"}->[0] = "REL_SRC_ASM_LIST";
								}
								elsif ($relValue =~ /^SRC_C_LIST/)
								{
									$matchFileArray[$_]->{"default_value"}->[0] = "SRC_ASM_LIST";
								}
							}
							push @fileHashRefArray, $matchFileArray[$_];
							$compareMatch ++;
						}
					}
				}
				elsif(($nextInd-2) > $fileMatched)
				{
					for (($fileMatched+1) ... ($nextInd-2))
					{
						if ($relValueFlag ne "true")
						{
							print LOG_FILE "ADD FILE - ", $matchFileArray[$_]->{"file_name"}->[0], " in ", $matchMakeName, " is added!\n";
						}
						if ($matchFileArray[$_]->{"file_name"}->[0] =~ /\.c/)
							{
								if ($relValue =~ /_C_LIST/)
								{
									$matchFileArray[$_]->{"default_value"}->[0] = $relValue;
								}
								elsif ($relValue =~ /^REL_SRC_ASM_LIST/)
								{
									$matchFileArray[$_]->{"default_value"}->[0] = "REL_SRC_C_LIST";
								}
								elsif ($relValue =~ /^SRC_ASM_LIST/)
								{
									$matchFileArray[$_]->{"default_value"}->[0] = "SRC_C_LIST";
								}
							}
							elsif ($matchFileArray[$_]->{"file_name"}->[0] =~ /\.asm/)
							{
								if ($relValue =~ /_ASM_LIST/)
								{
									$matchFileArray[$_]->{"default_value"}->[0] = $relValue;
								}
								elsif ($relValue =~ /^REL_SRC_C_LIST/)
								{
									$matchFileArray[$_]->{"default_value"}->[0] = "REL_SRC_ASM_LIST";
								}
								elsif ($relValue =~ /^SRC_C_LIST/)
								{
									$matchFileArray[$_]->{"default_value"}->[0] = "SRC_ASM_LIST";
								}
							}
						push @fileHashRefArray, $matchFileArray[$_];
						$compareMatch ++;
					}
				}
				
				#the current compared & matched file index
				push @fileHashRefArray, $inFile;
				$fileMatched = $_;				
				last;
			}
			elsif ($_ == $#matchFileArray)
			{
				#we are reaching the end of chking list
				if ($relValueFlag ne "true")
				{
					print LOG_FILE "RMV FILE - ", $inFile->{"file_name"}->[0], " in ", $inMakeName, " is removed!\n";
				}
				$compareMatch ++;
			}
		}					
	}
		
	
	if ($nextInd <= $#matchFileArray)
	{
		for ($nextInd ... $#matchFileArray)
		{
			if ($relValueFlag ne "true")
			{
				print LOG_FILE "ADD FILE - ", $matchFileArray[$_]->{"file_name"}->[0], " in ", $matchMakeName, " is added!\n";
			}
			if ($matchFileArray[$_]->{"file_name"}->[0] =~ /\.c/)
			{
				if ($relValue =~ /_C_LIST/)
				{
					$matchFileArray[$_]->{"default_value"}->[0] = $relValue;
				}
				elsif ($relValue =~ /^REL_SRC_ASM_LIST/)
				{
					$matchFileArray[$_]->{"default_value"}->[0] = "REL_SRC_C_LIST";
				}
				elsif ($relValue =~ /^SRC_ASM_LIST/)
				{
					$matchFileArray[$_]->{"default_value"}->[0] = "SRC_C_LIST";
				}
			}
			elsif ($matchFileArray[$_]->{"file_name"}->[0] =~ /\.asm/)
			{
				if ($relValue =~ /_ASM_LIST/)
				{
					$matchFileArray[$_]->{"default_value"}->[0] = $relValue;
				}
				elsif ($relValue =~ /^REL_SRC_C_LIST/)
				{
					$matchFileArray[$_]->{"default_value"}->[0] = "REL_SRC_ASM_LIST";
				}
				elsif ($relValue =~ /^SRC_C_LIST/)
				{
					$matchFileArray[$_]->{"default_value"}->[0] = "SRC_ASM_LIST";
				}
			}
			push @fileHashRefArray, $matchFileArray[$_];
			$compareMatch ++;
		}
	}
	
	if (defined($fileMatched))
	{
		$outFileHashRef = \@fileHashRefArray;
	}

	return $outFileHashRef;
}

#parameters: 1.the matched file hash reference(new), 2. file hash reference to be compared(old, i.e., released)
sub chkFileOption
{
	my $oldFileHashRef = $_[0];
	my $newFileHashRef = $_[1];
	my $optionHash;

	#if (defined($newFileHashRef->{"compile_option"}))
	if (exists $newFileHashRef->{"compile_option"})
	{
		$oldFileHashRef->{"compile_option"} = $newFileHashRef->{"compile_option"}->[0];
	}
	elsif (exists $oldFileHashRef->{"compile_option"})
	{
		delete $oldFileHashRef->{"compile_option"} ;
	}
	
	if (exists $newFileHashRef->{"compile_option_2"})
	{
		$oldFileHashRef->{"compile_option_2"} = $newFileHashRef->{"compile_option_2"}->[0];		
	}
	elsif (exists $oldFileHashRef->{"compile_option_2"})
	{
		delete $oldFileHashRef->{"compile_option_2"} ;
	}
}

#&filter("sc/customer/default");
&filter("juji/juji/juji");
&main;