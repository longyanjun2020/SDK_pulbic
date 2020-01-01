#!/usr/bin/perl

use warnings;
use strict;
use File::Basename;
use File::Copy;




####################################################################
# Global Variable
####################################################################
my $MAK_ARCH = "1";
use constant COMMON_OPTION_DIR  => 'sc/customer/product/common/mak/';

####################################################################
# START OF MAIN
####################################################################

my $const_product_dir = "";
if ($MAK_ARCH =~ 0) {
	$const_product_dir = "sc/customer/product/";
}
else{
	$const_product_dir = "mak/";
}


my $in;
my $options_path = "";
my @optionMakContent;
my @CommonoptionMakContent;
my $chipType="";
my $clean_resource=0;
my $P4_account = "full";

my $tngdir= "tng";
#(my $top=$0)=~s!tng\/configure.pl$!!;
# find OS type
my $os = `uname`;
if ($os =~ m/Linux/i) {
	$os = "linux";
}
elsif ($os =~ m/Cygwin/i) {
	$os = "cygwin";
}
elsif ($os =~ m/Windows/i) {
	$os = "Win32";
}elsif($os =~ m/msys|mingw/i){
    $os="msys";
}else {
	die "unknown system";
}

warn "OS type: \"$os\"\n";
my $tng;
if ( $os eq  "Win32" )
{
	$tng = $tngdir . "/";
}
else
{
	$tng = File::Basename::dirname($0) . "/";
}

warn "TNG dir: \"$tng\"\n";
my $top=File::Basename::dirname($tng);

#####################################
# List all Product
#####################################
my @prd;  # product list.

