#!/usr/bin/perl

#####
## SYNTAX:
## perl tng/genFileList.pl FileList.xml sc $cus_platform makErrPattern.log
#####

use warnings;
use strict;

my %used;

# get output file name
my $output = shift;

# get search folder
my $search_folder = shift;

#get platform name
my $all_platform = shift;
my @platform = split(/,/, $all_platform);

#get err log file
my $logFile = shift;

my $errPatternMatch = undef;

# output results according to a makefile syntax
open(xmlFile, "> $output") or die "cannot write to \"$output\"\n";
print xmlFile "<make_info>\n";

if (!defined($logFile))
{
	$logFile = "makErrPattern.log";
}
open(LOG_FILE, "> $logFile") or die "cannot write\"$logFile\" file\n";	

my $src_pattern = "";
my $nextLineCheck = 0;
sub checkMak
{
	my $makFile = shift;
	my $line = shift;
	my $lineNum = shift;
		
	if ($line !~ /^#/)
	{
		if ($line =~ /\=/)
		{
			$src_pattern = $`;
			$src_pattern =~ s/\W//g;
			if ($line =~ /\\$/)
			{
				$nextLineCheck = 1;
			}
		}
		elsif ($line !~ /\\$/)
		{
			$nextLineCheck = 0;
		}
		
		$line =~ s/\\//g;
		if ($line =~ /\.c$|\.asm$|\.S$/)
		{
			if ($src_pattern !~ /^REL_SRC_C_LIST$|^SRC_C_LIST$|^REL_SRC_ASM_LIST$|^SRC_ASM_LIST$/ && $src_pattern ne "")
			{
				# Err pattern
				$errPatternMatch ++;
				print "Err Pattern: $src_pattern\n";
				print LOG_FILE "Error pattern in $makFile Ln$lineNum: $src_pattern\n";
			}
		}
		if ($nextLineCheck == 0)
		{
			$src_pattern = "";
		}
	}
}

sub updateMak
{
	my $file = shift;
	my $pathname = shift;
	my @make_source;
	my $foundPattern = 0;
	my $keepFlag = 0;
	my $lineNum = 0;
	
	open(SOURCES, "< $file") or die "cannot read \"$file\" file\n";
	while(my $line = <SOURCES>)
	{
		my $tmpLine = $line;
		chomp $tmpLine;
		$tmpLine =~ s/\s//ig;
		
		$lineNum ++;
		checkMak("$pathname/$file", $tmpLine, $lineNum);
		
		if ($line =~ /Ignored by mak parser except/)
		{
			my $found = 0;
			for (0 ... $#platform)
			{
				if ($line =~ /$platform[$_]/)
				{
					$found = 1;
				}
			}
			if ($found == 0)
			{
				return "";
			}
		}
		elsif ($line =~ /Ignored by mak parser/)
		{
			return "";
		}		
		elsif ($line =~ /KEEP IN RELEASE PACKAGE BEGIN/)
		{
			#Start the protection area: Keep anything from the next line without being parsed
			#NOTE: If containing the key word REL_SRC_C_LIST|SRC_C_LIST|REL_SRC_ASM_LIST|SRC_ASM_LIST
			# it will be parsed to XML list and renamed to REL_SRC_C_LIST|SRC_C_LIST|REL_SRC_ASM_LIST|SRC_ASM_LIST
			$keepFlag = 1;
		}
		elsif ($line =~ /KEEP IN RELEASE PACKAGE END/)
		{
			#Be sure using #KEEP IN RELEASE PACKAGE END at the end of the protection area
			$keepFlag = 0;
		}
		
		if ($keepFlag == 1)
		{
			push @make_source, $line;
		}
		else
		{
			if ($line =~ /#Add files here/)
			{
				push @make_source, $line;
				$foundPattern = 1;
			}
			elsif ($line =~ /#/)
			{
				push @make_source, $line;
			}
			elsif ($line =~ /REL_SRC_C_LIST|SRC_C_LIST|REL_SRC_ASM_LIST|SRC_ASM_LIST/)
			{
			}
			elsif ($line =~ /\.c|\.asm|\.S/)
			{
				if ($line =~ /\%/)
				{
					push @make_source, $line;
				}
			}
			else
			{
				push @make_source, $line;
			}
		}
	}
	
	open(MAKE_FILE, "> $file") or die "cannot write to \"$file\"\n";
	for my $line (@make_source)
	{
		print MAKE_FILE "$line";
	}
	print MAKE_FILE "\n";
	if($foundPattern == 0)
	{
		print MAKE_FILE "#Add files here\n";
	}
	close(MAKE_FILE);
}

sub parseMak
{
	my $file = shift;
	my $pathname = shift;
	my @make_source;
	my $release_type = "";
	my $line_of_make = "";
	my $source_file_name = "";	
	my $source_file_num = 0;	
	my $xml_content = "    <make>\n";
	my $foundSource = 0;
	my @contentArray;
	my @levelArray;
	my $Alevel;
	my $Acontent;
	my $markFlag = 0;
	
	#print tmpFile "processing $pathname/$file\n";
	
	open(SOURCES, "< $file") or die "cannot read \"$file\" file\n";
	while(my $line = <SOURCES>)
	{
		chomp $line;
		my $tmpLine = $line;
		$tmpLine =~ s/\s//ig;
		
		
		if ($line =~ /Ignored by mak parser except/)
		{
			my $found = 0;
			for (0 ... $#platform)
			{
				if ($line =~ /$platform[$_]/)
				{
					$found = 1;
				}
			}
			if ($found == 0)
			{
				return "";
			}
		}
		elsif ($line =~ /Ignored by mak parser/)
		{
			return "";
		}
		elsif ($tmpLine =~ /^#/)
		{
			#ignore commments
			if ($tmpLine =~ /\\$/)
			{
				$markFlag = 1;
			}
		}
		elsif ($line =~ /ifeq|ifneq|endif/)
		{
			if ($markFlag == 0)
			{
				push @make_source, $line;
			}
			elsif ($tmpLine !~ /\\$/)
			{
				$markFlag = 0;
			}
		}
		elsif ($line =~ /REL_SRC_C_LIST|SRC_C_LIST|REL_SRC_ASM_LIST|SRC_ASM_LIST|REL_SRC_CPP_LIST|SRC_CPP_LIST/)
		{
			if ($markFlag == 0)
			{
				push @make_source, split(/=/,$line);
			}
			elsif ($tmpLine !~ /\\$/)
			{
				$markFlag = 0;
			}
		}
		else
		{
			if ($markFlag == 0)
			{
				push @make_source, split(/ /,$line);
			}
			elsif ($tmpLine !~ /\\$/)
			{
				$markFlag = 0;
			}
		}
	}
	
	$xml_content = $xml_content."        <make_name>$pathname/$file</make_name>\n";
		
	# for each object name on the command line
	for $line_of_make (@make_source)
	{ 
		my @tmpContentArray;
		my @tmpLevelArray;
		
		#if ($line_of_make =~ /#/)
		#{
			#ignore commments
			#print tmpFile "$line_of_make\n";
		#}
		#elsif ($line_of_make =~ /ifeq/)
		if ($line_of_make =~ /else/)
		{
			$line_of_make =~ s/else//;
			if ($#levelArray != -1)
			{
				$Alevel = pop (@levelArray);
				if ($Alevel =~ /ifeq/)
				{
					push (@levelArray, "ifneq");
				}
				elsif ($Alevel =~ /ifneq/)
				{
					push (@levelArray, "ifeq");
				}
			}
		}
		if ($line_of_make =~ /ifeq/)
		{
			$line_of_make =~ s/ifeq//;
			$line_of_make =~ s/\x20+\(/\(/;
			$line_of_make =~ s/\x0D//g;
			push (@contentArray, $line_of_make);
			push (@levelArray, "ifeq");
		}
		if ($line_of_make =~ /ifneq/)
		{
			$line_of_make =~ s/ifneq//;
			$line_of_make =~ s/\x20+\(/\(/;
			$line_of_make =~ s/\x0D//g;
			push (@contentArray, $line_of_make);
			push (@levelArray, "ifneq");
		}
		if ($line_of_make =~ /endif/)
		{
			$Alevel = pop (@levelArray);
			$Acontent = pop (@contentArray);
		}
		elsif ($line_of_make =~ /\%\.c|\%\.asm|\%\.S/)
		{
			#ignore commments
			#print tmpFile "$line_of_make\n";
		}
		elsif ($line_of_make =~ /\.c|\.asm|\.S/)
		{
			if (length($release_type) > 0)
			{
				my $pos;
				if ($line_of_make =~ /\.c/)
				{
					$pos = index($line_of_make, ".c");
					$pos += 2;
				}
				elsif ($line_of_make =~ /\.asm/)
				{
					$pos = index($line_of_make, ".asm");
					$pos += 4;
				}
				elsif ($line_of_make =~ /\.S/)
				{
					$pos = index($line_of_make, ".S");
					$pos += 2;
				}
				$source_file_name = substr $line_of_make, 0, $pos;
				$source_file_name =~ s/\x20//g;
				$source_file_name =~ s/\x09//g;
				$xml_content = $xml_content."        <file>\n";
				$xml_content = $xml_content."            <file_name>$source_file_name</file_name>\n";
				$xml_content = $xml_content."            <default_value>$release_type</default_value>\n";
				while ($#levelArray + 1)
				{
					$Acontent = pop (@contentArray);
					$Alevel = pop (@levelArray);
					if ($Alevel =~ /ifeq/)
					{
						$xml_content = $xml_content."            <compile_option>$Acontent</compile_option>\n";
					}
					elsif ($Alevel =~ /ifneq/)
					{
						$xml_content = $xml_content."            <compile_option_2>$Acontent</compile_option_2>\n";
					}
					push (@tmpContentArray, $Acontent);
					push (@tmpLevelArray, $Alevel);
				}
				@contentArray = reverse @tmpContentArray;
				@levelArray = reverse @tmpLevelArray;
				
				$xml_content = $xml_content."        </file>\n";
				$source_file_num++;
			}
			else
			{
				#print tmpFile "$line_of_make\n";
			}
		}
		elsif ($line_of_make =~ /REL_SRC_C_LIST/)
		{
			my $pos = index($line_of_make, "REL_SRC_C_LIST");
			$pos += 14;
			$release_type = substr $line_of_make, 0, $pos;
			$release_type =~ s/\x20//g;
		}
		elsif ($line_of_make =~ /SRC_C_LIST/)
		{
			my $pos = index($line_of_make, "SRC_C_LIST");
			$pos += 10;
			$release_type = substr $line_of_make, 0, $pos;
			$release_type =~ s/\x20//g;
		}
		elsif ($line_of_make =~ /REL_SRC_ASM_LIST/)
		{
			my $pos = index($line_of_make, "REL_SRC_ASM_LIST");
			$pos += 16;
			$release_type = substr $line_of_make, 0, $pos;
			$release_type =~ s/\x20//g;
		}
		elsif ($line_of_make =~ /SRC_ASM_LIST/)
		{
			my $pos = index($line_of_make, "SRC_ASM_LIST");
			$pos += 12;
			$release_type = substr $line_of_make, 0, $pos;
			$release_type =~ s/\x20//g;
		}
		elsif ($line_of_make =~ /\=/)
		{
			$release_type = "";
			#print tmpFile "$line_of_make\n";
		}
		else
		{
			#print tmpFile "$line_of_make\n";
		}
	}
	$xml_content = $xml_content."    </make>\n";
	if ($source_file_num == 0)
	{
		$xml_content = "";
	}
	else
	{
		updateMak($file, $pathname);
	}
	return $xml_content;
}

sub find
{
	my $pathname = shift;
	my $filenum = 0;
	my @makfiles = <*.mak>;
	
	if($#makfiles >= 0)
	{
		for my $item (@makfiles)
		{
			my $xml_content = parseMak($item,$pathname);
			print xmlFile "$xml_content";
		}
	}
	
	my @dir = <*>;
	for my $path (@dir)
	{
		if (-d $path)
		{
			chdir $path;
			#if ("$pathname/$path" !~ /sc\/product/)
			#{
				print "find $pathname/$path\n";
				find("$pathname/$path");
			#}
			chdir "../";
		}
	}
}

chdir $search_folder;
find($search_folder);

my @tmpFolder = split(/\//, $search_folder);
for (0 ... $#tmpFolder)
{
	chdir "../";
}

print xmlFile "</make_info>\n";
close(xmlFile);
#close(tmpFile);

close (LOG_FILE);	
if (!defined($errPatternMatch))
{
	unlink $logFile;
}
	