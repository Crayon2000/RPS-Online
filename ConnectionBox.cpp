//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ConnectionBox.h"
#include <Vcl.Clipbrd.hpp>
#include <IdComponent.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
    : TForm(Owner), FIPAddress(nullptr)
{
    throw Exception("Don't use this constructor!");
}
//---------------------------------------------------------------------------

__fastcall TForm2::TForm2(TComponent* Owner, String *AIPAddress)
    : TForm(Owner), FIPAddress(AIPAddress)
{
    Caption = "Connect to Opponent";

    if(FIPAddress == nullptr)
    {
        throw Exception("Second parameter must not be nullptr!");
    }
    txtOpponentIP->Text = *FIPAddress;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::cmdPasteClick(TObject *Sender)
{
    txtOpponentIP->PasteFromClipboard();
}
//---------------------------------------------------------------------------


void __fastcall TForm2::cmdConnectClick(TObject *Sender)
{
    *FIPAddress = txtOpponentIP->Text;
}
//---------------------------------------------------------------------------

