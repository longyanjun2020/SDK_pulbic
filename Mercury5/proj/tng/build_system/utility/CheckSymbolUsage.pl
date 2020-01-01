#!/usr/bin/perl

use warnings;
use strict;
use File::Basename;
use File::Copy;

die "This file is used to list the symbol used in one specific objfile with ROM/RAM usage\n \
Usage: CheckSymbolUsage link.info objfile\n" if @ARGV != 2;

my $input_file = shift (@ARGV);
my $obj_file = shift (@ARGV);

my $RAM = 0;
my $ROM = 0;

my $my_text = 0;
my $my_bss = 0;
my $my_ro_data = 0;
my $my_rw_data = 0;

my $my_temp_name;
my $my_temp_addr;
my $my_temp_type;
my $my_temp_size;
my $my_temp_obje;
my $my_temp_section;

my %SYM_HASH;

open MAP_FILE, "<$input_file" or die "LinkInfo $input_file not found\n";

# read map file
while (<MAP_FILE>)
{
	chomp;
	
	if (/^\s*Image Symbol Table\s*/)
	{
		last;
	}
}

while (<MAP_FILE>)
{
	#Symbol Name                              Value     Ov Type        Size  Object(Section)
	#sn_SapiSelect__Sapi                      0x0007ba59   Thumb Code    36  sn_sapi.o(.text)
	if (/^\s*([\w\@]+)\s+0x([\da-f]+)\s+(ARM Code|Thumb Code|Data)\s+(\d+)\s+([\w\.]+)\(([\w\.]+)\)/)
	{
		#print "$1 $2 $3 $4 $5 $6\n\n";
		$my_temp_name = $1;
		$my_temp_addr = $2;
		$my_temp_type = $3;
		$my_temp_size = $4;
		$my_temp_section = $6;
		if ($5 eq $obj_file)
		{
			if ($my_temp_section=~/(\.text)/ | $my_temp_type=~/(ARM Code)|(humb Code)/)
			{
				#    RtkSuspendTaskTreat                      0x00050f11   Thumb Code    64  rtk11utl.o(.text)
				$my_text += $my_temp_size;
				print "text \t\t $my_temp_size \t $my_temp_name\n";
			}
			elsif($my_temp_section=~/\.bss/)
			{
				#    rtk_Tasks                                0x00dc28a8   Data         800  rtk11utl.o(.bss)
				$my_bss += $my_temp_size;
				print "bss \t\t $my_temp_size \t $my_temp_name\n";
			}
			elsif($my_temp_section=~/\.constdata/)
			{
				#    cus_InitSem                              0x0087d41c   Data         417  init.o(.constdata)
				$my_ro_data += $my_temp_size;
				print "ro data \t $my_temp_size \t $my_temp_name\n";
			}
			elsif($my_temp_section=~/\.data/)
			{
				#    cus_NbTask                               0x00bba174   Data           1  init.o(.data)
				$my_rw_data += $my_temp_size;
				print "rw data \t $my_temp_size \t $my_temp_name\n";
			}
			else
			{
				# following pattern could not be treated as RO Data, RW Data
				#    Rtk_PtrFirstEnv                          0x00bb9644   Data           4  rtk11utl.o(.data)
				#    Rtk_PtrLastEnv                           0x00bb9648   Data           4  rtk11utl.o(.data)
				#    ms_memoryhandle                          0x00e276bc   Data           4  rtk11utl.o(SysNonZI)
				#    sys_HwWdtDebugData                       0x08000000   Data         148  rtk11utl.o(sys_HwWdtDebug)
				#print "\t [ special case:",$my_temp_name," @ ",$my_temp_section," ]\n";
				$SYM_HASH{$my_temp_name}=$my_temp_addr;
			}
		}
	}
	
	elsif (/^\s*Memory Map of the image\s*/)
	{
		last;
	}
	else
	{
		#print $_;
		next;
	}
	
}

