#! /usr/bin/perl

#if($#ARGV == 2)
#{
#	print "Please specify the functional profile result text file!";
#	die;
#}

my $func_profile_output = $ARGV[0];
open PROFILE_OUTPUT, $func_profile_output or die "Please specify function profile result txt file!\n";
open PROFILE_RESULT, ">FuncProfileResult.txt" or die "Cannot create result";

my @func_list;
my $func_total_count = 0;		# Exclude undecoded count
my $undecoded_count = 0;
my %func_statistics;
my $percentage = 0.0;

my $line_to_process;

sub hashValueDescendingNum
{
   $func_statistics{$b} <=> $func_statistics{$a};
}

while(<PROFILE_OUTPUT>)
{
	chomp;
	
	if($_ !~ /RTK\[08\]/ and $_ !~ /RAW\[00\]/){next;}
	
	# Skip leading numbers 
	#  33 TR#0090
	#1590 TR#1665
	if(/^\s*\d+ (.*)/)
	{
		$line_to_process = $1;
	}
	else
	{
		$line_to_process = $_;
	}
	
	# TR#1E1F  RTK[08] hac1_AllocPwrResources (0x0013afe2), hwll1_GoToLightSleep (0x000829c3), 
	# hwll1_GoToLightSleep (0x000829c3), hwll1_GoToLightSleep (0x000829c3),
	# RO#2BC1  RAW[00] 1748d5020000c3290800c3290800c3290800c32908000000
	# TR#0005  RTK[08] START to output functional level profile, sampling period = 20 ticks in 32khz, sampling count = 45916 times
	# TR#2CDD  RTK[08] END to output functional level profile

	if($line_to_process =~ /RTK\[08\] START/){next;}
	if($line_to_process =~ /RTK\[08\] END/){next;}

	@func_list = split(/\s+/, $line_to_process);
	
	foreach $func_item(@func_list)
	{
		if($func_item =~ /^TR#/){next;}
		if($func_item =~ /^RTK\[/){next;}
		if($func_item =~ /^\(0x/){next;}
		
		if($func_item =~ /^RO#/)
		{
			# There are traces not decoded by TMT and will affect the result
			$undecoded_count += 4;
			next;
		}
		if($func_item =~ /^RAW\[/){next;}
		if($func_item =~ /[0-9a-f]{48}/){next;}

		$func_statistics{$func_item}++;
		$func_total_count++;
	}
}

# Output result to console and file
print "Total function occurrence count: $func_total_count \n";
print "There are $undecoded_count functions undecoded by TMT and may affect the results.\n" if($undecoded_count);
print "Percentage\tOccurrence\tFunction\n";

print PROFILE_RESULT "Total function occurrence count: $func_total_count \n";
print PROFILE_RESULT "There are $undecoded_count functions undecoded by TMT and may affect the results.\n" if($undecoded_count);
print PROFILE_RESULT "Percentage\tOccurrence\tFunction\n";

foreach $key(sort hashValueDescendingNum(keys(%func_statistics)))
{
	$percentage = $func_statistics{$key} / $func_total_count;
	#print "$percentage\t$func_statistics{$key} \t $key\n";
	
	printf "%f\t %s\t\t %s\n", $percentage, $func_statistics{$key}, $key;
	
	printf PROFILE_RESULT "%f\t %s\t\t %s\n", $percentage, $func_statistics{$key}, $key;	
}

