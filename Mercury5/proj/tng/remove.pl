#!/usr/bin/perl

use warnings;
use strict;
use Getopt::Std;

my %used;

my %options=();
getopts("a:c:o:",\%options);

if(!defined($options{o})){
    die "$0: not specify the output file\n";
}

sub loadPaths
{
	my $file = shift;
	my @paths;

	open(PATHS, "< $file") or die "cannot read \"$file\" file\n";
	while(<PATHS>)
	{
		chomp;
        s#(:?\\|\/)+#\/#g;
		push @paths, split;
	}

	return(@paths);
}

# try to find a existing file throughout a path list
sub findPath
{
    # searched name
    (my $name, my $_paths)= @_;

    for my $path (keys(%used),@$_paths)
    {
        #my $test = "$path/$name";
        if (-f "$path/$name")
        {
            #if (defined($used{$path})) {
            #	$used{$path} += 1;
            #}
            #else {
            $used{$path}++;
#			}

            return "$path/$name";
        }
    }
}

# get output file name
my $output = $options{o};
# load content of paths files
my @c_paths = loadPaths($options{c}) if($options{c});
my @asm_paths = loadPaths($options{a}) if($options{a});

# init results strings
my $objs = "";
my $del_srcs = "";
# for each object name on the command line
for my $obj (@ARGV)
{
	my $path;
	$objs .= "\\\n\t$obj";
	# remove object ".o" extension

	# try to find a source file name
	$path = findPath("$obj", \@c_paths);
	if ($path ne "") {
		$del_srcs .= "\\\n\t$path";
	}else {
		$path = findPath("$obj", \@asm_paths);
		if ($path ne "") {
			$del_srcs .= "\\\n\t$path";
		}
		else {
			print "cannot find source of \"$obj\"\n";
		}
	}
}

# output results according to a makefile syntax
open(DFN, "> $output") or die "cannot write to \"$output\"\n";
print DFN "DEL_SRCS =$del_srcs\n\n",
    "DEL_SRC_DIRS =",
    map{"\\\n\t$_"} keys(%used);
#foreach my $path (keys(%used)) {
#	print DFN "\\\n\t", $path;
#}
close(DFN);
