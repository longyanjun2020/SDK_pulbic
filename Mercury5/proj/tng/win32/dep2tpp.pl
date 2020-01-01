#!/usr/bin/perl

use strict;
#use File::Basename;

my $target;
my %depends;
my %rules;

my %defines;
my %undefs;
my %includes;

my $src_path = shift;
my $dst_path = shift;

my $out_dir = shift;
my $inc_dir = shift;

sub basename
{
	my $path = shift;
	$path =~ s/[^\/]*\///g;
	return($path);
}

sub dirname
{
	my $path = shift;
	$path =~ s/\/[^\/]*$//;
	return($path);
}

my $sysinc = $ENV{"ARMINC"};
$sysinc =~ s/\\/\//g;

sub addPaths
{
	my $paths = shift;

	# remove unwanted spaces and "\"
	#$paths =~ s/^\s*//;
	#$paths =~ s/\s*\\?\z//;
	# dos to unix
	$paths =~ s/\\/\//g;

	foreach my $path (split("[ \t]+", $paths))
	{
		next if ($path =~ m/$sysinc/o);

		# extract file name
		my $name = basename($path);

		if ($name ne "")
		{
			# if target dependencies list is defined
			if (defined($depends{$target})) {
				# dependency is a included file
				$name = $inc_dir . $name;
			}
			else {
				# create a void list
				$depends{$target} = [];
				# first dependency is the source file
				$name = $out_dir . $name;
			}

			# add name to target dependencies list
			push @{$depends{$target}}, $name;
			# create a rule to copy the source file
			if (($rules{$name} ne "") and ($rules{$name} ne $path))
			{
				warn "conflict between $rules{$name} and $path\n";
			}
			$rules{$name} = $path;
		}
	}
}

# open input
open(DEP, "< $src_path") or die "cannot open input: \"$src_path\"\n";

while(<DEP>)
{
	chomp;
	# collect #define
	if (s/^#define //) {
		$defines{$_} += 1;
		next;
	}
	# collect #undef
	if (s/^#undef //) {
		$undefs{$_} += 1;
		next;
	}
	# collect #include
	if (s/^#include //) {
		$includes{dirname($_)} += 1;
		next;
	}

	# remove comments
	s/#.*//;

	# detect a target line
	if (m/^.+:/)
	{
		# change current target
		($target, my $paths) = split(":[ \t]+");

		$target = $out_dir . basename($target);

		addPaths($paths);
	}
	# detect a dependencie line
	elsif (m/.+/)
	{
		addPaths($_);
	}
}

close DEP;


sub printSorted
{
	my $_hash = shift;

	my @use = sort({$b <=> $a} values(%$_hash));
	for my $score (@use)
	{
		for my $key (keys(%$_hash))
		{
			if ($$_hash{$key} == $score)
			{
				print TPP "\\\n\t", $key;
				$$_hash{$key} = 0;
				last;
			}
		}
	}
}

# open output
open(TPP, "> $dst_path") or die "cannot open output \"$dst_path\"\n";

print TPP "USE_DEFS =";
printSorted \%defines;
print TPP "\n\n";

print TPP "USE_UNDEFS =";
printSorted \%undefs;
print TPP "\n\n";

print TPP "INC_DIRS =";
printSorted \%includes;
print TPP "\n\n";

# output objects dependencies lists
while ((my $object, my $_list) = each(%depends))
{
	print TPP $object, ":";
	foreach (@$_list) { print TPP " ", $_; }
	print TPP "\n\n";
}

print TPP "DEPENDS =";
for my $key (values(%rules)) { print TPP "\\\n\t", $key; }
print TPP "\n\n";

# output sources copy rules
while ((my $target, my $source) = each(%rules))
{
	print TPP $target, ": ", $source, "\n";
	if ($target =~ m/\.(c|h.*)\z/) {
#		print TPP "\t\@echo \$(CPP_LINE)\n";
		print TPP "\t\$(CPP_LINE)\n\n";
	}
	else {
#		print TPP "\t\@echo \$(PP_LINE)\n";
		print TPP "\t\$(PP_LINE)\n\n";
	}
}
#print  "src=$src_path, dst_path= $dst_path,  out_dir=$out_dir, inc_dir=$inc_dir\n";
close TPP;

