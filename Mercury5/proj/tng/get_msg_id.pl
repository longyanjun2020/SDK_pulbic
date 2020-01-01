#!/usr/bin/perl
##--------------------------------------------------------------------------------------------------
## Script to get RTK message IDs from header files.
##
## Does not require any extra Perl packages.
## See end of file for command line parameters.
##
## WARNING: it is assumed that message IDs are within a certain range which is hard-coded
##          in that script. The same applies for timer IDs.
##--------------------------------------------------------------------------------------------------
## Author | Rev | Date     | Comment
##--------------------------------------------------------------------------------------------------
##  RDO   | 1.0 | 16/10/07 | Creation
##--------------------------------------------------------------------------------------------------
##  DAY   | 1.1 | 21/11/07 | Added absolute path for each file parsed
##--------------------------------------------------------------------------------------------------
##  RDO   | 1.2 | 21/11/07 | * Fixed absolute path for '.'
##        |     |          | * Take into account internal L1 messages having a lower ID than 0x2000
##--------------------------------------------------------------------------------------------------
##  RDO   | 1.3 | 22/11/07 | Fixed enum parsing to get Battery messages.
##--------------------------------------------------------------------------------------------------
##  RDO   | 1.5 | 10/05/11 | We only parsing a header "$pp_out" which include all *_message_define__.hi.MSG
##--------------------------------------------------------------------------------------------------

use strict;
use Getopt::Std;

my $Version="1.5";
my $Date="May 2011";

my $WorkDir=".";
my @FileList;
my $File;
my $i;
my %MsgIdByNameHash;
my %MsgIdByIdHash;
my %BaseByNameHash;

my $Verbose=0;
my $OutputFile;
my $pp_out = "all_msg.h";		# it must sync. the $(ALL_HEADER_FILE_OUT) in tmt.mak

my %opts;
getopts('i:o:v:h', \%opts); ## parse command line arguments

if (exists $opts{i}) {$WorkDir=$opts{i};}
if (exists $opts{v}) {$Verbose=$opts{v};}
if (exists $opts{o}) {$OutputFile=$opts{o};}
if (exists $opts{h}) {PrintHelp(); exit; }

##
## Modify this list to skip specific files. Wildcards not accepted.
##
## these two files contain RTK message-like definitions which get the script confused.
#my @SkipList=("cpu_mem_map.hc", "master.hp");
my %SkipList={"cpu_mem_map.hc"=>1,
    "master.hp"=>1,
    "avp_msmComm.h"=>1,
    "msmError.h"=>1,
    "mdl_vdr_error.h"=>1
};

if (keys(%SkipList) > 0) {
  print ("WARNING: following files are not parsed:\n");
  foreach (keys %SkipList) {print "  $_\n";}
}

##
## All RTK messages (ie not timers) range from 0x2000 to 0x7000 (approx).
## However internal L1 messages range from 0x0600 to 0x0610 (approx)
my $MinID = 0x0600; ## needed to discard lower  than that IDs as non RTK message.
my $MaxID = 0xFFFF; ## needed to discard higher than that IDs as non RTK message.
printf ("WARNING: assume 0x%04x <= message ID <= 0x%04x\n", $MinID, $MaxID);
printf ("         assume 0x0000 <= timer ID   <= 0x%04x\n", $MaxID);

##
## Now let's go
##

##
## Step 0: Read all .h, .hi, .ht, ... files in working dir and skip those in SkipList
##
if ($WorkDir !~ /\/$/) {
  ## Working dir is not terminated by a '/', so add a trailing '/' so that
  ## absolute pathname can made by concatenating working dir and filename.
  $WorkDir .= "/";
}
dbg_print ("Working dir is '$WorkDir'\n");
dbg_print ("Step 0: get all files to parse\n");



# v 1.5: we only parsing the file $pp_pot
# replace @FileList as $pp_out
@FileList = ("$WorkDir".$pp_out);

