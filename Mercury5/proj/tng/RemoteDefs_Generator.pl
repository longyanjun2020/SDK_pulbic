#!/usr/bin/perl
use strict;
#use warnings;
use Getopt::Std;

getopts('i:o:hvf:rs');
our ($opt_i, $opt_o, $opt_h, $opt_v, $opt_r, $opt_s);

if(($opt_h) or (!$opt_i) or (!$opt_o)){
    print   <<"EOF";
Usage: $0 -i <input folder> -o <output file> [-h] [-v]
\t-i: specify the location of the c & h files, necessary!!
\t-o: specify optput file name, necessary!!
\t-h: show usage
\t-v: verbose(debug) mode, dump internal symbol tables
\t-r: skip system tasks generation and append other info, for release build
\t-s: only generate system task info to prepare release package
EOF
exit 0;
}

#opt_r = 1 to generate cust_task, mailbox, & diagnose info
#opt_s = 1 to generate sys task info
if($opt_r==0 && $opt_s==0){
    $opt_r=1;
    $opt_s=1;
}

############################
# get_make_def(FILE, VAR)
# grab VAR from FILE in makefile format and return its values in array
############################
sub get_make_def{
    (my $file, my $var)=@_;
    my @value;
    open (my $fin, "< $file") or return undef;
    while(chomp(my $line=<$fin>)){
        if($line =~ m/$var/){
            #skip the first line
            chomp($line =<$fin>);
            while($line =~ m/\\\s*$/){
                $line =~ s!\s*\\\s*$!!;
                $line =~ s!^\s*!!;
                push @value, $line;
                chomp($line =<$fin>);
            }
            $line =~ s!\s*$!!;
            $line =~ s!^\s*!!;
            push @value, $line;
            last;
        }
    }
    close($fin);
    return @value;
}

############################
# get_file_location(TPP_FILE,TARGET_FILE)
# grab TARGET_FILE file location in TPP_FILE
############################
sub get_file_location{
    (my $tpp_file, my $target_file) = @_;
    my $line;
    open (my $fin, "< $tpp_file") or return undef;
    while(chomp($line=<$fin>)){
        if($line =~ /DEPENDS/){
            do{
                chomp($line =<$fin>);
            }while($line !~ /\b$target_file\b/ && $line =~ /\\\s*$/);
            $line =~ s/^\s*//;
            $line =~ s/\\\s*$//g;
            last;
        }
    }
    close($fin);
    if($line =~ /\b$target_file\b/){
        return $line;
    }else{
        return undef;
    }
}

############################
# debug_print(STRING)
# print STRING if -v
############################
sub debug_print{
    print "@_" if($opt_v);
}

############################
# IsNumber(STRING)
# determine if STRING is a number string
############################
sub IsNumber{
    $_=shift;
    if(m/^0x[0-9a-fA-F]+[Ll]?$/){
        return 1;
    }elsif(m/^(\d+\.\d+)([Ee][+-]?\d+[Dd]?[LlFfDd]?)?$/){
        return 1;
    }elsif(m/^\d+[Ll]?$/){
        return 1;
    }
    return 0;
}

############################
# evalable(STRING)
# determine if STRING can be evalulated
############################
sub evalable{
    my $string=shift;
    &debug_print("in evalable, string='$string'\n");
    if($string =~ m/\d+\s*[\+\-\*\/]\s*\d+/){
        return 1;
    }
    return 0;
}

