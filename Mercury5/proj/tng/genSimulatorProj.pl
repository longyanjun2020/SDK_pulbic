#!/usr/bin/perl

use warnings;
use strict;
use File::Copy;

# tng/genSimulatorProj.pl sc/customer/default/profile/ReleaseConfigurations_CUS_B3.xml MStarStudio_Up/MStarDeveloper/XMMI/MMI_BuildAll.sln ../../genCusLib.bat ../../backupCusLibs.bat MStarStudio_Up/MStarDeveloper/XMMI/Cus_ReleaseEnv2005_Template.bat

my %used;

# get input release level configuration file name
my $src_release_config_xml = shift;

# get simulator build all sln
my $buildAllSlnName = shift;

# get cust project file name
my $custLibShellFile = shift;

my $backupLibBatFile = shift;

my $releaseEnv2005_template = shift;

my $B3vcprojPath = ""; #App_mmi_B3.vcproj
my $G1vcprojPath = ""; #App_mmi_3G.vcproj

my @releaseSrc;
my @cusVcProjFiles;
my @unchangedVcProjFiles;
my @removedVcProjFiles;

my @cusLibs;

# prdefined source c release list
my @predSrcRel      =(  "mae_unittest.cpp"
                        ,"e2p_symbol_win32.c"
                        );

my @backupLibs      = ( "libCommom.lib"
                        #,"MKDev_bat.lib" # linked in DLL
                        #,"MKDev_e2p.lib" # linked in DLL
                        #,"MKDev_RPC.lib" # linked in DLL
                        #,"MKDev_sim.lib" # linked in DLL
                        #,"MKDev_SMG.lib" # linked in DLL
                        #,"MKDev_V24.lib" # linked in DLL
                        #,"MKernelOpec.lib" # linked in DLL
                        #,"MKernelOpic.lib" # linked in DLL
                        ,"VDev_FlashNand.lib"
                        #,"VDev_Fms.lib" # linked in DLL
                        #,"VDev_Keypad.lib" # linked in DLL
                        #,"MKernelWin32.dll"
                        #,"MKDev_NetWork.lib" # linked in DLL
                        ,"Tts.lib"
                        #,"Java_Oakmont.lib"
                        ,"mmaudio.lib"
                        ,"SysTime.lib"
                        ,"Hook.lib"
                        ,"UnitTestApp.lib"
                        ,"MKernelWin32Lib.lib" #"XSysKernelLib.vcproj"
                        ,"MKernelWin32Common.lib" #"XSysKernelCommon.vcproj"
                        );
                        
my @simulatorProj   = ( "libCommom.vcproj"
                        ,"MKDev_bat.vcproj"
                        ,"MKDev_e2p.vcproj"
                        ,"MKDev_RPC.vcproj"
                        ,"MKDev_sim.vcproj"
                        ,"MKDev_SMG.vcproj"
                        ,"MKDEV_V24.vcproj"
                        ,"MStarKernelOpec.vcproj"
                        ,"MStarKernelOpic.vcproj"
                        ,"VDev_FlashNand.vcproj"
                        ,"VDev_E2p.vcproj"
                        ,"ResizableLib.vcproj"
                        ,"Msim_NetWork.vcproj"
                        ,"MSSimConsole.vcproj"
                        ,"MStarSimulator.vcproj"
                        #,"Tts.vcproj"
                        #,"Oakmont.vcproj"
                        ,"mmaudio.vcproj"
                        ,"SysTime.vcproj"
                        ,"Hook.vcproj"
                        ,"UnitTestApp.vcproj"
                        ,"tencentmcareadp.vcproj"
                        ,"XSysKernelLib.vcproj"
                        ,"XSysKernelCommon.vcproj"
                        );
                        
my @cusReleaseEnvCommands;

my $cmd;
my $tagState = 0;
my $tagData;
#0 NONE, wait start tag
#1 Parse start tag, wait data
#2 Parse data, wait end tag

