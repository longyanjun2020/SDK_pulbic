#!/usr/bin/perl

use warnings;
use strict;

#$ clean.pl [All_File|Lib_File|Dll_File|Exe_File|CUS_Folder|Dubug_Folder|Simu_Output]  path  xxx.txt
#
#$ tng/release_process/clean.pl Lib_File MStarStudio_UP/lib/Debug ../../SimuLibCheck/CmnLibList.txt

my $exeType = shift;
my $procDir = shift;
my $para = shift;

sub isInWhiteList()
{
    my $chkFile = shift;
    my $inpFile = shift;
    my @fileContent;
    my @tmp;
    
    open(LIST, "<$inpFile") or die "Error: Cannot open file $inpFile\n";
    @fileContent = <LIST>;
    close(LIST);
    
    foreach(@fileContent)
    {
        s/\012$//;
		s/\015$//;
        @tmp = $_;
        
        if($chkFile eq $_)
        {
            return 1;
        }
    }
    
    return 0;
}

sub removeFiles()
{
    my $type = shift;
    my $path = shift;
    my $inpFile = shift;
    my $filter = "\.lib";
    my $tmp;
    
    if($type == 0) # All file
    {
        $filter = "";
    }
    elsif($type == 1) # Lib
    {
    }
    elsif($type == 2) # Dll
    {
        $filter = "\.dll";
    }
    elsif($type == 3) # Exe
    {
        $filter = "\.exe";
    }
    else
    {
        return 0;
    }
    
    print "Path = $path\n";
    print "Filter = $filter\n";
    opendir PRD, "$path" or die "cannot access product in \"", "$path", "\"\n";
    for my $prd (sort(readdir(PRD)))
    {
        #print "[$prd]\n";
        if($type == 0)
        {
            if($prd eq "\.")
            {
                next;
            }
            if($prd eq "\.\.")
            {
                next;
            }
            
            goto RMFILE;
        }
    	if($prd =~ /$filter/)
    	{
RMFILE:    	    
            print "Check file: $prd";
    	    if(0 == &isInWhiteList($prd,$inpFile))
    	    {
    	        print " => rm $prd";
    	        $tmp = $path."/".$prd;
                system("rm -f \"$tmp\"");
    	    }
    	    else
    	    {
    	        print " => common";
    	    }
    	    print "\n";
    	}
    }
    closedir PRD;    
}

sub removeFolders
{
	my $searchPattern = shift;
	my $folder = shift;
	my $exactMatch = shift;
	my @findFiles = <*>;
	
	for my $path (@findFiles)
	{
		my $found = 0;
		if ($exactMatch == 0)
		{
			if (length($searchPattern) == 0)
			{
				$found = 1;
			}
			elsif ($path =~ /$searchPattern/)
			{
				$found = 1;
			}
		}
		else
		{
			if ($path eq $searchPattern)
			{
				$found = 1;
			}
		}
		if ($found == 1)
		{
			if (-d $path)
			{
				if ($folder == 1)
				{
					chdir $path;
					removeFolders("", 0, 0);
					chdir "../";
				}
				rmdir $path;
				#print "delete folder $path\n";
			}
			else
			{
				if ($folder == 0)
				{
					unlink $path;
					#print "delete file $path\n";
				}
			}
		}
	}
	
	my @dir = <*>;
	for my $path (@dir)
	{
		if (-d $path)
		{
			chdir $path;
			removeFolders($searchPattern, $folder, $exactMatch);
			chdir "../";
		}
	}
}

sub removSimuOutput()
{
    my $path = shift;
    
    chdir $path;

    system("rm -f *.lib");
    system("rm -f *.pdb");
    system("rm -f *.ilk");
    system("rm -f *.exp");
    system("rm -f MStarMDL1.*");
    system("rm -f MStarMDL2.*");
    system("rm -f MStarMMI.*");
    
    system("rm -f -r ./SimFileSys/CARD");
    system("mkdir ./SimFileSys/CARD");
    system("rm -f -r ./SimFileSys/NAND");
    system("mkdir ./SimFileSys/NAND");
}

##########################
## main
##########################
if($exeType eq "All_File")
{
    my $type = 0;

    print "Clean files...\n";
    
    &removeFiles($type, $procDir, $para);
}
elsif($exeType eq "Lib_File")
{
    my $type = 1;

    print "Clean Lib files...\n";
    
    &removeFiles($type, $procDir, $para);
}
elsif($exeType eq "Dll_File")
{
    my $type = 2;
    
    print "Clean Dll files...\n";
    
    &removeFiles($type, $procDir, $para);
    
}
elsif($exeType eq "Exe_File")
{
    my $type = 3;
    
    print "Clean Exe files...\n";
    
    &removeFiles($type, $procDir, $para);
    
}
elsif($exeType eq "CUS_Folder")
{
    print "Clean CUS folders...\n";

    chdir $procDir;
    &removeFolders("Cus", 1, 1);    
}
elsif($exeType eq "Dubug_Folder")
{
    print "Clean Debug folders...\n";

    chdir $procDir;
    &removeFolders("Debug", 1, 1);    
}
elsif($exeType eq "Simu_Output")
{
    print "Clean Simulator output files...\n";
    
    &removSimuOutput($procDir);
}
else
{
    print "Bad parameter!\n";
    print "Type: $exeType\n";
    print "Dir: $procDir\n";
    print "File: $para\n";
    exit 1;
}

print "finish clean\n";

