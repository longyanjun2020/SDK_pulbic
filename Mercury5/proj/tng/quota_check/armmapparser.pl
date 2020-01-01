#!/usr/bin/perl

use warnings;
use strict;

if((@ARGV ne 2) && (@ARGV ne 1))
{
    print "\nUsage: perl tng/quota_check/armmapparser.pl link1.info link2.info\n" ;
    exit 1;
}

my $mode_diff = 1;
my $folder_list_file = "./tng/quota_check/folder_list.xml";
my $object_mapping_file = "./tng/quota_check/object_mapping.xml";
my $link_info_file1 = "";
my $link_info_file2 = "";
my $output1 = "./1.xls";
my $output2 = "./2.xls";
my $rom_diff_file = "./rom_diff.xls";
my $ram_diff_file = "./ram_diff.xls";
my $debug = 0;
my $key;	
my %area;
my %lib2cat;
my %obj2lib_def;
my %obj2lib;
my $on_error = 0;

my %cat_rom_size1;
my %cat_ram_size1;
my %lib_rom_size1;
my %lib_ram_size1;
my %obj_rom_size1;
my %obj_ram_size1;
my %cat_rom_size2;
my %cat_ram_size2;
my %lib_rom_size2;
my %lib_ram_size2;
my %obj_rom_size2;
my %obj_ram_size2;

$area{"Code   RO"} = "ROM";
$area{"Data   RO"} = "ROM";
$area{"Data   RW"} = "ROM";
$area{"Zero   RW"} = "RAM";
$area{"Ven    RO"} = "ROM";

$obj2lib_def{"PAD"}="PAD";
$obj2lib_def{"anon\$\$obj.o"}='ARM<->Thumb';

$lib2cat{"PAD"}="Padding";
$lib2cat{"ARM<->Thumb"}="ARMThumb Veneer";

if(@ARGV eq 1)
{
    $mode_diff = 0;
    $link_info_file1 = shift(@ARGV);
}
else
{
    $link_info_file1 = shift(@ARGV);
    $link_info_file2 = shift(@ARGV);
}