# procrss unknow symbol collected in previous stage
# The goal is finding following pattern:
#    Base Addr    Size         Type   Attr      Idx    E Section Name        Object
#    0x00e276bc   0x00000004   Data   RW         3152    SysNonZI            rtk11utl.o(rtk.lib)


while (<MAP_FILE>)
{
	#print "special section:\n\n\n\n\n" ;
	#    0x00e276bc   0x00000004   Data   RW         3152    SysNonZI            rtk11utl.o(rtk.lib)
	if (/^\s*0x(\w+)\s*0x(\w+)\s*(Code   RO|Data   RO|Data   RW|Zero   RW|Ven    RO)\s+\d+\s+(\w+)\s+([\w\.]+)\(([\w\.]+)\)/)
	{
		if ($5 eq $obj_file)
		{
			#print "$1 $2 $3 $4";
			$my_temp_addr = $1;
			$my_temp_size = hex($2);
			$my_temp_type = $3;
			
			while (my ($key, $value) = each (%SYM_HASH))
			{
				# key: symbol name
				# value: address
				if ($my_temp_addr eq $value)
				{
					if ($my_temp_type =~/Data   RW/)
					{
						$my_rw_data += $my_temp_size;
						print "rw data \t $my_temp_size \t $key\n";
					}
					elsif ($my_temp_type =~/Code   RO/)
					{
						$my_text += $my_temp_size;
						print "text \t\t $my_temp_size \t $key\n";
					}
					elsif ($my_temp_type =~/Data   RO/)
					{
						$my_ro_data += $my_temp_size;
						print "ro data \t $my_temp_size \t $key\n";
					}
					elsif ($my_temp_type =~/Zero   RW/)
					{
						$my_bss += $my_temp_size;
						print "bss \t\t  $my_temp_size \t $key\n";
					}
					elsif($my_temp_type =~/Ven    RO/)
					{
						print "Ven    RO \t $my_temp_size \t $key (do not take in)\n";
					}
					delete $SYM_HASH{"$key"};
				}
			}
		}
	}
}

close MAP_FILE;

print "==================================\n";
print " text: ",$my_text,"\n";
print " ro_data: ",$my_ro_data,"\n";
print " bss: ",$my_bss,"\n";
print " rw_data: ",$my_rw_data,"\n";

print "==================================\n";

if(0)
{	
	while (my ($key, $value) = each (%SYM_HASH))
	{
		print "undefined: ",$key," ",$value,"\n";
	}
}

open MAP_FILE, "<$input_file" or die "LinkInfo $input_file not found\n";

# read map file
while (<MAP_FILE>)
{
	chomp;
	
	if (/^\s*Image Symbol Table\s*/)
	{
		last;
	}
}

while (<MAP_FILE>)
{
	#Symbol Name                              Value     Ov Type        Size  Object(Section)
	#sn_SapiSelect__Sapi                      0x0007ba59   Thumb Code    36  sn_sapi.o(.text)
	if (/^\s*([\w\@]+)\s+0x([\da-f]+)\s+(ARM Code|Thumb Code|Data)\s+(\d+)\s+([\w\.]+)\(([\w\.]+)\)/)
	{
		#print "$1 $2 $3 $4 $5 $6\n\n";
		$my_temp_name = $1;
		$my_temp_addr = $2;
		$my_temp_type = $3;
		$my_temp_size = $4;
		$my_temp_section = $6;
		if ($5 eq $obj_file)
		{
			
			while (my ($key, $value) = each (%SYM_HASH))
			{
				# key: symbol name
				# value: address
				if ($my_temp_name eq $key)
				{
					print "Data \t $my_temp_size \t $key\n";
					delete $SYM_HASH{"$key"};
				}
			}
		}
	}
	
	elsif (/^\s*Memory Map of the image\s*/)
	{
		last;
	}
	else
	{
		#print $_;
		next;
	}
	
}

close MAP_FILE;