#!/usr/bin/perl

use strict;
use Getopt::Std;

my $Verbose=0;
my $Product=0;
my $Input=0;
my $Output=0;
my $Mode=0;
my $line;
my %opts;
my %ADD_FILE_HASH;		# input CL file, for step 1
my %DEL_FILE_HASH;		# input CL file, for step 1
my %MOD_FILE_HASH;		# input CL file, for step 1
my @tpp;				# tpp file list, for step 2, 3
my %LIB_HASH;			# matched lib file list, for step 3, 4



# step 0 : take_parameter
take_parameter();

# step 1 : take all file and push to hash : FILE_HASH
take_all_file();

# step 2 : take all tpp file
find_all_tpp();

# step 3 : parsing all tpp file and find AND set, and print to output
check_for_AND();

# step 4 : output file to $output
output_file();

# final step : exit
exit 0 ;



#
#
#
sub take_parameter()
{
	getopts("h:p:i:o:m:v:",\%opts);
	
	if (exists $opts{h}) {PrintHelp(); exit 1; }
	if (exists $opts{p}) {$Product=$opts{p};}     else{print"\n No product is specified!\n\n";PrintHelp(); exit 1; }
	if (exists $opts{i}) {$Input=$opts{i};}     else{print"\n No input file is specified!\n\n";PrintHelp(); exit 1; }
	if (exists $opts{o}) {$Output=$opts{o};}	else{print"\n No output file is specified!!\n\n";PrintHelp(); exit 1; }
	if (exists $opts{m}) {$Mode=$opts{m};}		else{print"\n No mode file is specified!!\n\n";PrintHelp(); exit 1; }
	if (exists $opts{v}) {$Verbose=$opts{v};}

	print "\n\tProduct=$Product\n";
	print "\tInput=$Input\n";
	print "\tOutput=$Output\n";
	print "\tVerbose=$Verbose\n";
	print "\tMode=$Mode\n\n";
	
	if( $Product eq "" | $Input eq "" | $Output eq "" | $Mode eq "" | ( $Mode ne "H" & $Mode ne "D" ) ){
		PrintHelp(); 
		exit 1; 
	}
}

