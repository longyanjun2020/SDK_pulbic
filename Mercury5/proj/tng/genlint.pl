#!/usr/bin/perl

#use warnings;
use strict;
use Fcntl;
use File::Basename;

my $os = `uname`;
if ($os =~ m/Linux/i) {
	$os = "linux";
}
elsif ($os =~ m/Cygwin/i) {
	$os = "cygwin";
}
elsif ($os =~ m/Windows/i) {
	$os = "Win32";
}elsif($os =~ m/(?:msys|mingw)/i){
	$os = "msys";
}else {
	die "unknown system";
}

sub trim($)
{
	my $string = shift;
	$string =~ s/^\s+//;
	$string =~ s/\s+$//;
	return $string;
}

# Left trim function to remove leading whitespace
sub ltrim($)
{
	my $string = shift;
	$string =~ s/^\s+//;
	return $string;
}

# Right trim function to remove trailing whitespace
sub rtrim($)
{
	my $string = shift;
	$string =~ s/\s+$//;
	return $string;
}

my $LINT_DIR = "c:\\lint";
my $LINTPATH="";
if ($os eq "Win32" )
{
$LINTPATH = "c:\\lint\\lint-nt.exe";
}
elsif($os eq "msys")
{
$LINTPATH = "/c/lint/lint-nt.exe";
}elsif($os eq "cygwin"){
$LINTPATH = "/cygdrive/c/lint/lint-nt.exe";
}

my $LINTLNTLOG_DIR = "LINTLOG";

my $logfile = "lintgen.log";
my $lintDefineFile = "LINTDEFINE.lnt";
my $lintSourceFile = "LINTSOURCE.lnt";
my $LINTOPTION = "target.lnt $lintDefineFile $lintSourceFile  ";
my $mode = shift(@ARGV);
my $outdir = shift(@ARGV);
my $outTarget = shift(@ARGV);
my $LINTLNTLOG_SRC_DIR = "$LINTLNTLOG_DIR/$outTarget";
my $strOutLogPath;	
my $outLintLog = "$outTarget.lnt.log";

#create lint log folder
mkdir $LINTLNTLOG_DIR,0755;
$outLintLog = "./LintLog/$outLintLog";
$strOutLogPath = "./$LINTLNTLOG_SRC_DIR/$outTarget.total.log";

open(H_LOGFILE, ">> $logfile") or die "cannot read \"$logfile\" file\n";


print H_LOGFILE "\n****LINTPATH=$LINTPATH LINTOPTION=$LINTOPTION ****\n";
print H_LOGFILE "****Mode=$mode  OurDir=$outdir outLintLog=$outLintLog****\n";

if ( "LINTDEFINE" eq $mode )
{
	# generate lint definition file
	print H_LOGFILE "==>Generate LINTDEFINE.lnt\n";
	open(H_DEFINEFILE, ">> $lintDefineFile") or die "cannot read \"$lintDefineFile\" file\n";
	my $varXX = "";
	print H_DEFINEFILE "-D__arm\n";		
	foreach $varXX (@ARGV)
	{
		$varXX = trim($varXX);
		if((($varXX =~ m/__VER_INFO_CUS__/o) or
		    ($varXX =~ m/__VER_INFO__/o) or
		    ($varXX=~m/__FUNCTION__/o)) and ($varXX !~ m/=\".*\"/o)){
		    $varXX =~ s!=(\S+)!=\"\1\"!g;
		}
		if ($varXX =~ /^-d/i)
		{
		    print H_DEFINEFILE "$varXX\n";	
		}
		else
		{		
		    print H_DEFINEFILE "-D$varXX\n";	
		}
	}
	close(H_DEFINEFILE);
}
elsif ( "LINTINCLUDE" eq $mode  )
{
	# generate lint definition file
	print H_LOGFILE "==>Generate LINTDEFINE.lnt\n";
	open(H_DEFINEFILE, ">> $lintDefineFile") or die "cannot read \"$lintDefineFile\" file\n";
	my $varXX = "";
	foreach $varXX (@ARGV)
	{
		print H_DEFINEFILE "-i\"$varXX\"\n";	
	}
    #print H_DEFINEFILE "-i\"$outdir\"\n";	
	close(H_DEFINEFILE);
}
elsif ( "LINTSOURCE" eq $mode)
{
	# generate lint source and launch lint.
	
	mkdir $LINTLNTLOG_SRC_DIR,0755;
	
	print H_LOGFILE "==>Generate LINTSOURCE.lnt  tarDir=$LINTLNTLOG_SRC_DIR\n";
	
	my $varXX = "";
	my $varFilename = "";
	open(H_DEFINEFILE, ">> $strOutLogPath") or die "cannot write \"$strOutLogPath\" file\n";
	foreach $varXX (@ARGV)
	{
		$varFilename = basename $varXX;
		$outLintLog = "./$LINTLNTLOG_SRC_DIR/$varFilename.log";
		$LINTOPTION = " target.lnt $lintDefineFile $varXX ";
		
		my $lintcmd = $LINTPATH ."  -i\".\\tng\"  $LINTOPTION > $outLintLog";	
		if ($os eq "Win32" )
		{
			print STDERR "===Src:$varFilename Log:$outLintLog===\n";
		}		
		print H_LOGFILE "==>Run Lint Cmd=$lintcmd\n";
		system  $lintcmd;
		
		#merge log
		my $strreadline;
		open(H_LINTLOGFILE, "< $outLintLog") or die "cannot read \"$outLintLog\" file\n";
		while(defined($strreadline = <H_LINTLOGFILE>))
		{
			print H_DEFINEFILE "$strreadline\n";	
		}
		close(H_LINTLOGFILE);
	}
	close(H_DEFINEFILE);
	

}
elsif ( "LINTCLEAN" eq $mode  )
{
	unlink $strOutLogPath;
	print H_LOGFILE "==>Delete  $strOutLogPath\n";
	unlink $lintSourceFile;
	print H_LOGFILE "==>Delete  $lintSourceFile\n";
	unlink $lintDefineFile;
	print H_LOGFILE "==>Delete  $lintDefineFile\n";
}
else
{

}

close(H_LOGFILE);
