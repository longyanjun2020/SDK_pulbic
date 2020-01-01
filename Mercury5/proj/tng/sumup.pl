#!/usr/bin/perl

my $tag = "<TNG>";
my $log = shift;
my $msg;

open LOG, "< $log" or die "cannot open \"$log\"\n";

while(<LOG>)
{
	if (s/^$tag//) {
		$msg = "";
	}
	$msg .= $_;
}

$NORMAL="\e[0m";
$RED="\e[31m";
$BLUE="\e[1m\e[34m ";

print "last message:\n$RED$msg$NORMAL\n";

#-------------------------------------------------------------
# lib generation error code begin
#-------------------------------------------------------------
if ($msg =~ m/cannot find source of/i){
	print "$BLUE Error Code:  0x201 $NORMAL\n";
}
elsif ($msg =~ m/lib.mak:44: \/.*.mak: No such file or directory/i){
	print "$BLUE Error Code:  0x202 $NORMAL\n";
}
elsif ($msg =~ m/\*\*\* No rule to make target \`\/src\', needed by \`build\/.*\/out\/.*.lst/i){
	print "$BLUE Error Code:  0x203 $NORMAL\n";
}
elsif ($msg =~ m/\*\*\* No rule to make target \`\/inc\', needed by \`build\/.*\/out\/.*.lst/i){
	print "$BLUE Error Code:  0x203 $NORMAL\n";
}
elsif ($msg =~ m/Error: C3397E/i){
	print "$BLUE Error Code:  0x204 $NORMAL\n";
}
elsif ($msg =~ m/Too many -I flags/i){
	print "$BLUE Error Code:  0x205 $NORMAL\n";
}
#-------------------------------------------------------------
# install error code begin
#-------------------------------------------------------------
elsif ($msg =~ m/\*\*\* No rule to make target \`build\/.*\/out\/.*.lib\', needed by \`install\'.  Stop/i){
	print "$BLUE Error Code:  0x301 $NORMAL\n";
}
#-------------------------------------------------------------
# lib generation, install  error code end
#-------------------------------------------------------------



#-------------------------------------------------------------
# E2P error code begin
#-------------------------------------------------------------
if ($msg =~ m/\[E2P ERROR\] PADDING/i){
	print "$BLUE Error Code:  0x0101 $NORMAL\n";
}

if ($msg =~ m/\[E2P ERROR\] Overlap/i){
	print "$BLUE Error Code:  0x0102 $NORMAL\n";
}

if (($msg =~ m/File "E2pBlender.py", line 140, in <module>/i) && ($msg =~ m/File "E2pBlender.py", line 84, in find/i)){
	print "$BLUE Error Code:  0x0103 $NORMAL\n";
}

if (($msg =~ m/No rule to make target `.*\.e2p\.val'/i) || ($msg =~ m/No rule to make target `.*\.e2p'/i)){
	print "$BLUE Error Code:  0x0104 $NORMAL\n";
}

if ($msg =~ m/gene2p : Version v1a23 Copyright \(c\) WAVECOM/i){
	print "$BLUE Error Code:  0x0105 $NORMAL\n";
}
#-------------------------------------------------------------
#E2P error code end
#-------------------------------------------------------------


#-------------------------------------------------------------
# remtrace error code begin
#-------------------------------------------------------------
if (($msg =~ m/\[remtrace ERROR\] cannot find lib \"/i) && ($msg =~ m/\" in tng\/remtrace\/remtraceID/i)){
	print "$BLUE Error Code:  0x0001 $NORMAL\n";
}

if (($msg =~ m/\[remtrace ERROR\]/i) && ($msg =~ m/ libID_end:/i) && ($msg =~ m/ \<\= libMaxID:/i)){
	print "$BLUE Error Code:  0x0002 $NORMAL\n";
}

if (($msg =~ m/\[remtrace ERROR\] The trace ID range of target \"/i) && ($msg =~ m/\" overlap with target \"/i)){
	print "$BLUE Error Code:  0x0003 $NORMAL\n";
}
#-------------------------------------------------------------
# remtrace error code end
#-------------------------------------------------------------


#-------------------------------------------------------------
# dlchk  error code begin
#-------------------------------------------------------------
if ($msg =~ m/of them are critical/i){
	print "$BLUE Error Code:  601 $NORMAL\n";
}
#-------------------------------------------------------------
#  dlchk  error code end
#-------------------------------------------------------------

#-------------------------------------------------------------
# drv_pre_process  error code begin
#-------------------------------------------------------------
if ($msg =~ m/Err: Please ensure .dat and .txt indicated above are existed and not read-only/i){
	print "$BLUE Error Code:  0x0401 $NORMAL\n";
}
#-------------------------------------------------------------
#  drv_pre_process  error code end
#-------------------------------------------------------------
