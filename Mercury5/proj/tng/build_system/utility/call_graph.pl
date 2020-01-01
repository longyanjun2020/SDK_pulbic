#!/usr/bin/perl
use strict;
use warnings;
use Getopt::Std;
use POSIX;

my $Version="v 2.0";
my $Date="Mar 2012";

##--------------------------------------------------------------------------------------------------
## Author  | Rev | Date     | Comment
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.0 | 12/28/11 | Creation, first version (for 32/64 compression)
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.1 | 01/04/12 | process ".sym" pattern
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.2 | 01/12/12 | add option: \$CmprAlgo (compress algorithm)
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.3 | 01/31/12 | add limition, and add 32/32 compression 
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.4 | 02/02/12 | process new pattern in call_graph.htm 
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.5 | 02/06/12 | analysis enhancement 
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.6 | 02/09/12 | process static function by using 2 level hash  
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.7 | 02/14/12 | postpone check stage to the end of build process
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.8 | 02/21/12 | generate report to \$reportFile
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.9 | 03/01/12 | add "DrvClkgenInitSec" to %FUNCTION_LIST_HASH_EXTEND
##--------------------------------------------------------------------------------------------------
##  Carl   | 2.0 | 03/06/12 | add more info. to \$reportFile
##--------------------------------------------------------------------------------------------------
##  Carl   | 2.1 | 03/06/12 | set \@exception_object_list_extend
##--------------------------------------------------------------------------------------------------
##  Carl   | 2.2 | 04/17/12 | process call tree by using new 1 level hash  
##--------------------------------------------------------------------------------------------------
##  Carl   | 2.3 | 04/25/12 | place RO and string of call tree in uncompressed region
##--------------------------------------------------------------------------------------------------
##  Carl   | 2.4 | 07/04/12 | place Ke_FullReset_Config_WDT in uncompressed region
##--------------------------------------------------------------------------------------------------




#
# setting roots ! 
#
my %FUNCTION_LIST_HASH =	 					# the root of functions
(
	"sys_premain_first" => "sys_premain.o",
	"__rt_entry"        => "sys_boot_b5.o",
);

my %FUNCTION_LIST_HASH_EXTEND = 
(
	"DrvClkgenInitSec"          => "drv_clkgen_cmu.o",
	"DrvUartInit"               => "drv_uart_api.o",
	"sysCheckDwlMode"           => "hal_drv_util.o",
	"sys_MemInit"               => "sys_mem.o",
	"sys_Enable_cache"          => "sys_core.o",
	"_do_decompress_selected"   => "sys_premain.o",
	"Ke_FullReset_Config_WDT"   => "sys_reset.o"
);




#
# decompression function, since call back function could not be detected by call graph,
# we need to add them manumally
#
my %ZLIB_FUNCTION_HASH =
(
	"uncompress"           => "uncompr.o",
	"adler32"              => "adler32.o",
	"adler32_null"         => "adler32.o",
);
my %LZMA_FUNCTION_HASH =
(
	"MsLzmaDeCompress"     => "MsLzma.o",
);



#
# setting exception function list 
#
my $enable_exception_funtion_list = 1;
my @exception_funtion_list =  					# exception function list  
qw ( 
	BACKTRACE_STORE
	BACKTRACE_WATCHDOG
	_RtkAssertRoutine
	sys_InitE2pErrorStack
	MsSleep
	sys_premain_second
);


#
# setting exception object list
#
my $enable_exception_object_list = 1;
my @exception_object_list =  					# exception function list  
qw ( 
	sys_boot_bravo
	sys_boot_blossom
	sys_boot_b5
	hal_bus_qspi
	hal_bus_fsp_spi
);


my @exception_object_list_extend =  				# exception function list  
qw (
	drv_serial_flash
	hal_serial_flash
	drv_flash_lowl_comm
	hal_int_ctrl
);





