#!/usr/bin/perl

use warnings;
use strict;
use Fcntl;

my $log = shift;

# duplicate stdout
open USEROUT, ">&STDOUT" or die "cannot duplicate stdout\n";
# indicate USEROUT descriptor number to trace.pl
$ENV{"USEROUT"} = fileno(USEROUT);
# prevent close-on-exec for USEROUT
fcntl(USEROUT, F_SETFD,0) or die "$0: fcntl not supported\n";

# redirect sdtout and stderr to "log"
if($^O eq "msys"){
    open STDOUT, "|-", "cat > $log" or die "cannot redirect stdout to \"", $log, "\"\n";
}else{
    open STDOUT, "> $log" or die "cannot redirect stdout to \"", $log, "\"\n";
}
open STDERR, ">&STDOUT" or die "cannot redirect stderr to stdout\n";

# exec command line
my $arg = "@ARGV";
exec($arg);
