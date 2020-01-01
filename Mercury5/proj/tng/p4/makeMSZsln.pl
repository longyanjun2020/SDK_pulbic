#!/usr/bin/perl

#####
## SYNTAX:
## perl tng/p4/makeMSZsln.pl
#####

use warnings;
use strict;

open(LIB_LIST, "tng/p4/ap/simu_lib_list.txt") or die "cannot read \"simu_lib_list.txt\" file\n";
my @libList=<LIB_LIST>;
close(LIB_LIST);

sub findLib
{
	my $slnLine = shift;
	for my $libLine(@libList)
	{
		my $libName = "";
		if ($libLine =~ /\./)
		{
			$libName = $`;
		}
		
        $libName =~ s/^\s+//; # remove whitespace from the begin of the string
        $libName =~ s/\s+$//; # remove whitespace from the end of the string

		if ($slnLine =~ /\\$libName\.vcproj\"/i)
		{
			return 1;
		}
	}
}

#generate AP_BuildAll.sln
open(SLN_FILE, "MStarStudio_UP/MStarDeveloper/XMMI/MMI_BuildAll.sln") or die "cannot read \"MMI_BuildAll.sln\" file\n";
my @slnContent=<SLN_FILE>;
close(SLN_FILE);

open(AP_SLN, "> MStarStudio_UP/MStarDeveloper/XMMI/AP_BuildAll.sln") or die "cannot read \"AP_BuildAll.sln\" file\n";
my $rmFlag = 0;
for my $line (@slnContent)
{
	my $tmp_line = $line;
	$tmp_line =~ s/\x0d\x0a//ig;
	if ($tmp_line =~ /\.vcproj\"/)
	{
		if (findLib($tmp_line))
		{
			$rmFlag = 1;
		}
		else
		{
			print AP_SLN $line;
		}
	}
	else
	{
		if ($rmFlag)
		{
			if ($tmp_line =~ /^EndProject$/)
			{
				$rmFlag = 0;
			}
		}
		else
		{
			print AP_SLN $line;
		}
	}
}
close(AP_SLN);


#update App_mmi_B3.vcproj
my $vc_flag = 0;
my $addLink = "";

open(MMI_VCPROJ, "MStarStudio_UP/MStarKernel/App/XMMI/App_mmi_B3.vcproj") or die "cannot read \"App_mmi_B3.vcproj\" file\n";
my @content=<MMI_VCPROJ>;
close(MMI_VCPROJ);

open(MMI_VCPROJ, "> MStarStudio_UP/MStarKernel/App/XMMI/App_mmi_B3.vcproj") or die "cannot read \"App_mmi_B3.vcproj\" file\n";
for my $line (@content)
{
	if ($line =~ /Name\=\"Debug\|Win32\"/)
	{
		$vc_flag = 1;
	}
	elsif ($vc_flag == 1)
	{
		if ($line =~ /AdditionalDependencies\=\"/)
		{
			for my $libLine(@libList)
			{
				$libLine =~ s/\x0d\x0a//ig;
				if ($line !~ /$libLine/)
				{
					$addLink = $addLink." ".$libLine;
				}
			}
			$line =~ s/\.lib\"/\.lib$addLink\"/;
		}
		elsif ($line =~ /\<\/Configuration\>/)
		{
			$vc_flag = 0;
		}
	}
	print MMI_VCPROJ $line;
}
close(MMI_VCPROJ);
	