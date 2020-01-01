#!/usr/bin/perl

use strict;

my $product = shift;
my $smallRom = shift;
my $sinovoice_tcard = shift;

#print "PRODUCT: $product \n";
#print "smallRom: $smallRom \n";
#print "sinovoice_tcard: $sinovoice_tcard \n";
#print "sinovoice_tcard: $sinovoice_tcard \n";	

system("chmod 755 ./MStarStudio_UP/lib/hzrecog.lib");
if(	$sinovoice_tcard eq "TRUE" )
{	
	system("cp ./MStarStudio_UP/lib/hzrecog_file_v5.lib ./MStarStudio_UP/lib/hzrecog.lib");
	system("cp ./sc/customer/default/src/mmi/resource/project/3rd/HW_SINOVOICE_CT_CS_EN_V5.bin ./build/$product/out/SVData");
	print "cp hzrecog_file_v5.lib to hzrecog.lib\n";
	print "cp HW_SINOVOICE_CT_CS_EN_V5.bin to out\SVData \n";
}
else
{		
	system("cp ./MStarStudio_UP/lib/hzrecog_flash_v5.lib ./MStarStudio_UP/lib/hzrecog.lib");	
	print "cp hzrecog_flash_v5.lib to hzrecog.lib\n";
}
