#!/usr/bin/perl
use File::Copy;
use File::Path;
#use File::Copy::Recursive;
use warnings;
use strict;

my $pattern_filename = shift;
my $product_name = shift;

# ======== define G1 and B3 ========
my @G1 = ("8830n");
my @Bravo = ("8533d");
my @B3 = ("8533c", "8533n", "8532", "8536");

my $G1_flag = 0;
my $B3_flag = 0;

for (0 ... $#G1)
{
	if ($product_name =~ /$G1[$_]/)
	{
		$G1_flag = 1;
	}
}

for (0 ... $#B3)
{
	if ($product_name =~ /$B3[$_]/)
	{
		$B3_flag = 1;
	}
}

for (0 ... $#Bravo)
{
	if ($product_name =~ /$Bravo[$_]/)
	{
		$B3_flag = 1;
	}
}

if ($G1_flag && $B3_flag)
{
	die "ERROR -- wrong defination of G1 and B3. \n";
}
# ==================================

open(PATTERN_FILE, "$pattern_filename") or die "cannot read \"$pattern_filename\" file\n";
my @patterns=<PATTERN_FILE>;
close(PATTERN_FILE);

open(LOG_FILE, ">> UnmatchReleaseOp.log") or die "cannot write\"UnmatchReleaseOp.log\" file\n";
print "open UnmatchReleaseOp.log\n";

my $unmatchOp = undef;
my $productRelOp = undef;
unless (-e "ReleaseOptions_R_".$product_name.".txt")
{
	open(R_FILE, "> ReleaseOptions_R_".$product_name.".txt") or die "cannot read \"ReleaseOptions_R.txt\" file\n";
	$productRelOp = 1;
}

for my $pattern_line (@patterns)
{
	my $checkNextLine = 0;
	my $matchOp = undef;

	if ($pattern_line =~ /#/)
	{
		#ignore comments
	}
	elsif ($pattern_line =~ /replace/)
	{
		my @elements = split(/ /, $pattern_line);
		my $filename = $elements[1];
		my $pattern = $elements[2];
		my $on_off = $elements[3];
		$on_off =~ s/\s+$//;

		$on_off =~ s/\x0D\x0A//g;
		$filename =~ s/%product_name%/$product_name/ig;
		my $new_pattern_line="";
		if ($on_off eq "on")
		{
			$new_pattern_line = "replace ".$filename." ".$pattern." off\n";
		}
		elsif ($on_off eq "TRUE")
		{
			$new_pattern_line = "replace ".$filename." ".$pattern." FALSE\n";
		}
		elsif ($on_off eq "off")
		{
			$new_pattern_line = "replace ".$filename." ".$pattern." on\n";
		}
		elsif ($on_off eq "FALSE")
		{
			$new_pattern_line = "replace ".$filename." ".$pattern." TRUE\n";
		}

		if ((-e "ReleaseOptions_R_".$product_name.".txt") && defined($productRelOp))
		{
			print R_FILE $new_pattern_line;
		}


		if( -e "$filename")
		{
			#print "check $filename \n";
		}
		else
		{
			print "file does not exist!\nFile:$filename\n";
			next;
		}

		open(H_FILE, "$filename") or die "cannot read \"$filename\" file\n";
		my @content=<H_FILE>;
		close(H_FILE);

		open(H_FILE, "> $filename") or die "cannot read \"$filename\" file\n";
		for my $line (@content)
		{
			if ($filename =~ /\.mak$/)
			{
				my $line_tmp = $line;
				$line_tmp =~ s/\s//ig;
				if ($line_tmp =~ /PP_OPT_COMMON\+\=$pattern/ || $line_tmp =~ /^$pattern\=/ || $line_tmp =~ /^#$pattern\=/)
				{
					if (($on_off eq "on") || ($on_off eq "TRUE"))
					{
						if ($line =~ /^#/)
						{
							$line =~ s/#//;
							print "turn $on_off $pattern\n";
						}
						if ($line =~ /FALSE/)
						{
							$line =~ s/FALSE/TRUE/;
							print "turn $on_off $pattern\n";
						}
						$matchOp = 1;
					}
					elsif (($on_off eq "off") || ($on_off eq "FALSE"))
					{
						if ($line !~ /^#/)
						{
							if ($line =~ /TRUE/)
							{
								$line =~ s/TRUE/FALSE/;
								print "turn $on_off $pattern\n";
							}
							elsif ($line !~ /FALSE/)
							{
								$line = "#".$line;
								print "Disable $pattern\n";
							}
						}
						$matchOp = 1;
					}
					elsif ($on_off eq "del_op")
					{
						$line = "\n";
						$matchOp = 1;
					}
					elsif ($line_tmp =~ /$pattern\=/)
					{
						my $pattern_s = $';#'
						if ($pattern_s ne "")
						{
							$line =~ s/$pattern_s/$on_off/;
						}
						else
						{
							$line = "$pattern \= $on_off\n";
						}
						$matchOp = 1;
					}
					elsif ($line_tmp =~ /\=$pattern/)
					{
						$line =~ s/$pattern/$on_off/;
						$matchOp = 1;
					}
				}
			}
			else
			{
				if ($line =~ /$pattern/)
				{
					$line =~ s/$pattern/$on_off/;
					print "replace $pattern by $on_off\n";
					$matchOp = 1;
				}
			}
			print H_FILE $line;
		}
		if (!defined($matchOp))
		{
			print LOG_FILE "cannot turn $on_off $pattern\n";
			$unmatchOp ++;
		}
		close(H_FILE);
	}
	elsif ($pattern_line =~ /move/)
	{
		my @elements = split(/ /, $pattern_line);
		my $filename = $elements[1];
		$filename =~ s/\x0D\x0A//g;
		$filename =~ s/\s+$//;
		$filename =~ s/%product_name%/$product_name/ig;
		if (-e $filename)
		{
			print "move $filename\n";
			my @fname = split(/\//, $filename);
			my $ppath = "";
			for (0 ... $#fname-1)
			{
				if ($fname[$_] !~ /\./)
				{
					$fname[$_] =~ s/\s+$//;
					$ppath = $ppath . $fname[$_] . "/";
				}
			}
			$ppath =~ s/\s+$//;
			mkpath("proj");
			unless (-e "proj/".$ppath)
			{
				mkpath("proj/".$ppath);
			}
			if (-d $filename)
			{
				print "dir move $filename\n";
				system("mv $filename proj/$ppath/");
			}
			else
			{
				print "move $filename\n";
				move($filename, "proj/".$ppath."/");
			}
		}
		else
		{
			print LOG_FILE "cannot move $filename\n";
			$unmatchOp ++;
		}
	}
	elsif ($pattern_line =~ /copy/)
	{
		my @elements = split(/ /, $pattern_line);
		my $filename = $elements[1];
		$filename =~ s/\x0D\x0A//g;
		$filename =~ s/\s+$//;
		$filename =~ s/%product_name%/$product_name/ig;
		if (-e $filename)
		{
			my @fname = split(/\//, $filename);
			my $ppath = "";
			for (0 ... $#fname-1)
			{
				if ($fname[$_] !~ /\./)
				{
					$fname[$_] =~ s/\s+$//;
					$ppath = $ppath . $fname[$_] . "/";
				}
			}
			$ppath =~ s/\s+$//;
			mkpath("proj");
			unless (-e "proj/".$ppath)
			{
				mkpath("proj/".$ppath);
			}
			if (-d $filename)
			{
				print "dircopy $filename\n";
				system("cp -r $filename proj/$ppath/");
			}
			else
			{
				print "copy $filename\n";
				copy($filename, "proj/".$ppath."/");
			}
		}
		else
		{
			print LOG_FILE "cannot remove $filename\n";
			$unmatchOp ++;
		}
	}
	elsif ($pattern_line =~ /del/)
	{
		my @elements = split(/ /, $pattern_line);
		my $filename = $elements[1];
		$filename =~ s/\x0D\x0A//g;
		$filename =~ s/\s+$//;
		$filename =~ s/%product_name%/$product_name/ig;

		if (($elements[0] =~ /B3_/ && $B3_flag == 1) || ($elements[0] =~ /G1_/ && $G1_flag == 1) || $elements[0] =~ /^del/)
		{
			if (-e $filename)
			{
				my @fname = split(/\//, $filename);
				if (-d $filename)
				{
					print "dir remove $filename\n";
					system("rm -r $filename");
				}
				else
				{
					print "remove $filename\n";
					unlink "$filename";
				}
			}
			elsif ($filename =~ /\*/)
			{
				print "remove $filename\n";
				system("rm -r $filename");
			}
			else
			{
				print LOG_FILE "cannot remove $filename\n";
				$unmatchOp ++;
			}
		}
	}
}

if ((-e "ReleaseOptions_R_".$product_name.".txt") && defined($productRelOp))
{
	close(R_FILE);
}

#mkpath("proj/sc/application/mmi/app/EmuApp/inc/priv");

close (LOG_FILE);
if (!defined($unmatchOp))
{
	print "remove UnmatchReleaseOp.log\n";
	unlink "UnmatchReleaseOp.log";
}
