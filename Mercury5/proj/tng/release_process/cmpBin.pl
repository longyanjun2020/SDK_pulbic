#!/usr/bin/perl

use warnings;
use strict;

sub compareBin()
{
    my @binFileList = @{$_[0]};
    my $max = $_[1];
    my @chipPathList = @{$_[2]};
    my @cmnBinList = @{$_[3]};
    my @noncmnBinList = @{$_[4]};
    my $REPORT = $_[5];
    my $idx;
    my $i;
    my $j;
    my $diff;
    my $counter;
    my $tmpPath1;
    my $tmpPath2;
    my $lineData1;
    my $lineData2;
    my $tmpStr3;
    
    @cmnBinList = ();
    @noncmnBinList = ();
    
    print "compare bin files:\n";
    print $REPORT "\ncompare bin files:\n";
    for($i = 0; $i < $max; $i++)
    {
        $j = $i + 1;
        print "[$j/$max]$binFileList[0][$i]\n";
        print $REPORT "[$j/$max]$binFileList[0][$i]\n";
        $diff = 0;
        for($idx = 0; $idx < $#chipPathList; $idx++)
        {
            if($binFileList[$idx][$i] ne $binFileList[$idx+1][$i])
            {
                print "ERROR file does not exist!! Lib:$binFileList[$idx][$i]/$binFileList[$idx+1][$i]\n";
                print $REPORT "ERROR file does not exist!! Lib:$binFileList[$idx][$i]/$binFileList[$idx+1][$i]\n"; 
                exit 1;
            }
            # file1
            $tmpPath1 = $chipPathList[$idx];
            $tmpPath1 = $tmpPath1."/$binFileList[$idx][$i].txt";
            if( -e $tmpPath1)
            {
                ;
            }
            else
            {
                print "ERROR: cannot find the file. File: $tmpPath1\n";
                print $REPORT "ERROR: cannot find the file. File: $tmpPath1\n";
                exit 1;
            }
            # file2
            $tmpPath2 = $chipPathList[$idx+1];
            $tmpPath2 = $tmpPath2."/$binFileList[$idx+1][$i].txt";
            if( -e $tmpPath2)
            {
                ;
            }
            else
            {
                print "ERROR: cannot find the file. File: $tmpPath2\n";
                print $REPORT "ERROR: cannot find the file. File: $tmpPath2\n";
                exit 1;
            }
    
            $counter = 0;
            open(FILE1, "<$tmpPath1") or die "cannot read \"$tmpPath1\" file\n";
            open(FILE2, "<$tmpPath2") or die "cannot read \"$tmpPath2\" file\n";
            while ($lineData1 = <FILE1>)
            {
                $counter += 1;
                if($lineData2 = <FILE2>)
                {
                    if($lineData1 eq $lineData2)
                    {
                        #  Summary
                        if($lineData1 =~ /^  Summary\r$/)
                        {
                            last;
                        }
                        else
                        {
                            next;
                        }
                    }
                    #  4E73A605 time date stamp Sat Sep 17 03:39:49 2011
                    if($lineData1 =~ /^ +[0-9a-fA-F]{8} time date stamp (.*?) (\d+)\r$/)
                    {
                        if($lineData2 =~ /^ +[0-9a-fA-F]{8} time date stamp (.*?) (\d+)\r$/)
                        {
                            next;
                        }
                    }                    
=cut                    
                    if($binFileList[0][$i] =~ /tencentmcareadp\.lib/)
                    {
                        #   000000E5: B8 00 00 00 00     mov         eax,offset $SG8298
                        if($lineData1 =~ /^ +[0-9a-fA-F]{8}: B8 00 00 00 00     mov         eax,offset \$SG(\d+)\r$/)
                        {
                            if($lineData2 =~ /^ +[0-9a-fA-F]{8}: B8 00 00 00 00     mov         eax,offset \$SG(\d+)\r$/)
                            {
                                next;
                            }
                        }
                     }
=cut                     
=cut                
                    #  00000033: E9 D3 01 00 00     jmp         0000020B
                    if($lineData1 =~ /^ +[0-9a-fA-F]{8}: E(.*?)jmp         [0-9a-fA-F]{8}\r$/)
                    {
                        if($lineData2 =~ /^ +[0-9a-fA-F]{8}: E(.*?)jmp         [0-9a-fA-F]{8}\r$/)
                        {
                            next;
                        }
                    }                
=cut                            
                    #  000000A6: EB 6F              jmp         $Done$14533
                    if($lineData1 =~ /^(.*?)jmp         \$(.*?)\$\d+\r$/)
                    {
                        $tmpStr3 = $1;
                        if($lineData2 =~ /^(.*?)jmp         \$(.*?)\$\d+\r$/)
                        {
                            if($tmpStr3 =~ $1)
                            {
                                next;
                            }
                        }
                    }
                    #  00000122: 0F 87 FD 03 00 00  ja          $err$11572
                    if($lineData1 =~ /^(.*?)ja          \$(.*?)\$\d+\r$/)
                    {
                        $tmpStr3 = $1;
                        if($lineData2 =~ /^(.*?)ja          \$(.*?)\$\d+\r$/)
                        {
                            if($tmpStr3 =~ $1)
                            {
                                next;
                            }
                        }
                    }                
                    #  000002F9: 0F 82 71 01 00 00  jb          $sabort$9216
                    if($lineData1 =~ /^(.*?)jb          \$(.*?)\$\d+\r$/)
                    {
                        $tmpStr3 = $1;
                        if($lineData2 =~ /^(.*?)jb          \$(.*?)\$\d+\r$/)
                        {
                            if($tmpStr3 =~ $1)
                            {
                                next;
                            }
                        }
                    }                
                    #  00000079: 74 13              je          $Error$14582
                    if($lineData1 =~ /^(.*?)je          \$(.*?)\$\d+\r$/)
                    {
                        $tmpStr3 = $1;
                        if($lineData2 =~ /^(.*?)je          \$(.*?)\$\d+\r$/)
                        {
                            if($tmpStr3 =~ $1)
                            {
                                next;
                            }
                        }
                    }
                    #  00001BE5: 0F 8F 9F 08 00 00  jg          $EndOfBlock$8459
                    if($lineData1 =~ /^(.*?)jg          \$(.*?)\$\d+\r$/)
                    {
                        $tmpStr3 = $1;
                        if($lineData2 =~ /^(.*?)jg          \$(.*?)\$\d+\r$/)
                        {
                            if($tmpStr3 =~ $1)
                            {
                                next;
                            }
                        }
                    }            
                    #  00000560: 0F 83 6C 06 00 00  jae         $LYRICPARSER_END$9122
                    if($lineData1 =~ /^(.*?)jae         \$(.*?)\$\d+\r$/)
                    {
                        $tmpStr3 = $1;
                        if($lineData2 =~ /^(.*?)jae         \$(.*?)\$\d+\r$/)
                        {
                            if($tmpStr3 =~ $1)
                            {
                                next;
                            }
                        }
                    }     
                    #  000009F8: 0F 86 A4 FE FF FF  jbe         $SEARCH_NEXT_TIMEINFO$9145
                    if($lineData1 =~ /^(.*?)jbe         \$(.*?)\$\d+\r$/)
                    {
                        $tmpStr3 = $1;
                        if($lineData2 =~ /^(.*?)jbe         \$(.*?)\$\d+\r$/)
                        {
                            if($tmpStr3 =~ $1)
                            {
                                next;
                            }
                        }
                    }       
                    #  00000100: 0F 85 A6 00 00 00  jne         $CONFIG_END$6411
                    if($lineData1 =~ /^(.*?)jne         \$(.*?)\$\d+\r$/)
                    {
                        $tmpStr3 = $1;
                        if($lineData2 =~ /^(.*?)jne         \$(.*?)\$\d+\r$/)
                        {
                            if($tmpStr3 =~ $1)
                            {
                                next;
                            }
                        }
                    }
                    #  0000014F: 0F 8E 59 03 00 00  jle         $ID3_EMPTY$11323
                    if($lineData1 =~ /^(.*?)jle         \$(.*?)\$\d+\r$/)
                    {
                        $tmpStr3 = $1;
                        if($lineData2 =~ /^(.*?)jle         \$(.*?)\$\d+\r$/)
                        {
                            if($tmpStr3 =~ $1)
                            {
                                next;
                            }
                        }
                    }                
                    #0000017F: 0F 8D A9 00 00 00  jge         $Done$14666
                    if($lineData1 =~ /^(.*?)jge         \$(.*?)\$\d+\r$/)
                    {
                        $tmpStr3 = $1;
                        if($lineData2 =~ /^(.*?)jge         \$(.*?)\$\d+\r$/)
                        {
                            if($tmpStr3 =~ $1)
                            {
                                next;
                            }
                        }
                    }         
                    #$Done$14533:                
                    if($lineData1 =~ /^\$(.*)\$\d+:\r$/)
                    {
                        $tmpStr3 = $1;
                        if($lineData2 =~ /^\$(.*)\$\d+:\r$/)
                        {
                            if($tmpStr3 =~ $1)
                            {
                                next;
                            }                        
                        }
                    }
                    
                    if($counter eq 5)
                    {
                        if($lineData1 =~ /^Dump of file (.*)\r$/)
                        {
                            if($lineData1 =~ /^Dump of file (.*)\r$/)
                            {
                                next;
                            }
                        }
                    }
                       
                    print "  Check $chipPathList[$idx] and $chipPathList[$idx+1]";
                    print "--> Diff at line: $counter\n";
                    print "  File1: $lineData1";
                    print "  File2: $lineData2\n";
                    print $REPORT "  Check $chipPathList[$idx] and $chipPathList[$idx+1]";
                    print $REPORT "--> Diff at line: $counter\n";
                    print $REPORT "  File1: $lineData1";
                    print $REPORT "  File2: $lineData2\n";
                    $diff = 1;
                    last;
                }
                else
                {
                    print " --> Diff! \n";
                    print "File1: $tmpPath1 $idx\n";
                    print "File2: $tmpPath2";
    
                    print $REPORT " --> Diff! \n";
                    print $REPORT "File1: $tmpPath1 $idx\n";
                    print $REPORT "File2: $tmpPath2";
                    $diff = 1;
                    last;
                }
            }	
    	    close(FILE1);
    	    close(FILE2);
    	    if($diff == 1)
    	    {
    	        last;
    	    }
    	    else
    	    {
    	        print "  Check $chipPathList[$idx] and $chipPathList[$idx+1] --> OK!\n";
    	        print $REPORT "  Check $chipPathList[$idx] and $chipPathList[$idx+1] --> OK!\n";
    	        
    	        ## del asm text files
    	        #$tmpPath1 = "rm -f -r ";
                #$tmpPath1 = $tmpPath1.$chipPathList[$idx];
                #$tmpPath1 = $tmpPath1."/$binFileList[$idx][$i].txt";
                #system($tmpPath1);
    	        #$tmpPath1 = "rm -f -r ";
                #$tmpPath1 = $tmpPath1.$chipPathList[$idx+1];
                #$tmpPath1 = $tmpPath1."/$binFileList[$idx+1][$i].txt";
                #system($tmpPath1);                
    	    }
        }
        
        if($diff == 0)
        {
            push @cmnBinList, $binFileList[0][$i];
        }
        else
        {
            push @noncmnBinList, $binFileList[0][$i];
        }
    }
    
    @{$_[3]} = @cmnBinList; # call by reference
    @{$_[4]} = @noncmnBinList; # call by reference
}

$;
