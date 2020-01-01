#!/usr/bin/perl

use strict;
use Getopt::Std;

my $Version="v 1.0";
my $Date="June 2011";

my $CustimerTaskInfo=0;
my $SystemTaskInfo=0;
my $Output=0;
my $Verbose=0;
my $Tpp=0;

my %opts;
getopts("c:o:t:v:s:h",\%opts);
if (exists $opts{c}) {$CustimerTaskInfo=$opts{c};}	else{print"\n No Customer info is specified!!\n\n";PrintHelp(); exit 1; }
if (exists $opts{o}) {$Output=$opts{o};}	else{print"\n No Ontions file is specified!!\n\n";PrintHelp(); exit 1; }
if (exists $opts{s}) {$SystemTaskInfo=$opts{s};
	if (exists $opts{t}) {$Tpp=$opts{t};}else{	print"\n No Tpp file is specified!!\n\n";	PrintHelp(); 	exit 1; }
}
if (exists $opts{v}) {$Verbose=$opts{v};}
if (exists $opts{h}) {PrintHelp(); exit 1; }

dbg_print( "CustimerTaskInfo=$CustimerTaskInfo\n" );
dbg_print( "SystemTaskInfo=$SystemTaskInfo\n" ) if (exists $opts{s}) ;
dbg_print( "Output=$Output\n" );
dbg_print( "Verbose=$Verbose\n" );


#----------------------------------------------------------------------
# 1. parsing customer task priority
#----------------------------------------------------------------------
my %TSK_PRIO;

