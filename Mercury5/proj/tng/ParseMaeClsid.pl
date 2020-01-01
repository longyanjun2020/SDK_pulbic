die("Usage: ParseMaeClsid\n") if @ARGV != 10;

# open file handle
$input_file = shift(@ARGV);
$input_state_file = shift(@ARGV);
#$input_attr_file = shift(@ARGV);
$input_event_file = shift(@ARGV);
$input_trans_file = shift(@ARGV);
$output_clsidfile = shift(@ARGV);
$output_stateidfile = shift(@ARGV);
#$output_attridfile = shift(@ARGV);
$output_modeidfile = shift(@ARGV);
$output_eventidfile = shift(@ARGV);
$output_transidfile = shift(@ARGV);
$input_dir = shift(@ARGV);
	
$inLine;
$number = 0;
$prefixed;
$keyword;
$fileKeyword;
$dataIndex = 0;
$inData;
$fileName;
$clsIdStr;

@lineTokens;
@dataArray;
@sortDataArray;

# open file handle
open(INPUT_FILE, "<$input_file")
	or die ("Input file $input_file not found\n");

open(OUTPUT_FILE, ">$output_clsidfile")
	or die("Output file $output_clsidfile can not be created\n");
	
# read ini settings
# create class id table
$keyword = "MAE_ClassInfo_t";
$inLine = <INPUT_FILE>;
while ($inLine ne "")
{
	chop($inLine);

  if ($inLine =~ /^\s*extern\s+const\s+$keyword\s+.+/)
  { 	 	 	 	 	
  	$inLine = <INPUT_FILE>;
  	 	
		while ($inLine ne "")
  	{  		
  		chop($inLine);
  		
		 	if($inLine !~ /^\s*\{\s*/)
  		{
  			if ($inLine =~ /^\s*\}\s*\;\s*/)
  			{
  				last;
  			}
  			else
  			{
  				if ($inLine =~ /^\s*([0-9a-zA-Z_]+\s*=?\s*[0-9a-fxA-FX]*).*\s*/)
					{			
						$inLine = $1;						
						@lineTokens = split(/\s*=\s*/, $inLine);
						if ( @lineTokens > 1 )
						{
							$number = &converStringToInteger($lineTokens[1]);
							$buffer = sprintf("%04x %s", $number, $lineTokens[0]);	
						}
						else
						{
							$buffer = sprintf("%04x %s", $number, $inLine);	
						}
						push(@dataArray, $buffer);
						$number ++;
					}
				}
			}
			$inLine = <INPUT_FILE>;
		}
	}
	$inLine = <INPUT_FILE>;
}

# sort and print out file
@sortDataArray = sort(@dataArray);
while (	$dataIndex < @sortDataArray )
{
	$inData = $sortDataArray[$dataIndex];
	print(OUTPUT_FILE "$inData\n");
	$dataIndex = $dataIndex + 1;
}

close(INPUT_FILE);
close(OUTPUT_FILE);

# open file handle
open(INPUT_FILE, "<$input_state_file")
	or die ("Input file $input_state_file not found\n");

open(OUTPUT_FILE, ">$output_stateidfile")
	or die("Output file $output_stateidfile can not be created\n");
	
# read ini settings
# create state id table
$keyword = "APM_ST_";
$inLine = <INPUT_FILE>;
while ($inLine ne "")
{
	chop($inLine);
  if ($inLine =~ /^\s*($keyword[0-9a-zA-Z_]+)\s*\=\s*([0-9a-fA-FxX]+).*/)
  { 	 	 	 	 	
			$number = &converStringToInteger($2);
			$buffer = sprintf("%04x %s", $number, $1);	
			print(OUTPUT_FILE "$buffer\n");
			$number ++;
	}
	elsif ($inLine =~ /^\s*($keyword[0-9a-zA-Z_]+).*/)
	{
		$buffer = sprintf("%04x %s", $number, $1);	
		print(OUTPUT_FILE "$buffer\n");
		$number ++;
	}

	$inLine = <INPUT_FILE>;
}

close(INPUT_FILE);
close(OUTPUT_FILE);

