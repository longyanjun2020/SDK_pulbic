#!/usr/bin/perl

use warnings;
use strict;

#$ build_process.pl [DailyBuild|DailyBuild_MCD|HourlyBuild|RelPkg_Full|RelPkg_Chip|RelPkg_Keep|RelPkg_VT|CmnLib_Target|CmnLib_Simu] input_file output_file
#
#$ perl tng/build_process/build_process.pl HourlyBuild tng/build_process/Product_Settings.txt HourlyBuild_Settings.txt

if (($#ARGV+1) ne 3)
{
    print "usage: perl tng/build_process/build_process.pl HourlyBuild tng/build_process/Product_Settings.txt HourlyBuild_Settings.txt\n";
    exit 1;   
}

my $exe_type = shift;
my $input_file = shift;
my $output_file = shift;
my $section = 0;
my $section_name;

# variable
my $line_counter = 0;
my $line_data;
my @setting_file_content = ();
my $true_str = "True";
my $false_str = "False";

# daily build
my @db_product_list = ();
my @db_flag_target = ();
my @db_flag_simulator = ();
my @db_flag_prepare_lib = ();

# daily build mcd
my @db_mcd_product_list = ();
my @db_mcd_flag_target = ();
my @db_mcd_flag_simulator = ();
my @db_mcd_flag_prepare_lib = ();

# hourly build
my @hb_product_list = ();
my @hb_flag_target = ();
my @hb_flag_simulator = ();
my @hb_flag_prepare_lib = ();

# release pacakge - full build
my @rp_fb_product_list = ();
my @rp_fb_flag_target = ();
my @rp_fb_flag_simulator = ();

# release pacakge - chip build
my @rp_cb_product_list = ();
my @rp_cb_flag_target = ();
my @rp_cb_flag_simulator = ();

# release pacakge - keep product
my @rp_kp_product_list = ();
my @rp_kp_flag_target = ();
my @rp_kp_flag_simulator = ();

# release pacakge - vt build
my @rp_vtb_product_list = ();
my @rp_vtb_flag_target = ();
my @rp_vtb_flag_simulator = ();

# common lib check
my @cl_product_list = ();
my @cl_flag_target = ();
my @cl_flag_simulator = ();

##########################################
# add arry data                          #
##########################################
sub add_array_data()
{
    my $my_section = shift;
    my $my_product = shift;
    my $my_target = shift;
    my $my_simulator = shift;
    my $my_flag_prepare_lib = shift;    

    #print "get_array_list()\n";
    
    if($my_section eq "Daily build")
    {
        push @db_product_list, $my_product;
        push @db_flag_target, $my_target;
        push @db_flag_simulator, $my_simulator;
        print "$my_flag_prepare_lib\n\n\n\n\n";
        push @db_flag_prepare_lib, $my_flag_prepare_lib;
    }
    elsif($my_section eq "Daily build MCD")
    {
        push @db_mcd_product_list, $my_product;
        push @db_mcd_flag_target, $my_target;
        push @db_mcd_flag_simulator, $my_simulator;        
        push @db_mcd_flag_prepare_lib, $my_flag_prepare_lib;
    }
    elsif($my_section eq "Hourly build")
    {
        push @hb_product_list, $my_product;
        push @hb_flag_target, $my_target;
        push @hb_flag_simulator, $my_simulator;        
        push @hb_flag_prepare_lib, $my_flag_prepare_lib;
    }
    elsif($my_section eq "Release package ¡V Full build")
    {
        push @rp_fb_product_list, $my_product;
        push @rp_fb_flag_target, $my_target;
        push @rp_fb_flag_simulator, $my_simulator;        
    }
    elsif($my_section eq "Release package - Chip build")
    {
        push @rp_cb_product_list, $my_product;
        push @rp_cb_flag_target, $my_target;
        push @rp_cb_flag_simulator, $my_simulator;        
    }
    elsif($my_section eq "Release package - Keep product")
    {
        push @rp_kp_product_list, $my_product;
        push @rp_kp_flag_target, $my_target;
        push @rp_kp_flag_simulator, $my_simulator;        
    }
    elsif($my_section eq "Release package - VT build")
    {
        push @rp_vtb_product_list, $my_product;
        push @rp_vtb_flag_target, $my_target;
        push @rp_vtb_flag_simulator, $my_simulator;        
    }    
    elsif($my_section eq "Common lib check")
    {
        push @cl_product_list, $my_product;
        push @cl_flag_target, $my_target;
        push @cl_flag_simulator, $my_simulator;        
    }
    elsif($my_section eq "Library compare pair list")
    {
        # TBD 
    }
    else
    {
        print "\nERROR: \"$my_section\" is not supported\n";
        exit 1;        
    }
    
    return 0;
}

##########################################
# gen file for daily server              #
##########################################
sub gen_file_for_build_server
{
    my @my_product_list = @{$_[0]};
    my @my_flag_target = @{$_[1]};
    my @my_flag_simulator = @{$_[2]};
    my @my_flag_prepare_lib = @{$_[3]};
    
    my $idx = 0;
    
    print "    FLAG_STUDIO_BUILD = ";
    print OUT_FILE "FLAG_STUDIO_BUILD = ";
    foreach(@my_flag_simulator)
    {
        print "$_";
        print OUT_FILE "$_";
        $idx++;
        if($idx ne @my_flag_simulator)
        {
            print ",";
            print OUT_FILE ",";
        }
        else
        {
            print "\n";
            print OUT_FILE "\n";
        }
    }
    $idx = 0;
    print "    FLAG_PREPARE = ";
    print OUT_FILE "FLAG_PREPARE = ";
    foreach(@my_flag_prepare_lib)
    {
        print "$_";
        print OUT_FILE "$_";
        $idx++;
        if($idx ne @my_flag_prepare_lib)
        {
            print ",";
            print OUT_FILE ",";
        }
        else
        {
            print "\n";
            print OUT_FILE "\n";
        }
    }
    $idx = 0;
    print "    CONFIG_MAK_FILE_PARAM_PRODUCT = ";
    print OUT_FILE "CONFIG_MAK_FILE_PARAM_PRODUCT = ";
    foreach(@my_product_list)
    {
        print "$_";
        print OUT_FILE "$_";
        $idx++;
        if($idx ne @my_product_list)
        {
            print ",";
            print OUT_FILE ",";
        }
        else
        {
            print "\n";
            print OUT_FILE "\n";
        }
    }    
}

##########################################
# gen setting file for daily build       #
##########################################
sub gen_file_for_daily_build()
{
    &gen_file_for_build_server(\@db_product_list, \@db_flag_target, \@db_flag_simulator, \@db_flag_prepare_lib);
}

##########################################
# gen setting file for daily build mcd   #
##########################################
sub gen_file_for_daily_build_mcd()
{
    &gen_file_for_build_server(\@db_mcd_product_list, \@db_mcd_flag_target, \@db_mcd_flag_simulator, \@db_mcd_flag_prepare_lib);    
}

##########################################
# gen setting file for hourly build      #
##########################################
sub gen_file_for_hourly_build()
{
    &gen_file_for_build_server(\@hb_product_list, \@hb_flag_target, \@hb_flag_simulator, \@hb_flag_prepare_lib);
}

##########################################
# gen output file for cmn-lib-simu       #
##########################################
sub gen_file_for_cmn_lib_simu()
{
    my $idx = 0;
    
    foreach(@cl_product_list)
    {
        if($cl_flag_simulator[$idx] eq $true_str)
        {
            print "    $_\n";
            print OUT_FILE "$_\n";
        }
        $idx++;
    }    
}

##########################################
# output file                            #
##########################################
sub output_setting_file()
{
    my $my_type = shift;

    print "output_file:\n";
    print "  type: $my_type\n";
    print "  file: $output_file\n";
    print "  content:\n";
    
    if(-e $output_file)
    {
        system("rm -f $output_file");
    }
    
    open(OUT_FILE, ">$output_file") or die "Error: Cannot open file $output_file\n";
    
    if($my_type eq "DailyBuild")
    {
        &gen_file_for_daily_build();
    }
    elsif($my_type eq "DailyBuild_MCD")
    {
        &gen_file_for_daily_build_mcd();      
    }
    elsif($my_type eq "HourlyBuild")
    {
        &gen_file_for_hourly_build();
    }
    elsif($my_type eq "RelPkg_Full")
    {
    
    }
    elsif($my_type eq "RelPkg_Chip")
    {
       
    }
    elsif($my_type eq "RelPkg_Keep")
    {
      
    }
    elsif($my_type eq "RelPkg_VT")
    {
        
    }    
    elsif($my_type eq "CmnLib_Target")
    {
     
    }
    elsif($my_type eq "CmnLib_Simu")
    {
        &gen_file_for_cmn_lib_simu();
    }
    else
    {
        print "\nERROR: \"$my_type\" is not supported[1]\n";
        close(OUT_FILE);
        exit 1;        
    }
    
    close(OUT_FILE);
    
    return 0;

}

##########################################
#  main                                  #
##########################################
print "\n";

if( -e ! "$input_file")
{
    print "ERROR: can not find \"$input_file\"\n";
    exit 1;
}
open(FILE, "<$input_file") or die "Error: Cannot open file \"$input_file\"\n";
@setting_file_content = <FILE>;
close(FILE);

print"file content:\n";
# parse file content
foreach(@setting_file_content)
{
    my $product;
    my $flag_target;
    my $flag_simulator;
    my $flag_prepare_lib;
    
	chomp;
	s/\012$//;
	s/\015$//;
    $line_data = $_;
    $line_counter += 1;

    if($line_data =~ /\[(.*)\]/) 
    {
        # detecte section
        # [Hourly build]
        print "[$1]\n";
        $section_name = $1;
        $section = 1;
        next;
    }
    elsif($line_data =~ /^\s*$/) 
    {
        # new line
        $section_name = "";
        $section = 0;
        $product = "";
        next;
    }
    elsif($line_data =~ /(.*) *= *(.*)/) 
    {
        # product setting
        # 8536n_1g_256_mb303gm_3D = Target, simulator

        my @value_list;
        my $tmp_str = $2;
        
        $product = $1;
        $product =~ s/^\s+//; # remove whitespace from the begin of the string
        $product =~ s/\s+$//; # remove whitespace from the end of the string
        print "  $product\n";
        
        # empty check
        if($tmp_str eq "")
        {
            print "\nERROR: something wrong at line $line_counter\[2]\n";
            exit 1;
        }
        
        # check the value is correct
        $tmp_str =~ s/,/ /g;
        @value_list = split(' ', $tmp_str);
        foreach(@value_list)
        {
            if(($section_name eq "Daily build")
                || ($section_name eq "Daily build MCD"))
            {
                if(!(/Target/i || /Simulator/i || /PrepareLib/i))
                {
                    print "\nERROR: $_ is a undefined value.[line:$line_counter]\n";
                    exit 1;                    
                }
            }
            elsif(!(/Target/i || /Simulator/i))
            {
                print "\nERROR: $_ is a undefined value.[line:$line_counter]\n";
                exit 1;
            }
        }
        
        $flag_target = $false_str;
        $flag_simulator = $false_str;
        $flag_prepare_lib = $false_str;
        
        if($tmp_str =~ /Target/i)
        {
            $flag_target = $true_str;
        }
        
        if($tmp_str =~ /Simulator/i)
        {
            $flag_simulator = $true_str;
        }

        if($tmp_str =~ /PrepareLib/i)
        {
            $flag_prepare_lib = $true_str;
        }
        
        &add_array_data($section_name, $product, $flag_target, $flag_simulator, $flag_prepare_lib);
    }
    else
    {
        if($line_data =~ /Please check with PQA/)
        {
            next;
        }
        
        print "\nERROR: something wrong at line $line_counter\[1]\n";
        exit;
    }
}

print "\n";

#output file
&output_setting_file($exe_type);


