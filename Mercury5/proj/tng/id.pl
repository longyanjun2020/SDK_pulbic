#!/usr/bin/perl

use warnings;
use strict;

my $header = shift;

my $url;
my $rev;

sub basename
{
	my $path = shift;
	my $sep = rindex($path, "/");

	return(substr($path, $sep+1)) if ($sep > 0);

	return($path);
}

# get svn info
my $cmd = "";
open INFO, "svn info |";
while (<INFO>)
{
	chomp;
	next if (! m/: /);
	my ($tag, $val) = split(": ");

	$url = $val if ($tag eq "URL");
	$rev = $val if ($tag eq "Revision");
}
close INFO;

if (! defined($url) and ! defined($rev))
{
	die "error: cannot build any id";
}
	
# build the id string
my $id = sprintf("%s-%04d", substr(basename($url), 0, 10), $rev);

# build the header name
my $define = "__" . uc(basename($header)) . "__";
$define =~ s/\./_/g;

# write the header file
open HEADER, "> $header" or die "cannot write to \"", $header, "\"\n";

print HEADER "#ifndef ", $define, "\n";
print HEADER "#define ", $define, "\n";
print HEADER "const u8 CoreRelease[] = \"", $id, "\";\n";
print HEADER "#endif\n";

close HEADER;

