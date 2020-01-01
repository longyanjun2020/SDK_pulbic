die("Usage: ParseMaeClsid\n") if @ARGV != 4;

# open file handle
$input_raiid_class_file = shift(@ARGV);
$input_raiid_mmi_class_file = shift(@ARGV);
$input_raiid_file = shift(@ARGV);

$output_raiidfile = shift(@ARGV);

$inLine;
$prefixed;
$keyword;
$fileKeyword;
$dataIndex = 0;
$inData;

@lineTokens;
@dataArray;

# open file handle
open(INPUT_FILE, "<$input_raiid_class_file")
	or die ("Input file $input_raiid_class_file not found\n");

open(OUTPUT_FILE, ">$output_raiidfile")
	or die("Output file $output_raiidfile can not be created\n");
	
# create rai class id table
$finalKeyword = "_FS_RAI_START_ID";
$number = 0;
@raiClassIdTable;

$inLine = <INPUT_FILE>;
while ($inLine ne "")
{
	chop($inLine);
	
  if ($inLine =~ /^\s*(.+$finalKeyword\s*=\s*[0-9a-fxA-FX]*).*/)
  {
  	$inLine = $1;						
		@lineTokens = split(/\s*=\s*/, $inLine);	 	 	 	 	 	 	
		if (@lineTokens > 1)
		{
			$number = &converStringToInteger($lineTokens[1]);
			$buffer = sprintf("%s %d", $lineTokens[0], $number);	
		}
		else
		{
			$buffer = sprintf("%s %d", $lineTokens[0], $number);	
		}
		push(@raiClassIdTable, $buffer);
		$number ++;
	}
	$inLine = <INPUT_FILE>;
}

close(INPUT_FILE);

# open file handle
open(INPUT_FILE, "<$input_raiid_mmi_class_file")
	or die ("Input file $input_raiid_mmi_class_file not found\n");

# create rai mmi class id table
$keyword = "MMI_RAI_";
$number = 0;

$inLine = <INPUT_FILE>;
while ($inLine ne "")
{
	chop($inLine);
	
  if ($inLine =~ /^\s*($keyword[0-9a-zA-Z]+\s*=?\s*[0-9a-fxA-FX]*).*/)
  {
  	$inLine = $1;						
		@lineTokens = split(/\s*=\s*/, $inLine);	 	 	 	 	 	 	
		if (@lineTokens > 1)
		{
			$number = &converStringToInteger($lineTokens[1]);
			$buffer = sprintf("%s %d", $lineTokens[0], $number);	
		}
		else
		{
			$buffer = sprintf("%s %d", $lineTokens[0], $number);	
		}
		push(@raiClassIdTable, $buffer);
		$number ++;
	}
	$inLine = <INPUT_FILE>;
}

close(INPUT_FILE);

# open file handle
open(INPUT_FILE, "<$input_raiid_file")
	or die ("Input file $input_raiid_file not found\n");

# create rai id table
$keyword1 = "M_MMI_RAI_";
$keyword2 = "MMI_FS_RAI_ITEM_";
$keywordStart = "_START";
$keywordEnd = "_END";
$number = 0;
$stringLength = 0;
$charIndex;
$elementCount = 0;
$string1;
$string2;
$endNumber = 0;
$word;
$ignoral;
$beginNumber = 0;

