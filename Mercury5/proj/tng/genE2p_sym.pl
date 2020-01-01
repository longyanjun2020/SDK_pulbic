#!/usr/bin/perl

use strict;
use Getopt::Std;

my $sym_file = $ARGV[0]."e2p_symbol.sym";
#my $ext_sym = "./MStarStudio_Config\/"."e2p_symbol_win32.c";
my $e2p_h = $ARGV[0]."e2p.h";
print( "Start to gen e2p sym $ARGV[0]\n" );
open(SYM_BUF, "> $sym_file") or die "cannot open output \"$sym_file\"\n";
#open(SYM_EXT, "> $ext_sym") or die "cannot open output \"$ext_sym\"\n";
open(E2P_H, "< $e2p_h") or die "cannot open output \"$e2p_h\"\n";
print SYM_BUF "#<SYMDEFS># ARM Linker, RVCT2.2 \n" ;
#print SYM_EXT "typedef unsigned _int32 u32;\n";
while ( <E2P_H> ) {
	unless(/_s\b/){
		   if(/^#define\s+(\w+)\s+(0x[\dA-Fa-f]+)/){
#       print( "$1 $2\n" );
       print SYM_BUF $2," ","N"," ","E2P_SYM_",$1, "\n" ;
#       print SYM_EXT "u32","    ","E2P_SYM_",$1," = ",$2,";","\n" ;
       }

  }
}
close(SYM_BUF);
#close(SYM_EXT);
close(E2P_H);




