#!/usr/bin/perl

use warnings;
use strict;
use File::Copy;

my %used;

my $documentDir = shift;
my $group = shift;
my $outputFileName = shift;
my @documents;
my $found_group = -1;

sub genDocumentList
{
	my $path = shift;
	my @allFiles = <*>;
	my @current_path;
	for my $path (@allFiles)
	{
		if (-d $path)
		{
			if ($path !~ /\.svn/i)
			{
				if ($path =~ /$group|XMMI|Common/i)
				{
					$found_group++;
				}
				chdir $path;
				push @current_path, $path;
				genDocumentList();
				chdir "../";
				$path = pop (@current_path);
				if($path =~ /$group|XMMI|Common/i)
				{
					$found_group--;
				}
			}
		}
		elsif ($found_group == 1)
		{
			if ($path =~ /\_v[0-9]+\./i)
			{
				my $name = $`;
				my $found = 0;
				for my $document (@documents)
				{
					if ($document eq $name)
					{
						$found = 1;
					}
				}
				if ($found == 0)
				{
					push @documents, $name;
				}
			}
			else
			{
				print "bad document version: $path\n";
			}
		}
	}

}

chdir "$documentDir";
genDocumentList($documentDir);
chdir "../";

my $any_doc = 1;
if ($#documents == -1)
{
	$any_doc = 0;
}

open(INFILE, "< $outputFileName") or die "cannot read \"$outputFileName\" file\n";
my @content=<INFILE>;
close(INFILE);

open(OUTPUT, "> $outputFileName") or die "cannot write \"$outputFileName\" file\n";
#print OUTPUT "\<\?xml version=\"1.0\" encoding=\"utf-8\"\?\>\n";
#print OUTPUT "<documents>\n";
my $found_cnt = 1;
my $last_line;
for my $line (@content)
{
	if ($line =~ /<\/name>/)
	{
		my $name = $`;
		my $found = 0;
		my $document;
		my @new_documents;
		$name =~ s/<name>//;
		$name =~ s/\x20//g;
		$name =~ s/\x09//g;
		while ($#documents + 1)
		{
			$document = pop (@documents);
			if ($document eq $name)
			{
				$found = 1;
			}
			else
			{
				push @new_documents, $document;
			}
		}
		@documents = reverse @new_documents;
		unless ($found == 1)
		{
			$found_cnt = -3;
		}
	}
	if (($line !~ /<\/documents>/) && ($found_cnt == 1))
	{
		print OUTPUT $line;
		$last_line = $line;
	}
	unless ($found_cnt == 1)
	{
		$found_cnt ++;
	}
}

if ($any_doc == 0)
{
	close(OUTPUT);
	open(OUTPUT, "> $outputFileName") or die "cannot write \"$outputFileName\" file\n";
	print OUTPUT "\<\?xml version=\"1.0\" encoding=\"utf-8\"\?\>\n";
	print OUTPUT "<documents>\n";
}

for my $document (@documents)
{
	if ($last_line !~ /<doc_info>/)
	{
		print OUTPUT "	<doc_info>\n";
	}
	print OUTPUT "		<name>$document</name>\n";
	print OUTPUT "		<release>NO</release>\n";
	print OUTPUT "	</doc_info>\n";
	$last_line = "	</doc_info>\n";
}
print OUTPUT "</documents>\n";
close(OUTPUT);
