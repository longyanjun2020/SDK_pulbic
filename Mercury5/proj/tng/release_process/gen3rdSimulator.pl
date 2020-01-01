#!/usr/bin/perl

#####
## SYNTAX:
## perl tng/release_process/gen3rdSimulator.pl Oakmont,SG,Sinovoice,Tts
#####

use warnings;
use strict;

my $product = shift;

#Support $projs = Oakmont,SG,Sinovoice,Tts
#my $projs = shift;
#my @allProjs = split(/,/, $projs);
my @allProjs = ();
my @offProjs = ();

my $solutionFile = "./MStarStudio_UP/MStarDeveloper/XMMI/MMI_BuildAll_cus.sln";
my $appFile = "./MStarStudio_UP/MStarKernel/App/XMMI/App_mmi_B3.vcproj";

my @sgLinkLib = ("SGIME_ARA_WIN32.lib", "SGIME_BEN_WIN32.lib", "SGIME_CN_WIN32.lib", "SGIME_CZE_WIN32.lib", 
								 "SGIME_DUT_WIN32.lib", "SGIME_ENG_WIN32.lib", "SGIME_FOREIGN_ENGINE_WIN32.lib", "SGIME_FRE_WIN32.lib",
								 "SGIME_GER_WIN32.lib", "SGIME_GRE_WIN32.lib", "SGIME_HIN_WIN32.lib", "SGIME_IND_WIN32.lib", 
								 "SGIME_ITA_WIN32.lib", "SGIME_MAL_WIN32.lib", "SGIME_PER_WIN32.lib", "SGIME_POL_WIN32.lib", 
								 "SGIME_POR_WIN32.lib", "SGIME_RUS_WIN32.lib", "SGIME_SPA_WIN32.lib", "SGIME_THA_WIN32.lib", 
								 "SGIME_TUR_WIN32.lib", "SGIME_VIE_WIN32.lib");
								 
my @sinovoiceLinkLib = ("hzrecog.lib");
my $logFile = "gen3rdSimulator.log";

open(LOG_FILE, "> $logFile") or die "cannot read \"$logFile\" file\n";

