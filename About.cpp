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
    // Met l'image dans le carré
    ProgramIcon->Picture->Bitmap = Form1->ImRoche2;
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

