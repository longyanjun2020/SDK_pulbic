#!/usr/bin/perl

use warnings;
use File::Copy;

$Product = &ReadProduct;
$ProductOption = "mak\/options_".$Product.".mak";
$OutDir = "build\/".$Product."\/out\/";
$GenWpbTool = "..\/tools\/GenWpbTool\/mkfat.exe";
$UserDrive = "custo_nor_";
$HiddenDrive = "hidden_nor_";
$AUTO_PARTITION_SUPPORT = 0;
$HIDDEN_PARTITION_SUPPORT = 0;
$M18_MCP_SUPPORT = 0;
$ONBOARD_USER_STORAGE_SUPPORT = 0;

$RaiReserveTrash = 25;
$RaiReserveTrashSpace = 768;

open(PRODUCT_FILE, "<".$ProductOption) or $ProductOption = "mak\/Eng\/options_".$Product.".mak";
open(PRODUCT_FILE, "<".$ProductOption) or die "[ERROR] Can't read options_".$Product.".mak\n";
close(PRODUCT_FILE);

$CHECK_SIZE_CRITICAL_MCP = &ReadOptions($ProductOption, "CHECK_SIZE_CRITICAL_MCP");
$CRITICAL_LANGPACK = &ReadOptions($ProductOption, "CRITICAL_LANGPACK");
$APP_REQ_SIZE = &ReadOptions($ProductOption, "APP_REQ_SIZE");
$APP_REQ_OBJ_ENTRY = &ReadOptions($ProductOption, "APP_REQ_OBJ_ENTRY");
$FAT_REQ_SIZE = &ReadOptions($ProductOption, "FAT_REQ_SIZE");
$FAT_PRELOAD_PATH = &ReadOptions($ProductOption, "FAT_PRELOAD_PATH");
$HFAT_REQ_SIZE = &ReadOptions($ProductOption, "HFAT_REQ_SIZE");
$HFAT_PRELOAD_PATH = &ReadOptions($ProductOption, "HFAT_PRELOAD_PATH");

