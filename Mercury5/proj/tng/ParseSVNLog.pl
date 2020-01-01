#!/usr/bin/perl

sub END
{
	close INPUT_FILE;
	close OUTUPUT_FILE;
}

die "Usage: ParseSVNLog rev.log SVN_ROOT delta_files.txt\n" if @ARGV != 4;

# open file handle
$input_file = shift (@ARGV);
open INPUT_FILE, "<$input_file"
	or die "SVN log file $input_file not found\n";

$SVN_ROOT = shift (@ARGV);
	
$output_file = shift (@ARGV);
open OUTUPUT_FILE, ">$output_file"
	or die "Output file $output_file can not be created\n";
	
$del_file = shift (@ARGV);
if (-e $del_file)
{
open DEL_FILE, ">>$del_file"
	or die "$del_file can not be created\n";
} else
{
open DEL_FILE, ">$del_file"
	or die "$del_file can not be created\n";
print DEL_FILE "=========== Deleted files/Folders ===========\n";
print DEL_FILE "\n";
}
	
$prefix_add = "   A ";
$prefix_modify = "   M ";
$prefix_del = "   D ";

while (<INPUT_FILE>)
{
	chomp;

	if ($SVN_ROOT eq "NULL")
	{
		# for file add
		if ( (/^$prefix_add\/(.+) \(s*/) ||
		     (/^$prefix_add\/(.+)\x0d/) )
		{
			$filename = sprintf("%s", $1);
			if (-d $filename)
			{
				# this is a folder
			} else
			{
				if (-e $filename)
				{
					print OUTUPUT_FILE "$filename\n";
				}
			}
		
		}
			
		# for file modify
		if (/^$prefix_modify\/(.+)\x0d/)
		{
			$filename = sprintf("%s", $1);
			if (-d $filename)
			{
			} else
			{
				print OUTUPUT_FILE "$filename\n";
			}
		}
		
		# for file delete
		if (/^$prefix_del\/(.+)/)
		{
			$filename = sprintf("%s", $1);
			if (-d $filename)
			{
				# this is a folder
			} else
			{
				if (-e $filename)
				{
					# this file is added back?
				} else
				{
					print DEL_FILE "$filename\n";
				}
			}
		
		}
	} else
	{
		# for file add
		if ( (/^$prefix_add(.+)$SVN_ROOT\/(.+) \(s*/) ||
		     (/^$prefix_add(.+)$SVN_ROOT\/(.+)\x0d/) )
		{
			$filename = sprintf("%s", $2);
			if (-d $filename)
			{
				# this is a folder
			} else
			{
				if (-e $filename)
				{
					print OUTUPUT_FILE "$filename\n";
				}
			}
		
		}
			
		# for file modify
		if (/^$prefix_modify(.+)$SVN_ROOT\/(.+)\x0d/)
		{
			$filename = sprintf("%s", $2);
			if (-d $filename)
			{
			} else
			{
				print OUTUPUT_FILE "$filename\n";
			}
		}
		
		# for file delete
		if (/^$prefix_del(.+)$SVN_ROOT\/(.+)\x0d/)
		{
			$filename = sprintf("%s", $2);
			if (-d $filename)
			{
				# this is a folder
			} else
			{
				if (-e $filename)
				{
					# this file is added back?
				} else
				{
					print DEL_FILE "$filename\n";
				}
			}
		
		}
	}
		
}