sub load_setting()
{    
    # load category setting
    open FOLDER_LIST, "<$folder_list_file" or die "Folder list $folder_list_file not found\n";
    while (<FOLDER_LIST>)
    {
        my $lib;
        my $cat;
        my $tmp;
        
        #<Folder Name="Maxi" Lib="" Category="SDK" Owner="Eric.Shen/Randy.Wu"></Folder>
        if(/ *<Folder Name *= *\"(.*)\" *Lib *= *\"(.*)\" *Category *= *\"(.*) *\" Owner *= *\"(.*)\" */)
        {   
            $lib = $2;
            $cat = $3;
            if(($lib ne "") && ($cat ne ""))
            {
                $tmp = $lib;
                $tmp =~ s/,/ /g;
                
                my @tmp_array = split(/ /, $tmp);
                            
                foreach(@tmp_array)
                {
                    $lib2cat{"$_"} = "$cat";
                }
            }
        }
    }
    close FOLDER_LIST;
    
    #load object setting
    open OBJECT_MAPPING, "<$object_mapping_file" or die "Object mapping file $object_mapping_file not found\n";
    while (<OBJECT_MAPPING>)
    {
        my $lib;
        my $cat;
        my $tmp;
        
        #<OBJECT Name="cust_lcd_HX8346_yk701.o" LIB="cust_drv.lib" CATEGORY="Driver" />
        if(/ *<OBJECT Name *= *\"(.*)\" *LIB *= *\"(.*)\" *CATEGORY *= *\"(.*)\" *\/>/)
        {   
            $tmp = $1;
            $lib = $2;
            $cat = $3;
            $obj2lib_def{"$tmp"}="$lib";
        }
    }
    close OBJECT_MAPPING;
}

sub parse_link_info()
{
    my $my_link_info = $_[0];
    my %my_cat_rom_size = %{$_[1]};
    my %my_cat_ram_size = %{$_[2]};
    my %my_lib_rom_size = %{$_[3]};
    my %my_lib_ram_size = %{$_[4]};
    my %my_obj_rom_size = %{$_[5]};
    my %my_obj_ram_size = %{$_[6]};
    my $my_output_file = $_[7];
    my $my_save_obj2lib = $_[8];
    
    my $line_cunter=0;
    
    open MAP_FILE, "<$my_link_info" or die "LinkInfo $my_link_info not found\n";
    open LOG_FILE, ">$my_output_file" or die "Output file $my_output_file can not be created\n";
    
    # write header of output
    printf LOG_FILE "%s\t%s\t%s\t%s\t%s\n", "Category", "Section", "Length", "Lib Name", "Obj Name";
    
    # read map file
    while (<MAP_FILE>)
    {
    	chomp;
    	$line_cunter += 1;
    	if (/^\s*Memory Map of the image\s*/)
    	{
    		last;
    	}
    }
    
    while (<MAP_FILE>)
    {
    	my $len = 0;
    	my $link_section = "";
    	my $section = "";
    	my $objfile = "";
    	my $libfile = "";
    	my $catfile = "";
        my $cur_cat_hash;
        my $cur_lib_hash;
        my $cur_obj_hash;
    	
    	$line_cunter += 1;
    	#0x00000000   0x00000024   Code   RO        20063  * AAA_vectors         sys_boot_g1.o(sys.lib)
    	#0x0018d7d8   0x0000096c   Code   RO        36401    .text               mux_ctx.o(mux.lib)
    	$_ =~ s/avp_ms-mem/avp_ms_mem/g;
    	if (/^\s*0x[\da-f]+\s*0x([\da-f]+)\s*(Code   RO|Data   RO|Data   RW|Zero   RW|Ven    RO)\s+\d+\s+\*?\s+[\w\.!\$]+\s+([\w\.\$]+)\(([\w\.]+)\)/)
    	{
    		#printf LOG_FILE "$1 $2 $3 $4\n";
    		$len = hex($1);
    		$section = $2;
    		$objfile = $3;
    		$libfile = $4;
    	}
    	
    	#0x000000b4   0x00000008   Code   RO         1089    .text               stack_2.axf
    	elsif (/^\s*0x[\da-f]+\s*0x([\da-f]+)\s*(Code   RO|Data   RO|Data   RW|Zero   RW|Ven    RO)\s+\d+\s+\*?\s+[\w\.!\$]+\s+([\w\.\$]+)/)
    	{
    		#printf LOG_FILE "$1 $2 $3\n";
    		$len = hex($1);
    		$section = $2;
    		$objfile = $3;
    		$libfile = "";
    	}
    	
    	#0x1011afe5   0x00000003   PAD
    	elsif (/^\s*0x([\da-f]+)\s*0x([\da-f]+)\s*PAD\s*/)
    	{
    		$len = hex($2);
    		if (hex($1) >= 0x10000000)
    		{
    			$section = "Data   RW";
    		}
    		else
    		{
    			$section = "Code   RO";
    		}
    		$objfile = "PAD";
    		$libfile = "";
    	}
    	elsif (/^\s*Image component sizes\s*/)
    	{
    		last;
    	}
    	else
    	{
    		next;
    	}
    	
    	if (exists $area{$section})
    	{
    	    $link_section = $section;
    		$section = $area{$section};
    	}
    	else
    	{
    		print "Error - not found section $section\n";
    		$on_error = 1;
    	}
    
    	if ($libfile eq "" && exists $obj2lib_def{$objfile})
    	{
    		$libfile = $obj2lib_def{$objfile};
    	}
    		
    	if (exists $lib2cat{$libfile})
    	{
    		$catfile = $lib2cat{$libfile}
    	}
    	else
    	{
    		print "Error - not found library to category Line: $., $libfile\n";
    		$on_error = 1;
    	}
    	
    	#Category	Section	Length	Lib Name	Obj Name
    	printf LOG_FILE "%s\t%s\t%d\t%s\t%s\n", $catfile, $section, $len, $libfile, $objfile;
    
        if($section eq "ROM")
        {
            $cur_cat_hash = \%my_cat_rom_size;
            $cur_lib_hash = \%my_lib_rom_size;
            $cur_obj_hash = \%my_obj_rom_size;
        }
        elsif($section eq "RAM")
        {
            $cur_cat_hash = \%my_cat_ram_size;
            $cur_lib_hash = \%my_lib_ram_size;
            $cur_obj_hash = \%my_obj_ram_size;
        }
        else
        {
            print "Error - not found section\n";
            $on_error = 1;
        }
    
    	if (exists $cur_cat_hash->{$catfile})
    	{
    		$cur_cat_hash->{$catfile} = $cur_cat_hash->{$catfile} + $len;
    	}
    	else
    	{
    		$cur_cat_hash->{$catfile} = $len;
    	}
    		
    	if($libfile eq "")
    	{
    		print "Error - not found library to category Line: [$line_cunter][$catfile][$section][$len][$libfile][$objfile]\n";
    		$on_error = 1;
    	}
    
    	if (exists $cur_lib_hash->{$libfile})
    	{
    		$cur_lib_hash->{$libfile} = $cur_lib_hash->{$libfile} + $len;
    	}
    	else
    	{
    		$cur_lib_hash->{$libfile} = $len;
    	}
    
    	if (exists $cur_obj_hash->{$objfile})
    	{
    		$cur_obj_hash->{$objfile} = $cur_obj_hash->{$objfile} + $len;
    	}
    	else
    	{
    		$cur_obj_hash->{$objfile} = $len;
    	}
    	
    	if($my_save_obj2lib eq 1)
    	{
            if (! exists $obj2lib{$objfile})
            {
                $obj2lib{"$objfile"} = "$libfile";
            }
        }
            	
    	if($link_section eq "Data   RW")
    	{
            $cur_cat_hash = \%my_cat_ram_size;
            $cur_lib_hash = \%my_lib_ram_size;
            $cur_obj_hash = \%my_obj_ram_size;
            
        	if (exists $cur_cat_hash->{$catfile})
        	{
        		$cur_cat_hash->{$catfile} = $cur_cat_hash->{$catfile} + $len;
        	}
        	else
        	{
        		$cur_cat_hash->{$catfile} = $len;
        	}
        		
        	if($libfile eq "")
        	{
        		print "Error - not found library to category Line: [$line_cunter][$catfile][$section][$len][$libfile][$objfile]\n";
        		$on_error = 1;
        	}
        
        	if (exists $cur_lib_hash->{$libfile})
        	{
        		$cur_lib_hash->{$libfile} = $cur_lib_hash->{$libfile} + $len;
        	}
        	else
        	{
        		$cur_lib_hash->{$libfile} = $len;
        	}
        
        	if (exists $cur_obj_hash->{$objfile})
        	{
        		$cur_obj_hash->{$objfile} = $cur_obj_hash->{$objfile} + $len;
        	}
        	else
        	{
        		$cur_obj_hash->{$objfile} = $len;
        	}
    	}   	
    } 
    
	close MAP_FILE;
	close LOG_FILE;

    %{$_[1]} = %my_cat_rom_size; # call by reference
    %{$_[2]} = %my_cat_ram_size; # call by reference
    %{$_[3]} = %my_lib_rom_size; # call by reference
    %{$_[4]} = %my_lib_ram_size; # call by reference
    %{$_[5]} = %my_obj_rom_size; # call by reference
    %{$_[6]} = %my_obj_ram_size; # call by reference
	
}

sub sync_list()
{
    my %my_hash1 = %{$_[0]};
    my %my_hash2 = %{$_[1]};
    my %my_add = ();
    my %my_remove = ();
        
    foreach $key (keys %my_hash1)
    {
        if (exists $my_hash2{$key})
        {
            next;
        }
       
        if (! exists $my_remove{$key})
        {
            $my_remove{"$key"}="$key";
        }
    }
    
    foreach $key (keys %my_hash2)
    {
        if (exists $my_hash1{$key})
        {
            next;
        }
       
        if (! exists $my_add{$key})
        {
            $my_add{"$key"}="$key";
        }
    }
    
    foreach $key (keys %my_add)
    {
        $my_hash1{"$key"}="?";
    }
    foreach $key (keys %my_remove)
    {
        $my_hash2{"$key"}="?";
    }

    %{$_[0]} = %my_hash1; # call by reference
    %{$_[1]} = %my_hash2; # call by reference
}

sub fmt_write()
{
    my $WRITE_FILE = $_[0];
    my $cat = $_[1];
    my $item1 = $_[2];
    my $item2 = $_[3];
    my $item3 = $_[4];
    my $diff;
    my $v1 = 0;
    my $v2 = 0;
    
    if($item2 ne "?")
    {
        $v1 = int($item2);
    }
    if($item3 ne "?")
    {
        $v2 = int($item3);
    }
    $diff = $v2 - $v1;
    printf $WRITE_FILE "%s\t%s\t%s\t%s\t%d\n", "$cat", "$item1", "$item2", "$item3", $diff;
}

sub diff()
{
    my $my_link_file1 = shift;
    my $my_link_file2 = shift;
    my $my_rom_diff_file = shift;
    my $my_ram_diff_file = shift;
    my %my_cat_rom_size1 = %{$_[0]};
    my %my_cat_ram_size1 = %{$_[1]};
    my %my_lib_rom_size1 = %{$_[2]};
    my %my_lib_ram_size1 = %{$_[3]};
    my %my_obj_rom_size1 = %{$_[4]};
    my %my_obj_ram_size1 = %{$_[5]};
    my %my_cat_rom_size2 = %{$_[6]};
    my %my_cat_ram_size2 = %{$_[7]};
    my %my_lib_rom_size2 = %{$_[8]};
    my %my_lib_ram_size2 = %{$_[9]};
    my %my_obj_rom_size2 = %{$_[10]};
    my %my_obj_ram_size2 = %{$_[11]};
    my $tmp;
    my $cat;

    # write rom diff file
    open DIFF_FILE, ">$my_rom_diff_file" or die "Output file $my_rom_diff_file can not be created\n";
    # write header of output
    printf DIFF_FILE "%s\t%s\t%s\t%s\t%s\n", "", "", "$my_link_file1", "$my_link_file2", "Diff";
    foreach $key (sort keys %my_cat_rom_size1)
    {
        $tmp = $my_cat_rom_size2{$key};
        &fmt_write(*DIFF_FILE, "", $key, $my_cat_rom_size1{$key}, $tmp);        
    }
    printf DIFF_FILE "\n\n%s\t%s\t%s\t%s\t%s\n", "", "Library", "$my_link_file1", "$my_link_file2", "Diff";
    foreach $key (sort keys %my_lib_rom_size1)
    {
        $tmp = $my_lib_rom_size2{$key};
        $cat = $lib2cat{$key};
        &fmt_write(*DIFF_FILE, $cat, $key, $my_lib_rom_size1{$key}, $tmp);
    }
    printf DIFF_FILE "\n\n%s\t%s\t%s\t%s\t%s\n", "", "Object", "$my_link_file1", "$my_link_file2", "Diff";
    foreach $key (sort keys %my_obj_rom_size1)
    {
        $tmp = $my_obj_rom_size2{$key};
        $cat = $obj2lib{$key};
        &fmt_write(*DIFF_FILE, $cat, $key, $my_obj_rom_size1{$key}, $tmp);
    }
    printf DIFF_FILE "%s\n\n", " ";
    close DIFF_FILE;

    # write ram diff file
    open DIFF_FILE, ">$my_ram_diff_file" or die "Output file $my_ram_diff_file can not be created\n";
    # write header of output
    printf DIFF_FILE "%s\t%s\t%s\t%s\t%s\n", "", "", "$my_link_file1", "$my_link_file2", "Diff";
    
    foreach $key (sort keys %my_cat_ram_size1)
    {
        $tmp = $my_cat_ram_size2{$key};
        &fmt_write(*DIFF_FILE, "", $key, $my_cat_ram_size1{$key}, $tmp);
    }
    printf DIFF_FILE "\n\n%s\t%s\t%s\t%s\t%s\n", "", "Library", "$my_link_file1", "$my_link_file2", "Diff";
    foreach $key (sort keys %my_lib_ram_size1)
    {
        $tmp = $my_lib_ram_size2{$key};
        $cat = $lib2cat{$key};        
        &fmt_write(*DIFF_FILE, $cat, $key, $my_lib_ram_size1{$key}, $tmp);
    }
    printf DIFF_FILE "\n\n%s\t%s\t%s\t%s\t%s\n", "", "Object", "$my_link_file1", "$my_link_file2", "Diff";
    foreach $key (sort keys %my_obj_ram_size1)
    {
        $tmp = $my_obj_ram_size2{$key};
        $cat = $obj2lib{$key};
        &fmt_write(*DIFF_FILE, $cat, $key, $my_obj_ram_size1{$key}, $tmp);
    }
    printf DIFF_FILE "%s\n\n", " ";

    close DIFF_FILE;
}

# main

&load_setting();

#check setting file content integraty
die "[Area_Definition] is empty" if (!%area);
die "[Lib_To_Category] is empty" if (!%lib2cat);

if($output1 ne "")
{
    system("rm -f $output1");
}
if($output2 ne "")
{
    system("rm -f $output2");
}
if($rom_diff_file ne "")
{
    system("rm -f $rom_diff_file");
}
if($ram_diff_file ne "")
{
    system("rm -f $ram_diff_file");
}

&parse_link_info(
    $link_info_file1
    ,\%cat_rom_size1
    ,\%cat_ram_size1
    ,\%lib_rom_size1
    ,\%lib_ram_size1
    ,\%obj_rom_size1
    ,\%obj_ram_size1
    ,"$output1"
    ,0
    );
    
if($mode_diff eq 1)
{
    &parse_link_info(
        $link_info_file2
        ,\%cat_rom_size2
        ,\%cat_ram_size2
        ,\%lib_rom_size2
        ,\%lib_ram_size2
        ,\%obj_rom_size2
        ,\%obj_ram_size2
        ,"$output2"
        ,1
        );
    
    if($debug eq 1)
    {       
        print "\nCategory(ROM)1:\n";
        foreach $key (sort keys %cat_rom_size1)
        {
            print "$key = $cat_rom_size1{$key}\n";
        }
        
        print "\nCategory(RAM)1:\n";
        foreach $key (sort keys %cat_ram_size1)
        {
            print "$key = $cat_ram_size1{$key}\n";
        }
        
        print "\nLibary(ROM)1:\n";
        foreach $key (sort keys %lib_rom_size1)
        {
            print "$key = $lib_rom_size1{$key}\n";
        }
        
        print "\nLibary(RAM)1:\n";
        foreach $key (sort keys %lib_ram_size1)
        {
            print "$key = $lib_ram_size1{$key}\n";
        }
        
        print "\n";
        
        print "\nCategory(ROM)2:\n";
        foreach $key (sort keys %cat_rom_size2)
        {
            print "$key = $cat_rom_size2{$key}\n";
        }
        
        print "\nCategory(RAM)2:\n";
        foreach $key (sort keys %cat_ram_size2)
        {
            print "$key = $cat_ram_size2{$key}\n";
        }
        
        print "\nLibary(ROM)2:\n";
        foreach $key (sort keys %lib_rom_size2)
        {
            print "$key = $lib_rom_size2{$key}\n";
        }
        
        print "\nLibary(RAM)2:\n";
        foreach $key (sort keys %lib_ram_size2)
        {
            print "$key = $lib_ram_size2{$key}\n";
        }
    }
    
    if($on_error eq 1)
    {
        goto _ON_ERR;
    }
    # sync lib list
    &sync_list(\%lib_rom_size1, \%lib_rom_size2);
    &sync_list(\%lib_ram_size1, \%lib_ram_size2);
    &sync_list(\%obj_rom_size1, \%obj_rom_size2);
    &sync_list(\%obj_ram_size1, \%obj_ram_size2);
    
    # diff
    &diff(  $link_info_file1
            ,$link_info_file2
            ,$rom_diff_file
            ,$ram_diff_file
            ,\%cat_rom_size1
            ,\%cat_ram_size1
            ,\%lib_rom_size1
            ,\%lib_ram_size1
            ,\%obj_rom_size1
            ,\%obj_ram_size1
            ,\%cat_rom_size2
            ,\%cat_ram_size2
            ,\%lib_rom_size2
            ,\%lib_ram_size2
            ,\%obj_rom_size2
            ,\%obj_ram_size2
             );
}

_ON_ERR:

print "\nDone!\n"