if ($#ARGV >= 0)
{
    for ($i = 0; $i <= $#ARGV; $i++)
    {
        if ($ARGV[$i] =~ "-a")
        {
            $AUTO_PARTITION_SUPPORT = 1;
        }
        if ($ARGV[$i] =~ "-h")
        {
            $HIDDEN_PARTITION_SUPPORT = 1;
        }
        if ($ARGV[$i] =~ "-m")
        {
            $M18_MCP_SUPPORT = 1;
        }
        if ($ARGV[$i] =~ "-u")
        {
            $ONBOARD_USER_STORAGE_SUPPORT = 1;
        }        
    }
}

print "====== NOR Flash File System Config ... =======\n";
print "Product Option = ".$ProductOption."\n";
print "AUTO_PARTITION_SUPPORT = ".$AUTO_PARTITION_SUPPORT."\n";
print "HIDDEN_PARTITION_SUPPORT = ".$HIDDEN_PARTITION_SUPPORT."\n";
print "M18_MCP_SUPPORT = ".$M18_MCP_SUPPORT."\n";
print "ONBOARD_USER_STORAGE_SUPPORT = ".$ONBOARD_USER_STORAGE_SUPPORT."\n";
print "CHECK_SIZE_CRITICAL_MCP = ".$CHECK_SIZE_CRITICAL_MCP."\n";
print "CRITICAL_LANGPACK = ".$CRITICAL_LANGPACK."\n";
print "APP_REQ_SIZE = ".$APP_REQ_SIZE."\n";
print "APP_REQ_OBJ_ENTRY = ".$APP_REQ_OBJ_ENTRY."\n";
print "FAT_REQ_SIZE = ".$FAT_REQ_SIZE."\n";
print "FAT_PRELOAD_PATH = ".$FAT_PRELOAD_PATH."\n";
print "HFAT_REQ_SIZE = ".$HFAT_REQ_SIZE."\n";
print "HFAT_PRELOAD_PATH = ".$HFAT_PRELOAD_PATH."\n";

system("rm -rf ".$OutDir."fat");
system("rm -rf ".$OutDir."hfat");
system("rm -f ".$OutDir."*.fat");
system("rm -f ".$OutDir.$UserDrive."*.wpb");

if ($HIDDEN_PARTITION_SUPPORT == 1)
{
    print "============== Hidden Drive ... ===============\n";
    
    if (($HFAT_REQ_SIZE eq "") || ($HFAT_REQ_SIZE < 0))
    {
        die "[ERROR] Invalid parameter: HFAT_REQ_SIZE\n";
    }

    if (($HFAT_REQ_SIZE > 0) && ($HFAT_REQ_SIZE < 3))
    {
        die "[ERROR] Invalid parameter: HFAT_REQ_SIZE < 3 KB\n";
    }

    if ($HFAT_PRELOAD_PATH)
    {
        system("cp -af ".$HFAT_PRELOAD_PATH." ".$OutDir."hfat");
    }
    else
    {                                                  
        if ($HFAT_REQ_SIZE == 0)
        {
            print "[WARNING] Invalid parameter: Set HFAT_REQ_SIZE to fit preload, but HFAT_PRELOAD_PATH is unassigned!\n";
        }
    }

    $ret = 0;
    $ret += system($GenWpbTool." -s ".(2 * $HFAT_REQ_SIZE)." -p ".$OutDir."hfat -o ".$OutDir.$HiddenDrive.$HFAT_REQ_SIZE."KB -t h -r");
    die "[ERROR] mkfat failed!\n" if ($ret != 0);

    $HFAT_OUT_OBJ = (((stat($OutDir.$HiddenDrive.$HFAT_REQ_SIZE."KB.fat"))[7]) - 16) / (4 + 512);

    if (($HFAT_REQ_SIZE > 0) && ($HFAT_OUT_OBJ > ($HFAT_REQ_SIZE * 2)))
    {
        system("rm -f ".$OutDir."*.fat");
        die "[ERROR] Preload image large than HFAT_REQ_SIZE!\n";
    }
}

if ($ONBOARD_USER_STORAGE_SUPPORT == 0)
{
    $FatExistObject = 0;
    for $fname (glob $OutDir."*.fat")
    {
        $FatExistObject += (((stat($fname))[7]) - 16) / (4 + 512);
    }

    $MemReq = $APP_REQ_SIZE + &Ceiling($FatExistObject / 2 / 512 * 520);
    $RaiSize = $MemReq * 100 / (100 - $RaiReserveTrash);
    if ($RaiSize > ($MemReq + $RaiReserveTrashSpace))
    {
        $RaiSize = $MemReq + $RaiReserveTrashSpace;
    }

    $RaiSizeIn32k = &Ceiling($RaiSize / 32);

    if ($M18_MCP_SUPPORT == 1)
    {
        $RaiSizeIn32k = $RaiSizeIn32k * 2;
    }

    $RaiFormatChkSum = 65535 - $RaiSizeIn32k;
    $RaiEntriesNumber = int(($FatExistObject + $APP_REQ_OBJ_ENTRY) / 256) + 1;

    &UpdateE2pValue($OutDir."stack.e2p", "WRaiSizeIn32k", $RaiSizeIn32k);
    &UpdateE2pValue($OutDir."stack.e2p", "WRaiFormatChkSum", $RaiFormatChkSum);
    &UpdateE2pValue($OutDir."stack.e2p", "WRaiEntriesNumberExt", $RaiEntriesNumber);

    exit;
}

if ($AUTO_PARTITION_SUPPORT == 1)
{
    print "============== Auto Partition ... =============\n";

    if ($CHECK_SIZE_CRITICAL_MCP eq "")
    {
        die "[ERROR] Invalid parameter: CHECK_SIZE_CRITICAL_MCP\n";
    }
    if (($APP_REQ_SIZE eq "") || ($APP_REQ_SIZE < 0))
    {
        die "[ERROR] Invalid parameter: APP_REQ_SIZE\n";
    }
    if (($APP_REQ_OBJ_ENTRY eq "") || ($APP_REQ_OBJ_ENTRY < 0))
    {
        die "[ERROR] Invalid parameter: APP_REQ_OBJ_ENTRY\n";
    }
    if (($FAT_REQ_SIZE eq "") || ($FAT_REQ_SIZE < 0))
    {
        die "[ERROR] Invalid parameter: FAT_REQ_SIZE\n";
    }

    if ($FAT_PRELOAD_PATH)
    {
        system("cp -af ".$FAT_PRELOAD_PATH." ".$OutDir."fat");
    }

    # Parse CheckLog begin
    &UpdateE2pValue($OutDir."stack.e2p", "WRaiSizeIn32k", 0);
    system("make dlchk");
    open(CHECKLOG_FILE, "<CheckLog.txt") or die "[ERROR] Can't read \"CheckLog.txt\" file\n";
    
    if ($CRITICAL_LANGPACK eq "")
    {
        while (chomp($_lines = <CHECKLOG_FILE>))
        {
            if ($_lines =~ /.*Language Pack\(s\).*/)
            {
                last;
            }
        }
        $_maxlangsize = 0;
        while (chomp($_lines = <CHECKLOG_FILE>))
        {
            if ($_lines =~ /.*size.*/)
            {
                $_pos1 = index($_lines, ",");
                $_lang = substr($_lines, 0, $_pos1);
                $_lang =~ s/\s+//;
                $_pos2 = index($_lines, "=") + 1;
                $_langsize = substr($_lines, $_pos2);
                if ($_langsize > $_maxlangsize)
                {
                    $_maxlangsize = $_langsize;
                    $CRITICAL_LANGPACK = $_lang;
                }
            }
            else
            {
                last;
            }
        }
    }    

    $result = 0;

    while (chomp($_lines = <CHECKLOG_FILE>))
    {
        if ($_lines =~ /.*Flash Name.*$CHECK_SIZE_CRITICAL_MCP.*/)
        {
            $result = 1;
            last;
        }
    }

    die "[ERROR] Unsupport flash type\n" if($result == 0);

    while (chomp($_lines = <CHECKLOG_FILE>))
    {
        if ($_lines =~ /.*Region Number.*/)
        {
            $_pos1 = index($_lines, "=") + 1;
            $_pos2 = index($_lines, ",");
            $REG_NUM = substr($_lines, $_pos1, $_pos2 - $_pos1);
            last;
        }
    }

    while (chomp($_lines = <CHECKLOG_FILE>))
    {
        if ($_lines =~ /.*Sector Size.*/)
        {
            $REG_NUM = $REG_NUM - 1;
            $_pos1 = index($_lines, "=") + 1;
            $_pos2 = index($_lines, "KB");
            $_sector_size = substr($_lines, $_pos1, $_pos2 - $_pos1);
            push(@SECTOR, $_sector_size);
            if ($REG_NUM == 0)
            {
                last;
            }
        }
    }

    $result = 0;

    while(chomp($_lines = <CHECKLOG_FILE>))
    {
        if ($_lines =~ /.*$CRITICAL_LANGPACK.*/)
        {
            $_pos = rindex($_lines, "|") + 1;
            $_lines = substr($_lines, $_pos);
            for ($i = 0; $i < @SECTOR; $i++)
            {
                $_pos1 = index($_lines, ":") + 1;
                $_pos2 = index($_lines, "(");
                $_free_sector = substr($_lines, $_pos1, $_pos2 - $_pos1);
                push(@FREE_SECTOR, $_free_sector);            
                $_lines = substr($_lines, $_pos2 + 1);
            }
            $result = 1;
            last;
        }
    }

    die "[ERROR] CUS ".$CRITICAL_LANGPACK." not found!\n" if($result == 0);

    $RaiSizeIn32k = 0;

    for ($i = 0; $i < @SECTOR; $i++)
    {
        $_temp =  int($SECTOR[$i] / 32) * $FREE_SECTOR[$i];
        if ($_temp > $RaiSizeIn32k)
        {
            $RaiSizeIn32k = $_temp;
        }
    }

    close(CHECKLOG_FILE);
    # Parse CheckLog end

    $RaiReserveTrash = &ReadE2pValue($OutDir."stack.e2p", "WRaiReserveTrash");

    $RaiSize = $RaiSizeIn32k * 32;

    if ($M18_MCP_SUPPORT == 1)
    {
        $RaiSize = $RaiSize / 2;
    }

    if (($RaiSize * $RaiReserveTrash / 100) < $RaiReserveTrashSpace)
    {
        $RaiReserveTrashSpace = $RaiSize * $RaiReserveTrash / 100;
    }

    $MemReq = int($RaiSize - $RaiReserveTrashSpace);

    die "[ERROR] APP_REQ > Remaindar space" if ($MemReq < $APP_REQ_SIZE);

    $FatSize = $MemReq - $APP_REQ_SIZE;

    $FatSize = int($FatSize * 512 / 520);

    die "[ERROR] FatSize < FAT_REQ" if ($FatSize < $FAT_REQ_SIZE);

    $FatObject = $FatSize * 2;

    $FatExist = 0;
    for $fname (glob $OutDir."*.fat")
    {
        $FatExist += (((stat($fname))[7]) - 16) / (4 + 512);
    }
    $FatObject -= $FatExist;

    if ($FatObject < 6)
    {
        $FatObject = 0;
        print "[WARNING] Remaining space < 3KB, no FAT image is generated!";
    }
    else
    {
        $FAT_REQ_SIZE = int($FatObject / 2);
        $ret = 0;
        $ret += system($GenWpbTool." -s ".$FatObject." -p ".$OutDir."fat -o ".$OutDir.$UserDrive.$FAT_REQ_SIZE."KB -w -t b -r");
        $ret += system($GenWpbTool." -s ".$FatObject." -p ".$OutDir."fat -o ".$OutDir.$UserDrive." -t n -r");
        die "[ERROR] mkfat failed!\n" if ($ret != 0);

        $FAT_OUT_OBJ = (((stat($OutDir.$UserDrive.".fat"))[7]) - 16) / (4 + 512);

        if (($FAT_REQ_SIZE > 0) && ($FAT_OUT_OBJ > $FatObject))
        {
            system("rm -f ".$OutDir.$UserDrive.$FAT_REQ_SIZE."KB.wpb");
            system("rm -f ".$OutDir."*.fat");
            die "[ERROR] Preload image large than remaindar space!\n";
        }

        system("rm -f ".$OutDir.$UserDrive.".fat");
    }

    $RaiFormatChkSum = 65535 - $RaiSizeIn32k;

    $RaiEntriesNumber = int(($FatObject + $FatExist + $APP_REQ_OBJ_ENTRY) / 256) + 1;

    &UpdateE2pValue($OutDir."stack.e2p", "WRaiSizeIn32k", $RaiSizeIn32k);
    &UpdateE2pValue($OutDir."stack.e2p", "WRaiFormatChkSum", $RaiFormatChkSum);
    &UpdateE2pValue($OutDir."stack.e2p", "WRaiEntriesNumberExt", $RaiEntriesNumber);
}
else
{
    print "============== User Drive ... =================\n";

    if (($FAT_REQ_SIZE eq "") || ($FAT_REQ_SIZE < 0))
    {
        die "[ERROR] Invalid parameter: FAT_REQ_SIZE\n";
    }

    if (($FAT_REQ_SIZE > 0) && ($FAT_REQ_SIZE < 3))
    {
        die "[ERROR] Invalid parameter: FAT_REQ_SIZE < 3 KB\n";
    }

    if ($FAT_PRELOAD_PATH)
    {
        $ret = system("cp -af ".$FAT_PRELOAD_PATH." ".$OutDir."fat");
        die "[ERROR] Failed to copy preload!\n" if ($ret != 0);
    }
    else
    {                                                  
        if ($FAT_REQ_SIZE == 0)
        {
            print "[ERROR] Invalid parameter: Set FAT_REQ_SIZE to fit preload, but FAT_PRELOAD_PATH is unassigned!\n";
        }
    }

    $FatObject = 2 * $FAT_REQ_SIZE;

    if (($FAT_REQ_SIZE == 640) || ($FAT_REQ_SIZE == 720) || ($FAT_REQ_SIZE == 1200) || ($FAT_REQ_SIZE == 1440))
    {
        $FatObject -= 1;
    }

    $ret = 0;
    $ret += system($GenWpbTool." -s ".$FatObject." -p ".$OutDir."fat -o ".$OutDir.$UserDrive.$FAT_REQ_SIZE."KB -w -t b -r");
    $ret += system($GenWpbTool." -s ".$FatObject." -p ".$OutDir."fat -o ".$OutDir.$UserDrive." -t n -r");
    die "[ERROR] mkfat failed!\n" if ($ret != 0);

    $FAT_OUT_OBJ = (((stat($OutDir.$UserDrive.".fat"))[7]) - 16) / (4 + 512);

    if (($FAT_REQ_SIZE > 0) && ($FAT_OUT_OBJ > $FatObject))
    {
        system("rm -f ".$OutDir.$UserDrive.$FAT_REQ_SIZE."KB.wpb");
        system("rm -f ".$OutDir."*.fat");
        die "[ERROR] Preload image large than FAT_REQ_SIZE!\n";
    }

    $FatExistObject = 0;
    for $fname (glob $OutDir."*.fat")
    {
        $FatExistObject += (((stat($fname))[7]) - 16) / (4 + 512);
    }
    
    system("rm -f ".$OutDir.$UserDrive.".fat");

    $MemReq = $APP_REQ_SIZE + &Ceiling($FatExistObject / 2 / 512 * 520);
    $RaiSize = $MemReq * 100 / (100 - $RaiReserveTrash);
    if ($RaiSize > ($MemReq + $RaiReserveTrashSpace))
    {
        $RaiSize = $MemReq + $RaiReserveTrashSpace;
    }

    $RaiSizeIn32k = &Ceiling($RaiSize / 32);

    if ($M18_MCP_SUPPORT == 1)
    {
        $RaiSizeIn32k = $RaiSizeIn32k * 2;
    }

    $RaiFormatChkSum = 65535 - $RaiSizeIn32k;
    $RaiEntriesNumber = int(($FatExistObject + $APP_REQ_OBJ_ENTRY) / 256) + 1;

    &UpdateE2pValue($OutDir."stack.e2p", "WRaiSizeIn32k", $RaiSizeIn32k);
    &UpdateE2pValue($OutDir."stack.e2p", "WRaiFormatChkSum", $RaiFormatChkSum);
    &UpdateE2pValue($OutDir."stack.e2p", "WRaiEntriesNumberExt", $RaiEntriesNumber);
}

sub Ceiling
{
    $_temp = int($_[0]);

    if (($_[0] - $_temp) > 0)
    {
        $_temp = $_temp + 1;
    }
    $_temp;
}

sub ReadProduct
{
    open(CONFIG_FILE, "<config.mak") or die "[ERROR] cannot read \"config.mak\" file\n";
    while (chomp($_lines = <CONFIG_FILE>))
    {
        if ($_lines =~ s/PRODUCT:?=(.*)//)
        {
            $_product = $1;
            last;
        }
    }
    close(CONFIG_FILE);

    $_product;
}

sub ReadOptions
{
    open(OPTIONS_FILE, "<".$_[0]) or die "[ERROR] cannot read file : ".$_[0]."\n";
    while (chomp($_lines = <OPTIONS_FILE>))
    {
        if ($_lines =~ /^$_[1]./)
        {
            $_pos = index($_lines, "=");
            $_temp = substr($_lines, $_pos+1);
            $_temp =~ s/^ +//;
            $_temp =~ s/\r+$//;
            $_temp =~ s/\n+$//;
            $_temp =~ s/ +$//;
            $_options = $_temp;
            last; 
        }
    }
    close(OPTIONS_FILE);

    $_options;
}

sub ReadE2pValue
{
    open(E2P_FILE, "<".$_[0]) or die "[ERROR] cannot read \"stack.e2p\" file\n";
    while (chomp($_lines = <E2P_FILE>))
    {
        if ($_lines =~ /$_[1]./)
        {
            chomp($_lines = <E2P_FILE>);
            $_pos = index($_lines, " ");
            $_e2p = substr($_lines, 0, $_pos);
            last;
        }
    }
    close(E2P_FILE);

    $_e2p;
}

sub UpdateE2pValue
{
    open(E2P_INFILE, "<".$_[0]) or die "[ERROR] cannot read \"stack.e2p\" file\n";
    open(E2P_OUTFILE, ">"."stack.e2p") or die "[ERROR] cannot write \"stack.e2p\" file\n";    
    while (chomp($_lines = <E2P_INFILE>))
    {
        if (eof)
        {
            print E2P_OUTFILE $_lines."\n";
            last;
        }
    
        if ($_lines =~ /$_[1]./)
        {
            print E2P_OUTFILE $_lines."\n";
            chomp($_lines = <E2P_INFILE>);
            $_pos = index($_lines, " ");
            print E2P_OUTFILE  $_[2].substr($_lines, $_pos)."\n";
        }
        else
        {
            print E2P_OUTFILE $_lines."\n";
        }
    }
    close(E2P_INFILE);
    close(E2P_OUTFILE);

    move("stack.e2p", $_[0]);
}
