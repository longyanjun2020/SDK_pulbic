#!/usr/bin/perl

use warnings;
use strict;

# tng/release_process/checkVCProj.pl  

# prdefined source c release list
my @myPredSrcRel    =(  "mae_unittest.cpp"
                        ,"e2p_symbol_win32.c"
                        );

my @mySimulatorProj   = ( "libCommom.vcproj"
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
                        ,"Tts.vcproj"
                        #,"Oakmont.vcproj"
                        ,"mmaudio.vcproj"
                        ,"SysTime.vcproj"
                        ,"Hook.vcproj"
                        ,"UnitTestApp.vcproj"
                        ,"tencentmcareadp.vcproj"
                        ,"XSysKernelLib.vcproj"
                        ,"XSysKernelCommon.vcproj"
                        );

my @myReleaseSrc;

my $srcReleaseConfigXml = "sc/customer/default/profile/ReleaseConfigurations_CUS_B3.xml";
my $vcBuildAllSlnName = "MStarStudio_Up/MStarDeveloper/XMMI/MMI_BuildAll.sln";

my $hasFileRemovedInVCProj = 0;

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
				push @myReleaseSrc, $removeFileName;
			}
			$parseXmlState = 0;
		}
	}
}

my $tmpLine = "";
my $isRemoved = 1;
my $inSession = 0;
my @genCustLibBatchFileContent;

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
                    if ($ttmm =~ /[0-9a-zA-Z_]+\.cpp/)
                    {
                        print "RelLib: $&\n";
                    }
                    elsif ($ttmm =~ /[0-9a-zA-Z_]+\.c/)
                    {
                        print "RelLib: $&\n";
					}					
				}
				$hasFileRemovedInVCProj = 1;
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
				for my $source (@myReleaseSrc)
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

# step1. read vcproj content from XXX.vcproj file
# step2. get vcproj file path
# step3. create cus folder if not exist
# step4. parse vcproj content line by line to fiter out removed sources
# step5. save removed sources ito XXX_cus.vcproj
sub myRemoveSrcFromProj
{
	my $filename = shift;
	my @projContent;
	my @cusProjContent;
	
	$hasFileRemovedInVCProj = 0;
	#print "open proj file: $filename\n";
	open(PROJFILE, "$filename") or die "cannot read \"$filename\" file\n";
	@projContent=<PROJFILE>;
	close(PROJFILE);

	#get vcproj path
	my $projPath = $filename;
	$projPath =~ s/[0-9a-zA-Z_]+\.vcproj//;
	$projPath =~ s/\\/\//g;

	#update vcproj file
	my $cusProjFileName = $filename;
	print "\n\nRelPrj: $filename\n";
	open(OUTPUT_PROJFILE, "<$filename") or die "cannot read \"$filename\" file\n";
	for my $line (@projContent)
	{
		my $output = parserProjTag($line, $projPath);
		push @cusProjContent, $output;
	}
	close(OUTPUT_PROJFILE);
	
	#add command in batch file only if some source files are removed from vcproj
	if ($hasFileRemovedInVCProj == 1)
	{			
		#check if this is a empty vcproj
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
			print "ERROR: Found cus project: $cusProjFileName\n";
			print "ERROR: The vcproject contents \"source release files\" and \"lib release files\".\n";
			print "ERROR: Please help to check $filename.\n";
		}
		else
		{
			my $vcProjName = $filename;
			if ($vcProjName =~ /[0-9a-zA-Z_]+\.vcproj/)
			{
				print "Found empty project $vcProjName\n";								
			}
			else
			{
				die "ERROR: wrong vcproj name\n";
			}
		}
	}
	else
	{
		print "Unchanged project $cusProjFileName\n";
	}
	return $hasFileRemovedInVCProj;
}

# step1. read build all sln content
# step2. parse vcproj in sln
# step3. call removeSrcFromProj to removed sources
# step4. check if changed
# step5. if changed, put vcproj name in changed list
# step6. parse sln content and updated changed vcproj name
# step7. save build all sln as XXX_cus.sln
sub myUpdateProj
{
	my $buildAllSln = shift;
	my @tmpSlnContent;
	my @slnContent;
	my $skipEndProject = 0;
	
	open(SOURCES, "$buildAllSln") or die "cannot read \"$buildAllSln\" file\n";
	@tmpSlnContent = <SOURCES>;
	close(SOURCES);	

    #remove simulator proj from Sln
	for my $line (@tmpSlnContent)
	{
		my $found = 0;
		if ($line =~ /\.vcproj/)
		{
			$skipEndProject = 0;
			if ($found == 0)
			{
				for my $projName (@mySimulatorProj)
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
			push @slnContent, $line;
		}
	}
	
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
			myRemoveSrcFromProj($line);
		}
	}
}

for my $file (@myPredSrcRel)
{
    push @myReleaseSrc, $file;
}

open(SOURCES, "< $srcReleaseConfigXml") or die "cannot read \"$srcReleaseConfigXml\" file\n";
while(my $line = <SOURCES>)
{
	parseXml($line);
}
#update build all sln file
myUpdateProj($vcBuildAllSlnName);

print "Done!\n";