# open file handle
#open(INPUT_FILE, "<$input_attr_file")
#	or die ("Input file $input_attr_file not found\n");
#
#open(OUTPUT_FILE, ">$output_attridfile")
#	or die("Output file $output_attridfile can not be created\n");
#
# read ini settings
# create attribute id table
#$keyword = "APMF_";
#$inLine = <INPUT_FILE>;
#@attrTempTable;
#while ($inLine ne "")
#{
#	chop($inLine);
#  if ($inLine =~ /^\s*($keyword[0-9a-zA-Z_]+)\s*\=\s*([0-9a-fA-FxX]+).*/)
#  { 	 	 	 	 	
#			$number = &converStringToInteger($2);
#			$buffer = sprintf("%04x %s", $number, $1);	
#			push(@attrTempTable, $buffer);
#			$number ++;
#	}
#	elsif ($inLine =~ /^\s*($keyword[0-9a-zA-Z_]+).*/)
#	{
#		$buffer = sprintf("%04x %s", $number, $1);	
#		push(@attrTempTable, $buffer);
#		$number ++;
#	}
#
#	$inLine = <INPUT_FILE>;
#}
#
#close(INPUT_FILE);
#
# create all case attribute id table
#$dataIndex = 0;
#$dataCount = 0;
#@dataTokens;
#$attrTableSize = @attrTempTable;
#$breakToNext = 0;
#while ($dataIndex < $attrTableSize)
#{
#	$inData = $attrTempTable[$dataIndex];
#	@lineTokens = split(/\s+/, $inData);
#	$number = &converStringToInteger("0x".$lineTokens[0]);
#	
#	$buffer = sprintf("%04x %s", $number, $lineTokens[1]);
#	push(@attrSortTable, $buffer);
#		
#	if ($number < 65535 && $dataIndex != ($attrTableSize - 1))
#	{
#		for ($levelCount = 1; $levelCount < $attrTableSize; $levelCount++)
#		{
#			for ($dataCount = $dataIndex + 1; $dataCount < $attrTableSize; $dataCount++)
#			{
#				$numberTemp = $number;
#				$breakToNext = 0;
#				for ($joinCount = 0; $joinCount < $levelCount; $joinCount++)
#				{
#					if ($dataCount + $joinCount < $attrTableSize)
#					{
#						@dataTokens = split(/\s+/, $attrTempTable[($dataCount + $joinCount)]);
#						$localTempNumber = &converStringToInteger("0x".$dataTokens[0]);
#						if ( $localTempNumber < 65535 )
#						{
#							$numberTemp = $numberTemp + $localTempNumber;
#						}
#						else
#						{
#							$breakToNext = 1;
#							last;
#						}
#					}
#					else
#					{
#						$breakToNext = 1;
#						last;
#					}
#				}
#				
#				if ($breakToNext == 1)
#				{
#					last;
#				}
#				
#				$strTemp = $lineTokens[1];
#				for ($joinCount = 0; $joinCount < $levelCount; $joinCount++)
#				{
#					if ($dataCount + $joinCount < $attrTableSize)
#					{
#						@dataTokens = split(/\s+/, $attrTempTable[($dataCount + $joinCount)]);
#						$localTempNumber = &converStringToInteger("0x".$dataTokens[0]);
#						if ( $localTempNumber < 65535 )
#						{
#							$strTemp = $strTemp . "|" . $dataTokens[1];
#						}
#						else
#						{
#							$breakToNext = 1;
#							last;
#						}
#					}
#					else
#					{
#						$breakToNext = 1;
#						last;
#					}
#				}
#				
#				if ($breakToNext == 1)
#				{
#					last;
#				}
#				
#				if ($numberTemp != $number)
#				{
#					$buffer = sprintf("%04x %s", $numberTemp, $strTemp);
#					push(@attrSortTable, $buffer);
#				}
#			}
#		}
#	}
#	$dataIndex = $dataIndex + 1;
#}
#
# sort and print out file
#@attrTempTable = sort(@attrSortTable);
#$dataIndex = 0;
#while (	$dataIndex < @attrTempTable )
#{
#	$inData = $attrTempTable[$dataIndex];
#	print(OUTPUT_FILE "$inData\n");
#	$dataIndex = $dataIndex + 1;
#}
#
#close(OUTPUT_FILE);

# open file handle
open(OUTPUT_FILE, ">$output_modeidfile")
	or die("Output file $output_modeidfile can not be created\n");

