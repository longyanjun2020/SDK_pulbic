#!/usr/bin/perl

#use warnings;
use strict;
use Fcntl;
use File::Basename;

my $LINTLNTLOG_DIR = "LINTLOG";
my $outdir = "./$LINTLNTLOG_DIR";
my $owner_file = "./tng/Lint_Owner.txt";
my %mustfixlist;
my %mustfixlistcount;
my %topsort;
my %topsort_link;
my $topsortnumber=10;
my %modulelist_owner;
my $Lib_Owner;
my $print_Lib_Owner=0;

$mustfixlist{'Warning 644'}= 'Variable "xxx" may not have been initialized';
$mustfixlist{'Warning 548'}= 'else expected';
$mustfixlist{'Warning 509'}= 'extern used with definition';
$mustfixlist{'Warning 545'}= 'Suspicious use of &';
$mustfixlist{'Warning 578'}= 'Declaration of symbol "var_xxx" hides symbol "var_xxx"';  
$mustfixlist{'Warning 530'}= 'Symbol not initialized'; 
$mustfixlist{'Warning 419'}= 'Apparent data overrun for function "func_xxx", argument "Integer" exceeds argument "Integer"';
$mustfixlist{'Warning 420'}= 'Apparent access beyond array for function "func_xxx", argument "Integer" exceeds "Integer Reference"';

$mustfixlist{'Warning 401'}= 'Symbol not previously declared static';
$mustfixlist{'Warning 414'}= 'Possible division by 0';
#$mustfixlist{'Warning 415'}= 'Access of out-of-bounds pointer (beyond end of data) by operator';
#$mustfixlist{'Warning 416'}= 'Creation of out-of-bounds pointer (beyond end of data) by operator';
$mustfixlist{'Warning 418'}= 'Passing null pointer to function Symbol';
$mustfixlist{'Warning 428'}= 'Negative subscript (Integer) in operator';
$mustfixlist{'Warning 436'}= 'Preprocessor directive in invocation of macro';
$mustfixlist{'Warning 501'}= 'Expected signed type';
$mustfixlist{'Warning 504'}= 'Unusual shift value';
$mustfixlist{'Warning 514'}= 'Unusual use of a Boolean';
$mustfixlist{'Warning 522'}= 'Expected void type, assignment, increment or decrement';
$mustfixlist{'Warning 524'}= 'Loss of precision';
$mustfixlist{'Warning 527'}= 'Unreachable';
$mustfixlist{'Warning 528'}= 'Symbol not referenced';
$mustfixlist{'Warning 529'}= 'Symbol not subsequently referenced';
$mustfixlist{'Warning 533'}= 'Function should (not) return a value';
#$mustfixlist{'Warning 546'}= 'Suspicious use of &';
$mustfixlist{'Warning 550'}= 'Symbol not accessed';
$mustfixlist{'Warning 551'}= 'Symbol not accessed';
$mustfixlist{'Warning 564'}= 'Variable depends on order of evaluation';
$mustfixlist{'Warning 568'}= 'Nonnegative quantity is never less than zero';
#$mustfixlist{'Warning 569'}= 'Loss of information';
$mustfixlist{'Warning 570'}= 'Loss of sign';
$mustfixlist{'Warning 573'}= 'Signed-unsigned mix with divide';
$mustfixlist{'Warning 605'}= 'Increase in pointer capability';
$mustfixlist{'Warning 618'}= 'Storage class specified after a type';
#$mustfixlist{'Warning 620'}= 'Suspicious constant (L or one?)';
$mustfixlist{'Warning 645'}= 'Symbol may not have been initialized';
$mustfixlist{'Warning 652'}= 'Define of symbol declared previously';
$mustfixlist{'Warning 659'}= 'Nothing follows on line within struct/union/enum declaration';
#$mustfixlist{'Warning 661'}= 'Possible access of out-of-bounds pointer';
#$mustfixlist{'Warning 662'}= 'Possible creation of out-of-bounds pointer';
#$mustfixlist{'Warning 665'}= 'Unparenthesized parameter';
$mustfixlist{'Warning 666'}= 'Expression with side effects passed to repeated parameter';
$mustfixlist{'Warning 668'}= 'Possibly passing a null pointer to function';
$mustfixlist{'Warning 669'}= 'Possible data overrun for functions';
$mustfixlist{'Warning 670'}= 'Possible access beyond array for function';
$mustfixlist{'Warning 676'}= 'Possibly negative subscript';
$mustfixlist{'Warning 682'}= 'Sizeof applied to a parameter whose type is a sized array';
$mustfixlist{'Warning 683'}= 'Function defined';