# step1. parse start tag
# step2. parse data
# step3. parse end tag
# step4. return data
sub parseXmlTag
{
	my $line=shift;
	my $pattern=shift;
	
	if ($tagState == 0)
	{
		$tagData = "";
		if ($line =~ /\<$pattern\>/)
		{
			$line =~ s/\<$pattern\>//;
			$tagState = 1;
		}
	}
	
	if ($tagState == 1)
	{
		if ($line =~ /\<\/$pattern\>/)
		{
			$line =~ s/\<\/$pattern\>//;
			if (length($line) != 0)
			{				
				$tagData = $line;
				$tagState = 0;
				return $tagData;
			}
		}
		elsif ($line =~ /\<\/$pattern\>/)
		{
			die "error end tag";
		}
		else
		{
			$tagData = $line;
			$tagState = 2;
		}
	}
	
	if ($tagState == 2)
	{
		if ($line =~ /\<\/$pattern\>/)
		{
			$tagState = 0;
			return $tagData;
		}
		else
		{
			die "error end tag, expected $pattern";
		}
	}
}

my $parseXmlState=0;
my $removeFileName;
#0 NONE, wait filename
#1 Parse filename, wait default_value

# step1. parse tag file_name
# step2. get file name
# step3. parse tag default_value
# step4. check if release level is not REL_SRC_C_LIST
# step5. add removed list
sub parseXml
{
	my $line=shift;
	if ($parseXmlState == 0)
	{
		$removeFileName = parseXmlTag($line, "file_name");
		if (length($removeFileName) != 0)
		{
			$parseXmlState = 1;
		}
	}
	elsif ($parseXmlState == 1)
	{
		my $value = parseXmlTag($line, "default_value");
		if (length($removeFileName) != 0)
		{
			chomp $removeFileName;
			$removeFileName =~ s/|\x20|\x09//g;
			if ($value =~ /REL_SRC_C_LIST/)
			{
				push @releaseSrc, $removeFileName;
			}
			$parseXmlState = 0;
		}
	}
}

my $tmpLine = "";
my $isRemoved = 1;
my $inSession = 0;
my @genCustLibBatchFileContent;
my $hasFileRemovedInProj = 0;

# step1. filter tag <file
# step2. parse XXX.c
# step3. check if XXX.c in removed list
# step4. return original line if not in removed list or return empty line
sub parserProjTag
{
	my $line = shift;
	my $projPath = shift;
	
	if ($inSession == 0)
	{
		$isRemoved = 1;
		if ($line =~ /\<Files|\<FileConfiguration/)
		{
			return $line;
		}
		elsif ($line =~ /\<File/)
		{
			$tmpLine = $line;
			$inSession = 1;
			return "";
		}
	}
	elsif ($inSession == 1)
	{
		$tmpLine = $tmpLine.$line;
		if ($line =~ /\<\/File\>/)
		{
			my $result = "";
			if ($isRemoved == 0)
			{
			 	$result = $tmpLine;
			}
			else
			{
				my $objName = $tmpLine;
				chomp $objName;
				my $ttmm = $objName;
				$objName =~ s/\.cpp/\.obj/;
				$objName =~ s/\.c/\.obj/;
				if ($objName =~ /[0-9a-zA-Z_]+\.obj/)
				{
					$objName = $projPath."Debug/".$&;
					my $destFile = $projPath."Cus";
					#print "copy $objName to $destFile\n";
					#copy obj file from debug to cus for customer libs
					copy($objName,$destFile);
					
                    if ($ttmm =~ /[0-9a-zA-Z_]+\.cpp/)
                    {
                        print "RelLib: $&\n";
                    }
                    elsif ($ttmm =~ /[0-9a-zA-Z_]+\.c/)
                    {
                        print "RelLib: $&\n";
					}					
				}
				$hasFileRemovedInProj = 1;
			}
			$tmpLine = "";
			$isRemoved = 1;
			$inSession = 0;
			return $result;
		}
		elsif ($line =~ /RelativePath=/)
		{
			$line =~ s/RelativePath=//;
			$line =~ s/\"|\x20|\x09//g;
			my $filename = $line;

			$filename =~ s/\\/\//g;
			if (($filename =~ /[0-9a-zA-Z_]+\.cpp/) || ($filename =~ /[0-9a-zA-Z_]+\.c/))
			{
				$filename = $&;
				for my $source (@releaseSrc)
				{
					if (($isRemoved == 1) and ($filename eq $source))
					{
						$isRemoved = 0;
						print "RelSrc: $filename\n";
						last;
					}
				}
				if ($line !~ /^..\\..\\..\\..\\sc/)
				{
				    if($line =~ /^\.\.\\ati1\\src\\/)
				    {
				        print "RelLib[2]: $filename\n";
				    }
				    elsif($line =~ /^\.\.\\ati1\\src\\/)
				    {
				        print "RelLib[2]: $filename\n";
				    }
				    elsif($line =~ /^\.\.\\vml1\\src\\/)
				    {
				        print "RelLib[2]: $filename\n";
				    }
				    elsif($line =~ /^\.\.\\vml2\\src\\/)
				    {
				        print "RelLib[2]: $filename\n";
				    }
				    elsif($line =~ /^\.\\src\\mmt_sign_fakeWin32\.c/)
				    {
				        print "RelLib[2]: $filename\n";
				    }				    
				    elsif($line =~ /^\.\\src\\ati_mandatory_main_msim\.c/)
				    {
				        print "RelLib[2]: $filename\n";
				    }				    
				    else
				    {
				        print "RelSrc[2]: $filename\n";
				        print "Warning!! please check again!\n";
					$isRemoved = 0;
				    }
				}
			}
			else
			{
				$isRemoved = 0;
			}
			return "";
		}
		return "";
	}
	return $line;
}