my %FUN_HASH;                           # to record the function (2 level)
my %FUN_HASH_EXCEPTION;                 # exception function hash
my %OBJ_HASH;                           # to record the object
my %OBJ_HASH_EXCEPTION;                 # exception object file hash
my %LIB_HASH;                           # to record the hash
my %OBJ_TO_LIB_HASH;                    # generate a link back to lib
my %CALL_GRAPH_DATABASE_HASH;           # recond the location in call graph html (2 level)
my %CALL_GRAPH_DATABASE_HASH2;          # recond the location in call graph html (1 level but more powerful)
my %DEP_OBJ_HASH;                       # object hash for dependency 
my @CALL_TREE;                          # call tree, element: "$function name"."AZAZAZAZ"."$obj name"


my %opts;
my $call_graph_html ;                   # input:  $(product_name).htm
my $link_info;
my $fl;
my $ol;
my $ol2;
my $ll;
my $Verbose=100;
my $parsing_level=0;
my $product;
my $cmpr_algo=1;
my $max_number_of_function;					# KB
my $max_size_of_object;					
my $extend_function=0;					
my $testify=0;
my $reportFile=0;

getopts("h:c:f:o:a:v:l:p:s:n:e:z:t:r:",\%opts);
if( exists $opts{h} ) { PrintHelp(); exit 0;  }
if( exists $opts{t} ) { 
	$testify=$opts{t};
	if( exists $opts{n} ) { $max_number_of_function=$opts{n};}else{print "no max_number_of_function";PrintHelp(); exit 1; }
	if( exists $opts{s} ) { $max_size_of_object = $opts{s}; } else {print "no max_size_of_object";PrintHelp(); exit 1; }
}
if( exists $opts{p} ) { $product = $opts{p}; } else { print "no product!"; PrintHelp(); exit 1; }
if( exists $opts{c} ) { $call_graph_html = $opts{c}; } else { print "no call graph html!"; PrintHelp(); exit 1; }
if( exists $opts{l} ) { $link_info = $opts{l}; } else { print "no link\.info!"; PrintHelp(); exit 1; }
if( exists $opts{a} ) { $ll = $opts{a}; }
if( exists $opts{z} ) { $cmpr_algo = $opts{z};  if( 2<$cmpr_algo|| 0>$cmpr_algo ){ print "wrong algo!"; exit 1;} } 
	else { print "no compress algo!"; PrintHelp(); exit 1; }
if( exists $opts{e} ) { $extend_function = $opts{e}; }
if( exists $opts{f} ) { $fl = $opts{f}; } else { print "no function list!"; PrintHelp(); exit 1; }
if( exists $opts{o} ) { $ol = $ol2 = $opts{o}; } else { print "no obj list!"; PrintHelp(); exit 1; }
if( exists $opts{r} ) { $reportFile = $opts{r}; }
if( exists $opts{v} ) { $Verbose=$opts{v}; } #else { print "warning: no call_levle is specified, only level > $Verbose would be show"; }



#
# print user guide
#
sub PrintHelp {
print "\n".<<"EOF";

Script to parse call graph
RDO - MStar Taiwan - $Date - version $Version

Usage:$0 [-h htm] [-p product] [-c htm] 
 [-l link.info] [-f function list ] [-o object list] [-z compress algo] 
 [-n max number of function] [-s max size of object] [-e extend] [-t testify]
 [-v verbose level]
 
  -h: help, show this user guide
  -t: testify: to check the size constraint
  -p, product, the product name
  -c: htm, specify call graph html e.g.  85xx_xx_xx_mbxxx.htm
  -l: link.info
  -f: function list, specify the output function list
  -o: object list, specify the output object file list
  -a: lib(archive) list, specify the output lib file list
  -z: compress algo, 1:zlib, 2:lzma
  -n: max number of function
  -s: max size of object
  -e: extend, 0:(default) __EXTRACT_BOOT_IMAGE__, 1:__COMPRESS_SELECTED_BIN__
  -v: verbose mode, print debug messages if level > verbose, e.g. -v1
EOF
}