############################
# MacroExpander(TABLE_REF)
# iterative parsing TABLE_REF content
############################
sub MacroExpander{
    my $table=shift;
    my %simple_macros;
    my %eval_macros;
    for my $macro_name(keys(%$table)){
        if($$table{$macro_name} =~ m/^(0x[0-9a-fA-F]+)[Ll]?$/ ){
            $simple_macros{$macro_name}=hex($1);
            &debug_print("##simple:hex $macro_name -> $simple_macros{$macro_name}\n");
        }elsif($$table{$macro_name} =~ m/^(\d+)[Ll]{0,2}$/){
            $simple_macros{$macro_name}=$1;
            &debug_print("##simple:decimal $macro_name -> $simple_macros{$macro_name}\n");
        }elsif($$table{$macro_name} =~ m/^((\d+\.)?\d+)(([Ee][+-]?\d+)[Dd]?[LlFfDd]?)?$/){
            $simple_macros{$macro_name}="$1$4";
            &debug_print ("##simple:floating point : $macro_name -> $simple_macros{$macro_name}\n");
        }elsif($$table{$macro_name} =~ m/^([_a-zA-Z]\w*)$/){
            $eval_macros{$macro_name}=$1;
            while(exists $eval_macros{$eval_macros{$macro_name}}){
                $eval_macros{$macro_name}=$eval_macros{$eval_macros{$macro_name}};
            }
            &debug_print ("##eval:word: $macro_name -> $eval_macros{$macro_name}\n");
        }else{
            if($$table{$macro_name} =~ m/[^\=\?\:\.\+\-\*\/\%\w\s\(\)\{\}]/){
                &debug_print ("##skip: '$$table{$macro_name}'\n");
                next;
            }
            $eval_macros{$macro_name}=$$table{$macro_name};
            my $string_to_be_split = $$table{$macro_name};
            $string_to_be_split =~ s/^\W*//g;
            my @tokens=split /[\b|\W]+/, $string_to_be_split;
            &debug_print ("##eval:token $macro_name -> $$table{$macro_name} ->".join(':', @tokens));
            for(@tokens){
                if(exists $simple_macros{$_}){
                    $eval_macros{$macro_name} =~ s;\b$_\b;$simple_macros{$_};g;
                }elsif(exists $eval_macros{$_}){
                    $eval_macros{$macro_name} =~ s;\b$_\b;$eval_macros{$_};g;
                }
            }
            &debug_print (" -> $eval_macros{$macro_name}\n");
        }
    }

    while(keys(%eval_macros)!=0){
        #while still uneval macros in eval_macros table
        for my $macro_name(keys %eval_macros){
            my $string_to_be_split = $eval_macros{$macro_name};
            $string_to_be_split =~ s/^\W*//g;
            my @tokens=split /[\b|\W]+/, $string_to_be_split;
            #&debug_print ("haha_tokens = ".join(';',@tokens));
            &debug_print (" original=$eval_macros{$macro_name}\n");
            for my $token (@tokens){
                if(&IsNumber($token)==1){
                    &debug_print("[1] number $token\n");
                    if($token =~ m/^(0x[0-9a-fA-F]+)[Ll]?$/){
                        my $dec_value=hex($token);
                        $eval_macros{$macro_name} =~ s;\b$token\b;$dec_value;g;
                    }
                    next;
                }elsif(exists($simple_macros{$token})){
                    &debug_print ("[2] before simple sub: $eval_macros{$macro_name}, $token, $simple_macros{$token}\n");
                    $eval_macros{$macro_name} =~ s;\b$token\b;$simple_macros{$token};g;
                }elsif(exists($eval_macros{$token})){
                    &debug_print ("[3] $token -> $eval_macros{$token}\n");
                    my $name=$token;
                    my $value=$eval_macros{$name};
                    &debug_print ("before loop:  $eval_macros{$macro_name}, $name, $value\n");
                    while((exists $simple_macros{$value}) or (exists $eval_macros{$value})){
                        if(exists $simple_macros{$value}){
                            &debug_print ("[3-1]del eval_macros: $name-> '$eval_macros{$value}' '$eval_macros{$name}' ");
                            delete $eval_macros{$value};
                            delete $eval_macros{$name};
                            $value=$simple_macros{$value};
                            $simple_macros{$name}=$value;
                            &debug_print ("to simple_macros $name -> $simple_macros{$name}\n");
                            last;
                        }else{
                            &debug_print ("[3-2]\n");
                            $value=$eval_macros{$value};
                            $eval_macros{$name}=$value;
                        }
                    }
                    &debug_print ("before sub: $eval_macros{$macro_name}, $name, $value\n");
                    $eval_macros{$macro_name} =~ s;\b$name\b;$value;g;
                }else{
                    &debug_print ("[4]del eval_macros: $macro_name -> $eval_macros{$macro_name}, token='$token'\n");
                    delete $eval_macros{$macro_name};
                    last;
                }
            }
            &debug_print ("after loop $eval_macros{$macro_name}\n");
            if($eval_macros{$macro_name} =~ m/^[\(\)\d\.\+\-\*\/\%\s]+$/){
                &debug_print ("eval it!! $macro_name -> $eval_macros{$macro_name} ");
                $simple_macros{$macro_name}=eval "$eval_macros{$macro_name}";
                &debug_print ("-> $simple_macros{$macro_name}\n");
                delete $eval_macros{$macro_name};
            }else{
                &debug_print ("unable to eval: $macro_name -> $eval_macros{$macro_name}\n");
            }
        }
    }
    %$table=%simple_macros;
}

