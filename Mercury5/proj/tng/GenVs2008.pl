#!/usr/bin/perl

die "GenVs2008 v0.1\nUsage: GenVs2008\n" if @ARGV != 0;

my @AppVerifierProj = ("App_mmi", "MStarSimulator");
my @NoAppVerifierProj = ("App_mdl1","App_mdl2","MKDev_bat","MKDev_e2p","MKDev_RPC","MKDev_sim","MKDev_SMG","MKDEV_V24","Msim_NetWork","MSSimConsole","XSysMain");

sub gen
{
	my $file = shift;
  my $vs2008File = $file;
  $vs2008File =~ s/\.vcproj/_2008\.vcproj/;
    
  my $addAppVerifier = 0;

	open(SOURCES, "< $file") or die "cannot open source \"$file\"\n";
	
	for my $item (@AppVerifierProj)
	{
		if ($file =~ /$item/)
		{
			$addAppVerifier = 1;
		}
	}
	
	for my $item (@NoAppVerifierProj)
	{
		if ($file =~ /$item/)
		{
			$addAppVerifier = 2;
		}
	}
	
	unlink $vs2008File;
	open(OUTPUT, "> $vs2008File") or die "cannot open output \"$vs2008File\"\n";

	while(my $line = <SOURCES>)
	{
		print OUTPUT "$line";
		if ($line =~ /VCAppVerifierTool/)
		{
			if (1 == $addAppVerifier)
			{
				print OUTPUT "				HeapVerification=\"1\"\n";
				print OUTPUT "				HandleVerification=\"0\"\n";
				print OUTPUT "				LocksVerification=\"0\"\n";
			}
			if (2 == $addAppVerifier)
			{
				print OUTPUT "				HeapVerification=\"0\"\n";
				print OUTPUT "				HandleVerification=\"0\"\n";
				print OUTPUT "				LocksVerification=\"0\"\n";
			}
		}
  }
  close(OUTPUT);
}

sub genSln
{
	my $file = shift;
    my $vs2008File = $file;
    $vs2008File =~ s/\.sln/_2008\.sln/;
    
	open(SOURCES, "< $file") or die "cannot open source \"$file\"\n";
	unlink $vs2008File;
	open(OUTPUT, "> $vs2008File") or die "cannot open output \"$vs2008File\"\n";
	#print "open $file\n";
	while(my $line = <SOURCES>)
	{
		$line =~ s/\.vcproj/_2008\.vcproj/;
		print OUTPUT "$line";
  }
  close(OUTPUT);
}

sub find
{
	my $pathname = shift;
	my @projFiles = <*.vcproj>;
	my @slnFiles = <*.sln>;
	
	if($#projFiles >= 0)
	{
		for my $item (@projFiles)
		{
		    if ($item !~ /_2008/)
		    {
	            gen($item);
	        }
	    }
	}
	if($#slnFiles >= 0)
	{
		for my $item (@slnFiles)
		{
		    if ($item !~ /_2008/)
		    {
	            genSln($item);
	        }
	    }
	}
	
	my @dir = <*>;
	for my $path (@dir)
	{
		if (-d $path)
		{
			chdir $path;
			print "find $pathname/$path\n";
			find("$pathname/$path");
			chdir "../";
		}
	}
}

chdir "MStarStudio_UP";
find("");
chdir "../";
