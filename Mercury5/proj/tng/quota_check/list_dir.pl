#!/usr/bin/perl

use warnings;
use strict;
use Cwd;

#####
## SYNTAX:
## $ perl tng/quota_check/list_dir.pl  D:/EMMI/EMMI/branch/v2.04.04/proj/tng/quota_check/folder_list.xml D:/EMMI/EMMI/branch/v2.04.04/proj/tng/quota_check/category_setting_8532_64_32_mb406g.xml D:/EMMI/EMMI/branch/v2.04.04/proj/tng/quota_check/folder_list2.xml
#####

#output file
my $input_xml = shift;
my $input_cat = shift;
my $output_file = shift;
my $pwd = getcwd;

# global variable
my @category_type = ();

# checked folder list
my @folder_list1
    = (
         "./sc/driver/drv"
        ,"./sc/customer/product/cust"
        ,"./sc/customer/default/src/drv"
        ,"./sc/driver/hal/msw8533x/"
        ,"./sc/middleware"
        ,"./sc/system"
        ,"./sc/telecom"
        ,"./sc/telserv"
      );

my @folder_list2
    = (
         "./sc/application/3rd"
        ,"./sc/application/3rd/utility"
        ,"./sc/application/mmi"
        ,"./sc/application/mmi/cus"
        ,"./sc/application/mmi/app"
        ,"./sc/application/mmi/srv"
        ,"./sc/application/sys"
      );
      
sub list_dir()
{
    my $folder = shift;
    my $level = shift;
    my $enter = shift;
    my @find_files = <*>;
    my @saved_name = ();
    my @saved_lib = ();
    my @saved_category = ();
    my @saved_owner = ();
    my $secton = 0;
    my $secton_checked = 99;    
    my $index;

    print "\nlist folder: $folder\n";
    
    # get the old define
    open (INP_FILE,"<$input_xml") || die("Cannot Open File $input_xml");
    for my $line (<INP_FILE>)
    {
        if($line =~ /<List Folder=/)
        {
            $secton += 1;
            
            if($line =~ /$folder *\"> *$/)
            {
                $secton_checked = $secton;
                next;
            }            
            next;
        }

        if($line =~ " </List>")
        {
            $secton -= 1;
            if($secton < $secton_checked)
            {
                $secton_checked = 99;
            }
            next;
        }
        
        if($secton eq $secton_checked)
        {           
            #<Folder Name="wlan" Lib="wlan_drv.lib" Category="Driver" Owner="john.chen/john.chen"></Folder>
            if($line =~ /Name *= *\"(.*)\" *Lib *= *\"(.*)\" *Category *= *\"(.*)\" Owner *= *\"(.*)\" */)
            {
                my $found = 0;
             
                if($1 eq "" or $2 eq "" or $3 eq "" or $4 eq "")
                {
                    #print "ERROR: format incorrect![1]\n$line ";
                }
                else
                {
                    foreach(@category_type)
                    {
                        if($3 eq $_)
                        {
                            $found  = 1;
                            last;
                        }
                    }
                    if($found eq 0)
                    {
                        print "ERROR: categoy is set incorrect![2] $line\n";
                    }
                }
                push @saved_name, $1;
                push @saved_lib, $2;
                push @saved_category, $3;
                push @saved_owner, $4;
            }
            else
            {
                my $found = 0;
                
                for my $f (@folder_list2)
    	        {
    	            if($f eq "$folder")
    	            {
    	                $found = 1;
    	                last;
    	            }
    	        }
    	        if($folder eq "./sc/application")
    	        {
                    $found = 1;
    	        }
    	        if($found eq 0)
    	        {
                    print "ERROR: format incorrect![3]\nfolder:$folder\n$line ";
                }
            }
        }
    }
    close(INP_FILE);
    
    # check files
    for(my $i=0; $i<$enter; $i++)
    {
        print XML_FILE "  ";  
    }
    print XML_FILE "  <List Folder=\"$folder\">\n";
    for my $prd (sort(@find_files))
    {
        if(! -d $prd)
        {
            next;
        }
    	if($prd !~ /^\.$/ && $prd !~ /^\.\.$/)
    	{
    	    my $lib = "";
            my $cat = "";
            my $owner = "";
    	    
    	    if($level eq 1)
    	    {
    	        my $sub_folder;
    	        my $found = 0;
    	        
    	        for my $f (@folder_list2)
    	        {
    	            if($f eq "$folder/$prd")
    	            {
    	                $found = 1;
    	                $sub_folder = $f;
    	            }
    	        }
    	        
    	        if($found eq 1)
    	        {
    	            chdir "$pwd/$sub_folder";
    	            &list_dir($sub_folder, 1, $enter+1);
    	            chdir "../";
    	        }
    	        else
    	        {
    	            goto _OUT;
    	        }
    	    }
    	    else
    	    {
_OUT:
                my $found = 0;
                
                $index = 0;
                
                for($index = 0; $index<@saved_name; $index++)
                {
                    if($saved_name[$index] eq $prd)
                    {
                        $found = 1;
                        last;
                    } 
                }
                
                if($found eq 1)
                {
                    $lib = $saved_lib[$index];
                    $cat = $saved_category[$index];
                    $owner = $saved_owner[$index];
                }
                else
                {
                    if($folder =~ "sc/application/mmi")
                    {
                        $cat = "MMI";
                    }
                }
                       
	            for(my $i=0; $i<$enter; $i++)
	            {
	                print XML_FILE "  ";  
	            }    	        
                print XML_FILE "    <Folder Name=\"$prd\" Lib=\"$lib\" Category=\"$cat\" Owner=\"$owner\"></Folder>\n";
            }
    	}
    }
    for(my $i=0; $i<$enter; $i++)
    {
        print XML_FILE "  ";  
    }    
    print XML_FILE "  </List>\n";
}

# main
if(! -e $input_xml)
{
    print "can not find $input_xml\n";
    exit 1;
}

# get category type
open (CAT_FILE,"<$input_cat") || die("Cannot Open File $input_cat");
for my $line (<CAT_FILE>)
{
    #<CATEGORY Name="ARMThumb"         ROM_LIMIT_SIZE="0"          RAM_LIMIT_SIZE="0"          Rule="-1" />
    if($line =~ /Name *= *\"(.*)\" *ROM_LIMIT_SIZE/)
    {
        my $tmp = $1;
        
        if($tmp =~ /,/)
        {
            my @tmp_array = split /,/, $tmp; 
            
            foreach(@tmp_array)
            {
                push @category_type, $_;
            }
        }
        else
        {
            push @category_type, $1;
        }
    }
}
close(CAT_FILE);

if(-e $output_file)
{
    system("rm -f $output_file");
}
open (XML_FILE,">>$output_file") || die("Cannot Open File $output_file");
print XML_FILE "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
print XML_FILE "<All>\n";

chdir "./sc/application/";
&list_dir("./sc/application" , 1, 0);
chdir "$pwd";
for my $folder (@folder_list1)
{
    chdir "$folder";
    &list_dir($folder, 0, 0);
    chdir "$pwd";
}

print XML_FILE "</All>\n";
close(XML_FILE);
print "\ndone!\n";