#
# 1.  set function list, exception function list, exception object list 
#
sub set_extend_and_exception_list
{

	if( $extend_function eq 1 ) {
		foreach my $keys (keys %FUNCTION_LIST_HASH_EXTEND) {
			$FUNCTION_LIST_HASH{$keys} = $FUNCTION_LIST_HASH_EXTEND{$keys} ;
		}
	}

	if( $cmpr_algo eq 1 ) {
		foreach my $keys (keys %ZLIB_FUNCTION_HASH) {
			$FUNCTION_LIST_HASH{$keys} = $ZLIB_FUNCTION_HASH{$keys} ;
		}
	}

	if( $cmpr_algo eq 2 ) {
		foreach my $keys (keys %LZMA_FUNCTION_HASH) {
			$FUNCTION_LIST_HASH{$keys} = $LZMA_FUNCTION_HASH{$keys} ;
		}
	}

	if( $enable_exception_funtion_list eq 1) {
		$FUN_HASH_EXCEPTION{$_} = "1" for @exception_funtion_list ;
	}

	if( $enable_exception_object_list eq 1) {
		$OBJ_HASH_EXCEPTION{$_} = "1" for @exception_object_list ;
		if( $extend_function eq 1 ) {
			$OBJ_HASH_EXCEPTION{$_} = "1" for @exception_object_list_extend ;
		}
	}

}






