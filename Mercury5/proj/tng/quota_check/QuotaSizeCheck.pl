#!/usr/bin/perl

#####
## SYNTAX:
## perl quotaSizeCheck.pl quota-check.log category_setting_8532_64_32_mb406g.xml
#####

use warnings;
use strict;

my $quotaCheckLog = shift;
my $categoryXML = shift;

my $emailTo = "";
my @emailContent = ();
my $warning_str = "";

sub checkSize
{
	my $logLine = shift;
	my $rom_ram = shift;
	my $catName = shift;
	my $warningSize = shift;
	my $catEmail = shift;
	
	my $rSize = 0;
	my $rLimit = 0;
	my $leftSize = 0;
	my $tmp;
	my $ret;
	my $too_large_str = "(Size is TOO LARGE!!)";
	
	$catName =~ s/\\\\/\\/g;
	
	if ($logLine =~ /$rom_ram Limit Size:/ig)
	{
		$rSize = $`;
		$rLimit = $'; #'
		
		$rSize =~ s/ //g;
		
		$rLimit =~ s/\n//;
		$rLimit =~ s/ //g;
	}
	
	$leftSize = $rLimit - $rSize;
	$tmp = "";

	if ($leftSize <= $warningSize)
	{
		$ret = 1;
		if($rSize eq 0)
		{
			$too_large_str = "";
			$ret = 0;
		}
		$tmp = "$catName $rom_ram Size:$rSize, Limit Size:$rLimit, Warning Size:$warningSize, Left Size:$leftSize  $too_large_str\n";
	}
	else
	{
		$tmp = "$catName $rom_ram Size:$rSize, Limit Size:$rLimit, Warning Size:$warningSize, Left Size:$leftSize\n";
		$ret = 0;
	}
	
	$warning_str .= "$tmp";
	if($rom_ram eq "RAM")
	{
		$warning_str .= "\n";
		$warning_str = "Owner: $catEmail\n".$warning_str;
		push @emailContent, $warning_str;
		$warning_str = "";
	}
	elsif($rom_ram eq "CUS")
	{
		$warning_str = "Owner: $catEmail\n".$warning_str;
		push @emailContent, $warning_str;
	}	
	
	return $ret;
}

sub parseQuotaLog
{
	my $catName = shift;
	my $romWarning = shift;
	my $ramWarning = shift;
	my $catEmail = shift;
	
	my $warningFlag_rom = 0;
	my $warningFlag_ram = 0;
	my $warningFlag_cus = 0;
	
	open(LOG_FILE, "< $quotaCheckLog") or die "cannot read \"$quotaCheckLog\" file\n";
	my @logContant = <LOG_FILE>;
	close(LOG_FILE);
	
	$catName =~ s/\\/\\\\/g;
	
	for my $line (@logContant)
	{
		if ($line =~ /^$catName ROM Size:/ig)
		{
			$warning_str = "";
			$warningFlag_rom = checkSize($', "ROM", $catName, $romWarning, $catEmail); #'
		}
		if ($line =~ /^$catName RAM Size:/ig)
		{
			$warningFlag_ram = checkSize($', "RAM", $catName, $ramWarning, $catEmail); #'
		}
		if ($line =~ /^$catName CUS Size:/ig)
		{
			$warningFlag_cus = checkSize($', "CUS", $catName, $romWarning, $catEmail); #'
			return $warningFlag_cus;
		}
	}
	return $warningFlag_rom + $warningFlag_ram;
}

sub parseCategoryXml
{
	my $catName = "";
	my $catEmail = "";
	my $romWarning = 0;
	my $ramWarning = 0;
	
	open(XML_FILE, "< $categoryXML") or die "cannot read \"$categoryXML\" file\n";
	my @xmlContant = <XML_FILE>;
	close(XML_FILE);
	
	for my $line (@xmlContant)
	{
		$line =~ s/\n//;
		if ($line =~ /^\<QUOTA Manager=\"/)
		{
			$line =~ s/$&//;
			$line =~ s/\"\>//;
			$line =~ s/\r//g;
			if ($emailTo ne "")
			{
				$emailTo = $emailTo.",".$line;
			}
			else
			{
				$emailTo = $line;
			}
			open(LOG_FILE, "< $quotaCheckLog") or die "cannot read \"$quotaCheckLog\" file\n";
			my @logContant = <LOG_FILE>;
			close(LOG_FILE);
			
			if ($logContant[$#logContant] =~ /DZ CHECK QUOTA DONE:FAIL/)
			{
				push @emailContent, "DZ CHECK QUOTA DONE:FAIL";
				return 0;
			}
		}
		elsif ($line =~ /\<CATEGORY Name=\"/)
		{
			$line = $'; #'
			$line =~ s/ //g;
			$line =~ s/\"\/\>//;
			if ($line =~ /\"ROM_LIMIT_SIZE=\"/)
			{
				$catName = $`;
			}
			if ($line =~ /ROM_Warning=\"/)
			{
				$line = $'; #'
				if ($line =~ /\"RAM_Warning=\"/)
				{
					$romWarning = $`;
					$line = $'; #'
					if ($line =~ /\"Contact=\"/)
					{
						$ramWarning = $`;
						$catEmail = $'; #'
						$catEmail =~ s/\r//g;
					}
				}
			}
			my $warningFlag = parseQuotaLog($catName, $romWarning, $ramWarning, $catEmail);
			if ($warningFlag)
			{
				if ($emailTo ne "")
				{
					$emailTo = $emailTo.",".$catEmail;
				}
				else
				{
					$emailTo = $catEmail;
				}
			}
		}
		elsif ($line =~ /\<CUS Name=\"/)
		{
			$line = $'; #'
			$line =~ s/ //g;
			$line =~ s/\"\/\>//;
			if ($line =~ /\"ROM_LIMIT_SIZE=\"/)
			{
				$catName = $`;
			}
			if ($line =~ /Warning=\"/)
			{
				$line = $'; #'
				if ($line =~ /\"Contact=\"/)
				{
					$romWarning = $`;
					$catEmail = $'; #'
					$catEmail =~ s/\r//g;
				}
			}
			my $warningFlag = parseQuotaLog($catName, $romWarning, 0, $catEmail);
			if ($warningFlag)
			{
				if ($emailTo ne "")
				{
					$emailTo = $emailTo.",".$catEmail;
				}
				else
				{
					$emailTo = $catEmail;
				}
			}
		}
	}
}

# main code
parseCategoryXml();

if (-e "QuotaCheckEmail.txt")
{
	unlink "QuotaCheckEmail.txt";
}
open(RESULT_FILE, "> QuotaCheckEmail.txt") or die "cannot read \"QuotaCheckEmail.txt\" file\n";
print RESULT_FILE "$emailTo,\n";
print RESULT_FILE @emailContent;
close(RESULT_FILE);
