#!/usr/bin/perl -w
#
# Usage: perl ./buildmake.pl <mcp.xml> <Folder> 
# ex. perl ./build core.mcp.xml SourceCode 
#
use strict;
use warnings;
use Cwd;
use Fcntl ':mode';
use XML::Simple;
use File::Copy qw(copy);
use Term::ANSIColor qw(:constants);
use 5.010;

my @demand;
my $DEBUG = 1;
my $root   = "/cygdrive/d/tmp/CPUB_RTOS";
my $outtail = "/inc";
my $outinc = "inc.mak";
#

sub print_help
{
	say "\nUsage: $0 <mcp.xml> <Folder>";
	say "eg. $0 core.mcp xml core/system/net/api";
	say "\nBecause this script is dedicated to \$(PATH_) scanning, ", BOLD, RED, "Please cd to /proj/sc/.", RESET;
	say "In the example here, core/system/net/api would be parsed as \$(PATH_core_system_net_api)";
	say "There should be '", BOLD, "core_system_net_api.scanned.mak", RESET, "' in core/system/net/api/.";
	say "Review/compare/rename it against the final file '", BOLD, "core_system_net_api.mak", RESET, "'";
}


# get files of @types in $dir
# Usage: get_filelist $dir, @types
# Output: A @list
sub get_filelist
{
	my ($dir, @types) = ($_[0], @{$_[1]});
	my @list;
	opendir(DIR, $dir) or return;
	while (defined(my $file = readdir DIR)) {
		if (-d $file) { next; }
		if (scalar @types == 0) { push @list, $file; next; }
		foreach my $item (@types) {
			if ($item eq substr($file, -length($item))) {
				push @list, $file;
			}
		}
	}
	closedir(DIR);
	return @list;
}

# seperate path and file
# Usage: my($path, $file) = distill $incfile
# Output:$path, $file
sub distill
{
	my $full = $_[0];
	if ($full =~ m/.+\//) {
		$full =~ /(.+\/)(.+)/;
		return (substr($1, 0, -1), $2);
	}
	return ("", $full);
}

# check input string with #include
# Usage: get_incf $line
# Output:same input string if yes
sub get_incf {
	if ($_[0] =~ m/^\s*#include\s+/) {
		$_[0] =~ m/"(\S+)"/;
		if (!defined $1) { return ""; };
		my $incf = $1;
		$incf =~ s/\\/\//g;
		return $incf;
	}
	return "";
}

# push file into array, check identical element first.
# Usage: push_file \@array, $path
sub push_file
{
	my ($array_ref, $new) = ($_[0], $_[1]);
	if ($DEBUG) { print STDERR "ADD NEW FILE $_[1]\n"; }
	foreach my $n (@$array_ref) {
		if ($new eq $n) { return; }
	}
	push (@$array_ref, $new);
}

# push path into array, check identical element first.
# Usage: push_path \@array, $path
sub push_path
{
	my ($array_ref, $new) = ($_[0], $_[1]);
	foreach my $n (@$array_ref) {
		if ($new eq $n) { return 0; }
	}
	push (@$array_ref, $new);
	return 1;
}

# build include flag -I<path>
# Usage: build_inc_flags \@array
# Output: A string of -I....
sub build_inc_flags
{
	my ($array_ref) = @_;
	my $idx = 0;
	my $incflag = "\nPATH_H += \\\n    ";
	#my ($sorted) = sort { $a cmp $b } \@$array_ref;
	#my ($sorted) = sort \@$array_ref;
	#my ($sorted) = sort @_;
	my @another = ();
	#push(@$another, "aaa");
	#print STDERR "before:@$array_ref\n";
	#print STDERR "after :@$sorted\n";
	#print STDERR "test :@$sorted[1]\n";
	#print STDERR "another :@$another\n";
	foreach my $n (@$array_ref) {
	#foreach my $n (@$sorted) {
	#foreach my $n (@$_) {
		push(@another, $n);
	}
	@another = sort @another;
	#print STDERR "another :@another\n";
	#foreach my $n (@$sorted) {
	foreach my $n (@another) {
		if ($idx++ == 0) {
			$incflag = join "", $incflag, $n, "\\\n";
			next;
		}
		$incflag = join "", $incflag, "    ", $n, "\\\n";
	}
	return substr $incflag, 0, -2;
}