my @keyMsg = keys %mustfixlist;
                  
##################################################################
sub sort_by_count($a,$b)
{	
	if ($topsort{$a}>=$topsort{$b})
	{
		return -1;
	}
	
	return 1;
}

sub trim($)
{
	my $string = shift;
	$string =~ s/^\s+//;
	$string =~ s/\s+$//;
	return $string;
}

# Left trim function to remove leading whitespace
sub ltrim($)
{
	my $string = shift;
	$string =~ s/^\s+//;
	return $string;
}

# Right trim function to remove trailing whitespace
sub rtrim($)
{
	my $string = shift;
	$string =~ s/\s+$//;
	return $string;
}

sub get_lint_lib_owner
{
    my $in_lib_name  = $_[0];
    my $out_lib_owner="";    
    my $key;
    my $value;
 
    if (defined($modulelist_owner{$in_lib_name}))
    {
   	$out_lib_owner = $modulelist_owner{$in_lib_name};
    }            	
   return $out_lib_owner;
}

sub load_owner
{
	my $str_read_line;
	my @list;

	print OUTLINTLOG "load owner\n";
	open owner_file, "<$owner_file" or die "can not open file $owner_file\n";
	while(defined($str_read_line = <owner_file>))
	{
		@list=split("=",$str_read_line);
   		if ((@list[0]) && (@list[1]))
   		{
  			$modulelist_owner{trim(@list[0])} = trim(@list[1]);
   		}
	}
	close (owner_file);
}

if (-e $owner_file)
{
	#owner file exist, read owner file 
	$print_Lib_Owner =1;
	load_owner();
}

#######################################################################

# Enum outdir


my $outIndexHTML ="";
my $outLibHTML ="";
my $outDirName;
my $strLintLogFilename;
my $strreadline;		
my @SepStr;
my @param;
my @reportHTMLHead = ('<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">',
'<html>',
'<head>',
'  <meta http-equiv="content-type" content="text/html; charset=UTF-8" />',
'  <style type="text/css">',
'  body, th { font-family:tahoma, verdana, arial, helvetica, sans; font-weight:normal; font-size:9pt; }',
'body { margin:0; background-color:#DDF; padding:10px; }',
'p { margin:0 }',
'a { text-decoration:none;  background-color:Transparent; color:#05F; }',
'a:visited { color:#55F; }',
'a:hover { background-color:#EEF; }',
'img { border-style:none }',
'td { font-size:10pt; background:#FFF; border:1px solid #BBF }',
'td img { vertical-align:top }',
'th, th a, th a:visited { color:#555; font-size:13pt; font-weight:bold; padding-bottom:0; }',
'#foldercomment { font-size:10pt; color:#888; background:#EEE; padding:3px; border:1px solid #DDD; border-bottom:3px solid #DDD; margin-top:2px; }',
'#tools { text-align:right; font-size: 8pt; }',
'#folder, .big { font-size:14pt; font-weight:bold;  }',
'#folderlabel, #folderstats, #footer { font-size: 8pt; }',
'#body {',
'  border-bottom: 4px solid #BBF;',
'     border-top: 4px solid #BBF;',
'    border-left: 1px dotted #BBF;',
'   border-right: 1px dotted #BBF;',
'  background:#F3F3FF;',
'  padding:15px;',
'  margin:15px;',
'}',
'.comment { font-size:7pt; color:#888; background:#EEE; padding:3px; border:1px solid #DDD; margin-top:2px; }',
'.button { float:right; padding:5px; padding-top:7px; margin:15px; border:2px solid black; background:white; font-size:8pt; font-weight:bold; }',
'.button img { vertical-align:text-bottom; }',
'.flag { font-weight:bold; font-size:8pt; background:white; color:red; text-align:center; border:1px solid red; }',
'  </style>',  
'<title>Lint Report /</title>',
'</head>',
'<body>',
'',
'<div id=folder>Lint Report</div>',
);

