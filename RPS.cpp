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
    HANDLE LMutex = NULL;

    try
    {
        const wchar_t LMutexName[] = L"allow_only_one_instance_running";
        // See if the LMutex already exists.
        LMutex = OpenMutex(0, false, LMutexName);

        if (LMutex == NULL)
        {
            /* Create a LMutex so that all other programs will know that
            * this program is running.*/
            LMutex = CreateMutex(NULL, true, LMutexName);
        }
        else
        {
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