my $RemoteDefs_file=$opt_o;
my $task_file="$opt_i/init.c.pp";
my $cust_task_id_file="$opt_i/sys_rtk_config.h.pp";
my $cust_task_file="sc/application/cus_app/sc/src/cus_app.c";
my $mbox_file="$opt_i/osdefs.hc.pp";
my $diagnose_file="$opt_i/sys_vm_dbg.ho.pp";

my $fin;
my $fout;
my %task;
my $parsing=0;
my $task_id=0;
my $index=0;

#my $compiler;

# sys Task Parsing
if($opt_s){
    #grab init.c location from sys.tpp or use fixed location
    if(!-e $task_file){
        warn "$0: $task_file not found, unable to determine system task ID and skip it\n";
    }else{
        #($compiler = "gcc -E $ENV{DFLAGS} $ENV{IFLAGS} ") =~ s#\\#\/#g;
        #&debug_print("task preprocess command=$compiler $task_file\n");
        open($fin, "<", $task_file) || die "$0: unable to open $task_file for Task name input\n";
        while(<$fin>){
            if(m!const\s+cus_InitTask_t\s+cus_InitTask\s*\[\]\s*=!o .. m!};!o){
                if(m!\{\s*\"(.*)\"!o){
                    $task{$task_id}=$1;
                    $task_id++;
                }
            }
        }
        close($fin);
    }
    $parsing=0;
    open($fout, ">", $RemoteDefs_file) || die "$0: unable to open $RemoteDefs_file\n";
    print $fout <<"EOF";
; ###############################################################################
;							T A S K S
; ###############################################################################
EOF

}
if($opt_r){
    #grab sys_rtk_config.h location from rtk.tpp or use predefined location
    #if(!defined($cust_task_id_file=&get_file_location("$opt_i/rtk.tpp","sys_rtk_config.h"))){
    #    $cust_task_id_file="sc/system/rtk/pub/sys_rtk_config.h";
    #    die "$0: $cust_task_id_file is not found!!\n" if(! -e $cust_task_id_file);
    #}
    if(!defined($cust_task_file=&get_file_location("$opt_i/cus_app.tpp", "cus_app.c"))){
        $cust_task_file="sc/application/cus_app/sc/src/cus_app.c";
        die "$0: $cust_task_file is not found!!\n" if(! -e $cust_task_file);
    }
    #if(!defined($mbox_file=&get_file_location("$opt_i/sys.tpp", "osdefs.hc"))){
    #    $mbox_file="sc/system/fc/com/osdefs.hc";
    #    die "$0: $mbox_file is not found!!\n" if(! -e $mbox_file);
    #}
    #if(!defined($diagnose_file=&get_file_location("$opt_i/trc.tpp","sys_vm_dbg.ho"))){
    #    $diagnose_file="sc/system/trc/pub/sys_vm_dbg.ho";
    #    die "$0: $diagnose_file is not found!!\n" if(! -e $diagnose_file);
    #}
    # Cust Task Parsing
    # get first customer task id
    #$compiler="cpp -dM -E $ENV{DFLAGS} ".join(" ", map{"-I$_";} &get_make_def("$opt_i/rtk.tpp", "INC_DIRS"));
    #$compiler="cpp -dM -E $ENV{DFLAGS} $ENV{IFLAGS} ";
    #&debug_print("cus_task preprocess command=$compiler $cust_task_id_file\n");
    die "$0: $cust_task_id_file no exist\n" if(!-e $cust_task_id_file);
    open($fin, "<", $cust_task_id_file) || die "$0: unable to open $cust_task_id_file\n";
    while(<$fin>){
        if(m/^\s*#define\s+RTK_MAX_SYSTEM_TASKS\s+(\d+)\s*$/o){
            $task_id=$1;
            &debug_print("update task_id=$task_id\n");
            last;
        }
    }
    close($fin);

    if(!$opt_s && -e $RemoteDefs_file){
        #only generate cus_app, mbox, diagnose info
        #restore index from previous index
        open($fin,"sed -n '\/\\\[Task[0-9]*\\\]\/{N;N;s/\\n//g;\/Id = $task_id\$\/q;p}' $RemoteDefs_file |");
        my @lines = reverse <$fin>;
        for my $line(@lines){
            if($line =~ m;\[Task(\d+)\].*Id = (\d+)$;){
                if($task_id == $2){
                    $index=$1;
                }else{
                    $index=$1+1;
                }
                &debug_print("update index to $index\n");
                last;
            }
        }
        system("sed -i '\/^\$\/{N;\/\\\[Task$index\\\]\/{s/.*//;q}}' $RemoteDefs_file");
        close($fin);
    }

    # starting parsing cust task names
    die "$0: $cust_task_file not exist\n" if(!-e $cust_task_file);
    open($fin, "<", $cust_task_file) || die "$0: unable to open $cust_task_file\n";
    while(<$fin>){
        s/\/\*.*\*\///g;
        s/\/\/.*//g;
        if(m/vm_apmOneTask_t\s+\w+Tasks\s*\[.*\]\s*=/o .. m/};/o){
            if(m/\"(.*)\"\s*\},?/o){
                $task{$task_id}=$1;
                $task_id++;
            }
        }
    }
    close($fin);
    $parsing=0;

    # Task ID output
    open($fout, ">> $RemoteDefs_file") || die "$0: unable to open $RemoteDefs_file\n";
}