sub build_path_h
{
	my ($array_ref) = @_;
	my $idx = 0;
	my $incflag = "\nPATH_H += \\\n    ";
	my @another = ();

	@another = sort @$array_ref;
	foreach my $n (@another) {
		if ($idx++ == 0) {
			$incflag .= "$n\\\n";
			next;
		}
		$incflag .= "    $n\\\n";
	}
	return substr $incflag, 0, -2;
}

# To make relative path from current path to goal path
# Usage: make_rel_path $cur_path, $goal
sub make_rel_path
{
	my ($curr, $goal) = ($_[0], $_[1]);;
	my (@fc, @fg, @fr, $idx, $sn);
	my $relp = "";

	@fc = split /\//, $curr;
	@fg = split /\//, $goal;
	@fr = ();
	my $nc = scalar(@fc);
	my $ng = scalar(@fg);
	$sn = ($nc < $ng)? $nc : $ng;
	my ($iu, $id);
	for ($iu = 0; $iu < $sn; $iu++) {
		if ($fc[$iu] ne $fg[$iu]) {
			last;
		}
	}
	$id = $iu;
	for (; $iu < $nc; $iu++) {
		push(@fr, "..");
	}
	for (; $id < $ng; $id++) {
		push(@fr, $fg[$id]);
	}
	if (scalar(@fr) != 0) {
		$relp = join "/", @fr;
		return $relp;
	} else {
		return ".";
	}
}

# To make relative path variable from current path to parent path
# Usage: make_parent_path_variable $in_path, $delimiter
sub make_parent_path_variable
{
	my $in = $_[0];
	my $delimiter = $_[1];
	my $result = "";
	my $tail;
	
	my (@fg);
	
	@fg = split /\//, $in;
	
	$tail = pop(@fg);
	#$target = substr($curr, 1);
	#print "pop:$tail $curr $target: $goal\n";
	if (scalar(@fg) != 0) {
		$result = join $delimiter, @fg;
		#$result = "" . $result . "}" . "$curr";
		return $result;
	} else {
		return ".";
	}
}

# To make relative path from current path to goal path
# Usage: make_path_variable $cur_path, $goal
sub make_path_variable
{
	my ($curr, $goal) = ($_[0], $_[1]);
	my (@fg);
	my $result = "";
	my $tail;
	my $target = "";

	@fg = split /\//, $goal;
	
	$tail = pop(@fg);
	$target = substr($curr, 1);
	#print "pop:$tail $curr $target: $goal\n";
	if ($tail eq $target) {
		#say "EQ\n";
	} else {
		say RED, "Special path", RESET, ": $goal";
		push(@fg, $tail);
		$curr = "";
	}
	if (scalar(@fg) != 0) {
		$result = join "_", @fg;
		#$result = "\${PATH_" . $result . "}/inc";
		$result = "\$(PATH_" . $result . ")" . "$curr";
		return $result;
	} else {
		return ".";
	}
}

# merge two path
# Usage: merge_path $first, $second
# Output:A path
sub merge_path
{
	my (@f1, @f2, @ff);
	my ($first, $second) = ($_[0], $_[1]);
	my $path = $second;
	my $ret;

	@f1 = split /\//, $first;
	@f2 = split /\//, $second;
	@ff = @f2;
	foreach my $elem (@ff) {
		if ($elem eq "..") { shift @f2; pop @f1; } else { last; }
	}
	@ff = @f2;
	if (scalar @ff > 0) {
		for (my $i = scalar @ff - 1; $i >= 0 ; $i--) {
			if ($f1[scalar @f1 - 1] eq $ff[$i]) {
				pop @f1; shift @f2;
			} else {
				last;
			}
		}
	}
	$ret = "";
	foreach my $elem (@f1) { $ret = join "", $ret, $elem, "/"; }
	foreach my $elem (@f2) { $ret = join "", $ret, $elem, "/"; }
	$ret = substr($ret, 0, -1);
	return $ret;
}

