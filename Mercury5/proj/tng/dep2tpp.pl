#!/usr/bin/perl
use strict;
use warnings;
use Getopt::Std;

my %options=();
getopts("f:o:i:c:ghrt:v",\%options);
if($options{h}){
    print <<EOF;
Usage: $0 [-h] [-f TPP_FILE] [-o OUT_DIR] [-i dfn/rfn file] [-c COMPILER] [-g] [-r] [-t OSTYPE] DEP_FILES
\tDEP_FILES: input dependency files
\t-h: show usage
\t-f TPP_FILE: specify tpp file path
\t-o OUT_DIR: specify the folder to store rtpp preprocessed c files
\t-i dfn/rfn file: specify the dfn/cfn file
\t-c COMPILER: specify the compiler. if not specified, it will be found in
\t             config.mak
\t-g: rtpp with remtrace ID
\t-r: produce rtpp rules
\t-t: specify the ostype, cygwin or msys(mingw)
\t-v: verbose mode, print debug messages
EOF
    exit 0;
}

############################
# debug_print(STRING)
# print STRING if -v
############################
sub debug_print{
    print "@_" if($options{v});
}

sub src2obj{
    local $_=shift;
    s^\.c(?:pp)?$^\.o^;
    s^\.S$^\.o^;
    s^\.asm$^\.o^;
    return $_;
}

#get file name
sub basename{
    local $_=shift;
    s/.*\///;
    return $_;
}

#get dir name
sub dirname{
    local $_ = shift;
     s/\/[^\/]*$//;
    return $_;
}

#erase front & tailing space
sub strip{
    local $_=shift;
    s/^\s+//;
    s/\s+$//;
    return $_;
}

sub _sort{
    my $_hash = shift;
    return [sort {
        $$_hash{$b} <=> $$_hash{$a} or length($a) <=> length($b)
    } keys(%$_hash)];
}
sub _uniq{
    my %uniq=();
    return grep{
            !$uniq{$_}++
        }@_;
}

my (%depends, %defines, %undefs, %includes);
my $compiler = $options{c};			# Get Compiler type from input argument.
(my $target_lib=$options{f}) =~ s!^.*\/(\w+)\.tpp!$1!g;
my $ostype;
if(defined($options{t})){
    $ostype=$options{t};
}elsif(defined($^O)){
    $ostype=$^O;
}elsif(defined($ENV{"OSTYPE"})){
    $ostype=$ENV{"OSTYPE"};
}else{
    $ostype=`uname -s`;
    if($ostype =~ m/mingw/i || $ostype=~ m/msys/i){
        debug_print("$0: mingw\n");
        $ostype="msys";
    }elsif ($ostype =~ m/cygwin/i){
        debug_print("$0: cygwin\n");
        $ostype="cygwin";
    }else{
        die "$0: unknown OS type\n";
    }
}


# get compiler from config.mak
if(!defined($compiler) or $compiler eq "")
{
    my $config = "config.mak";
    my $in;
    open CONFIG, "<", $config or die "$0: unable to open $config $!\n";
    while ($in = <CONFIG>)
    {
        chomp($in);
        if ($in =~ m/COMPILER_VERSION:?=(.*)/o)
        {
            $compiler = $1;
            last;
        }
    }
    close(CONFIG);
}

#
# Set system INC
#
my $sysinc;
if ($compiler eq "AEONGCC")
{
    $sysinc = $ENV{"AEONINC"};
}elsif ($compiler eq "MIPSGCC"){
    $sysinc = $ENV{"MIPSINC"};
}elsif ($compiler eq "X86LINUXGCC"){
    $sysinc = $ENV{"X86LINUXINC"};
}elsif ($compiler eq "ARMGCC"){
    $sysinc = $ENV{"ARMGCCINC"};
}else{
    $sysinc = $ENV{"ARMINC"};
}
$sysinc =~ s/\\/\//g;
{
    my %uniq=();
    $sysinc = join("|",
        grep {!$uniq{$_}++}  #unique the list
        split(/\s+/,
            "$sysinc @{[&fix_path($sysinc)]}")
    );
}
$sysinc=qr/$sysinc/i; #pre-compile regex pattern
debug_print("$0: sysinc=$sysinc\n");

