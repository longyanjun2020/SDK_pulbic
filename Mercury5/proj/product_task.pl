#!/usr/bin/perl

use warnings;
use strict;
use File::Basename;
use File::Copy;
use File::Compare;
use File::Path;

####################################################################
# Global Variable
####################################################################
use constant PRODUCT_DIR  => 'sc/customer/product/';
use constant MAGIC_STR  => 'abcd';

# List all Product
my @prd;  # product list.
my $match_number = 25;
my @prefix = (
				"audioparam",    						#0
				"cusSetting ",							#1
				"mmi_emapp_custom",					    #2
				"calibration_table",		        #3
				"battery",								#4
				"gpio",									#5
				"pm",									#6
				"keypad",								#7
				"kpdlight",								#8
				"pwm",									#9
				"touchscreen",							#10
				"service",								#11
				"gpd",									#12
				"DUMMY_PATH",							#13 : DISPTBL_DEFAULT 原本要移除, 改為保留
				"lcd_logo",								#14
				"LCD_BASE",								#15
				"nandprt",								#16
				"fat",									#17
				"sys_config",							#18
				"fms_config",							#19
				"e2p",									#20
				"DUMMY_PATH",							#21 : LCD_SRC_LIST 原本要移除, 改為保留
				"LCD_LOGO_BASE",						#22
				"SUB_LCD_LOGO_BASE",				    #23
				"sys_time_config"                       #24
);
my @match =(
        "MAKE_AUD_E2P",							        #0
				"MAKE_CUS_E2P ",                        #1
				"EM_CUSTOM",                            #2
				"CALTBL",                               #3
				"BATTERY",                              #4
				"GPIO",                                 #5
				"PM",                                   #6
				"KEYPAD",                               #7
				"KPDLIGHT",                             #8
				"PWM",                                  #9
				"TOUCHSCREEN",                          #10
				"SERVICE",                              #11
				"GPD",                                  #12
				"DUMMY_PATH",          			        #13 : DISPTBL_DEFAULT 原本要移除, 改為保留
				"LCD_LOGO",                             #14
				"LCD_BASE",                             #15
				"PARTITION_V2_PNI",                     #16
				"FAT_CONFIG",                           #17
				"SYS_CONFIG",                           #18
				"FMS_CONFIG",                           #19
				"SYS_E2P",								#20
				"DUMMY_PATH",							#21 : LCD_SRC_LIST 原本要移除, 改為保留
				"LCD_LOGO_BASE",						#22
				"SUB_LCD_LOGO_BASE",				    #23
				"SYSTIME_CONFIG"                        #24
				);
