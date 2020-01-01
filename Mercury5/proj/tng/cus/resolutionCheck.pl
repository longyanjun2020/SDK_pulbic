#!/usr/bin/perl

package Resource;

use strict;

$Resource::profileResult = "";
$Resource::cus_resResult = "";
$Resource::cus_projectResult = "";

#Auto select resolution parameter
sub lcm_auto_slect()
{
	my($lcm_support,$lcm_type,$profile,$cus_res,$cus_project,$smallRom,$multi_theme) = @_;

	my $i=0;
	my @lcm_tmp1 = ();
	my @lcm_tmp2 = ();
	my $tmp1 = "" ;
	my $match=0;

	my $cus_resTmp = "";
	my $cus_pathTmp = "";
	my $cus_projectTmp = "";
	my $profileTmp = "";
	my $failCase=0;


	#print "#####################################\n";
	#print "lcm_type = $lcm_type \n";
	#print "lcm_support = $lcm_support \n";

	@lcm_tmp1 = $lcm_support =~ /\(.*?\)/g;
	for ($i=0; $i<(@lcm_tmp1); $i++)
	{
		$tmp1 = $lcm_tmp1[$i];
		$tmp1 =~ s/[\(]//g;
		$tmp1 =~ s/[\)]/ /g;
		@lcm_tmp2 = $tmp1 =~ /(.*?)[, ]/g;
		#print "lcm_tmp2= @lcm_tmp2 \n";

		if( "$lcm_tmp2[0]" eq "$lcm_type" )
		{
			$profileTmp = $lcm_tmp2[2];
			$cus_resTmp = $lcm_tmp2[1];
			$match = 1;
		}
		#print "$lcm_tmp2[0] & $lcm_type   \n";
	}

	$tmp1 = $lcm_type;
	$tmp1 =~ s/ //g;
	if( $tmp1 eq "" )   #special case for no UI EVB board.  in this case, doesn't support AUTO mode
	{
		$match = 1;
	}

	if( ($smallRom == 1) && ($multi_theme eq "TRUE") )
	{
		print "multi-theme is not support with SmallRom product!!!\n";
		exit 1;
	}

	if( $match == 0 )
	{
		print "can't found match simulator profile \n";
		exit 1;
	}
	else
	{
		if ( $profile eq "AUTO" )
		{
			$profile = $profileTmp;
		}

		if ( $cus_res eq "AUTO" )
		{
			if( $smallRom == 1 )
			{
				$cus_resTmp =~ s/_/_SmallRom_/g;
				$cus_res = $cus_resTmp
			}
			else
			{
				$cus_res = $cus_resTmp;
			}
		}

		if ( $cus_project eq "AUTO" )
		{
			my $result = 0;

			$result = $lcm_type =~ /LANDSCAPE/i;
			print "result: $result \n";

			if( $result == 1 )
			{
				$cus_project = "CommonLandscape";
			}
			else
			{
				$cus_project = "CommonPortrait";
			}

			if( $multi_theme eq "TRUE" )
			{
				$cus_project .= "Theme";
			}

			chomp $cus_project;
		}

		#print "Simulator_Profile: $profile \n";
		#print "cus_res: $cus_res \n";
		#print "cus_project: $cus_project \n";

		open( FILE, ">./tng/cus/cus_parameter.mak") || die "cus_parameter.mak open Error!\n";

		print FILE "CUS_PROJECT_PERL = $cus_project\n";
		print FILE "CUS_RES_PERL = $cus_res\n";

		close(FILE);
	}

	# check file or folder is exist
#	if( -e "../proj/MStarStudio_UP/MStarDeveloper/XMMI/debug/PhoneProfile/$profile")
#	{
#		#print "$profile exist\n";
#	}
#	else
#	{
#		print "Simulator Profile($profile) not exist. please check profile value and profile folder /proj/MStarStudio_UP/MStarDeveloper/XMMI/debug/PhoneProfile \n";
#		$failCase=1;
#	}

	if( -e "../proj/sc/customer/default/src/mmi/resource/Control_Files/$cus_project.xml")
	{
		#print "$cus_project exist\n";
	}
	else
	{
		print "cus_project($cus_project.xml) not exist, please check cus_project value and file (in /proj/sc/customer/default/src/mmi/resource/Control_Files/) \n";
		$failCase=1;
	}

	if( -e "../proj/sc/customer/default/src/mmi/resource/$cus_res" )
	{
		#print "$cus_res exist\n";
	}
	else
	{
		print "cus_res($cus_res) not exist, please check cus_res value and folder proj/sc/customer/default/src/mmi/resource/$cus_res  \n";
		$failCase=1;
	}

	if( $failCase == 1 )
	{
		exit 1;
	}

#	$Resource::profileResult = $profile;
	$Resource::cus_resResult = $cus_res;
	$Resource::cus_projectResult = $cus_project;

	return ;
}

sub getProfile()
{
	return $Resource::profileResult;
}

sub getCusRes()
{
	return $Resource::cus_resResult;
}

sub getCusProject()
{
	return $Resource::cus_projectResult;
}

1;
