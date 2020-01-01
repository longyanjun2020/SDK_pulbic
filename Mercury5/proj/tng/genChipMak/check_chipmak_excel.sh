#!/bin/sh

out_path=chip_mak_tmp
in_path=sc/customer/product/common/mak/hal
pa_cmd=./tng/genChipMak/ChipMakExcelParser.exe
pa_cmd_opt='-i ${in_path} -o ${out_path} -c options_summary_ChipSeries.xls'
#echo ' echo "chip_mak excel comparison started."'

#date +"%T" > /dev/null 2>&1

if [ ! -d "${out_path}" ]; then
	mkdir ${out_path}
fi

tng/genChipMak/ChipMakExcelParser.exe -i ${in_path} -o ${out_path} -c options_summary_ChipSeries.xls > pa_log.txt # /dev/null 2>&1

if grep 'does not exist' pa_log.txt 1> /dev/null
	then echo file_not_exist
	exit
fi

if grep 'Failed to open' pa_log.txt 1> /dev/null
	then echo file_corrupted
	exit
fi


if grep 'Applicable chip number mismatch' pa_log.txt 1> /dev/null
	then grep 'Applicable chip number mismatch' pa_log.txt > 1.txt
	cat 1.txt
	exit
fi

for filename in `ls ${out_path}`; do
	if [ -f ${in_path}/${filename} ]; then
		if [ `diff ${out_path}/${filename} ${in_path}/${filename}  | wc -l` -ne 0 ]; then
			echo mismatch
			exit
		fi
	else
		echo 'nothing is compared. Probably chip mak generation process was failed'
	fi
done
