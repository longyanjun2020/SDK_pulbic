#!/usr/bin/perl 
@FileContent = ();
@PeakContent = ();
@PeakStr = ();

if(1 ne @ARGV)
{
    die "Open the Input File";
}

unless(open(FileInFd,$ARGV[0]))
{
    die "Open" . $ARGV[0] . "Failed";
}

push (@FileContent,<FileInFd>);
close (FileInFd);

foreach(@FileContent)
{
    if(m#Current Memory Peak = (\d+),#)
    {
        chomp($_);
        push @PeakContent,$1;
        push @PeakStr , $_;
        print $_ . "\r\n";
    }
}
print "================\r\n";
if(1 ge @PeakContent)
{
    print"The number of peak value greping should be at least 2" . "\r\n";
    $tmpCnt = 1;
    foreach(@PeakContent)
    {
        print "No." . $tmpCnt++ . "  " . $_ . "\r\n";
    }
}

$Peak1 = shift(@PeakContent);
$Peak1Str = shift(@PeakStr);
while($Peak2 = shift(@PeakContent))
{
    $Peak2Str = shift(@PeakStr);
    print $Peak1Str . "\r\n";
    print $Peak2Str . "\r\n";
    print $Peak2 . "-" . $Peak1 . "=" . ($Peak2 - $Peak1) ."\r\n\r\n";
    $Peak1 = $Peak2;
    $Peak1Str = $Peak2Str;
}
