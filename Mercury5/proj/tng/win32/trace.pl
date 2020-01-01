#!/usr/bin/perl

use warnings;
use strict;
my $product = shift;
my $log = $product .".trace";

# get trace level
my $default = shift;
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
	$cmd .= $arg . " ";
}
$cmd .= " 1>$log 2>&1";

#print "[TRACE]=======$cmd=======\n";

my $result = system($cmd) >> 8;

# open the traces file
open LOG, "< $log" or die "Perl:cannot read $log\n";
# open the user terminal
# use the stdout descriptor saved by log.pl

print "<TNG>";
# for each trace line
while(<LOG>)
{
	# compute current line level
	my $level = $default;
	if (m/error:/i) { $level = "error" }
	elsif (m/warning:/i) { $level = "warn" }

	# print line to stdout
	print $_;

	# if line level is not filtered
	if ($filter !~ m/$level/i)
	{		
		print STDERR $_;		
	}
}

close LOG;
unlink $log;

exit $result;
