#!/usr/bin/perl

use File::Copy;
#use File::Find;

#$Product = &ReadProduct;
#$dir = "build\\".$Product."\\out\\";

#print( "Start to e2p overwrite $ARGV[0], $ARGV[1]\n" );
#find(\&print_name_if_dir, $dir);

#sub print_name_if_dir
#{
#    my $file = $_;
#    
#    if ($file =~ /\.e2p$/)
#    {
#    	print $file,"\n";
#    }
#}
foreach $arg (@ARGV)
{
#	print "show ", $arg, "\n";
	my @e2pCongi = split(/:/, $arg);
	my ($e2pdata, $e2pvalue) = split(/=/, $e2pCongi[1]);	
	print "E2p Overwrite ", $e2pCongi[0], " ", $e2pdata," ",$e2pvalue, "\n";
	unless($e2pCongi[0] =~ /\.e2p$/)
	{
		print "$e2pCongi[0] is not e2p file, skip it\n";
		next;
	}  
	&UpdateE2pValue($e2pCongi[0], $e2pdata, $e2pvalue);
}

sub UpdateE2pValue
{
    my @e2pSettings = split(/,/, $_[2]);
    my $e2pLineNum = 0;
    my $n = @e2pSettings;
    print "e2pSetting ", $n, "\n";
    foreach $e2pSetting (@e2pSettings)
    {
    	print $e2pSetting," ";
    }
    print"\n";
    open(E2P_INFILE, "<".$_[0]) or die "cannot read \"stack.e2p\" file\n";
    open(E2P_OUTFILE, ">"."stack.e2p") or die "cannot write \"stack.e2p\" file\n";    
    while(chomp($_lines = <E2P_INFILE>))
    {
        if ($_lines =~ /$_[1]\s/)
        {
            print E2P_OUTFILE $_lines."\n";
            chomp($_lines = <E2P_INFILE>);
            my $SettingCnt = 0;
            while(!($_lines =~ /^W\w+\s/))
            {
	            my $cnt = 0;
	            my @e2pLines = split(/\s/, $_lines);
	            my $newline;
	            foreach $e2pLine (@e2pLines)
	            {
	            	if(($e2pLine =~ /^%/) || ($SettingCnt>=@e2pSettings))
	            	{
	            		last;
	            	}
                $e2pLines[$cnt] = $e2pSettings[$SettingCnt];
                $cnt++;
                $SettingCnt++;
	            }
              $newline = join " ", @e2pLines;
              print "New line ",$newline,"\n";
              print E2P_OUTFILE $newline."\n";; 
	            chomp($_lines = <E2P_INFILE>);
	            if($SettingCnt>=@e2pSettings)
	            {
	            	last;
	            }
	          }
            print "Stop for next e2p ", $_lines, "\n";
            print E2P_OUTFILE $_lines."\n"; 
        }
        else
        {
            print E2P_OUTFILE $_lines."\n";
        }
    }
    close(E2P_INFILE);
    close(E2P_OUTFILE);
    move("stack.e2p", $_[0]);
}