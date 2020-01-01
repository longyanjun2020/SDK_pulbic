#!/usr/bin/perl

use warnings;
use strict;
use File::Copy;

my %used;

# if source code release (ex. yes/no)
my $relCode = shift;

# platform project name (ex. pb_duo/mmi_m700d/xmmi_d300_v2)
my $all_platformName = shift;
my @platformName = split(/,/, $all_platformName);

# product name (ex. u8/s7)
#my $productName = shift;

# get release configuration xml filename
my $releaseConfigureXml = shift;

# get input sln file
#my $slnFileName = shift;

#open(INIFILE, "< $inputName") or die "cannot read \"$inputName\" file\n";
#my @projNames=<INIFILE>;
#close(INIFILE);

my @projNames=("Drv_Acc.vcproj");

sub updateConfigMake
{
	my $configMak = "config.mak";
	open(CONFIG_MAK, "< $configMak") or die "cannot read \"$configMak\" file\n";
	my @configMakContent=<CONFIG_MAK>;
	close(CONFIG_MAK);
	
	open(CONFIG_MAK, "> $configMak") or die "cannot read \"$configMak\" file\n";
	for my $line (@configMakContent)
	{
		my $head;
		my $body;
		if ($line =~ /PRODUCT\=/)
		{
			$head = $`;
			$body = $&;
			my $config_product = $platformName[0];
			my @pName = split(/\_/, $config_product);
			#$config_product = $pName[0]."_".$pName[3];
			$config_product =~ s/\_$pName[1]\_$pName[2]//;
			$line = $head.$body."$config_product\n";
		}
		print CONFIG_MAK $line;
	}
	close(CONFIG_MAK);
}

sub genReleaseConfiguration
{
	my $filename = shift;
	my $pattern = shift;
	my $product = shift;
	open(XML_FILE, "$filename") or die "cannot read \"$filename\" file\n";
	my @content=<XML_FILE>;
	close(XML_FILE);
	
	open(XML_FILE, "> $filename") or die "cannot read \"$filename\" file\n";
	for my $line (@content)
	{
		if ($line =~ /$pattern/)
		{
			$line =~ s/$pattern/$product/;
		}
		print XML_FILE $line;
	}
	close(XML_FILE);
}

sub genCustomerBuildShells
{
	my $filename = shift;
	my $destination = shift;
	open(SHELL_FILE, "$filename") or die "cannot read \"$filename\" file\n";
	my @content=<SHELL_FILE>;
	close(SHELL_FILE);
	
	open(SHELL_FILE, "> $destination") or die "cannot read \"$destination\" file\n";
	for my $line (@content)
	{
		if ($line =~ /\$product_name/)
		{
			$line =~ s/\$product_name/\$1/g;
		}
		print SHELL_FILE $line;
	}
	close(SHELL_FILE);
}

sub changeMode
{
	my @allFiles = <*>;
	for my $path (@allFiles)
	{
		if (-d $path)
		{
			chdir $path;
			changeMode();
			chdir "..\\";
		}
		else
		{
			if ($path =~ /\.pl$/ || $path =~ /\.bat$/)
			{
				chmod(0744, $path);
			}
		}
	}
}

if ($relCode =~ /yes/i)
{
	updateConfigMake();
}

my @cus_product;

for (0 ... $#platformName)
{
	$cus_product[$_] = $platformName[$_];
	my @pName = split(/\_/, $cus_product[$_]);
	#$cus_product[$_] = $pName[0]."_".$pName[3];
	$cus_product[$_] =~ s/\_$pName[1]\_$pName[2]//;
	
	if (-e "mak/options_$platformName[$_].mak")
	{
		print "change filename mak/options_$platformName[$_] to $cus_product[$_]\n";
		rename ("mak/options_$platformName[$_].mak", "mak/options_$cus_product[$_].mak");
	}
	if (-e "sc/customer/product/cust/feedback/fb_$platformName[$_].txt")
	{	
		print "change filename fb_$platformName[$_].txt to fb_$cus_product[$_].txt\n";
		rename ("sc/customer/product/cust/feedback/fb_$platformName[$_].txt", "sc/customer/product/cust/feedback/fb_$cus_product[$_].txt");
	}
	if (-e "sc/customer/product/cust/code_size_log/CodeSizeLog_$platformName[$_].txt")
	{	
		print "change filename CodeSizeLog_$platformName[$_].txt to CodeSizeLog_$cus_product[$_].txt\n";
		rename ("sc/customer/product/cust/code_size_log/CodeSizeLog_$platformName[$_].txt", "sc/customer/product/cust/code_size_log/CodeSizeLog_$cus_product[$_].txt");
	}
	if (-e "sc/customer/product/cust/release_$platformName[$_].mak")
	{	
		print "change filename release_$platformName[$_].mak to release_$cus_product[$_].mak\n";
		rename ("sc/customer/product/cust/release_$platformName[$_].mak", "sc/customer/product/cust/release_$cus_product[$_].mak");
	}
	if (-e "sc/customer/product/cust/CustReleaseFiles_$platformName[$_].txt")
	{	
		print "change filename CustReleaseFiles_$platformName[$_].txt to CustReleaseFiles_$cus_product[$_].txt\n";
		rename ("sc/customer/product/cust/CustReleaseFiles_$platformName[$_].txt", "sc/customer/product/cust/CustReleaseFiles_$cus_product[$_].txt");
	}
	if (-e "sc/customer/product/cust/include/global_config_$platformName[$_].h")
	{	
		print "change filename global_config_$platformName[$_].h to global_config_$cus_product[$_].h\n";
		rename ("sc/customer/product/cust/include/global_config_$platformName[$_].h", "sc/customer/product/cust/include/global_config_$cus_product[$_].h");
	}
}

sub delUnusedProd
{
	my @allFiles = <*>;
	my $found_juji = 0;
	for my $files (@allFiles)
	{
		my $foundFile = 0;
		if (-e $files)
		{
			for (0 ... $#cus_product)
			{
				if ($cus_product[$_] =~ /8533n\_mb303av2/)
				{
					$found_juji = 1;
				}
				if ($cus_product[$_] =~ /8532\_mb406gos/)
				{
					$found_juji = 1;
				}
				if (($files =~ /$cus_product[$_]/) || ($files =~ /CustReleaseFiles_Common/) || ($files =~ /saveLCMBase/) || ($files =~ /fb.txt/))
				{
					$foundFile = 1;
				}
			}
			if (($files =~ /8533n\_71623d/) && ($found_juji == 1))
			{
				$foundFile = 1;
			}
			if (($files =~ /8532\_mb406g/) && ($found_juji == 1))
			{
				$foundFile = 1;
			}
			if ($foundFile == 0)
			{		
				print "del $files ";
				system("rm $files");
			}
		}
	}
}

#delete all unused product options.mak
chdir "mak";
delUnusedProd();
chdir "../";

#delete all unused product fb_xxxxx.mak
chdir "sc/customer/product/cust/feedback";
delUnusedProd();
chdir "../../../../../";


#delete all unused product CodeSizeLog_xxxxx.mak
chdir "sc/customer/product/cust/code_size_log";
delUnusedProd();
chdir "../../../../../";


#delete all unused product release_xxxxx.mak
chdir "sc/customer/product/cust";
delUnusedProd();
chdir "../../../../";

#delete all unused product global_config_xxxxx.h
chdir "sc/customer/product/cust/include";
delUnusedProd();
chdir "../../../../../";