# step1. read XXX_cus.vcproj
# step2. add XXX_cus.lib to AdditionalDependencies
# step3. save file
sub addDependencyInProj
{
	my $projName = shift;
	my $libName = shift;
	my @projContent;

	open(PROJFILE, "$projName") or die "cannot read \"$projName\" file\n";
	@projContent=<PROJFILE>;
	close(PROJFILE);
	
	$libName =~ s/[0-9a-zA-Z_\.]+lib/$&/;
	
	open(OUTPUT_PROJFILE, "> $projName") or die "cannot read \"$projName\" file\n";
	
	if ($projName =~ /App_mmi/)
	{
		for my $line (@projContent)
		{
			if ($line =~ /AdditionalDependencies\=/)
			{
				my $header = $`.$&;
				my $parameters = $';#'
				$parameters =~ s/\x0D\x0A//;
				$parameters =~ s/\"//g;

				if ($libName =~ /[0-9a-zA-Z_]+\.lib/)
				{
					$parameters = "\"$parameters $&\"";
					print OUTPUT_PROJFILE $header.$parameters."\n";
				}
				else
				{
					die "bad library name\n";
				}
			}
			else
			{
				print OUTPUT_PROJFILE "$line";
			}
		}
	}
	else
	{
		for my $line (@projContent)
		{
			print OUTPUT_PROJFILE "$line";
			if ($line =~ /VCLibrarianTool/)
			{
				if ($libName =~ /[0-9a-zA-Z_]+\.lib/)
				{
					print OUTPUT_PROJFILE "				AdditionalDependencies=\"../../../lib/Debug/$&\"\n"
				}
				else
				{
					die "bad library name\n";
				}
			}
		}
	}
	close(OUTPUT_PROJFILE);	
}

# step1. read vcproj content from XXX.vcproj file
# step2. get vcproj file path
# step3. create cus folder if not exist
# step4. parse vcproj content line by line to fiter out removed sources
# step5. save removed sources ito XXX_cus.vcproj
sub removeSrcFromProj
{
	my $filename = shift;
	my @projContent;
	
	$hasFileRemovedInProj = 0;
	#print "open proj file: $filename\n";
	open(PROJFILE, "$filename") or die "cannot read \"$filename\" file\n";
	@projContent=<PROJFILE>;
	close(PROJFILE);

	#get vcproj path
	my $projPath = $filename;
	$projPath =~ s/[0-9a-zA-Z_]+\.vcproj//;
	$projPath =~ s/\\/\//g;

	if($filename =~ /App_mmi_B3\.vcproj/)
	{
	    $B3vcprojPath = $filename;
	}
	if($filename =~ /App_mmi_3G\.vcproj/)
	{
	    $G1vcprojPath = $filename;
	}

	#create cus folder
	my $folderName = $projPath."Cus";
	if (-e $folderName)
	{
	}
	else
	{
		print "create dir ".$projPath."Cus\n";
		mkdir ($projPath."Cus");
	}

	#update vcproj file
	my $cusProjFileName = $filename;
	print "\n\nRelPrj: $filename\n";
	$cusProjFileName =~ s/\.vcproj/_cus\.vcproj/g;
	open(OUTPUT_PROJFILE, "> $cusProjFileName") or die "cannot read \"$cusProjFileName\" file\n";
	for my $line (@projContent)
	{
		my $output = parserProjTag($line, $projPath);
		print OUTPUT_PROJFILE "$output";
	}
	close(OUTPUT_PROJFILE);	
	
	#add command in batch file only if some source files are removed from vcproj
	if ($hasFileRemovedInProj == 1)
	{
		open(SOURCES, "$filename") or die "cannot read \"$filename\" file\n";
		my @vcProjContent=<SOURCES>;
		close(SOURCES);
		
		my $foundLibName = 0;
		my $foundProjectHeader = 0;
		my $tmpLine;
		my $libName;
		for my $line (@vcProjContent)
		{
			if ($foundLibName == 0)
			{
				if ($line =~ /VisualStudioProject/)
				{
					$line =~ s/\x0D\x0A//;
					$tmpLine = $line;
					$foundProjectHeader = 1;
				}
				elsif (($foundProjectHeader == 1) && ($line =~ /\>/))
				{
					if ($tmpLine =~ /Name\=\"[0-9a-zA-Z_]+\"/)
					{
						$foundLibName = 1;
						$libName = $&;
						$libName =~ s/Name\=//;
						$libName =~ s/\"//g;
					}
				}
				else
				{
					$line =~ s/\x0D\x0A//;
					$tmpLine = $tmpLine.$line;
				}
			}
		}
				
		#check if this is a empty vcproj
		open(CUS_PROJFILE, "$cusProjFileName") or die "cannot read \"$cusProjFileName\" file\n";
		my @cusProjContent=<CUS_PROJFILE>;
		close(CUS_PROJFILE);
		my $hasSource = 0;
		for my $srcFile (@cusProjContent)
		{
			if ($hasSource == 0)
			{
				if (($srcFile =~ /[0-9a-zA-Z_]+\.cpp/) || ($srcFile =~ /[0-9a-zA-Z_]+\.c/))
				{
					$hasSource = 1;
				}
			}
		}
		if ($hasSource == 1)
		{
			push @genCustLibBatchFileContent, "echo generating $libName\_cus\.lib\n";
			push @genCustLibBatchFileContent, "lib.exe /nologo /NODEFAULTLIB /out:./MStarStudio_UP/lib/Debug/$libName\_cus\.lib ./".$projPath."Cus/*.obj\n";
    		    
			#add dependency in vcproj file
			addDependencyInProj($cusProjFileName, $libName."_cus\.lib");
			push @cusVcProjFiles, $cusProjFileName;
			print "cus project $cusProjFileName\n";

			print "ERROR: The vcproject contents \"source release files\" and \"lib release files\".\n";
			print "ERROR: Please help to check $filename.\n";

			if (! -e "../../SimuVCProjFail.txt")
			{
			    open(ERRORFILE, ">../../SimuVCProjFail.txt") or die "cannot open SimuVCProjFail.txt\n";
			    print ERRORFILE "ERROR: Please help to check full_release.log.\n";
			    close(ERRORFILE);			
			}

			if ($foundLibName == 1)
			{
				push @cusLibs, $libName;
				push @backupLibs, "$libName\_cus\.lib";
			}
			else
			{
				die "can not find name in vc project file";
			}
		}
		else
		{
			my $vcProjName = $filename;
			if ($vcProjName =~ /[0-9a-zA-Z_]+\.vcproj/)
			{
				$vcProjName = $&;
				$vcProjName =~ s/\.vcproj//;
				unlink $cusProjFileName;
				push @removedVcProjFiles, $vcProjName;
				print "found empty project $vcProjName\n";								
			}
			else
			{
				die "error! wrong vcproj name\n";
			}
			if ($foundLibName == 1)
			{
				push @backupLibs, "$libName\.lib";
			}
			else
			{
				die "can not find name in vc project file";
			}
		}
	}
	else
	{
		print "unchanged project $cusProjFileName\n";
		push @unchangedVcProjFiles, $filename;
		unlink $cusProjFileName;
	}
	return $hasFileRemovedInProj;
}

sub removeSimulatorProjFromSln
{
	my $buildAllSln = shift;
	my $cusBuildAllSln = shift;
	open(CUST_SLN_FILE, "$buildAllSln") or die "cannot read \"$buildAllSln\" file\n";
	my @slnContent=<CUST_SLN_FILE>;
	close(CUST_SLN_FILE);
	
	my $skipEndProject = 0;
	
	open(CUST_SLN_FILE, "> $cusBuildAllSln") or die "cannot read \"$cusBuildAllSln\" file\n";
	for my $line (@slnContent)
	{
		my $found = 0;
		if ($line =~ /\.vcproj/)
		{
			$skipEndProject = 0;
			if ($found == 0)
			{
				for my $projName (@simulatorProj)
				{
					if (($found == 0) && ($line =~ /$projName/))
					{
						$found = 1;
						$skipEndProject = 1;
						print "remove project $projName from sln\n";
					}
				}
			}
		}
		elsif ($skipEndProject == 1)
		{
			$found = 1;
			my $tmpLine = $line;
			$tmpLine =~ s/\x0D\x0A//i;
			#print "remove $line from sln\n";
			if ($tmpLine eq "EndProject")
			{
				$skipEndProject = 0;
			}
		}
		if ($found == 0)
		{
			print CUST_SLN_FILE $line;
		}
	}
	close(CUST_SLN_FILE);
}

# step1. read build all sln content
# step2. parse vcproj in sln
# step3. call removeSrcFromProj to removed sources
# step4. check if changed
# step5. if changed, put vcproj name in changed list
# step6. parse sln content and updated changed vcproj name
# step7. save build all sln as XXX_cus.sln
sub updateProj
{
	my $buildAllSln = shift;
	my @slnContent;
	my @backupSlnContent;
	my $tempBuildAllSln = $buildAllSln;
	
	$tempBuildAllSln =~ s/\.sln/_temp\.sln/;
	removeSimulatorProjFromSln($buildAllSln, $tempBuildAllSln);

	open(SOURCES, "$tempBuildAllSln") or die "cannot read \"$tempBuildAllSln\" file\n";
	@slnContent=<SOURCES>;
	close(SOURCES);	
	@backupSlnContent = @slnContent;
	#read all vcproj files from sln	
	for my $line (@slnContent)
	{
		if ($line =~ /\"[0-9a-zA-Z_\.\\]+vcproj\"/)
		{
			$line = $&;
			my $projName = $line;
			$line =~ s/\"//g;
			if ($line =~ /\.\.\\\.\.\\/)
			{
				$line =~ s/\.\.\\\.\.\\/MStarStudio_UP\\/;
			}
			elsif ($line =~ /\.\.\\/)
			{
				$line =~ s/\.\.\\/MStarStudio_UP\\MStarDeveloper\\/;
			}
			#print "find project: $line\n";
			
			#read vcproj file, remove not release sources, save as new vcproj file
			removeSrcFromProj($line);
		}
	}

	# update App_mmi_B3.vcproj and App_mmi_3G.vcproj
	if(( -e $B3vcprojPath) || ( -e $G1vcprojPath))
	{
	    my $path;
	    my $flag = 0;
	    
	    if( -e $B3vcprojPath)
	    {
	        $path = $B3vcprojPath;
	    }
	    else
	    {
	        $path = $G1vcprojPath;
	    }
		open(PROJFILE, "$path") or die "cannot read \"$path\" file\n";
		my @projContent=<PROJFILE>;
		close(PROJFILE);
		
		open(PROJFILE, ">$path") or die "cannot read \"$path\" file\n";
		for my $linedata (@projContent)
		{
		    if($flag == 0)
		    {
                if ($linedata =~ /AdditionalDependencies\=/)		    
                {
                    $flag = 1;
        			for my $libName (@backupLibs)
        			{
        				if (($libName !~ /MStarMDL1/) && ($libName !~ /MStarMDL2/) && ($libName !~ /MKernelWin32Common/) && ($libName !~ /MKernelWin32Lib/))
        				{
        					if($linedata =~ /$libName/)
        					{
        					    next;
        					}
        					if($libName =~ /_cus\.lib/)
        					{
        					    next;
        					}
        					if( -e "MStarStudio_UP/lib/Debug/$libName")
        					{
        					    $linedata =~ s/ / $libName /;
        					}
        				}
        			}                
                }
            }
			print PROJFILE $linedata;
		}
		close(PROJFILE);
	}
	
	for my $projName (@cusVcProjFiles)
	{
		open(PROJFILE, "$projName") or die "cannot read \"$projName\" file\n";
		my @projContent=<PROJFILE>;
		close(PROJFILE);
		
		open(PROJFILE, ">$projName") or die "cannot read \"$projName\" file\n";
		for my $srcFile (@projContent)
		{
			for my $libName (@cusLibs)
			{
				if (($libName !~ /MStarMDL1/) && ($libName !~ /MStarMDL2/))
				{
					$srcFile =~ s/$libName\.lib/$libName\.lib $libName\_cus\.lib/;
				}
			}
			print PROJFILE $srcFile;
		}
		close(PROJFILE);
	}

	#write cus build all sln
	my $cusBuildAllSln = $buildAllSln;
	$cusBuildAllSln =~ s/\.sln/_cus\.sln/;
	open(CUST_SLN_FILE, "> $cusBuildAllSln") or die "cannot read \"$cusBuildAllSln\" file\n";
	my $skipEndProject = 0;
	
	for my $line (@backupSlnContent)
	{
		my $found = 0;
		if ($line =~ /\.vcproj/)
		{
			$skipEndProject = 0;
			for my $cusProjName (@cusVcProjFiles)
			{
				if ($cusProjName =~ /[0-9a-zA-Z_]+\_cus\.vcproj/)
				{
					my $projName = $&;
					$projName =~ s/\_cus\.vcproj/\.vcproj/;
					#print "compare $projName $line\n";
					if (($line =~ /$projName/) and ($found == 0))
					{
						#change XXX.vcproj to XXX_cus.vcproj
						#print "found $projName changed\n";
						$found = 1;
						$line =~ s/\.vcproj/_cus\.vcproj/;
						print CUST_SLN_FILE $line;
					}
				}
			}
			if ($found == 0)
			{
				for my $projName (@removedVcProjFiles)
				{
					if (($line =~ /$projName\.vcproj/) and ($found == 0))
					{
						my $vcProjPath = $`;
						$found = 1;
						$skipEndProject = 1;
						if ($vcProjPath =~ /MStarKernel\\[0-9a-zA-Z_]+/)
						{
							my $dirName = $&;
							my $delDir = $';#'
							$dirName =~ s/\\/\//;
							$delDir =~ s/\\//g;
							push @cusReleaseEnvCommands, "cd $dirName\n";
							push @cusReleaseEnvCommands, "rmdir /S /Q $delDir\n";
							push @cusReleaseEnvCommands, "cd ..\\..\\\n";
						}
					}
				}
			}
		}
		elsif ($skipEndProject == 1)
		{
			$found = 1;
			$line =~ s/\x0D\x0A//i;
			#print "remove $line from sln\n";
			if ($line eq "EndProject")
			{
				$skipEndProject = 0;
			}
		}
		if ($found == 0)
		{
			print CUST_SLN_FILE $line;
		}
	}
	close(CUST_SLN_FILE);
}

