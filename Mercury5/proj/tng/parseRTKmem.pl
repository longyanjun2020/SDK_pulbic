#!/usr/bin/perl 
use integer;

#Section: Constant value declaration

$FALSE = 0;
$TRUE = 1;
$PoolGuard = 6;
$PoolAmount = 6;
$HeapGuard = 6;
$HeapLstSizePole = 3;
$PoolUsePole = 4;
$PoolSizePole = 1;
$PoolGroupIdt = "Stack Pool Group";
$HeapUsageIdt = "Heap Usage Histogram";
$HeapListIdt = "Heap Blocks List";
$HeapTotalAllocSizePole = 3;
$FileOutName = scalar(localtime);
$FileOutName =~ s# #_#g;
$FileOutName =~ s#\:#-#g;
$FileOutName = $FileOutName . "_Out.txt";


#Section: Varable declaration
$FStartName;
$FEndName;
@StartContent =();
@EndContent =();

#Start File data
@StPool =();
@StPool0=(1...6);
@StPool1=(1...6);
@StPool2=(1...6);
@StPool3=(1...6);
@StPool4 =(1...6);
@StPool5=(1...6);
@StPoolNum = (\@StPool0,\@StPool1,\@StPool2,\@StPool3,\@StPool4,\@StPool5);

@StHeapSts =();

@StHeapLst =();


#End File data
@EndPool =();
@EndHeapSts= ();
@EndHeapLst =();
$EndPoolNum[$PoolAmount][$PoolGuard];

@EndPool0=(1...6);
@EndPool1=(1...6);
@EndPool2=(1...6);
@EndPool3=(1...6);
@EndPool4 =(1...6);
@EndPool5=(1...6);
@EndPoolNum = (\@EndPool0,\@EndPool1,\@EndPool2,\@EndPool3,\@EndPool4,\@EndPool5);

#Diff
@HeapFree = ();
@HeapAlloc = ();



#Temporary Varable
$tmpCnt = 0;
$TotalPoolUse = 0;

#Input Check & Read File
if(2 ne @ARGV)
{
    die "Error: ./parseRTKmem.pl argv1(File Name Before opeartion) argv2(File Name After operation)";
}
else
{
    $FStartName = $ARGV[0];
    $FEndName = $ARGV[1];
}
unless(open(FileStartFd, "< " . $FStartName))
{
    die "Error: Open " . $FStartName . " Failed";
}

unless(open(FileEndFd, "< " . $FEndName))
{
    die "Error: Open " . $FEndName . " Failed";
}
push(@StartContent,<FileStartFd>);

push(@EndContent,<FileEndFd>);
close(FileStartFd);
close(FileEndFd);

sub BothPrint
{
    print ($_[0] . "\r\n");
    print FileOutFd ($_[0] . "\r\n");
}

&_parse_data_out(\@StartContent,\@StPool,\@StHeapSts,\@StHeapLst,\@StPoolNum);
&_parse_data_out(\@EndContent,\@EndPool,\@EndHeapSts,\@EndHeapLst,\@EndPoolNum);


#Pool comparison 
foreach(@StPoolNum)
{
    $srcPool = $_;
    $tgtPool = $EndPoolNum[$tmpCnt];
    $tmpCnt ++;
    push @DiffPool,@$tgtPool[$PoolUsePole] - @$srcPool[$PoolUsePole];
    $TotalPoolUse += (@$tgtPool[$PoolUsePole] - @$srcPool[$PoolUsePole]) * @$tgtPool[$PoolSizePole];
}

#Heap Status Calculation

#Heap List Comparison and Calculation
    #Pick the free members
&_diff_heap(\@StHeapLst,\@EndHeapLst,\@HeapFree);
$TotalFree = &_diff_heap_calculation(\@HeapFree);

    #Pick the new allocated members
&_diff_heap(\@EndHeapLst,\@StHeapLst,\@HeapAlloc);
$TotalAlloc = &_diff_heap_calculation(\@HeapAlloc);

#Show Heap Slot Result
unless(open(FileOutFd, "> " . $FileOutName))
{
    die "Error: Open " . $FileOutName . " Failed";
}
$tmp_Cnt = 0;
BothPrint"===== Pool ====";
foreach(@DiffPool)
{
    BothPrint"Pool No." . $tmp_Cnt . " use " . $_ . " Blocks";
}
BothPrint"Total Pool memory use " . $TotalPoolUse . " Bytes";
BothPrint"===== Heap ====";
BothPrint"Free Heap size is " . $TotalFree . " Bytes" ; 
BothPrint"Feature's Allocated Heap size is " . $TotalAlloc . " Bytes" ; 
#BothPrint"[Calculated From table]The Total size in use is " . ($TotalAlloc - $TotalFree) . " Bytes ";
BothPrint"The Total size used in Heap is " . ($EndHeapSts[$HeapTotalAllocSizePole] - $StHeapSts[$HeapTotalAllocSizePole]) . " Bytes ";
BothPrint"The Total size used in Heap & Pool is " . ($EndHeapSts[$HeapTotalAllocSizePole] - $StHeapSts[$HeapTotalAllocSizePole] + $TotalPoolUse) . " Bytes ";