# Fetch class id from output file and find the header file
# to create mode table
$dataIndex = 0;
$keyword = "_MODE_";
$prefixed = "#define";
while ( $dataIndex < @sortDataArray )
{
	$inData = $sortDataArray[$dataIndex];
	
	@lineTokens = split(/\s+/, $inData);
	if ( @lineTokens > 1 )
	{
		$fileName = &converClsIdToFileName($lineTokens[1]);
		
		$fileKeyword = "c" . $fileName . $keyword;
    $fileName = $input_dir . "mmi_" . $fileName . "_sm.h";    
    if (open(INPUT_FILE, "<$fileName"))
    {
    	$clsIdStr = "0x" . $lineTokens[0];
    	$inLine = <INPUT_FILE>;
			while ($inLine ne "")
			{
				chop($inLine);
				if ($inLine =~ /^\s*$prefixed\s+($fileKeyword[0-9a-zA-Z_]+)\s+([0-9]+)\s*/)
				{
					$number = (&converStringToInteger($clsIdStr) * 65536) + $2;
					$buffer = sprintf("%08x %s", $number, $1);	
					print(OUTPUT_FILE "$buffer\n");
				}
				$inLine = <INPUT_FILE>;
			}
    	close(INPUT_FILE);
    }
	}
	$dataIndex = $dataIndex + 1;
}

close(OUTPUT_FILE);

# open file handle
open(OUTPUT_FILE, ">$output_eventidfile")
	or die("Output file $output_eventidfile can not be created\n");

# Fetch class id from output file and find the header file
# to create event table
$dataIndex = 0;
$prefixed = "#define";
$eachFileName;
while ( $dataIndex < @sortDataArray )
{
	$inData = $sortDataArray[$dataIndex];
	
	@lineTokens = split(/\s+/, $inData);
	if ( @lineTokens > 1 )
	{
		$fileName = &converClsIdToFileName($lineTokens[1]);
		$clsIdStr = "0x" . $lineTokens[0];
		
		#create mae event table from mae_event.h
		$keyword = "MAE_EVT_";
		if (open(INPUT_FILE, "<$input_event_file"))
    {
    	$inLine = <INPUT_FILE>;
			while ($inLine ne "")
			{
				chop($inLine);
				if ($inLine =~ /^($keyword[0-9a-zA-Z_]+)\s+\=\s+\(*$lineTokens[1]\s+\<\<\s+16\)\s*\+\s*([0-9a-fA-FxX]+)\)?\s*,\s*/)
				{
					$number = (&converStringToInteger($clsIdStr) * 65536) + &converStringToInteger($2);
					$buffer = sprintf("%08x %s", $number, $1);	
					print(OUTPUT_FILE "$buffer\n");
				}
				$inLine = <INPUT_FILE>;
			}
    	close(INPUT_FILE);
    }
		
		#create external event table for this file
		$keyword = "_EVT_";
		$fileKeyword = $fileName . $keyword;
    $eachFileName = $input_dir . "mmi_" . $fileName . ".h";    
    if (open(INPUT_FILE, "<$eachFileName"))
    {
    	$inLine = <INPUT_FILE>;
			while ($inLine ne "")
			{
				chop($inLine);
				if ($inLine =~ /^\s*$prefixed\s+($fileKeyword[0-9a-zA-Z_]+)\s+\(?\s*$lineTokens[1]\s*\<\<\s*[0-9]+\s*\|\s*([0-9]+)\s*\)?\s*/)
				{
					$number = (&converStringToInteger($clsIdStr) * 65536) + $2;
					$buffer = sprintf("%08x %s", $number, $1);	
					print(OUTPUT_FILE "$buffer\n");
				}
				$inLine = <INPUT_FILE>;
			}
    	close(INPUT_FILE);
    }
		
		#create internal event table for this file
		$keyword = "_IEVT_";
		$fileKeyword = $fileName . $keyword;
    $eachFileName = $input_dir . "mmi_" . $fileName . "_sm.h";    
    if (open(INPUT_FILE, "<$eachFileName"))
    {
    	$inLine = <INPUT_FILE>;
			while ($inLine ne "")
			{
				chop($inLine);
				if ($inLine =~ /^\s*$prefixed\s+($fileKeyword[0-9a-zA-Z_]+)\s+\(?\s*$lineTokens[1]\s*\<\<\s*[0-9]+\s*\|\s*([0-9]+)\s*\)?\s*/)
				{
					$number = (&converStringToInteger($clsIdStr) * 65536) + $2;
					$buffer = sprintf("%08x %s", $number, $1);	
					print(OUTPUT_FILE "$buffer\n");
				}
				$inLine = <INPUT_FILE>;
			}
    	close(INPUT_FILE);
    }
	}
	$dataIndex = $dataIndex + 1;
}