sub fix_path{
    local $_=shift;
    debug_print("$0 fix_path entry: $_\n");

    #erase the starting ./
    s;^\.\/;;g;
    s;\s+\.\/; ;g;
    #erase the duplicate \ or / or /./
    s#\\+#\/#g;
    s#\/+#\/#g;
    s#\/\.\/#\/#g;

    if($ostype eq "msys"){
        s#(^|\s)(\w):\/#$1\/\l$2\/#g;
        s#(^|\s)\/cygdrive\/#$1\/#g;
    }elsif($ostype eq "cygwin"){
        s!(^|\s)(\w):\/!$1\/cygdrive\/\l$2\/!g;
        s!(^|\s)\/(\w)\/!$1\/cygdrive\/\l$2\/!g;
    }
    1 while(s;
        \/
        [^/]+   #folder
        \/
        \.\.    #parent dir
        \/;\/;gx);
    debug_print("$0 fix_path end: $_\n");
    return $_;
}

sub add_inc{
    for my $path(grep {!/$sysinc/} @{$_[0]}){
            $includes{$path}++;
            debug_print("$0 add_inc: add $path\n");
    }
}

# open input
if(scalar(@ARGV)<1){
    die "$0: no dep files input\n";
}

while(@ARGV>0){
    open (my $fin, "<", $ARGV[0]) or die "$0: unable to open $ARGV[0]\n";
    shift @ARGV;
    while(<$fin>){
        chomp;
        # collect #define
        if (m/^#define (.*)/o) {
            $defines{$1} += 1;
            next;
        }
        # collect #undef
        if (m/^#undef (.*)/o) {
            $undefs{$1} += 1;
            next;
        }
        # collect #include
        if (m/^#include (?:.*)/o) {
            #my $inc_file=$1;
            #next if $inc_file =~ m/$sysinc/o;
            #(my $dirname=$inc_file)=~s/\\/\//g;
            #&add_inc([&fix_path(&dirname($dirname))]);
            next;
        }

        while(s/\\$//){
            $_.=<$fin>;
        }
        s/[\n\r]//g;

        if(m#^([^:]+):(.*)$#xo){
            #single line rule
            my ($target, $prerequisite)=(&basename(&strip($1)), &strip($2));
            if(defined $depends{$target}){
                $depends{$target}[0] .= " ".$prerequisite;
            }else{
                $depends{$target}[0] = $prerequisite;
            }
        }
    }
    close($fin);
}

#read old tpp file
if(-e $options{f}){
    my (%full_path, # table to transform basename to full path
        %old_cdep,  # to store dependency chain in old format
    );
    my $old_format=1;

    if(open my $fin, "<", $options{f}){
        while(<$fin>){
            chomp;
            s$[\n\r]$$g;
            if(/^USE_DEFS =\\$/ .. /^$/){
                if(/^\s+(\w+)\\?$/){
                    $defines{$1} += 1;
                    next;
                }
            }elsif(/^USE_UNDEFS =\\$/ .. /^$/){
                if(/^\s+(\w+)\\?$/){
                    $undefs{$1} += 1;
                    next;
                }
            }elsif(m/^DEPENDS =\\$/ .. /^$/){
                if(/^\s+([^\\]+)\\?$/){
                    my $path=$1;
                    $full_path{&basename($path)}=$path;
                }
            }elsif(m/^dep_(\S+)\s:=\s(.*)/){
                my ($target, $prerequisite)=(&basename(&strip($1)), &strip($2));
                $target = &src2obj($target);
                unless(defined $depends{$target}){
                    $depends{$target}[0]=$prerequisite;
                }
                $old_format=0 if ($old_format==1);
            }elsif(/(\w+\.o):\s(.*)/){
                # to be compatible with old format
                my ($target, $prerequisite)=(&basename(&strip($1)), &strip($2));
                $old_cdep{$target}[0]=$prerequisite;
            }

        }
        close $fin;

        # if depends still empty here, rearrange and append old format dependencies
        # to be compatible with old format
        if($old_format == 1){
            for (keys %old_cdep){
                my @tmp_array=map{
                            s/^\$\(\w+\)//g;
                            if(index($_, "/") == -1 and exists $full_path{$_}){
                                $full_path{$_};
                            }else{
                                $_;
                            }
                        }split(/\s+/, $old_cdep{$_}[0]);
                unless(defined $depends{$_}){
                    $depends{$_}[0] = join(" ", @tmp_array);
                    &debug_print("from old cdep: $_-> $depends{$_}[0]\n");
                }
            }
        }
    }else{
        warn "$0: unable to open $options{f}\n";
    }
}