my $max_product_index= 0;
if($#ARGV < 0)
{
	#set product as parameter in command line, which do not need to list all products for user selection
	print "available products:\n";

	if ($MAK_ARCH =~ 0) {
		my $dir = $const_product_dir;
		opendir PRD, $dir or die "cannot access product in \"", $dir, "\"\n";
		print "available products:\n";
		for my $prd (sort(readdir(PRD)))
		{
			if ((-d "$dir/$prd") and ($prd !~ m/^\./) and ($prd ne "common"))
			{
				print " $max_product_index ";
				push @prd, $prd;
				print "\t- ", $prd, "\n";
				$max_product_index++;
			}
		}
		closedir PRD;
	}
	else
	{
		open(CMD, "find ${\$top}/mak -maxdepth 1 -name \"options_*.mak\"|");
		while(<CMD>)
		{
			chomp;
			$_ =~ s/.*\/options_//g;
			$_ =~ s/\.mak//g;
			print " $max_product_index ";
			push @prd, $_;
			print " - ", $_, "\n";
			$max_product_index++;
		}
		close(CMD);
	}
}

#####################################
# Get Original Product Name
#####################################
my $product = "";
my $quick=undef;
my $global_header="FALSE";
# default to previous product
my $config = "config.mak";

if (open CONFIG, "< $config")
{
	while ($in = <CONFIG>)
	{
		chomp($in);
        if($in =~ m/^GLOBAL_HEADER=(.*)/){
            $global_header=$1;
        }
		if ($in =~ s/PRODUCT:?=(.*)//)
		{
			$product = $1;
		}
		if( $product ne "" )
		{
			$clean_resource=1;
		}
	}
}

my $filter = "debug";

#####################################
# Get Product Name
#####################################
if($#ARGV >= 0)
{
	#set product as parameter in command line
	$product=shift;
	print "product set as [$product]\n";

  if(-e "tng/p4/ap/p4_access.txt" and -e "./tng/p4/ps/p4_access.txt" and -e "./tng/p4/sys/p4_access.txt"){
      $P4_account="full";
  }elsif(-e "tng/p4/ap/p4_access.txt"){
      $P4_account="MSZ";
      $quick="ap";
  }elsif(-e "tng/p4/sys/p4_access.txt"){
      $quick="sys";
  }elsif(-e "tng/p4/ps/p4_access.txt"){
      $quick="ps";
  }else{
      #warn "$0: unable to identify QUICK\n";
      $P4_account="full";
  }

#	if($#ARGV >= 0)
#	{
#		$P4_account = shift ;
#		print "P4_account set as [$P4_account]\n";
#	}
}
else
{
	#let user input parameter in console mode
	print "product [$product]: ";
	chomp($in = <STDIN>);

	if ( ($in ne "") && ($in !~ /[A-Za-z]/) )
	{
		if ($in >=0 && $in<$max_product_index )
		{
			if ($MAK_ARCH =~ 0) {
				my $i=0;
				my $dir = $const_product_dir;
				opendir PRD, $dir or die "cannot access product in \"", $dir, "\"\n";
				for my $prd (sort(readdir(PRD)))
				{
					if ((-d "$dir/$prd") and ($prd !~ m/^\./) and ($prd ne "common"))
					{
						if ( $i == $in )
						{
							print " Chose product $i. $prd \n";
							$product = $prd;
							last;
						}
						$i++;
					}
				}
			}
			else
			{
				$product = $prd[$in];
				print " Chose product $in. $product \n";
			}
		}else{
				print " Index out of boundary !!!"if ($in ne "");
				exit 1;
		}
	}else{
		$product = $in if ($in ne "");
		print " Chose product $product\n";
	}

	#1. P4 account
my $release=`sed -n '\/WMpRelease\/{N;s/^.*\\n//g;\/1\/p}' sc/customer/product/common/e2p/stack_nand.e2p.val sc/customer/product/common/e2p/stack_nor.e2p.val 2>/dev/null`;
if($release !~ m/1/o){
    #stack_nand.e2p.val stack_nor.e2p.val both not exist
    # or they are both assigned to 0
    #normal build
    if(-e "tng/p4/ap/p4_access.txt" and -e "./tng/p4/ps/p4_access.txt" and -e "./tng/p4/sys/p4_access.txt"){
        $P4_account="full";
    }elsif(-e "tng/p4/ap/p4_access.txt"){
        $P4_account="MSZ";
        $quick="ap";
    }elsif(-e "tng/p4/sys/p4_access.txt"){
        $quick="sys";
    }elsif(-e "tng/p4/ps/p4_access.txt"){
        $quick="ps";
    }else{
        #warn "$0: unable to identify QUICK\n";
        $P4_account="full";
    }
    #print " 0 - full\n";
	#print " 1 - MSZ\n";
	#print " 2 - MSC\n";
	#print "P4_account [$P4_account]: ";
	#chomp($in = <STDIN>);
	#if ($in ne ""){
	#	$P4_account = "full" if ($in eq "0");
	#	$P4_account = "MSZ" if ($in eq "1");
	#	$P4_account = "MSC" if ($in eq "2");
	#}
	#print " Chose P4_account $in. $P4_account \n";
}else{
    #release build
    # at least one of the e2p.val file exists
    # and set to 1
    #default assigned to full
    $P4_account="full";
    system("perl ./tng/release_process/gen3rdSimulator.pl $product");
}

	#2. traces options
#	print "traces options:\n";

	#3. filter
	print "filter [$filter]: ";
	chomp($in = <STDIN>);
	$filter = $in if ($in ne "");

	#4. colors
	print "colors [y]: ";
	chomp($in = <STDIN>);
	$filter = "color " . $filter if ($in =~ m/n/i);


	# create config file
	if (-f $config)
	{
		print "overwrite \"$config\" [y]: ";
		chomp($in = <STDIN>);
		($in !~ m/n/i) or die $config, " unchanged\n";
	}
}

my $release2=`sed -n '\/WMpRelease\/{N;s/^.*\\n//g;\/1\/p}' sc/customer/product/common/e2p/stack_nand.e2p.val sc/customer/product/common/e2p/stack_nor.e2p.val 2>/dev/null`;
if($release2 =~ m/1/o){
	if($#ARGV >= 0)
    {
    	my $rename_BD=shift;
    	system("perl ./tng/cus/renameFiles.pl $rename_BD");
    }
    else
    {
    	system("perl ./tng/cus/renameFiles.pl");
    }
}

#####################################
# Check Product existed or not
#####################################

if ($MAK_ARCH =~ 0) {
	my $product_dir = $const_product_dir. $product;
	if (!-d $product_dir)
	{
		print " ERROR - Product DIR is not exist: $product_dir \n";
		exit(1);
	}
	$options_path = $const_product_dir.$product."/mak/options.mak";
	print $options_path. "\n";
	open(OPTION_MAK, "< $options_path") or die "cannot read \"$options_path\" file\n";
}
else
{
    my $product_mak;
    if(-e $const_product_dir."options_".$product.".mak"){
	    $product_mak = $const_product_dir."options_".$product.".mak";
    }else{
        $product_mak = $const_product_dir."Eng/options_".$product.".mak";
    }
	print $options_path. "\n";
	open(OPTION_MAK, "< $product_mak") or die "cannot read \"$product_mak\" file\n";
	system("cp ../tools/RSExtend/comment.h sc/application/mmi/common/inc/rs_gen_struct.h");
}
@optionMakContent=<OPTION_MAK>;
close(OPTION_MAK);

#####################################
# Check multiple definition options_$(product_name).mak
#####################################
my %OPTION_HASH;
my $switch_line=0;
my $temp=0;
for my $line1 (@optionMakContent)
{
	$temp = $switch_line ;
	if( $line1 =~ m/(\\)/g )
	{
		$switch_line = 1;
		next ;
	}
	next if ( $temp eq 1 ) ;

	#print "0:", $line1;
	next if $line1 =~ m/(\#)|(^\s*$)|(PP_OPT_COMMON)|(ifeq)|(ifneq)|(endif)|(\\)/g;
	#print "1:", $line1;
	$line1 =~ m/(\w*)\s*=\s*(\w*)\s*/g ;
	#print "\t2: -$1-, 3: -$2- \n";
	next if ( $1 eq "" || $2 eq "" );
	#print "\t4: $1, 5: $2 \n";

	if (exists $OPTION_HASH{$1})
	{
		print "----------------------------------------------------\n" ;
		print "Please correct the configuration in options_$product\.mak\n";
		print "$1 is multiple defined ! \n";
		if( $OPTION_HASH{$1} ne $2 )
		{
			print "and we got conflict!!\n";
			print "1st value : $OPTION_HASH{$1}\n";
			print "2nd value : $2\n";
			print "----------------------------------------------------\n" ;
			exit 1;
		}
		print "----------------------------------------------------\n" ;
	}
	$OPTION_HASH{$1}=$2;
}

#####################################
# Check Common_option.mak existed or not
#####################################
my $common_option_mak = COMMON_OPTION_DIR."common_option.mak";
open(COMMON_OPTION_MAK, "< $common_option_mak") or die "cannot read \"$common_option_mak\" file\n";
@CommonoptionMakContent=<COMMON_OPTION_MAK>;
close(COMMON_OPTION_MAK);

#####################################
# Clean mmi temp resource and dlm entry file
#####################################
my $build_dir = "./build";

if ( (-d $build_dir) && ($clean_resource == 1) )
{
    system "make clean_mmi_cus_temp_resource AUTO_CLEAN=2";
    system "make clean_dlm_pre";
}

#####################################
# Get Compiler type and Chip type
#####################################
my $compiler = "";
my $profile = "";
my $cus_res = "";
my $cus_path = "";
my $cus_project = "";
my $cus_folder = "";
my $lcm_type = "";
my $lcm_support = "";
my $multi_theme = "";
my $sinovoice_tcard = "";
my $lp_setting = "";
my $chinese_s = "";
my $chinese_t = "";

my $compilerType="";

my $smallRom = 0;
my $java_solution = "";

for my $line2 (@optionMakContent)
{
	if ($line2 =~ /^LANGUAGE_PACK_LIST\s*=\s*(.*)/)
	{
		$lp_setting = $1;
		$lp_setting =~ s/ /#/g;
		chomp $lp_setting;
		last;
	}
}

for my $line (@CommonoptionMakContent)
{
	$line =~ s/\s//g;

	if ($line =~ /^LCM_SUPPORT\s*=\s*(.*)/)
	{
		$lcm_support = $1;
		chomp $lcm_support;

	}
}

for my $line1 (@optionMakContent)
{
	$line1 =~ s/\s//g;
	$line1 =~ s/\x0d\x0a//ig;
	$line1 =~ s/ //g;

	if ($line1 =~ /SMALL_ROM_SOLUTION\=/)
	{
		if ($' ne "")
		{
			$smallRom = 1;
			last;
		}
	}
	if ($line1 =~ /^SMALL_ROM_SUPPORT\=TRUE/x)
	{
		$smallRom = 1;
		last;
	}
}

for my $line (@optionMakContent)
{
	$line =~ s/\s//g;
	if ($line =~ /COMPILER_TYPE \= /x)
	{
		$compilerType = $';
		$compilerType =~ s/\x0d\x0a//ig;
		chomp $compilerType;
	}elsif ($line =~ /^CHIP_TYPE \= /x)
	{
		$chipType = $';
		$chipType =~ s/\x0d\x0a//ig;
		chomp $chipType;

		if ($smallRom eq 1)
		{
			$chipType =~ s/^\__//;
			$chipType =~ s/__$//;
			$chipType = $chipType."_64";
			$chipType = "__".$chipType."__";
		}
	}
	elsif ($line =~ /^SIMULATOR_PROFILE=(.*)/)
	{
		$profile = $1;
		chomp $profile;
	}
	elsif ($line =~ /^CUS_RES\s*=\s*(.*)/)
	{
		$cus_res = $1;
		chomp $cus_res;
	}
	elsif ($line =~ /^CUS_PATH\s*=\s*(.*)/)
	{
		$cus_path = $1;
		chomp $cus_path;
	}
	elsif ($line =~ /^CUS_PROJECT\s*=\s*(.*)/)
	{
		$cus_project = $1;
		chomp $cus_project;
	}
	elsif ($line =~ /^CUS_FOLDER\s*=\s*(.*)/)
	{
		$cus_folder = $1;
		chomp $cus_folder;
	}
	elsif ($line =~ /^LCM_RESOLUTION\s*=\s*(.*)/)
	{
		$lcm_type = $1;
		chomp $lcm_type;
	}
	elsif ($line =~ /^MULTI_THEMES_ENABLED\s*=\s*(.*)/)
	{
		$multi_theme = $1;
		chomp $multi_theme;
	}
	elsif ($line =~ /^HANDWRING_DB_TCARD_SUPPORT\s*=\s*(.*)/)
	{
		$sinovoice_tcard = $1;
		chomp $sinovoice_tcard;
	}
    elsif ($line =~ /^CHINESE_S_SUPPORT\s*=\s*(.*)/)
	{
		$chinese_s = $1;
		chomp $chinese_s;
	}
    elsif ($line =~ /^CHINESE_T_SUPPORT\s*=\s*(.*)/)
	{
		$chinese_t = $1;
		chomp $chinese_t;
	}

    if(($chipType ne "") && ($compilerType ne "") && ($profile ne ""))
	{
	    last;
	}
}

# for java oakmont solution generate preinstall data with diff scope
# current valid scope : __JAVA_OAKMONT_JAP0__ / __JAVA_OAKMONT__ / __JAVA_OAKMONT_JAP2__
for my $line1 (@optionMakContent)
{
    $line1 =~ s/\s//g;
    if ( (($line1 =~ /JAVA_SOLUTION \= __JAVA_OAKMONT_JAP0__/x) && ($line1 !~ /\#JAVA_SOLUTION \= __JAVA_OAKMONT_JAP0__/)) ||
          (($line1 =~ /JAVA_SOLUTION \= __JAVA_OAKMONT__/x) && ($line1 !~ /\#JAVA_SOLUTION \= __JAVA_OAKMONT__/)) ||
          (($line1 =~ /JAVA_SOLUTION \= __JAVA_OAKMONT_JAP2__/x) && ($line1 !~ /\#JAVA_SOLUTION \= __JAVA_OAKMONT_JAP2__/)) ||
          (($line1 =~ /JAVA_SOLUTION \= __JAVA_OAKMONT_JAP2C__/x) && ($line1 !~ /\#JAVA_SOLUTION \= __JAVA_OAKMONT_JAP2C__/)))
    {
         if ($line1 =~ /^JAVA_SOLUTION\s*=\s*(.*)/)
         {
             $java_solution = $1;
         }
     }

    if (($line1 =~ /JAVA_PREINSTALL_DATA_SUPPORT \= FALSE/x) && ($line1 !~ /\#JAVA_PREINSTALL_DATA_SUPPORT \= FALSE/))
    {
        #$java_solution = "NO_PREINSTALL_DATA";
        last;
    }
}
if( $java_solution ne "" )
{
    # Make sure there has Oakmont folder
    if(-e "./sc/application/3rd/java/Oakmont/")
    {
        chomp $java_solution;
        chdir "./sc/application/3rd/java/Oakmont/src/data/config";
        system("./gen_buildindata.bat $java_solution >oakmontdata_log.txt");
        chdir "./../../../../../../../..";
    }
    else
    {
        print "\nThere's NO Oakmont folder but enable Oakmont solution!\n";
    }
}

if($compilerType ne "")
{
    $compiler = $compilerType;
    $compiler =~ s/_//ig;
}else{
    $compiler = "RVCTV22";
}

print "ChipType: $chipType \n";
if($chipType eq "")
{
	print "\nERROR - CHIP_TYPE is not defined!\n";
	exit(1);
}

#Auto select resolution
if($cus_res ne "NONE")
{
	require "./tng/cus/resolutionCheck.pl";
	&Resource::lcm_auto_slect($lcm_support,$lcm_type,$profile,$cus_res,$cus_project,$smallRom,$multi_theme);
	$profile = &Resource::getProfile();
	$cus_res = &Resource::getCusRes();
	$cus_project = &Resource::getCusProject();
	#print "Simulator_Profile: $profile \n";

	print "Compiler: $compiler \n";
	print "Simulator_Profile: $profile \n";
	print "cus_res: $cus_res \n";
	print "cus_project: $cus_project \n";

	#modiy xml file
	system("perl ./tng/cus/modify_xml.pl $cus_path $cus_project $cus_res");

	#write language parameter to ./tng/cus/languagePack.mak
	#print "lp_setting: $lp_setting \n";
	system("perl ./tng/cus/languagePack.pl $lp_setting");
}
#####################################
# Write to Config.mak
#####################################
open CONFIG, "> $config" or die "cannot write to ", $config, "\n";
print CONFIG 'ifeq "$(OSTYPE)" "Win32"', "\n";
print CONFIG "OSTYPE=Win32\n";
print CONFIG "else\n";
print CONFIG 'OS:=$(shell uname)'."\n";
print CONFIG 'ifeq "$(OS)" "Linux"'."\n";
print CONFIG "OSTYPE = linux\n";
print CONFIG "else\n";
print CONFIG 'OSTYPE = $(shell echo $$OSTYPE)'."\n";
print CONFIG "endif\n";
print CONFIG "endif\n";
print CONFIG "TNG:=\$(TOP)", $tng, "\n";
print CONFIG "#PRODUCT was written by Perl, don't change it\n";
print CONFIG "PRODUCT=", $product, "\n";
print CONFIG "COMPILER_EXECUTABLE=arm-none-eabi-gcc\n";
print CONFIG "COMPILER_VERSION=$compiler\n";
print CONFIG "COMPILER_ARM=", $compiler, "_arm\n";
print CONFIG "COMPILER_THUMB=", $compiler, "_thumb\n";
print CONFIG "LINKER=", $compiler, "_link\n";
print CONFIG "export FILTER=$filter\n";
print CONFIG "COMMON=\$(TOP)sc/customer/product/common/mak/\n";
if ($MAK_ARCH =~ 0) {
	print CONFIG "MAK=\$(TOP)sc/customer/product/\$(PRODUCT)/mak/\n";
}else{
	print CONFIG "MAK=\$(TOP)/mak/\n";
}
print CONFIG "QUICK=$quick\n" if($quick);
print CONFIG "EXISTED_LIBS=\$(LIB_\$(QUICK)_SET:%=\$(OUT)%.lib)\n";
print CONFIG "EXISTED_DUO_LIBS=\$(LIB_\$(QUICK)_SET:%=\$(OUT_DUP)%_2.axf)\n";
print CONFIG "EXISTED_LIBS_FILE=\$(LIB_\$(QUICK)_SET:%=\$(LIBS_DIR_FOR_QUICK)%.lib)\n";
print CONFIG "#GLOBAL_HEADER must be defined before including the following two makefiles\n";
print CONFIG "#\"GLOBAL_HEADER=TRUE\" to enable global header file feature\n";
print CONFIG "GLOBAL_HEADER=$global_header\n";
print CONFIG "include \$(TNG)config.mak\n";
print CONFIG "include \$(TNG)compil.mak\n";
print CONFIG "PROFILE=$profile\n";
print CONFIG "P4_ACC=$P4_account\n";
close CONFIG;

if (! -d "./build/".$product)
{
	mkdir "./build/".$product
}
copy($config,"./build/".$product."/".$config);
chmod 0760,"./build/".$product."/".$config;

#Clean PC Simulator build files
#print "\nCleaning PC Simulator build files.....\n";
#if (-e "C:/Program Files/Microsoft Visual Studio 8/Common7/IDE/devenv.com")
#{
#	chdir "./MStarStudio_UP/MStarDeveloper/XMMI";
#	if($compiler eq "RVCTV22")
#	{
#		print "clean MMI_BuildAll.sln \n";
#        if($os eq "msys"){
#            system "cmd \/c .\\\\devenv.bat";
#        }else{
#		system '"C:/Program Files/Microsoft Visual Studio 8/Common7/IDE/devenv.com" MMI_BuildAll.sln "MStarSimulator - Win32 Debug" /clean';
#        }
#	}
#	else
#	{
#		print "clean MMI_BuildAll_G1.sln \n";
#        if($os eq "msys"){
#            system "cmd \/c .\\\\devenv_g1.bat";
#        }else{
#		system '"C:/Program Files/Microsoft Visual Studio 8/Common7/IDE/devenv.com" MMI_BuildAll_G1.sln "MStarSimulator - Win32 Debug" /clean';
#        }
#	}
#	chdir "./../../..";
#}
#system "rm -fr ./MStarStudio_UP/MStarDeveloper/XMMI/debug/SimFileSys/FLASH/*";
#system "rm -fr ./MStarStudio_UP/MStarOut/include/*";
#
#chdir "./MStarStudio_UP/MStarModule/libCommom";
#if($os eq "msys"){
#    system "cmd \/c .\\\\copy.bat";
#}else{
#system "./copy.bat";
#}
#chdir "./../../..";
#
##Generate compile option files for XRG and PC Simulator
#system ("./tng/GenOpt/GenOpt.pl",$product);
#
##Copy files that have different libs in different simulator
#if($P4_account ne "full")
#{
#	my $dir_MStarDeveloper = "./libs/ap/COMMON/MStarDeveloper/debug/";
#
#	if(-e $dir_MStarDeveloper)
#	{
#		print "\nCopying simulator files from $dir_MStarDeveloper..,\n";
#		system "cp $dir_MStarDeveloper/* ./MStarStudio_UP/lib/Debug";
#	}
#	else{
#		print "\e[31m$dir_MStarDeveloper is not exist!\n\e[0m";
#		print "\e[31mThere are no lib files for Simulator ,Simulator would build fail!\n\e[0m";
#		print "\e[31mPlease chech this if you want to build Simulator!\n\e[0m";
#	}
#	system ("./tng/p4/makeMSZsln.pl");
#}
#if(-e "./sc/libs/".$chipType."/MStarStudio_UP")
#{
#	print "\nCopying simulator files.....\n";
#	system "cp ./sc/libs/$chipType/MStarStudio_UP/* ./MStarStudio_UP/lib/Debug";
#	if(-e "./sc/libs/".$chipType."/MStarDeveloper/debug")
#	{
#		system "cp ./sc/libs/$chipType/MStarDeveloper/debug/* ./MStarStudio_UP/MStarDeveloper/XMMI/debug";
#	}
#}
#
##Generate vs2008 project and solution files
##system ("perl ./tng/GenVs2008.pl");
#
##Copy GenerateTestLoadFromOut_* files, please read GenerateTestLoadFromOut_Readme.txt for detail
#system "cp ./tng/GenerateTestLoadFromOut_* ./build/$product/out";
#
##undefine layout_id in sc/application/mmi/common/inc/ \n";
#system("perl ./tng/undef_layout_id.pl");
#
##copy handwriting lib & DB
#system("perl ./tng/cus/handwriting.pl $product $smallRom $sinovoice_tcard");
#
##copy KMX Simulator csk2.lib
#system("perl ./tng/cus/kmx_replace_sim_csk2_lib.pl $product $chinese_s $chinese_t");
#
##add global header file and path to simPath.2005
#if($global_header =~ /TRUE/)
#{
#    my $global_header_file_version = 0; #0: old version (v2.01, v2.02, v2.03), 1: new version (mainline, v2.04)
#
#    for my $line (@CommonoptionMakContent)
#    {
#	  	$line =~ s/\s//g;
#
#			#match PP_OPT_COMMON += __COMPONENT_BASE_CONFIGURATION__
#			if ($line =~ /^PP_OPT_COMMON\+=__COMPONENT_BASE_CONFIGURATION__/)
#			{
#				$global_header_file_version = 1;
#			}
#		}
#	system("perl ./tng/add_global_header_file.pl $product $global_header_file_version");
#
#    if ($global_header_file_version == 1)
#    {
#        if (-e "./sc/customer/product/cust/include/global_config_".$product.".h")
#        {
#            system ("./tng/GenOpt/strip/strip.sh", "./sc/customer/product/cust/include/global_config_".$product.".h");
#        }
#        else
#        {
#            print "\e[31mERROR!! global header file not exist!\e[0m";
#            exit 1;
#        }
#    }
#    else
#    {
#        if (-e "./sc/customer/product/".$product."/include/global_config.h")
#        {
#            system ("./tng/GenOpt/strip/strip.sh", "./sc/customer/product/".$product."/include/global_config.h");
#        }
#        else
#        {
#            print "\e[31mERROR!! global header file not exist!\e[0m";
#            exit 1;
#        }
#    }
#}

#####################################
# Write to CusConfig.ini
#####################################
#my $cusfolderini = "./sc/application/mmi/cus/cusfolder.ini";
#my $cusfolderpath = "";
#
#print "crate cusfolder.ini file for semulator for $cus_folder.....\n";
#open CUSFOLDERPATH, "> $cusfolderini" or die "cannot write to ", $cusfolderini, "\n";
#
#if($cus_folder =~ /__CUS_1__/  )
#{
#print CUSFOLDERPATH "/I \"..\\..\\..\\..\\sc\\application\\mmi\\cus\\cus1\\pub\"";
#$const_product_dir = "..\\..\\..\\..\\sc\\application\\mmi\\cus\\cus1\\";
#}
#elsif($cus_folder =~ /__CUS_2__/  )
#{
#print CUSFOLDERPATH "/I \"..\\..\\..\\..\\sc\\application\\mmi\\cus\\cus2\\pub\"";
#$const_product_dir = "..\\..\\..\\..\\sc\\application\\mmi\\cus\\cus2\\";
#}
#elsif($cus_folder =~ /__CUS_3__/  )
#{
#print CUSFOLDERPATH "/I \"..\\..\\..\\..\\sc\\application\\mmi\\cus\\cus3\\pub\"";
#$const_product_dir = "..\\..\\..\\..\\sc\\application\\mmi\\cus\\cus3\\";
#}
#elsif($cus_folder =~ /__CUS_4__/  )
#{
#print CUSFOLDERPATH "/I \"..\\..\\..\\..\\sc\\application\\mmi\\cus\\cus4\\pub\"";
#$const_product_dir = "..\\..\\..\\..\\sc\\application\\mmi\\cus\\cus4\\";
#}
#elsif($cus_folder =~ /__CUS_5__/  )
#{
#print CUSFOLDERPATH "/I \"..\\..\\..\\..\\sc\\application\\mmi\\cus\\cus5\\pub\"";
#$const_product_dir = "..\\..\\..\\..\\sc\\application\\mmi\\cus\\cus5\\";
#}
#else
#{
##default case
#print CUSFOLDERPATH "/I \"..\\..\\..\\..\\sc\\application\\mmi\\cus\\default\\pub\"";
#$const_product_dir = "..\\..\\..\\..\\sc\\application\\mmi\\cus\\default\\";
#}
#
#close CUSFOLDERPATH;

###########################################
# Write to Modify cusFolder project file
###########################################
#my $cusfolderproj = "./MStarStudio_UP/MStarKernel/Task/XMMI_CusFolder/mmi_cusfolder.vcproj";
#my @CusprojContent;
##my @CusprojContent1;
#chmod 0777,$cusfolderproj;
#
#print "read cusfolder.proj file from $cusfolderproj \n";
#open CUSFOLDERPROJ, "<$cusfolderproj" or die "cannot write to ", $cusfolderproj, "\n";
#@CusprojContent=<CUSFOLDERPROJ>;
#close(CUSFOLDERPROJ);
#
#print "modify cusfolder.proj file for semulator to $const_product_dir folder.....\n";
#open CUSFOLDERPROJ, ">$cusfolderproj" or die "cannot write to ", $cusfolderproj, "\n";
#
##p4 reansfer used
#foreach my $line(@CusprojContent)
#{
#	if ($line =~ /RelativePath="..\\..\\..\\..\\sc\\application\\mmi\\cus\\(.*?)\\(.*?)\"/)
#	{
#		my $temp = $2;
#		$line =~ s/RelativePath=\"(.*?)\"/RelativePath=\"$const_product_dir$temp\"/g;
#		print CUSFOLDERPROJ $line;
#	}
#	else
#	{
#		print CUSFOLDERPROJ $line;
#	}
#}
#
##project file org used
##foreach my $line (@CusprojContent)
##{
##	my @content =split(/<\/File>/, $line);
##
##	foreach my $content (@content)
##	{
##		if ($content =~ /RelativePath="..\\..\\..\\..\\sc\\application\\mmi\\cus\\(.*?)\\(.*?)\"/)
##		{
##			my $temp = $2;
##			$content =~ s/RelativePath=\"(.*?)\"/RelativePath=\"$const_product_dir$temp\"/g;
##			push  @CusprojContent1, "$content";
##		}
##		else
##		{
##			push  @CusprojContent1, "$content";
##		}
##		push @CusprojContent1, "</File>";
##
##	}
##}
##pop @CusprojContent1;
##foreach (@CusprojContent1)
##{
##	print CUSFOLDERPROJ "$_";
##}
#close(CUSFOLDERPROJ);
#
##chmod 0444,$cusfolderproj;
