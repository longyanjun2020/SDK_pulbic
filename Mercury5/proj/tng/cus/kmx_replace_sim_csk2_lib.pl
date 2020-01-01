#!/usr/bin/perl

use strict;

my $product = shift;
my $chinese_s = shift;
my $chinese_t = shift;

#print "PRODUCT: $product \n";
#print "chinese_s: $chinese_s \n";
#print "chinese_t: $chinese_t \n";

system("chmod 755 ./MStarStudio_UP/lib/csk2.lib");
if(	$chinese_s eq "TRUE" or $chinese_t eq "TRUE")
{
    system("cp ./MStarStudio_UP/lib/csk2_full.lib ./MStarStudio_UP/lib/csk2.lib");
	print "Support Fully language: cp csk2_full.lib to csk2.lib\n";
}
else
{
    system("cp ./MStarStudio_UP/lib/csk2_noChinese.lib ./MStarStudio_UP/lib/csk2.lib");
	print "No support Chinese_S or Chinese_T language: cp csk2_noChinese.lib to csk2.lib\n";
}
