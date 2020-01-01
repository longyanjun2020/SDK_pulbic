#!/usr/bin/perl
################################################################################
# genPatchLogArray.pl:
# @ Brief		used to transform patch log to C array
# @ Usage		genPatchLogArray.pl [SOURCE_FOLDER_NAME] [DESTINATION_FILE_NAME]
# @ Hint		Patch files format should be xxx.lib	
################################################################################

use warnings;
use strict;

my $DEBUG = 0;
my $patchlog_path = $ARGV[0];
my $patcharray_file = $ARGV[1];
my @patchlog_list = glob "$patchlog_path/*";
my $c_array_name = "PatchIdTable";
my @exclude_files = ("dummy");
my $base_ver = "";

sub DBG
{
	if ($DEBUG == 1)
	{
		print "@_\n";
	}
	else
	{
		return;
	}
}

sub IsExclusion
{
	my $id = shift @_;
	$id =~ s/(.*)(\/)(.*)(\.lib)/$3$4/;

	DBG("");
	for my $item (@exclude_files)
	{
		DBG("  [CMP]: ($id, $item)");
		if ($id eq $item)
		{
			return 1;
		}
	}
	return 0;
}

sub ParsePatchId
{
	my $id = shift @_;
	my $b_ver = "";
	my $m_ver = "";
	my $p_ver = "";
	my $check_base = "";
	my $len = length($id);

#	Naming rule of patch log will be "v2.04.02.M2.log", "v2.04.02.M2.P1.log", 
#	display on EM will be "v2.04.02.M2, M2.P1, M2.P2D, M2.P3D, ..."
#	[EXAMPLE]: v2.04.02.M2.P1.lib
#		       Branch Version => v2.04.02
#		       MP Version => M2
#		       Patch Version = P1

	# Branch Version
	$id =~ s/(.*)(M.*)/$2/;
	$b_ver = $1;

	# Non-match format, just print out.
	if ($len == length($id))
	{
		return $id;
	}

	# MP Version
	$id =~ s/(.*)(M.*)(P.*)/$2$3/;
	$m_ver = $2;

	# Patch Version
	$len = length($id);
	$id =~ s/(.*)(P.*)/$2/;
	if ($len != length($id))
	{
		$p_ver = $id;
	}

	DBG("  [VER]:B:$b_ver, M:$m_ver, P:$p_ver");

	$check_base = "$b_ver$m_ver";
	$check_base =~ s/(.*)(M.*)(\.)/$1$2/; # remove the redundant "." at the end 	
	if ($base_ver eq $check_base)
	{
		# Print MP and Patch version.
		return "$m_ver$p_ver"
	}
	else
	{
		# Print Base Version
		$base_ver = $check_base;
		return "$base_ver";
	}
}

sub IdToArray
{
	DBG("[PatchLog_List]:");
	for my $patchid (@patchlog_list)
	{
		my $exfile = 0;
		my $id_len = length($patchid);

		$exfile = IsExclusion($patchid);
		if ($exfile == 1)
		{
			DBG("  [EXC]: $patchid");
			next;
		}
		
		$patchid =~ s/(.*)(\/)(.*)(\.lib)/$3/;

		if ($id_len == length($patchid))
		{
			DBG("  [FMT]: Wrong format (*.lib)");
			next;
		}

		my $str = ParsePatchId($patchid);
		DBG("  [ACP] $str");
		print ARRAY_FILE "$str, ";
		
	}
}

DBG("[PatchLog_Source]:$patchlog_path");
DBG("[PatchLog_Array]:$patcharray_file");

open(ARRAY_FILE, "> $patcharray_file") or die "cannot open $patcharray_file\n";

print ARRAY_FILE "/* This file is auto-generated */ \n";
print ARRAY_FILE "#ifndef __PATCHID_ARRAY_H__\n";
print ARRAY_FILE "#define __PATCHID_ARRAY_H__\n\n";
print ARRAY_FILE "const u8 *$c_array_name = \"";
IdToArray();
print ARRAY_FILE "\"; \n\n";
print ARRAY_FILE "#endif \n\n";

close(ARRAY_FILE);


