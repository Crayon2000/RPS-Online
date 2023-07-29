//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Form1);
USEFORM("About.cpp", AboutBox);
USEFORM("ConnectionBox.cpp", Form2);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    HANDLE LMutex = nullptr;

    try
    {
        // Create a mutex so that all other programs will know that this program is running
        const String LMutexName = "allow_only_one_instance_running";
        LMutex = CreateMutexExW(nullptr, LMutexName.c_str(), 0, SYNCHRONIZE);

        if (LMutex == nullptr)
        {
            Application->MessageBox(L"Fail to create named mutex.", L"RPS Online", MB_ICONERROR);
            return 0;
        }
        else if( GetLastError() == ERROR_ALREADY_EXISTS )
        {   // The mutex already exists
            Application->MessageBox(L"Application is already running.", L"RPS Online", MB_ICONWARNING);
            return 0;
        }

        Application->Initialize();
        Application->Title = "RPS Online";
        Application->CreateForm(__classid(TForm1), &Form1);
        Application->CreateForm(__classid(TAboutBox), &AboutBox);
        Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    ReleaseMutex(LMutex);
    return 0;
}
//---------------------------------------------------------------------------

