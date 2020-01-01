#!/usr/bin/perl

use File::Basename;

$LINT_DIR        = "c:/lint";
$SDE_DIR         = GetSdeRootPath();
$SDE_INCLUDE     = "$SDE_DIR/sde/include";
$LINT_VDEC       = $ENV{'LINT_VDEC'} || FALSE;
#$LINT_EN         = $ENV{'LINT_EN'} || TRUE;
$LINT_EN         = TRUE;
$lintExe         = $LINT_DIR."/lint-nt";


@fixIncludeDir = ("-i".$LINT_DIR,
		  "-i".$SDE_INCLUDE."/machine",
		  "-i".$SDE_INCLUDE);

($cmpListFile, $cmpcmd) = @ARGV;

$LintOutputDir = dirname $cmpListFile;
$LintTmpFile   = $LintOutputDir."/tmp";

if (!-e $LintOutputDir)
{
    mkdir $LintOutputDir;
}

open  COMPILE_CMD_LIST, ">>$cmpListFile" or die "can't opne $cmpListFile\n";
print COMPILE_CMD_LIST "$cmpcmd\n\n";
close COMPILE_CMD_LIST;

if($LINT_EN eq 'TRUE')
{
    system("rm -f $LintTmpFile");
    @cmd = split /\s/, $cmpcmd;
    
    @exe = Compile2Lint(@cmd);

#    To dump PC Lint command
#    foreach(@exe) {
#        print $_;
#        printf(" ");
#    }
#    printf("\n");
    $result = FilterLintResult(@exe);
    
    system("rm -f $LintTmpFile");
    if($result)
    {
	die "Lint error occured.\n";
    }
}



sub FilterLintResult {
    
    my @exe = @_;
    my $stop = 0;
    
    
    
    @mustFix =('Warning 650',
	       'Warning 648',
	       'Warning 644',
	       'Warning 578',
	       'Warning 548',
	       'Warning 545',
	       'Warning 530',
	       'Warning 509',
	       'Warning 420',
	       'Warning 419',
	       'Warning 520',
	       'Warning 605',
# new
	       'Warning 645',
	       'Warning 669',
#	       'Warning 428',
	       'Warning 501',
#	       'Warning 522',
	       'Warning 533',
	       'Warning 564',
	       'Warning 652',
	       'Warning 688',
	       'Warning 524',
	       'Warning 659',
	       'Warning 416',
	       'Warning 415',
	       'Warning 618',
	       
	       );
    
    if(!@exe)
    {
	return 0;
    }
    


    system("@exe > $LintTmpFile");
    open LINT_CMD, "$LintTmpFile" or die "can't open $LintTmpFile\n";
    
    while(<LINT_CMD>)
    {
	$str = $_;
	
	($src, $err, $msg) = split /:\s/, $str;
	($src, undef) = split /:[0-9]/, $src; 
	
	foreach $cmp (@mustFix) {
	    if($err =~ /$cmp/){
		$stop = 1;
		Cnvt2CygPath($str);
		print $str;
	    }
	}

	if($err =~ /Error /){
	    $stop = 1;
	    Cnvt2CygPath($str);
	    print $str;
	}
    }

    close LINT_CMD;
    return $stop;
}

sub Compile2Lint {
    
    my $src = undef;
    my @include = undef;
    my @define = undef;
    my @exe = undef;
    my @cmd = @_;
    
    @FilterOutECOSFiles =('var_misc.c',
			  'ser16c550a.c',
			  'hal_if.c',
			  'rbtree.c',
			  'drvcr.c',
			  'aacd_mdct.c',
			  '../src/utils/os_none.c',
			  "language/c/libm",
			  "sde/include/mips/cpu.h"); 
    
    foreach (@cmd) {
	if(/\.(c|cpp|cxx)$/i){
	    $src = $_;
	}
	
	if(/^-I/){
	    s/^-I/-i/;
	    push (@include, $_);
	}
	
	if(/^-D/){
	    s/^-D/-d/;
	    push (@define, $_);
	}
    }


    if($src)
    {
	
	$cyg_src=$src;
	Cnvt2CygPath($cyg_src);
	
	foreach $name (@FilterOutECOSFiles) {
	    
	    if($cyg_src =~ m<$name>){
		return ;
	    }
	}
	
	push(@include, @fixIncludeDir);
	
	@exe=($lintExe, @include, @define,"std.lnt", $src);
	
	foreach (@exe) {	
	    s/\/cygdrive\/(\w)/$1:/gi;  # replace /cygdrive/d/ to d:/
	    s/-I/-i/g;
	    s/\/vdecplayer\//\/mp4player\//g;
	    s/\/vdec2\//\/vdec\//g;
	    s/\/vdecrvc\//\/vdec\//g;
	}

	if($src =~ /\/vdec2/ || $src =~ /\/vdecrvc/ || $src =~ /\/vdec\//)
	{
	    if($LINT_VDEC ne 'TRUE')
	    {
		return ;
	    }
	}
	
	return @exe;
    }

    return ;
    
}

sub Cnvt2CygPath {
    
    foreach (@_) {
	s/\\/\//g; #repleace "\" to "/" 
	s/(\w):\//\/cygdrive\/$1\//gi;  # replace d: to /cygdrive/d
    }
    return @_;
}

sub Cnvt2DosPath {
    
    foreach (@_) {
	s/\/cygdrive\/(\w)/$1:/gi;  # replace /cygdrive/d/ to d:/
	#s/\//\\/g; #repleace "/" to "\" 
    }
    return @_;
}

sub GetSdeRootPath {
    chomp($_ = `which sde-gcc`);
    s/\/bin\/sde-gcc//g;
    Cnvt2DosPath($_);
    return $_;
}