#read dfn file
my $dfn_file=$options{i};
if (-e $dfn_file){
    my %srcs;
    if(open my $fin, "<", $dfn_file){
        while(<$fin>){
            chomp;
            s$[\n\r]$$g;
            if(/^OBJS =/ .. /^$/){
                if(m/^\s+([^\\]+)\\?$/o){
                    $srcs{$1}++;
                }
            }
        }
        close $fin;

        delete @depends{grep {!$srcs{$_}} keys %depends};
    }else{
        warn "$0: unable to open $dfn_file\n";
    }
}

for(keys %depends){
    my @tmp = _uniq(grep {
           !m/$sysinc/
       }map{
            fix_path($_);
       }split(/\s+/, $depends{$_}[0]));

   add_inc([map{
            &dirname($_)
        }grep {
            !/\.c(?:pp)?$/ and !/\.S$/ and !/\.asm$/
        } @tmp]);

   if($_ ne &src2obj(&basename($tmp[0]))){
        for my $i(1 .. $#tmp){
            if($_ eq &src2obj(&basename($tmp[$i]))){
                @tmp[0, $i] = @tmp[$i, 0];
        last;
    }
        }
   }
   my @idx= sort {$tmp[$a] cmp $tmp[$b]} (1 .. $#tmp);
   unshift @idx, 0;
   @{$depends{$_}}= @tmp[@idx];
}

# open output
open(TPP, "> $options{f}") or die "cannot open output \"$options{f}\"\n";
printf TPP <<END, join("\\\n\t", sort keys %defines), join("\\\n\t", sort keys %undefs), join("\\\n\t", @{_sort(\%includes)}), join("\\\n\t", @{[_uniq(sort map{@{$depends{$_}}}keys(%depends))]});
USE_DEFS =\\
	%s

USE_UNDEFS =\\
	%s

INC_DIRS =\\
	%s

DEPENDS =\\
	%s

END

print TPP map{
    sprintf <<EOM, ${$depends{$_}}[0], join(" ", @{$depends{$_}}), $options{o}, $_, join(" ", map{if(m/\.c(?:pp)?$/ || m/\.S$/ || m/\.asm$/){"$options{o}@{[&basename($_)]}"}else{$_}} @{$depends{$_}});
dep_%s := %s

%s%s: %s

EOM
} sort keys(%depends);

# Add trace ID segmentation
if($options{r}){
    my $libID_begin =undef;
    my $cpp_line="\$(CPP_LINE)";
    my $regex=qr!^$target_lib=(\d+),!;

    if($options{g}){
        open(TRC_ID, "<", "tng/remtrace/remtraceID") or die "$0: cannot open file: \"remtraceID\"\n";
        while (<TRC_ID>){
            chomp;
            if (m/$regex/o){
                $libID_begin=$1;
                $cpp_line.=" -f $libID_begin";
                debug_print("$0: $target_lib.lib remtraceID start from $libID_begin\n");
                last;
            }
        }
        close TRC_ID;
    }
    warn "$0: unable to find remtraceID for $target_lib\n" unless(defined $libID_begin);

# output sources copy rules
    my @all_files=_uniq(sort map{@{$depends{$_}}} keys %depends);

    print TPP map{
        sprintf <<EOM, $options{o}, &basename($_), $_, $cpp_line;
%s%s: %s
	%s

EOM
    }grep {/\.c(?:pp)?$/} @all_files;

    print TPP map{
        sprintf <<EOM, $options{o}, &basename($_), $_;
%s%s: %s
	\$(PP_LINE)

EOM
    }grep {/\.S$/ || /\.asm$/} @all_files;

    print TPP map{
        sprintf <<EOM, basename($_), $_;
\$(DIR_MSG)%s: %s
	-\$(COPY) \$< \$@

EOM
    }grep {/_message_define__\.hi$/} @all_files;
}
close TPP;
