#!/usr/bin/perl

use warnings;
use strict;
my $product = shift;
my $log = $product . ".trace";
my $o_file; 
my $c_file;

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
	$cmd .= $arg . " ";
	$o_file = $c_file;
	$c_file = $arg;
}
$cmd .= " 1>$log 2>&1";

my $result = system($cmd) >> 8;

# open the traces file
open LOG, "< $log" or die "cannot read $log\n";
if($result==1)
{
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

# for each trace line
while(<LOG>)
{
	if(m/warning:/i) 
	{ 
		#To stop target build for compile warning
		$result=1;
		#delete c and o file in out folder
		unlink $o_file;
		unlink $c_file;
	}
	# print line to stdout
	print $_;
}

close USER;
close LOG;
unlink $log;

exit $result;
