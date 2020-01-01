#!/usr/bin/perl

#use File::Copy;


&EditConfigINI($ARGV[1], $ARGV[2], $ARGV[3]);
sub EditConfigINI
{
    my $paramCnt;
    open(_CONFIG_, "+>>".$ARGV[0]) or die "cannot write \"config.ini\" file\n";   #open for append
    print $ARGV[0],"\n";
    seek(_CONFIG_, 0, 0); 
    while(chomp($_lines = <_CONFIG_>))
    {
        print $_lines,"\n";
        if ($_lines =~ /Parameter_(\d+)/)
        {
        	$paramCnt = $1;
        	print "Parameter cnt ", $paramCnt, "\n";
        }
#        if (eof())
#        {
#        	print "Add param ", $paramCnt, "\n";
#        	$paramCnt++;
#        	print "Add param ", $paramCnt, "\n";
#        	print _CONFIG_ "\n\[Parameter_".$paramCnt."\]\n";
#        	print _CONFIG_ "; For Is_embed_spi_flash_only\n";
#        	print _CONFIG_ "id=".$_[0]."\n";
#        	print _CONFIG_ "length=".$_[1]."\n";
#        	print _CONFIG_ "data=".$_[2]."\n";
#        }
    }
    $paramCnt++;
    print _CONFIG_ "\n\n\[Parameter_".$paramCnt."\]\n";
    print _CONFIG_ ";Is_embed_spi_flash_only\n";
    print _CONFIG_ "id=".$_[0]."\n";
    print _CONFIG_ "length=".$_[1]."\n";
    print _CONFIG_ "data=".$_[2]."\n";
    close(_CONFIG_); 
}