my @reportHTMLTail = (
'</div>',
'',
'</body>',
'',
'</html>'
);

my @reportTableHead_without_Owner = ('<div id=body>',
'	<table cellpadding=5>',
'<th>Project</th>',
'		<th>Error Count</th>',
'		<th>Warning Count</th>',
'		<th>Critical Count</th>');

my @reportTableHead_with_Owner = ('<div id=body>',
'	<table cellpadding=5>',
'<th>Project</th>',
'		<th>Error Count</th>',
'		<th>Warning Count</th>',
'		<th>Critical Count</th>',
'		<th>Owner</th>');

my @reportTableTail = ('	</table>',
'	</div>');

my @reportTableLibHead = ('<div id=body>',
'	<table cellpadding=4>',
'<th>File</th>',
'		<th>Error Count</th>',
'		<th>Warning Count</th>',
'		<th>Critical Count</th>');

my @reportMustTopTableHead = ('<div id=body>',
"<div id=folder>Top $topsortnumber Files</div>",
'	<table cellpadding=3>',
'<th>File</th>',
'		<th>Critical Error Count</th>');

my @reportMustFixTableHead = ('<div id=body>',
'<div id=folder>Must Fix Errors or Warnings</div>',
'	<table cellpadding=4>',
'<th>MsgID</th>',
'		<th>Error Count</th>',
'		<th>Msg description</th>');

my $nTotalCriticalCount=0;
my $nTotalErrCount=0;
my $nTotalWarncount=0;
my $strTableContent = "";
my $tmp;
my $strTableMustFixContent = "";
$outIndexHTML = "$outdir/index.html";
unlink $outIndexHTML;

opendir OUTDIR, $outdir or die "can not open dir $outdir";

open (OUTMAINHTML, "> $outIndexHTML") or die "cannot write \"$outIndexHTML\" file\n";
open (OUTLINTLOG, "> lint_summary.log") or die "cannot write \"lint_summary.log\" file\n";
$tmp = localtime;
print OUTLINTLOG "**************Lint Summary Report $tmp************\r\n\r\n";
#print index.html head

foreach $tmp (@reportHTMLHead)
{
	print OUTMAINHTML "$tmp\n";
}

