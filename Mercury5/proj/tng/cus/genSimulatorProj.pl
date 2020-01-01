#!/usr/bin/perl

use warnings;
use strict;
use File::Copy;

my %used;

# get input release level configuration file name
my $src_release_config_xml = shift;

# get simulator build all sln
my $buildAllSlnName = shift;

# get cust project file name
my $custLibShellFile = shift;

my $releaseEnv2005_template = shift;

# get source directory name
my $sourceDirectoryName = shift;

my @releaseSrc;

my @cusVcProjFiles;
my @unchangedVcProjFiles;
my @removedVcProjFiles;

my @cusLibs;
my @dependentCusLibs;

my @backupFiles=("libCommom.lib", "MKDev_bat.lib", "MKDev_e2p.lib", "MKDev_NetWork.lib", "MKDev_RPC.lib", "MKDev_sim.lib", "MKDev_SMG.lib", "MKDev_V24.lib", "MKernelOpec.lib", "MKernelOpic.lib", "MKernelWin32.lib", "MKernelWin32.dll", "VDev_FlashNand.lib", "VDev_Fms.lib", "VDev_Keypad.lib", "App_Storage.lib");
my @cusReleaseEnvCommands;

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
				$objName =~ s/\.cpp/\.obj/;
				$objName =~ s/\.c/\.obj/;
				if ($objName =~ /[0-9a-zA-Z_]+\.obj/)
				{
					$objName = $projPath."Debug/".$&;
					my $destFile = $projPath."Cus";
					#print "copy $objName to $destFile\n";
					#copy obj file from debug to cus for customer libs
					copy($objName,$destFile);
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
	print "!!write ".$projName."\n";
	if ($projName =~ /App_mmi/)
	{
		print "App_mmi ".$projName."\n";
		for my $line (@projContent)
		{
			if ($line =~ /AdditionalDependencies\=/)
			{
				my $header = $`.$&;
				my $parameters = $';
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
		my $libFlag = 0;
		for my $line (@projContent)
		{
			if ($line =~ /AdditionalDependencies\=/)
			{
				my $header = $`.$&;
				my $parameters = $';
				$parameters =~ s/\x0D\x0A//;
				$parameters =~ s/\x0A//;
				$parameters =~ s/\"//g;
				if ($libName =~ /[0-9a-zA-Z_]+\.lib/)
				{
					$parameters = "\"$parameters ../../../lib/Debug/$&\"";
					print OUTPUT_PROJFILE $header.$parameters."\n";
				}
				else
				{
					die "bad library name\n";
				}
				$libFlag = 0;
			}
			else
			{
				if($libFlag == 1)
				{
					if ($libName =~ /[0-9a-zA-Z_]+\.lib/)
					{
						print OUTPUT_PROJFILE "				AdditionalDependencies=\"../../../lib/Debug/$&\"\n"
					}
					else
					{
						die "bad library name\n";
					}
					$libFlag = 0;
				}
				print OUTPUT_PROJFILE "$line";
				if ($line =~ /VCLibrarianTool/)
				{
					$libFlag = 1;
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
	my $sourceDirectory = shift;
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
	$cusProjFileName =~ s/\.vcproj/_cus\.vcproj/g;
	open(OUTPUT_PROJFILE, "> $cusProjFileName") or die "cannot read \"$cusProjFileName\" file\n";
	print "!!write ".$cusProjFileName."\n";
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
		
		push @genCustLibBatchFileContent, "echo generating $libName\_cus2\.lib\n";
		push @genCustLibBatchFileContent, "lib.exe /nologo /NODEFAULTLIB /out:$sourceDirectory/proj/MStarStudio_UP/lib/Debug/$libName\_cus2\.lib $sourceDirectory/proj/".$projPath."Cus/*.obj\n";
		
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
			#add dependency in vcproj file
			addDependencyInProj($cusProjFileName, $libName."_cus2\.lib");
			push @cusVcProjFiles, $cusProjFileName;
			print "cus project $cusProjFileName\n";
			if ($foundLibName == 1)
			{
				push @cusLibs, $libName;
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
				push @dependentCusLibs, $libName;
				push @backupFiles, "$libName\_cus2\.lib";
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
	my @simulatorProj = ("XSysMain.vcproj", "libCommom.vcproj", "MStarKernelOpec.vcproj", "MStarKernelOpic.vcproj", "VDev_FlashNand.vcproj", "VDev_E2p.vcproj", "ResizableLib.vcproj", "MKDev_e2p.vcproj", "Msim_NetWork.vcproj", "MKDev_sim.vcproj", "MKDev_RPC.vcproj", "MKDev_SMG.vcproj", "MKDEV_V24.vcproj", "MSSimConsole.vcproj", "MKDev_bat.vcproj", "MStarSimulator.vcproj");
	open(CUST_SLN_FILE, "$buildAllSln") or die "cannot read \"$buildAllSln\" file\n";
	my @slnContent=<CUST_SLN_FILE>;
	close(CUST_SLN_FILE);
	
	my $skipEndProject = 0;
	
	open(CUST_SLN_FILE, "> $cusBuildAllSln") or die "cannot read \"$cusBuildAllSln\" file\n";
	print "!!write ".$cusBuildAllSln."\n";
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
	my $sourceDir = shift;
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
			removeSrcFromProj($line, $sourceDir);
		}
	}
	
	for my $projName (@cusVcProjFiles)
	{
		open(PROJFILE, "$projName") or die "cannot read \"$projName\" file\n";
		my @projContent=<PROJFILE>;
		close(PROJFILE);
		
		open(PROJFILE, ">$projName") or die "cannot read \"$projName\" file\n";
		print "!!write ".$projName."\n";
		for my $srcFile (@projContent)
		{
			for my $libName (@dependentCusLibs)
			{
				if (($libName !~ /MStarMDL1/) && ($libName !~ /MStarMDL2/))
				{
					if($srcFile =~ /$libName\.lib $libName\_cus\.lib/i)
					{
						$srcFile =~ s/$libName\.lib $libName\_cus\.lib/$libName\_cus\.lib $libName\_cus2\.lib/i;
					}
					else
					{
						if($srcFile =~ /$libName\.lib/i)
						{
							$srcFile =~ s/$libName\.lib/$libName\_cus2\.lib/i;
						}
						elsif($srcFile =~ /$libName\_cus\.lib/i)
						{
							$srcFile =~ s/$libName\_cus\.lib/$libName\_cus2\.lib/i;
						}
					}
				}
			}
			for my $libName (@cusLibs)
			{
				if (($libName !~ /MStarMDL1/) && ($libName !~ /MStarMDL2/))
				{
					if($srcFile =~ /$libName\.lib $libName\_cus\.lib/i)
					{
						$srcFile =~ s/$libName\.lib $libName\_cus\.lib/$libName\.lib $libName\_cus\.lib $libName\_cus2\.lib/i;
					}
					else
					{
						if($srcFile =~ /$libName\.lib/i)
						{
							$srcFile =~ s/$libName\.lib/$libName\.lib $libName\_cus2\.lib/i;
						}
					}
				}
			}
			print PROJFILE $srcFile;
		}
		close(PROJFILE);
	}
	for my $projName (@unchangedVcProjFiles)
	{
		open(PROJFILE, "$projName") or die "cannot read \"$projName\" file\n";
		my @projContent=<PROJFILE>;
		close(PROJFILE);
		
		open(PROJFILE, ">$projName") or die "cannot read \"$projName\" file\n";
		print "!!write ".$projName."\n";
		for my $srcFile (@projContent)
		{
			for my $libName (@dependentCusLibs)
			{
				if (($libName !~ /MStarMDL1/) && ($libName !~ /MStarMDL2/))
				{
					$srcFile =~ s/$libName\.lib/$libName\_cus2\.lib/i;
				}
			}
			for my $libName (@cusLibs)
			{
				if (($libName !~ /MStarMDL1/) && ($libName !~ /MStarMDL2/))
				{
					if ($srcFile =~ /$libName\.lib $libName\_cus\.lib/i)
					{
						$srcFile =~ s/$libName\.lib $libName\_cus\.lib/$libName\.lib $libName\_cus\.lib $libName\_cus2\.lib/i;
					}
					elsif ($srcFile =~ /$libName\.lib/i)
					{
						$srcFile =~ s/$libName\.lib/$libName\.lib $libName\_cus2\.lib/i;
					}
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
	print "\n!!write ".$cusBuildAllSln."\n";
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
							my $delDir = $';
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
	updateProj($buildAllSlnName, $sourceDirectoryName);
}

parseReleaseConfig();

#generate batch file to generate customer libs
open(GEN_CUST_LIB_BATCH_FILE, "> $custLibShellFile") or die "cannot read \"$custLibShellFile\" file\n";
print "!!write ".$custLibShellFile."\n";
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

#print GEN_CUST_LIB_BATCH_FILE "cd $sourceDirectoryName/MStarStudio_Config/lib/Debug\n";
#for my $simulatorFile (@backupFiles)
#{
#	print GEN_CUST_LIB_BATCH_FILE "echo copy $simulatorFile\n";
#	print GEN_CUST_LIB_BATCH_FILE "copy $simulatorFile ..\\Backup\n";
#}
#print GEN_CUST_LIB_BATCH_FILE "cd ../../../../\n";
	
#print GEN_CUST_LIB_BATCH_FILE "link.exe /OUT:$sourceDirectoryName/proj/MStarStudio_UP/lib/Debug/MStarMDL1.dll /NOLOGO /LIBPATH:$sourceDirectoryName/proj/MStarStudio_UP/lib /LIBPATH:$sourceDirectoryName/proj/MStarStudio_UP/lib/Debug /DLL /DEF:$sourceDirectoryName/proj/MStarStudio_UP/MStarKernel/App/MDL1/App_mdl1.def /DEBUG /SUBSYSTEM:WINDOWS /MACHINE:X86 /ERRORREPORT:PROMPT MKernelWin32.lib App_vml1_cus.lib App_ati1_cus.lib libCommom.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $sourceDirectoryName/proj/MStarStudio_UP/MStarKernel/App/MDL1/CUS/*.obj\n";
#print GEN_CUST_LIB_BATCH_FILE "link.exe /OUT:$sourceDirectoryName/proj/MStarStudio_UP/lib/Debug/MStarMDL2.dll /NOLOGO /LIBPATH:$sourceDirectoryName/proj/MStarStudio_UP/lib /LIBPATH:$sourceDirectoryName/proj/MStarStudio_UP/lib/Debug /DLL /DEF:$sourceDirectoryName/proj/MStarStudio_UP/MStarKernel/App/MDL2/App_mdl2.def /DEBUG /SUBSYSTEM:WINDOWS /MACHINE:X86 /ERRORREPORT:PROMPT MKernelWin32.lib App_vml2_cus.lib App_ati2_cus.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $sourceDirectoryName/proj/MStarStudio_UP/MStarKernel/App/MDL2/CUS/*.obj\n";
print GEN_CUST_LIB_BATCH_FILE "echo finished\n";
close(GEN_CUST_LIB_BATCH_FILE);


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
