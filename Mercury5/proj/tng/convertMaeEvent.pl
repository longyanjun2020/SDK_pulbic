die("Usage: convertMaeEvent input_file output_file\n") if @ARGV < 2;

# open file handle
$input_maefile;
$output_maefile;

$inputFileNum = @ARGV - 1;
$output_eventfile = $ARGV[$inputFileNum];

open(OUTPUT_FILE, ">$output_eventfile")
	or die("Output file $output_eventfile can not be created\n");
	
# read ini settings
# create class id table
$inLine;
$keyword = "MAE_EVT_";
$keyDefine = "#define";
@dataArray;
$inEnum = 0;
$clsValue = 0;
$tempDef;
$inDefCount = 0;
$putInData = 0;
$inCommon = 0;
$inputCount = 0;

for ($inputCount = 0; $inputCount < $inputFileNum; $inputCount++)
{
	# open file handle
	$input_maefile = $ARGV[$inputCount];
	open(INPUT_FILE, "<$input_maefile")
		or die ("Input file $input_maefile not found\n");
	
	$inLine = <INPUT_FILE>;
	while ($inLine ne "")
	{
		chop($inLine);
	
		#check common lines
		if ($inLine =~ /^.*\/\*.*\*\/.*/)
		{
			$inCommon = 0;
		}
		elsif ($inLine =~ /^.*\/\*.*/)
		{
			$inCommon = 1;
		}
		elsif ($inLine =~ /^.*\*\/.*/)
		{
			$inCommon = 0;
		}
		else
		{
			if ($inCommon == 1)
			{
				print(OUTPUT_FILE "$inLine\n");	
				$inLine = <INPUT_FILE>;
				next;
			}
		}	

  	if ($inLine =~ /^\s*$keyDefine\s+($keyword[0-9a-zA-Z_]+)\s+(.+)/)
  	{	 	 	 	 	 	
  		if ($inEnum == 0)
  		{ 		
  			$inEnum = 1;
  			$buffer = sprintf("typedef enum{\n");
  			push(@dataArray, $buffer);
  		}
 			$tempDef = "TMT_TEMP_" . $1;
 			$buffer = sprintf("%s = %s,\n", $1, $tempDef);
 			push(@dataArray, $buffer);
 			$buffer = sprintf("#define %s %s", $tempDef, $2);
 			print(OUTPUT_FILE "$buffer\n", );
  	}
  	else
  	{
  		$putInData = 0;
  		if ($inLine =~ /^\s*$keyDefine\s+.+/)
  		{
  			if ($inEnum == 1 && $inDefCount == 0)
  			{
  				$inEnum = 0;
  				$buffer = sprintf("};\n");
  				push(@dataArray, $buffer);
  			}
  		}
  		elsif ($inLine =~ /^\s*\#if.+/ || $inLine =~ /^\s*\#ifdef.+/ || $inLine =~ /^\s*\#ifndef.+/)
  		{
  			if ($inEnum == 1)
  			{
  				$inDefCount = $inDefCount + 1;
  				$putInData = 1;
  			}
  		}
  		elsif ($inLine =~ /^\s*\#else.+/)
  		{
  			if ($inDefCount > 0)
  			{
  				$putInData = 1;
  			}
  		}
  		elsif ($inLine =~ /^\s*\#endif.+/)
  		{
  			if ($inDefCount > 0)
  			{
  				$inDefCount = $inDefCount - 1;
  				$putInData = 1;
  			}
  		}
  	
  		if ($putInData == 1)
  		{
  			$buffer = sprintf("%s\n", $inLine);
 				push(@dataArray, $buffer);
 			}
  		print(OUTPUT_FILE "$inLine\n");
  	}
		$inLine = <INPUT_FILE>;
	}

	close(INPUT_FILE);
	if ($inEnum == 1 && $inDefCount == 0)
	{
		$buffer = sprintf("};\n");
  	push(@dataArray, $buffer);
	}
}

$dataIndex = 0;
while ( $dataIndex < @dataArray )
{
	print(OUTPUT_FILE "$dataArray[$dataIndex]");
	$dataIndex = $dataIndex + 1;
}

close(OUTPUT_FILE);