foreach $outDirName (readdir OUTDIR)
{
	chomp($outDirName);
	my $nLibErrCount=0;
	my $nLibWarncount=0;
	my $nFileErrCount=0;
	my $nFileWarncount=0;	
	my $nLibCriticalCount=0;
	my $strFile="";
	my $strLib="";
	my %mustfixlistcountlocal;
	if (( $outDirName ne ".") && ($outDirName ne "..") &&($outDirName ne "index.html") )
	{
		my $strLibUrl = "./$outDirName/$outDirName.html";
		my $strLibTableContent = "";				
		my $nFileCriticalCount=0;
		$nLibCriticalCount=0;
		$strLib = $outDirName;
		$outLibHTML = "$outdir/$outDirName/$outDirName.html";
		$strLintLogFilename = "$outdir/$outDirName/$outDirName.total.log";
		#print "Dir: $outDirName Log=$strLintLogFilename\n";
				
		open(H_LINTLOGFILE, "< $strLintLogFilename");
		open(OUTLIBHTML, "> $outLibHTML");
				
		# write library html head
		foreach $tmp (@reportHTMLHead)
		{
			print OUTLIBHTML "$tmp\n";
		}

		while(defined($strreadline = <H_LINTLOGFILE>))
		{
			chomp($strreadline);
			if ($strreadline ne "")
			{
				if ($strreadline =~ /--- Module/i)
				{										
					if ($strFile ne "")
					{
						my $varFilename = substr ( $strFile,rindex($strFile, "\\" )+1,255);
						#print "\"$strFile\" => Err($nFileErrCount) ,Warning($nFileWarncount)\n";												
						$strLibTableContent  =  $strLibTableContent."<tr><td> <a href=\"./$varFilename.log\">$strFile</a> <td align=right>$nFileErrCount  <td align=right>$nFileWarncount<td align=right>$nFileCriticalCount\n";	
						
						$topsort{$strFile} =$nFileCriticalCount ;
						$topsort_link{$strFile} ="./$strLib/$varFilename.log" ;
					}										
					
					$nFileErrCount=0;
					$nFileWarncount=0;
					$nFileCriticalCount=0;					
					$strreadline = substr($strreadline,14);
					trim($strreadline);					
					$strFile =  substr ( $strreadline,0, rindex($strreadline, "(" ) -1);
					trim($strFile);										
				}
				else
				{
					@param = split /\s:\s/ ,$strreadline;
					#Search each module.
					if (  defined(@param[1])  &&
					      ( @param[1] =~ /Warning/i ||  @param[1] =~ /Error/i   )
					    )
					{
	#					print "@param[0]\n";
						my $localtmp;												
						$localtmp =@param[1];
						trim($localtmp);	
						if (@param[1] =~ /Error/i)
						{
							$nFileErrCount++;
							$nLibErrCount++;
							$nTotalErrCount++;							
						}
						elsif(@param[1] =~ /Warning/i)
						{
							$nFileWarncount++;
							$nLibWarncount++;
							$nTotalWarncount++;							
						}
						
						#count must fix error warning count.
						if ( defined($mustfixlist{$localtmp}) )
						{
							{
								my $localcount = 0;
								if (defined($mustfixlistcount{$localtmp})){$localcount=$mustfixlistcount{$localtmp};}
								$localcount++;
								$mustfixlistcount{$localtmp}  =$localcount ;								
#								print "\"$localtmp\" count $mustfixlistcount{$tmp}\r\n";
							}
							
							{
								my $localcount = 0;
								if (defined($mustfixlistcountlocal{$localtmp})){$localcount=$mustfixlistcountlocal{$localtmp};}
								$localcount++;
								$mustfixlistcountlocal{$localtmp}  =$localcount ;								
#								print "\"$localtmp\" count $mustfixlistcountlocal{$tmp}\r\n";
							}
							$nFileCriticalCount++;
							$nLibCriticalCount++;
							$nTotalCriticalCount++;
						}
						else
						{
							
						}
					}
				}				
			}
		}		

#########################################################################		
		#dump last file 
		{
				my $varFilename = substr ( $strFile,rindex($strFile, "\\" )+1,255);
				#print "\"$strFile\" => Err($nFileErrCount) ,Warning($nFileWarncount)\n";						
						
				$strLibTableContent  =  $strLibTableContent."<tr><td> <a href=\"./$varFilename.log\">$strFile</a> <td align=right>$nFileErrCount<td align=right>$nFileWarncount<td align=right>$nFileCriticalCount\n";			
		}
		
		if($print_Lib_Owner)
		{
			#add lib owner
			$Lib_Owner = get_lint_lib_owner($strLib);
			my $strLibLog = sprintf "Lib \%15s\: Error=%6d, Warning=%6d, Owner=\%15s" , $strLib,$nLibErrCount,$nLibWarncount,$Lib_Owner;

			$strTableContent  =  $strTableContent."<tr><td> <a href=\"$strLibUrl\">$strLib</a> <td align=right>$nLibErrCount  <td align=right>$nLibWarncount<td align=right>$nLibCriticalCount<td align=right>$Lib_Owner\n";
		}
		else
		{
			my $strLibLog = sprintf "Lib \%15s\: Error=%6d, Warning=%6d" , $strLib,$nLibErrCount,$nLibWarncount;
			#print "Library \"$strLib\": Error Count:$nLibErrCount , Warning count:$nLibWarncount\n";
			print OUTLINTLOG "$strLibLog\r\n";
				
			$strTableContent  =  $strTableContent."<tr><td> <a href=\"$strLibUrl\">$strLib</a> <td align=right>$nLibErrCount  <td align=right>$nLibWarncount<td align=right>$nLibCriticalCount\n";
		}

		# write library html content
		print OUTLIBHTML "<div id=folder>Library $strLib summary: Error=$nLibErrCount , Warning=$nLibWarncount (Is critical:$nLibCriticalCount)</div>\n";
		$tmp = localtime;
		print OUTLIBHTML "<div id=folderlabel>$tmp</div>\n";
		
		#dump must fix msg local		
		# dump must fix waring error local
		$strTableMustFixContent = "";
		foreach $tmp (@keyMsg)
		{			
			my $nMsgCount = 0;
			if (defined($mustfixlistcountlocal{$tmp})){$nMsgCount=$mustfixlistcountlocal{$tmp};}
			$strTableMustFixContent  =  $strTableMustFixContent."<tr><td>$tmp<td align=right>$nMsgCount  <td align=right>$mustfixlist{$tmp}\n";	
		}
		
		foreach $tmp (@reportMustFixTableHead)
		{
			print OUTLIBHTML "$tmp\n";
		}
		print OUTLIBHTML "$strTableMustFixContent\n";
		foreach $tmp (@reportTableTail)
		{
			print OUTLIBHTML "$tmp\n";
		}
		
		#dump file warn error local		
		foreach $tmp (@reportTableLibHead)
		{
			print OUTLIBHTML "$tmp\n";
		}
		print OUTLIBHTML "$strLibTableContent\n";
		foreach $tmp (@reportTableTail)
		{
			print OUTLIBHTML "$tmp\n";
		}

		
		# dump HTML tail local
		foreach $tmp (@reportHTMLTail)
		{
			print OUTLIBHTML "$tmp\n";
		}

		
		close (OUTLIBHTML);		
		close(H_LINTLOGFILE);		
	}			
}

