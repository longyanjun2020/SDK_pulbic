#!/usr/bin/perl
#---------------------------------------------------------------------------------------------
#
#                   AIT Multimedia Network - Configuration Space Compiler
#                     (c) Copyright 2012, Alpha Imaging Technology Corp.
#               All rights reserved. Protected by international copyright laws.
#
#---------------------------------------------------------------------------------------------

use strict;
use Getopt::Std;

#---------------------------------------------------------------------------------------------
my $usage =<<EOF;
USAGE: $0  [OPTION]...  <CFG_FILE>

	Parsing the System Configuration file into a C source codes

Options:
	-o file_name : output filename
	-d <n> : enable debug for phase <n>
	-h : this help message

Example:
	cd Firmware/NET
	bin/cfg-compile.pl -o common/inc/auto_syscfg.h common/conf/amn_system.linux.conf
	bin/cfg-compile.pl -o common/inc/auto_syscfg.h common/conf/amn_system.ucos.conf
EOF
	;


my %options=();
my ($outFP, $inFP, $debug);

get_options();
check_options();


#---------------------------------------------------------------------------------------------
my ($i, $j, %cfgs, $name, $val, $attr, $len, $size);

# phase 1: parsing input
#------------------------
while (<$inFP>) {
	$i++;
	next if (($_ =~ /^#/) || ($_ =~ /^\s*$/));   # skip empty lines or comments

	$_ =~ /([^=]*)\s*=\s*(.*)/;
	$name = trim($1);
	$val = trim($2);

	if ($val =~ /(.*)\s*;\s*(.*)/) {
		my $tmp;
		$val  = trim($1);
		$tmp  = trim($2);
		if ($tmp eq 'RUNTIME') {
			$attr = 1;
		} else {
			printf "##ERROR## BAD ATTRIB - %s\n", $tmp;
			$attr = 0;
		}
	} else {
		$attr = 0;
	}
    
    #remove tailing inline comment
    if ($val =~ /(.*)\s*#.*/) {
        $val = trim($1);
    }
    
	if ($val =~ /^[0-9]+$/ || $val =~ /^0x[0-9a-fA-F]+$/) {
		$cfgs{$name} = {
			type  => 'INT',
			value => $val,
			attr  => $attr
		};
#		if ($debug == 1) { printf "NAME='%s' \t%s=%s\n", $name, $cfgs{$name}{'type'}, $val; }
	}
    elsif (!(substr($val,0,1) eq '"') || !(substr($val,-1,1) eq '"')) {
# =begin BLOCK_COMMENT
        if ($val =~ m/^(yes|no)$/i) {
            $cfgs{$name} = {
                type  => 'INT',
                value => ($val =~ /yes/i ? 1 : 0),
                attr  => $attr
            };
        }
        elsif ($val =~ m/^(on|off)$/i) {
            $cfgs{$name} = {
                type  => 'INT',
                value => ($val =~ /on/i ? 1 : 0),
                attr  => $attr
            };
        }
        else {
            printf "\n##WARN## LINE %d: NAME='%s' \tinvalid string = '%s'\n\n", $i, $name, $val;
            next;
        }
# =end BLOCK_COMMENT
    }
# =cut
	else {
		if ($val eq "") {
			$val = "        ";
		}
		#                           2 = -2+3+1  ==>  -2: surrounding ",  +3: rounding up to 4,  +1: C string trailing '\0'
		$size = int((length($val) + 2) / 4) * 4;      # rounding 4
		$val = substr($val,1,-1);                     # strip off the leading and ending "
		$val = trim($val);                            # removing SPACE's
		$len = length($val);

		$cfgs{$name} = {
			type  => 'STR',
			value => $val,
			len   => $len,
			bufsz => $size,
			attr  => $attr
		};

#		if ($debug == 1) { printf "NAME='%s' \t%s.%d.%d='%s'\n", $name, $cfgs{$name}{'type'}, $len, $size, $val; }
	}
	dbg_print( $name, 1 );
}

# phase 2: generating output
#-----------------------------
my @cfgnames = keys(%cfgs);
my $totals = $#cfgnames + 1;

printf $outFP <<EOF;
// THIS IS AUTOMATICALLY GENERATED FILE, DON'T EDIT IT !!!
#ifndef __AMN_CONFIG_SPACE_FOR_NETWORK_DEFINITIONS__
#define __AMN_CONFIG_SPACE_FOR_NETWORK_DEFINITIONS__

#define AMN_CONFIGSPACE_TOTAL_ENTRIES     $totals
#define AMN_CONFIGSPACE_MAGIC_IDENTITY    0xAA1155BB

struct amn_config_space_storage_t {
	int  amn_cfg_magic_identify;
	void *amn_pic_struct_base; // Base Address for Position Independent (Code) String Buffer relocation
	char *amn_pic_strbuf_base;
	struct amn_cfgspace_value_t cfg_values[AMN_CONFIGSPACE_TOTAL_ENTRIES];
EOF

$j = -1;
$i = 0;
foreach $name (sort keys(%cfgs)) {
	if ($cfgs{$name}{'type'} eq 'STR') {
		printf $outFP "\tchar strbuf%d[%d]; // %s\n", $i, $cfgs{$name}{'bufsz'}, $name;
		if ($j == -1)  { $j = $i; }
	}
	$i++;
	dbg_print( $name, 2 );
}

printf $outFP <<EOF;
};

#ifdef __AMN_DEFINES_FOR_CONFIGSPACE_STATICS__
struct amn_config_space_storage_t amn_syscfg_factory = {
\tAMN_CONFIGSPACE_MAGIC_IDENTITY,
\t&amn_syscfg_factory,
\t&amn_syscfg_factory.strbuf${j}[0],
\t{
EOF

$i = 0;
foreach $name (sort keys(%cfgs)) {
	if ($cfgs{$name}{'type'} eq 'STR') {
		printf $outFP "\t\t{ CFGSPACE_VALTYP__STR,%4d,%4d,%4d, { &amn_syscfg_factory.strbuf%d[0] }, }, // %s\n",
			$cfgs{$name}{'bufsz'}, $cfgs{$name}{'len'}, $cfgs{$name}{'attr'}, $i, $name;
	}
	else {
		printf $outFP "\t\t{ CFGSPACE_VALTYP__INT,   0,   0,%4d, { (char*)%s }, }, // %s\n",
			$cfgs{$name}{'attr'}, $cfgs{$name}{'value'}, $name;
	}
	$i++;
	dbg_print( $name, 3 );
}
printf $outFP "\t},\n";

$i = 0;
foreach $name (sort keys(%cfgs)) {
	if ($cfgs{$name}{'type'} eq 'STR') {
		printf $outFP "\t\"%s\", // %s\n", $cfgs{$name}{'value'}, $name;
	}
	dbg_print( $name, 4 );
}

printf $outFP <<EOF;
};

// struct amn_system_config_space_t amn_ConfigSpaceDict[AMN_CONFIGSPACE_TOTAL_ENTRIES] = {
char *amn_ConfigSpaceDict[AMN_CONFIGSPACE_TOTAL_ENTRIES] = {
EOF

$i = 0;
foreach $name (sort keys(%cfgs)) {
#	printf $outFP "\t{ \"%s\", &amn_syscfg_factory.cfg_values[%d] },\n", $name, $i++;
	printf $outFP "\t\"%s\",\n", $name;
}

printf $outFP <<EOF;
};
#else
extern char *amn_ConfigSpaceDict[AMN_CONFIGSPACE_TOTAL_ENTRIES];
extern struct amn_config_space_storage_t amn_syscfg_factory;

#endif

#endif

EOF

#---------------------------------------------------------------------------------------------
sub get_options() {
	if (!getopts("ho:d:",\%options) || $options{'h'}) {
		print $usage;
		exit 0;
	}
}

sub check_options() {
	$debug = 0;
	if ($options{'d'}) {
		$debug = $options{'d'};
	}

	if ($options{'o'}) {
		open($outFP, ">", $options{'o'}) or die "Can't open $options{'o'}: $!";
	}
	else {
		open($outFP, ">-") or die "Can't open STDOUT $!";
	}

	open($inFP, "<", $ARGV[0]) or die "Can't open $ARGV[0]: $!";
}


#---------------------------------------------------------------------------------------------
sub dbg_print($$)
{
	my ($name, $phase) = @_;
	if ($debug == $phase) {
		if ($cfgs{$name}{'type'} eq 'INT') {
			printf "NAME='%s' \tINT=%s\n", $name, $cfgs{$name}{'value'};
		}
		else {
			printf "NAME='%s' \tSTR.%d.%d='%s'\n", $name, $cfgs{$name}{'len'}, $cfgs{$name}{'bufsz'}, $cfgs{$name}{'value'};
		}
	}
}

#---------------------------------------------------------------------------------------------
# Perl trim function to remove whitespace from the start and end of the string
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

