//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Win.ScktComp.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.MPlayer.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPServer.hpp>
//---------------------------------------------------------------------------
enum class TPlayerMove : unsigned char
{
    None,
    Rock,
    Paper,
    Scissors
};

class TMoveStats {
public:
    int Rock;
    int Paper;
    int Scissors;

    void __fastcall Reset()
    {
        Rock = 0;
        Paper = 0;
        Scissors = 0;
    }

    int __fastcall Total()
    {
        return Rock + Paper + Scissors;
    }
};

class TForm1 : public TForm
{
    typedef TForm inherited;

__published:    // IDE-managed Components
    TServerSocket *ServerSocket;
    TClientSocket *ClientSocket;
    TStatusBar *StatusBar1;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *Help1;
    TMenuItem *Network1;
    TMenuItem *Options1;
    TMenuItem *Connecttoopponent1;
    TMenuItem *Disconnectec1;
    TMenuItem *HelpTopic1;
    TMenuItem *About1;
    TMenuItem *N1;
    TMenuItem *Quitter1;
    TPanel *Panel1;
    TLabel *Label1;
    TLabel *Label2;
    TPanel *Win;
    TPanel *Lost;
    TGroupBox *BoxYou;
    TGroupBox *GroupBox1;
    TMemo *Memo2;
    TEdit *Memo1;
    TButton *Send;
    TMenuItem *NewGame1;
    TMenuItem *N2;
    TImage *GLancer;
    TImage *Logo;
    TSpeedButton *Roche1;
    TSpeedButton *Papier1;
    TSpeedButton *Ciseaux1;
    TMenuItem *Sound1;
    TMediaPlayer *PlayerMidi;
    TPanel *Tie;
    TLabel *Label3;
    TMenuItem *Music1;
    TMenuItem *N3;
    TMenuItem *Statistics1;
    void __fastcall Quitter1Click(TObject *Sender);
    void __fastcall Disconnectec1Click(TObject *Sender);
    void __fastcall SendClick(TObject *Sender);
    void __fastcall Connecttoopponent1Click(TObject *Sender);
    void __fastcall ClientSocketError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
      int &ErrorCode);
    void __fastcall ClientSocketRead(TObject *Sender,
      TCustomWinSocket *Socket);
    void __fastcall ServerSocketAccept(TObject *Sender,
      TCustomWinSocket *Socket);
    void __fastcall ServerSocketClientConnect(TObject *Sender,
      TCustomWinSocket *Socket);
    void __fastcall ServerSocketClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket);
    void __fastcall ServerSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket);
    void __fastcall ClientSocketConnect(TObject *Sender,
      TCustomWinSocket *Socket);
    void __fastcall ClientSocketDisconnect(TObject *Sender,
      TCustomWinSocket *Socket);
    void __fastcall About1Click(TObject *Sender);
    void __fastcall NewGame1Click(TObject *Sender);
    void __fastcall HelpTopic1Click(TObject *Sender);
    void __fastcall Roche1Click(TObject *Sender);
    void __fastcall Papier1Click(TObject *Sender);
    void __fastcall Ciseaux1Click(TObject *Sender);
    void __fastcall Sound1Click(TObject *Sender);
    void __fastcall PlayerMidiNotify(TObject *Sender);
    void __fastcall Music1Click(TObject *Sender);
    void __fastcall Statistics1Click(TObject *Sender);
private:    // User declarations
    String IPServer;   // Contient l'adresse IP de l'adversaire
    String NickServer; // Contient le nick name de l'adversaire
    bool IsServer;     // Si VRAI=Serveur, si FAUX=pas serveur
    TPlayerMove FPlayer1Choice; // Player 1 choice
    TPlayerMove FPlayer2Choice; // Player 2 choice
    int FWinCount; // Calcul le nombre de partie gagnée
    int FLostCount; // Calcul le nombre de partie perdue
    int FTieCount; // Calcul le nombre de partie nulle
    bool FSoundEnabled; // Enable/Disable sound effects
    bool FMusicEnabled; // Enable/Disable music
    int PortCom;       // Port de communication
    TMoveStats FPlayerStats; // Stats sur signe du joueur

    Graphics::TBitmap* FBitmapPaperLeft;
    Graphics::TBitmap* FBitmapScissorsLeft;
    Graphics::TBitmap* FBitmapRockRight;
    Graphics::TBitmap* FBitmapPaperRight;
    Graphics::TBitmap* FBitmapScissorsRight;

    void __fastcall Play(TPlayerMove AChoice); // On joue
    void __fastcall ConnectServer(const String IP); // Connection par TCP/IP
    void __fastcall Listen(bool AListen); // Attend une connection TCP/IP
    void __fastcall Compare(); // Compare le joueur à l'adversaire
    void __fastcall Reception(TCustomWinSocket *Socket); // Réception (réseau)
protected:
    void __fastcall LoadPng(Graphics::TBitmap *ABitmapImage, const String AIdentifier);
    void __fastcall FlipImageH(Graphics::TBitmap *AImage);
    void __fastcall FlipImageV(Graphics::TBitmap *AImage);
    void __fastcall ReplaceColor(Graphics::TBitmap* ABitmap, TColor AOldColor, TColor ANewColor);
public:     // User declarations
    Graphics::TBitmap* FBitmapRockLeft;

    __fastcall TForm1(TComponent* Owner);
    __fastcall virtual ~TForm1();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