#
# 2. parsing call graph to record the location of each function  (for speedup) 
#
sub call_graph_database
{
	my $seek_addr = 0;
	open( CALL_GRAPH_HEML, "<", $call_graph_html) or die "can not open $call_graph_html";
	while($_=<CALL_GRAPH_HEML>)
	{
		if( $_ =~ /\<P\>\<STRONG\>\<a name\=\"\[(.*)\]\"\>\<\/a>(\w*)\<\/STRONG\>.+, (\d+) bytes, Stack size \w+ bytes, (\w+\.o|\w+\.sym|UNDEFINED)/g )
		{
			my $html_id = $1;
			my $function_name = $2;
			my $obj_name = $4;
			$obj_name =~ s/\.o//g;

			# 2-level hash
			# level 1: key -> value == function name -> level 2 hash
			# level 2: key -> value == object name -> seek addr
			${$CALL_GRAPH_DATABASE_HASH{$function_name}}{$obj_name} = $seek_addr;
			$CALL_GRAPH_DATABASE_HASH2{$html_id} = $seek_addr;
		}
		$seek_addr = tell CALL_GRAPH_HEML;
	}
	close CALL_GRAPH_HEML;
}





#
# 3. start parsgin call tree recursively by using DFS
#
sub parsing_call_graph
{
	my @function_list = sort keys %FUNCTION_LIST_HASH;

	for( my $i=0; $i<=$#function_list; ++$i )	
	{
		my $target_function = $function_list[$i];
		my $target_obj = $FUNCTION_LIST_HASH{$target_function};

		if( !exists $FUN_HASH{$target_function} && !exists ${$FUN_HASH{$target_function}}{$target_obj} ) 
		{
			go_parsing_function( $target_function, $target_obj, "ABABABAB" ) ;
		}
	}
}





#
# 3-1. DFS
#
sub go_parsing_function
{
	my $target_function = shift ;
	my $target_obj = shift ;  # the obj of caller
	my $html_id = shift ;

	return if ( $enable_exception_funtion_list eq 1 && exists $FUN_HASH_EXCEPTION{$target_function} );



	if( $html_id ne "ABABABAB" )
	{
		if( !exists $CALL_GRAPH_DATABASE_HASH2{$html_id} )
		{
			print $target_function."error message: html_id: $html_id not find -$target_function-!!\n\n";
			exit 1;
		}
	}
	elsif( !exists $CALL_GRAPH_DATABASE_HASH{$target_function} )
	{
		print $target_function."error message: seek not find -$target_function-!!\n\n";
		exit 1;
	}

	
	$parsing_level++;

	
	#
	# take seek address by 2 key: $target_function, $target_obj
	#
	my $target_seek_addr = 0 ;
	open( CALL_GRAPH_HEML, "<", $call_graph_html) or die "can not open $call_graph_html";


	if( $html_id ne "ABABABAB" )
	{
		$target_seek_addr = $CALL_GRAPH_DATABASE_HASH2{$html_id} ;
		dbg_print( "target_function target_seek_addr(html_id)= $target_seek_addr\n");
	}
	else
	{
		if( exists ${$CALL_GRAPH_DATABASE_HASH{$target_function}}{$target_obj} ) {
			$target_seek_addr = ${$CALL_GRAPH_DATABASE_HASH{$target_function}}{$target_obj} ;
			dbg_print( "yes,  $target_function target_seek_addr= $target_seek_addr\n");
		}
		else {
			my @tmp = values %{$CALL_GRAPH_DATABASE_HASH{$target_function}};
			$target_seek_addr = $tmp[0];
			dbg_print( "default  $target_function target_seek_addr= $target_seek_addr\n");
		}
	}
	seek CALL_GRAPH_HEML, $target_seek_addr, 0; 



	while($_=<CALL_GRAPH_HEML>)
	{
		if( $_ =~ /\<P\>\<STRONG\>.*>$target_function\<\/STRONG\>.+, (\d+) bytes, Stack size \w+ bytes, (\w+\.o|\w+\.sym|UNDEFINED)/g )
		{

			# $1 : size
			# $2 : xxx.o or xxx.sym or UNDEFINED

			my $size = $1;
			my $obj_name = $2;
			my $section_name = $3;
			#print( "  size: $size, obj: $obj_name\n" );

			if( exists ${$FUN_HASH{$target_function}}{$obj_name} ) {
				dbg_print( "-$obj_name- return 1\n") ;
				goto STOP_PARSING;
			}

			push @CALL_TREE, "$target_function"."\=\>".$obj_name;

			# anonymous_fun_array[0] = levle
			# anonymous_fun_array[1] = function size
			# anonymous_fun_array[2] = object name
			# anonymous_fun_array[3] = size in sepcial section(.RoCodeOnBoot)?  0:not in section, >0: function size
			${$FUN_HASH{$target_function}}{$obj_name} = [ ( $parsing_level, $size, $obj_name, 0, ) ] ;
		
	
			if( $obj_name eq "UNDEFINED" || $obj_name =~ m/\w+\.sym/g  ) {
				dbg_print( "-$obj_name- return 2\n") ;
				goto STOP_PARSING;
			}
			$obj_name =~ s/\.o//g;

		
			if( $_ =~ /RoCodeOnBoot/g )
			{
				${$FUN_HASH{$target_function}}{$obj_name.".o"}->[3] = $size ;
			}
			elsif( $_ =~ /RoCodeOnBootStage2/g && $extend_function eq 1 )
			{
				${$FUN_HASH{$target_function}}{$obj_name.".o"}->[3] = $size ;
			}
			else
			{
				# anonymous_obj_array[0] = object size
				# anonymous_obj_array[1] = used size 
				# anonymous_obj_array[2] = object percentage 
				$OBJ_HASH{$obj_name} = [ ( 0, 0, 0 ) ]  if ( !exists $OBJ_HASH_EXCEPTION{$obj_name} ) ;
			}
			$DEP_OBJ_HASH{$obj_name} = 1 if ( !exists $DEP_OBJ_HASH{$obj_name} );
			

			my $find_called_by = 0;
			
			while(my $line=<CALL_GRAPH_HEML>)
			{
				if ( $line =~ /\<\/UL\>/g )
				{
					if( $find_called_by eq 1 ) {
						dbg_print( "return 3 from $target_function !\n");
						goto STOP_PARSING;
					}
					next ;
				}
				elsif ( $line =~ /\[Called By\]|\<BR\>\[Address Reference Count \:/g )
				{
					dbg_print( "return 4 from $target_function !\n");
					goto STOP_PARSING;
				}
				elsif ( $line =~ /\[Calls\]/g )
				{
					$find_called_by = 1 ;
				}
				
				if( $find_called_by eq 1 )
				{
					dbg_print ($line);
					if( $line =~ /.*\<a href\=\"\#\[(.*)\]\"\>&gt;\&gt;\<\/a\>.*/g ) {
						$html_id = $1;
					}
					else {
						print "error message: undefined function: $line\n";
						exit 1; 
					}

					$line =~ s/.*\&nbsp;\&nbsp;\&nbsp;| \(via BLX\)| \(via Veneer\)| \(Weak Reference\)|\s$//g;

					if( !exists $FUN_HASH{$line} 
						|| exists $CALL_GRAPH_DATABASE_HASH2{$html_id} )  
					{
						#
						# Get current location in file and close the file to avoid stack overflow
						#
						my $seek_addr = tell CALL_GRAPH_HEML;
						close CALL_GRAPH_HEML ;
						
						
						#
						# Depth-first search
						#
						dbg_print( "parent: -$target_function-, param: -$line-, html_id=$html_id\n") ;
						go_parsing_function($line, $obj_name, $html_id);
						dbg_print( "restore from -$line-\n") ;
						
						
						#
						# reopen the file and seek to the location
						#
						open( CALL_GRAPH_HEML, "<", $call_graph_html) or die "can not open $call_graph_html";
						seek CALL_GRAPH_HEML, $seek_addr, 0; 
					}
				}
			}
		}
	}


	print  $target_function. " should not happed !!!!!\n";


STOP_PARSING:

	$parsing_level--;
	close CALL_GRAPH_HEML;

}





#
# 4. parsing link.info to get function size and binary size 
#
sub parsing_link_info
{
	my $line;	


	open( LINK_INFO, "<", $link_info  ) or die "can not open $link_info";


	while( <LINK_INFO> )
	{
		last if (/Memory Map of the image/g); 
	}

	#
	# get the corresponding lib name according to oibject file name
	#
	while( $line=<LINK_INFO> )
	{

		last if ( $line =~ /Image component sizes/g);

		#pattern:
		#    0x0009c474   0x0000000e   Code   RO         8435    .rom_cmpr           drv_timer.o(timer.lib)
		#    0x0009ecd0   0x00000004   Code   RO       119986    .text               use_no_semi.o(c_t__un.l)


		if( $line =~ /\s+0x\w+\s+0x\w+\s+Code   RO\s+\d+\s+.*\s+(\w+)\.o\((\w+)(\.lib|\.l)\)/g )
		{
			# $1: obj name
			# $2: lib name
			#print $line. "  ". $1. " \n";
			if( exists $OBJ_HASH{$1} )
			{
				#print $1."  ".$2." ".$OBJ_HASH{$1}."\n";
				$LIB_HASH{$2} = 0 ;
				
				#
				# generate a link back to lib
				#
				$OBJ_TO_LIB_HASH{$1} = $2;
			}
		}
	}
	
	
	#
	# get the RO size of each object
	# 
	while( $line=<LINK_INFO> )
	{

		last if ( $line =~ /Debug   Library Name/g);

		#pattern:
		#     8808        428          0          0          0      61140   ABL_Aud.o
		#     4332        252          0          0          0      29324   ABL_Cam.o
		if( $line =~ /(\d+)\s+(\d+)\s+\d+\s+\d+\s+\d+\s+\d+\s+(\w+)\.o/g )
		{
			# $1 : text size
			# $2 : ro date size
			# $3 : object name
			#print $1. "  ". $2." ".$3."\n";
			if( exists $OBJ_HASH{$3} && $OBJ_HASH{$3}->[0] eq 0 )
			{
				$OBJ_HASH{$3}[0] = $1+$2 ;
			}
		}
	}


	#
	# get the RO size of each lib
	# 
	while( $line=<LINK_INFO> )
	{

		#pattern:
		#      1688         88          0          0          0       7544   3dsurround.lib
		#      8456        376         24          0          0          0   fz_t_p.l
		if( $line =~ /(\d+)\s+(\d+)\s+\d+\s+\d+\s+\d+\s+\d+\s+(\w+)(\.lib|\.l)/g )
		{
			# $1 : text size
			# $2 : ro date size
			# $3 : lib name
			#print $1. "  ". $2." ".$3."\n";
			if( exists $LIB_HASH{$3} && $LIB_HASH{$3} eq 0 )
			{
				$LIB_HASH{$3} = $1+$2 ;
			}
		}
	}

	
	close LINK_INFO;
}






#
# 5. sum up those size get from setp 4
#
sub gen_obj_list_and_report
{
	#
	# 5.1 output object list
	#
	my @obj_name_array = sort keys(%OBJ_HASH);
	my @dep_name_array = sort keys(%DEP_OBJ_HASH);
	my $size_in_obj = 0;
	for( my $i=0; $i<=$#obj_name_array; ++$i )
	{
		$size_in_obj += $OBJ_HASH{$obj_name_array[$i]}->[0];
	} 
	open( OBJ_LIST, ">".$ol) or die "Can't open Output object list: -$ol-";
	print OBJ_LIST "\n\n#\tsize_in_obj= ".$size_in_obj; 
	print OBJ_LIST "\n\nNON_CMPR_OBJ_LIST_S=\\\n", map { "\t"."$_"."\\\n"  } @obj_name_array ;
	print OBJ_LIST "\n\nNON_CMPR_OBJ_LIST= \\\n", map { "\t".$_."\\\n" } grep { -e $_ } map { "\.\/build\/$product\/out\/$_\.o " } @dep_name_array ;
	close OBJ_LIST;

	open( OBJ_LIST2, ">".$ol2."\.h") or die "Can't open Output object list: -$ol2-";
	print OBJ_LIST2 "\n\n\#define __ALL_SYS_DRV_LIB__ \\\n", map { "\t"."$_"."\#\#\.\#\#o (+RO-CODE) \\\n"  } @obj_name_array ;
	print OBJ_LIST2 map { "\t"."$_"."\#\#\.\#\#o (+RO-DATA) \\\n"  } grep{ !exists $OBJ_HASH_EXCEPTION{$_} } @dep_name_array ;

	print OBJ_LIST2 "\n\n\#define __ALL_SYS_DRV_LIB_STRING__ ", map { "\t"."$_"."\#\#\.\#\#o\(\.\#\#conststring, \.\#\#conststrlit, \.\#\#constwstring\) \\\n"  } @dep_name_array ;
	print OBJ_LIST2 "\n\n";
	close OBJ_LIST2;


	#
	# 5.2 output call tree(function list) and analysis enhancement
	#
	unlink $fl if ( -e "$fl" );
	open(OUTPUT, ">>".$fl) or die "Can't open Output function list: -$fl-";
	my $size_in_fun = 0 ;
	my $total_function =  scalar keys(%FUN_HASH)-1 ;
	my $total_function_size_in_section = 0 ;
	for(my $i=0; $i<=$#CALL_TREE; ++$i) {

		my $target_function = $CALL_TREE[$i];
		my $obj_name;

		if ( $target_function =~  m/(\w+)\=\>(\w+)/g  )
		{
			$target_function = $1;
			$obj_name = $2;
			$obj_name .= "\.o" if( $obj_name ne "UNDEFINED" ) ;
				
		}

		my $parsing_level   = ${$FUN_HASH{$target_function}}{$obj_name}[0];
		my $function_size   = ${$FUN_HASH{$target_function}}{$obj_name}[1];
		my $function_size_in_section = ${$FUN_HASH{$target_function}}{$obj_name}[3];
		
		for(my $j=0; $j<$parsing_level; $j++ ){	print OUTPUT "  ";	}
		
		print OUTPUT "$parsing_level :  $target_function \($function_size\) ";
		print OUTPUT "                            $obj_name " ;
		
		if( $function_size_in_section ne 0 ) { print OUTPUT "\n"; }
		else{ print OUTPUT "\*\n"; }

		
		$obj_name =~  s/\.o//g  ;
		$size_in_fun += $function_size;
		$OBJ_HASH{$obj_name}[1] += $function_size ;
		push @{$OBJ_HASH{$obj_name}}, $target_function;  
		$total_function_size_in_section += $function_size_in_section if ( $function_size_in_section ne 0 );

	}

	print "\n\n\ttotal $total_function functions\n";
	print "\tsize_in_fun= ".$size_in_fun."\n";
	print "\ttotal function size in section ", $total_function_size_in_section, "\n";
	print "\tsize_in_obj= $size_in_obj\n\n\n";

	print OUTPUT "\n\n\ttotal ". $total_function . " functions\n";
	print OUTPUT "\tsize_in_fun= ".$size_in_fun."\n";
	print OUTPUT "\ttotal function size in section ", $total_function_size_in_section, "\n";
	print OUTPUT "\tsize_in_obj= ".$size_in_obj."\n\n\n";

	
	my $percentage_threshold = 60;
	my $size_threshold = 128;
	
	print OUTPUT " ------------------> size threshold: $size_threshold <-----------------------\n\n";
	for( my $i=0; $i<=$#obj_name_array; ++$i )
	{
		my $obj_name      = $obj_name_array[$i];
		my $obj_size_real = $OBJ_HASH{$obj_name}->[0] ;
		my $obj_size_used = $OBJ_HASH{$obj_name}->[1] ;
		my $obj_percentage= $OBJ_HASH{$obj_name}->[2] = $OBJ_HASH{$obj_name}->[1]/$OBJ_HASH{$obj_name}->[0];
		my $diff_size = $obj_size_real - $obj_size_used;

		$obj_percentage = ceil($obj_percentage*1000)/10 ;
		
		#if( ($obj_percentage < $percentage_threshold && $obj_percentage ne 0 ) ||  $diff_size > $size_threshold )
		if( $diff_size > $size_threshold )
		{
			print OUTPUT "$obj_name\.o\n";
			print OUTPUT "  size=$obj_size_real \tused_size=$obj_size_used \t";
			print OUTPUT "percentage=$obj_percentage% \tdiff_size=$diff_size\n";
			for( my $j=3; $j<=$#{$OBJ_HASH{$obj_name}}; $j++ ){
				my $target_function = $OBJ_HASH{$obj_name}->[$j];
				my $tmp_obj_name = $obj_name.".o";

				print OUTPUT "   $target_function  \(${$FUN_HASH{$target_function}}{$tmp_obj_name}->[1]\) ";

				if( ${$FUN_HASH{$target_function}}{$tmp_obj_name}->[3] ne 0 ) { print OUTPUT "\n"; }
				else{ print OUTPUT "\*\n"; }

			}
			print OUTPUT "\n\n";
		}
	} 

	close OUTPUT;



	#
	# 5.3 output lib list
	#
	if( exists $opts{a} )
	{
		open( LIB_LIST, ">".$ll) or die "Can't open Output lib list: -$ll-";
		my $size_in_lib = 0 ;
		while ((my $key, my $value) = each (%LIB_HASH))
		{
			$size_in_lib += $LIB_HASH{$key};
			print  LIB_LIST $key."\t\t";
			#print  LIB_LIST $key."\.lib\n";
		}
		print LIB_LIST "\n\tsize_in_lib= ".$size_in_lib."\n\n";
		print "\tsize_in_lib= ".$size_in_lib."\n\n";
		close LIB_LIST;
	}



	#
	# 5.4 output lib list
	#
	if( $reportFile ne 0 )
	{
		open( DLCHKLOG, ">>".$reportFile ) or die "Can't open report file -$reportFile-";

		print DLCHKLOG "\n\n\n========================================\n";
		if( $extend_function eq 0 ) 
		{
			 print DLCHKLOG " __EXTRACT_BOOT_IMAGE__ report\n" ;
		}
		else
		{
			 print DLCHKLOG " __COMPRESS_SELECTED_BIN__ report\n" ;
		}
		print DLCHKLOG "========================================\n\n";
		print DLCHKLOG "\ttotal $#CALL_TREE functions\n";
		print DLCHKLOG "\ttotal $#obj_name_array object files\n"; 
		print DLCHKLOG "\tsize_in_fun= ".$size_in_fun."\n";
		print DLCHKLOG "\tsize_in_obj= ".$size_in_obj."\n";
		print DLCHKLOG "\n\tplease see list_fun\.mak and list_obj\.mak to check the function and object files list\n";

		if( $extend_function ne 0 ) 
		{
			my $temp_size ;
			
			$temp_size = -s "./build/$product/out/CmprBin\_Cmpr/SelectBin/SELECTED\_BIN";
			print DLCHKLOG "\n\tSelected bin pool size $temp_size\n" ;
			
			$temp_size = -s "./build/$product/out/CmprBin\_Cmpr/SelectBin/CompressedBin";
			print DLCHKLOG "\tSelected bin size $temp_size\n" ;
			
			$temp_size = -s "./build/$product/out/CmprBin\_Cmpr/SelectBin/CompressedBin\_bin";
			print DLCHKLOG "\tCompressed bin size $temp_size\n" ;
		}
		
		close DLCHKLOG;
	}



}




#
# 6. check if there is critical path and size checking
#
sub check_constraint
{
	my $total_function = 0 ;
	my $size_in_obj = 0 ;
	my $line ;


	open(FL, "<".$fl) or die "Can't open Output function list: -$fl-";
	

	while( $line =<FL> )
	{
		if( $line=~ m/total (\d+) functions/ )
		{
			$total_function = $1;
		}
		elsif( $line =~ m/size_in_obj= (\d+)/ )
		{
			$size_in_obj = $1; 
		}

		last if ( 0 ne $total_function && 0 ne $size_in_obj );
	}

	if( $total_function eq 0 || $size_in_obj eq 0 )
	{
		print "total_function=$total_function, size_in_obj=$size_in_obj\n";
		exit 1;
	}

	if( $total_function > $max_number_of_function || $size_in_obj > eval( $max_size_of_object*1024 ) )  
 	{
		print "\nerror message: size limition:  $max_size_of_object KB \n";
		print "error message: number of function limition:  $max_number_of_function \n";
		print "error message: there is critical path, please check $fl to remove it !!!\n\n";
		unlink $ol if ( -e "$ol" );
		exit 1 ;
	}
	close FL;
}





sub dbg_print 
{
	if ( $Verbose >= -1 && $parsing_level > $Verbose ) { printf shift; }
}








#
#  code start from here !!!
#
main();

sub main
{
	#print "v=", $Verbose,"\n";
	
	#
	# 1.  set function list, exception function list, exception object list 
	#
	set_extend_and_exception_list();

	#
	# 2. parsing call graph to record the location of each function  (for speedup) 
	#
	call_graph_database();

	#
	# 3. start parsgin call tree recursively by using DFS
	#
	parsing_call_graph();

	#
	# 4. parsing link.info to get function size and binary size 
	#
	parsing_link_info();

	#
	# 5. sum up those size get from setp 4
	#
	gen_obj_list_and_report();

	if( $testify eq 1 )
	{
		#
		# 6. check if there is critical path and size checking
		#
		check_constraint();
	}
}


