//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Project1.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("About.cpp", AboutBox);
USE("Project1.todo", ToDo);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int )
{
HANDLE mutex ;

        try
        {
        	const char mutex_name[] = "allow_only_one_instance_running" ;
        	// See if the mutex already exists.
	        mutex = OpenMutex ( 0, false, mutex_name ) ;

        	if (mutex == NULL)
	        {
		        /* Create a mutex so that all other programs will know that
        		* this program is running.*/
        		mutex = CreateMutex( NULL, true, mutex_name ) ;
	        }
        	else
        	{
	        	Application->MessageBox("Application is already running.", "RPS Online", MB_ICONWARNING );
        		return 0 ;
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
        ReleaseMutex (mutex) ;
        return 0;
}
//---------------------------------------------------------------------------