map{
    print $fout "[Task$index]\nName = \"$task{$_}\"\nId = $_\n\n";
    $index++;
} sort {$a <=> $b} keys(%task);
die "$0: No task ID output!!\n" if ($index==0);

if($opt_s and !$opt_r){
    #only generate sys task info
    #stop here!
    close($fout);
    exit(0);
}

# ========================================= Mailbox ==============================================
# Mailbox Parsing
my %mailbox;
#&debug_print("mbox preprocess cmd=$compiler $mbox_file\n");
die "$0: $mbox_file not exist\n" if (!-e $mbox_file);
open($fin, "<", $mbox_file) || die "$0: unable to open $mbox_file\n";
while(<$fin>){
    chomp;
    s/[\r\n]//g;
    s/\s+$//g;
    if(m/^\s*#define\s+(\S+)\s+(.*)$/o){
        $mailbox{$1}=$2;
    }
}
close($fin);

&MacroExpander(\%mailbox);

# Mailbox output
print $fout <<"EOF";
; ###############################################################################
;							M A I L B O X E S
; ###############################################################################
EOF

$index=0;
map{
    my $mbox_name=$_;
    if($mbox_name =~ m/^VM_MBX_CUS(\d+)$/o){
        $mbox_name=(exists $task{$mailbox{$mbox_name}})?$task{$mailbox{$mbox_name}}:"EMPTY";
    }
    $mbox_name =~ s#VM_MBX_##g;
    print $fout "[MailBoxe$index]\nName = \"$mbox_name\"\nId = $mailbox{$_}\n\n";
    $index++;
}sort {$mailbox{$a} <=> $mailbox{$b}} grep{
    m/^VM_MBX_/o && !m$UNSUBSCRIB$o;
    #only grab macros started with VM_MBX_
}keys(%mailbox);

die "$0: No mailbox ID output!!\n" if ($index==0);

#diagnose Parsing
my %diagnose;
my @diagnose;
#$compiler="cpp -dM -E $ENV{DFLAGS} ".join(" ", map{"-I$_";} &get_make_def("$opt_i/trc.tpp", "INC_DIRS"));
#&debug_print("diagnose preprocess cmd=$compiler $diagnose_file\n");
die "$0: $diagnose_file not exist\n" if (!-e $diagnose_file);
open($fin, "<", $diagnose_file) || die "$0: unable to open $diagnose_file\n";
while(<$fin>){
    chomp;
    s/[\n\r]//g;
    s/\s+$//g;
    s#\((u16|u32)\)##g;
    if(m/^\s*#define\s+\w+\(.*$/o){
        #function macros, skip it!!
        next;
    }elsif(m/^\s*#define\s+(\w+)\s+SET_IDENT\s*\(\s*(.*)\)\s*$/o){
        $diagnose{$1}=$2;
        push @diagnose, $1;
        # only macro definitions with SET_IDENT will be identified as diagnose
    }elsif(m/^\s*#define\s+(\w+)\s+(.*)$/o){
        $diagnose{$1}=$2;
    }
}
close($fin);

&MacroExpander(\%diagnose);

# diagnose result output
print $fout <<"EOF";
; ###############################################################################
;							D I A G N O S E
; ###############################################################################
EOF
$index=0;
map{
    my $name=$_;
    s#^_##g;
    print $fout "[Diagnose$index]\nName = $_\nId = $diagnose{$name}\n\n";
    $index++;
}sort {$diagnose{$a} <=> $diagnose{$b}} @diagnose;
die "$0: No diagnose ID output!!\n" if ($index==0);
close($fout);
# output to RemoteDefs.ini end
