// FileProspector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>

#include "FlashTranslater.h"

int _tmain(int argc, _TCHAR* argv[])
{
    FlashTranslaterClass hFt;

    if ((argv[1] == NULL) || (argv[2] == NULL))
    {
        cout << "\nUsage: FileProspector upload.bin upload_info.bin" << endl;
        cout << "\n   Dump file tree and RAI information" << endl;
        cout << "\n   Version: " << hFt.GetVersionAnsciiStr() << endl;
    }
    else
    {
        cout << "\nFileProspector: Version: " << hFt.GetVersionAnsciiStr() << endl << endl;

        if (TRUE == hFt.SetFlashFilePath(argv[1], argv[2], argv[3]))
        {
            hFt.LoadRaiObjects();
            hFt.LoadFatLibrary();
            hFt.LoadFileTree();
            hFt.DumpRaiObjects();
            hFt.DumpFileTree();
            hFt.DumpStatistics();

            cout << "\nDone!!" << endl;
        }
        else
        {
            cout << "\nExecute error!!" << endl;
        }
    }

    cout << "\n\nPress any key to leave.." << endl;
    cin.ignore(0,'\n');
    _getch();

	return 0;
}