#read release levels from xml configuration file
sub parseReleaseConfig
{
	open(SOURCES, "< $src_release_config_xml") or die "cannot read \"$src_release_config_xml\" file\n";
	while(my $line = <SOURCES>)
	{
		parseXml($line);
	}
	#update build all sln file
	updateProj($buildAllSlnName);
}

for my $file (@predSrcRel)
{
    push @releaseSrc, $file;
}

parseReleaseConfig();

#generate batch file to generate customer libs
open(GEN_CUST_LIB_BATCH_FILE, "> $custLibShellFile") or die "cannot read \"$custLibShellFile\" file\n";
print GEN_CUST_LIB_BATCH_FILE "PUSHD C:\n";
print GEN_CUST_LIB_BATCH_FILE "cd\\\n";
print GEN_CUST_LIB_BATCH_FILE "cd Program Files/Microsoft Visual Studio 8/Common7/Tools/\n";
print GEN_CUST_LIB_BATCH_FILE "call \"vsvars32.bat\"\n";
print GEN_CUST_LIB_BATCH_FILE "cd ../../../..\n";
print GEN_CUST_LIB_BATCH_FILE "POPD\n";

for my $cusFiles (@genCustLibBatchFileContent)
{   
	print GEN_CUST_LIB_BATCH_FILE "$cusFiles";
}