close(OUTPUT_FILE);

# open file handle
open(INPUT_FILE, "<$input_trans_file")
	or die ("Input file $input_trans_file not found\n");

open(OUTPUT_FILE, ">$output_transidfile")
	or die("Output file $output_transidfile can not be created\n");
	
# read ini settings
# create state id table
$keyword = "TRANS_TYPE_";
$inLine = <INPUT_FILE>;
while ($inLine ne "")
{
	chop($inLine);
  if ($inLine =~ /^\s*($keyword[0-9a-zA-Z_]+)\s*\=\s*([0-9a-fA-FxX]+).*/)
  { 	 	 	 	 	
			$number = &converStringToInteger($2);
			$buffer = sprintf("%04x %s", $number, $1);	
			print(OUTPUT_FILE "$buffer\n");
			$number ++;
	}
	elsif ($inLine =~ /^\s*($keyword[0-9a-zA-Z_]+).*/)
	{
		$buffer = sprintf("%04x %s", $number, $1);	
		print(OUTPUT_FILE "$buffer\n");
		$number ++;
	}

	$inLine = <INPUT_FILE>;
}

close(INPUT_FILE);
close(OUTPUT_FILE);

# convert string to integer
sub converStringToInteger
{
	my ($tempStr) = @_;
	my ($tempNumLen) = 0;
	my ($tempNum) = 0;
	my ($tempDigit) = 0;
			
	if ($tempStr =~ /^\s*0[xX]([0-9a-fA-F]+).*\s*/)
	{
		#remove 0x characters
		$tempStr = $1;
		$tempNumLen = length($tempStr);
		while ($tempNumLen > 0)
		{
			$tempDigit = substr($tempStr, 0, 1);
			$tempDigit = &converAFToInteger($tempDigit);
			$tempNum = ($tempNum * 16) + $tempDigit;
			$tempStr = substr($tempStr, 1);
			$tempNumLen = length($tempStr);
		}
	}
	else
	{
		if ($tempStr =~ /^\s*([0-9]+).*\s*/)
		{
			$tempStr = $1;
			$tempNumLen = length($tempStr);
			while ($tempNumLen > 0)
			{
				$tempDigit = substr($tempStr, 0, 1);
				$tempNum = ($tempNum * 10) + $tempDigit;
				$tempStr = substr($tempStr, 1);
				$tempNumLen = length($tempStr);
			}
		}
	}
	return $tempNum;
}

# convert A-F to integer
sub converAFToInteger
{
	my ($tempDigit) = @_;
	my ($tempNum) = 0;
	
	if($tempDigit =~ /^[aA]$/)
	{
		$tempNum = 10;
	}
	elsif ($tempDigit =~ /^[bB]$/)
	{
		$tempNum = 11;
	}
	elsif ($tempDigit =~ /^[cC]$/)
	{
		$tempNum = 12;
	}
	elsif ($tempDigit =~ /^[dD]$/)
	{
		$tempNum = 13;
	}
	elsif ($tempDigit =~ /^[eE]$/)
	{
		$tempNum = 14;
	}
	elsif ($tempDigit =~ /^[fF]$/)
	{
		$tempNum = 15;
	}
	else
	{
		$tempNum = $tempDigit;
	}
	return $tempNum;
}

# convert class id to file name
sub converClsIdToFileName
{
	my ($tempStr) = @_;
	my ($tempKeyword) = "CLSID_";
	my ($tempFileName);
		
	if ($tempStr =~ /^\s*$tempKeyword([0-9a-zA-Z_]+)\s*/)
	{
		$tempFileName = $1;
	}
		
	return $tempFileName;
}