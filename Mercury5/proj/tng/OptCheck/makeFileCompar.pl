#!/usr/bin/perl

use strict;

#####
## SYNTAX:
## darry.huang@msnb5802 /cygdrive/d/EMMI/EMMI/mainline/proj
## $ perl tng/OptCheck/makeFileCompar.pl
#####

# bkack list

sub isInBlackList()
{
	my $fileToCheck = shift;
	my @blackFileList = 
	(	
		"options_8533c_128_32_yk701d.mak",
		"options_8533c_64_32_64yk701.mak",
		"options_8533c_64_32_m160c.mak",
		"options_8533d_128_32_mb405f.mak",
		"options_8533d_64_32_wbg5005.mak",
		"options_8533n_1g_256_gax7163.mak",
		"options_8533n_1g_256_gax7163_i686.mak",
		"options_8533n_1g_256_mb301n.mak",
		"options_8533n_1g_256_mb303av2.mak",
		"options_8533n_256_256_7162.mak",
		"options_8533n_512_256_3301.mak",
		"options_8533n_512_256_3303.mak",
		"options_8533n_512_256_3305_ctp.mak",
		"options_8533n_512_256_3310_ctp.mak",

		#G1
		"options_8830n_1g_256_canisV.mak",
		"options_8830n_1g_256_mg101v3.mak",
	);
	my $found = 0;
	
	return ($found);# 
	
	foreach (@blackFileList)
	{
		if($_ eq $fileToCheck)
		{
			$found = 1;
			last;
		}
	}
	
	return ($found);
}

my $indPath = "./mak/";
my $path = ".";
my $templateMakFile = "options_8532_64_32_mb406g.mak";
my $compareMakeFile = "";

if ($#ARGV != 0)
{
	;
}
else
{
	$path = $ARGV[0];
	$indPath = $path."/mak/";
}

my $cmd = "perl $path/tng/OptCheck/makeFileCheck.pl check $indPath$templateMakFile";
my $result = system($cmd);

if($result != 0)
{
	print "makeFileCheck.pl returns error: $result\n";
	print "Please check $templateMakFile\n";		
	exit 1;
}
print "\nCompare make files with $templateMakFile...\n";

my @cmpFileList= ();
	
# gat product list
opendir PRD, "mak/" or die "cannot access product in \"", "mak/", "\"\n";
for my $prd (sort(readdir(PRD)))
{
	if($prd =~ /\.mak/)
	{
		#print "$prd\n";
		push @cmpFileList,$prd; 
	}
}
closedir PRD;

foreach (@cmpFileList)
{
	my @tmpFile;
	my @cmpFile;
	my $tmpLine;
	
	$compareMakeFile = $_;
	
	if(1 == &isInBlackList($compareMakeFile))
	{
		print "$compareMakeFile -> ";
		print "ignored\n";
		next;
	}
	
	open(FILE, "<$indPath$templateMakFile");
	@tmpFile = <FILE>;
	close(FILE);

	if (! -e "$indPath$compareMakeFile")
	{
		print "$compareMakeFile -> ";
		print "File does not exist.\n";
		next;
	}
	open(FILE, "<$indPath$compareMakeFile");
	@cmpFile = <FILE>;
	close(FILE);
	
	my $cmpLine = 0;
	my $i = 0;
	my $lineCounter = 0;
	my $skip = 0;
	
	print "$compareMakeFile -> ";
	foreach (@tmpFile)
	{
		my $cmpCo;
		my $cmpCoVal;

		if($skip == 1)
		{
			next;
		}
				
		$lineCounter += 1;
		chomp;
		s/\012$//;
		s/\015$//;
		$tmpLine = $_;
		$i = 0;
		$cmpCo = "";
		$cmpCoVal = "";
		foreach(@cmpFile)
		{
			$i += 1;
			if($i == $lineCounter)
			{
				chomp;
				s/\012$//;
				s/\015$//;
				$cmpLine = $_;
				if(/#* *(.*?)\s*=\s*(.*)/)
				{
					$cmpCo = $1;
					$cmpCoVal = $2;
					$cmpCoVal =~ s/\s+$//; # remove whitespace from the end of the string
				}
				last;
			}
		}
	
		if($tmpLine =~ /^# Customer proprietary compile option/)
		{
			if($cmpLine =~ /^# Customer proprietary compile option/)
			{
				$skip = 1;
				next;
			}
		}	
		
		# new line or start from "#"
		if((/^\s*$/) || (/^#/))
		{			
			if(/#* *(.*?)\s*=\s*(.*)/)
			{
				my $findCo;
				my $findCoVal;

				$findCo = $1;
				$findCoVal = $2;				
				$findCoVal =~ s/\s+$//; # remove whitespace from the end of the string
=cut				
				# Feature_Name = Hall Switch. <== check feature name
				# Description = Options to enable hall switch <== check Description
				# Pre_Variable_True = N/A <== check Pre_Variable_True
				# Pre_Variable_False = N/A <== check Pre_Variable_False
				# Option_Selection = TRUE, FALSE <== check Option_Selection
				#HALL_SWITCH_SUPPORT = FALSE
=cut				
				if(($cmpCo =~ /Feature_Name/)
						||($cmpCo =~ /Description/)
						||($cmpCo =~ /Pre_Variable_True/)
						||($cmpCo =~ /Pre_Variable_False/)
						||($cmpCo =~ /Option_Selection/)
						)
				{
					if($cmpCoVal ne $findCoVal)
					{
=cut
						print "\n$_\n\n";
						print "$cmpCo\n\n";
						print "$findCo\n\n";
						print "$cmpCoVal\n\n";
						print "$findCoVal\n\n";
=cut
						print "\nERROR: Format incorrect[4]. please check line $lineCounter.\n";
						exit 1;
					}
				}		
=cut				
				# Feature_Name = Hall Switch.
				# Description = Options to enable hall switch
				# Pre_Variable_True = N/A
				# Pre_Variable_False = N/A
				# Option_Selection = TRUE, FALSE
				#HALL_SWITCH_SUPPORT = FALSE	<== compare compile option line				
=cut						
				if($cmpCo ne $findCo)
				{
					print "\n$cmpCo\n";
					print "$1\n";
					
					print "ERROR: Format incorrect[1]. please check line $lineCounter.\n";
					exit 1;
				}
				next;
			}
		
			# compare general lines
			if($tmpLine ne $cmpLine)
			{
			    print "\n$tmpLine\n";
			    print "$cmpLine\n";
				print "\nERROR: Format incorrect[2]. please check line $lineCounter.\n";
				exit 1;
			}
		}#if((/^\s*$/) || (/^#/))
		else
		{	
=cut						
			# Feature_Name = Hall Switch.
			# Description = Options to enable hall switch
			# Pre_Variable_True = N/A
			# Pre_Variable_False = N/A
			# Option_Selection = TRUE, FALSE
			HALL_SWITCH_SUPPORT = FALSE	<== compare compile option line
=cut				
			if(/#* *(.*?)\s*=\s*(.*)/)
			{
				if($cmpCo ne $1)
				{
					print "\n$cmpCo\n";
					print "$1\n";
					
					print "ERROR: Format incorrect[32]. please check line $lineCounter.\n";
					exit 1;
				}
				next;
			}
			
			print "\nnot compare$lineCounter: $tmpLine\n";
		}
		
	}#foreach (@tmpFile)
	
	print "pass\n";
} #foreach (@cmpFiles)

print "Done!"
		
