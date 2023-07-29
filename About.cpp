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
    Caption = "About RPS Online";

    // Set image
    ProgramIcon->Picture->Bitmap = Form1->FBitmapRockLeft;
}
//---------------------------------------------------------------------

void __fastcall TAboutBox::CommentsClick(TObject *Sender)
{
    ShellExecuteW(Handle,
                 L"open",
                 L"mailto:crayon1@rocketmail.com?subject=RPS Online",
                 nullptr, nullptr, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