print GEN_CUST_LIB_BATCH_FILE "echo finished\n";
close(GEN_CUST_LIB_BATCH_FILE);

# backup lib files
open(BKUP_LIB_BATCH_FILE, "> $backupLibBatFile") or die "cannot read \"$backupLibBatFile\" file\n";
print BKUP_LIB_BATCH_FILE "set ChipName=%1\n\n";
for my $libFile (@backupLibs)
{
    $cmd = "./MStarStudio_UP/lib/Debug/$libFile ./sc/libs/%ChipName%/MStarStudio_UP/$libFile\n\n";
    $cmd =~ s/\//\\/g;
    $cmd = "move /Y ".$cmd;
    print BKUP_LIB_BATCH_FILE "$cmd";
}

# remove dll files
$cmd = "./MStarStudio_UP/MStarDeveloper/XMMI/debug/MStarMDL1.dll\n\n";
$cmd =~ s/\//\\/g;
$cmd = "del /F /Q ".$cmd;
print BKUP_LIB_BATCH_FILE "$cmd";
$cmd = "./MStarStudio_UP/MStarDeveloper/XMMI/debug/MStarMDL2.dll\n\n";
$cmd =~ s/\//\\/g;
$cmd = "del /F /Q ".$cmd;
print BKUP_LIB_BATCH_FILE "$cmd";    
$cmd = "./MStarStudio_UP/MStarDeveloper/XMMI/debug/MStarMMI.dll\n\n";
$cmd =~ s/\//\\/g;
$cmd = "del /F /Q ".$cmd;
print BKUP_LIB_BATCH_FILE "$cmd";   
$cmd = "./MStarStudio_UP/MStarDeveloper/XMMI/debug/MKernelWin32.dll\n\n";
$cmd =~ s/\//\\/g;
$cmd = "del /F /Q ".$cmd;
print BKUP_LIB_BATCH_FILE "$cmd";
# backup *.dll and *.exe files
$cmd = "./MStarStudio_UP/MStarDeveloper/XMMI/debug/*.dll ./sc/libs/%ChipName%/MStarDeveloper/debug/\n\n";
$cmd =~ s/\//\\/g;
$cmd = "move /Y ".$cmd;
print BKUP_LIB_BATCH_FILE "$cmd";
$cmd = "./MStarStudio_UP/MStarDeveloper/XMMI/debug/*.exe ./sc/libs/%ChipName%/MStarDeveloper/debug/\n\n";
$cmd =~ s/\//\\/g;
$cmd = "move /Y ".$cmd;
print BKUP_LIB_BATCH_FILE "$cmd";
print BKUP_LIB_BATCH_FILE "echo finished\n";
close(BKUP_LIB_BATCH_FILE);