# v 1.5: The following code would never be used after v 1.5,
# however, we reserve the code since it is quite pretty.
if(0)
{

opendir (DIR, $WorkDir) or die "Cannot open $WorkDir: $!";

my @TPPFileList=grep{
    m/.*\.tpp$/i
} readdir DIR;
closedir DIR;

my $parsing_flag=0;
my %FileList_hash;
foreach my $TPPFile (@TPPFileList){
    open(FIN, "<", "$WorkDir$TPPFile")
        or die "parse_tpp: unable to open $TPPFile: $!\n";
    while(<FIN>){
        if($parsing_flag == 1){
            if(m/\s+(\S+)\\$/){
                $FileList_hash{$1}++;
            }elsif(m/\s+(\S+)$/){
                $FileList_hash{$1}++;
                $parsing_flag=0;
            }
        }elsif(m/DEPENDS\s*=\s*\\\s*$/){
            $parsing_flag=1;
        }
    }
    if($parsing_flag){
        warn "parse_tpp: stilling parsing\n" ;
        $parsing_flag=0;
    }
    close(FIN);
}

foreach my $file (grep {
    my $File=$_;
  /.*\.h.?/ and ! /\.pp$/
    and $SkipList{$_}!=1
    }sort(keys(%FileList_hash))){
    if(-e $file){
        #print "$file exists, push into FileList!!\n";
        push @FileList, $file;
    }
}
} # end of "if(0)"

foreach (@FileList) {	dbg_print ("'$_'\n");}

##
## Step 1: Get all message names and their definition in hash table
## Example: message "MM_REST_CONF" => "MM_BASE + MMC_SUB_BASE + FROM_MM + 0x06"
##
my $LastBase;
my $LastIndex;
my $ParseEnumAllowed;
my $msg_start_found;

dbg_print ("Step 1: parse files\n");

foreach $File (@FileList) {
    dbg_print ("Opening $File\n");
    open (FILE, $File) or die "Cannot open file $File : $!";

 $ParseEnumAllowed=0;
 $msg_start_found=0;
 while (<FILE>) {
   chomp;    ; ## remove any '\n' at end of line

   s/\/\*.*//; ## remove comment /* to ease regex match below
   s/\/\/.*//; ## remove comment // to ease regex match below
   s/,[\r\W]+//;
   if(/^#/) {
    next;
   }
   s/^[\W\r]+$//;


   if($msg_start_found==0) {
       if (/MESSAGE_ID_START/) {
        $msg_start_found=1;
       }
       next;
   }

   if (0) {#(/\#define\s+(\w+)\s+(.*_BASE.*)/) {
     ##
     ## Ignore message names terminated by '_BASE' as it's unlikely an RTK message but a base
     #next if ($1 =~ /_BASE$/);

     dbg_printf ("%-16s: %-50s: %s\n", $File, $1, $2);
     $MsgIdByNameHash{$1} = $2;
     ##
     ## Would extract bases "MM_BASE", "MMC_SUB_BASE", "FROM_MM" from example to store them
     ExtractBase ($2);
     next;
   }
   next unless ($_);

   my ($Name, $Str) = ParseEnum1($_);
   next unless ($Name);
   dbg_printf ("$Name=$Str\n");
   $MsgIdByNameHash{$Name} = $Str;
   ExtractBase ($Str);
 }
 close (FILE);
}


## Step 1a: Parse .pp files enums (#define will not appear in .pp files)
dbg_print ("Step 1a: parse .pp files\n");

my $WorkDir_PP;
my $File_PP;
$WorkDir_PP = "$WorkDir"."PreprocessFiles\/";
#$WorkDir_PP = "$WorkDir"."PreprocessFiles\\temp\\";

foreach $File (@FileList) {
    #$File_PP = "$WorkDir_PP"."$File"."\.pp";
    $File_PP = "$WorkDir_PP".basename_unix($File)."\.pp";
 #open (FILE, $File_PP) or warn "Cannot open file $File_PP : $!";
    open (FILE, $File_PP) or next;

 $ParseEnumAllowed=0;
 while (<FILE>) {
   chomp;    ; ## remove any '\n' at end of line
   s/\/\*.*//; ## remove comment /* to ease regex match below
   s/\/\/.*//; ## remove comment // to ease regex match below

   my ($Name, $Str) = ParseEnum_PP($_);
   #dbg_printf ("ParseEnum_PP parsing result: %-16s: %-50s: %s\n", $Name, $Str);
   next unless ($Name);
   ##
   ## $Name is defined, go ahead
   #next if ($Name =~ /_BASE$/);

   ## Special rule: skip MSMERR_ prefix definitions
   next if($Name =~ /^MSMERR_/);

   ## This log amount is very large!
   #dbg_printf ("[PP]%-16s: %-50s: %s\n", $File, $Name, $Str);

   $MsgIdByNameHash{$Name} = $Str;
   ExtractBase ($Str);
 }
 close (FILE);
}