BothPrint"===== List  ====";
&print_title("Free Heap Slot List",\@StHeapLst,\@HeapFree);
BothPrint "";
&print_title("Allocated Heap Slot List",\@EndHeapLst,\@HeapAlloc);

close(FileOutFd);

sub _diff_heap_calculation
{
    my $DiffheapLst = $_[0];
    my $tmpStr = 0;
    my @tmpAry = ();
    my $Acc = 0;
    foreach(@$DiffheapLst)
    {
        $tmpStr = $_;
        @tmpAry = split/\|/,$tmpStr;
        $tmpAry[$HeapLstSizePole] =~ s#\s+##g;
        $Acc += $tmpAry[$HeapLstSizePole]; 
    }
    return $Acc;
}

sub print_title
{
    my $Title = $_[0];
    my $heapLst = $_[1];
    my $heapprint = $_[2];
    chomp @$heapLst[0];
    chomp @$heapLst[1];
    chomp @$heapLst[2];
    BothPrint $Title."";
    BothPrint @$heapLst[0]."";
    BothPrint @$heapLst[1]."";
    BothPrint @$heapLst[2]."";
    foreach(@$heapprint)
    {
        BothPrint$_;
    }
}


sub _diff_heap
{
    my $SrcHeap = $_[0];
    my $DstHeap = $_[1];
    my $DiffMembers = $_[2];
    my $diff = $TRUE;
    my $src = 0;
    my $tgt = 0;
    foreach $src(@$SrcHeap)
    {
        $diff = $TRUE;
        foreach $tgt(@$DstHeap)
        {
            if($src eq $tgt)
            {
                $diff = $FALSE;
                last;
            }
        }
        if($TRUE eq $diff )
        {
            if($src =~ m#FREE#)
            {
                next;
            }
            push @$DiffMembers, $src;
        }
    } 
}


#print @StartContent;
#print @EndContent;

#FileContent Error Check

#Sub Function Declaration
sub _parse_data_out #parse needed data out
{
    my   $ary = $_[0];
    my   $Pool = $_[1];
    my   $HeapStatus = $_[2];
    my   $HeapList = $_[3];
    my   $PoolNum = $_[4];
#    my   $HeapLstNum = $_[5];
    my   $flag = undef;
    my   $flag_str = "INIT";
    my   $Poolflag_str = 0;
    my   @tmpPoolNum = ();
    my   $tmpMod = 0;
    my   @tmp = ();
    while(($_= shift(@$ary)))
    {
#        chomp($_);
        unless(m#\d|\w#)
        {
            next;
        }
            
        s#^(.*RTK\[\d+\])# #;
        if(m#$PoolGroupIdt#)
        {
            $flag_str = $PoolGroupIdt;
            $tmpMod = 0;
        }
        elsif(m#$HeapListIdt#)
        {
            $flag_str = $HeapListIdt;
            $tmpMod = 0;
        }
        elsif(m#$HeapUsageIdt#)
        {
            $flag_str = $HeapUsageIdt;
            $tmpMod = 0;
        }

        if($flag_str eq $PoolGroupIdt)
        {
            chomp($_);
            if((m#--+--#))
            {
                push(@$Pool,$_);
            }
            @tmp = split/\|/ , $_;
            if($PoolGuard eq scalar(@tmp))
            {
                push(@$Pool,$_);
                my $tmpStr = $_;
                $tmpStr =~ s#\s+##g;
                @tmp = split/\|/ , $tmpStr;
                if(($tmp[0] =~ m#\d+#))
                {
                    my $loc = @$PoolNum[$tmpMod]; 
                    @$loc = @tmp;
                    $tmpMod++;
                }
            }
        }
        elsif($flag_str eq $HeapListIdt)
        {
            chomp($_);
            if((m#--+--#))
            {
                push(@$HeapList,$_);
            }
            @tmp = split/\|/ , $_;
            if($HeapGuard eq scalar(@tmp))
            {
                push(@$HeapList,$_);

            }
        }
        elsif($flag_str eq $HeapUsageIdt)
        {
            chomp($_);
            s#\s+##g;
            if(m#\b=(\d+)#)
            {
#set the number
                s#\w+=##;
                push(@$HeapStatus,$_);
            }
            
        }
    }
}
no integer;
