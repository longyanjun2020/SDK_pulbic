#!/usr/bin/perl

#####
## SYNTAX:
## perl tng/OptCheck/optionCheck.pl ReleaseConfigurations_CUS_B3.xml 8533n_1g_256_mb303av2 all
## or
## perl tng/OptCheck/optionCheck.pl ReleaseConfigurations_CUS_B3.xml 8533n_1g_256_mb303av2 sc
#####

use warnings;
use strict;

my $xmlFile = shift;
my $product = shift;
my $optLevel = shift;

my @noRelLibs;
my @optMak;

my @whiteList = ("__MM_MIDDLEWARE__", "__G1__");
my @specialOpt = ("CHIP_TYPE", "JAVA_SOLUTION", "LCM_ROTATE_DIRECTION_CCW", "HALL_SWITCH_BEHAVIOR", 
									"FLASHLIGHT_CTRL_METHOD", "ATV_CHIP", "ATV_AUDIO_PATH", "BACKLIGHT_CTRL", "BLUETOOTH_CHIP", 
									"G_SENSOR_TYPE", "SD_CARD_DETECT_PIN_POLARITY", "SD2_CARD_DETECT_PIN_POLARITY", 
									"CAMERA_MAX_RESOLUTION", "DIALER_EFFECT", "IME_SOLUTION", "RFIC", "PA", "SYS_PHY_RAM_SIZE_SETTING");
my @specialOptMak;

my @pOptMak;

## parse PP_OPT_COMMON in options.mak
open(OPT_FILE, "mak/options_$product.mak") or die "cannot read \"mak/options_$product.mak\" file\n";
my @opt_content=<OPT_FILE>;
close(OPT_FILE);