##
## Step 2: Now search for all bases by iterating several times to find sub-bases.
## Using above example:
## Search for definition of "MM_BASE", "MMC_SUB_BASE", "FROM_MM" which may use sub-bases.
## For instance "FROM_MM" is based on "FROM_EL", so extract "FROM_EL" base which requires
## another pass to find its definition. I believe that two passes are enough.
##
my $NbPasses = 2;
dbg_print ("Step 2: Searching for all bases\n");

while ($NbPasses-- > 0) {
  dbg_print ("Pass \#$NbPasses\n");
  SearchForBases1();
}

## Check that all bases are defined, however not very relevant
## because they are unlikely to be real bases, but just some defines for other purposes.
## The script is not smart enough to discriminate between real bases for messages
## or of other purposes.
if ($Verbose) {
  foreach (keys %BaseByNameHash) {
    dbg_errorf ("%-50s: is not defined!\n", $_) if ($BaseByNameHash{$_} eq "");
  }
}

##
## Step 3: Now evaluate all message IDs by remplacing the string with their numerical definition.
##
dbg_print ("Step 3: evaluating definitions\n");

foreach (keys %MsgIdByNameHash) {
  my $Str = $MsgIdByNameHash{$_};
  ##
  ## we need 3 passes to remplace message with its definition which may itself contains
  ## another string definition until we get a numerical definition.
  $NbPasses = 20;
  while ($NbPasses-- > 0)
  {
    if($Str =~ /([A-Z_][A-Z0-9_]+).*/)
    {
      #if($BaseByNameHash{$1})
      if(exists $BaseByNameHash{$1})
      {
        $Str =~ s/([A-Z_][A-Z0-9_]+)/$BaseByNameHash{$1}/xe;
      }
    }
  }

  if(0)
  {
    ##
    ## Substitute bases with their definition
    ##
    $Str =~ s{
	      ([A-Z_][A-Z0-9_]+) ## look for words in upper case
	    }{
	      ## it's a word, so check if it's a known base, if so return its definition
	      ## otherwise return the word (which is likely to be a 0xAAAA number)
	      $BaseByNameHash{$1} ? "$BaseByNameHash{$1}" : $& ## $& = match
	    }xge;
  }

  ##
  ## get rid of (u8), (u16), (u32)
  $Str =~ s/\(u(8|16|32)\)//g;

  dbg_printf ("%-50s: %s\n", $_, $Str);

  my $ID = eval"$Str";
  if ($@) {
    ##
    ## The substituted string failed to be evaluated
    dbg_errorf("%-50s: cannot evaluate %s\n", $_, $Str);
    next;
  }

  if ($ID > $MaxID) {
    dbg_printf ("Ignoring ID %04x: too high\n",$ID);
    next;
  }

  if (exists $MsgIdByIdHash{$ID}) {
    ##
    ## A message having this ID already exists, so check if they only differ by VM_ prefix
    my $CurMsg = $MsgIdByIdHash{$ID};
    my $NewMsg = $_;

    $CurMsg =~ s/^VM_//;
    $NewMsg =~ s/^VM_//;
    if ($CurMsg eq $NewMsg) {
      ##
      ## they only differ by 'VM_', store the one without VM_ prefix
      $_ = $NewMsg;
    }
    else {
      dbg_errorf ("%-50s: (ID %04x): already exists, skip %s\n", $MsgIdByIdHash{$ID}, $ID, $_);
      next;
    }
  }

  if ($ID < $MinID) {
    ##
    ## Assume it's a timer so search for TIM in message name
    if (!/TIM/) {
      dbg_printf ("Ignoring ID %04x:$_, not a timer\n",$ID);
      next;
    }
  }

  ##
  ## Ok, store its numerical value
  $MsgIdByIdHash{$ID} = $_;
}

##
## Step 4: Wrap up job: write output file
##
dbg_print ("Step 4: wrap up job!\n");

if ($OutputFile) {
  open(OUT, ">$OutputFile") || die "Cannot create $OutputFile: $!";
}
else {
  open(OUT, ">-"); ## open OUT on STDOUT
}

sub AscendingSort { $a <=> $b }
foreach (sort AscendingSort keys %MsgIdByIdHash) {
  printf OUT "%04x %s\n", $_, $MsgIdByIdHash{$_};
}
close (OUT);

dbg_print ("We're done!\n");



sub ParseEnum1 {
    $_ = shift;
    my($name, $Str) = split(/=/);

    if (length($Str)) {
        $LastBase = $Str;
        $LastIndex = 0;
        $ParseEnumAllowed=1;
    }elsif ($ParseEnumAllowed) {
        $LastIndex++;
        $Str = "$LastBase + $LastIndex";
    }
    #dbg_printf("ParseEnum1 \"$name\",\"$Str\"\n");
    return ($name, $Str);

}

