#!/usr/bin/perl

use lib '.';
use Cwd;

#$ perl tng/abi/gen_report.pl ./tng/abi/abi_compat_report.html ./tng/abi/abilib_mobile.xml ./tng/abi/abi_compat_report2.html abi_compat_report.xls

my $html = shift;
my $abilib_mobile_xml = shift;
my $report = shift;
my $excel_file = shift;

my %category_list = ();
my $category_neum = 0;

my $folder_list_XML = "./tng/quota_check/folder_list.xml";

my @excel_header_list1 = ();
my @excel_header_info1 = ();
my @excel_cate_info1 = ();
my @excel_owner_info1 = ();
my @excel_contact1= ();
my $excel_num1 = 0;

my @excel_header_list2 = ();
my @excel_header_info2 = ();
my @excel_cate_info2 = ();
my @excel_owner_info2 = ();
my @excel_contact2 = ();
my $excel_num2 = 0;

my $change_info;

##########################
## 
##########################
sub get_all_category()
{
    my $line;
    my $new_cate;
    
    print "Category:\n";
    open(XML_FILE, "<$folder_list_XML") or die "ERROR: Cannot open file folder_list.xml\n";
    $category_neum += 1;
    $category_list{$new_cate} = "undefined";     
    while ($line = <XML_FILE>)
    {
        if($line =~ /<Folder Name=(.*) Category=\"(.*)\" *Owner=/)
        {
            $new_cate = $2;
            if($new_cate eq "")
            {
                next;
            }
            if($category_list{$new_cate})
            {
            }
            else
            {
                print "  $new_cate\n";
                $category_neum += 1;
                $category_list{$new_cate} = $new_cate; 
            }
        }
    }
    close(XML_FILE);
    print "category_neum = $category_neum\n";
}

##########################
## search entire workspace
##########################
sub find_file()
{
	my $search_pattern = shift;
    my $curr_dir = getcwd;
    my $new_dir;

	my @dir = <*>;
	for my $path (@dir)
	{	    
		if (-d $path)
		{
		    my $ret;
		    
            chdir $path;
            $ret = &find_file($search_pattern);
            chdir "../";
            if($ret ne "")
            {
                return $ret;
            }
		}
		else
		{
		    if($path =~ /$search_pattern/)
		    {
		        print "file: $curr_dir/$path \n";
		        return "$curr_dir/$path";
		    }
		}
	}
	
	return "";
}

sub file_file_in_pub()
{
    my $header_file = shift;
    my @pub_folder_list = ();
    my $line;
    my $section = 0;
    my $curr_dir = getcwd;
    my $ret = "";
        
    open(XML_FILE, "<$abilib_mobile_xml") or die "ERROR: Cannot open file $abilib_mobile_xml\n";
    while ($line = <XML_FILE>)
    {
        if($line =~ /will not automatically detect include paths -->$/)
        {
            $section = 1;
            next;
        }
        if($line =~ /<\/include_paths>$/)
        {
            $section = 0;
            last;
        }
        if($section eq 1)
        {
            chomp($line);
            push @pub_folder_list, $line;
        }
    }
    close(XML_FILE);
    
    foreach(@pub_folder_list)
    {
        my $path = $_;
        my @dir;
        
        chdir $path;
        @dir = <*>;
    	for my $file (@dir)
    	{	    
    		if (-d $file)
    		{
                next;
    		}
    		else
    		{
    		    if($file =~ /$header_file/)
    		    {
    		        if($path =~ /\/$/)
    		        {
    		            $path = substr("$path", 0, -1);
    		        }
    		        #print "file: $path/$file \n";
    		        $ret = "$path/$file";
    		        last;
    		    }
    		}
    	}        
        chdir $curr_dir;
    }
    
    return $ret;
}

##########################
## 
##########################
sub gen_report()
{
    my $abi_compat_report = shift;
    my $output_report = shift;
    my $line;
    my $section_flag = 0;
    my @header_list = ();
    my @header_info = ();
    my @cate_info = ();
    my @owner_info = ();
    my @contact = ();
    my $num = 0;
    my $tmp;
    my $ignored;
    my $problems_in_data_types_section = 0;
    my $interface_problems_section = 0;
    
    print "abi_compat_report: $abi_compat_report\n";
    print "output: $output_report\n\n";
    
    if(-e "$output_report")
    {        
        system("rm -r -f $output_report");
    }
    open (OUTFILE,">$output_report") || die("Cannot open file $output_report");
    
    $change_info = "";
    open(ABI_FILE, "<$abi_compat_report") or die "ERROR: Cannot open file abi_compat_report.xml\n";
    while ($line = <ABI_FILE>)
    {
        if($line =~ /ABI compliance report for the library mobile from version (.*) on x86/)
        {
            $change_info = $1;
        }
        if(($line =~ /<!--Checked_Headers-->/)
            ||($line =~ /<!--Checked_Libs-->/))
        {
            $ignored = 1;
            next;
        }
        if(($line =~ /<!--Checked_Headers_End-->/)
            ||($line =~ /<!--Checked_Libs_End-->/))        
        {
            $ignored = 0;
            next;
        }
        if($ignored eq 1)
        {
            next;
        }
        if(($line =~/<!--Type_Problems_High-->/)
            || ($line =~ /<!--Type_Problems_Medium-->/)
            || ($line =~ /<!--Type_Problems_Low-->/)
            || ($line =~ /<!--Interface_Problems_High-->/)
            || ($line =~ /<!--Interface_Problems_Medium-->/)
            || ($line =~ /<!--Interface_Problems_Low-->/)
            || ($line =~ /<!--Withdrawn_Interfaces-->/)
            || ($line =~ /<!--Added_Interfaces-->/)
            || ($line =~ /<!--Changed_Constants-->/))
        {
            $problems_in_data_types_section = 0;
            $interface_problems_section = 0;
            
            if(($line =~/<!--Type_Problems_High-->/)
                || ($line =~ /<!--Type_Problems_Medium-->/)
                || ($line =~ /<!--Type_Problems_Low-->/))
            {
                $problems_in_data_types_section = 1;
            }
            if(($line =~ /<!--Interface_Problems_High-->/)
                || ($line =~ /<!--Interface_Problems_Medium-->/)
                || ($line =~ /<!--Interface_Problems_Low-->/))
            {
                $interface_problems_section = 1;
            }
            
            $section_flag = 1;
            @header_list = ();
            @header_info = ();
            @cate_info = ();
            @owner_info = ();
            @contact = ();
            $num = 0;
            print OUTFILE $line;
            next;
        }
        if(($line =~ /<!--Type_Problems_High_End-->/)
            || ($line =~ /<!--Type_Problems_Medium_End-->/)
            || ($line =~ /<!--Type_Problems_Low_End-->/)
            || ($line =~ /<!--Interface_Problems_High_End-->/)
            || ($line =~ /<!--Interface_Problems_Medium_End-->/)
            || ($line =~ /<!--Interface_Problems_Low_End-->/)
            || ($line =~ /<!--Withdrawn_Interfaces_End-->/)
            || ($line =~ /<!--Added_Interfaces_End-->/)
            || ($line =~ /<!--Changed_Constants_End-->/))
        {
            my $key;
            my $idx;
            my $first = 1;
            my $table_tag = 0;
            my $highlight_str;
            
            $section_flag = 0;
            foreach $key (keys %category_list)
            {
                $idx = 0;
                $first = 1;
                foreach(@cate_info)
                {
                    $highlight_str = "";
                    if($_ eq "$category_list{$key}")
                    {
                        if($_ eq "undefined")
                        {
                            $highlight_str = "background:yellow; mso-highlight:yellow";
                        }
                        if($first eq 1)
                        {
                            if($table_tag eq 0)
                            {
                                print OUTFILE "<table class=MsoTableMediumGrid1Accent1 border=1 cellspacing=0 cellpadding=0 width=\"100%\" style='width:100.0%;border-collapse:collapse;border:none; mso-border-alt:solid #7BA0CD 1.0pt;mso-border-themecolor:accent1;mso-border-themetint: 191;mso-yfti-tbllook:1184;mso-padding-alt:0cm 5.4pt 0cm 5.4pt'>\n";
                                $table_tag = 1;
                            }
                            
                            print OUTFILE "<tr style='mso-yfti-irow:-1;mso-yfti-firstrow:yes'>\n";                            
                            print OUTFILE "<td width=200 valign=top><b style='mso-bidi-font-weight:normal'><span lang=EN-US style='font-family:\"Arial\",\"sans-serif\";color:red;$highlight_str'>$cate_info[$idx]:</span></b>\n";
                            print OUTFILE "<b style='mso-bidi-font-weight:normal'><span lang=EN-US style='font-family:\"Arial\",\"sans-serif\"'>$contact[$idx]</span></b></td>\n<td width=1400 valign=top>\n";
                        }
                        $tmp = $header_info[$idx];
                        $tmp =~ s/<br\/><span class='header_name'>/<span class='header_name'>/;
                        if($tmp =~ /<br\/>$/)
                        {
                        }
                        else
                        {
                            $tmp .= "<br>\n";
                        }

                        print OUTFILE $tmp;
                        $first = 0;
                        
                        #save data for generating excel
                        if($problems_in_data_types_section eq 1)
                        {
                            push @excel_header_list1, $header_list[$idx];
                            push @excel_header_info1, $header_info[$idx];
                            push @excel_cate_info1, $cate_info[$idx];
                            push @excel_owner_info1, $owner_info[$idx];
                            push @excel_contact1, $contact[$idx];
                            $excel_num1  += 1;
                        }
                        elsif($interface_problems_section eq 1)
                        {
                            push @excel_header_list2, $header_list[$idx];
                            push @excel_header_info2, $header_info[$idx];
                            push @excel_cate_info2, $cate_info[$idx];
                            push @excel_owner_info2, $owner_info[$idx];
                            push @excel_contact2, $contact[$idx];
                            $excel_num2  += 1;
                        }                       
                    }
                    $idx += 1;
                }
                if($first eq 0)
                {
                    print OUTFILE "</tr>\n</td>\n\n";
                }
            }
            if($table_tag eq 1)
            {
                print OUTFILE "</table>\n";
            }
            print OUTFILE $line;
            
            next;
        }
        
        if($section_flag eq 1)
        {
            my $header = "";
            
            # <span class='header_name'>drv_emi_sram_nor_pub.h</span>, <span class='solib_name'>lib_emi.so</span><br/>
            # <span class='header_name'>drv_vm_spi.h</span><br/>
            if($line =~ /<span class=\'header_name\'>(.*)<\/span>, /)
            {
                #print "$1\n";
                $header = $1;
            }
            elsif($line =~ /<span class=\'header_name\'>(.*)<\/span><br\/>/)
            {
                #print "$1\n";
                $header = $1;
            }
            
            if($header ne "")
            {
                my $contact_widnow = "";
                my $folder_name = "";
                my $parent_path = "";
                my $path;
                my $idx;
                
                my $my_cat = "";
                my $my_folder_owner = "";
                
                require "./tng/abi/parse_log.pl";
                
                $path = &file_file_in_pub($header);
                
                #@@ debug
                #$path = "./sc/driver/drv/bus/pub/drv_vm_spi.h";
                
                # get folder name
                # ex:./sc/driver/drv/bus/pub/drv_vm_spi.h
                if($path =~ /\/(.*)\/(.*)\.h.*$/g)
                {
                    #print "$1\n";
                    $idx = rindex($1, "/");
                    #print "$idx\n";
                    $folder_name = substr($1, $idx+1);
                    $parent_path = substr($1, 0, $idx);
                    print "$parent_path\n";
                    if($1 ne "sc/application/mmi/srv/pub")
                    {
                        $idx = rindex($parent_path, "/");
                        #print "$idx\n";
                        $folder_name = substr($parent_path, $idx+1);
                        $parent_path = substr($parent_path, 0, $idx);
                    }
                    $parent_path = "./".$parent_path;
                }
                else
                {
                    print "ERROR: can not get the folder name!\n$path\n";
                }
                
                if($path ne "")
                {
                    print "problem file: $path\n";
                }
                else
                {
                    print "problem file: $header\n";
                }
                if($parent_path ne "")
                {
                    print "parent path: $parent_path\n";
                }
                if($folder_name ne "")
                {
                    print "folder name: $folder_name\n";
                }

                &search_owner_from_folder_list_xml($folder_list_XML, $parent_path, $folder_name, $my_cat, $my_folder_owner);
                
                if($my_cat ne "")
                {
                    print "category: $my_cat\n";
                }
                if($my_folder_owner ne "")
                {
                    print "folder owner: $my_folder_owner\n";
                }
                                
                $cate_info[$num] = $my_cat;
                $owner_info[$num] = $my_folder_owner;
                
                $contact_widnow = $group{"$my_cat"};     
                if($contact_widnow eq "")
                {
                    $contact_widnow = "undefined"; #TBD
                }
                $contact[$num] = $contact_widnow;
                $tmp = "(<span lang=EN-US style='font-size:10.5pt;font-family:\"Arial\",\"sans-serif\"; color:#00B050'>Folder <span class=SpellE>woner:<span style='color:#00B0F0'>$my_folder_owner<span class='header_name'>)$header</span></span></span></span>";
                $line =~ s/$header/$tmp/;
                print "\n";
                $num += 1;

                $header_list[$num-1] = $header;
            }
            $header_info[$num-1] .= $line;
        }
        else
        {
            print OUTFILE $line;            
        }      
    }
    close(ABI_FILE);
    
    close(OUTFILE);    
}

sub write_my_id 
{
    my $worksheet = shift;

    return $worksheet->write_string(@_);
}

##########################
## generate excel file
##########################
sub gen_excel()
{
    use Spreadsheet::WriteExcel;
    
    my $workbook;
    my $worksheet;
    my $id_format;
    my $id_format_group1;
    my $id_format_group2;
    my $id_format_PL;
    my $id_format_contact;
    my $id_format_meeting;
    my $id_palette1;
    my $row_idx = 2;
    my $content;
    
    my $idx;
    my $counter;
    my $tmp_str1;
    my $tmp_str2;
    my @split_arr1;
    my @split_arr2;
    my $problem;
    my $function_name;
    my $signature_changed;
    my $height;
    my $item_neum;

    if( -e "$excel_file")
    {
        system("rm -f $excel_file");
    }
    
    $workbook   = Spreadsheet::WriteExcel->new("$excel_file");
    $worksheet  = $workbook->add_worksheet();
    $worksheet->add_write_handler(qr[^\d{7}$], \&write_my_id);

    # This format maintains the cell as text even if it is edited.
    $id_format  = $workbook->add_format(text_wrap => 1, valign => 'top');
    
    $worksheet->freeze_panes(1, 1);

    $worksheet->set_column('A:A', 55);
    $id_palette1 = $workbook->set_custom_color(40, 234, 241, 221);
    $id_format_PL  = $workbook->add_format(bg_color => $id_palette1);
    $worksheet->write('A1', "ABI change ($change_info)", $id_format_PL);
    $worksheet->write('B1', 'Team', $id_format_PL);
    $worksheet->set_column('B:B', 13);
    $worksheet->write('C1', 'Contact', $id_format_PL);
    $worksheet->set_column('C:C', 13);

    $id_palette1 = $workbook->set_custom_color(41, 242, 221, 220);
    $id_format_contact  = $workbook->add_format(bg_color => $id_palette1);
    $worksheet->write('D1', 'Owner', $id_format_contact);
    $worksheet->set_column('D:D', 13);
    $worksheet->write('E1', 'File', $id_format_contact);
    $worksheet->set_column('E:E', 35);
    $worksheet->write('F1', 'Changelist', $id_format_contact);
    $worksheet->set_column('F:F', 13);
    $worksheet->write('G1', 'Reason', $id_format_contact);
    $worksheet->set_column('G:G', 35);
    $worksheet->write('H1', 'Change before', $id_format_contact);        
    $worksheet->set_column('H:H', 45);
    $worksheet->write('I1', 'Change after', $id_format_contact);        
    $worksheet->set_column('I:I', 45);
    $worksheet->write('J1', 'Team owner comment', $id_format_contact);        
    $worksheet->set_column('J:J', 50);

    $id_palette1 = $workbook->set_custom_color(42, 197, 217, 241);
    $id_format_meeting  = $workbook->add_format(bg_color => $id_palette1);
    $worksheet->write('K1', 'ABI reviewer comment', $id_format_meeting);        
    $worksheet->set_column('K:K', 45);
    $worksheet->write('L1', 'Add to release note ?', $id_format_meeting);        
    $worksheet->set_column('L:L', 20);

    print "Problems in Data Types:\n";
    for($idx = 0; $idx < $excel_num1; $idx++)
    {
        print "Header: $excel_header_list1[$idx]\n\n\n\n$excel_header_info1[$idx]\n";
        
        $problem = "";
        if($excel_header_info1[$idx] =~ /<br\/><br\/><\/div>/)
        {
            @split_arr1 = split("<br/><br/></div>", $excel_header_info1[$idx]);
            $content = "";
            $counter = 1;            
            foreach(@split_arr1)
            {
                $tmp_str1 = $_;

                if($tmp_str1 !~ /problem_body/g)
                {
                    next;
                }
                
                $problem = "";
                $signature_changed = 0;            
                @split_arr2 = split("<table", $tmp_str1);
                $tmp_str1 = $split_arr2[0];
                if($tmp_str1 =~ /\[\+\]<\/span> (.*)<\/span>/g)
                {
                    $problem = $1;
                    $problem = "$counter) ".$problem;
                    $counter += 1;
                }
                
                $problem =~ s/&nbsp;//g;
                $problem =~ s/<span class='int_p'>//g;
                $problem =~ s/<span style='white-space:nowrap;'>//g;
                $problem =~ s/<span class='color_param'>//g;
                $problem =~ s/<\/span>//g;
            
                print "Problem: $problem\n";
                $content .= "$problem\n";
                $tmp_str1 = $split_arr2[1];
                @split_arr2 = split("</span></td></tr>", $tmp_str1);
                $item_neum = 0;
                foreach(@split_arr2)
                {
                    $tmp_str1 = $_;
                    $tmp_str1 =~ s/\r//g;
                    $tmp_str1 =~ s/\n//g;
                    if($tmp_str1 =~ /<span class='problem_body'>(.*)<span class='problem_body'>(.*)/)
                    {
                        $tmp_str1 = $1;
                        $tmp_str2 = $2;
                        $tmp_str1 =~ s/<b>//g;
                        $tmp_str1 =~ s/<\/b>//g;
                        $tmp_str1 =~ s/<\/span><\/td>//g;
                        $tmp_str1 =~ s/<td align='left' valign='top'>//g;
                        $tmp_str1 =~ s/<span style='white-space:nowrap;'>//g;                       
                        $tmp_str1 =~ s/<\/span>//g;
                        
                        print "      Incompatibility: $tmp_str1\n";
                        $content .= "        Incompatibility: $tmp_str1\n";
                        
                        $tmp_str2 =~ s/<b>//g;
                        $tmp_str2 =~ s/<\/b>//g;
                        $tmp_str2 =~ s/<\/span><\/td>//g;
                        $tmp_str2 =~ s/<td align='left' valign='top'>//g;
                        $tmp_str2 =~ s/<\/tr>//g;
                        if($tmp_str2 =~ /(.*)<span class\=\"section\" onclick\=\"javascript/)
                        {
                            $tmp_str2 = $1;
                        }
                        print "      Effect: $tmp_str2\n";
                        $content .= "        Effect: $tmp_str2\n";
                        $item_neum += 1;
                    }
                    if($item_neum > 6)
                    {
                        $content .= "        .....\n";
                        last;
                    }                    
                }
            }
        }

        if($excel_header_list1[$idx] eq "")
        {
            print "ERROR: header can not be detected!\n";
            exit 1;
        }
        
        print "Header: $excel_header_list1[$idx]\n";    
        print "Problem: $problem\n";
        print "Team: $excel_cate_info1[$idx]\n";
        print "Owner: $excel_owner_info1[$idx]\n";
        print "Contact: $excel_contact1[$idx]\n\n";
        
        $worksheet->set_row($row_idx-1,  undef, undef, 0, 1);
        $worksheet->write("A$row_idx", "$content", $id_format);
        $height = 350;
        if(2000 < length($content))
        {
            $height = 800;
        }        
        $worksheet->write_comment("A$row_idx", "$content\n<End>", width => 800, height => $height);
        $worksheet->write("B$row_idx", "$excel_cate_info1[$idx]", $id_format);
        $worksheet->write("C$row_idx", "$excel_contact1[$idx]", $id_format);        
        $worksheet->write("E$row_idx", "$excel_header_list1[$idx]\n", $id_format);        
        $row_idx += 1;
    }
    
    $id_palette1 = $workbook->set_custom_color(43, 219, 238, 243);
    $id_format_group1  = $workbook->add_format(bg_color => $id_palette1);
    $worksheet->write("A$row_idx", "Problems in Data Types", $id_format_group1);
    $worksheet->set_row($row_idx-1,  undef, undef, 0, 0);
    $row_idx += 1;    
        
    print "Interface Problems:\n";
    $tmp_str1 = "";
    $tmp_str2 = "";
    @split_arr1 = ();
    $problem = "";    
    for($idx = 0; $idx < $excel_num2; $idx++)
    {
        print "Header: $excel_header_list2[$idx]\n";
        
        $problem = "";
               
        if($excel_header_info2[$idx] =~ /<\/table><br\/><\/div>/)
        {
            @split_arr1 = split("</table><br/></div>", $excel_header_info2[$idx]);
            $content = "";
            $counter = 1;            
            foreach(@split_arr1)
            {
                $tmp_str1 = $_;

                if($tmp_str1 !~ /problem_body/g)
                {
                    next;
                }
                
                $signature_changed = 0;            
                @split_arr2 = split("<table", $tmp_str1);
                $tmp_str1 = $split_arr2[0];
                if($tmp_str1 =~ /\[\+\]<\/span> (.*)<\/span> /g)
                {
                    $problem = $1;
                    $problem = "$counter) ".$problem;
                    $counter += 1;
                }  
                
                if($tmp_str1 =~ /signature changed(.*)<\/span><\/span>/g)
                {
                    $signature_changed = 1;
                    $tmp_str2 = $1;
                    $tmp_str2 =~ s/<br\/><span class='new_signature'>//g;                    
                    $problem = $problem."\n       signature changed >>>>>>>>>>>>>>\n     ".$tmp_str2;
                }
                
                $problem =~ s/&nbsp;//g;
                $problem =~ s/<span class='int_p'>//g;
                $problem =~ s/<span style='white-space:nowrap;'>//g;
                $problem =~ s/<span class='color_param'>//g;
                $problem =~ s/<\/span>//g;
            
                print "Problem: $problem\n";
                $content .= "$problem\n";
                
                $tmp_str1 = $split_arr2[1];
                @split_arr2 = split("</span></td></tr>", $tmp_str1);                
                $item_neum = 0;
                foreach(@split_arr2)
                {
                    $tmp_str1 = $_;
                    $tmp_str1 =~ s/\r//g;
                    $tmp_str1 =~ s/\n//g;
                    if($tmp_str1 =~ /<span class='problem_body'>(.*)<span class='problem_body'>(.*)/)
                    {
                        $tmp_str1 = $1;
                        $tmp_str2 = $2;
                        $tmp_str1 =~ s/<b>//g;
                        $tmp_str1 =~ s/<\/b>//g;
                        $tmp_str1 =~ s/<\/span><\/td>//g;
                        $tmp_str1 =~ s/<td align='left' valign='top'>//g;
                        $tmp_str1 =~ s/<span style='white-space:nowrap;'>//g;                       
                        $tmp_str1 =~ s/<\/span>//g;
                        
                        print "      Incompatibility: $tmp_str1\n";
                        $content .= "        Incompatibility: $tmp_str1\n";
                        
                        $tmp_str2 =~ s/<b>//g;
                        $tmp_str2 =~ s/<\/b>//g;
                        $tmp_str2 =~ s/<\/span><\/td>//g;
                        $tmp_str2 =~ s/<td align='left' valign='top'>//g;
                        $tmp_str2 =~ s/<\/tr>//g;
                        if($tmp_str2 =~ /(.*)<span class\=\"section\" onclick\=\"javascript/)
                        {
                            $tmp_str2 = $1;
                        }
                        print "      Effect: $tmp_str2\n";
                        $content .= "        Effect: $tmp_str2\n";
                        $item_neum += 1;
                    }
                    if($item_neum > 6)
                    {
                        $content .= "        .....\n";
                        last;
                    }                    
                }
            }
        }
        if($excel_header_list2[$idx] eq "")
        {
            print "ERROR2: header can not be detected!\n";
            exit 1;
        }
                
        print "Team: $excel_cate_info2[$idx]\n";
        print "Owner: $excel_owner_info2[$idx]\n";
        print "Contact: $excel_contact2[$idx]\n\n";
        $worksheet->set_row($row_idx-1,  undef, undef, 0, 1);
        $worksheet->write("A$row_idx", "$content", $id_format);
        $height = 350;
        if(2000 < length($content))
        {
            $height = 800;
        }
        $worksheet->write_comment("A$row_idx", "$content\n<End>", width => 800, height => $height);        
        $worksheet->write("B$row_idx", "$excel_cate_info2[$idx]", $id_format);
        $worksheet->write("C$row_idx", "$excel_contact2[$idx]", $id_format);        
        $worksheet->write("E$row_idx", "$excel_header_list2[$idx]\n", $id_format);        
        $row_idx += 1;        
    }
    $id_palette1 = $workbook->set_custom_color(44, 229, 224, 236);
    $id_format_group2  = $workbook->add_format(bg_color => $id_palette1);    
    $worksheet->write("A$row_idx", "Interface Problems", $id_format_group2);
    $worksheet->set_row($row_idx-1,  undef, undef, 0, 0);
    $row_idx += 1;    
    
    $worksheet->set_column('A:A', undef, $id_format);
}

##########################
## 
##########################
&get_all_category();
&gen_report($html, $report);
&gen_excel();