# gen common lib list
system ("rm -f ./CmnLibList.txt");
open(CMN_LIB_LIST_FILE, "> ./CmnLibList.txt") or die "cannot read \"CmnLibList.txt\" file\n";
for my $libFile (@backupLibs)
{
    print CMN_LIB_LIST_FILE "$libFile\n";    
}
close(CMN_LIB_LIST_FILE);

# gen common dll list
system ("rm -f ./CmnDllList.txt");
open(CMN_DLL_LIST_FILE, "> ./CmnDllList.txt") or die "cannot read \"CmnDllList.txt\" file\n";
opendir PRD, "./MStarStudio_UP/MStarDeveloper/XMMI/debug/" or die "cannot access product in \"", "./MStarStudio_UP/MStarDeveloper/XMMI/debug/", "\"\n";
for my $prd (sort(readdir(PRD)))
{
	if($prd =~ /\.dll$/)
	{
	    if($prd =~ /MStarMDL1.dll/)
	    {
	        next;
	    }
	    if($prd =~ /MStarMDL2.dll/)
	    {
	        next;
	    }
	    if($prd =~ /MStarMMI.dll/)
	    {
	        next;
	    }
	    if($prd =~ /MKernelWin32.dll/)
	    {
	        next;
	    }

        print CMN_DLL_LIST_FILE "$prd\n";    
	}   	
}
closedir PRD;
close(CMN_DLL_LIST_FILE);

open(RELEASE_ENV, "$releaseEnv2005_template") or die "cannot read \"$releaseEnv2005_template\" file\n";
my @releaseEnvContent=<RELEASE_ENV>;
close(RELEASE_ENV);

$releaseEnv2005_template =~ s/_template//i;
open(RELEASE_ENV, "> $releaseEnv2005_template") or die "cannot read \"$releaseEnv2005_template\" file\n";
for my $command (@releaseEnvContent)
{
	print RELEASE_ENV "$command";
	if ($command =~ /\:Step140/)
	{
		for my $cusCommand (@cusReleaseEnvCommands)
		{
			print RELEASE_ENV "$cusCommand";
		}
	}
}
close(RELEASE_ENV);

open(RELEASE_FILES, "> releaseFiles.txt") or die "cannot read \"releaseFiles.txt\" file\n";
for my $releaseSourceFilename (@releaseSrc)
{
	print RELEASE_FILES "$releaseSourceFilename";
}
close(RELEASE_FILES);