#
# parsing $Input, transfer format, and dump to $output
#
sub take_all_file()
{
	my $flag = 0 ;
	my $suffix = 0 ;
	
	if($Input eq "") {print"\n No lint cl file is specified!!\n\n";PrintHelp(); exit 1; }
	system("dos2unix.exe $Input");
	open(PATCH_FILE, "< $Input") or die "cannot read \"$Input\" file\n";
	while ($line=<PATCH_FILE>)
	{
		$line =~ s/\n//g;
		
		next if($line=~m/^\s*$/); 
		next if($line!~m/^.*sc/);
		
		#$line =~ s#\\#\/#g;
		$line =~ m/(\w)\s(.*)/;
		$flag = $1 ;
		$suffix = get_suffix($line);
		
		if( $suffix =~ m/png|gif|jpg|bmp|xml|ini|mp3|e2p|lib|bat|bin|sym|jar|val|bak|ttf|wav|wt|dat|ldi|rom|def/i )
		{
			# those file would not effect lib generation
			next;
		}
		elsif( $suffix =~ m/h|ho|hi|hc|hv|hm|hp|ht|hpp|i|c|cpp|asm|txt|rs|info/i )
		{
			# those file would effect lib generation
		}
		elsif( $line =~ m/(options_.*\.mak)|(common_option\.mak)/i )
		{
			if( $Mode eq "H" )
			{
				print "there is options file: $line changed, please build all module\t" ;
				exit 1 ;
			}
		}
		elsif( $suffix =~ m/mak/i )
		{
			# in 'sc' folder but not in 'customer' folder
			if( ($line =~ m/\/sc\//i) && ($line !~ m/\/customer\//i) )
			{
					print "--find module make: ".get_basename($line)."--\n";
					$LIB_HASH{get_basename($line)} = 1 ;
			}
			next;
		}
		else
		{
			if( $Mode eq "H" )
			{
				print "undefined suffix: ",$suffix,", ".$line."\t" ;
				exit 1 ;
			}
		}
		
		if( $flag eq "A"){
			# Add file
			$ADD_FILE_HASH{get_notdir($line)}=1;
		}elsif ($flag eq "D"){
			# Delete file
			$DEL_FILE_HASH{get_notdir($line)}=1;
		}elsif ($flag eq "M"){
			# Modify file
			$MOD_FILE_HASH{get_notdir($line)}=1;
		}else{
			print $line,"\n" ;
			print "unknow flag $flag\n";
			exit 1 ;
		}
	}; # end of while
	close PATCH_FILE;
}



#
# find all tpp file
#
sub find_all_tpp()
{
	my $dir = "\.\/build\/$Product\/out\/";
	opendir PRD, $dir or die "cannot access out folder in \"", $dir, "\"\n";
	for my $file (sort(readdir(PRD)))
	{
		if ( $file =~ m/tpp/ && $file !~ m/tpp2/)
		{
			push @tpp, $file;
		}
	}
	closedir PRD;
}
	


#
# parsing all tpp file and find AND set
#
sub check_for_AND
{
	for my $tpp_file (@tpp)
	{
		dbg_print( "$tpp_file\n");
		
		
		if (exists $LIB_HASH{get_basename($tpp_file)})
		{
			print "\t\--".get_basename($tpp_file)." is modified!--\n";
			next;
		}
		
		open(TPP, "< \.\/build\/$Product\/out\/$tpp_file") or die "$0: cannot tpp file: \"$tpp_file\"\n";
		
		my $start_parsing = 0 ;
		
		while (chomp($line=<TPP>) && $start_parsing != -1)
		{
			if ( $start_parsing == 0 && $line =~ m/DEPENDS/)
			{
				$start_parsing=1;
				next;
			}
			elsif( $start_parsing == 1)
			{
			
	if(0){
				# search ADD_FILE_HASH
				while (my ($key, $value) = each (%ADD_FILE_HASH)){
					if ($line =~ /$key/){
						dbg_print( "\t\t$key MATCH $tpp_file: !\n" );
						# delete non-header file to speedup match process
						if( $key =~ m/(\.c)|(\.cpp)|(\.asm)|(\.S)|/ ){
							delete $ADD_FILE_HASH{"key"};
						}
						$start_parsing = -1 ;
						#last;
					}
				}
	}
				
				# search DEL_FILE_HASH
				while (my ($key, $value) = each (%DEL_FILE_HASH)){
					$key =~ s#\.#\\\.#;
					if ($line =~ /\/$key/){
						dbg_print( "\t\t$key MATCH $tpp_file: !\n" );
						# delete non-header file to speedup match process
						if( $key =~ m/(\.c)|(\.cpp)|(\.asm)|(\.S)|/ ){
							delete $DEL_FILE_HASH{"key"};
						}
						$start_parsing = -1 ;
						#last;
					}
				}
				
				# search MOD_FILE_HASH
				while (my ($key, $value) = each (%MOD_FILE_HASH)){
					$key =~ s#\.#\\\.#;
					if ($line =~ /\/$key/){
						dbg_print( "\t\t$key MATCH $tpp_file: !\n" );
						# delete non-header file to speedup match process
						if( $key =~ m/(\.c)|(\.cpp)|(\.asm)|(\.S)|/ ){
							delete $MOD_FILE_HASH{"key"};
						}
						$start_parsing = -1 ;
						#last;
					}
				}
				
				if( $start_parsing == -1 )
				{
					$LIB_HASH{get_basename($tpp_file)} = 1 ;
				}
			
				# there is no file after this line and we still can not find a AND with the CL file
				if ( $line !~ m/\\/ )
				{
					$start_parsing = -1 ;
				}
			}
		}
	}
	close TPP;
	
	return 0 ;
}



#
# output LIB_LIST to $output
#
sub output_file()
{
	if($Output eq "") {print"\n No output file is specified!!\n\n";PrintHelp(); exit 1; }
	open(OUTPUT, "> $Output") or die "cannot read \"$Output\" file\n";
	open(OUTTPP, "> TPPLIST") or die "cannot read \"$Output\" file\n";
	print "\nALL UPDATE LIST:\n" ;
	print OUTPUT "AND_MODULE_LIST=";
	for my $key( sort keys %LIB_HASH)
	{
		print "\t", $key, "\n";
		print OUTPUT "\\\n\t$key";
		print OUTTPP "\.\/build\/","8536n_1g_256_mb303gm","\/out\/$key\.tpp\n";
	}
	system("dos2unix.exe $Output");	
	close OUTPUT ;
}


#h:p:i:o:v:m
#
# user guide
#
sub PrintHelp {
    print <<"EOF";
Usage:$0 [-h] [-p prodcut name] [-i input file list] [-o output file] [-m mode] [-v verbose mode]
    -h: help, show this user guide
    -p: product name, specify the prodcut name
    -i: input file, specify the input file which contains the file in testing CL
    -o: output file, specify the output file for module to update
    -m: mode, for a "hot fix patch"(H)/"dependency check"(D)/big patch(B) (not support yet)
    -v: verbose mode, print debug messages, e.g. -v2
EOF
exit 0;
}



#
# get_dir : /proj/sc/system/sys/sys.mak  --> /proj/sc/system/sys/
#
sub get_dir
{
	my $dir = shift ;
	$dir =~ s#\/[^\/]*$##;
	#print "--",$dir."--\n";
	return $dir
}


#
# get_notdir:  /proj/sc/system/sys/sys.mak  --> sys.mak
#
sub get_notdir
{
	my $notdir = shift ;
	$notdir =~ s/(.*\/)//g;
	#print "--",$notdir."--\n";
	return $notdir
}

#
# get_suffix:  /proj/sc/system/sys/sys.mak  --> mak
#
sub get_suffix
{
	my $suffix = shift ;
	$suffix =~ s/(.*\/)|(.*\.)//g;
	#print "--",$suffix."--\n";
	return $suffix
}


#
#sub get_basename:  /proj/sc/system/sys/sys.mak  --> sys
#
sub get_basename
{
	my $basename = shift ;
	$basename =~ s/(.*\/)|(\..*)//g;
	#print "--",$basename."--\n";
	return $basename

}

#
# debug print
#
sub dbg_print {
  if ($Verbose >= 2) { printf shift; }
}