open(CUS_APP, "< $CustimerTaskInfo") or die "cannot open CustimerTaskInfo \"$CustimerTaskInfo\"\n";
while(<CUS_APP>)
{
	# skip command and spece line
	next if ( $_ =~ m/(\#)|(^\s*$)/ );
	
	#
	# start parsing following pattern:
	# {Stack pointer, Initialisation function, Parser function, Stack Size, Priority, Task Name},
	# {vm_apmCustomStack1,  vm_apmAppliInit1 , vm_apmAppliParser1  , 4000,  59, "DEV"},
	# {vm_apmCustomStack2,  vm_apmAppliInit2 , vm_apmAppliParser2  , 512,  56, "DVTST" },
	#
	#if( $_ =~ m#(\{.*vm_apmCustomStack.*vm_apmAppliParser\w*\s*\,\s*(\w*)\s*\,\s*\"(\w*)\".*)# )
	if( $_ =~ m#(\{.*vm_apmCustomStack.*vm_apmAppliParser\w*\s*\,.*\,\s*(\w*)\s*\,\s*\"(\w*)\".*)# )
	{
		dbg_print( $1."\n" );
		dbg_print( $2."--".$3."\n" );
		
		if($2<10){	$TSK_PRIO{$3}="0".$2;	}
		else	 {	$TSK_PRIO{$3}=$2;		}
	}
}
close(CUS_APP);

#----------------------------------------------------------------------
# 2-1. parsing tpp file to get location of sys_rtk_config.h
# 2-2. parsing sys_rtk_config.h to get RTK_MAX_TASKS
# 2-3. parsing init.c.pp to get system task priority
#----------------------------------------------------------------------
my $sys_rtk_config;
my $RTK_MAX_TASKS;
	
if (exists $opts{s}) 
{
	# 2-1. parsing tpp file to get location of sys_rtk_config.h
	open(TPP_FILE, "< $Tpp") or die "cannot open Tpp \"$Tpp\"\n";
	while(<TPP_FILE>)
	{
		if ( $_ !~ m/sys_rtk_config.h/ )
		{
			next;
		}
		else
		{
			$_ =~ m#(\s+sc(\w*\/)*sys_rtk_config\.h)#o;
			$sys_rtk_config = $1 ;
			dbg_print( $sys_rtk_config."\n" );	
			# 2-2. parsing sys_rtk_config.h to get RTK_MAX_TASKS
			open(SYS_RTK_CONFIG, "< $sys_rtk_config") or die "cannot open sys_rtk_config \"$sys_rtk_config\"\n";
			while(<SYS_RTK_CONFIG>)
			{
				# skip command and spece line
				next if ( $_ !~ m/RTK_MAX_TASKS/ );
				$_ =~ m#RTK_MAX_TASKS\s*(\w*)\s*#;
				$RTK_MAX_TASKS = $1 ;
				dbg_print( "RTK_MAX_TASKS = ".$RTK_MAX_TASKS);
				last
			}
			close(SYS_RTK_CONFIG);
			last;
		}
		
	}
	close(TPP_FILE);


	# 2-3. parsing init.c.pp to get system task priority
	open(INIT_C, "< $SystemTaskInfo") or die "cannot open SystemTaskInfo \"$SystemTaskInfo\"\n";
	while(<INIT_C>)
	{
		# skip command and spece line
		next if ( $_ =~ m/(\#)|(^\s*$)/ );
		
		#
		# start parsing following pattern:
		# {Name,   EntryPoint, Priority, StackSize, arm exception el },
		# {"IDLE", idle_Task,  0,        5000,     ((u32) ((0x16) & 0xff))},
		# {"CE",   ce_Task,    50,       700,      ((u32) (((0x17 + 1 + 0x8) + 0x0a + 0x16) & 0xff))},
		#
		 if( $_ =~ m#(\{\"(\w*)\"\s*\,\s*\w*_Task\s*\,\s*(\w*)\s*\,)#i )
		{
			dbg_print( $1."\n" );
			dbg_print( $2."--".$3."\n" );			
			if($3>0){	$TSK_PRIO{$2}=($RTK_MAX_TASKS+$3);	}
			else	{	$TSK_PRIO{$2}="0".$3;		}
		}
	}
	close(INIT_C);
} #if (exists $opts{s}) 


#----------------------------------------------------------------------
# 3. output task priority info.
#----------------------------------------------------------------------
my @order = sort { $TSK_PRIO{$a} <=> $TSK_PRIO{$b} } keys %TSK_PRIO;
open(OUTPUT, "> $Output") or die "cannot read \"$Output\" file\n";
print OUTPUT "# priority:\ttask name\n";
print OUTPUT "#\n";
print OUTPUT "# Following are customer tasks\n";
print OUTPUT "#\n";
for my $line (@order)
{
	last if ( (exists $opts{s}) && ($TSK_PRIO{$line} >= $RTK_MAX_TASKS) );
	print OUTPUT $TSK_PRIO{$line},":\t",$line,"\n";
}
if(exists $opts{s})
{
	print OUTPUT "#\n";
	print OUTPUT "# Following are system tasks\n";
	print OUTPUT "# (RTK_MAX_TASKS=$RTK_MAX_TASKS)\n";
	print OUTPUT "#\n";
	for my $line (@order)
	{
		next if ( $TSK_PRIO{$line} < $RTK_MAX_TASKS );
		print OUTPUT $TSK_PRIO{$line},":\t",$line,"\n";
	}
}
close OUTPUT ;

#----------------------------------------------------------------------
# debug print
#----------------------------------------------------------------------
sub dbg_print {
  if ($Verbose >= 1) { printf shift; }
}


#----------------------------------------------------------------------
# print user guide
#----------------------------------------------------------------------
sub PrintHelp {
print <<"EOF";
Script to check multiple defined symbol
RDO - MStar Taiwan - $Date - version $Version
Usage:$0 [-l link\.info] [-o options_\$\(product_name\)\.mak] [-v verbose mode] [-h]
  -c: customer task file, for parsing customer task priority 
      e.g. ./build/$(product_name)/out/cus_app.c.pp
  -s: system task file, for parsing system task priority 
      e.g. ./build/$(product_name)/out/init.c.pp
  -t: tpp file which contans sys_rtk_config.h, for getting RTK_MAX_TASKS,
      (this option only work as -s is specified)
      e.g. ./build/$(product_name)/out/tsk_prio.tpp
  -o: Output file
  -v: verbose mode, print debug messages, e.g. -v1
  -h: help, show this user guide
EOF
exit 0;  
}

