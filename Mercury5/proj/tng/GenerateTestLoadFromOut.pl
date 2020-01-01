#!/usr/bin/perl

use warnings;
use strict;
use File::Copy;

my $productname;
my $needjtag="n";
my $in;

sub getproductname
{
	my $configMak = "config.mak";
	open(CONFIG_MAK, "< $configMak") or die "cannot read \"$configMak\" file\n";
	my @configMakContent=<CONFIG_MAK>;
	close(CONFIG_MAK);
	
	for my $line (@configMakContent)
	{
		if ($line =~ /PRODUCT\=/)
		{
			$productname = $';
			chomp($productname);
		}
	}
}

getproductname();

print "product [$productname]: ";
chomp($in = <STDIN>);
$productname = $in if ($in ne "");

print "Need JTAG data?[n]: ";
chomp($in = <STDIN>);
$needjtag = $in if ($in ne "");

my $testloadpath = "./build/".$productname."/out/testload/";
my $testloadtmtpath = "./build/".$productname."/out/testload/tmt/";
my $outpath = "./build/".$productname."/out/";
my $tmtpath = "./build/".$productname."/tmt/";

if(-e $testloadpath)
{
	system "rm -fr $testloadpath*";
}
else
{
	system "mkdir $testloadpath";
}
system "mkdir $testloadtmtpath";

system "cp $outpath\*.bin $testloadpath";
system "cp $outpath\*.e2p $testloadpath";
system "cp $outpath\*.cus $testloadpath";
system "cp $outpath\*.CUS $testloadpath";
system "cp $outpath\*.wpb $testloadpath";
system "cp $outpath\*.fat $testloadpath";
system "cp $outpath\*.ini $testloadpath";
system "cp $outpath\*.prm $testloadpath";
system "cp $outpath\*.wt $testloadpath";
system "cp $outpath\*.pat $testloadpath";
system "cp $outpath\*.img $testloadpath";
system "cp $outpath\*.prt $testloadpath";
system "cp $outpath\*link.info $testloadpath";
system "cp $outpath\*.nni $testloadpath";
system "cp $outpath\*.pni $testloadpath";
system "cp $outpath\*.ldr $testloadpath";
system "cp $outpath\*.bst $testloadpath";
system "cp $outpath\*.nro $testloadpath";
system "cp $outpath\*.nrw $testloadpath";
system "cp $outpath\*.dll $testloadpath";
system "cp $outpath\*.val $testloadpath";
system "cp -r $outpath\\fat $testloadpath";
system "cp -r $outpath\\hfat $testloadpath";
system "cp $outpath\\NvramMerge.exe $testloadpath";
system "cp $outpath\\nvram.i $testloadpath";
system "cp $outpath\\setting.miu $testloadpath";
system "cp $outpath\*.bt.map $testloadpath";
system "cp $tmtpath\* $testloadtmtpath";
system "cp $outpath\\list_*.mak $testloadpath";

if($needjtag eq "y")
{
	system "cp $outpath\*.axf $testloadpath";
}