##### functions #############################################################################
##
## Search for base name in the given string:
## Search for #define XXXX YYYY and if XXXX is already defined, store YYYY definition for XXXX.
## Parse enums as well
## Input : void
## Return: void
##
sub SearchForBases1 {
    foreach (keys %BaseByNameHash) {
        if ($BaseByNameHash{$_} eq "") {
            $BaseByNameHash{$_} = $MsgIdByNameHash{$_};
        }
    }
}
sub SearchForBases {
  foreach $File (@FileList) {
        #open (FILE, $WorkDir.$File) or die "Cannot open file $WorkDir.$File : $!";
        open (FILE, $File) or die "Cannot open file $File : $!";
        #open (FILE, $File) or next;

    $ParseEnumAllowed=0;
    while (<FILE>) {
      chomp;
      s/\/\*.*//; ## remove comment /* at end of the line
      s/\/\/.*//; ## remove comment //

      if (/\#define\s+(\w+)\s+(.*)/) {
	if (exists $BaseByNameHash{$1}) {
 	    dbg_printf ("%-50s = %s\n", $1, $2);
 	    $BaseByNameHash{$1} = $2;
 	    ## perhaps base is based on sub bases...
 	    ExtractBase ($2);
	  }
	next;
      }
      my ($Name, $Str) = ParseEnum ($_);
      next unless ($Name);

      if (exists $BaseByNameHash{$Name}) {
	dbg_printf ("%-50s = %s\n", $Name, $Str);
	$BaseByNameHash{$Name} = $Str;
	ExtractBase ($Str);
      }
    }
    close (FILE);
  }
}

##
## Parses enums to find out "VM_XXXX," or "VM_XXXX = YYYY_BASE + ZZZZ,"
## or "XXXX = VM_YYYY_BASE + ZZZZ," (for Battery for instance)
## Enums which don't have a "VM_XXXX = YYYY_BASE + ZZZZ," are ignored
## as we assume they don't define RTK messages
##
## Input : file line string
## Return: (VM_XXXX, definition string) or void if nothing found.
## definition string is "YYYY_BASE + ZZZZ + Increment"
##
sub ParseEnum {
  $_ = shift;

   #if (/^\s*(VM_[A-Z0-9_]+)\s*(=\s*(\w*_BASE.*))?,/ or
   #    /^\s*([A-Z0-9_]+)\s*(=\s*(VM_\w*_BASE.*))?,/) {

   if (/^\s*(VM_[A-Z0-9_]+)\s*(=\s*(\w*_BASE.*))?,/ or
       /^\s*([A-Z0-9_]+)\s*(=\s*(VM_\w*_BASE.*))?,/ or
       # Fix the last line will not be parsed
       #/^\s*([A-Z0-9_]+)\s*(=\s*(VM_\w*_BASE.*))?/) {
       # Add for general types (and must precede the "last line" rule)
       /^\s*([A-Z0-9_]+)\s*(=\s*(\w*_BASE.*))?,/ or
       /^\s*([A-Z0-9_]+)\s*(=\s*(VM_\w*_BASE.*))?/) {
       #/^\s*([A-Z0-9_]+)\s*(=\s*(\w*_BASE.*))?,/) {

     my $Str;

     if ("$3" ne "") {
       ##
       ## it's a "VM_XXXX = YYYY_BASE [+ ZZZZ]," pattern, so save it for later use
       ## and allow parsing of rest of the enum
       $Str = $LastBase = $3;
       $LastIndex = 0;
       $ParseEnumAllowed=1;
     }
     elsif ($ParseEnumAllowed) {
       ##
       ## it's a single "VM_XXXX," pattern and parsing of current enum is allowed
       ## so build a pattern "VM_XXXXX = YYYYY + INDEX"
       $LastIndex++;
       $Str = "$LastBase + $LastIndex";
     }
     else {
       ## it's a single "VM_XXXXX," and parsing is not allowed as it's unlikely an enum
       ## for RTK message
       return;
     }

     return ($1, $Str);
   }

   if ($ParseEnumAllowed && /^\s*\}/) {
     ##
     ## Enum parsing is allowed and we found a terminating enum '}' so reset parsing.
     $ParseEnumAllowed = 0;
   }
}