# find_file - search $file from $path
# Usage : find_file $file, $path, $curr
# Output: full file name
sub find_file
{
	my ($file, $path, $curr) = ($_[0], $_[1], $_[2]);
	my $cmd = join(' ', "find", $path, "-iname", $file);
	my $out = `$cmd`;
	#print STDERR "$out";
	my @multilines = split /\n/, $out;
	if (scalar @multilines == 1) {
		# only a file found, just return it.
		return $out;
	} else {
		# many files found, get the shortest path
		my @currsp = split /\//, $curr;
		my $currsz = scalar @currsp;
		my $best = -1;
		my $idx = 0;
		my $max = -1;
		foreach my $candidate (@multilines) {
			if ($DEBUG) { print STDERR ">> $idx:$candidate\n"; }
			my $goalpath = substr($candidate, length($path) + 1, length($candidate) -
																 length($path) - 1 -
																 length($file) - 1);
			my @goalsp = split /\//, $goalpath;
			my $goalsz = scalar @goalsp;
			my $chkt = $currsz < $goalsz ? $currsz : $goalsz;
			my $i;
			for ($i = 0; $i < $chkt; $i++) {
				last unless ($currsp[$i] eq $goalsp[$i]);
			}
			if ($max < $i) { $max = $i; $best = $idx; }
			$idx++;
		}
		if ($DEBUG) {
			if ($best >= 0) {
				print STDERR "  The Best is $best\n";
			} else {
				print STDERR RED, "  File not found! ($best)\n", RESET;
			}
		}
		return $multilines[$best];
	}
}
# get line of #include to process
# Usage: process_include $relpath, $file, $toroot \@outHeader, [,\@outgrp]
#
sub process_include
{
	my ($curr, $file, $toroot, $oh, $outgrp, $donelist) =
					($_[0], $_[1], $_[2], $_[3], $_[4], $_[5]);
	my @incgrp = ();

	open my $fd, $file or return;
	if ($DEBUG) { print STDERR BOLD, GREEN, "======= $file =======\n", RESET; }
	while (my $line = <$fd>)  {   
		my $inc = get_incf($line);
		if ($inc ne "") {
			my ($path, $file) = distill $inc;
			if ($DEBUG) { print STDERR "  GOT \"$path\", \"$file\"\n"; }
			# FIND FILE FROM $toroot BY CMD - find $toroot -iname $file
			if (push_path(\@$donelist, $inc) == 0) { next; }
			print STDERR "  find - $toroot, $file\n";
			my $out = find_file($file, $toroot, $curr);
			if (!defined $out) { print STDERR "**miss $file\n"; next; }
			chomp($out);
			# print "File find $out\n";
			if ($out ne "") { push_path(\@$oh, $out); }
			if ($DEBUG) { print STDERR "  found \"$out\"\n"; }
			$out = get_relpath($out, $toroot);
			if ($out ne "") {
				my $trip = substr($out, 0, -(length($file) + 1));
				my $goal = merge_path $trip, $path;
				#my $inc = make_rel_path $curr, $goal;
				my $inc = make_path_variable ("/inc", $goal);
				if ($inc ne "") {
					if (defined $outgrp) { push_path(\@$outgrp, $inc); }
									else { push_path(\@incgrp, $inc); }
				} elsif ($path ne "") {
					if (defined $outgrp) { push_path(\@$outgrp, "."); }
									else { push_path(\@incgrp, "."); }
				}
			} else {
				print STDERR "**WARNNING**- CANNOT FIND $file\n";
			}
		}
	}
	if (scalar @incgrp) {
		my $incflags = build_path_h(\@incgrp);
		print STDERR "$incflags\n";
	}
	close $fd;
}

# get relative path
# Usage: get_relpath $file_abspath, $base_abspath
sub get_relpath
{
	my ($path, $base) = ($_[0], $_[1]);
	if (length($path) > length($base)) {
		return substr($path, length($base) + 1);
	} else {
		return "";
	}
}

