#!/usr/bin/perl

use warnings;
use strict;
use Cwd;

#$ perl tng/abi/parse_log.pl abilog.txt

# group mapping
our %group = (  "MMI", "Clark.Tseng"
                ,"MMI_WDG", "Max-cc.Huang"
                ,"MMI_SDK", "Mark.Kang"
                ,"Middleware", "Ken.Huang"
                ,"LCD", "Ken.Huang"
                ,"Driver", "Vincent.Liang"
                ,"System", "Vincent.Liang"
                ,"Stack", "Bart.Liang"
                ,"Stack-MDL", "Bart.Liang"
                ,"BlueTooth", "Davy.Tao"
                ,"WIFI", "Peter-jc.Lin"
                ,"undefined", "Darry.Huang"
                );

##########################
## 
##########################
sub search_owner_from_folder_list_xml
{
    my $xml_folder_list_file = $_[0];
    my $parent_path = $_[1];
    my $folder_name = $_[2];
    my $my_cat = "undefined";
    my $my_folder_owner = "undefined";
    my $find;
    my $line;
    my $flag = 0;
    
    $find = 0;
    
    open(XML_FILE, "<$xml_folder_list_file") or die "ERROR(parse_log): Cannot open file $xml_folder_list_file\n";
    while ($line = <XML_FILE>)
    {
        if($line =~ /<List Folder=\"$parent_path\">/)
        {
            $flag = 1;
        }
        if($flag eq 0)
        {
            next;
        }
        #<Folder Name="SrvWrapper" Lib="SrvWrapper.lib" Category="MMI" Owner="Christoph.Kuo/Jous.Chan"></Folder>
        if($line =~ /<Folder Name=\"$folder_name\" Lib=\"(.*)\" Category=\"(.*)\" Owner=\"(.*)\"><\/Folder>/)
        {
            #print "lib name: $1\n";
            if($2 ne "")
            {
                $my_cat = $2;
            }
            #print "category: $my_cat\n";
            if($3 ne "")
            {
                $my_folder_owner = $3;
            }
            #print "folder owner: $my_folder_owner\n";
            $find = 1;
            last;
        }
    }
    close(XML_FILE);
    
    if($find eq 0)
    {
        print "ERROR(parse_log): folder is not defined in folder_list.xml\n";
    }
    
    $_[3] = $my_cat;
    $_[4] = $my_folder_owner;    
}

##########################
## 
##########################
sub get_owner()
{
    my $xml_file = "./sc/customer/default/profile/ReleaseConfigurations_CUS_B3.xml";
    my $xml_folder_list_file = $_[0];
    my $checked_c_file = $_[1];
    my $make_file_path;
    my $line;
    my $my_cat = "undefined";
    my $my_folder_owner = "undefined";
    my $find = 0;
    
    open(XML_FILE, "<$xml_file") or die "ERROR(parse_log): Cannot open file $xml_file\n";
    while ($line = <XML_FILE>)
    {
        if($line =~ /<make_name>(.*)<\/make_name>/)
        {
            $make_file_path = $1;
        }
        if($line =~ /<file_name>$checked_c_file<\/file_name>/)
        {
            print "make file: $make_file_path\n";
            $find = 1;
            last;
        }
    }
    close(XML_FILE);
    
    if($find eq 1)
    {
        my $folder_name = "";
        my $parent_path = "";
        my $idx;
        
        # get folder name
        # ex:sc/application/mmi/SrvWrapper/SrvWrapper.mak
        if($make_file_path =~ /\/(.*)\/(.*)\.mak$/g)
        {
            #print "$1\n";
            $idx = rindex($1, "/");
            #print "$idx\n";
            $folder_name = substr($1, $idx+1);
            $parent_path = substr($1, 0, $idx);
            $parent_path = "./sc/".$parent_path;
            print "folder name: $folder_name\n";
        }
        else
        {
            print "ERROR(parse_log): can not get the folder name!\n";
        }
        
        &search_owner_from_folder_list_xml($xml_folder_list_file, $parent_path, $folder_name, $my_cat, $my_folder_owner);        
    }
    else
    {        
        print "ERROR(parse_log): c file is not defined in ReleaseConfigurations_CUS_B3.xml\n";
    }
    
    $_[2] = $my_cat;
    $_[3] = $my_folder_owner;
}

##########################
## 
##########################
sub parse_log()
{
    my $log_file = $_[0];
    my $folder_list_xml = $_[1];
    my @error_c_list = @{$_[2]};
    my @error_category_list = @{$_[3]};
    my @error_owner_list = @{$_[4]}; 
    my $line_data;
    
    open(FILE, "<$log_file") or die "ERROR(parse_log): Cannot open file $log_file\n";
    while ($line_data = <FILE>)
    {
        my $c_file;
        my $category;
        my $owner;
    
        if($line_data =~ /compile error in (.*?)$/)
        {
            $c_file = $1;
            print "compile error in $c_file\n";
            push @error_c_list, $c_file;
            &get_owner($folder_list_xml, $c_file, $category, $owner);
            print "category = $category, folder owner = $owner\n";
            push @error_category_list, $category;
            push @error_owner_list, $owner;
            
            print "\n";
        }       
    }
    close(FILE);
    
    @{$_[2]} = @error_c_list;
    @{$_[3]} = @error_category_list;
    @{$_[4]} = @error_owner_list;
}

$;