$inLine = <INPUT_FILE>;
while ($inLine ne "")
{
	chop($inLine);
	$endNumber = 0;
	$ignoral = 0;
	$word = "";
	
	if ($inLine =~ /^\s*$keyword1[0-9a-zA-Z_]+\s*=\s*([0-9a-zA-Z_\(\)\<\+\-\s\&]*).*\s*/)
	{
		$string1 = $1;
		$ignoral = 1;
		$number = &calculateString($string1) + 1;
		#print(OUTPUT_FILE "$string1 = $number\n");
	}
	elsif ( $inLine =~ /^\s*($keyword2[0-9a-zA-Z_]+)\s*=?\s*([0-9a-zA-Z_\(\)\<\+\-\s\&]*).*\s*/ )
	{
		$string1 = $1;
		@lineTokens = split(/_STAR/, $string1);
		if ( @lineTokens > 1 )
		{
			$buffer = sprintf("%s %d", $string1, $number);
			push(@raiClassIdTable, $buffer);
			$ignoral = 1;
			$number ++;
		}
		else
		{
			@lineTokens = split(/_EN/, $string1);
			if ( @lineTokens > 1 )
			{
				#print(OUTPUT_FILE "$string1\n");
				if ( $2 ne "" )
				{
					$string2 = $2;
					$word = @lineTokens[0];
					#print(OUTPUT_FILE "token $word num str = $string2\n");
					$endNumber = &calculateString($string2);
					#print(OUTPUT_FILE "endNumber $endNumber\n");
				}
				else
				{
					$ignoral = 1;
					$number ++;
				}
			}
		}
	}
	else
	{
		$ignoral = 1;
	}
	
	if ( $ignoral == 0 )
	{
		if ( $endNumber > 0 && $word ne "" )
		{
			$beginNumber = &converTokenToInteger($word.$keywordStart);
			if ( $beginNumber > 0 )
			{
				$buffer = sprintf("%08x ~ %08x %s", $beginNumber, $endNumber, $word);
			}
			else
			{
				if ( $number > 0 )
				{
					$buffer = sprintf("%08x ~ %08x %s", $number - 1, $endNumber, $word);
				}
				else
				{
					$buffer = sprintf("%08x ~ %08x %s", $number - 1, $endNumber, $word);
				}
			}
			$number = $endNumber;
		}
		else
		{
			$buffer = sprintf("%08x %s", $number, $string1);
		}
		
		push(@dataArray, $buffer);
		$number ++;
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

# convert string to integer
sub converTokenToInteger
{
	my ($tempStr) = @_;
	my ($tempCount);
	my (@dataTokens);
	my ($tempToken);
	my (@tableTokens);
	my ($tempNum) = 0;
	my ($searched) = 0;
	my ($tempInLine);
			
	@dataTokens = split(/\s+/, $tempStr);
	
	if ( @dataTokens == 0 )
	{
		return 0;
	}
	$tempToken = @dataTokens[0];
				
	#first table search
	for ($tempCount = 0; $tempCount < @raiClassIdTable; $tempCount++)
	{
		@tableTokens = split(/\s+/, @raiClassIdTable[$tempCount]);
		if ( $tempToken eq @tableTokens[0] )
		{
			$searched = 1;
			$tempNum = @tableTokens[1];
			last;
		}
	}
	
	if ( $searched == 0 )
	{
		#print(OUTPUT_FILE "not found $tempToken\n");
		
		# open file handle
		open(TMP_INPUT_FILE, "<$input_raiid_file")
			or die ("Input file $input_raiid_file not found\n");
			
		$tempInLine = <TMP_INPUT_FILE>;
		while ($tempInLine ne "")
		{
			chop($tempInLine);

			if ( $tempInLine =~ /^\s*$tempToken\s*=?\s*([0-9a-fxA-FX]*).*/ )
  		{			 	 	 	 	
				if ( $1 ne "" )
				{
					$tempNum = &converStringToInteger($1);
					$buffer = sprintf("%s %d", $tempToken, $tempNum);	
				}
				else
				{
					$tempNum = 0;
					$buffer = sprintf("%s %d", $tempToken, $tempNum);	
				}
				push(@raiClassIdTable, $buffer);
				last;
			}
			$tempInLine = <TMP_INPUT_FILE>;
		}
		close(TMP_INPUT_FILE);
	}
	
	return $tempNum;
}

# convert class id to file name
sub calculateString
{
	my ($tempStr) = @_;
	my ($tempStrLength);
	my ($tempCharIndex) = 0;
	my ($tempCharIndex1) = 0;
	my ($tempOldCharIndex) = 0;
	my ($tempNumber) = 0;
	my ($leftBracket) = "(";
	my ($rightBracket) = ")";
	my ($tempSpace) = " ";
	my ($localStr);
	my ($tempMatched) = 0;
	
	$tempStrLength = length($tempStr);
	
	#print(OUTPUT_FILE "$tempStr\n");
	
	while ( $tempStrLength > 0 && $tempCharIndex < $tempStrLength )
	{
		#print(OUTPUT_FILE "tempStr = $tempStr\n");
		#print(OUTPUT_FILE "tempStrLength = $tempStrLength\n");
		#print(OUTPUT_FILE "tempOldCharIndex = $tempOldCharIndex\n");	
		
		$tempMatched = 0;
		$tempCharIndex = $tempOldCharIndex + index(substr($tempStr, $tempOldCharIndex, ($tempStrLength - $tempOldCharIndex)), "(");
		#print(OUTPUT_FILE " ( tempCharIndex = $tempCharIndex\n");
		
		if ( $tempCharIndex >= $tempOldCharIndex )
		{
			$tempMatched = 1;
		}
		
		$tempCharIndex1 = $tempOldCharIndex + index(substr($tempStr, $tempOldCharIndex, ($tempStrLength - $tempOldCharIndex)), ")");
		#print(OUTPUT_FILE " ) tempCharIndex1 = $tempCharIndex1\n");
		if ( $tempCharIndex1 >= $tempOldCharIndex )
		{
			if ( $tempMatched == 1 )
			{
				if ( $tempCharIndex1 < $tempCharIndex )
				{
					$tempCharIndex = $tempCharIndex1;
				}
			}
			else
			{
				$tempCharIndex = $tempCharIndex1;
				$tempMatched = 1;
			}
		}
		
		$tempCharIndex1 = $tempOldCharIndex + index(substr($tempStr, $tempOldCharIndex, ($tempStrLength - $tempOldCharIndex)), "+");
		#print(OUTPUT_FILE " + tempCharIndex1 = $tempCharIndex1\n");
		if ( $tempCharIndex1 >= $tempOldCharIndex )
		{
			if ( $tempMatched == 1 )
			{
				if ( $tempCharIndex1 < $tempCharIndex )
				{
					$tempCharIndex = $tempCharIndex1;
				}
			}
			else
			{
				$tempCharIndex = $tempCharIndex1;
				$tempMatched = 1;
			}
		}
		
		$tempCharIndex1 = $tempOldCharIndex + index(substr($tempStr, $tempOldCharIndex, ($tempStrLength - $tempOldCharIndex)), "-");
		#print(OUTPUT_FILE " - tempCharIndex1 = $tempCharIndex1\n");
		if ( $tempCharIndex1 >= $tempOldCharIndex )
		{
			if ( $tempMatched == 1 )
			{
				if ( $tempCharIndex1 < $tempCharIndex )
				{
					$tempCharIndex = $tempCharIndex1;
				}
			}
			else
			{
				$tempCharIndex = $tempCharIndex1;
				$tempMatched = 1;
			}
		}
		
		if ( $tempMatched == 1 )
		{
			if ( $tempCharIndex == 0 )
			{
				$tempStr = substr($tempStr, 0, ($tempCharIndex + 1)).$tempSpace.substr($tempStr, ($tempCharIndex + 1), ($tempStrLength - 1));
				$tempCharIndex = $tempCharIndex + 2;
			}
			elsif ( $tempCharIndex == $tempStrLength - 1 )
			{
				$tempStr = substr($tempStr, 0, $tempCharIndex).$tempSpace.substr($tempStr, $tempCharIndex, 1).$tempSpace;
				last;
			}
			else
			{
				$tempStr = substr($tempStr, 0, $tempCharIndex).$tempSpace.substr($tempStr, $tempCharIndex, 1).$tempSpace.substr($tempStr, ($tempCharIndex + 1), $tempStrLength - 1);
				$tempCharIndex = $tempCharIndex + 3;
			}
			$tempStrLength = length($tempStr);
			if ( $tempCharIndex >= $tempStrLength )
			{
				$tempCharIndex = $tempStrLength - 1;
			}
			$tempOldCharIndex = $tempCharIndex;
		}
		else
		{
			last;
		}
	}
	
	#print(OUTPUT_FILE "$tempStr\n");
	($tempNumber, $tempCharIndex) = &calculateToken($tempStr, 0);
	return $tempNumber;
}

# convert class id to file name
sub calculateToken
{
	my ($tempStr, $tempStrIndex) = @_;
	my (@tempElements);
	my ($additionWord) = "+";
	my ($subtractionWord) = "-";
	my ($leftShiftWord) = "<<";
	my ($leftBracket) = "(";
	my ($rightBracket) = ")";
	my ($opAnd) = "&";
	my (@tempOperation);
	my ($tempCount) = 0;
	my ($tempNumber) = 0;
	my ($Operator) = 0;
	my ($hasOperator) = 0;
	my ($operationNum) = 0;
	my ($number1) = 0;
	my ($number2) = 0;
	my ($invalidString) = 0;
	
	@tempElements = split(/\s+/, $tempStr);
			 	 	 	 	 			 	 	 	 	 	
	for ($tempCount = $tempStrIndex; $tempCount < @tempElements; $tempCount++)
	{
		if (@tempElements[$tempCount] =~ /^[0-9a-fA-FxX]+/)
		{
			$tempNumber = &converStringToInteger(@tempElements[$tempCount]);
			$operationNum = $operationNum + 1;
			#print(OUTPUT_FILE "@tempElements[$tempCount] = $tempNumber , $operationNum\n");
			push(@tempOperation, $tempNumber);
		}
		elsif (@tempElements[$tempCount] =~ /^[0-9a-zA-Z_]+/)
		{
			$tempNumber = &converTokenToInteger(@tempElements[$tempCount]);
			$operationNum = $operationNum + 1;
			#print(OUTPUT_FILE "@tempElements[$tempCount] = $tempNumber , $operationNum\n");
			push(@tempOperation, $tempNumber);
		}
		elsif (@tempElements[$tempCount] eq $leftBracket)
		{
			#print(OUTPUT_FILE "call calculateToken\n");
			($tempNumber, $tempCount) = &calculateToken($tempStr, $tempCount + 1);
			$operationNum = $operationNum + 1;
			#print(OUTPUT_FILE "$operationNum\n");
			push(@tempOperation, $tempNumber);
		}
		elsif (@tempElements[$tempCount] eq $rightBracket)
		{
			#print(OUTPUT_FILE "@tempElements[$tempCount]\n");
			last;
		}
		elsif (@tempElements[$tempCount] eq $additionWord)
		{
			#print(OUTPUT_FILE "@tempElements[$tempCount]\n");
			push(@tempOperation, $additionWord);
			$hasOperator = 1;
		}
		elsif (@tempElements[$tempCount] eq $subtractionWord)
		{
			#print(OUTPUT_FILE "@tempElements[$tempCount]\n");
			push(@tempOperation, $subtractionWord);
			$hasOperator = 1;
		}
		elsif (@tempElements[$tempCount] eq $leftShiftWord)
		{
			#print(OUTPUT_FILE "@tempElements[$tempCount]\n");
			push(@tempOperation, $leftShiftWord);
			$hasOperator = 1;
		}
		elsif (@tempElements[$tempCount] eq $opAnd)
		{
			#print(OUTPUT_FILE "@tempElements[$tempCount]\n");
			push(@tempOperation, $opAnd);
			$hasOperator = 1;
		}
			
		if ( $operationNum == 2 )
		{
			if ( $hasOperator == 1 )
			{
				$number2 = pop(@tempOperation);
				$Operator = pop(@tempOperation);
				$number1 = pop(@tempOperation);
			
				if ( $Operator eq $additionWord )
				{
					$tempNumber = $number1 + $number2;
					#print(OUTPUT_FILE "$tempNumber = $number1 + $number2\n");
					push(@tempOperation, $tempNumber);
					$operationNum = 1;
				}
				elsif ( $Operator eq $subtractionWord )
				{
					$tempNumber = $number1 - $number2;
					#print(OUTPUT_FILE "$tempNumber = $number1 - $number2\n");
					push(@tempOperation, $tempNumber);
					$operationNum = 1;
				}
				elsif ( $Operator eq $leftShiftWord )
				{
					$tempNumber = $number1 << $number2;
					#print(OUTPUT_FILE "$tempNumber = $number1 << $number2\n");
					push(@tempOperation, $tempNumber);
					$operationNum = 1;
				}
				elsif ( $Operator eq $opAnd )
				{
					$tempNumber = $number1 & $number2;
					#print(OUTPUT_FILE "$tempNumber = $number1 & $number2\n");
					push(@tempOperation, $tempNumber);
					$operationNum = 1;
				}
				else
				{
					$operationNum = 0;
				}
			}
			else
			{
				$invalidString = 1;
				#print(OUTPUT_FILE "hasOperator = $hasOperator invalidString\n");
				last;
			}
		}
	}
	
	while (@tempOperation > 0 && $invalidString == 0 )
	{
		if ( @tempOperation > 2 )
		{
			$number2 = pop(@tempOperation);
			$Operator = pop(@tempOperation);
			$number1 = pop(@tempOperation);
	
			if ( $Operator eq $additionWord )
			{
				$tempNumber = $number1 + $number2;
				#print(OUTPUT_FILE "$tempNumber = $number1 + $number2\n");
				push(@tempOperation, $tempNumber);
			}
			elsif ( $Operator eq $subtractionWord )
			{
				$tempNumber = $number1 - $number2;
				#print(OUTPUT_FILE "$tempNumber = $number1 - $number2\n");
				push(@tempOperation, $tempNumber);
			}
			elsif ( $Operator eq $leftShiftWord )
			{
				$tempNumber = $number1 << $number2;
				#print(OUTPUT_FILE "$tempNumber = $number1 << $number2\n");
				push(@tempOperation, $tempNumber);
			}
			elsif ( $Operator eq $opAnd )
			{
				$tempNumber = $number1 & $number2;
				#print(OUTPUT_FILE "$tempNumber = $number1 & $number2\n");
				push(@tempOperation, $tempNumber);
			}
		}
		elsif ( @tempOperation == 1 )
		{
			$tempNumber = pop(@tempOperation);
		}
		elsif ( @tempOperation == 2 )
		{
			#print(OUTPUT_FILE "@tempOperation invalidString\n");
			$invalidString = 1;
		}
	}
	
	if ( $invalidString == 1 )
	{
		#print(OUTPUT_FILE "invalidString\n");
		$tempNumber = 0;
	}
		
	#print(OUTPUT_FILE "tempNumber = $tempNumber\n");
	return ($tempNumber, $tempCount);
}