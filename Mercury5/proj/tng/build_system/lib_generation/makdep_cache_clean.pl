#!/usr/bin/perl -s
use strict;
use warnings;
use File::Find;
use File::stat;
use vars qw($d $h $v $l);

# clean dependency cache
#  delete order files until the cache size is under limit

if(defined($h) || !defined($d) || ! -d $d){
    print <<END;
Usage: $0 -d FOLDER -p MAKDEP_PATH -o CDEP_FILE -d DEP_CACHE [-h]
\t-d=CACHE_PATH: folder name of dependency cache
\t-h: show this usage
\t-l=LIMIT: limit size(in bytes), if not specified, will only show files in cache
\t          LIMIT can be suffixed with k/K/m/M, ex: -l=10M means 10MB
\t-v: verbose
END
    exit 0;
}

my (%files, @list, %dirs);

# fix the limit value if they are terminated by m/M/k/K
if(defined $l){
    if($l !~ m/^\d+[mMkK]?$/){
        die "Limit $l isn't a size\n";
    }
    if($l =~ s/m$//i){
        $l=scalar($l)*(2**20);
    }elsif($l =~ s/k$//i){
        $l=scalar($l)*(2**10);
    }else{
        $l=scalar($l);
    }
}

# find all .dep files in dependency cache
&find(sub {
    if($File::Find::name =~ m/\.dep$/){
        push @list, $File::Find::name;
        $dirs{$File::Find::dir}++;
    }
}, ($d));

for(@list){
    # record the size and the modification time of the files in dependency cache
    ($files{$_}{size}, $files{$_}{mtime}) = @{stat($_)}[7,9];
}

print "="x130, "\n";
printf "%-100s%-15s%-15s\n", "Filename", "Size(bytes)", "Mtime"; 
print "="x130, "\n";

my($total_size, @deleted);

# calculate total size
for(sort {
            $files{$b}{mtime} <=> $files{$a}{mtime} or  # 1st criteria: modification time, from new to old
            $a cmp $b                                   # if 1st certeria equal, sort by 2nd criteria: file path
        }keys %files){
    printf "%-100s%-15d%-15d\n", $_, $files{$_}{size}, $files{$_}{mtime}; 
    $total_size += $files{$_}{size};
    if(defined $l){
        if($total_size > $l){
            push @deleted, $_;
            # delete older file if the limit is reached
            unlink $_;
        }
    }
}

for(keys %dirs){
# remove empty folders, rmdir will only succeed if folder is empty
    rmdir or next;
}

print "="x130, "\n";
if(defined $l){
    printf "%-100s%-15d\n", "Total", $total_size;
    printf "%-100s%-15d\n", "Limit", $l;
    print "="x130, "\n", "Files deleted:\n";
    for(@deleted){
        print "$_\n";
    }
}else{
    printf "%-100s%-15d\n", "Total", $total_size;
}
print "="x130, "\n";
