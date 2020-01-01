#!/usr/bin/perl

use warnings;
use strict;

#$ genDeltaLibForSim.pl oldLibPath newLibPath outputPath tempDir mode

require "cmpBin.pl";

if (($#ARGV+1) != 5)
{
  print "usage($#ARGV): genDeltaLibForSim.pl oldLibPath newLibPath outputPath tempDir mode\n";
  exit 1;
}

# Lib path
my $oldLibPath = shift;
my $newLibPath = shift;
my $outputPath = shift;
my $outputTempPath = shift;
my $runMode = shift;

# Output bat path
my $disasmBat = "./disasmLib.bat";
my $disasmBatExeLog = "$disasmBat\.log";
my $genSimuCmnLibBat = "./getSimuCmnLib.bat";
my $genSimuCmnLibBatExeLog = "./getSimuCmnLib.bat.log";
my $upPath = "MStarStudio_UP";
my $devDebugPath = "MStarDeveloper/debug";

#Output folder
my $asmOutputDir = $outputTempPath;

my $reportFileLibs = "$asmOutputDir/LibsResult.txt";
my $reportFileLibDebug = "$asmOutputDir/LibDebugResult.txt";
my $reportFileDevDebug = "$asmOutputDir/DevDebugResult.txt";
my $asmTempFolder1 = "old";
my $asmTempFolder2 = "new";
my $asmTempFolder3 = "$asmTempFolder1/libDebug";
my $asmTempFolder4 = "$asmTempFolder2/libDebug";
my $asmTempFolder5 = "$asmTempFolder1/devDebug";
my $asmTempFolder6 = "$asmTempFolder2/devDebug";

my $modeLibs = "Libs";
my $modeLibDebug = "LibDebug"; # lib only
my $modeDevDebug = "DevDebug"; # dll only
my $cmd;
my $found;
my $idx = 0;
my $counter = 0;
my @oldChipList = ();
my @newChipList = ();
my $cmpChip1;
my $cmpChip2;
my $tmpStr1;
my $tmpStr2;

my $time1;
my $time2;

my $fatalErr = 0;

my $vsvars32Path = "c:/\"Program Files\"/\"Microsoft Visual Studio 8\"/Common7/Tools/vsvars32.bat";

#debug setting, 1: debug mode; 0: normal mode
my $skipDisAsm = 0;

if($runMode eq $modeLibs)
{
}
elsif($runMode eq $modeLibDebug)
{
}
elsif($runMode eq $modeDevDebug)
{
}
else
{
    print "Bat parameter!\n";
    exit 1;
}

sub genAsmText()
{
    #&genAsmText("\.lib", $oldLibPath, $asmTempFolder1, @oldBinList, $cmpChip1);
    my($fileType, $path, $folder, $chip, $counter, @binFileList) = @_;

    my $idx;
    my $chkDir;
    
    @binFileList = ();
    
    if($fileType eq ".lib")
    {
        $chkDir = $upPath;
    }
    elsif($fileType eq ".dll")
    {
        $chkDir = $devDebugPath;
    }
    else
    {
        print "ERROR: known type! $fileType\n";
        exit 1;
    }
    
    print "gen asm path: $path/$chip/$chkDir\n";
    print "file type:\*$fileType\n";
    print "file list:\n";
    $counter = 0;
    opendir PRD, "$path/$chip/$chkDir" or die "cannot access $path/$chip/$chkDir\n";
    for my $prd (sort(readdir(PRD)))
    {
    	if($prd =~ /$fileType$/)
    	{
    	    print "  $prd\n";
    	    $binFileList[$counter] = $prd;
    	    $counter += 1;
    	}
    	elsif($prd =~ /\.$/)
    	{
    	    next;
    	}
    	elsif($prd =~ /\.\.$/)
    	{
    	    next;
    	}
    	elsif($prd =~ /MSSimConsole.exe$/)
    	{
    	    next;
    	}
    	elsif($prd =~ /MStarSimulator.exe$/)
    	{
    	    next;
    	}
    	else
        {
    	    print "ERROR: unhandled file, $prd\n";
    	    exit 1;
        }
        
    }
    closedir PRD;
    
    $cmd = "mkdir -p $asmOutputDir/$folder/$chip/$chkDir";
    print "$cmd\n";
    system ($cmd);
    $cmd = "chmod 777 -R $asmOutputDir/$folder/$chip/$chkDir";
    print "$cmd\n";
    system ($cmd);
            
    # gen disasmLib batch file
    open(BATFILE, ">$asmOutputDir/$folder/$chip$fileType\.bat") or die "Error: Cannot open file $asmOutputDir/$folder/$chip$fileType\.bat\n";
    print BATFILE "call $vsvars32Path\n";
    print BATFILE "\n";
           
    for($idx = 0; $idx < $counter; $idx++)
    {
        $tmpStr1 = "$path/$chip/$chkDir/$binFileList[$idx] > $asmOutputDir/$folder/$chip/$chkDir/$binFileList[$idx].txt\n";
        # $tmpPath2 =~ s/\//\\/g;
        print BATFILE "dumpbin /DISASM /EXPORTS $tmpStr1";
        print BATFILE "\n";
    }           
    close(BATFILE);

    # execute batch file to generate lib-disassembly text file
    print "\ngenerate asm files...\n";
    system("chmod 777 -R $asmOutputDir/$folder/$chip$fileType\.bat");
    if($skipDisAsm eq 0)
    {
        system("$asmOutputDir/$folder/$chip$fileType\.bat > $asmOutputDir/$folder/$chip$fileType\.bat.log");    
    }
    print "\n";
    
    $_[4] = $counter; # call by reference
    @{$_[5]} = @binFileList; # call by reference
}

sub genAsmTextEx()
{
    my($fileType, $path, $folder, $counter, @binFileList) = @_;

    my $idx;
    
    @binFileList = ();
    
    if($fileType eq ".lib")
    {
    }
    elsif($fileType eq ".dll")
    {
    }
    else
    {
        print "ERROR: known type! $fileType\n";
        exit 1;
    }
    
    print "gen asm path: $path/\n";
    print "file type:\*$fileType\n";
    print "file list:\n";
    $counter = 0;
    opendir PRD, "$path" or die "cannot access $path\n";
    for my $prd (sort(readdir(PRD)))
    {
    	if($prd =~ /$fileType$/)
    	{
    	    print "  $prd\n";
    	    $binFileList[$counter] = $prd;
    	    $counter += 1;
    	}
    }
    closedir PRD;
    
    $cmd = "mkdir -p $asmOutputDir/$folder";
    print "$cmd\n";
    system ($cmd);
    $cmd = "chmod 777 -R $asmOutputDir/$folder";
    print "$cmd\n";
    system ($cmd);
            
    # gen disasmLib batch file
    open(BATFILE, ">$asmOutputDir/$folder/tmp$fileType\.bat") or die "Error: Cannot open file $asmOutputDir/$folder/tmp$fileType\.bat\n";
    print BATFILE "call $vsvars32Path\n";
    print BATFILE "\n";
           
    for($idx = 0; $idx < $counter; $idx++)
    {
        $tmpStr1 = "$path/$binFileList[$idx] > $asmOutputDir/$folder/$binFileList[$idx].txt\n";
        # $tmpPath2 =~ s/\//\\/g;
        print BATFILE "dumpbin /DISASM $tmpStr1";
        print BATFILE "\n";
    }           
    close(BATFILE);

    # execute batch file to generate lib-disassembly text file
    print "\ngenerate asm files...\n";
    system("chmod 777 -R $asmOutputDir/$folder/tmp$fileType\.bat");
    if($skipDisAsm eq 0)
    {
        system("$asmOutputDir/$folder/tmp$fileType\.bat > $asmOutputDir/$folder/tmp$fileType\.bat.log");    
    }
    print "\n";
    
    $_[3] = $counter; # call by reference
    @{$_[4]} = @binFileList; # call by reference
}

##########################
## main
##########################

print "oldLibPath: $oldLibPath\n";
print "newLibPath: $newLibPath\n";
print "outputPath: $outputPath\n";
print "mode: $runMode\n";

if($runMode eq $modeLibs)
{
    goto _MODE_LIBS;
}
elsif($runMode eq $modeLibDebug)
{
    goto _MODE_LIBDEBUG;
}
elsif($runMode eq $modeDevDebug)
{
    goto _MODE_DEVDEBUG;    
}

print "ERROR: undefined mode!";
exit 1;

##########################
## for libs mode
##########################
_MODE_LIBS:
if($skipDisAsm eq 1)
{
    $cmd = "rm -f -r $reportFileLibs";
    system ($cmd);    
}

# get all chip name
opendir PRD, "$oldLibPath" or die "cannot access product in \"", "$oldLibPath", "\"\n";
for my $prd (sort(readdir(PRD)))
{
	if($prd =~ /^__(.*)__$/)
	{
	    push @oldChipList, $prd;
	}
}
closedir PRD;

opendir PRD, "$newLibPath" or die "cannot access product in \"", "$newLibPath", "\"\n";
for my $prd (sort(readdir(PRD)))
{
	if($prd =~ /^__(.*)__$/)
	{
	    push @newChipList, $prd;
	}
}
closedir PRD;

if($skipDisAsm eq 1)
{
    goto _DISASM;
}

# check if it has new chip
for my $cmpChip1 (@newChipList)
{
    $found = 0;
    foreach(@oldChipList)
    {
        $cmpChip2 = $_;
        if($cmpChip1 eq $cmpChip2)
        {
            $found = 1;
            last;    
        }
    }
    
    if($found eq 0)
    {
        print "new chip: $cmpChip1\n";
        if( !-e "$outputPath/$cmpChip1/$devDebugPath")
        {
            $cmd = "mkdir -p $outputPath/$cmpChip1/$devDebugPath";
            print "$cmd\n";
            system ($cmd);
            $cmd = "chmod 777 -R $outputPath/$cmpChip1";
            print "$cmd\n";
            system ($cmd);           
        }       
        if( -e "$outputPath/$cmpChip1/$upPath")
        {
            $cmd = "rm -f -r $outputPath/$cmpChip1/$upPath";
            print "$cmd\n";
            system ($cmd);
        }
        # copy files
        $cmd = "cp -r -f $newLibPath/$cmpChip1/$upPath $outputPath/$cmpChip1/$upPath";
        print "$cmd\n";
        system ($cmd);
        if( -e "$outputPath/$cmpChip1/$devDebugPath")
        {
            $cmd = "rm -f -r $outputPath/$cmpChip1/$devDebugPath";
            print "$cmd\n";
            system ($cmd);
        }
        # copy files
        $cmd = "cp -r -f $newLibPath/$cmpChip1/$devDebugPath $outputPath/$cmpChip1/$devDebugPath";
        print "$cmd\n";
        system ($cmd);
    }
}

# remove temp folder
if( -e "$asmOutputDir")
{
    print "remove $asmOutputDir\n";
    $cmd = "chmod 777 -R $asmOutputDir";
    print "$cmd\n";
    system ($cmd);
    $cmd = "rm -f -r $asmOutputDir";
    print "$cmd\n";
    system ($cmd);
}
print "create new $asmOutputDir\n";
$cmd = "mkdir $asmOutputDir";
print "$cmd\n";
system ($cmd);
$cmd = "chmod 777 -R $asmOutputDir";
print "$cmd\n";
system ($cmd);

open(REPORT, ">$reportFileLibs") or die "Error: Cannot open file $reportFileLibs\n";

print "create new $asmOutputDir/$asmTempFolder1\n";
$cmd = "mkdir $asmOutputDir/$asmTempFolder1";
print "$cmd\n";
system ($cmd);
$cmd = "chmod 777 -R $asmOutputDir/$asmTempFolder1";
print "$cmd\n";
system ($cmd);    
print "create new $asmOutputDir/$asmTempFolder2\n";
$cmd = "mkdir $asmOutputDir/$asmTempFolder2";
print "$cmd\n";
system ($cmd);
$cmd = "chmod 777 -R $asmOutputDir/$asmTempFolder2";
print "$cmd\n";
system ($cmd);

_DISASM:

#disasm libs/dlls
$time1 = time; 	
print "\n";
for my $cmpChip1 (@oldChipList)
{
    my $NL;
    my $binNum1;
    my $binNum2;
    my @oldBinList = ();
    my @newBinList = ();    
    my @cmpChipPathList;
    my @cmnBinList;
    my @noncmnBinList;
    my @tempList = ();
    my @fileList = ([]);
    
    print "check $oldLibPath/$cmpChip1:\n";   
    print REPORT "check $oldLibPath/$cmpChip1:\n";   

    @cmpChipPathList = ();
    @cmnBinList = ();
    @noncmnBinList = ();
    $found = 0;
    foreach(@newChipList)
    {
        $cmpChip2 = $_;
        if($cmpChip1 eq $cmpChip2)
        {
            $found = 1;
            last;    
        }
    }
    
    if($found eq 0)
    {
        print "ERROR: $cmpChip1 is removed in new release package!\n";
        print REPORT "ERROR: $cmpChip1 is removed in new release package!\n";
        exit 1;
    }
    
    &genAsmText("\.lib", $oldLibPath, $asmTempFolder1, $cmpChip1, $binNum1, \@oldBinList);
    &genAsmText("\.lib", $newLibPath, $asmTempFolder2, $cmpChip1, $binNum2, \@newBinList);
    if ( !-e "$outputPath/$cmpChip1/$upPath")
    {
        $cmd = "mkdir -p $outputPath/$cmpChip1/$upPath";
        print "$cmd\n";
        system ($cmd);
        $cmd = "chmod 777 -R $outputPath/$cmpChip1/$upPath";
        print "$cmd\n";
        system ($cmd);
    }
    # check new libs
    @tempList = @newBinList;
    @newBinList = ();
    $NL = 0;    
    foreach(@tempList)
    {
        $found = 0;
        $tmpStr1 = $_;
        foreach(@oldBinList)
        {
            if($tmpStr1 eq $_)
            {
                $found = 1;
                last;
            }
        }
        
        if($found eq 0)
        {
            $NL = 1;
            print "\nnew lib file: $tmpStr1";
            print REPORT "new lib file: $tmpStr1\n";
            
            $cmd = "cp -f $newLibPath/$cmpChip1/$upPath/$tmpStr1 $outputPath/$cmpChip1/$upPath/$tmpStr1";
            print "$cmd\n";
            system ($cmd); 
                       
        }
        else
        {
            push @newBinList, $tmpStr1;
        }
    }
    if($NL eq 1)
    {
        print "\n";
    }
    #check if some libs are removed in new release package
    @tempList = @oldBinList;
    @oldBinList = ();
    $NL = 0;
    foreach(@tempList)
    {
        $found = 0;
        $tmpStr1 = $_;
        foreach(@newBinList)
        {
            if($tmpStr1 eq $_)
            {
                $found = 1;
                last;
            }
        }
        
        if($found eq 0)
        {
            $NL = 1;
            print "\nERROR: removed lib file: $tmpStr1";
            print REPORT "ERROR: removed lib file: $tmpStr1\n";
            $fatalErr = 1;
        }
        else
        {
            push @oldBinList, $tmpStr1;
        }
    }
    if($NL eq 1)
    {
        print "\n";
    }
    
    #debug
    $binNum1 = $#oldBinList + 1;
    $binNum2 = $#newBinList + 1;
    if($#oldBinList ne $#newBinList)
    {
        print "$#oldBinList\n";
        print "$#newBinList\n";
        print "$binNum1\n";
        
        $idx = 0;
        foreach(@oldBinList)
        {
            print "$idx:$_\n";
            $idx += 1;
        }
        $idx = 0;
        foreach(@newBinList)
        {
            print "$idx:$_\n";
            $idx += 1;
        }
        print "ERROR: fatal error!\n";
        exit 1;    
    }
         
    $cmpChipPathList[0] = "$asmOutputDir/$asmTempFolder1/$cmpChip1/$upPath";
    $cmpChipPathList[1] = "$asmOutputDir/$asmTempFolder2/$cmpChip1/$upPath";
    @fileList = ([@oldBinList],[@newBinList]); 
    &compareBin(\@fileList, $binNum1, \@cmpChipPathList, \@cmnBinList, \@noncmnBinList, *REPORT);   
    print "\nnon-common lib list:\n";
    print REPORT "\nnon-common lib list:\n";
    foreach(@noncmnBinList)
    {
        $cmd = "cp -f $newLibPath/$cmpChip1/$upPath/$_ $outputPath/$cmpChip1/$upPath/$_";
        print "$cmd\n";
        system ($cmd);
        print REPORT "  $_\n";
    }
    print REPORT "\n";
    
    &genAsmText("\.dll", $oldLibPath, $asmTempFolder1, $cmpChip1, $binNum1, \@oldBinList);
    &genAsmText("\.dll", $newLibPath, $asmTempFolder2, $cmpChip1, $binNum2, \@newBinList);
    if ( !-e "$outputPath/$cmpChip1/$devDebugPath")
    {
        $cmd = "mkdir -p $outputPath/$cmpChip1/$devDebugPath";
        print "$cmd\n";
        system ($cmd);
        $cmd = "chmod 777 -R $outputPath/$cmpChip1/$devDebugPath";
        print "$cmd\n";
        system ($cmd);
    }    
    # check new dlls
    @tempList = @newBinList;
    @newBinList = ();
    $NL = 0;    
    foreach(@tempList)
    {
        $found = 0;
        $tmpStr1 = $_;
        foreach(@oldBinList)
        {
            if($tmpStr1 eq $_)
            {
                $found = 1;
                last;
            }
        }
        
        if($found eq 0)
        {
            $NL = 1;
            print "\nnew dll file: $tmpStr1";
            print REPORT "new dll file: $tmpStr1\n";
            
            $cmd = "cp -f $newLibPath/$cmpChip1/$devDebugPath/$tmpStr1 $outputPath/$cmpChip1/$devDebugPath/$tmpStr1";
            print "$cmd\n";
            system ($cmd); 
                       
        }
        else
        {
            push @newBinList, $tmpStr1;
        }
    }
    if($NL eq 1)
    {
        print "\n";
    }
    #check if some libs are removed in new release package
    @tempList = @oldBinList;
    @oldBinList = ();
    $NL = 0;
    foreach(@tempList)
    {
        $found = 0;
        $tmpStr1 = $_;
        foreach(@newBinList)
        {
            if($tmpStr1 eq $_)
            {
                $found = 1;
                last;
            }
        }
        
        if($found eq 0)
        {
            $NL = 1;
            print "\nERROR: removed dll file: $tmpStr1";
            print REPORT "ERROR: removed dll file: $tmpStr1\n";
            $fatalErr = 1;
        }
        else
        {
            push @oldBinList, $tmpStr1;
        }
    }
    if($NL eq 1)
    {
        print "\n";
    }
    $binNum1 = $#oldBinList + 1;
    $binNum2 = $#newBinList + 1;    
    $cmpChipPathList[0] = "$asmOutputDir/$asmTempFolder1/$cmpChip1/$devDebugPath";
    $cmpChipPathList[1] = "$asmOutputDir/$asmTempFolder2/$cmpChip1/$devDebugPath";
    @fileList = ([@oldBinList],[@newBinList]); 
    &compareBin(\@fileList, $binNum1, \@cmpChipPathList, \@cmnBinList, \@noncmnBinList, *REPORT);
    print "\nnon-common dll list:\n";
    print REPORT "\nnon-common dll list:\n";
    foreach(@noncmnBinList)
    {       
        $cmd = "cp -f $newLibPath/$cmpChip1/$devDebugPath/$_ $outputPath/$cmpChip1/$devDebugPath/$_";
        print "$cmd\n";
        print REPORT "  $_\n";
        system ($cmd);
    }
    $cmd = "cp -f $newLibPath/$cmpChip1/$devDebugPath/MSSimConsole.exe $outputPath/$cmpChip1/$devDebugPath/MSSimConsole.exe";
    print "$cmd\n";
    system ($cmd);
    $cmd = "cp -f $newLibPath/$cmpChip1/$devDebugPath/MStarSimulator.exe $outputPath/$cmpChip1/$devDebugPath/MStarSimulator.exe";
    print "$cmd\n";
    system ($cmd);
    
    if($skipDisAsm eq 1)
    {
        exit 1;
    } 
}
$time2 = time;
$tmpStr1 = sprintf("%d mins", ($time2 - $time1)/60);
print "\ntime spent: $tmpStr1\n";

if($fatalErr eq 1)
{
    print "\nERROR: something wrong, please hlep to check log.";
    print REPORT "\nERROR: something wrong, please hlep to check log.\n";
}
else
{
    print "\nDone\n";
}

close(REPORT);  
exit 0;

##########################
## for libdebug mode
##########################
_MODE_LIBDEBUG:
;
_MODE_DEVDEBUG:
{
#$ perl genDeltaLibForSim.pl D:/qqq/E_08071032/SRC/proj/MStarStudio_UP/lib/Debug D:/qqq/E_08081140/SRC/proj/MStarStudio_UP/lib/Debug d:/33 D:/SimuLibCheck LibDebug
    my $binNum1;
    my @oldBinList;
    my $binNum2;
    my @newBinList;
    my @tempList;
    my $NL = 0;
    my @cmnBinList;
    my @noncmnBinList;    
    my @cmpFolderList;
    my @fileList = ([]);
    my $binStr = "lib";
    my $extStr = ".lib";
    my $tmpFolder1 = $asmTempFolder3;
    my $tmpFolder2 = $asmTempFolder4;
    my $reportFile = $reportFileLibDebug;
 
    if( !-e "$outputPath")
    {
        $cmd = "mkdir -p $outputPath";
        print "$cmd\n";
        system ($cmd);
        $cmd = "chmod 777 -R $outputPath";
        print "$cmd\n";
        system ($cmd);        
    }
 
    if($runMode eq $modeDevDebug) 
    {
        $binStr = "dll";
        $extStr = ".dll";
        $reportFile = $reportFileDevDebug;
        $tmpFolder1 = $asmTempFolder5;
        $tmpFolder2 = $asmTempFolder6;        
    }
    # remove temp folder
    if( -e "$asmOutputDir")
    {
        print "remove $asmOutputDir\n";
        $cmd = "chmod 777 -R $asmOutputDir";
        print "$cmd\n";
        system ($cmd);
        $cmd = "rm -f -r $asmOutputDir";
        print "$cmd\n";
        system ($cmd);
    }
    
    $cmd = "mkdir -p $asmOutputDir";
    print "$cmd\n";
    system ($cmd);
    $cmd = "chmod 777 -R $asmOutputDir";
    print "$cmd\n";
    system ($cmd);

    open(REPORT, ">$reportFile") or die "Error: Cannot open file $reportFileLibs\n";

    &genAsmTextEx("$extStr", $oldLibPath, $tmpFolder1, $binNum1, \@oldBinList);
    &genAsmTextEx("$extStr", $newLibPath, $tmpFolder2, $binNum2, \@newBinList);
    # check new libs
    @tempList = @newBinList;
    @newBinList = ();
    $NL = 0;    
    foreach(@tempList)
    {
        $found = 0;
        $tmpStr1 = $_;
        foreach(@oldBinList)
        {
            if($tmpStr1 eq $_)
            {
                $found = 1;
                last;
            }
        }
        
        if($found eq 0)
        {
            $NL = 1;
            print "\nnew $binStr file: $tmpStr1";
            print REPORT "new $binStr file: $tmpStr1\n";
            
            $cmd = "cp -f $newLibPath/$tmpStr1 $outputPath/$tmpStr1";
            print "$cmd\n";
            system ($cmd); 
                       
        }
        else
        {
            push @newBinList, $tmpStr1;
        }
    }
    if($NL eq 1)
    {
        print "\n";
    }
    #check if some libs are removed in new release package
    @tempList = @oldBinList;
    @oldBinList = ();
    $NL = 0;
    foreach(@tempList)
    {
        $found = 0;
        $tmpStr1 = $_;
        foreach(@newBinList)
        {
            if($tmpStr1 eq $_)
            {
                $found = 1;
                last;
            }
        }
        
        if($found eq 0)
        {
            $NL = 1;
            print "\nERROR: removed $binStr file: $tmpStr1";
            print REPORT "ERROR: removed $binStr file: $tmpStr1\n";
            $fatalErr = 1;
        }
        else
        {
            push @oldBinList, $tmpStr1;
        }
    }
    if($NL eq 1)
    {
        print "\n";
    }
    
    $binNum1 = $#oldBinList + 1;
    $binNum2 = $#newBinList + 1;    
    $cmpFolderList[0] = "$asmOutputDir/$tmpFolder1";
    $cmpFolderList[1] = "$asmOutputDir/$tmpFolder2";
    @fileList = ([@oldBinList],[@newBinList]); 
    &compareBin(\@fileList, $binNum1, \@cmpFolderList, \@cmnBinList, \@noncmnBinList, *REPORT);
    
    #debug
    $binNum1 = $#oldBinList + 1;
    $binNum2 = $#newBinList + 1;
    if($#oldBinList ne $#newBinList)
    {
        print "$#oldBinList\n";
        print "$#newBinList\n";
        print "$binNum1\n";
        
        $idx = 0;
        foreach(@oldBinList)
        {
            print "$idx:$_\n";
            $idx += 1;
        }
        $idx = 0;
        foreach(@newBinList)
        {
            print "$idx:$_\n";
            $idx += 1;
        }
        print "ERROR: fatal error!\n";
        exit 1;    
    }    
    print "\nnon-common $binStr list:\n";
    print REPORT "\nnon-common $binStr list:\n";
    foreach(@noncmnBinList)
    {       
        $cmd = "cp -f $newLibPath/$_ $outputPath/$_";
        print "$cmd\n";
        print REPORT "  $_\n";
        system ($cmd);
    }
    
    if($runMode eq $modeDevDebug)     
    {
        if( -e "$newLibPath/MSSimConsole.exe")
        {
            $cmd = "cp -f $newLibPath/MSSimConsole.exe $outputPath/MSSimConsole.exe";
            print "$cmd\n";
            system ($cmd);
        }
        else
        {
            print "\nERROR: can not find $newLibPath/MSSimConsole.exe\n";
            print REPORT "\nERROR: can not find $newLibPath/MSSimConsole.exe\n";
        }
        if( -e "$newLibPath/MStarSimulator.exe")
        {
            $cmd = "cp -f $newLibPath/MStarSimulator.exe $outputPath/MStarSimulator.exe";
            print "$cmd\n";
            system ($cmd);
        }
        else
        {
            print "\nERROR: can not find $newLibPath/MStarSimulator.exe\n";
            print REPORT "\nERROR: can not find $newLibPath/MStarSimulator.exe\n";
        }
    }
    
    close(REPORT);

    exit 0;
}
