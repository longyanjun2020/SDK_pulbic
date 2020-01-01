#!/usr/bin/perl

use warnings;
use strict;

#$ SRC/proj/tng/release_process/genCommLibForSim.pl SRC/proj/tng/release_process SRC/proj ./SimuLibCheck


# Lib path
my $incPath = shift;
my $srcPath = shift;
my $outputPath = shift;
my $libsPath = $srcPath."/sc/libs";
my $checkList = $srcPath."/tng/p4/simu_cmn_lib_checklist.txt";

require "$incPath/cmpBin.pl";

# Output bat path
my $disasmBat = "./disasmLib.bat";
my $disasmBatExeLog = "$disasmBat\.log";
my $genSimuCmnLibBat = "./getSimuCmnLib.bat";
my $genSimuCmnLibBatExeLog = "./getSimuCmnLib.bat.log";

#Output folder
my $asmOutputDir = $outputPath;

my $reportFile = "$asmOutputDir/Result.txt";
my $libCmnListFile = "$asmOutputDir/CmnLibList.txt";
my $dllCmnListFile = "$asmOutputDir/CmnDllList.txt";

my $vsvars32Path = "c:\\\"Program Files\"\\\"Microsoft Visual Studio 8\"\\Common7\\Tools\\vsvars32.bat";

my @predCmnLibList  = (  "MKernelWin32Lib.lib"
                      );

my @predCmnDllList  = (  "MKDev_NetWork.dll"
                      );

my @pathList = ();
my @tmpPathList = ();
my @libFileList = ([]);
my @dllFileList = ([]);
my @cmnLibList = ();
my @noncmnLibList = ();
my @cmnDllList = ();
my @noncmnDllList = ();
my $lineData1;
my $lineData2;
my $tmpPath1;
my $tmpPath2;
my $tmpStr1;
my $tmpStr2;
my $tmpStr3;
my $tmpStr4;
my $idx = 0;
my $counter = 0;
my $maxLib = 0;
my $maxDll = 0;
my $maxLine = 0;
my $cmd;
my $i;
my $j;
my $flag;
my $found = 0;
my $diff = 0;

##########################
## main
##########################

print "Path: $libsPath\n";

# get all chip name
opendir PRD, "$libsPath" or die "cannot access product in \"", "$tmpPath1", "\"\n";
for my $prd (sort(readdir(PRD)))
{
	if($prd =~ /^__(.*)__$/)
	{
	    push @pathList, $prd;
	}
}
closedir PRD;

if($#pathList <= 0)
{
    print "No need to gen common libs. $#pathList\n";
    exit 1;
}

# get the lib list for each folder(chip)
$idx = 0;
print "Chist List:\n";
foreach(@pathList)
{
    #print "Chip: $_\n";
    $tmpPath1 = "$libsPath/".$_."/MStarStudio_UP";
    $counter = 0;
    opendir PRD, "$tmpPath1/" or die "cannot access product in \"", "$tmpPath1", "\"\n";
    for my $prd (sort(readdir(PRD)))
    {
    	if($prd =~ /\.lib$/)
    	{
            $found = 0;
    	    foreach(@predCmnLibList)
    	    {
    	        if($prd eq $_)
    	        {
    	            $found = 1;
    	            last;
    	        }
    	    }    	    
    	    if($found eq 1)
    	    {
    	        next;
            }
            	    
    	    $libFileList[$idx][$counter] = $prd;
    	    $counter += 1;
    	}
    }
    closedir PRD;
    if($maxLib == 0)
    {
        $maxLib = $counter;
    }
    else
    {
        if($maxLib != $counter)
        {
            print "Some lib file will not be compared. $maxLib / $counter\n";
        }
    }
    $idx += 1;
}

# get the dll list from each folder(chip)
$idx = 0;
print "Preparing dll list...\n";    
foreach(@pathList)
{
    $tmpPath1 = "$libsPath/".$_."/MStarDeveloper/debug";
    $counter = 0;    
    opendir PRD, "$tmpPath1/" or die "cannot access product in \"", "$tmpPath1", "\"\n";
    for my $prd (sort(readdir(PRD)))
    {
    	#if($prd =~ /\.dll$|\.exe$/)
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
            $found = 0;
    	    foreach(@predCmnDllList)
    	    {
    	        if($prd eq $_)
    	        {
    	            $found = 1;
    	            last;
    	        }
    	    }    	    
    	    if($found eq 1)
    	    {
    	        next;
            }
            
    	    $dllFileList[$idx][$counter] = $prd;
    	    $counter += 1;
    	}   	
    }
    closedir PRD;
    if($maxDll == 0)
    {
        $maxDll = $counter;
    }
    else
    {
        if($maxDll != $counter)
        {
            print "Some dll file will not be compared. $maxDll / $counter\n";
            print "Please help to check: $tmpPath1\n";
        }
    }
    $idx += 1;
}

