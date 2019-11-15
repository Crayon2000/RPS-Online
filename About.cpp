//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "About.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::CommentsClick(TObject *Sender)
{
    ShellExecute(Handle,
                 L"open",
                 L"mailto:crayon1@rocketmail.com?subject=RPS Online",
                  NULL, NULL, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------
void __fastcall TAboutBox::FormCreate(TObject *Sender)
{
    //Met l'image dans le carré
    ProgramIcon->Picture->Bitmap = Form1->ImRoche2;
}
//---------------------------------------------------------------------------