# input mcp xml file
# create_demandlist $xmlfile, $extension
# output a filename list
sub create_demandlist
{
	my $xmlfile = $_[0];

	my $filelist = XMLin($xmlfile);
	my $file = $filelist->{FILE};
	print scalar(@$file), "\n";
	foreach my $elem (@{$file}) {
		my $name = $elem->{PATH};
		if ($name =~ m/\.c/) {
			push(@demand, $name);
		} elsif ($name =~ m/\.s/) {
			push(@demand, $name);
		}
	}
}
#
# dirlist $folder
sub dirlist
{
	my $dname = $_[0];
	my $hasfile = 0;
	
	say "dname:$dname";

	opendir(my $dh, $dname) || die "can't opendir $dname $!";
	my @list = grep { !/^\./ && $_ } readdir($dh);
	my @pd = ();
	my @pc = ();
	closedir $dh;
	foreach my $file (@list) {
		my $match = 0;
		my $mode = (stat("$dname/$file"))[2];
		next unless ($match == 0);
		if (-d "$dname/$file") { push @pd, "$dname/$file"; }
		if (-f "$dname/$file" && $file =~ /\.c/) { push @pc, $file; }
		if (-f "$dname/$file" && $file =~ /\.s/) { push @pc, $file; }
	}
	# do prefix trace
	my @regdir = ();
	if (scalar @pd) {
		#print "--SUBFOLDER $dname\n";
		foreach my $subf (@pd) {
			#print "\t$subf\n";
			my $has = dirlist($subf);
			if ($has) {
				$subf =~ /(.+\/)(.+)/;
				push(@regdir, $2);
			}
			$hasfile += $has;
		}
	}
	if (scalar @pc || $hasfile) {
		my $srcf;
		my $fh;
		my $troot = ".";	#$dname;
		my @incpath = ();
		my @inch = ();
		my @foundlist = ();
		# get rel path to $root
		#$troot =~ s/\w+/\.\./g;
		# create source.mak
		
		
		#temp debug
		my $p_path = make_parent_path_variable($dname, "/");
		$srcf = make_parent_path_variable($dname, "_");
		my $fname = $p_path . "/" . $srcf . ".scanned.mak";
		#say "open $dname/source.mak \nproposed($p_path __ $srcf)";
		#say "open ====> $fname";

		#open($fh, ">", "$dname/source.mak") ||
		#		die "Cannot open $dname/source.mak:$!";
		open($fh, ">", "$fname") ||
				die "Cannot open $fname:$!";
		print $fh "#-------------------------------------------------------------------------------
#	\${Variable} is generated by script and \$(variable) is manually maintained.
#-------------------------------------------------------------------------------\n\n";
		print $fh "#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib\n\n";

		$srcf = make_path_variable("/src", $dname);
		print $fh "PATH_C +=\\\n    $srcf\\\n";

		#temp debug
		#say "srcf: $srcf";
		#close $fh;
		#return $hasfile;

		foreach my $csrc (@pc) {
			if ("@demand" =~ /\b$csrc\b/) {
			#	print "\t$csrc\n";
				print "inc - $dname, $csrc, $troot\n";
				process_include($dname, "$dname/$csrc", $troot,
								\@inch, \@incpath, \@foundlist);
				#print $fh "    $csrc \\\n";
				$hasfile = 1;
			} else {
				#print "Drop $csrc\n";
			}
		}
		if (0) {
			print $fh "\nDIRS := \\\n";
			foreach my $csub (@regdir) {
				#print "write DIR - $csub\n";
				print $fh "\t\t$csub \\\n";
			}
			print $fh "\n";
		}
		# build inc.mak
		foreach my $item (@inch) {
			print STDERR "CheckHeader = $item\n";
			process_include($dname, $item, $troot, \@inch,
							\@incpath, \@foundlist);
		}
		if (scalar @incpath) {
			print STDERR "Build INC PATH @incpath\n";
			my $incflags = build_inc_flags(\@incpath);
			#open (my $fh, '>', "$dname/$outinc") or
			#		die "Could not write to '$outinc'\n";
			print $fh "$incflags\n\n";
		}
		
		#build SRC_C_LIST
		print $fh "#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\\\n";
		foreach my $csrc (@pc) {
			if ("@demand" =~ /\b$csrc\b/) {
				print $fh "    $csrc \\\n";
			}
		}

		close $fh;
		#copy "build.mak", "$dname/build.mak" ###??? where is this file?
	}
	return $hasfile;
}

#####################################
if (@ARGV <= 1) {
    print_help;
	exit 1;
}

my $mcpxml = $ARGV[0];
create_demandlist($mcpxml);
my $dir = shift @ARGV;
#my @test = ("aaa", "ccc", "bbb");
#my @test = ("\${PATH_core_system_net_dhcp}/inc", "\${PATH_ahc_api}/inc", "\${PATH_core_system_net_lwip_porT}/inc");
#my $re = sort_test(\@test);
#my ($after) = sort \@$test;
#my @after = sort @test;
#say "after @after \n";
#print STDERR "after: $re \n";

foreach $dir (@ARGV) 
{
	dirlist($dir);
}