sub ParseEnum_PP {
  $_ = shift;

  ## TEST
  #if(0)
  #{
  #  if(/API_ATI_MSG_COMMAND_RSP/)
  #  {
  #    my $foo = 0;
  #    $foo = 1;
  #  }
  #}

  #dbg_printf("ParseEnum_PP parsing: %s\n", $_);

  my $EnumStr;
  my $Str;
  my $ID;


  ## If merely a number
  ## API_ATI_MSG_COMMAND_RSP     = (u16) (0x3800) + (u16) (0x0400) + 0x0000,
  if (/^\s*([A-Z0-9_]+)\s*(=\s*([0-9A-Fa-f()xu+\s]*))?,?/)
  {
    #dbg_printf("ParseEnum_PP parsing match: %s: %s\n", $1, $2, $3);

    $EnumStr = $1;

    if("$3" ne "")
    {
      ## If can be directly evaluated, then we want it
      $Str = $3;

      ## (u16)(0x3800) + (u16)(0x0400) + 0x0000 -> (0x3800) + (0x0400) + 0x0000
      $Str =~ s/\(u(8|16|32)\)//g;
      $ID = eval"$Str";
      if($@)
      {
        #dbg_printf("ParseEnum_PP parsing eval string fail: %s\n", $Str);
        return;
      }

      ## Save it for later use
      $LastBase = $Str;
      $LastIndex = 0;
      $ParseEnumAllowed=1;
      #dbg_printf("ParseEnum_PP parsing start: %s, LastIndex = %d\n", $Str, $LastIndex);
    }
    elsif($ParseEnumAllowed)
    {
      $LastIndex++;
      $Str = "$LastBase + $LastIndex";
      #dbg_printf("ParseEnum_PP parsing allow: %s\n", $Str);
    }
    else
    {
      #dbg_printf("ParseEnum_PP parsing no match & not allowed\n");
      return;
    }

    #dbg_printf ("ParseEnum_PP parsing return: %s: %s\n", $EnumStr, $Str);
    return ($EnumStr, $Str);
  }

  if ($ParseEnumAllowed && /^\s*\}/)
  {
    ##
    ## Enum parsing is allowed and we found a terminating enum '}' so reset parsing.
    $ParseEnumAllowed = 0;
    #dbg_printf ("ParseEnum_PP parsing allowed turn off\n");
  }
}

##
## Parse the definition string to extract bases, e.g. given "XXXX + YYYY + 0xAAAA"
## it extracts and store the bases XXXX, YYYY to be search for later on.
##
## Input : definition string
## Return: void
##
sub ExtractBase {
  my $IdStr = shift; ## get first argument
  my $IdVar = shift;

  $IdStr =~ s/\s//g; ## remove any blank to ease 'split' below.

  my @SubIdList = split /\(|\)|\+|\|/, $IdStr; ## split string on (, ), + or |

  foreach (@SubIdList) {
    if (/^[A-Z_][A-Z0-9_]+/) {
      ## it's not a number (decimal or hex) nor an operator nor a space
      ## so it's a define value we have to store to search for later
      if (not exists $BaseByNameHash{$_}) {
	## this base does not exist yet so define it to empty string
	$BaseByNameHash{$_}=$IdVar;
	dbg_print ("                  Adding base '$_'\n");
      }
    }
  }
}

sub dbg_print {
  if ($Verbose >= 2){ print shift; }
}

sub dbg_printf {
  if ($Verbose >= 2) { printf @_; }
}

sub dbg_error {
  if ($Verbose >= 1) {print "ERROR: ", shift;}
}

sub dbg_errorf {
  if ($Verbose >= 1) {printf (join ("", "ERROR: ", shift), @_);}
}

sub PrintHelp {
  print ("Script to get RTK message ID from header files\n");
  print ("RDO - MStar France - $Date - version $Version\n");
  print ("Options:\n");
  print ("-o<file>  : ouput message IDs to <file>, default STDOUT\n");
  print ("-i<dir>   : parse files in <dir>, default is current dir (.)\n");
  print ("-v<level> : verbose level:\n");
  print ("            0: no information is spitted out\n");
  print ("            1: only errors/warning are shown\n");
  print ("            2: adds more debug information\n");
  print ("-h        : print this help\n");
}

sub basename_unix{
    my $path=shift;
    if($path =~ m/^.*\/(.*)/){
        return $1;
    }else{
        return $path;
    }
}

sub dirname{
	my $path = shift;
	$path =~ s/\/[^\/]*$//;
	return($path);
}