$strTableMustFixContent = "";
my @topsortFile = sort sort_by_count keys %topsort;
my $strTableTopNContent = "";
#TEXT summary report
my $strLibLog1 = sprintf "\%19s\: Error=%6d, Warning=%6d Critical=%6d" , "Total Summary",$nTotalErrCount,$nTotalWarncount,$nTotalCriticalCount;
print OUTLINTLOG "\r\n$strLibLog1\r\n";

# dump must fix waring error global
print OUTLINTLOG "\r\nMust Fix Error or Warning list\r\n";
foreach $tmp (@keyMsg)
{
	my $nMsgCount = 0;
	if (defined($mustfixlistcount{$tmp})){$nMsgCount=$mustfixlistcount{$tmp};}
	
	my $strLibLog2 = sprintf "\%19s\: Count=%6d, Description=\"%s\"" ,$tmp,$nMsgCount,$mustfixlist{$tmp};
	print OUTLINTLOG "$strLibLog2\r\n";
	$strTableMustFixContent  =  $strTableMustFixContent."<tr><td>$tmp<td align=right>$nMsgCount  <td align=right>$mustfixlist{$tmp}\n";	
}


#INDEX HTML report
print OUTMAINHTML "<div id=folder>Total summary: Error=$nTotalErrCount , Warning=$nTotalWarncount (Is critical=$nTotalCriticalCount)</div>\n";
$tmp = localtime;
print OUTMAINHTML "<div id=folderlabel>$tmp</div>\n";

#INDEX Top report
for (my $i=1; $i<= $topsortnumber ; $i++)
{
	my $strTopFile = $topsortFile[$i];
	if (defined($strTopFile))
	{
		$strTableTopNContent = $strTableTopNContent."<tr><td><a href=\"$topsort_link{$strTopFile}\">$strTopFile</a><td align=right>$topsort{$strTopFile}";
	}
}
foreach $tmp (@reportMustTopTableHead)
{
	print OUTMAINHTML "$tmp\n";
}
print OUTMAINHTML "$strTableTopNContent\n";
foreach $tmp (@reportTableTail)
{
	print OUTMAINHTML "$tmp\n";
}

#INDEX Critical report		
foreach $tmp (@reportMustFixTableHead)
{
	print OUTMAINHTML "$tmp\n";
}
print OUTMAINHTML "$strTableMustFixContent\n";
foreach $tmp (@reportTableTail)
{
	print OUTMAINHTML "$tmp\n";
}

#INDEX LIB report		
my @reportTableHead;
if($print_Lib_Owner)
{
	@reportTableHead=@reportTableHead_with_Owner;
}
else
{
	@reportTableHead=@reportTableHead_without_Owner;
}
foreach $tmp (@reportTableHead)
{
	print OUTMAINHTML "$tmp\n";
}
print OUTMAINHTML "$strTableContent\n";
foreach $tmp (@reportTableTail)
{
	print OUTMAINHTML "$tmp\n";
}


foreach $tmp (@reportHTMLTail)
{
	print OUTMAINHTML "$tmp\n";
}

close (OUTMAINHTML);
close (OUTDIR);
close (OUTLINTLOG);
