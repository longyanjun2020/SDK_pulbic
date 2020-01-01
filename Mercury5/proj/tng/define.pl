#!/usr/bin/perl

use warnings;
use strict;
use Getopt::Std;

my %options=();
getopts("a:c:o:",\%options);

if(!defined($options{o})){
    die "$0: not specify the output file\n";
}

my %used;

sub fix_path{
    local $_=shift;

    #erase the starting ./
    s;^\.\/;;g;
    s;\s+\.\/; ;g;
    #erase the duplicate \ or / or /./
    s#\\+#\/#g;
    s#\/+#\/#g;
    s#\/\.\/#\/#g;
    s#\/$##;
    #s!(^|\s)(\w):\/!$1\/cygdrive\/\l$2\/!g;
    #s!(^|\s)\/(\w)\/!$1\/cygdrive\/\l$2\/!g;

    1 while(s#\/[^/]+\/\.\.\/#\/#g);
    return $_;
}

sub loadPaths
{
    my $file = shift;
    my @paths;

    open(PATHS, "< $file") or die "cannot read \"$file\" file\n";
    while(<PATHS>)
    {
        chomp;
        s#(?:\\+|\/+)#\/#g;
        push @paths, split;
    }

    return(\@paths);
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
my $c_paths = loadPaths($options{c}) if($options{c});
my $asm_paths = loadPaths($options{a}) if($options{a});

# init results strings
my (%c_srcs, %cpp_srcs, %asm_srcs, %objs); 

# for each object name on the command line
for my $obj (@ARGV)
{
    my $path;
    # $obj =~ s/\.o$//;

    # get file extension
    my $sub_obj = $obj;
    $sub_obj =~ s/.*\.//;

    if( $sub_obj eq "c" ||  $sub_obj eq "cpp" )
    {
        $path = findPath("$obj", $c_paths);
        if ($path ne ""){
            if ($sub_obj eq "c"){
                $c_srcs{$path} =1;
            }
            if ($sub_obj eq "cpp"){
                $cpp_srcs{$path} = 1;
            }
        }
        else{
            die "cannot find source of \"$obj\"\n";
        }
    }
    elsif( $sub_obj eq "asm" ||  $sub_obj eq "S" )
    {
        $path = findPath("$obj", $asm_paths);
        if ($path ne ""){
            $asm_srcs{$path}= 1;
        }
        else{
            die "cannot find source of \"$obj\"\n";
        }
    }
    else{
            die "no such file type \"$obj\"\n";
    }
    $obj =~ s/\..*$/\.o/;
    $objs{$obj}=1;
}

sub fix_paths_to_str{
    return join("\\\n\t", map{fix_path($_)} sort @_);
}

# output results according to a makefile syntax
open(DFN, "> $output") or die "cannot write to \"$output\"\n";
printf DFN <<EOM, fix_paths_to_str(keys %objs), fix_paths_to_str(keys %c_srcs), fix_paths_to_str(keys %cpp_srcs), fix_paths_to_str(keys %asm_srcs), fix_paths_to_str(keys %used);
OBJS =\\
	%s

C_SRCS =\\
	%s

CPP_SRCS =\\
	%s

ASM_SRCS =\\
	%s

SRC_DIRS =\\
	%s

EOM
#print DFN "\nOBJS =", (map{"\\\n\t$_"} sort keys %objs), "\n\n",
#    "C_SRCS =", (map{"\\\n\t$_"} sort keys %c_srcs), "\n\n",
#    "CPP_SRCS =", (map{"\\\n\t$_"} sort keys %cpp_srcs), "\n\n",
#    "ASM_SRCS =", (map{"\\\n\t$_"} sort keys %asm_srcs), "\n\n",
#    "SRC_DIRS =",
#    map{"\\\n\t$_"} keys(%used),
#    "\n\n\$(C_SRCS) \$(CPP_SRCS) \$(ASM_SRCS):;\n";

#foreach my $path (keys(%used)) {
#    print DFN "\\\n\t", $path;
#}
close(DFN);
