#define __MMI_ENUM_STRING__
using namespace System;
using namespace System::IO;

#include "mmi_mae_clstbl.h"
#include "mmi_clstbl.h"
#include "mmi_enumtbl.h"

int main(int argc, char *argv[])
{
	int i, j;
	array<String^>^ cmd = Environment::GetCommandLineArgs();
	String^ path = Path::GetDirectoryName(cmd[0]);

	// generate the id list of MAE classes
	StreamWriter^ sw = gcnew StreamWriter(path + "\\mae_clsid.txt");
	for (i = 0; i < MAE_Enumerations::Item->Length; i ++)
	{
		Array^ e = Enum::GetValues(MAE_Enumerations::Item[i]);

		for (j = 0; j < e->Length; j ++)
		{
			Object^ o = e->GetValue(j);
			sw->WriteLine("0x{0:X4}\t{1}", Convert::ToUInt32(o), o);
		}
	}
	sw->Close();

	return 0;
}
