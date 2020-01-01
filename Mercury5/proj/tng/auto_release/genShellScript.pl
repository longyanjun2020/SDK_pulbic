#!/usr/bin/perl

#use warnings;
use strict;
use File::Copy;

my %used;

# get release note
my $releaseNote = shift;

# get release note
my $releaseConfigureXml = shift;

my $relCode;
my $relSim;
my $relTool;
my $relDoc;
my @cus_product;
my @muti_platform;
my @cus_chipset;
my @muti_chipset;
my $fileListChangeStop;
my $relBuild;
my $OffBuild;
my $noFeedback;
my $lib_chipType;

my $ostype=`uname -s`;
if($ostype =~ m/mingw|msys/i){
    $ostype='msys';
}else{
    $ostype='cygwin';
}

sub genAutoReleaseShell
{
	my $srcDir = shift;
	my $srcSvn = shift;
	my $MMIsrcSvn = shift;
	my $CoreSWsrcSvn = shift;
	my $CommDocToolSvn = shift;
	my $shellScript = "auto_release.sh";
	
	open(SHELL_SCRIPT, "> $shellScript") or die "cannot read \"$shellScript\" file\n";
	print SHELL_SCRIPT "#!/bin/bash\n\n";
	print SHELL_SCRIPT "sync\n\n";
	print SHELL_SCRIPT "echo export codes\n";
	print SHELL_SCRIPT "if [ -e export_code.sh ]; then\n";
	print SHELL_SCRIPT "	./export_code.sh\n";
	#print SHELL_SCRIPT "	rm export_code.sh\n";
	print SHELL_SCRIPT "else\n";
	print SHELL_SCRIPT "	echo can not find export_code.sh\n";
	print SHELL_SCRIPT "	exit 1\n";
	print SHELL_SCRIPT "fi\n\n";
	print SHELL_SCRIPT "if [ -e $srcDir/proj/tng/UnmatchReleaseOp.log ]; then\n";
	print SHELL_SCRIPT "	echo Unmatched released option or removed files: UnmatchReleaseOp.log\n";
	print SHELL_SCRIPT "else\n";
	print SHELL_SCRIPT "	echo ReleaseOptions.txt all update!\n";
	print SHELL_SCRIPT "fi\n\n";
	print SHELL_SCRIPT "if [ -e $srcDir/proj ]; then\n";
	print SHELL_SCRIPT "	echo enter $srcDir/proj\n";
	print SHELL_SCRIPT "	cd $srcDir/proj\n";
	print SHELL_SCRIPT "else\n";
	print SHELL_SCRIPT "	echo can not find $srcDir/proj\n";
	print SHELL_SCRIPT "	exit 1\n";
	print SHELL_SCRIPT "fi\n\n";
	print SHELL_SCRIPT "rm ../export_rev.txt\n\n";
	print SHELL_SCRIPT "if [ -e ../../create_customer_project.sh ]; then\n";
	print SHELL_SCRIPT "	echo create project\n";
	print SHELL_SCRIPT "	../../create_customer_project.sh\n";
	print SHELL_SCRIPT "else\n";
	print SHELL_SCRIPT "	echo can not find ../../create_customer_project.sh\n";
	print SHELL_SCRIPT "	exit 1\n";
	print SHELL_SCRIPT "fi\n\n";
	print SHELL_SCRIPT "if [ -e ../../release.sh ]; then\n";
	print SHELL_SCRIPT "	echo start release process\n";
	print SHELL_SCRIPT "	../../release.sh\n";
	print SHELL_SCRIPT "else\n";
	print SHELL_SCRIPT "	echo can not find ../../release.sh\n";
	print SHELL_SCRIPT "	exit 1\n";
	print SHELL_SCRIPT "fi\n\n";
	if ($relCode =~ /no/i)
	{
		print SHELL_SCRIPT "if [ -e ./sc ]; then\n";
		print SHELL_SCRIPT "	echo remove folder sc\n";
		print SHELL_SCRIPT "	rm -r -f sc\n";
		print SHELL_SCRIPT "else\n";
		print SHELL_SCRIPT "	echo can not find ./sc\n";
		print SHELL_SCRIPT "	exit 1\n";
		print SHELL_SCRIPT "fi\n\n";
		
		print SHELL_SCRIPT "if [ -e ./tng ]; then\n";
		print SHELL_SCRIPT "	echo remove folder tng\n";
		print SHELL_SCRIPT "	rm -r -f tng\n";
		print SHELL_SCRIPT "else\n";
		print SHELL_SCRIPT "	echo can not find ./tng\n";
		print SHELL_SCRIPT "	exit 1\n";
		print SHELL_SCRIPT "fi\n\n";
	}
	print SHELL_SCRIPT "echo finish auto release\n";
	close(SHELL_SCRIPT);
}

sub genExportShell
{
	my $srcSvn = shift;
	my $srcDir = shift;
	my $MMIsrcSvn = shift;
	my $srcRevision = shift;
	my $relTo = shift;
	my $username = shift;
	my $password = shift;
	my $exportShellScript = "export_code.sh";
	
	open(SHELL_SCRIPT, "> $exportShellScript") or die "cannot read \"$exportShellScript\" file\n";
	print SHELL_SCRIPT "\#\!\/bin\/bash\n\n";
	print SHELL_SCRIPT "sync\n\n";
	
	if ((length($srcDir) != 0))
	{
		if ($relCode =~ /yes/i)
		{
			if ($relTo =~ /external/i)
			{
				print SHELL_SCRIPT "if [ -e $srcDir/proj/tng ]; then\n";
				print SHELL_SCRIPT "	echo enter $srcDir/proj/tng\n";
				print SHELL_SCRIPT "	cd $srcDir/proj/tng\n";
				print SHELL_SCRIPT "else\n";
				print SHELL_SCRIPT "	echo can not find $srcDir/proj\n";
				print SHELL_SCRIPT "	exit 1\n";
				print SHELL_SCRIPT "fi\n\n";

				print SHELL_SCRIPT "if [ -e releaseOp.pl ] && [ -e ReleaseOptions.txt ]; then\n";
				for (0 ... $#muti_platform)
				{
					open(OPTION_MAK, "< $srcDir/proj/mak/options_$muti_platform[$_].mak") or die "cannot read \"options.mak\" file\n";
					my @optionMakContent=<OPTION_MAK>;
					close(OPTION_MAK);	

					my $chipType;
					my $smallRom = 0;
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
						
						if ($line =~ /CHIP_TYPE \= /x)
						{
							$chipType = $';#'
							$chipType =~ s/\x0d\x0a//ig;
							chomp $chipType;
							$chipType =~ s/^\__//;
							$chipType =~ s/$\__//;
							if ($smallRom eq 1)
							{
								$chipType = $chipType."_64";
								#$chipType = "__".$chipType."__";
							}
							last;
						}
					}

					print SHELL_SCRIPT "	perl releaseOp.pl ReleaseOptions_$chipType.txt $muti_platform[$_]\n";
					print SHELL_SCRIPT "	perl releaseOp.pl ReleaseOptions.txt $muti_platform[$_]\n";
				} 
				for (0 ... $#muti_chipset)
				{
					open(OPTION_MAK, "< $srcDir/proj/mak/options_$muti_chipset[$_].mak") or die "cannot read \"options.mak\" file\n";
					my @optionMakContent=<OPTION_MAK>;
					close(OPTION_MAK);	

					my $chipType;
					my $smallRom = 0;
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
						
						if ($line =~ /CHIP_TYPE \= /x)
						{
							$chipType = $';#'
							$chipType =~ s/\x0d\x0a//ig;
							chomp $chipType;
							$chipType =~ s/^\__//;
							$chipType =~ s/$\__//;
							if ($smallRom eq 1)
							{
								$chipType = $chipType."_64";
								#$chipType = "__".$chipType."__";
							}
							last;
						}
					}

					print SHELL_SCRIPT "	perl releaseOp.pl ReleaseOptions_$chipType.txt $muti_chipset[$_]\n";
					print SHELL_SCRIPT "	perl releaseOp.pl ReleaseOptions.txt $muti_chipset[$_]\n";
				} 
				print SHELL_SCRIPT "	perl releaseOp.pl ReleaseDeletedLibs.txt $muti_platform[0]\n";
				print SHELL_SCRIPT "else\n";
				print SHELL_SCRIPT "	echo can not find releaseOp.pl or ReleaseOptions.txt\n";
				print SHELL_SCRIPT "	exit 1\n";
				print SHELL_SCRIPT "fi\n\n";

				open(VER_MAK, "< $srcDir/proj/sc/customer/product/common/mak/version.mak") or die "cannot read \"options.mak\" file\n";
				my @verMakContent=<VER_MAK>;
				close(VER_MAK);
		
				my $majVer;
				my $minVer;
				for my $line2 (@verMakContent)
				{
					$line2 =~ s/\s//g;
				
					if ($line2 =~ /SW_MAJ_VER\=/x)
					{
						$majVer = $';#'
						$majVer =~ s/\x0d\x0a//ig;
						chomp $majVer;
						$majVer =~ s/SW_MAJ_VER\=//;
						$majVer =~ s/0//;
					}
					if ($line2 =~ /SW_MIN_VER\=/x)
					{
						$minVer = $';#'
						$minVer =~ s/\x0d\x0a//ig;
						chomp $minVer;
						$minVer =~ s/SW_MIN_VER\=//;
					}
				}
				my $ver = $majVer.".".$minVer;
		
				print SHELL_SCRIPT "cd ../sc\n";
				print SHELL_SCRIPT "mkdir libs\n";
				print SHELL_SCRIPT "cd libs\n";
				print SHELL_SCRIPT "mkdir patchlog\n";
				print SHELL_SCRIPT "cp ../../config.mak patchlog/\n";
				print SHELL_SCRIPT "mv patchlog/config.mak patchlog/$ver.lib\n\n";
				print SHELL_SCRIPT "cd ../../tng\n";

				print SHELL_SCRIPT "if [ -e UnmatchReleaseOp.log ]; then\n";
				print SHELL_SCRIPT "	echo Unmatched released option or removed files: UnmatchReleaseOp.log\n";
				print SHELL_SCRIPT "else\n";
				print SHELL_SCRIPT "	echo ReleaseOptions.txt all update!\n";
				print SHELL_SCRIPT "fi\n\n";
				print SHELL_SCRIPT "echo leave $srcDir/proj/tng\n";
				print SHELL_SCRIPT "cd ../../..\n";

				#print SHELL_SCRIPT "cd $srcDir/proj/tng\n";
				#print SHELL_SCRIPT "perl MP_Release_E2P.pl ../sc/customer/product/common/e2p/stack_nand.e2p.val MpRelease\n";
				#print SHELL_SCRIPT "perl MP_Release_E2P.pl ../sc/customer/product/common/e2p/stack_nor.e2p.val MpRelease\n";
				#print SHELL_SCRIPT "perl GPRS_E2P.pl ../sc/customer/product/common/e2p/stack_nand.e2p.val WEnabledFtr 6\n";
				#print SHELL_SCRIPT "perl GPRS_E2P.pl ../sc/customer/product/common/e2p/stack_nor.e2p.val WEnabledFtr 6\n";
				#print SHELL_SCRIPT "cd ../../..\n";
				
				print SHELL_SCRIPT "cd $srcDir/proj\n";
				print SHELL_SCRIPT "if [ -e tng/release_process/release_E2P.pl ]; then\n";
				print SHELL_SCRIPT "perl tng/release_process/release_E2P.pl tng/release_process/E2P_list.txt vt_false\n";
				print SHELL_SCRIPT "fi\n\n";
				print SHELL_SCRIPT "cd ../..\n";

				print SHELL_SCRIPT "cd $srcDir/proj\n";
				print SHELL_SCRIPT "perl tng/release_process/process_make.pl\n";
				print SHELL_SCRIPT "cd ../..\n";				
			}
		}
	}
	
	close(SHELL_SCRIPT);
}