# gen batch file for lib file disassembly
open(BATFILE, ">$disasmBat") or die "Error: Cannot open file $disasmBat\n";
print BATFILE "call $vsvars32Path\n";
print BATFILE "\n";
$tmpStr4 = "if exist \"$asmOutputDir\" (";
$tmpStr4 =~ s/\//\\/g;
print BATFILE "$tmpStr4\n";
$tmpStr4 = "chmod 777 -R $asmOutputDir";
$tmpStr4 =~ s/\//\\/g;
print BATFILE "$tmpStr4\n";
$tmpStr4 = "rm -f -r $asmOutputDir";
$tmpStr4 =~ s/\//\\/g;
print BATFILE "$tmpStr4\n";
print BATFILE ")\n";
$tmpStr4 = "mkdir $asmOutputDir";
$tmpStr4 =~ s/\//\\/g;
print BATFILE "$tmpStr4\n";
$tmpStr4 = "chmod 777 -R $asmOutputDir";
$tmpStr4 =~ s/\//\\/g;
print BATFILE "$tmpStr4\n";
print BATFILE "\n";
$tmpStr4 =~ s/\//\\/g;
$idx = 0;
foreach(@pathList)
{
    $tmpPath1 = "$_";
    $tmpStr4 = "if exist \"$asmOutputDir/$tmpPath1\" (";
    $tmpStr4 =~ s/\//\\/g;
    print BATFILE "$tmpStr4\n";
    $tmpStr4 = "rm -f -r $asmOutputDir/$tmpPath1";
    $tmpStr4 =~ s/\//\\/g;
    print BATFILE "$tmpStr4\n";
    print BATFILE ")\n";    
    $tmpStr4 = "mkdir $asmOutputDir/$tmpPath1";
    $tmpStr4 =~ s/\//\\/g;
    print BATFILE "$tmpStr4\n";
    $tmpStr4 = "chmod 777 -R $asmOutputDir/$tmpPath1";
    $tmpStr4 =~ s/\//\\/g;
    print BATFILE "$tmpStr4\n";
    print BATFILE "\n";
    $tmpStr4 = "mkdir $asmOutputDir/$tmpPath1/dll";
    $tmpStr4 =~ s/\//\\/g;
    print BATFILE "$tmpStr4\n";
    $tmpStr4 = "chmod 777 -R $asmOutputDir/$tmpPath1/dll";
    $tmpStr4 =~ s/\//\\/g;
    print BATFILE "$tmpStr4\n";    
    print BATFILE "\n";    
    print BATFILE "cd $libsPath/".$_."/MStarStudio_UP\n";
    for($i = 0; $i < $maxLib; $i++)
    {
        $tmpPath2 = "$libFileList[$idx][$i] > $asmOutputDir/".$_."/$libFileList[$idx][$i].txt\n";
        print BATFILE "dumpbin /DISASM /EXPORTS $tmpPath2";
    }
    print BATFILE "cd ../../../../\n";    
    print BATFILE "cd $libsPath/".$_."/MStarDeveloper/debug\n";
    for($i = 0; $i < $maxDll; $i++)
    {
        $tmpPath2 = "$dllFileList[$idx][$i] > $asmOutputDir/".$_."/dll/$dllFileList[$idx][$i].txt\n";
       # $tmpPath2 =~ s/\//\\/g;
        print BATFILE "dumpbin /DISASM /EXPORTS $tmpPath2";
    }
    print BATFILE "cd ../../../../../\n";    
    print BATFILE "\n";
    $idx += 1;
}
close(BATFILE);

# execute batch file to generate lib-disassembly text file
system("chmod 777 -R $disasmBat");
system("$disasmBat > $disasmBatExeLog");

unlink $reportFile;
open(REPORT, ">$reportFile") or die "Error: Cannot open file $reportFile\n";

# compare the lib files
print "Checking libs...\n";
foreach(@pathList)
{
    $tmpPath1 = "$asmOutputDir/".$_;
    push @tmpPathList, $tmpPath1;
}
&compareBin(\@libFileList, $maxLib, \@tmpPathList, \@cmnLibList, \@noncmnLibList, *REPORT);   
@tmpPathList = ();

# compare the dll files
print "Checking dlls...\n";
foreach(@pathList)
{
    $tmpPath1 = "$asmOutputDir/".$_."/dll";
    push @tmpPathList, $tmpPath1;
}
&compareBin(\@dllFileList, $maxDll, \@tmpPathList, \@cmnDllList, \@noncmnDllList, *REPORT);   
@tmpPathList = ();

foreach(@predCmnLibList)
{
    push @cmnLibList, $_;
}

foreach(@predCmnDllList)
{
    push @cmnDllList, $_;
}

# copy common libs
open(GSNCMNLIB, ">$genSimuCmnLibBat") or die "Error: Cannot open file $genSimuCmnLibBat\n";

