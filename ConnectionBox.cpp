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
    : TForm(Owner), FIPAddress(NULL)
{
    throw Exception("Don't use this constructor!");
}
//---------------------------------------------------------------------------

__fastcall TForm2::TForm2(TComponent* Owner, String *AIPAddress)
    : TForm(Owner), FIPAddress(AIPAddress)
{
    if(FIPAddress == NULL)
    {
        throw Exception("Second paramater must not be NULL!");
    }
    txtOpponentIP->Text = *FIPAddress;

    // Fill IP list
    TIdStackLocalAddressList* LLocalAddresses = new TIdStackLocalAddressList();
    try
    {
        TIdStack::IncUsage(); // Ensures GStack is available even if no Indy components are active
        GStack->GetLocalAddressList(LLocalAddresses);
        TIdStack::DecUsage();
        const int LIpCount = LLocalAddresses->Count;
        for(int i = 0; i < LIpCount; ++i)
        {   // We try find an IP v4
            TIdStackLocalAddress* LStackLocalAddress = LLocalAddresses->Addresses[i];
            if(LStackLocalAddress->IPVersion == TIdIPVersion::Id_IPv4)
            {
                lstMyIP->AddItem(LStackLocalAddress->IPAddress, NULL);
            }
        }
        if(lstMyIP->Items->Count == 0 && LIpCount > 0)
        {   // Nothing was found, we take the default local address
            lstMyIP->AddItem(LLocalAddresses->Addresses[0]->IPAddress, NULL);
        }
    }
    __finally
    {
        delete LLocalAddresses;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::cmdPasteClick(TObject *Sender)
{
    txtOpponentIP->PasteFromClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::cmdCopyClick(TObject *Sender)
{
    if(lstMyIP->ItemIndex != -1)
    {
        const String LSelectedString = lstMyIP->Items->Strings[lstMyIP->ItemIndex];
        Clipboard()->AsText = LSelectedString; // Copy to clipboard
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::cmdConnectClick(TObject *Sender)
{
    *FIPAddress = txtOpponentIP->Text;
}
//---------------------------------------------------------------------------