sub genCreateProjectShell
{
	my $platform = shift;
	my $product = shift;
	my $simulatorPath = shift;
	my $simulatorWorkSpace = shift;
	my $relPD = shift;
	my $srcDir = shift;

	my $shellScript = "create_customer_project.sh";
	open(SHELL_SCRIPT, "> $shellScript") or die "cannot read \"$shellScript\" file\n";
	print SHELL_SCRIPT "#!/bin/bash\n\n";
	print SHELL_SCRIPT "sync\n\n";
	
	if ($relCode =~ /yes/i)
	{
		open(KEEP_MAK, "< $srcDir/proj/tng/release_process/keepProduct") or die "cannot read \"keepProduct\" file\n";
		my $keepProduct=<KEEP_MAK>;
		close(KEEP_MAK);	

		if ($#muti_platform != -1)
		{
			print SHELL_SCRIPT "echo generate cust_release.mak\n";
			print SHELL_SCRIPT "tng/configure.pl $muti_platform[0]\n";
			print SHELL_SCRIPT "make clean\n\n";
			print SHELL_SCRIPT "make -f tng/CustRelease.mak\n\n";
			
			print SHELL_SCRIPT "make cust_check\n\n";
			print SHELL_SCRIPT "if [ -e build/$muti_platform[0]/out/cust_check.log ]; then\n";
			print SHELL_SCRIPT "	echo make cust_check success\n";
			print SHELL_SCRIPT "else\n";
			print SHELL_SCRIPT "	echo make cust_check fail\n";
			print SHELL_SCRIPT "	exit 1\n";
			print SHELL_SCRIPT "fi\n\n";
		}
		elsif ($#muti_chipset != -1)
		{
			print SHELL_SCRIPT "echo generate cust_release.mak\n";
			print SHELL_SCRIPT "tng/configure.pl $muti_chipset[0]\n";
			print SHELL_SCRIPT "make clean\n\n";
			print SHELL_SCRIPT "make -f tng/CustRelease.mak\n\n";
		}
		
		print SHELL_SCRIPT "if [ -e tng/genProductFiles.pl ] && [ -e sc/customer/product ]; then\n";
		print SHELL_SCRIPT "	echo create product folder\n";
		print SHELL_SCRIPT "	tng/genProductFiles.pl $relCode $platform$keepProduct $releaseConfigureXml\n";
		print SHELL_SCRIPT "else\n";
		print SHELL_SCRIPT "	echo can not find tng/genProductFiles.pl or $simulatorWorkSpace or sc/product\n";
		print SHELL_SCRIPT "	exit 1\n";
		print SHELL_SCRIPT "fi\n\n";

		print SHELL_SCRIPT "cd tng\n";
		print SHELL_SCRIPT "filelist=\$(ls ../sc/customer/product/cust/*.txt)\n";
		print SHELL_SCRIPT "for filename in \$filelist\n";
		print SHELL_SCRIPT "do\n";
		print SHELL_SCRIPT "  echo generate cust_release_files based on CustReleaseFiles_XXX.txt\n";
		print SHELL_SCRIPT "	perl releaseOp.pl \$filename CustRelease\n";
		print SHELL_SCRIPT "done\n\n";

		print SHELL_SCRIPT "echo move cust_release_files back\n";		
		print SHELL_SCRIPT "cp -rf proj/sc/customer/product/cust ../sc/customer/product\n";		
		print SHELL_SCRIPT "rm -rf proj/sc/customer/product/cust\n\n";
		print SHELL_SCRIPT "cd ..\n\n";

		my $cus_platform = join ',' , @cus_product;
	
		print SHELL_SCRIPT "if [ -e tng/genFileList.pl ] && [ -e sc ]; then\n";
		print SHELL_SCRIPT "	echo generate file list and update make file\n";
		print SHELL_SCRIPT "	tng/genFileList.pl FileList.xml sc $cus_platform\n";
		print SHELL_SCRIPT "else\n";
		print SHELL_SCRIPT "	echo can not find tng/genFileList.pl or sc\n";
		print SHELL_SCRIPT "	exit 1\n";
		print SHELL_SCRIPT "fi\n\n";
		
		print SHELL_SCRIPT "if [ -e tng/mergeCode.pl ] && [ -e sc/customer/default/profile/$releaseConfigureXml ]; then\n";
		print SHELL_SCRIPT "	echo compare and merge file list\n";
		print SHELL_SCRIPT "	tng/mergeCode.pl sc/customer/default/profile/$releaseConfigureXml FileList.xml fileChangeLog.txt\n";
		print SHELL_SCRIPT "else\n";
		print SHELL_SCRIPT "	echo can not find tng/mergeCode.pl or sc/customer/default/profile/$releaseConfigureXml\n";
		print SHELL_SCRIPT "	exit 1\n";
		print SHELL_SCRIPT "fi\n\n";

		print SHELL_SCRIPT "if [ -e fileChangeLog.txt ]; then\n";
		print SHELL_SCRIPT "	echo file list changed: fileChangeLog.txt\n";
		print SHELL_SCRIPT "	echo sc/customer/default/profile/$releaseConfigureXml is update!\n";
		if ($fileListChangeStop =~ /yes/i)
		{
			print SHELL_SCRIPT "	exit 1\n";
		}
		print SHELL_SCRIPT "else\n";
		print SHELL_SCRIPT "	echo file list no update\n";
		print SHELL_SCRIPT "fi\n\n";
	}
	
	my $cus_platform;
	$cus_platform = join ',' , @cus_product;
	
	#print SHELL_SCRIPT "if [ -e tng/cus_auto_release/ReleaseConfigurations.txt ]; then\n";
	#print SHELL_SCRIPT "	echo update auto release tool for customers\n";
	#print SHELL_SCRIPT "	tng/replacePattern.pl tng/cus_auto_release/ReleaseConfigurations.txt %Platform% $cus_platform\n";
	#print SHELL_SCRIPT "	tng/replacePattern.pl tng/cus_auto_release/ReleaseConfigurations.txt %Product% $product\n";
	#print SHELL_SCRIPT "	tng/replacePattern.pl tng/cus_auto_release/ReleaseConfigurations.txt %ReleasePD% $relPD\n";
	#print SHELL_SCRIPT "fi\n\n";
		
	print SHELL_SCRIPT "echo finish create customer project\n";
	close(SHELL_SCRIPT);
}

sub genReleaseShell
{
	my $releaseType = shift;
	my $shellScript = "release.sh";
	open(SHELL_SCRIPT, "> $shellScript") or die "cannot read \"$shellScript\" file\n";
	print SHELL_SCRIPT "#!/bin/bash\n\n";
	print SHELL_SCRIPT "sync\n\n";
	if ($relCode =~ /yes/i)
	{
		print SHELL_SCRIPT "if [ -e fileChangeLog.txt ]; then\n";
		print SHELL_SCRIPT "	echo file list changed: fileChangeLog.txt\n";
		if ($fileListChangeStop =~ /yes/i)
		{
			print SHELL_SCRIPT "	exit 1\n";
		}
		print SHELL_SCRIPT "else\n";
		print SHELL_SCRIPT "	echo file list no update\n";
		print SHELL_SCRIPT "fi\n\n";
		
		if ($#muti_platform != -1)
		{
			print SHELL_SCRIPT "if [ -e build/$muti_platform[0]/out/cust_check.log ]; then\n";
			print SHELL_SCRIPT "	make clean\n\n";
			print SHELL_SCRIPT "else\n";
			print SHELL_SCRIPT "	echo make cust_check fail\n";
			print SHELL_SCRIPT "	exit 1\n";
			print SHELL_SCRIPT "fi\n\n";
		}
		
		print SHELL_SCRIPT "cd tng\n";
        if($ostype eq "msys"){
		    print SHELL_SCRIPT "./CodeReleaseMaker.exe //C MAK //F ..//sc//customer//default//profile//$releaseConfigureXml //O ..//\n";
        }else{
		    print SHELL_SCRIPT "./CodeReleaseMaker.exe /C MAK /F ../sc/customer/default/profile/$releaseConfigureXml /O ../\n";
		}
		#print SHELL_SCRIPT "./CodeReleaseMaker.exe /C CONFIG /F ../sc/customer/default/profile/CustomerSettings.xml /O ../sc/customer/default/profile/CustomerSettings.dat\n";
		print SHELL_SCRIPT "cd -\n\n";
	}
	print SHELL_SCRIPT "../../full_release.sh\n\n";
	if ($releaseType =~ /delta/)
	{
		print SHELL_SCRIPT "../../delta_release.sh\n\n";
	}
	print SHELL_SCRIPT "echo finish release\n";
	close(SHELL_SCRIPT);
}

sub genFullReleaseShell
{
	my $simulatorPath = shift;
	my $simulatorWorkSpace = shift;
	my $srcDir = shift;
	my $relPD = shift;
	my $simuProduct = shift;
	my $shellScript = "full_release.sh";
	open(SHELL_SCRIPT, "> $shellScript") or die "cannot read \"$shellScript\" file\n";
	print SHELL_SCRIPT "#!/bin/bash\n\n";
	print SHELL_SCRIPT "sync\n\n";
	if ($relCode =~ /yes/i)
	{
		print SHELL_SCRIPT "cd ../tools/RawToC\n";
		print SHELL_SCRIPT "cd ../../proj\n";

		print SHELL_SCRIPT "cd sc\n";
		print SHELL_SCRIPT "mkdir libs\n";
		print SHELL_SCRIPT "cd ..\n";

		my $cnt = 0;
		for (0 ... $#cus_product)
		{
			print SHELL_SCRIPT "echo replace pattern for turn on compile options\n";
			print SHELL_SCRIPT "tng/replacePattern.pl config.mak $cus_product[$cnt] $cus_product[$#cus_product-$_]\n";
			$cnt = $#cus_product-$_;

			if ($cus_product[$cnt] =~ /ct/i)
			{
				print SHELL_SCRIPT "if [ -e tng/replaceOption.pl ] && [ -e mak/options_$cus_product[$cnt].mak ]; then\n";
				print SHELL_SCRIPT "	tng/replaceOption.pl mak/options_$cus_product[$cnt].mak \"LOG_LEVEL_CUT_OPTION = LOG_LEVEL_ALL\" \"LOG_LEVEL_CUT_OPTION = LOG_LEVEL_CRITICAL_ONLY\"\n";
				print SHELL_SCRIPT "fi\n\n";
			}
			print SHELL_SCRIPT "echo clean\n";
			print SHELL_SCRIPT "make clean\n\n";
			
			print SHELL_SCRIPT "if [ -e tng/configure.pl ]; then\n";			
			print SHELL_SCRIPT "  tng/configure.pl $cus_product[$cnt]\n";
			print SHELL_SCRIPT "fi\n\n";

			print SHELL_SCRIPT "echo make speed\n";
			if ($noFeedback =~ /yes/i)
			{
				#print SHELL_SCRIPT "echo -ne \"start time : \"\n";
				#print SHELL_SCRIPT "date +%k:%M\n";
				#print SHELL_SCRIPT "make DZbuild_debug DISABLE_FEEDBACK=1 NO_DEBUG=1 2>&1 1>&make_$cus_product[$cnt].log\n\n";
				#print SHELL_SCRIPT "echo -ne \"end time : \"\n";
				#print SHELL_SCRIPT "date +%k:%M\n";

				print SHELL_SCRIPT "echo -ne \"start time : \"\n";
				print SHELL_SCRIPT "date +%k:%M\n";
				print SHELL_SCRIPT "make csn csn2 build_preprocess build_common_libs DISABLE_FEEDBACK=1 NO_DEBUG=1 2>&1 1>&make_$cus_product[$cnt].log\n\n";
				print SHELL_SCRIPT "make build_feature_libs DISABLE_FEEDBACK=1 NO_DEBUG=1 2>&1 1>&make_$cus_product[$cnt].log\n\n";
				print SHELL_SCRIPT "make build_bsp_libs DISABLE_FEEDBACK=1 NO_DEBUG=1 2>&1 1>&make_$cus_product[$cnt].log\n\n";
				print SHELL_SCRIPT "make build_chip_libs DISABLE_FEEDBACK=1 NO_DEBUG=1 2>&1 1>&make_$cus_product[$cnt].log\n\n";
				print SHELL_SCRIPT "echo -ne \"end time : \"\n";
				print SHELL_SCRIPT "date +%k:%M\n";
			}
			else
			{
				print SHELL_SCRIPT "echo -ne \"start time : \"\n";
				print SHELL_SCRIPT "date +%k:%M\n";
				print SHELL_SCRIPT "make DZbuild_debug 2>&1 1>&make_$cus_product[$cnt].log\n\n";
				print SHELL_SCRIPT "make log > make_log_cmd_$cus_product[$cnt].log\n\n";
				print SHELL_SCRIPT "echo -ne \"end time : \"\n";
				print SHELL_SCRIPT "date +%k:%M\n";

				print SHELL_SCRIPT "if [ -e build/$cus_product[$cnt]/out/$cus_product[$cnt]\.bin ]; then\n";
				print SHELL_SCRIPT "	echo -ne \"start time : \"\n";
				print SHELL_SCRIPT "	date +%k:%M\n";
				print SHELL_SCRIPT "	make build_chip_libs 2>&1 1>&make_libs_$cus_product[$cnt].log\n\n";
				print SHELL_SCRIPT "    make log > make_log_cmd_$cus_product[$cnt].log\n\n";
				print SHELL_SCRIPT "	echo -ne \"end time : \"\n";
				print SHELL_SCRIPT "	date +%k:%M\n";				
				print SHELL_SCRIPT "fi\n\n";
			}

			if (($noFeedback =~ /no/i) && ($relSim =~ /yes/i))
			{		    
                print SHELL_SCRIPT "if [ -e $simulatorPath ] && [ -e $simulatorPath/$simulatorWorkSpace ]; then\n";
			    if($simuProduct eq $cus_product[$cnt])
			    {    				
    				print SHELL_SCRIPT "	echo use VisualStudio 2005 to open simulator sln and build all\n";
    				print SHELL_SCRIPT "	cd $simulatorPath\n";
    
    				print SHELL_SCRIPT "  echo -ne \"start time : \"\n";
    				print SHELL_SCRIPT "  date +%k:%M\n";
    				print SHELL_SCRIPT "	/cygdrive/c/Program\\ Files/Microsoft\\ Visual\\ Studio\\ 8/Common7/IDE/devenv.com $simulatorWorkSpace /rebuild 2>&1 1>&../../../vs2005_r_$cus_product[$cnt].log\n";
    				#print SHELL_SCRIPT "	/cygdrive/c/Program\\ Files/Xoreax/IncrediBuild/BuildConsole.exe $simulatorWorkSpace /CFG=\"Debug\|Win32\" /REBUILD 2>&1 1>&../../../vs2005_r_$cus_product[$cnt].log\n";
    				print SHELL_SCRIPT "  echo -ne \"end time : \"\n";
    				print SHELL_SCRIPT "  date +%k:%M\n";
    				print SHELL_SCRIPT "	cp -rf debug/*.exe ../../lib/debug/\n";
   				print SHELL_SCRIPT "	cp -rf debug/M*.dll ../../lib/debug/\n";
    				print SHELL_SCRIPT "	cd ../../..\n\n";
                }
                else
                {
                    print SHELL_SCRIPT "\n  echo -n \"========== Rebuild All: 107 succeeded, 0 failed, 0 skipped ==========\" > vs2005_r_$cus_product[$cnt].log\n\n";
                }

				open(OPTION_MAK, "< $srcDir/proj/mak/options_$muti_platform[$cnt].mak") or die "cannot read \"options.mak\" file\n";
				my @optionMakContent=<OPTION_MAK>;
				close(OPTION_MAK);	
				my $chipType;
				my $smallRom = 0;
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

					if ($line =~ /CHIP_TYPE \= /x)
					{
						$chipType = $';#'
						$chipType =~ s/\x0d\x0a//ig;
						chomp $chipType;
						if ($smallRom eq 1)
						{
							$chipType =~ s/^\__//;
							$chipType =~ s/$\__//;
							$chipType = $chipType."_64";
							$chipType = "__".$chipType."__";
						}
						last;
					}
				}

				#print SHELL_SCRIPT "  cd sc/libs\n";
				#print SHELL_SCRIPT "  mkdir $chipType\n";
				#print SHELL_SCRIPT "  cd ../..\n";

				#print SHELL_SCRIPT "  cd sc/libs/$chipType\n";
				#print SHELL_SCRIPT "  mkdir MStarStudio_UP\n";
				#print SHELL_SCRIPT "  mkdir MStarDeveloper\n";
				#print SHELL_SCRIPT "  cd MStarDeveloper\n";
				#print SHELL_SCRIPT "  mkdir debug\n";
				#print SHELL_SCRIPT "  cd ../../../..\n\n";

				print SHELL_SCRIPT "else\n";
				print SHELL_SCRIPT "	echo can not find $simulatorPath or $simulatorPath/$simulatorWorkSpace\n";
				print SHELL_SCRIPT "	exit 1\n";
				print SHELL_SCRIPT "fi\n\n";
				
				if($simuProduct eq $cus_product[$cnt])
				{
				    $lib_chipType = $chipType;
				    
    				print SHELL_SCRIPT "if [ -e tng/genSimulatorProj.pl ] && [ -e sc/customer/default/profile/$releaseConfigureXml ]; then\n";
    				print SHELL_SCRIPT "	echo exe tng/genSimulatorProj.pl\n";
    				print SHELL_SCRIPT "	tng/genSimulatorProj.pl sc/customer/default/profile/$releaseConfigureXml $simulatorPath/$simulatorWorkSpace ../../genCusLib.bat ../../backupCusLibs.bat $simulatorPath/Cus_ReleaseEnv2005_Template.bat\n\n";
    				print SHELL_SCRIPT "	tng/release_process/remove_lib_from_vcproj.pl\n";			
    				print SHELL_SCRIPT "	if [ -e SIMULATOR_ERROR.txt ]; then\n";
    				print SHELL_SCRIPT "	    echo somethig wrong in generating simulator project files.\n";
    				#print SHELL_SCRIPT "	    exit 1\n";
    				print SHELL_SCRIPT "	fi\n";				
    				print SHELL_SCRIPT "else\n";
    				print SHELL_SCRIPT "	echo can not find tng/genSimulatorProj.pl or sc/customer/default/profile/$releaseConfigureXml\n";
    				print SHELL_SCRIPT "	exit 1\n";
    				print SHELL_SCRIPT "fi\n\n";

    				print SHELL_SCRIPT "if [ -e ../../backupCusLibs.bat ]; then\n";
    				print SHELL_SCRIPT "	echo gen cus libs for backup simulator libs\n";
    				print SHELL_SCRIPT "	chmod 777 ../../backupCusLibs.bat\n";
    				print SHELL_SCRIPT "  echo -ne \"start time : \"\n";
    				print SHELL_SCRIPT "  date +%k:%M\n";				
    				print SHELL_SCRIPT "	../../backupCusLibs.bat $chipType > backupCusLibs_$cus_product[$cnt].log\n";
    				print SHELL_SCRIPT "  echo -ne \"end time : \"\n";
    				print SHELL_SCRIPT "  date +%k:%M\n";
    				print SHELL_SCRIPT "else\n";
    				print SHELL_SCRIPT "	echo can not find ../../backupCusLibs.bat\n";
    				print SHELL_SCRIPT "	exit 1\n";
    				print SHELL_SCRIPT "fi\n\n";
    				
    				#print SHELL_SCRIPT "cd SRC/proj\n";
    				#print SHELL_SCRIPT "rm MStarStudio_UP/lib/Debug/*.*\n\n";
    
    				#print SHELL_SCRIPT "rm MStarStudio_UP/MStarDeveloper/XMMI/debug/*.exe\n\n";
    				#print SHELL_SCRIPT "rm MStarStudio_UP/MStarDeveloper/XMMI/debug/*.lib\n\n";
			    }
			}
		}

		my $cnt = 0;
		for (0 ... $#cus_chipset)
		{
			print SHELL_SCRIPT "echo replace pattern for turn on compile options\n";
			print SHELL_SCRIPT "tng/replacePattern.pl config.mak $cus_chipset[$cnt] $cus_chipset[$#cus_chipset-$_]\n";
			$cnt = $#cus_chipset-$_;
	
			if ($cus_chipset[$cnt] =~ /ct/i)
			{
				print SHELL_SCRIPT "if [ -e tng/replaceOption.pl ] && [ -e mak/options_$cus_chipset[$cnt].mak ]; then\n";
				print SHELL_SCRIPT "	tng/replaceOption.pl mak/options_$cus_chipset[$cnt].mak \"LOG_LEVEL_CUT_OPTION = LOG_LEVEL_ALL\" \"LOG_LEVEL_CUT_OPTION = LOG_LEVEL_CRITICAL_ONLY\"\n";
				print SHELL_SCRIPT "fi\n\n";
			}
			
			print SHELL_SCRIPT "if [ -e tng/configure.pl ]; then\n";			
			print SHELL_SCRIPT "  tng/configure.pl $cus_chipset[$cnt]\n";
			print SHELL_SCRIPT "fi\n\n";
	
			print SHELL_SCRIPT "echo make build_chip_libs\n";
			if ($noFeedback =~ /yes/i)
			{			
				print SHELL_SCRIPT "echo -ne \"start time : \"\n";
				print SHELL_SCRIPT "date +%k:%M\n";
				print SHELL_SCRIPT "make csn csn2 build_preprocess build_chip_libs DISABLE_FEEDBACK=1 NO_DEBUG=1 2>&1 1>&make_$cus_chipset[$cnt].log\n\n";
				print SHELL_SCRIPT "make log > make_log_cmd_$cus_chipset[$cnt].log\n\n";
				print SHELL_SCRIPT "echo -ne \"end time : \"\n";
				print SHELL_SCRIPT "date +%k:%M\n";
			}
			else
			{
				print SHELL_SCRIPT "echo -ne \"start time : \"\n";
				print SHELL_SCRIPT "date +%k:%M\n";
				print SHELL_SCRIPT "make csn csn2 build_preprocess build_chip_libs 2>&1 1>&make_$cus_chipset[$cnt].log\n\n";
				print SHELL_SCRIPT "make log > make_log_cmd_$cus_chipset[$cnt].log\n\n";
				print SHELL_SCRIPT "echo -ne \"end time : \"\n";
				print SHELL_SCRIPT "date +%k:%M\n";
			}
	
			if (($noFeedback =~ /no/i) && ($relSim =~ /yes/i))
			{
				print SHELL_SCRIPT "if [ -e $simulatorPath ] && [ -e $simulatorPath/$simulatorWorkSpace ]; then\n";
                   
                print SHELL_SCRIPT "\n  echo -n \"========== Rebuild All: 107 succeeded, 0 failed, 0 skipped ==========\" > vs2005_r_$cus_chipset[$cnt].log\n\n";

				open(OPTION_MAK, "< $srcDir/proj/mak/options_$muti_chipset[$cnt].mak") or die "cannot read \"options.mak\" file\n";
				my @optionMakContent=<OPTION_MAK>;
				close(OPTION_MAK);	
				my $chipType;
				my $smallRom = 0;
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
	    
					if ($line =~ /CHIP_TYPE \= /x)
					{
						$chipType = $';#'
						$chipType =~ s/\x0d\x0a//ig;
						chomp $chipType;
						if ($smallRom eq 1)
						{
							$chipType =~ s/^\__//;
							$chipType =~ s/$\__//;
							$chipType = $chipType."_64";
							$chipType = "__".$chipType."__";
						}
						last;
					}
				}
	    
				#print SHELL_SCRIPT "  cd sc/libs\n";
				#print SHELL_SCRIPT "  mkdir $chipType\n";
				#print SHELL_SCRIPT "  cd ../..\n";
	    
				#print SHELL_SCRIPT "  cd sc/libs/$chipType\n";
				#print SHELL_SCRIPT "  mkdir MStarStudio_UP\n";
				#print SHELL_SCRIPT "  mkdir MStarDeveloper\n";
				#print SHELL_SCRIPT "  cd MStarDeveloper\n";
				#print SHELL_SCRIPT "  mkdir debug\n";
				#print SHELL_SCRIPT "  cd ../../../..\n\n";
	    	    
				print SHELL_SCRIPT "else\n";
				print SHELL_SCRIPT "	echo can not find $simulatorPath or $simulatorPath/$simulatorWorkSpace\n";
				print SHELL_SCRIPT "	exit 1\n";
				print SHELL_SCRIPT "fi\n\n";
			}
		}

		print SHELL_SCRIPT "if [ -e tng/release_process/clean.pl ]; then\n";
		print SHELL_SCRIPT "	echo clean temporarily obj\n";
		print SHELL_SCRIPT "	perl tng/release_process/clean.pl CUS_Folder MStarStudio_UP > ../../cleanCus.log\n";
		print SHELL_SCRIPT "	perl tng/release_process/clean.pl Simu_Output MStarStudio_UP/MStarDeveloper/XMMI/debug ../../SimuLibCheck/CmnDllList.txt > ../../cleanSimu.log\n";
		print SHELL_SCRIPT "else\n";
		print SHELL_SCRIPT "	echo can not find clean.pl \n";
		print SHELL_SCRIPT "fi\n\n";
		
		#print SHELL_SCRIPT "echo move lib and dll files \n";
		#print SHELL_SCRIPT "echo -ne \"start time : \"\n";
		#print SHELL_SCRIPT "date +%k:%M\n";
		#print SHELL_SCRIPT "mv -f sc/libs/$lib_chipType/MStarStudio_UP/*.* MStarStudio_UP/lib/Debug \n";
		#print SHELL_SCRIPT "mv -f sc/libs/$lib_chipType/MStarDeveloper/debug/*.* MStarStudio_UP/MStarDeveloper/XMMI/Debug \n\n";
		#print SHELL_SCRIPT "echo -ne \"end time : \"\n";
		#print SHELL_SCRIPT "date +%k:%M\n";
	}
				
	print SHELL_SCRIPT "echo finish full release\n";
	close(SHELL_SCRIPT);
}

sub genDeltaReleaseShell
{
	my $relRevision = shift;
	my $lastRevision = shift;
	my $relMmiRevision = shift;
	my $lastMmiRevision = shift;
	my $relCoreSwRevision = shift;
	my $lastCoreSwRevision = shift;
	my $svnRoot = shift;
	my $mmiSvnRoot = shift;
	my $coreSwRoot = shift;
	my $mmiDirectoriesStr = shift;
	my $coreDirectoriesStr = shift;
	my $SourceSvn = shift;
	my $MMISourceSvn = shift;
	my $CoreSwSourceSvn = shift;

	my @mmiDirectories = split(/;/, $mmiDirectoriesStr);
	my @coreDirectories = split(/;/, $coreDirectoriesStr);

	my $shellScript = "delta_release.sh";
	open(SHELL_SCRIPT, "> $shellScript") or die "cannot read \"$shellScript\" file\n";
	print SHELL_SCRIPT "#!/bin/bash\n\n";
	print SHELL_SCRIPT "sync\n\n";
	print SHELL_SCRIPT "rm del_files.txt\n";
	print SHELL_SCRIPT "rm -r -f delta\n";
	print SHELL_SCRIPT "mkdir delta\n\n";
	
	if (length($mmiDirectoriesStr) != 0)
	{
		for my $mmiDirectory (@mmiDirectories)
		{
			#print SHELL_SCRIPT "echo get MMI SW $mmiDirectory Change\n";
			#print SHELL_SCRIPT "svn log -v -r $relMmiRevision:$lastMmiRevision $MMISourceSvn/$mmiDirectory > ./rev.log\n";
			print SHELL_SCRIPT "tng/ParseSVNLog.pl rev.log $mmiSvnRoot delta_files.txt del_files.txt\n";
			print SHELL_SCRIPT "tng/copyUpdate.pl delta_files.txt delta\n";
			print SHELL_SCRIPT "rm rev.log\n";
			print SHELL_SCRIPT "rm delta_files.txt\n\n";
		}
	}
	if (length($coreDirectoriesStr) != 0)
	{
		for my $coreDirectory (@coreDirectories)
		{
			#print SHELL_SCRIPT "echo get Core SW $coreDirectory Change\n";
			#print SHELL_SCRIPT "svn log -v -r $relCoreSwRevision:$lastCoreSwRevision $CoreSwSourceSvn/$coreDirectory > ./rev.log\n";
			print SHELL_SCRIPT "tng/ParseSVNLog.pl rev.log $coreSwRoot delta_files.txt del_files.txt\n";
			print SHELL_SCRIPT "tng/copyUpdate.pl delta_files.txt delta\n";
			print SHELL_SCRIPT "rm rev.log\n";
			print SHELL_SCRIPT "rm delta_files.txt\n\n";
		}
	}
	print SHELL_SCRIPT "mv del_files.txt delta/del_files.txt\n\n";
	
	print SHELL_SCRIPT "echo Copy target lib\n";
	print SHELL_SCRIPT "cp -r sc/libs delta/sc\n";
	print SHELL_SCRIPT "echo Copy Simulator\n";
	print SHELL_SCRIPT "cp -r MStarStudio_Config delta\n\n";
	print SHELL_SCRIPT "echo Rename Customer folder\n";
	print SHELL_SCRIPT "echo finish delta release\n";
	close(SHELL_SCRIPT);
}

sub genCleanShell
{
	my $simulatorPath = shift;
	my $sourceDir = shift;
	my $simulatorWorkSpace = shift;

	my $shellScript = "clean.sh";
	open(SHELL_SCRIPT, "> $shellScript") or die "cannot read \"$shellScript\" file\n";
	print SHELL_SCRIPT "#!/bin/bash\n\n";
	print SHELL_SCRIPT "sync\n\n";
	print SHELL_SCRIPT "cd $sourceDir/proj\n";
	my $cnt = 0;
	print SHELL_SCRIPT "cp sc/customer/default/profile/$releaseConfigureXml sc/ReleaseConfigurations.xml\n";
	$simulatorWorkSpace =~ s/\./\_cus\./;

	if ($relBuild =~ /yes/i)
	{
		for (0 ... $#cus_product)
		{
			print SHELL_SCRIPT "tng/replacePattern.pl config.mak $cus_product[$cnt] $cus_product[$#cus_product-$_]\n";
			$cnt = $#cus_product-$_;
			print SHELL_SCRIPT "if [ -e build/$cus_product[$cnt]/out/$cus_product[$cnt]\.bin ]; then\n";
	
			#print SHELL_SCRIPT "	echo collect libraries\n";
			print SHELL_SCRIPT "  tng/configure.pl $cus_product[$cnt]\n";
			#print SHELL_SCRIPT "  make dlm_pre\n\n";
	
			#print SHELL_SCRIPT "	make SCM_clean 2>&1 1>&make_SCM_clean_$cus_product[$cnt].log\n";
			#print SHELL_SCRIPT "	rm -rf backup_src unused_src\n\n";
			#print SHELL_SCRIPT "	echo make clean\n";
			#print SHELL_SCRIPT "	make clean\n\n";
	
			#if ($noFeedback =~ /yes/i)
			#{
			#	print SHELL_SCRIPT "  echo -ne \"start time : \"\n";
			#	print SHELL_SCRIPT "  date +%k:%M\n";
			#	print SHELL_SCRIPT "	make csn csn2 build_preprocess build_chip_libs DISABLE_FEEDBACK=1 NO_DEBUG=1 2>&1 1>&make_SCM_clean_$cus_product[$cnt].log\n";
			#	print SHELL_SCRIPT "  echo -ne \"end time : \"\n";
			#	print SHELL_SCRIPT "  date +%k:%M\n";
			#}
			#else
			#{
			#	print SHELL_SCRIPT "  echo -ne \"start time : \"\n";
			#	print SHELL_SCRIPT "  date +%k:%M\n";
			#	print SHELL_SCRIPT "	make csn csn2 build_preprocess build_chip_libs 2>&1 1>&make_SCM_clean_$cus_product[$cnt].log\n";
			#	print SHELL_SCRIPT "  echo -ne \"start time : \"\n";
			#	print SHELL_SCRIPT "  date +%k:%M\n";
			#}
			
			#if ($relBuild =~ /yes/i)
			#{
				print SHELL_SCRIPT "	echo make release_build\n";
				print SHELL_SCRIPT "  echo -ne \"start time : \"\n";
				print SHELL_SCRIPT "  date +%k:%M\n";
				print SHELL_SCRIPT "	make release_fast 2>&1 1>&make_release_build_$cus_product[$cnt].log\n\n";	
				print SHELL_SCRIPT "  echo -ne \"end time : \"\n";
				print SHELL_SCRIPT "  date +%k:%M\n";
			#}

		print SHELL_SCRIPT "else\n";
		print SHELL_SCRIPT "	echo build failed\n";
		#print SHELL_SCRIPT "	exit 1\n";
		print SHELL_SCRIPT "fi\n\n";

		if ($relSim =~ /yes/i)
		{
			print SHELL_SCRIPT "echo Cus_ReleaseEnv2005.bat\n";
			print SHELL_SCRIPT "cd $simulatorPath\n";
			print SHELL_SCRIPT "chmod 755 Cus_ReleaseEnv2005.bat\n";
            if($ostype eq "msys"){
			    print SHELL_SCRIPT "cmd //c ./Cus_ReleaseEnv2005.bat 2>&1 1>&../../../vs2005_rve_$cus_product[$cnt].log\n";
            }else{
			    print SHELL_SCRIPT "./Cus_ReleaseEnv2005.bat 2>&1 1>&../../../vs2005_rve_$cus_product[$cnt].log\n";
			}
			print SHELL_SCRIPT "cd -\n\n";
    
			if ($relBuild =~ /yes/i)
			{
				print SHELL_SCRIPT "if [ -e $simulatorPath ] && [ -e $simulatorPath/$simulatorWorkSpace ]; then\n";
				print SHELL_SCRIPT "	echo use VisualStudio 2005 to open simulator sln and build all\n";
				print SHELL_SCRIPT "	cd $simulatorPath\n";
				print SHELL_SCRIPT "  echo -ne \"start time : \"\n";
				print SHELL_SCRIPT "  date +%k:%M\n";
				#print SHELL_SCRIPT "	/cygdrive/c/Program\\ Files/Xoreax/IncrediBuild/BuildConsole.exe $simulatorWorkSpace /CFG=\"Debug\|Win32\" /REBUILD 2>&1 1>&../../../vs2005_rb_$cus_product[$cnt].log\n";
				print SHELL_SCRIPT "  /cygdrive/c/Program\\ Files/Microsoft\\ Visual\\ Studio\\ 8/Common7/IDE/devenv.com $simulatorWorkSpace /clean 2>&1 1>&../../../../../vs2005_rb_clean_$cus_product[$cnt].log\n";
				print SHELL_SCRIPT "  echo -ne \"end time : \"\n";
				print SHELL_SCRIPT "  date +%k:%M\n";
				print SHELL_SCRIPT "  cd -\n";
				print SHELL_SCRIPT "else\n";
				print SHELL_SCRIPT "	echo can not find $simulatorPath or $simulatorPath/$simulatorWorkSpace\n";
				print SHELL_SCRIPT "	exit 1\n";
				print SHELL_SCRIPT "fi\n\n";
			}
		}
		else
		{
			print SHELL_SCRIPT "	rm -rf MStarStudio_Config MStarStudio_UP\n\n";	
		}
	}	

		my $cnt = 0;
		for (0 ... $#cus_chipset)
		{
			print SHELL_SCRIPT "tng/replacePattern.pl config.mak $cus_chipset[$cnt] $cus_chipset[$#cus_chipset-$_]\n";
			$cnt = $#cus_chipset-$_;
	
			print SHELL_SCRIPT "echo make release_build\n";
			print SHELL_SCRIPT "tng/configure.pl $cus_chipset[$cnt]\n";
			print SHELL_SCRIPT "echo -ne \"start time : \"\n";
			print SHELL_SCRIPT "date +%k:%M\n";
			print SHELL_SCRIPT "make release_fast 2>&1 1>&make_release_build_$cus_chipset[$cnt].log\n\n";	
			print SHELL_SCRIPT "echo -ne \"end time : \"\n";
			print SHELL_SCRIPT "date +%k:%M\n";
	
			if ($relSim =~ /yes/i)
			{
				print SHELL_SCRIPT "echo Cus_ReleaseEnv2005.bat\n";
				print SHELL_SCRIPT "cd $simulatorPath\n";
				print SHELL_SCRIPT "chmod 755 Cus_ReleaseEnv2005.bat\n";
				print SHELL_SCRIPT "./Cus_ReleaseEnv2005.bat 2>&1 1>&../../../vs2005_rve_$cus_chipset[$cnt].log\n";
				print SHELL_SCRIPT "cd -\n\n";
			    
				print SHELL_SCRIPT "if [ -e $simulatorPath ] && [ -e $simulatorPath/$simulatorWorkSpace ]; then\n";
				print SHELL_SCRIPT "	echo use VisualStudio 2005 to open simulator sln and build all\n";
				print SHELL_SCRIPT "	cd $simulatorPath\n";
				print SHELL_SCRIPT "  echo -ne \"start time : \"\n";
				print SHELL_SCRIPT "  date +%k:%M\n";
				#print SHELL_SCRIPT "	/cygdrive/c/Program\\ Files/Xoreax/IncrediBuild/BuildConsole.exe $simulatorWorkSpace /CFG=\"Debug\|Win32\" /REBUILD 2>&1 1>&../../../vs2005_rb_$cus_chipset[$cnt].log\n";
				print SHELL_SCRIPT "  /cygdrive/c/Program\\ Files/Microsoft\\ Visual\\ Studio\\ 8/Common7/IDE/devenv.com $simulatorWorkSpace /clean 2>&1 1>&../../../../../vs2005_rb_clean_$cus_chipset[$cnt].log\n";
				print SHELL_SCRIPT "  echo -ne \"end time : \"\n";
				print SHELL_SCRIPT "  date +%k:%M\n";				
				print SHELL_SCRIPT "  cd -\n";
				print SHELL_SCRIPT "else\n";
				print SHELL_SCRIPT "	echo can not find $simulatorPath or $simulatorPath/$simulatorWorkSpace\n";
				print SHELL_SCRIPT "	exit 1\n";
				print SHELL_SCRIPT "fi\n\n";
			}
			else
			{
				print SHELL_SCRIPT "	rm -rf MStarStudio_Config MStarStudio_UP\n\n";	
			}
		}
	}

	if ($noFeedback =~ /no/i) 
	{
			print SHELL_SCRIPT "echo Clean source files\n";
			#print SHELL_SCRIPT "tng/configure.pl $cus_product[$cnt]\n";
			print SHELL_SCRIPT "echo -ne \"start time : \"\n";
			print SHELL_SCRIPT "date +%k:%M\n";
			print SHELL_SCRIPT "make csn csn2 build_preprocess SCM_clean_source 2>&1 1>&make_SCM_clean_source_$cus_product[$cnt].log\n";
			print SHELL_SCRIPT "echo -ne \"end time : \"\n";
			print SHELL_SCRIPT "date +%k:%M\n";
			print SHELL_SCRIPT "rm -rf backup_src unused_src\n\n";
	}

	print SHELL_SCRIPT "if [ -e sc/customer/product/common/mak/version.mak ]; then\n";
	print SHELL_SCRIPT "  echo remove version.mak\n";
	print SHELL_SCRIPT "  rm ./sc/customer/product/common/mak/version.mak\n";
	print SHELL_SCRIPT "  echo remove cust_release.mak\n";
	#print SHELL_SCRIPT "  make -f tng/CustRelease.mak clean\n";
	print SHELL_SCRIPT "fi\n\n";

	print SHELL_SCRIPT "if [ -e tng/xmlFilter.pl ]; then\n";
	print SHELL_SCRIPT "	echo clean file list un-released item\n";
	print SHELL_SCRIPT "	tng/xmlFilter.pl sc/customer/default/profile/$releaseConfigureXml SRC_C_LIST\n";
	print SHELL_SCRIPT "	tng/xmlFilter.pl sc/customer/default/profile/$releaseConfigureXml SRC_ASM_LIST\n";
	print SHELL_SCRIPT "else\n";
	print SHELL_SCRIPT "	echo can not find tng/xmlFilter.pl\n";
	print SHELL_SCRIPT "	exit 1\n";
	print SHELL_SCRIPT "fi\n\n";
	
	print SHELL_SCRIPT "if [ -e tng/truncateFile.pl ]; then\n";
	print SHELL_SCRIPT "	echo clean mak files\n";
	print SHELL_SCRIPT "	tng/truncateFile.pl sc \"#Add files here\"\n";
	print SHELL_SCRIPT "else\n";
	print SHELL_SCRIPT "	echo can not find tng/truncateFile.pl\n";
	print SHELL_SCRIPT "	exit 1\n";
	print SHELL_SCRIPT "fi\n\n";
	
	print SHELL_SCRIPT "cd tng\n";
	print SHELL_SCRIPT "./CodeReleaseMaker.exe /C MAK /F ../sc/customer/default/profile/$releaseConfigureXml /O ../\n";
	print SHELL_SCRIPT "cd -\n\n";
	
	#To remove 3rd party folders unused.
	print SHELL_SCRIPT "cd sc/application/3rd\n";
	print SHELL_SCRIPT "rm -rf Embider\n";
	print SHELL_SCRIPT "cd -\n\n";
	
	print SHELL_SCRIPT "if [ -e Makefile_lint ]; then\n";
	print SHELL_SCRIPT "	rm Makefile_lint\n";
	print SHELL_SCRIPT "fi\n\n";
	print SHELL_SCRIPT "if [ -e tng/lint.mak ]; then\n";
	print SHELL_SCRIPT "	rm tng/lint.mak\n";
	print SHELL_SCRIPT "fi\n\n";
	print SHELL_SCRIPT "if [ -e tng/CodeReleaseMaker.exe ]; then\n";
	print SHELL_SCRIPT "	rm tng/CodeReleaseMaker.exe\n";
	print SHELL_SCRIPT "fi\n\n";

	print SHELL_SCRIPT "if [ -e tng/release_process/clean.pl ]; then\n";	
	print SHELL_SCRIPT "	perl tng/release_process/clean.pl All_File MStarStudio_UP/lib/Debug CmnLibList.txt > ../../cleanLib.log\n";
	print SHELL_SCRIPT "	perl tng/release_process/clean.pl Dll_File MStarStudio_UP/MStarDeveloper/XMMI/debug CmnDllList.txt > ../../cleanDll.log\n";
	#print SHELL_SCRIPT "	perl tng/release_process/clean.pl Exe_File MStarStudio_UP/MStarDeveloper/XMMI/debug CmnDllList.txt > ../../cleanExe.log\n";
	print SHELL_SCRIPT "	perl tng/release_process/clean.pl Simu_Output MStarStudio_UP/MStarDeveloper/XMMI/debug CmnDllList.txt > ../../cleanSimu.log\n";
	print SHELL_SCRIPT "	perl tng/release_process/clean.pl Dubug_Folder MStarStudio_UP/MStarKernel > ../../cleanDebug1.log\n";
	print SHELL_SCRIPT "	perl tng/release_process/clean.pl Dubug_Folder MStarStudio_UP/MStarModule > ../../cleanDebug2.log\n";
	print SHELL_SCRIPT "else\n";
	print SHELL_SCRIPT "	echo can not find clean.pl \n";
	print SHELL_SCRIPT "fi\n\n";

	print SHELL_SCRIPT "find sc/driver/drv/bluetooth/bt_host -iname *.h -exec rm -f {} \\;\n";
	print SHELL_SCRIPT "find sc/driver/drv/bluetooth/bt_host -iname *.c -exec rm -f {} \\;\n";
	print SHELL_SCRIPT "find sc/driver/drv/bluetooth/bt_mac -iname *.h -exec rm -f {} \\;\n";
	print SHELL_SCRIPT "find sc/driver/drv/bluetooth/bt_mac -iname *.c -exec rm -f {} \\;\n";
	print SHELL_SCRIPT "find sc/telserv -iname *.c -exec rm -f {} \\;\n";
	print SHELL_SCRIPT "find sc/telserv -iname *.l -exec rm -f {} \\;\n";
	print SHELL_SCRIPT "find sc/telserv -iname *.y -exec rm -f {} \\;\n";
	print SHELL_SCRIPT "find sc/telserv -iname *.awk -exec rm -f {} \\;\n";
	print SHELL_SCRIPT "find sc/telserv -iname *.simple -exec rm -f {} \\;\n\n";
	print SHELL_SCRIPT "find sc/system/rtk/src -iname mrgtmp* -exec rm -f {} \\;\n\n";
	
	print SHELL_SCRIPT "if [ -e tng/release_process/release_process/rmSimuFiles.pl ] && [ -e tng/release_process/release_process/processSimulator.txt ]; then\n";	
	print SHELL_SCRIPT "	perl tng/release_process/rmSimuFiles.pl\n";
	print SHELL_SCRIPT "else\n";
	print SHELL_SCRIPT "	echo can not find rmSimuFiles.pl or processSimulator.txt \n";
	print SHELL_SCRIPT "fi\n\n";
	
	print SHELL_SCRIPT "echo finish clean\n";
	close(SHELL_SCRIPT);
}


sub genOffShell
{
	my $simulatorPath = shift;
	my $sourceDir = shift;
	my $simulatorWorkSpace = shift;
	my $simuProduct = shift;

	my $shellScript = "off.sh";
	open(SHELL_SCRIPT, "> $shellScript") or die "cannot read \"$shellScript\" file\n";
	print SHELL_SCRIPT "#!/bin/bash\n\n";
	print SHELL_SCRIPT "sync\n\n";
	print SHELL_SCRIPT "cd $sourceDir/proj/tng\n";
	my $cnt = 0;
	
	print SHELL_SCRIPT "if [ -e releaseOp.pl ] && [ -e ReleaseOptions_Off.txt ]; then\n";
	print SHELL_SCRIPT "	perl releaseOp.pl ReleaseDeletedLibs_Off.txt $cus_product[0]\n";
	for (0 ... $#cus_product)
	{
		open(OPTION_MAK, "< $sourceDir/proj/mak/options_$muti_platform[$_].mak") or die "cannot read \"options.mak\" file\n";
		my @optionMakContent=<OPTION_MAK>;
		close(OPTION_MAK);	

		my $chipType;
		my $smallRom = 0;
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

			if ($line =~ /CHIP_TYPE \= /x)
			{
				$chipType = $';#'
				$chipType =~ s/\x0d\x0a//ig;
				chomp $chipType;
				$chipType =~ s/^\__//;
				$chipType =~ s/$\__//;
				if ($smallRom eq 1)
				{
					$chipType = $chipType."_64";
					#$chipType = "__".$chipType."__";
				}
				last;
			}
		}
		print SHELL_SCRIPT "	perl releaseOp.pl ReleaseOptions_Off.txt $cus_product[$_]\n";
		print SHELL_SCRIPT "	perl releaseOp.pl ReleaseOptions_Off_$chipType.txt $cus_product[$_]\n";
	}

	for (0 ... $#cus_chipset)
	{
		open(OPTION_MAK, "< $sourceDir/proj/mak/options_$muti_chipset[$_].mak") or die "cannot read \"options.mak\" file\n";
		my @optionMakContent=<OPTION_MAK>;
		close(OPTION_MAK);	

		my $chipType;
		my $smallRom = 0;
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

			if ($line =~ /CHIP_TYPE \= /x)
			{
				$chipType = $';
				$chipType =~ s/\x0d\x0a//ig;
				chomp $chipType;#'
				$chipType =~ s/^\__//;
				$chipType =~ s/$\__//;
				if ($smallRom eq 1)
				{
					$chipType = $chipType."_64";
					#$chipType = "__".$chipType."__";
				}
				last;
			}
		}
		print SHELL_SCRIPT "	perl releaseOp.pl ReleaseOptions_Off.txt $cus_chipset[$_]\n";
		print SHELL_SCRIPT "	perl releaseOp.pl ReleaseOptions_Off_$chipType.txt $cus_chipset[$_]\n\n";
	}
	
	open(KEEP_MAK, "< $sourceDir/proj/tng/release_process/keepProduct") or die "cannot read \"keepProduct\" file\n";
	my $keepProduct=<KEEP_MAK>;
	close(KEEP_MAK);
	
	my @keepProductName = split(/,/, $keepProduct);
	
	for (1 ... $#keepProductName)
	{
		open(OPTION_MAK, "< $sourceDir/proj/mak/options_$keepProductName[$_].mak") or die "cannot read \"options.mak\" file\n";
		my @optionMakContent=<OPTION_MAK>;
		close(OPTION_MAK);	

		my $chipType;
		my $smallRom = 0;
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

			if ($line =~ /CHIP_TYPE \= /x)
			{
				$chipType = $';
				$chipType =~ s/\x0d\x0a//ig;
				chomp $chipType;#'
				$chipType =~ s/^\__//;
				$chipType =~ s/$\__//;
				if ($smallRom eq 1)
				{
					$chipType = $chipType."_64";
					#$chipType = "__".$chipType."__";
				}
				last;
			}
		}
		my $cus_keepProduct = $keepProductName[$_];
		my @keepProductName_tmp = split(/\_/, $cus_keepProduct);
		$cus_keepProduct =~ s/\_$keepProductName_tmp[1]\_$keepProductName_tmp[2]//;
		
		print SHELL_SCRIPT "	perl releaseOp.pl ReleaseOptions_Off.txt $cus_keepProduct\n";
		print SHELL_SCRIPT "	perl releaseOp.pl ReleaseOptions_Off_$chipType.txt $cus_keepProduct\n\n";
	}

	open(OPTION_MAK, "< $sourceDir/proj/mak/options_$muti_platform[0].mak") or die "cannot read \"options.mak\" file\n";
	my @optionMakContent=<OPTION_MAK>;
	close(OPTION_MAK);	

	my $chipType;
	my $smallRom = 0;
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

		if ($line =~ /CHIP_TYPE \= /x)
		{
			$chipType = $';#'
			$chipType =~ s/\x0d\x0a//ig;
			chomp $chipType;
			$chipType =~ s/^\__//;
			$chipType =~ s/$\__//;
			if ($smallRom eq 1)
			{
				$chipType = $chipType."_64";
			}
			last;
		}
	}

	open(VER_MAK, "< $sourceDir/proj/sc/customer/product/common/mak/version.mak") or die "cannot read \"options.mak\" file\n";
	my @verMakContent=<VER_MAK>;
	close(VER_MAK);

	my $majVer;
	my $minVer;
	for my $line2 (@verMakContent)
	{
		$line2 =~ s/\s//g;
	
		if ($line2 =~ /SW_MAJ_VER\=/x)
		{
			$majVer = $';#'
			$majVer =~ s/\x0d\x0a//ig;
			chomp $majVer;
			$majVer =~ s/SW_MAJ_VER\=//;
			$majVer =~ s/0//;
		}
		if ($line2 =~ /SW_MIN_VER\=/x)
		{
			$minVer = $';#'
			$minVer =~ s/\x0d\x0a//ig;
			chomp $minVer;
			$minVer =~ s/SW_MIN_VER\=//;
		}
	}
	my $ver = $majVer.".".$minVer;

	print SHELL_SCRIPT "	cd ../sc/libs\n";
	#print SHELL_SCRIPT "	mkdir patchlog\n";
	print SHELL_SCRIPT "	rm patchlog/$ver.lib\n";
	print SHELL_SCRIPT "	cp \_\_$chipType\_\_/cus_app_sc.lib patchlog/\n";
	print SHELL_SCRIPT "	mv patchlog/cus_app_sc.lib patchlog/$ver.lib\n\n";


	print SHELL_SCRIPT "else\n";
	print SHELL_SCRIPT "	echo can not find releaseOp.pl or ReleaseOptions_Off.txt\n";
	print SHELL_SCRIPT "	exit 1\n";
	print SHELL_SCRIPT "fi\n\n";
	print SHELL_SCRIPT "cd ../..\n";

	if ($OffBuild =~ /yes/i)
	{
		$simulatorWorkSpace =~ s/\./\_cus\./;
		for (0 ... $#cus_product)
		{
			print SHELL_SCRIPT "tng/replacePattern.pl config.mak $cus_product[$cnt] $cus_product[$#cus_product-$_]\n";
			$cnt = $#cus_product-$_;
			print SHELL_SCRIPT "	echo make clean\n";
			print SHELL_SCRIPT "  tng/configure.pl $cus_product[$cnt]\n";
			print SHELL_SCRIPT "	make clean\n";
			print SHELL_SCRIPT "	echo make release_speed\n";
			print SHELL_SCRIPT "	echo -ne \"start time : \"\n";
			print SHELL_SCRIPT "	date +%k:%M\n";
			print SHELL_SCRIPT "	make release_fast 2>&1 1>&make_release_speed_$cus_product[$cnt].log\n\n";	
			print SHELL_SCRIPT "	echo -ne \"start time : \"\n";
			print SHELL_SCRIPT "	date +%k:%M\n";
	
			if (($relSim =~ /yes/i) && ($simuProduct eq $cus_product[$cnt]))
			{
				print SHELL_SCRIPT "if [ -e $simulatorPath ] && [ -e $simulatorPath/$simulatorWorkSpace ]; then\n";
				print SHELL_SCRIPT "	echo use VisualStudio 2005 to open simulator sln and build all\n";
				print SHELL_SCRIPT "	cd $simulatorPath\n";
				print SHELL_SCRIPT "	/cygdrive/c/Program\\ Files/Microsoft\\ Visual\\ Studio\\ 8/Common7/IDE/devenv.com $simulatorWorkSpace /rebuild 2>&1 1>&../../../vs2005_rs_$cus_product[$cnt].log\n";
				#print SHELL_SCRIPT "	/cygdrive/c/Program\\ Files/Xoreax/IncrediBuild/BuildConsole.exe $simulatorWorkSpace /CFG=\"Debug\|Win32\" /REBUILD 2>&1 1>&../../../vs2005_rs_$cus_product[$cnt].log\n";
				print SHELL_SCRIPT "	cd -\n";
				print SHELL_SCRIPT "else\n";
				print SHELL_SCRIPT "	echo can not find $simulatorPath or $simulatorPath/$simulatorWorkSpace\n";
				print SHELL_SCRIPT "	exit 1\n";
				print SHELL_SCRIPT "fi\n\n";
			}
			else
			{
				print SHELL_SCRIPT "	rm -rf MStarStudio_Config MStarStudio_UP\n\n";	
			}
		}


		for (0 ... $#cus_chipset)
		{
			print SHELL_SCRIPT "tng/replacePattern.pl config.mak $cus_chipset[$cnt] $cus_chipset[$#cus_chipset-$_]\n";
			$cnt = $#cus_product-$_;
			print SHELL_SCRIPT "	echo make clean\n";
			print SHELL_SCRIPT "  tng/configure.pl $cus_chipset[$cnt]\n";
			print SHELL_SCRIPT "	make clean\n";
			print SHELL_SCRIPT "	echo make release_speed\n";
			print SHELL_SCRIPT "	echo -ne \"start time : \"\n";
			print SHELL_SCRIPT "	date +%k:%M\n";
			print SHELL_SCRIPT "	make release_fast 2>&1 1>&make_release_speed_$cus_chipset[$cnt].log\n\n";	
			print SHELL_SCRIPT "	echo -ne \"end time : \"\n";
			print SHELL_SCRIPT "	date +%k:%M\n";
	
			if (($relSim =~ /yes/i) && ($simuProduct eq $cus_chipset[$cnt]))
			{
				print SHELL_SCRIPT "if [ -e $simulatorPath ] && [ -e $simulatorPath/$simulatorWorkSpace ]; then\n";
				print SHELL_SCRIPT "	echo use VisualStudio 2005 to open simulator sln and build all\n";
				print SHELL_SCRIPT "	cd $simulatorPath\n";
				print SHELL_SCRIPT "	/cygdrive/c/Program\\ Files/Microsoft\\ Visual\\ Studio\\ 8/Common7/IDE/devenv.com $simulatorWorkSpace /rebuild 2>&1 1>&../../../vs2005_rs_$cus_chipset[$cnt].log\n";
				#print SHELL_SCRIPT "	/cygdrive/c/Program\\ Files/Xoreax/IncrediBuild/BuildConsole.exe $simulatorWorkSpace /CFG=\"Debug\|Win32\" /REBUILD 2>&1 1>&../../../vs2005_rs_$cus_chipset[$cnt].log\n";
				print SHELL_SCRIPT "	cd -\n";
				print SHELL_SCRIPT "else\n";
				print SHELL_SCRIPT "	echo can not find $simulatorPath or $simulatorPath/$simulatorWorkSpace\n";
				print SHELL_SCRIPT "	exit 1\n";
				print SHELL_SCRIPT "fi\n\n";
			}
			else
			{
				print SHELL_SCRIPT "	rm -rf MStarStudio_Config MStarStudio_UP\n\n";	
			}
		}
	}
	print SHELL_SCRIPT "cd $simulatorPath\n";
	print SHELL_SCRIPT "mv -f debug/*.exe ../../lib/debug/\n";
	print SHELL_SCRIPT "mv -f debug/*.dll ../../lib/debug/\n";
	print SHELL_SCRIPT "cd ../../..\n\n";
	
	print SHELL_SCRIPT "./tng/release_process/copyAudioTable.pl\n\n";
	print SHELL_SCRIPT "echo finish off\n";
	close(SHELL_SCRIPT);
}



sub parseReleaseNote
{
	my $curReleaseNote = shift;
	open(RELEASE_NOTE, "< $curReleaseNote") or die "cannot read \"$curReleaseNote\" file\n";
	my @content=<RELEASE_NOTE>;
	close(RELEASE_NOTE);
	
	my $relRevision;
	my $relMmiRevision;
	my $relCoreSwRevision;
	my $relCommDocToolRevision;
	my $lastRevision;
	my $lastMmiRevision;
	my $lastCoreSwRevision;
	my $lastCommDocToolRevision;
	my $platform;
	my $chipset;
	my $product;
	my $srcSvn;
	my $srcDir;
	my $releaseType;
	my $simulatorPath;
	my $simulatorWorkSpace;
	my $svnRoot;
	my $mmiSvnRoot;
	my $coreSwRoot;
	my $CommDocToolRoot;
	my $mmiDirectories;
	my $coreDirectories;
	my $svnUserName;
	my $svnUserPassword;
	my $MMIsrcSvn;
	my $CoreSWsrcSvn;
	my $CommDocToolSvn;
	my $relTo;
	my $relPD;
	my $simulatorProduct;

	for my $line (@content)
	{
		if ($line =~ /ReleaseRevision\=/)
		{
			$relRevision = $';#'
			$relRevision =~ s/\x0d\x0a//ig;
			chomp $relRevision;
			print "Setup release rev: $relRevision\n";
		}
		elsif ($line =~ /ReleaseMmiRevision\=/)
		{
			$relMmiRevision = $';#'
			$relMmiRevision =~ s/\x0d\x0a//ig;
			chomp $relMmiRevision;
			print "Setup mmi release rev: $relMmiRevision\n";
		}
		elsif ($line =~ /ReleaseCoreSwRevision\=/)
		{
			$relCoreSwRevision = $';#'
			$relCoreSwRevision =~ s/\x0d\x0a//ig;
			chomp $relCoreSwRevision;
			print "Setup core sw release rev: $relCoreSwRevision\n";
		}
		elsif ($line =~ /ReleaseCommDocToolRevision\=/)
		{
			$relCommDocToolRevision = $';#'
			$relCommDocToolRevision =~ s/\x0d\x0a//ig;
			chomp $relCommDocToolRevision;
			print "Setup common docs tools release rev: $relCommDocToolRevision\n";
		}
		elsif ($line =~ /LastRevision\=/)
		{
			$lastRevision = $';#'
			$lastRevision =~ s/\x0d\x0a//ig;
			chomp $lastRevision;
			print "Setup last release rev: $lastRevision\n";
		}
		elsif ($line =~ /LastMmiRevision\=/)
		{
			$lastMmiRevision = $';#'
			$lastMmiRevision =~ s/\x0d\x0a//ig;
			chomp $lastMmiRevision;
			print "Setup last mmi release rev: $lastMmiRevision\n";
		}
		elsif ($line =~ /LastCoreSwRevision\=/)
		{
			$lastCoreSwRevision = $';#'
			$lastCoreSwRevision =~ s/\x0d\x0a//ig;
			chomp $lastCoreSwRevision;
			print "Setup last core sw release rev: $lastCoreSwRevision\n";
		}
		elsif ($line =~ /LastCommDocToolRevision\=/)
		{
			$lastCommDocToolRevision = $';#'
			$lastCommDocToolRevision =~ s/\x0d\x0a//ig;
			chomp $lastCommDocToolRevision;
			print "Setup last common docs tools release rev: $lastCommDocToolRevision\n";
		}
		elsif ($line =~ /Platform\=/)
		{
			$platform = $';#'
			$platform =~ s/\x0d\x0a//ig;
			chomp $platform;
			print "Setup plaform: $platform\n";
			@muti_platform = split(/,/, $platform);
		}
		elsif ($line =~ /Chipset\=/)
		{
			$chipset = $';#'
			$chipset =~ s/\x0d\x0a//ig;
			chomp $chipset;
			print "Setup Chipset: $chipset\n";
			@muti_chipset = split(/,/, $chipset);
		}
		elsif ($line =~ /^Product\=/)
		{
			$product = $';#'
			$product =~ s/\x0d\x0a//ig;
			chomp $product;
			print "Setup product: $product\n";
		}
		elsif ($line =~ /SourceDir\=/)
		{
			$srcDir = $';#'
			$srcDir =~ s/\x0d\x0a//ig;
			chomp $srcDir;
			print "Setup source code directory: $srcDir\n";
		}
		elsif ($line =~ /MMISourceSvn\=/)
		{
			$MMIsrcSvn = $';#'
			$MMIsrcSvn =~ s/\x0d\x0a//ig;
			chomp $MMIsrcSvn;
			print "MMI SVN: $MMIsrcSvn\n";
		}
		elsif ($line =~ /CoreSwSourceSvn\=/)
		{
			$CoreSWsrcSvn = $';#'
			$CoreSWsrcSvn =~ s/\x0d\x0a//ig;
			chomp $CoreSWsrcSvn;
			print "Core SW SVN: $CoreSWsrcSvn\n";
		}
		elsif ($line =~ /CommDocToolSvn\=/)
		{
			$CommDocToolSvn = $';#'
			$CommDocToolSvn =~ s/\x0d\x0a//ig;
			chomp $CommDocToolSvn;
			print "Core Common Docs Tools SVN: $CommDocToolSvn\n";
		}
		elsif ($line =~ /SourceSvn\=/)
		{
			$srcSvn = $';#'
			$srcSvn =~ s/\x0d\x0a//ig;
			chomp $srcSvn;
			print "Setup SVN: $srcSvn\n";
		}
		elsif ($line =~ /Release\=/)
		{
			$releaseType = $';#'
			$releaseType =~ s/\x0d\x0a//ig;
			chomp $releaseType;
			print "Setup release type: $releaseType\n";
		}
		elsif ($line =~ /SimulatorPath\=/)
		{
			$simulatorPath = $';#'
			$simulatorPath =~ s/\x0d\x0a//ig;
			chomp $simulatorPath;
			print "Setup simulator path: $simulatorPath\n";
		}
		elsif ($line =~ /SimulatorWorkSpace\=/)
		{
			$simulatorWorkSpace = $';#'
			$simulatorWorkSpace =~ s/\x0d\x0a//ig;
			chomp $simulatorWorkSpace;
			print "Setup simulator workspace: $simulatorWorkSpace\n";
		}
		elsif ($line =~ /MMISvnRoot\=/)
		{
			$mmiSvnRoot = $';#'
			$mmiSvnRoot =~ s/\x0d\x0a//ig;
			chomp $mmiSvnRoot;
			print "Setup mmi svn root: $mmiSvnRoot\n";
		}
		elsif ($line =~ /CoreSwSvnRoot\=/)
		{
			$coreSwRoot = $';#'
			$coreSwRoot =~ s/\x0d\x0a//ig;
			chomp $coreSwRoot;
			print "Setup core sw svn root: $coreSwRoot\n";
		}
		elsif ($line =~ /CommDocToolSvnRoot\=/)
		{
			$CommDocToolRoot = $';#'
			$CommDocToolRoot =~ s/\x0d\x0a//ig;
			chomp $CommDocToolRoot;
			print "Setup common Docs Tools svn root: $CommDocToolRoot\n";
		}
		elsif ($line =~ /SvnRoot\=/)
		{
			$svnRoot = $';#'
			$svnRoot =~ s/\x0d\x0a//ig;
			chomp $svnRoot;
			print "Setup svn root: $svnRoot\n";
		}
		elsif ($line =~ /MMIDirectories\=/)
		{
			$mmiDirectories = $';#'
			$mmiDirectories =~ s/\x0d\x0a//ig;
			chomp $mmiDirectories;
			print "Setup mmi directories: $mmiDirectories\n";
		}
		elsif ($line =~ /CoreDirectories\=/)
		{
			$coreDirectories = $';#'
			$coreDirectories =~ s/\x0d\x0a//ig;
			chomp $coreDirectories;
			print "Setup core sw directories: $coreDirectories\n";
		}
		elsif ($line =~ /SvnUserName\=/)
		{
			$svnUserName = $';#'
			$svnUserName =~ s/\x0d\x0a//ig;
			chomp $svnUserName;
			print "Setup svn login username: $svnUserName\n";
		}
		elsif ($line =~ /SvnPassword\=/)
		{
			$svnUserPassword = $';#'
			$svnUserPassword =~ s/\x0d\x0a//ig;
			chomp $svnUserPassword;
			print "Setup svn login password\n";
		}
		elsif ($line =~ /ReleaseCode\=/)
		{
			$relCode = $';#'
			$relCode =~ s/\x0d\x0a//ig;
			chomp $relCode;
			print "Code release: $relCode\n";
		}
		elsif ($line =~ /ReleaseSimulator\=/)
		{
			$relSim = $';#'
			$relSim =~ s/\x0d\x0a//ig;
			chomp $relSim;
			print "Simulator release: $relSim\n";
		}
		elsif ($line =~ /ReleaseTool\=/)
		{
			$relTool = $';#'
			$relTool =~ s/\x0d\x0a//ig;
			chomp $relTool;
			print "Tool release: $relTool\n";
		}
		elsif ($line =~ /ReleaseDoc\=/)
		{
			$relDoc = $';#'
			$relDoc =~ s/\x0d\x0a//ig;
			chomp $relDoc;
			print "Document release: $relDoc\n";
		}
		elsif ($line =~ /ReleaseTo\=/)
		{
			$relTo = $';#'
			$relTo =~ s/\x0d\x0a//ig;
			chomp $relTo;
			print "Release to: $relTo\n";
		}
		elsif ($line =~ /ReleasePD\=/)
		{
			$relPD = $';#'
			$relPD =~ s/\x0d\x0a//ig;
			chomp $relPD;
			print "Release PD: $relPD\n";
		}
		elsif ($line =~ /FileListChangeStop\=/)
		{
			$fileListChangeStop = $';#'
			$fileListChangeStop =~ s/\x0d\x0a//ig;
			chomp $fileListChangeStop;
			print "File list change stop: $fileListChangeStop\n";
		}
		elsif ($line =~ /OffBuild\=/)
		{
			$OffBuild = $';#'
			$OffBuild =~ s/\x0d\x0a//ig;
			chomp $OffBuild;
			print "Off Option Build: $OffBuild\n";
		}
		elsif ($line =~ /RelBuild\=/)
		{
			$relBuild = $';#'
			$relBuild =~ s/\x0d\x0a//ig;
			chomp $relBuild;
			print "Release Build: $relBuild\n";
		}
		elsif ($line =~ /NoFeedback\=/)
		{
			$noFeedback = $';#'
			$noFeedback =~ s/\x0d\x0a//ig;
			chomp $noFeedback;
			print "No Feedback Build: $noFeedback\n";
		}
		elsif ($line =~ /SimulatorProduct\=/)
		{
			$simulatorProduct = $';#'
			$simulatorProduct =~ s/\x0d\x0a//ig;
			chomp $simulatorProduct;
			print "Simulator Product: $simulatorProduct\n";
		}
	}
	for (0 ... $#muti_platform)
	{
		$cus_product[$_] = $muti_platform[$_];
		my @productName = split(/\_/, $cus_product[$_]);
		#$cus_product[$_] = $productName[0]."_".$productName[3];
		$cus_product[$_] =~ s/\_$productName[1]\_$productName[2]//;
	}
	for (0 ... $#muti_chipset)
	{
		$cus_chipset[$_] = $muti_chipset[$_];
		my @chipsetName = split(/\_/, $cus_chipset[$_]);
		#$cus_chipset[$_] = $chipsetName[0]."_".$chipsetName[3];
		$cus_chipset[$_] =~ s/\_$chipsetName[1]\_$chipsetName[2]//;
	}
	if (length($simulatorProduct) != 0)
	{
		my @simuProd = split(/\_/, $simulatorProduct);
		$simulatorProduct =~ s/\_$simuProd[1]\_$simuProd[2]//;
	}
	if ((length($relPD) == 0) && ($relCode =~ /yes/i))
	{
		print "!! Please Fill in \"ReleasePD\" field !!\n";
	}
	else
	{
		if (length($srcDir) != 0)
		{
			genAutoReleaseShell($srcDir, $srcSvn, $MMIsrcSvn, $CoreSWsrcSvn, $CommDocToolSvn);
		}
		
		#if ((length($srcSvn) != 0) && (length($srcDir) != 0) && (length($relMmiRevision) != 0))
		if ((length($srcDir) != 0) && (length($relMmiRevision) != 0))
		{
			genExportShell($srcSvn, $srcDir, $MMIsrcSvn, $relMmiRevision, $relTo, $svnUserName, $svnUserPassword);
		}
		
		if ((length($product) != 0) && (length($simulatorPath) != 0) && (length($simulatorWorkSpace) != 0))
		{
			genCreateProjectShell($platform.",".$chipset, $product, $simulatorPath, $simulatorWorkSpace, $relPD, $srcDir);
		}
		
		if (length($releaseType) != 0)
		{
			genReleaseShell($releaseType);
		}
		
		if ((length($simulatorPath) != 0) && (length($simulatorWorkSpace) != 0))
		{
			genFullReleaseShell($simulatorPath, $simulatorWorkSpace, $srcDir, $relPD, $simulatorProduct);
		}
		
		if (length($simulatorPath) != 0)
		{
			genCleanShell($simulatorPath, $srcDir, $simulatorWorkSpace);
		}

		if (length($simulatorPath) != 0)
		{
			genOffShell($simulatorPath, $srcDir, $simulatorWorkSpace, $simulatorProduct);
		}
		
		genDeltaReleaseShell($relRevision, $lastRevision, $relMmiRevision, $lastMmiRevision, 
			$relCoreSwRevision, $lastCoreSwRevision, $svnRoot, $mmiSvnRoot, $coreSwRoot, $mmiDirectories, $coreDirectories, 
			$srcSvn, $MMIsrcSvn, $CoreSWsrcSvn, $CommDocToolSvn, $relCommDocToolRevision, $lastCommDocToolRevision, $CommDocToolRoot);	
	}
}

parseReleaseNote($releaseNote);