# del vc output files
$tmpStr2 = "$srcPath/MStarStudio_UP/lib/Debug/*.*";
$tmpStr2 =~ s/\//\\/g;
print GSNCMNLIB "del /F /Q $tmpStr2\n\n"; 
$tmpStr2 = "$srcPath/MStarStudio_UP/MStarDeveloper/XMMI/debug/*.dll";
$tmpStr2 =~ s/\//\\/g;
print GSNCMNLIB "del /F /Q $tmpStr2\n\n"; 
$tmpStr2 = "$srcPath/MStarStudio_UP/MStarDeveloper/XMMI/debug/*.exe";
$tmpStr2 =~ s/\//\\/g;
print GSNCMNLIB "del /F /Q $tmpStr2\n\n"; 
$tmpStr2 = "$srcPath/MStarStudio_UP/MStarDeveloper/XMMI/debug/*.ilk";
$tmpStr2 =~ s/\//\\/g;
print GSNCMNLIB "del /F /Q $tmpStr2\n\n"; 
$tmpStr2 = "$srcPath/MStarStudio_UP/MStarDeveloper/XMMI/debug/*.exp";
$tmpStr2 =~ s/\//\\/g;
print GSNCMNLIB "del /F /Q $tmpStr2\n\n"; 
$tmpStr2 = "$srcPath/MStarStudio_UP/MStarDeveloper/XMMI/debug/*.lib";
$tmpStr2 =~ s/\//\\/g;
print GSNCMNLIB "del /F /Q $tmpStr2\n\n"; 
$tmpStr2 = "$srcPath/MStarStudio_UP/MStarDeveloper/XMMI/debug/MStarMDL1.*";
$tmpStr2 =~ s/\//\\/g;
print GSNCMNLIB "del /F /Q $tmpStr2\n\n"; 
$tmpStr2 = "$srcPath/MStarStudio_UP/MStarDeveloper/XMMI/debug/MStarMDL2.*";
$tmpStr2 =~ s/\//\\/g;
print GSNCMNLIB "del /F /Q $tmpStr2\n\n"; 
$tmpStr2 = "$srcPath/MStarStudio_UP/MStarDeveloper/XMMI/debug/MStarMMI.*";
$tmpStr2 =~ s/\//\\/g;
print GSNCMNLIB "del /F /Q $tmpStr2\n\n"; 

print REPORT "\nCommon lib list:\n";
open(CMNLIST, ">$libCmnListFile") or die "Error: Cannot open file $libCmnListFile\n";
foreach(@cmnLibList)
{
    $flag = 0;
    $tmpStr1 = $_;
    
    foreach(@pathList)
    {
        if($flag == 0)
        {
            $tmpStr2 = "$libsPath/".$_."/MStarStudio_UP/$tmpStr1 $srcPath/MStarStudio_UP/lib/Debug/$tmpStr1\n";
            $tmpStr2 =~ s/\//\\/g;
            print GSNCMNLIB "copy /Y $tmpStr2";
            $flag = 1;
            
            print CMNLIST "$tmpStr1\n";
        }

        $tmpStr2 = "$libsPath/".$_."/MStarStudio_UP/$tmpStr1";
        $tmpStr2 =~ s/\//\\/g;
        print GSNCMNLIB "del /F /Q $tmpStr2\n";        
    }
    print GSNCMNLIB "\n";
    
    print REPORT "  $_\n";
}
close(CMNLIST);

foreach(@cmnDllList)
{
    $flag = 0;
    $tmpStr1 = $_;
    
    foreach(@pathList)
    {
        if($flag == 0)
        {
            $tmpStr2 = "$libsPath/".$_."/MStarDeveloper/debug/$tmpStr1 $srcPath/MStarStudio_UP/MStarDeveloper/XMMI/debug/$tmpStr1\n";
            $tmpStr2 =~ s/\//\\/g;
            print GSNCMNLIB "copy /Y $tmpStr2";
            $flag = 1;
        }

        $tmpStr2 = "$libsPath/".$_."/MStarDeveloper/debug/$tmpStr1";
        $tmpStr2 =~ s/\//\\/g;
        print GSNCMNLIB "del /F /Q $tmpStr2\n";        
    }
    print GSNCMNLIB "\n";
}
close(GSNCMNLIB);

print REPORT "\n\nNon-Common lib list:\n";
if (@noncmnLibList == 0)
{
    print REPORT "  (empty)\n";
}
foreach(@noncmnLibList)
{
    print REPORT "  $_\n";
}

print REPORT "\n\nCommon dll list:\n";
open(CMNLIST, ">$dllCmnListFile") or die "Error: Cannot open file $libCmnListFile\n";
foreach(@cmnDllList)
{
    print REPORT "  $_\n";
    
    print CMNLIST "$_\n";
}
close(CMNLIST);

print REPORT "\n\nNon-Common dll list:\n";
if (@noncmnDllList == 0)
{
    print REPORT "  (empty)\n";
}
foreach(@noncmnDllList)
{
    print REPORT "  $_\n";
}

print "preparing common libs...\n";
system("chmod 777 -R $genSimuCmnLibBat");
#system("$genSimuCmnLibBat > $genSimuCmnLibBatExeLog");

if ((@noncmnLibList ne 0) || (@noncmnDllList ne 0))
{
    print "\nERROR: simulator common lib check is failed!\n";
    print REPORT "\nERROR: simulator common lib check is failed!\n";
}
close(REPORT);

print "Done\n";
