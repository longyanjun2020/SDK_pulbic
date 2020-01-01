#!/usr/bin/perl

use warnings;
use strict;

my $outPath = shift;
my $firstLine = "Id; Entity; String; File; Line";

system("date");

unlink "$outPath/remtrace.csv";
unlink "$outPath/remtrace.ini";

open(OUT_CSV, ">> $outPath/remtrace.csv") or die "cannot read \"$outPath/remtrace.csv\" file\n";
print OUT_CSV "$firstLine\n";

chdir "$outPath/remtrace_lib";
my @allFiles = <*.csv>;
for my $path (@allFiles)
{
	open(CSV_FILE, "$path") or die "cannot read \"$path\" file\n";
	my @content=<CSV_FILE>;
	close(CSV_FILE);
	for my $line (@content)
	{
		if ($line !~ /$firstLine/)
		{
			print OUT_CSV $line;
		}
	}
}
chdir "../../../../";
close(OUT_CSV);

open(TRC_ID, "< tng/remtrace/remtraceID") or die "cannot open file: \"remtraceID\"\n";
my $currentID = 0;
my @traceIDContent=<TRC_ID>;
for my $line (@traceIDContent)
{
	if ($line =~ /CURRENT_ID\=/)
	{
		$currentID = $';
		$currentID =~ s/\x0d\x0a//ig;
		chomp $currentID;
	}
}
close TRC_ID;

open(OUT_INI, "> $outPath/remtrace.ini") or die "cannot read \"$outPath/remtrace.ini\" file\n";
print OUT_INI "[BaseTraceId]\n";
print OUT_INI "Value=$currentID\n\n";
print OUT_INI "[AllString]\n";
print OUT_INI "FreeSize=10000\n";
close OUT_INI;

system("date");