sub changeName
{
	my $oldName = shift;
	my $newName = shift;
	my $oldVcproj = shift;
	my $newVcproj = shift;
	
	open(SLN_FILE, "< $solutionFile") or die "cannot read \"$solutionFile\" file\n";
	my @slnContant = <SLN_FILE>;
	close(SLN_FILE);

	open(SLN_FILE, "> $solutionFile") or die "cannot read \"$solutionFile\" file\n";
	
	for my $line (@slnContant)
	{
		if ($line =~ /\"$oldName\"/ && $line =~ /\\$oldVcproj\.vcproj/)
		{
			if ($oldName ne $newName)
			{
				$line =~ s/\"$oldName\"/\"$newName\"/;
				print LOG_FILE " - change vcproj name from $oldName to $newName\n";
			}
			if ($oldVcproj ne $newVcproj)
			{
				$line =~ s/\\$oldVcproj\.vcproj/\\$newVcproj\.vcproj/;
				print LOG_FILE " - change vcproj from $oldVcproj\.vcproj to $newVcproj\.vcproj\n";
			}
		}
		print SLN_FILE $line;
	}
	close(SLN_FILE);
}

sub addLinkLib
{
	my $onoff = shift;
	my $linkLibPtr = shift;
	my @linkLib = @$linkLibPtr;
	my $linkLibFlag = 0;
	
	open(APP_FILE, "< $appFile") or die "cannot read \"$appFile\" file\n";
	my @appContant = <APP_FILE>;
	close(APP_FILE);
	
	open(APP_FILE, "> $appFile") or die "cannot read \"$appFile\" file\n";
	
	for my $line (@appContant)
	{
		if (($line =~ /AdditionalDependencies=\"/) && ($linkLibFlag == 0))
		{
			$linkLibFlag = 1;
			if ($onoff eq "on")
			{
				if ($line =~ /\.lib\"/)
				{
					for (0 ... $#linkLib)
					{
						if ($line !~ /$linkLib[$_]/)
						{
							$line =~ s/\.lib\"/\.lib $linkLib[$_]\"/;
							print LOG_FILE " - add link lib to AdditionalDependencies: $linkLib[$_]\n";
						}
						else
						{
							print LOG_FILE " - $linkLib[$_] already exist\n";
						}
					}
				}
			}
			else
			{
				for (0 ... $#linkLib)
				{
					if ($line =~ /$linkLib[$_]/)
					{
						$line =~ s/ $linkLib[$_]//;
						print LOG_FILE " - remove link lib to AdditionalDependencies: $linkLib[$_]\n";
					}
					else
					{
						print LOG_FILE " - $linkLib[$_] not exist\n";
					}
				}
			}
		}
		print APP_FILE $line;
	}
	close(APP_FILE);
}

sub updateSln
{
	my $vcproj = shift;
	my $onoff = shift;
	
	if ($vcproj =~ /Oakmont/i)
	{
		print "Update $solutionFile: $vcproj\n";
		print LOG_FILE "Update $solutionFile\n";
		if ($onoff eq "on")
		{
			changeName("Java", "Java_Oakmont", "Java", "Oakmont");
		}
		else
		{
			changeName("Java_Oakmont", "Java", "Oakmont", "Java");
		}
	}
	elsif ($vcproj =~ /SG/i)
	{
		print "Update $solutionFile: $vcproj\n";
		print LOG_FILE "Update $solutionFile\n";
		if ($onoff eq "on")
		{
			changeName("App_3rd", "App_3rd", "Task_ime", "Task_ime_sg");
		}
		else
		{
			changeName("App_3rd", "App_3rd", "Task_ime_sg", "Task_ime");
		}
	}
	elsif ($vcproj =~ /Tts/i)
	{
		print "Update $solutionFile: $vcproj\n";
		print LOG_FILE "Update $solutionFile\n";
		if ($onoff eq "on")
		{
			changeName("Tts_dummy", "Tts", "Tts_dummy", "Tts");
		}
		else
		{
			changeName("Tts", "Tts_dummy", "Tts", "Tts_dummy");
		}
	}
	else
	{
		print "No need to update $solutionFile: $vcproj\n";
		print LOG_FILE "No need to update $solutionFile\n";
	}
}

sub updateApp
{
	my $vcproj = shift;
	my $onoff = shift;
	
	if ($vcproj =~ /SG/i)
	{
		print "Update $appFile: $vcproj\n";
		print LOG_FILE "Update $appFile\n";
		addLinkLib($onoff, \@sgLinkLib);
	}
	elsif ($vcproj =~ /Sinovoice/i)
	{
		print "Update $appFile: $vcproj\n";
		print LOG_FILE "Update $appFile\n";
		addLinkLib($onoff, \@sinovoiceLinkLib);
	}
	else
	{
		print "No need to update $appFile: $vcproj\n";
		print LOG_FILE "No need to update $appFile\n";
	}
}

# main code
open(OPTIONS, "< mak/options_$product.mak") or die "cannot read \"options_$product.mak\" file\n";
my @optContant = <OPTIONS>;
close(OPTIONS);

for my $optLine (@optContant)
{
	$optLine =~ s/\x0d\x0a//ig;
	$optLine =~ s/ //ig;
	chomp $optLine;
	if ($optLine =~ /^JAVA_SOLUTION\=/)
	{
		print "java: $'\n";
		if ($' =~ /__JAVA_OAKMONT_/)
		{
			push @allProjs, "Oakmont";
		}
		else
		{
			push @offProjs, "Oakmont";
		}
	}
	elsif ($optLine =~ /^TTS_SUPPORT\=/)
	{
		print "tts: $'\n";
		if ($' eq "TRUE")
		{
			push @allProjs, "Tts";
		}
		else
		{
			push @offProjs, "Tts";
		}
	}
	elsif ($optLine =~ /^IME_SOLUTION\=/)
	{
		print "sg: $'\n";
		if ($' eq "__IME_MMI_SG__")
		{
			push @allProjs, "SG";
		}
		else
		{
			push @offProjs, "SG";
		}
	}
	elsif ($optLine =~ /^DISABLE_HANDWRITING_INPUT_SUPPORT\=/)
	{
		print "sinovoice: $'\n";
		if ($' eq "FALSE")
		{
			push @allProjs, "Sinovoice";
		}
		else
		{
			push @offProjs, "Sinovoice";
		}
	}
}

unless (-e $solutionFile and -e $appFile)
{
	die "***$solutionFile or $appFile doesn't exist!\n";
}
system "cp -f $solutionFile $solutionFile\.orig\n";
system "cp -f $appFile $appFile\.orig\n";
for (0 ... $#allProjs)
{
	print LOG_FILE "========== $allProjs[$_] on ===========\n";
	updateSln($allProjs[$_], "on");
	print LOG_FILE "\n";
	updateApp($allProjs[$_], "on");
	print LOG_FILE "\n";
}

for (0 ... $#offProjs)
{
	print LOG_FILE "========== $offProjs[$_] off ==========\n";
	updateSln($offProjs[$_], "off");
	print LOG_FILE "\n";
	updateApp($offProjs[$_], "off");
	print LOG_FILE "\n";
}

print LOG_FILE "\n=========================================\n";
print LOG_FILE "Original file is at\n$solutionFile\.orig\n$appFile\.orig\n";

close(LOG_FILE);
