#!/usr/bin/perl

@safe_funcs = ();

if ($#ARGV >= 0)
{
	print "Read allow function list from $ARGV[0].\n";
	open(OK_FH, $ARGV[0]);
	while (<OK_FH>)
	{
		if (/^(.*)\#.*\r\n/)
		{
			$_ = "$1\r\n";
		}
		/^[ \t]*([0-9a-zA-Z_]*)[ \t]*\r\n/;
		push(@safe_funcs, $1) if length $1 > 0;
	}
	print "There are $#safe_funcs functions listed in $ARGV[0]:\n";
	foreach $func (@safe_funcs) {
		print "$func,";
	}
	print "\n\n";
	close(OK_FH);
}

while (<STDIN>)
{
	last if /^Symbol[ \t]*File\r\n/;
}

%libc_caller = ();

$line_ready = 0;
while ($line_ready || ($_=<STDIN>))
{
   $line_ready = 0;
   
   $func_name = "";
   
   if (/^([.0-9a-zA-Z_][.0-9a-zA-Z_]*)[ \t]*([\.\: -_\\\/0-9a-zA-Z]*)libc.lib\((.*)\)\r\n/)
   {
      $func_name = $1;
      $filepath = $2;
      $filename = $3;
      
	$is_ok = 0;
	foreach $func (@safe_funcs) {
		if ($func eq $func_name)
		{
			$is_ok = 1;
		}
	}
	
	$func_name = "" if ($is_ok);
   }
   
   if ($func_name ne "")
   {
#      print "$func_name\n";
      @caller_list = ();
      while (<STDIN>)
      {
#	print $_;
        $line_ready = 1;
        last if (!(/^[ \t][ \t]*([\.\: +-_\\\/0-9a-zA-Z]*)\((.*)\)\r\n/));
	
	{
	  $caller_libfullpath = $1;
	  $caller_fname = $2;
	  $caller_libfullpath =~ /.*[\\\/]([+-_.0-9a-zA-Z]*)/;
	  $caller_basename = $1;
#	  push(@libc_funcs, $caller_fname);
	  push(@caller_list, [ $caller_basename, $caller_fname] ) if ($caller_basename ne "libc.lib");
#	  print "            $caller_basename($caller_fname)\n" if ($caller_basename ne "libc.lib");
	}
	
      }
      
      $libc_caller{$func_name} = [ @caller_list ] if ($#caller_list >= 0);
   }
}

$caller_count = keys %libc_caller;
if ($caller_count > 0)
{
	print "Unsafe C function list and caller object filename:\n";
	print "==================================================\n";
	foreach $c_func (sort keys %libc_caller)
	{
		print "$c_func()\n";
		$caller_list = $libc_caller{$c_func};
		foreach $caller (@$caller_list)
		{
			($caller_basename, $caller_fname) = @$caller;
			print "                $caller_basename($caller_fname)\n";
		}
	}

	print "\nThere are $caller_count un-safety functions linked from libc!!!\n";
	print "\n\n";
	exit (1);
}

print "libc ref check ok\n";
