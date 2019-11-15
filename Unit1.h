//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
#include <MPlayer.hpp>
#include <vcl\Registry.hpp> // Pour le REGISTRE ou INI
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// Composants gérés par l'EDI
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
        void __fastcall FormCreate(TObject *Sender);
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
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Statistics1Click(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
private:	// Déclarations utilisateur
        Graphics::TBitmap*    ImRoche;
        Graphics::TBitmap*    ImPapier;
        Graphics::TBitmap*    ImCiseaux;
        Graphics::TBitmap*    ImPapier2;
        Graphics::TBitmap*    ImCiseaux2;
        void __fastcall TForm1::Play(int Choix);           //On joue
        void __fastcall TForm1::ConnectServeur(String IP); //Connection par TCP/IP
        void __fastcall TForm1::Listen(bool Ecoute);       //Attend une connection TCP/IP
        void __fastcall TForm1::Compare();                 //Compare le joueur à l'adversaire
        void __fastcall TForm1::Reception(TCustomWinSocket *Socket); //Réception (réseau)
public:		// Déclarations utilisateur
        String IPServer;   // Contient l'adresse IP de l'adversaire
        String Temp_IPServer;   //On s'en sert pour le fichier ini
        String NickServer; // Contient le nick name de l'adversaire
        String MailServer; // Contient le E-Mail de l'adversaire
        bool IsServer;     // Si VRAI=Serveur, si FAUX=pas serveur
        int P1Choix;       // Choix du Player 1 (rien, roche, papier ou sciseaux)
        int P2Choix;       // Choix du Player 2 (rien, roche, papier ou sciseaux)
        int Wins;          // Calcul le nombre de partie gagnée
        int Losts;         // Calcul le nombre de partie perdue
        int Ties;          // Calcul le nombre de partie nulle
        bool Son, Musique; // Enable/Disable les sons et la musique
        int PortCom;       // Port de communication
        Graphics::TBitmap*    ImRoche2;
        struct Signe {     //Signes
                int Roche;
                int Papier;
                int Ciseaux;
        };
        Signe StatsJoueur; //Stats sur signe du joueur
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
