#!/usr/bin/perl

use warnings;
use strict;
use Cwd;

#
#$ perl tng/abi/check_files.pl [check_sub_folder|check_header_c|check_pub_header]
#$ perl tng/abi/check_files.pl check_sub_folder > 1.txt
#$ perl tng/abi/check_files.pl check_header_c > 2.txt
#$ perl tng/abi/check_files.pl check_pub_header > 3.txt

## Variable
my $type = shift;
my $xml = "";
if (($#ARGV+1) == 2)
{
    $xml = shift;
}
my $pwd = getcwd;
my $proc_dir = "";
my @abi_headers_list_defined;
my @abi_headers_list_search;
my @abi_headers_list_xml;


sub file_path()
{
    my @list = @{$_[0]};
    my $path = $_[1];
    my $find = 0;
    
    foreach(@list)
    {
        if($path =~ $_)
        {
            $find = 1;
        }
    }
    
    return $find;
}

sub chak_header()
{
    my $src = shift;
    my $pub = shift;
    my $curr_dir = getcwd;
    my $find = 0;
    my $abi_herders_c_file;
    my $abi_herders_c_file2 = "";
    my $if_section = 0;
    my $comment_section = 0;
    
    chdir $src;
    my @dir = <*>;
    for my $path (@dir)
	{
        if($path =~ /abi_headers_/)
        {
            $find = 1;

            $abi_herders_c_file = $path;
            push @abi_headers_list_defined, $abi_herders_c_file;
            if($abi_herders_c_file eq "abi_headers_rai.c")
            {
                $abi_herders_c_file2 = "abi_headers_fms.c";
                #push @abi_headers_list_defined, $abi_herders_c_file2;
            }
        }
	}
	
	if($find eq 0)
	{
	    if($type eq "check_header_c")
	    {
            my @pub_white_list
            =(
                "proj/sc/application/sys/cn/src"
                ,"proj/sc/application/sys/hopper/src"
                ,"proj/sc/application/sys/file_mgr/src"
                ,"proj/sc/system/r2/src"
                ,"proj/sc/application/sys/fat/src"               
            );

            if(0 eq &file_path(\@pub_white_list, $src))
            {
                print "ERROR2: cant find abi_headers_xxx.c in $src\n";
            }	        
	    }
	}
	else
	{
    	chdir $pub;
    	my $lineData;
    	my @pub_list = <*>;
    	$if_section = 0;
    	$comment_section = 0;
    	for my $file (@pub_list)
    	{
    	    if($file eq "dummy")
    	    {
    	        next;
    	    }
    	    $find = 0;
            open(C_FILE, "<$src/$abi_herders_c_file") or die "ERROR: Cannot open file $abi_herders_c_file\n";
            while ($lineData = <C_FILE>)
            {                              
                if($lineData =~ /(.*?)\/\//)
                {
                    if($1 eq "")
                    {
                        next;
                    }
                    else
                    {
                        $lineData = $1;
                    }
                }
                if($lineData =~ /\/\//)
                {
                    #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                }
                elsif($lineData =~ /\/\*(.*?)\*\//)
                {
                    #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                }
                elsif($lineData =~ /\/\*/)
                {
                    #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                    $comment_section = 1;
                }
                elsif($lineData =~ /\*\//)
                {
                    #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                    $comment_section = 0;
                }                             
                elsif($lineData =~ /#if/)
                {
                    #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                    $if_section = 1;

                    if($lineData =~ /#if *1/)
                    {
                        $if_section  = 0;
                    }
                 
                    if($lineData =~ /#ifdef *__X86LINUXGCC__ *$/)
                    {
                        $if_section  = 0;
                    }
                }
                elsif($lineData =~ /#endif/)
                {
                    #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                    $if_section = 0;
                }
                elsif($if_section eq 1)
                {
                    #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                }
                elsif($comment_section eq 1)
                {
                    #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                }
                elsif($lineData =~ /$file/i)
                {
                    $find = 1;
                    last;
                }            
            }
            close(C_FILE);
        	$if_section = 0;
        	$comment_section = 0;
            if($find eq 0)
            {
        	    if($abi_herders_c_file2 ne "")
        	    {
                    open(C_FILE, "<$src/$abi_herders_c_file2") or die "ERROR: Cannot open file $abi_herders_c_file2\n";
                    while ($lineData = <C_FILE>)
                    {
                        if($lineData =~ /#if/)
                        {
                            #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                            $if_section = 1;
                        }
                        elsif($lineData =~ /#endif/)
                        {
                            #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                            $if_section = 0;
                        }
                        elsif($lineData =~ /\/\//)
                        {
                            #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                        }
                        elsif($lineData =~ /\/\*(.*?)\*\//)
                        {
                            #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                        }
                        elsif($lineData =~ /\/\*/)
                        {
                            #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                            $comment_section = 1;
                        }
                        elsif($lineData =~ /\*\//)
                        {
                            #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                            $comment_section = 0;
                        }
                        elsif($if_section eq 1)
                        {
                            #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                        }
                        elsif($comment_section eq 1)
                        {
                            #print "WARNING: $src/$abi_herders_c_file: $lineData\n";
                        }
                        elsif($lineData =~ /$file/i)
                        {
                            $find = 1;
                            last;
                        }            
                    }
                    close(C_FILE);        	        
        	    }                
            }
            
        	if($find eq 0)
        	{
        	    my $len = length("$src/$abi_herders_c_file");
        	    my $tmm = "";
        	    my $i;
        	    
        	    for($i=$len; $i < 110; $i++)
        	    {
        	        $tmm .= " ";
        	    }
        	    if($type eq "check_pub_header")
        	    {
                    my @headers_white_list
                    =(
                        "mmi_mae_unittest_data.h"   
                        ,"mmi_platform_version_info.h"                       
                        ,"mmi_atsyncsrv_todolist.h"
                        ,"mmi_drmagentsrv_util.h"
                        ,"mmi_evtcentersrv_accessory.h"
                        ,"mmi_evtcentersrv_alarm.h"
                        ,"mmi_evtcentersrv_battery.h"
                        ,"mmi_evtcentersrv_bt.h"
                        ,"mmi_evtcentersrv_calllog.h"
                        ,"mmi_evtcentersrv_dialog.h"
                        ,"mmi_evtcentersrv_logmsg.h"
                        ,"mmi_evtcentersrv_media.h"
                        ,"mmi_evtcentersrv_mics.h"
                        ,"mmi_evtcentersrv_model.h"
                        ,"mmi_evtcentersrv_sms_mms.h"
                        ,"mmi_evtcentersrv_timer.h"
                        ,"mmi_common_inttbl.h"
                        ,"mmi_layout.h"
                        ,"mmi_layout_gen.h"
                        ,"mmi_layout_gen_L.h"
                        ,"mmi_layout_gen_undef.h"
                        ,"mmi_layout_hvga_320_480.h"
                        ,"mmi_layout_hvga_320_480_undef.h"
                        ,"mmi_layout_landscape_hvga.h"
                        ,"mmi_layout_landscape_hvga_undef.h"
                        ,"mmi_layout_landscape_qcif.h"
                        ,"mmi_layout_landscape_qcif_undef.h"
                        ,"mmi_layout_landscape_qqvga.h"
                        ,"mmi_layout_landscape_qqvga_undef.h"
                        ,"mmi_layout_landscape_qvga.h"
                        ,"mmi_layout_landscape_qvga_undef.h"
                        ,"mmi_layout_landscape_wqvga_240_400.h"
                        ,"mmi_layout_landscape_wqvga_240_400_undef.h"
                        ,"mmi_layout_qcif_plus.h"
                        ,"mmi_layout_qcif_plus_undef.h"
                        ,"mmi_layout_qqvga.h"
                        ,"mmi_layout_qqvga_undef.h"
                        ,"mmi_layout_qvga.h"
                        ,"mmi_layout_qvga_undef.h"
                        ,"mmi_layout_undef.h"
                        ,"mmi_layout_wqvga_240_400.h"
                        ,"mmi_layout_wqvga_240_400_undef.h"
                        ,"mmi_macro_ap_undef.h"
                        ,"mmi_macro_prop_empty.h"
                        ,"mmi_macro_prop_val.h"
                        ,"mmi_rs_macro_struct.h"
                        ,"mmi_rs_macro_val.h"
                        ,"rs_gen_struct.h"
                        ,"widget_layout_gen.h"
                        ,"widget_layout_hvga_320_480.h"
                        ,"sys_sys_ftr.h"
                        ,"rs_layout.h"
                        ,"rs_layout_id.h"
                        ,"rs_layout_id_customer.h"
                        ,"rs_layout_id_define.h"
                        ,"Common_textlabel.h"
                    );
                    
                    if(0 eq &file_path(\@headers_white_list, $file))
                    {
                        if($file =~ /\.c$/)
                        {
                            
                        }
                        else
                        {
                            if((($abi_herders_c_file eq "abi_headers_mae.c")&&($file eq "fonts"))
                                ||(($abi_herders_c_file eq "abi_headers_mae.c")&&($file eq "models"))
                                )
                            {
                            }
                            else
                            {
                                print "ERROR3: not checked: $src/$abi_herders_c_file$tmm-> $file\n";
                            }
                        }
                    }
        	    }
        	}        
    	}
        chdir $curr_dir;
	}
	chdir $curr_dir;
}

sub search_folder()
{
    my $level = shift;
	my $search_pattern = "pub";
    my $curr_dir;
    my $find_pub = 0;
    my $leaf = 1;

	my @dir = <*>;
	for my $path (@dir)
	{	    
		if (-d $path)
		{
		    if($proc_dir eq "./sc/middleware")
		    {
                if($path eq "stereo")
                {
                    next;
                }
		    }
		    $leaf = 0;
		    #print "proc_dir = $proc_dir\n";		    
		    #print "$path\n";
		    if(($path =~ /$search_pattern/i)
		        || ($proc_dir eq "./sc/application/mmi/common") && ($path eq "inc")
		        || ($proc_dir eq "./sc/application/mmi/common") && ($path eq "cfg")
		        || ($proc_dir eq "./sc/application/3rd/mserv") && ($path eq "inc")
		        || ($proc_dir eq "./sc/application/3rd/java/common") && ($path eq "inc")
		        || ($proc_dir eq "./sc/application/mmi/AppLauncher") && ($path eq "inc")
		        )
            {
		        my $src;
		        my $pub;
		        
		        $find_pub = 1;
                $curr_dir = getcwd;
                $pub = "$curr_dir/$path";
                $src = $curr_dir."/src";
		        #print "$pub\n";

                if($pub =~ /proj\/sc\/middleware\/avp\/pub/)
		        {
		            $src = $curr_dir."/mmplayer/src";
		            &chak_header($src, $pub);
                }
		        elsif($pub =~ /proj\/sc\/middleware\/mmaudio\/pub/)
		        {
		            $src = $curr_dir."/audiocontrol/src";
		            &chak_header($src, $pub);
                }
		        elsif($pub =~ /proj\/sc\/application\/sys\/ResMgr\/pub/)
		        {
		            $src = $curr_dir."/src/ResMgr";
		            &chak_header($src, $pub);
                }
		        elsif($pub =~ /proj\/sc\/driver\/drv\/atv\/pub/)
		        {
		            $src = $curr_dir."/mstar/src";
		            &chak_header($src, $pub);
                }
		        elsif($pub =~ /proj\/sc\/driver\/drv\/gps\/pub/)
		        {
		            $src = $curr_dir."/Platform/RTK/src";
		            &chak_header($src, $pub);
                }
		        elsif($pub =~ /proj\/sc\/application\/mmi\/mgl\/pub/)
		        {
		            $src = $curr_dir."/mCore/src";
		            &chak_header($src, $pub);
                }
		        elsif($pub =~ /proj\/sc\/application\/mmi\/srv\/pub/)
		        {
		            $src = $curr_dir."/SrvCommon/src";
		            &chak_header($src, $pub);
                }
		        elsif($pub =~ /proj\/sc\/application\/mmi\/pgl\/pub/)
		        {
		            $src = $curr_dir."/pUtility/src";
		            &chak_header($src, $pub);
                }                
                elsif(-e $src)
                {
                    &chak_header($src, $pub);
                }               
                else
                {
                    if($type eq "check_sub_folder")
                    {
                        my @no_src_white_list
                        =(
                            "proj/sc/application/mmi/core"
                        );
            
                        if(0 eq &file_path(\@no_src_white_list, $src))
                        {
                            print "ERROR1: $pub  -> can not find Src dir.\n";
                        }
		            }
		        }
		    }
		    else
		    {
		        # can not find pub folder
		        
		        my $new_dir;

		        $curr_dir = getcwd;
		        $new_dir = $curr_dir."/$path";
		        
		        if(($new_dir =~ /proj\/sc\/application\/mmi\/app$/)
		            || ($new_dir =~ /proj\/sc\/application\/mmi\/AppLauncher$/)
		            || ($new_dir =~ /proj\/sc\/application\/mmi\/common$/)
		            || ($new_dir =~ /proj\/sc\/application\/mmi\/cus$/)
		            || ($new_dir =~ /proj\/sc\/application\/mmi\/emmi_studio$/)
		            || ($new_dir =~ /proj\/sc\/application\/mmi\/enum$/)
		            || ($new_dir =~ /proj\/sc\/application\/mmi\/resource$/)
		            || ($new_dir =~ /proj\/sc\/application\/sys\/simbt$/)
		            )
		        {
		        }
		        else
		        {
                    chdir $path;
        			&search_folder($level+1);
        			chdir "../";
        		}
    		}
		}
	}
	
	if(($find_pub eq 0) && ($leaf eq 0) && ($level eq 2))
	{
        $curr_dir = getcwd;
	    
	    if(($curr_dir =~ /inc$/)
	        || ($curr_dir =~ /itf$/)
	        || ($curr_dir =~ /rec$/)
	        )
	    {
	    }
        else
        {
            if($type eq "check_sub_folder")
            {
                my @pub_white_list
                =(
                    "proj/sc/telserv/3g_atp"
                    ,"proj/sc/telserv/3g_cm"
                    ,"proj/sc/telserv/3g_conn"
                    ,"proj/sc/telserv/3g_ip"
                    ,"proj/sc/telserv/3g_mdlut"
                    ,"proj/sc/telserv/3g_mux"
                    ,"proj/sc/telserv/3g_ngip"
                    ,"proj/sc/telserv/3g_ngos"
                    ,"proj/sc/telserv/3g_ppp"
                    ,"proj/sc/telserv/3g_ril"
                    ,"proj/sc/telserv/3g_vml"
                    ,"proj/sc/telserv/ati"
                    ,"proj/sc/telserv/vml"
                    ,"proj/sc/driver/drv/dsp_isw"
                    ,"proj/sc/driver/drv/g3d"
                    ,"proj/sc/system/BootUp"
                    ,"proj/sc/system/CheckSize"
                    ,"proj/sc/system/dlm"
                    ,"proj/sc/system/libc"
                    ,"proj/sc/system/opec"
                    ,"proj/sc/application/sys/utility"
                    ,"proj/sc/application/sys/truetype"
                    ,"proj/sc/application/mmi/common"
                    ,"proj/sc/application/mmi/mae/extras"
                    ,"proj/sc/application/mmi/mae/porting"
                    ,"proj/sc/application/mmi/mae/src"
                    ,"proj/sc/application/cus_app"
                    ,"proj/sc/telserv/sig"
                    ,"proj/sc/telserv/sril"
                );
                $curr_dir = getcwd;
                
                if(0 eq &file_path(\@pub_white_list, $curr_dir))
                {
                    print "ERROR0: $curr_dir  -> can not find Pub dir.\n";
                }
            }
        }
	}
}

sub find_all_files()
{
	my $search_pattern = shift;
    my $curr_dir = getcwd;
    my $new_dir;

	my @dir = <*>;
	for my $path (@dir)
	{	    
		if (-d $path)
		{
            $new_dir = $curr_dir."/$path";
	        if(($new_dir =~ /proj\/sc\/customer\/default\/src\/mmi$/)
	            || ($new_dir =~ /proj\/sc\/customer\/default\/src\/mmi$/)		            
	            )
	        {
	        }
	        else            
	        {
                #print "check: $new_dir\n";
                chdir $path;                
                &find_all_files($search_pattern);
                chdir "../";
            }
		}
		else
		{
		    if($path =~ /$search_pattern/)
		    {
		        #print "file: $path \n";
		        push @abi_headers_list_search, $path;
		    }
		}
	}
}

##########################
## main
##########################
my @folder=(
         #"./sc/driver/drv"
        #,"./sc/customer/default/src/drv"
        #,"./sc/middleware"
        #,"./sc/middleware/stereo"
        "./sc/system"
        ,"./sc/system/dlm/dlm_entry"
        ,"./sc/telserv"
        ,"./sc/application/3rd/mserv"
        ,"./sc/application/3rd/sdk"
        ,"./sc/application/3rd/java/common"
        ,"./sc/application/email"
        ,"./sc/application/mmi"
        ,"./sc/application/mmi/mae"
        ,"./sc/application/mmi/models"
        ,"./sc/application/mmi/AppLauncher"
        ,"./sc/application/mmi/core"
        ,"./sc/application/mmi/mgl"
        ,"./sc/application/mmi/common"
        ,"./sc/application/mmi/srv"
        ,"./sc/application/mms"
        ,"./sc/application/sys"
        ,"./sc/application/wap"
        ,"./sc/application/cus_app"
        );

=cut        
@folder=(
        "./sc/application/mmi/mae"
        );
=cut

foreach(@folder)
{
    my $level;
    
    $level = 1;
    if(($_ eq "./sc/application/mmi/mgl")
     || ($_ eq "./sc/application/mmi/srv")
     || ($_ eq "./sc/application/mmi/core")
     || ($_ eq "./sc/application/mmi/common")     
     || ($_ eq "./sc/application/cus_app")     
     )
    {
        $level = 2;
    }
    $proc_dir = $_;
    print "check: $proc_dir\n";
    chdir $proc_dir;
    &search_folder($level);
    chdir "$pwd";
    print "\n";
}

if(($type eq "check_header_c") && ($xml ne ""))
{   
    # get abi_headers_xxx.c by searching folder  
    $proc_dir = "./sc";
    chdir $proc_dir;
    &find_all_files("abi_headers_");
    chdir "$pwd";
 
    my $lineData;
    my $flag = 0;
   
    # get abi_headers_xxx.c from xml
    open(XML_FILE, "<D:/EMMI/EMMI/mainline/proj/build/8532_64_32_mb406g/out/abilib_mobile.xml") or die "ERROR: Cannot open file abilib_mobile.xml\n";
    while ($lineData = <XML_FILE>)
    {
        if($lineData =~ /<headers>$/)
        {
            $flag = 1;
            next;
        }
        if($lineData =~ /<\/headers>$/)
        {
            $flag = 0;
            last;
        }
        if($flag eq 1)
        {
            #./build/8536n_1g_256_mb303gmv3/out/abi_headers_AppLauncher.c.h
            if($lineData =~ /out\/(.*?)\.h$/)
            {
                push @abi_headers_list_xml, $1;
            }
            else
            {
                if($lineData =~ /The list of paths to header files/)
                {
                    next;
                }
                if($lineData =~ /directories with header files/)
                {
                    next;
                }
                print "ERROR: unhandled case!!\n$lineData\n";
                exit 1;
            }             
        }        
    }
    close(XML_FILE);
    
    # list results
    my @sorted = ();
    print "defined: \n";
    @sorted = sort {lc $a cmp lc $b} @abi_headers_list_defined;
    @abi_headers_list_defined = @sorted;
    foreach(@sorted)
    {
        print "$_\n";
    }
    print "search: \n";
    @sorted = sort {lc $a cmp lc $b} @abi_headers_list_search;
    @abi_headers_list_search = @sorted;
    foreach(@sorted)
    {
        print "$_\n";
    }
    print "xml: \n";  
    @sorted = sort {lc $a cmp lc $b} @abi_headers_list_xml;
    @abi_headers_list_xml = @sorted;
    foreach(@sorted)
    {
        print "$_\n";
    }
    
    # check @abi_headers_list_defined -> @abi_headers_list_search
    foreach(@abi_headers_list_search)
    {
        my $not_defined = 1;
        my $header_file = $_;
        
        if($header_file eq "abi_headers_dsp_isw.c")
        {
            next;
        }
        foreach(@abi_headers_list_defined)
        {
            if($header_file eq $_)
            {
                $not_defined = 0;
                last;
            }
        }
        if($not_defined eq 1)
        {
            print "ERROR: $header_file is unchecked\n";
        }       
    }
}

print "\nDone!\n";