my $max_product_index= 0;
if($#ARGV < 0)
{
	#set product as parameter in command line, which do not need to list all products for user selection
	print "available products:\n";

	open(CMD, "find ./mak -name \"options_*.mak\"|");
	while(<CMD>)
	{
		if(! /i_sw_os/)
		{
			chomp;
			s/options_//g;
			s/mak//g;
			s/\W//g;
			print " $max_product_index ";
			push @prd, $_;
			print " - ", $_, "\n";
			$max_product_index++;
		}
	}
	print " $max_product_index ";
	push @prd, "ALL";
	print " - ALL and delete cust";
	#$max_product_index++;
	close(CMD);
}

my $product;
my $rootdir = PRODUCT_DIR;

if($#ARGV < 0)
{
	my $in;
	print "type product: ";
	chomp($in = <STDIN>);

	if ( ($in ne "") && ($in !~ /[A-Za-z]/) )
	{
		if ($in >=0 && $in<=$max_product_index )
		{
			$product = $prd[$in];
			print "Chose product $in. $product \n";
		}
		else
		{
				print " Index out of boundary !!!"if ($in ne "");
				exit 1;
		}
	}
	elsif($in =~ "")
	{
		exit 1;
	}
	else
	{
		$product = $in if ($in ne "");
		print "Chose product $product\n";
	}
}

my @files_array;

my $product_path = "$rootdir$product";
my $mak_path = "$product_path/mak";
my $e2p_path = "$product_path/e2p";
my $cust_path = "$product_path/cust";
my $include_path = "$product_path/include";
my $nandprt_path = "$product_path/nandprt";
my $feedback_path = "$product_path/feedback";
my $fat_path = "$product_path/fat";
my $cust_mmi_path = "$cust_path/mmi";
my $cust_sys_path = "$cust_path/sys";
my $cust_drv_path = "$cust_path/drv";

if($product =~ /ALL/)
{
	my $temp = 0;
	while($temp < $max_product_index)
	{
		$product = $prd[$temp];
		$product_path = "$rootdir$product";
		$mak_path = "$product_path/mak";
		$e2p_path = "$product_path/e2p";
		$cust_path = "$product_path/cust";
		$include_path = "$product_path/include";
		$nandprt_path = "$product_path/nandprt";
		$feedback_path = "$product_path/feedback";
		$fat_path = "$product_path/fat";
		$cust_mmi_path = "$cust_path/mmi";
		$cust_sys_path = "$cust_path/sys";
		$cust_drv_path = "$cust_path/drv";
		&process;
		$temp++;
	}

	#
	# this should be the last one
	#
	&refineMak;

	`rm -rf ./mak`;
	`rm -rf ./sc/customer/product/cust`;
}
else
{
	&process;
}

#process a product
sub process
{
	print "\n########## $product ##########\n";
	&parseMak;
	&include;
	&e2p;
	&codesizelog;
	&fat;
	&feedback;
	&nandprt;
	&scatter;
	&mmi;
	&sys;
	&drv;
	print "#####################################\n";
}

# replacePattern.pl
sub replacePattern
{
	my $filename = shift;
	my $pattern = shift;
	my $newPattern = shift;

	open(H_FILE, "$filename") ;
	my @content=<H_FILE>;
	close(H_FILE);

	open(H_FILE, "> $filename") ;
	$pattern =~ s/\$/\\\$/ig;
	$pattern =~ s/\(/\\\(/ig;
	$pattern =~ s/\)/\\\)/ig;
	$pattern =~ s/\+/\\\+/ig;
	if ($pattern =~ /MAK_ARCH/)
	{
		$pattern =~ s/\\/\\\\/ig;
	}
	#$newPattern =~ s/\$/\\\$/ig;
	#$newPattern =~ s/\(/\\\(/ig;
	#$newPattern =~ s/\)/\\\)/ig;

	printf "releace $pattern "." with "." $newPattern\n";

	for my $line (@content)
	{
		if ($line =~ /$pattern/)
		{
			printf "releace $pattern "." with "." $newPattern\n";
			$line =~ s/$pattern/$newPattern/;
		}
		print H_FILE $line;
	}
	close(H_FILE);
}

#parse option.mak
sub refineMak
{
	# 1. ./config.mak: MAK=$(TOP)/mak/ --> MAK=$(TOP)/sc/customer/product/$(PRODUCT)/mak/
	replacePattern("./config.mak", "MAK=\$\(TOP\)/mak/",  "MAK=\$\(TOP\)/sc/customer/product/\$\(PRODUCT\)/mak/" );

	# 2. ./tng/compil.mak: options_$(product_name).mak --> options.mak
	replacePattern("./tng/compil.mak", "OPTIONS_CUS_MAK=\$\(MAK\)options_\$\(PRODUCT\).mak",  "OPTIONS_CUS_MAK=\$\(MAK\)options.mak" );

	# 3. ./tng/configure.pl: my $MAK_ARCH = "1"; -> my $MAK_ARCH = "0";
	replacePattern("./tng/configure.pl", "MAK_ARCH = \"1\"",  "MAK_ARCH = \"0\"" );

	# 4. ./sc/customer/product/common/mak/common_option.mak: PP_OPT_COMMON += __COMPONENT_BASE_CONFIGURATION__ -> #PP_OPT_COMMON += __COMPONENT_BASE_CONFIGURATION__
	replacePattern("./sc/customer/product/common/mak/common_option.mak", "PP_OPT_COMMON \+= __COMPONENT_BASE_CONFIGURATION__",  "#PP_OPT_COMMON \+= __COMPONENT_BASE_CONFIGURATION__" );


}


#parse option.mak
sub parseMak
{
	  my @array;
		mkdir $product_path, 0755;
		mkdir $e2p_path, 0755;
		mkdir $mak_path, 0755;
		mkdir $cust_path, 0755;
		mkdir $cust_mmi_path, 0755;
		mkdir $cust_sys_path, 0755;
		mkdir $cust_drv_path, 0755;
		mkdir $nandprt_path, 0755;
		mkdir $fat_path, 0755;
		mkdir $feedback_path, 0755;
		mkdir $include_path, 0755;
		mkdir "$cust_mmi_path/inc", 0755;
		mkdir "$cust_sys_path/inc", 0755;
		mkdir "$cust_drv_path/inc", 0755;
		mkdir "$cust_mmi_path/src", 0755;
		mkdir "$cust_sys_path/src", 0755;
		mkdir "$cust_drv_path/src", 0755;

		my $i = 0;
		while($i < $match_number)
		{
			$files_array[$i] = MAGIC_STR;
			$i++;
		}
		my $dir = "./mak";
		opendir PRD, $dir ;
		for my $makfile (sort(readdir(PRD)))
		{
			if ($makfile =~ /$product\.mak/)
			{
				#copy("$dir/$makfile","$mak_path/options.mak");
				open (MAK1, "+>$mak_path/options.mak") ;
				open (MAK,"$dir/$makfile") ;
				my $temp = 0;
				while(<MAK>)
				{
					my $count = 0;
					while($count < $match_number)
					{
						if(index($_,$match[$count]) == 0)
						{
							@array = split(/=/);
							$files_array[$count] = $array[1];
							$files_array[$count] =~ s/\s//g;
							chomp($files_array[$count]);
							$temp = 1;
							print "$match[$count] = $files_array[$count]\n";
							if(! $files_array[$count])
							{
								$files_array[$count] = MAGIC_STR;
							}
						}
						$count++;
					}
					if($temp == 0)
					{
						print MAK1 $_ ;
					}
					else
					{
						$temp = 0;
					}
				}
				close MAK;
				close MAK1;
			}
		}
		closedir PRD;
}

#include part
sub include
{
	my $dir = "sc/customer/product/cust/include";
	opendir DIR, $dir ;
	for my $file (sort(readdir(DIR)))
	{
		if($file =~ /\_$product\./)
		{
			copy("$dir/$file", "$include_path/global_config.h");
		}
	}
	closedir DIR;
}
#e2p part
sub e2p
{
	my $dir = "sc/customer/product/cust/e2p";
	opendir DIR, $dir ;
	for my $file (sort(readdir(DIR)))
	{
		if($file =~ /audioparam\_$files_array[1]\./)
		{
			copy("$dir/$file", "$e2p_path/audioparam.e2p");
		}
		if($file =~ /cusSetting\_$files_array[1]\./)
		{
			copy("$dir/$file", "$e2p_path/cusSetting.e2p.val");
		}
	}
	closedir DIR;
}
#code size log part
sub codesizelog
{
	my $dir = "sc/customer/product/cust/code_size_log";
	opendir DIR, $dir ;
	for my $file (sort(readdir(DIR)))
	{
		#print "$file $product\n";
		if($file =~ /$product/)
		{
			my $temp_name = $file;
			my $temp_string = "_$product";
			$temp_name =~ s/$temp_string//g;
			#print "$dir/$file $product_path/$temp_name\n";
			copy("$dir/$file", "$product_path/$temp_name");
		}
	}
	closedir DIR;
}
#fat part
sub fat
{
	my $dir = "sc/customer/product/cust/fat";
	opendir DIR, $dir ;
	for my $file (sort(readdir(DIR)))
	{
		#print "$file $product\n";
		if($file =~ /$files_array[17]/)
		{
			#print "$dir/$file $fat_path/$temp_name\n";
			copy("$dir/$file", "$fat_path/$file");
		}
	}
	closedir DIR;
}
#feedback part
sub feedback
{
	my $dir = "sc/customer/product/cust/feedback";
	opendir DIR, $dir ;
	for my $file (sort(readdir(DIR)))
	{
		#print "$file $product\n";
		if($file =~ /$product/)
		{
			my $temp_name = $file;
			my $temp_string = "_$product";
			$temp_name =~ s/$temp_string//g;
			#print "$dir/$file $product_path/$temp_name\n";
			copy("$dir/$file", "$feedback_path/$temp_name");
		}
	}
	closedir DIR;
}
#nandprt part
sub nandprt
{
	my $dir = "sc/customer/product/cust/nandprt";
	opendir DIR, $dir ;
	for my $file (sort(readdir(DIR)))
	{
		#print "$file $product\n";
		if($file =~ /nand_conf/)
		{
			my $temp_name = $file;
			if(index("$product", "8533") == 0)
			{
				$temp_name =~ s/_b3//g;
				#print "$dir/$file $product_path/$temp_name\n";
				copy("$dir/$file", "$mak_path/$temp_name");
			}
			else
			{
				$temp_name =~ s/_g1//g;
				#print "$dir/$file $product_path/$temp_name\n";
				copy("$dir/$file", "$mak_path/$temp_name");
			}
		}
		elsif($file =~ /PARTITION/)
		{
			if($file =~ /$files_array[16]/)
			{
				my $part = $file;
				$part =~ s/\_$files_array[16]//g;
				copy("$dir/$file", "$nandprt_path/$part");
			}
		}
		else
		{
			copy("$dir/$file", "$nandprt_path/$file");
		}
	}
	unlink "$mak_path/nand_conf_b3.mak";
	unlink "$mak_path/nand_conf_g1.mak";
	closedir DIR;
}
#scatter part
sub scatter
{
	my $dir = "sc/customer/product/cust/scatter";
	opendir DIR, $dir ;
	for my $file (sort(readdir(DIR)))
	{
		if(index("$product", "8533") == 0)
		{
			if(index("$file", "8533") != -1)
			{
				copy("$dir/$file", "$mak_path/$file");
			}
		}
		else
		{
			if(index("$file", "8533") == -1)
			{
				copy("$dir/$file", "$mak_path/$file");
			}
		}
	}
	closedir DIR;
}
#mmi part
sub mmi
{
	my $dir = "sc/customer/product/cust/mmi";
	opendir DIR, "$dir/inc" ;
	for my $file (sort(readdir(DIR)))
	{
		copy("$dir/inc/$file", "$cust_mmi_path/inc/$file");
	}
	closedir DIR;
	opendir DIR, "$dir/src" ;
	for my $file (sort(readdir(DIR)))
	{
		if($file =~ /$prefix[2]\_$files_array[2]\./)
		{
			copy("$dir/src/$file", "$cust_mmi_path/src/mmi_emapp_custom.c");
		}
	}
	closedir DIR;
	open (MAK, "$dir/cust_mmi.mak") ;
	open (MAK1, "+>$cust_mmi_path/cust_mmi.mak") ;
	while(<MAK>)
	{
		if(/if/)
		{}
		elsif(index("$_","CUS_EM_SRC_LIST") == 0 )
		{
			if($files_array[2] =~ /abcd/ and $_ =~ /$match[2]/)
			{
					#print "$match[$temp] $files_array[$temp]\n";
					$_ =~ s/[\d\D]//g;
			}
			s/$match[2]//g;
			s/\_\$\(\)//g;
			#print "$_";
			print MAK1 $_ ;
		}
		else
		{
			print MAK1 $_ ;
		}

	}
	close MAK;
	close MAK1;
}
#sys part
sub sys
{
	my $dir = "sc/customer/product/cust/sys";
	opendir DIR, "$dir/inc" ;
	for my $file (sort(readdir(DIR)))
	{
		copy("$dir/inc/$file", "$cust_sys_path/inc/$file");
	}
	closedir DIR;
	opendir DIR, "$dir/src" ;
	for my $file (sort(readdir(DIR)))
	{
		my $temp = $file;
		if($file =~ /e2p/)
		{
			if($file =~ /$prefix[20]\_$files_array[20]\./)
			{
				$temp =~ s/\_$files_array[20]//g;
				copy("$dir/src/$file", "$cust_sys_path/src/$temp");
			}
		}
		if($file =~ /fms/)
		{
			if($file =~ /$prefix[19]\_$files_array[19]\./)
			{
				$temp =~ s/\_$files_array[19]//g;
				copy("$dir/src/$file", "$cust_sys_path/src/$temp");
			}
		}
		if($file =~ /sys/)
		{
			if($file =~ /$prefix[18]\_$files_array[18]\./)
			{
				$temp =~ s/\_$files_array[18]//g;
				copy("$dir/src/$file", "$cust_sys_path/src/$temp");
			}
			if($file =~ /$prefix[24]\_$files_array[24]\./)
			{
				$temp =~ s/\_$files_array[24]//g;
				copy("$dir/src/$file", "$cust_sys_path/src/$temp");
			}
		}
	}
	closedir DIR;
	open (MAK, "$dir/cust_sys.mak") ;
	open (MAK1, "+>$cust_sys_path/cust_sys.mak") ;
	while(<MAK>)
	{
		if(/ifdef/ or /endif/)
		{

		}
		else
		{
			my $temp = 18;
			while($temp < $match_number)
			{
				#print "$files_array[$temp] \n";
				if($files_array[$temp] =~ /abcd/ and $_ =~ /$match[$temp]/)
				{
					#print "$match[$temp] $files_array[$temp]\n";
					$_ =~ s/[\d\D]//g;
				}
				else
				{
					s/$match[$temp]//g;
				}
				$temp++;
			}
			s/\_\$\(\)//g;
			$temp = 18;
			print MAK1 $_ ;
		}
	}
	close MAK;
	close MAK1;
}
#drv part
sub drv
{
	my $number = 0;
	my $dir = "sc/customer/product/cust/drv";
	opendir DIR, $dir ;
	for my $file (sort(readdir(DIR)))
	{
		if($file ne "cust_drv.mak")
		{
			my $temp = 0;
			while($temp < $match_number)
			{
				if($file =~ /$prefix[$temp]/)
				{
					$number = $temp;
					#print "[$number]\n";
				}
				$temp++;
			}
			#print "$dir/$file \n";
			if (($file !~ m/^\./) and ($file ne "lcm") and ($file ne "sensor") and ($file ne "disptbl")
			             and ($file ne "backlight") and ($file ne "gsensor") and ($file ne "ofn"))
			{
				opendir DIR_1, "$dir/$file/src";
				for my $drv_file (sort(readdir(DIR_1)))
				{
					if(index($drv_file,$files_array[$number]) != -1)
					{
							my $temp_name = $drv_file;
							#my $temp_string = "$prefix[$number]_$files_array[$number].";
							$temp_name =~ s/\_$files_array[$number]//g;
							if($drv_file =~ /$prefix[$number]\_$files_array[$number]\./)
							{
								#print "$drv_file $temp_string \n";
								copy("$dir/$file/src/$drv_file","$cust_drv_path/src/$temp_name");
							}
							if($number == 5) #gpio for iss
							{
								if($drv_file =~ /init_sleep\_$files_array[$number]\./)
								{
									copy("$dir/$file/src/$drv_file","$cust_drv_path/src/init_sleep.iss");
								}
							}
							#print "1 $drv_file,$temp_name\n";
							chop($temp_name);
							chop($temp_name);
							copy("$dir/$file/inc/$temp_name.h","$cust_drv_path/inc/$temp_name.h");
							#print "2 $drv_file,$temp_name\n";
					}
				}
				closedir DIR_1;
			}
			elsif(($file =~ "lcm"))
			{
				opendir DIR_1, "$dir/$file" ;
				for my $drv_file (sort(readdir(DIR_1)))
				{
					open(FILE,"$dir/$file/$drv_file");
					if(-z FILE)
					{
						if($drv_file =~ /\b$files_array[15]\b/ )
						{
							#print "$dir/$file/$drv_file\n";
							mkdir "$cust_drv_path/src/lcd", 0755;
							opendir DIR_2, "$dir/$file/$drv_file";
							for my $lcd_file (sort(readdir(DIR_2)))
							{
								copy("$dir/$file/$drv_file/$lcd_file", "$cust_drv_path/src/lcd/$lcd_file");
							}
							closedir DIR_2;
						}
						if(index("$drv_file", "logo") == 0)
						{
							opendir DIR_2, "$dir/$file/$drv_file";
							for my $lcd_file (sort(readdir(DIR_2)))
							{
								if($lcd_file =~ /$files_array[14]/)
								{
									my $temp_name = $lcd_file;
									#my $temp_string = "$prefix[14]_$files_array[14].";
									$temp_name =~ s/\_$files_array[14]//g;
									if($lcd_file =~ /$prefix[14]\_$files_array[14]\./)
									{
										copy("$dir/$file/$drv_file/$lcd_file", "$cust_drv_path/src/$temp_name");
									}
								}
							}
							if(index("$files_array[22]", "abcd") == -1)
								{
									mkdir "$cust_drv_path/logo", 0755;
									mkdir "$cust_drv_path/logo/main", 0755;
									opendir DIR_3, "$dir/$file/$drv_file/$files_array[22]";
									for my $lcd_file (sort(readdir(DIR_3)))
									{
										copy("$dir/$file/$drv_file/$files_array[22]/$lcd_file", "$cust_drv_path/logo/main/$lcd_file");
									}
									close DIR_3
								}
								if(index("$files_array[23]", "abcd") == -1)
								{
									mkdir "$cust_drv_path/logo", 0755;
									mkdir "$cust_drv_path/logo/sub", 0755;
									opendir DIR_4, "$dir/$file/$drv_file/$files_array[23]";
									for my $lcd_file (sort(readdir(DIR_4)))
									{
										copy("$dir/$file/$drv_file/$files_array[23]/$lcd_file", "$cust_drv_path/logo/sub/$lcd_file");
									}
									close DIR_4
								}
							closedir DIR_2;
						}
						if(index("$drv_file", "lcdtbl") == 0)
						{
							mkpath("$rootdir/common/drv/lcm/lcdtbl",1,0755);
							opendir DIR_2, "$dir/$file/$drv_file";
							for my $lcd_file (sort(readdir(DIR_2)))
							{
								copy("$dir/$file/$drv_file/$lcd_file", "$rootdir/common/drv/lcm/lcdtbl/$lcd_file");
							}
							close DIR_2;
						}
						if(index("$drv_file", "global_base") == 0 or index("$drv_file", "allinone_base") == 0)
						{
							my $dest = "$rootdir/common/drv/lcm";
							my $src = "$rootdir/cust/drv/lcm/$drv_file";
							`cp -R $src $dest`;
						}
					}
					else
					{
						#print "$dir/$file/$drv_file\n";
						copy("$dir/$file/$drv_file", "$cust_drv_path/src/$drv_file");
					}
					close  FILE;
				}
				closedir DIR_1;
			}

			if( ($file eq "backlight") or ($file eq "gsensor") or ($file eq "ofn") or ($file eq "disptbl") or ($file eq "sensor"))
			{
			    mkpath("$rootdir/common/drv/$file",1,0755);
            	my $dest = "$rootdir/common/drv";
            	my $src = "$rootdir/cust/drv/$file";
            	`cp -R $src $dest`;
			}
		}
	}
	closedir DIR;
	open (MAK, "$dir/cust_drv.mak") ;
	open (MAK1, "+>$cust_drv_path/cust_drv.mak") ;
	while(<MAK>)
	{
		if(/ifdef/ or /endif/ or /ifneq/ or /ifeq/ or /\$\(error/)
		{}
		elsif(index("$_","CUST_LCD_C_FILES") == 0 or index("$_","PANEL_DATABSE") == 0)
		{
			my $temp_string = "$product\/cust\/";
			s/cust\//$product\/cust\//g;
			s/lcm/src/g;
			s/\$\(LCD_BASE\)/lcd/g;
			#print "$_";
			print MAK1 $_ ;
		}
		elsif(index("$_","CUS_DRV_SRC_LIST") == 0)
		{
			my $temp_number = 3;
			while($temp_number < $match_number)
			{
				if($files_array[$temp_number] =~ /abcd/ and $_ =~ /$match[$temp_number]/)
				{
					$_ =~ s/[\d\D]//g;
				}
				s/$match[$temp_number]//g;
				s/\_\$\(\)//g;
				$temp_number++;
			}
			#print "$_";
			print MAK1 $_ ;
		}
		else
		{
			print MAK1 $_ ;
		}

	}
	close MAK;
	close MAK1;

	copy("$dir/cust_drv_dummy.mak","$cust_drv_path/cust_drv_dummy.mak");
}
