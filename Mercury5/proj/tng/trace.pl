#!/usr/bin/perl

use warnings;
use strict;
my $o_file; 
my $c_file;

my $NORMAL="\e[0m";
my $BOLD="\e[1m";
my $GREEN="\e[32m";
my $YELLOW="\e[33m";
my $RED="\e[31m";

my %colors = ( "debug" => $YELLOW,
			   "info" => $NORMAL,
			   "warn" => $GREEN,
			   "error" => $RED );

# get trace level
my $default = shift;
my $warning_stop = shift;
my $userout_switch = shift;
my $filter = $ENV{"FILTER"};

$filter = "" if (! defined($filter));

# execute command
my $cmd = "";
# quote args which contains special chars
foreach my $arg ( @ARGV )
{
	if ($arg =~ m/[ \t\\]/)
	{
		$arg =~ s/\"/\\\"/g;
		$arg = "\"" . $arg . "\"";
	}
	elsif ($arg =~ m/=\"/)
	{
		$arg =~ s/\"/\\\"/g;
	}
	$cmd .= $arg . " ";
	$o_file = $c_file;
	$c_file = $arg;
}
$cmd .= " 2>&1";

my $result = 0;

# popen the command and pipe output to LOG
open LOG, "$cmd |" or die "error execute $cmd";
if ($userout_switch eq "userout_on") {
# open the user terminal
my $userout = $ENV{"USEROUT"};
if (defined($userout)) {
	# use the stdout descriptor saved by log.pl
	open USER, ">&=$userout" or die "cannot echo to <", $userout, ">\n";
}
else {
	# or use the current terminal
    my $tty=`tty`;
	open USER, "> $tty" or die "cannot echo to $tty\n";
}
}

# enable colors:
my $color;
if ($userout_switch eq "userout_on") {
	$color = ((-t USER)               # on interactive terminal
			 and ($filter !~ m/color/)       # at user request
			 and (($ENV{"TERM"} eq "xterm")         # on xterm
				  or ($ENV{"TERM"} eq "cygwin"))); # or cygwin
} else {
	$color = (($filter !~ m/color/)       # at user request
				and (($ENV{"TERM"} eq "xterm")         # on xterm
				or  ($ENV{"TERM"} eq "cygwin"))); # or cygwin				 
}

print "<TNG>";
# for each trace line
while(<LOG>)
{
	# compute current line level
	my $level = $default;
	if (m/error:/i) { $level = "error" }
	elsif (m/warning:/i) 
		{ 
		    $level = "warn";
		    if ($warning_stop eq "warning_stop_on")
		    {
		        $result=1;
		        #delete c and o file in out folder
		        unlink $o_file if ($o_file !~ /\.c$/ && $o_file !~ /\.cpp$/);
		        unlink $c_file if ($c_file !~ /\.c$/ && $c_file !~ /\.cpp$/);
		    }
		}

	# print line to stdout
	print $_;

	# if line level is not filtered
	if ($filter !~ m/$level/i)
	{
		if ($userout_switch eq "userout_on") {
		# if colors are allowed
		if ($color) {
		# echo colored line to user
		print USER $colors{$level}, $_, $NORMAL;
			} else {
				print USER $_;
	}
		}
	}
}

if ($userout_switch eq "userout_on") {	
close USER;
}

close LOG;
$_ = $? >> 8;
if ($_) {
	$result = $_;
}

exit $result;
