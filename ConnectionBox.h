//---------------------------------------------------------------------------
#ifndef ConnectionBoxH
#define ConnectionBoxH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
    typedef TForm inherited;

__published:	// IDE-managed Components
    TButton *cmdConnect;
    TButton *cmdCancel;
    TButton *cmdCopy;
    TButton *cmdPaste;
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TEdit *txtOpponentIP;
    TListBox *lstMyIP;
    void __fastcall cmdPasteClick(TObject *Sender);
    void __fastcall cmdCopyClick(TObject *Sender);
    void __fastcall cmdConnectClick(TObject *Sender);
private:	// User declarations
    String *FIPAddress;
public:		// User declarations
    __fastcall TForm2(TComponent* Owner);
    __fastcall TForm2(TComponent* Owner, String *AIPAddress);
    inline __fastcall virtual ~TForm2() { }
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