for my $line (@opt_content)
{
	$line =~ s/\s//ig;
	$line =~ s/\x0d\x0a//ig;
	if ($line !~ /^#/)
	{
		if ($line =~ /\=TRUE/ || $line =~ /\=FALSE/)
		{
			my $pOptMakTmp = $`;
			my $matchWList = 0;
			for (0 ... $#whiteList)
			{
				if ($pOptMakTmp eq $whiteList[$_])
				{
					$matchWList = 1;
				}
			}
			if ($matchWList == 0)
			{
				push @pOptMak, $pOptMakTmp;
				print "$pOptMakTmp\n";
			}					
		}
	}

	for (0 ... $#specialOpt)
	{
		if ($line =~ /^$specialOpt[$_]\=/)
		{
			$specialOptMak[$_] = $';
			print "$specialOptMak[$_]\n";
			last;
		}
	}
}
## parse PP_OPT_COMMON in options.mak == END ==

## parse PP_OPT_COMMON in common_option.mak
my @ifLevel;
my $ifFlag = 0;
#my @commonOptMak;

open(COMOPT_FILE, "sc/customer/product/common/mak/common_option.mak") or die "cannot read \"common/mak/common_option.mak\" file\n";
my @comopt_content=<COMOPT_FILE>;
close(COMOPT_FILE);
my $sFlag = 0;
for my $line (@comopt_content)
{
	$line =~ s/\s//ig;
	$line =~ s/\x0d\x0a//ig;
	if ($line =~ /ifeq/ && $line =~ /\$\(PP_OPT_COMMON\)/)
	{
		my $matchOpt = 0;
		for (0 ... $#optMak)
		{
			if ($line =~ /$optMak[$_]/)
			{
				$matchOpt = 1;
				last;
			}
		}
		if ($matchOpt == 1)
		{
			push @ifLevel, 1;
		}
		else
		{
			push @ifLevel, 0;
			$ifFlag --;
		}
	}
	elsif ($line =~ /ifeq\(TRUE,\$\(strip/ || $line =~ /ifneq\(FALSE,\$\(strip/)
	{
		my $matchOpt = 0;
		for (0 ... $#pOptMak)
		{
			if ($line =~ /$pOptMak[$_]/)
			{
				$matchOpt = 1;
				last;
			}
		}
		if ($matchOpt == 1)
		{
			push @ifLevel, 1;
		}
		else
		{
			push @ifLevel, 0;
			$ifFlag --;
		}
	}
	elsif ($line =~ /ifneq/ && $line =~ /\$\(PP_OPT_COMMON\)/)
	{
		my $matchOpt = 0;
		for (0 ... $#optMak)
		{
			if ($line =~ /$optMak[$_]/)
			{
				$matchOpt = 1;
				last;
			}
		}
		if ($matchOpt == 1)
		{
			push @ifLevel, 0;
			$ifFlag --;
		}
		else
		{
			push @ifLevel, 1;
		}
	}
	elsif ($line =~ /ifeq\(FALSE,\$\(strip/ || $line =~ /ifneq\(TRUE,\$\(strip/)
	{
		my $matchOpt = 0;
		for (0 ... $#pOptMak)
		{
			if ($line =~ /$pOptMak[$_]/)
			{
				$matchOpt = 1;
				last;
			}
		}
		if ($matchOpt == 1)
		{
			push @ifLevel, 0;
			$ifFlag --;
		}
		else
		{
			push @ifLevel, 1;
		}
	}
	elsif ($line =~ /^endif/)
	{
		unless (pop @ifLevel)
		{
			$ifFlag ++;
		}
	}
	elsif ($line =~ /^else/)
	{
		if (pop @ifLevel)
		{
			$ifFlag --;
			push @ifLevel, 0;
		}
		else
		{
			$ifFlag ++;
			push @ifLevel, 1;
		}
	}
	elsif ($line =~ /^PP_OPT_COMMON\+\=/)
	{
		my $tmpOpt = $';
		my $matchWList = 0;
		if ($tmpOpt =~ /\\/)
		{
			$sFlag = 1;
		}
		elsif ($ifFlag == 0)
		{
			if ($#ifLevel >= 0)
			{
				#push @commonOptMak, $tmpOpt;
				for (0 ... $#whiteList)
				{
					if ($tmpOpt eq $whiteList[$_])
					{
						$matchWList = 1;
					}
				}
				if ($matchWList == 0)
				{
					push @optMak, $tmpOpt;
					print "$tmpOpt\n";
				}
			}
		}
	}
	elsif ($line =~ /\$\(strip/ || $line =~ /\$\(filter/)
	{
		my $specOptMatch = 0;
		for (0 ... $#specialOpt)
		{
			if (($line =~ /ifeq/ && $line =~ /\$\($specialOpt[$_]\)/) || ($line =~ /ifneq/ && $line =~ /\$\($specialOpt[$_]\)/ && $line =~ /\)\),\)/))
			{
				if ($specialOptMak[$_] eq "")
				{
					if ($line =~ /\(\,/)
					{
						$specOptMatch = 1;
						last;
					}
				}
				elsif ($line =~ /$specialOptMak[$_]/)
				{
					$specOptMatch = 1;
					last;
				}
			}
			elsif (($line =~ /ifneq/ && $line =~ /\$\($specialOpt[$_]\)/) || ($line =~ /ifeq/ && $line =~ /\$\($specialOpt[$_]\)/ && $line =~ /\)\),\)/))
			{
				if ($specialOptMak[$_] eq "")
				{
					if ($line !~ /\(,/)
					{
						$specOptMatch = 1;
						last;
					}
				}
				elsif ($line !~ /$specialOptMak[$_]/)
				{
					$specOptMatch = 1;
					last;
				}
			}
		}
		if ($specOptMatch == 1)
		{
			push @ifLevel, 1;
		}
		else
		{
			push @ifLevel, 0;
			$ifFlag --;
		}
	}
	elsif ($sFlag == 1)
	{
		if ($line =~ /\\/)
		{
			if ($ifFlag == 0)
			{
				if ($#ifLevel != 0)
				{
					#push @commonOptMak, $`;
					my $optMakTmp = $`;
					my $matchWList = 0;
					for (0 ... $#whiteList)
					{
						if ($optMakTmp eq $whiteList[$_])
						{
							$matchWList = 1;
						}
					}
					if ($matchWList == 0)
					{
						push @optMak, $optMakTmp;
						print "$optMakTmp\n";
					}
				}
			}
		}
		else
		{
			if ($ifFlag == 0)
			{
				if ($#ifLevel != 0)
				{
					#push @commonOptMak, $line;
					my $matchWList = 0;
					for (0 ... $#whiteList)
					{
						if ($line eq $whiteList[$_])
						{
							$matchWList = 1;
						}
					}
					if ($matchWList == 0)
					{
						push @optMak, $line;
						print "$line\n";
					}
				}
			}
			$sFlag = 0;
		}
	}
}
#push @optMak, @commonOptMak;
## parse PP_OPT_COMMON in common_option.mak == END ==

## read XML file to get the release libs
open(XML_FILE, "sc/customer/default/profile/$xmlFile") or die "cannot read \"$xmlFile\" file\n";
my @xml_content=<XML_FILE>;
close(XML_FILE);

my $chipType = $specialOptMak[0];
$chipType =~ s/\D//ig;

my $findMak = 0;
my $libName = "";
for my $line (@xml_content)
{
	if ($findMak == 1)
	{
		if ($line =~ /\<default_value\>/)
		{
			if ($line =~ /\>SRC_C_LIST/)
			{
				push @noRelLibs, $libName;
				print "lib release: $libName\n";
			}
			$findMak = 0;
		}
	}
	
	if ($line =~ /\.mak/)
	{
		my @tmpLibName = split(/\//, $`);
		unless ($line =~ /\/msw/ && $line !~ /$chipType/)
		{
			$libName = $tmpLibName[$#tmpLibName];
			$findMak = 1;
		}
	}
}
## read XML file to get the release libs == END ==

## search if libs contain optMak or not
if ($optLevel =~ /all/i)
{
	open(LOG_FILE, ">tng/OptCheck/illegalOpt_all.log") or die "cannot read \"illegalOpt.log\" file\n";
	print LOG_FILE "Search all sc and include files...\n\n";
}
elsif ($optLevel =~ /sc/i)
{
	open(LOG_FILE, ">tng/OptCheck/illegalOpt_sc.log") or die "cannot read \"illegalOpt.log\" file\n";
	print LOG_FILE "Search only c files...\n\n";
}
open(OPTLOG_FILE, ">tng/OptCheck/optMak.log") or die "cannot read \"optMak.log\" file\n";
chdir "build/$product/out";
my @tppFiles = <*.tpp>;
for my $path (@tppFiles)
{
	my $fileMatch = 0;
	my $matchNoRelLib = "";
	
	for (0 ... $#noRelLibs)
	{
		$matchNoRelLib = $noRelLibs[$_];
		my $tmpMatchNoRelLib = $matchNoRelLib.".tpp";
		if ($path =~ /^$tmpMatchNoRelLib/)
		{
			$fileMatch = 1;
			last;
		}
	}
	if ($fileMatch == 1)
	{
		print "Search $path...\n";
		open(TPP_FILE, "$path") or die "cannot read \"$path\" file\n";
		my @tpp_content=<TPP_FILE>;
		close(TPP_FILE);
		for my $line (@tpp_content)
		{
			if ($optLevel =~ /all/i)
			{
				for (0 ... $#optMak)
				{
					my $matchOpt = $optMak[$_];
					if ($line =~ /$matchOpt/)
					{
						print LOG_FILE "Lib \"$matchNoRelLib\" contain illegal compile option: $matchOpt\n";
					}
				}
			}
			elsif ($optLevel =~ /sc/i)
			{
				$line =~ s/\s//ig;
				$line =~ s/\x0d\x0a//ig;
				if ($line =~ /^\.\// && $line =~ /\.c/)
				{
					$line =~ s/\.\///ig;
					$line =~ s/\\//ig;
					print "$line $path\n";
					open(C_FILE, "<../../../$line") or next;
					my @c_content=<C_FILE>;
					close(C_FILE);
					
					for my $c_line (@c_content)
					{
						for (0 ... $#optMak)
						{
							my $matchOpt = $optMak[$_];
							if ($c_line =~ /$matchOpt/)
							{
								print LOG_FILE "Lib \"$matchNoRelLib\" $line contain illegal compile option: $matchOpt\n";
							}
						}
					}
				}
			}
		}
	}
}

for (0 ... $#pOptMak)
{
	print OPTLOG_FILE "All product optMak: $pOptMak[$_]\n";
}
for (0 ... $#optMak)
{
	print OPTLOG_FILE "All optMak: $optMak[$_]\n";
}
chdir "../../../";
close(OPTLOG_FILE);
close(LOG_FILE);
## search if libs contain optMak or not == END ==
