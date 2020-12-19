//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "About.h"
#include <System.IniFiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma resource "images.RES"
TForm1 *Form1;
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
    Logo->Transparent = true;
    Logo->Picture->Bitmap->LoadFromResourceName((NativeUInt)HInstance, "Title");

    TIniFile *LIniFile;       // Lecture dans le fichier INI
    LIniFile = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );
    Temp_IPServer   = LIniFile->ReadString ( "Setting", "IP", "192.168.0.2" );
    Musique         = LIniFile->ReadBool   ( "Setting", "Music", true );
    Son             = LIniFile->ReadBool   ( "Setting", "Sound", true);
    PortCom         = LIniFile->ReadInteger( "Setting", "Port", 1024 );
    delete LIniFile;

    // Prend les paramètres que ICQ envoie (Détection d'arguments)
    // Arguments: -ip numip -name nom_du_user  (pas bon)
    // IPServer = _argv[1];
    // NickServer = _argv[2];
    // MailServer = _argv[3];

    // Sert a faire un vrai Random
    randomize();

    // Met les numéros de Port par défaut
    ClientSocket->Port = PortCom;
    ServerSocket->Port = PortCom;

    P1Choix = 0; // On a rien choisi encore
    P2Choix = 0; // L'adversaire n'a rien choisi encore

    //Audio
    PlayerMidi->FileName = ExtractFilePath(Application->ExeName) + "\\rps.mid"; // Spécifie le fichier son
    Music1->Checked = !Musique;   // Par défaut on met de la musique (true=musique)
    Music1Click(NULL);
    Sound1->Checked = !Son;       // Par défaut on met du son (true=son)
    Sound1Click(NULL);

    // On load les images du fichier RES
    ImRoche = new Graphics::TBitmap;
    ImRoche->LoadFromResourceName((NativeUInt)HInstance, "Roche");
    ImRoche->Transparent = true;
    ImPapier = new Graphics::TBitmap;
    ImPapier->LoadFromResourceName((NativeUInt)HInstance, "Papier");
    ImPapier->Transparent = true;
    ImCiseaux = new Graphics::TBitmap;
    ImCiseaux->LoadFromResourceName((NativeUInt)HInstance, "Ciseaux");
    ImCiseaux->Transparent = true;

    ImRoche2 = new Graphics::TBitmap;
    ImRoche2->LoadFromResourceName((NativeUInt)HInstance, "Roche2");
    ImRoche2->Transparent = true;
    ImPapier2 = new Graphics::TBitmap;
    ImPapier2->LoadFromResourceName((NativeUInt)HInstance, "Papier2");
    ImPapier2->Transparent = true;
    ImCiseaux2 = new Graphics::TBitmap;
    ImCiseaux2->LoadFromResourceName((NativeUInt)HInstance, "Ciseaux2");
    ImCiseaux2->Transparent = true;

    // On réutilise les mêmes images
    Roche1->Glyph = ImRoche;
    Papier1->Glyph = ImPapier;
    Ciseaux1->Glyph = ImCiseaux;

    // Met les valeurs par défaut
    if (IPServer.IsEmpty() == true)           // Si il n'y a rien d'écrit
    {
        IPServer = Temp_IPServer;
        MailServer = "";
        Listen(true);
    }
    else
    {
        ConnectServer(IPServer);
    }

    if (NickServer.IsEmpty() == true)           // Si il n'y a rien d'écrit
    {
        NickServer = "CPU Opponent";         // Versus Distant
    }
}
//---------------------------------------------------------------------------

__fastcall TForm1::~TForm1()
{
    TIniFile *LIniFile;       // Écriture dans le fichier INI
    LIniFile = new TIniFile(ChangeFileExt( Application->ExeName, ".ini" ) );
    LIniFile->WriteString ( "Setting", "IP", IPServer );
    LIniFile->WriteBool   ( "Setting", "Music", Musique );    // 0 = Off
    LIniFile->WriteBool   ( "Setting", "Sound", Son );        // 1 = On
    delete LIniFile;

    // On récupère la mémoire
    delete ImRoche;
    delete ImPapier;
    delete ImCiseaux;
    delete ImRoche2;
    delete ImPapier2;
    delete ImCiseaux2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConnectServer(String IP)
{
    if (ClientSocket->Active == true)
    {             // Si Client enable
        ClientSocket->Active = false;       // On le disable
    }

    ClientSocket->Host = IP;        // On écrit le IP
    ClientSocket->Active = true;    // On enable le Client
    Listen(false);                  // On arrête d'écouter

    StatusBar1->Panels->Items[0]->Text = "Connecting to " + IP;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Listen(bool AListen)
{
    if (AListen == true)                          // Si cocher (menu)
    {
        ClientSocket->Active = false;                      // Disable le Client
        ServerSocket->Active = true;                       // Enable le Serveur
        StatusBar1->Panels->Items[0]->Text = "Listening...";  // Écrit bar d'état
        Disconnectec1->Enabled = false;
        // Si on avait fait un choix avant d'être déconnecter, on enable tout
        Roche1->Enabled = true;
        Papier1->Enabled = true;
        Ciseaux1->Enabled = true;
    }
    else
    {
        if (ServerSocket->Active == true)                  // Si Socket serveur enable
        {
            ServerSocket->Active = false;           // Disable le Serveur
        }
        StatusBar1->Panels->Items[0]->Text = "";   // Écrit dans la bar d'état
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Compare()
{
    TCanvas *MonCanvas = GLancer->Canvas;
    SetBkMode(MonCanvas->Handle, TRANSPARENT);
    MonCanvas->Font->Name = "Arial";
    MonCanvas->Font->Size = 30;
    MonCanvas->Font->Style = TFontStyles() << TFontStyle::fsBold;
    SetTextAlign (MonCanvas->Handle, TA_CENTER);

    int x = GLancer->Width;                          // Emplacement des images
    int y = GLancer->Height - 10;

    if (P1Choix != 0 && P2Choix != 0)
    {
        // Affichage des mains Joueurs DEUX et UN
        switch ( P2Choix )
        {
            case 1 :
                MonCanvas->Draw(x-ImRoche2->Width , y-ImRoche2->Height+7, ImRoche2);
                break;
            case 2 :
                MonCanvas->Draw(x-ImPapier2->Width , y-ImRoche2->Height+16, ImPapier2);
                break;
            case 3 :
                MonCanvas->Draw(x-ImCiseaux->Width , y-ImRoche2->Height+8, ImCiseaux2);
                break;
            default:
                break;
        }
        switch ( P1Choix )
        {
            case 1 :
                MonCanvas->Draw(0, y-ImRoche2->Height+7, ImRoche);
                break;
            case 2 :
                MonCanvas->Draw(0, y-ImRoche2->Height+16, ImPapier);
                break;
            case 3 :
                MonCanvas->Draw(0, y-ImRoche2->Height+8, ImCiseaux);
                break;
            default:
                break;
        }

        x = GLancer->Width / 2;                            // Emplacement du texte
        y = 0;

        // Détermine si c'est une victoire, défaite ou nulle
        if ((P1Choix == 1 && P2Choix == 3) ||
            (P1Choix == 2 && P2Choix == 1) ||
            (P1Choix == 3 && P2Choix == 2))
        {
            Wins++;
            Win->Caption = Wins;

            String Texte = "WIN";
            MonCanvas->Font->Color = (TColor)RGB(255, 254, 255);
            MonCanvas->TextOut(x+1, y+1, Texte);
            MonCanvas->Font->Color = clBlack;
            MonCanvas->TextOut(x, y, Texte);
        }
        if ((P2Choix == 1 && P1Choix == 3) ||
            (P2Choix == 2 && P1Choix == 1) ||
            (P2Choix == 3 && P1Choix == 2))
        {
            Losts++;
            Lost->Caption = Losts;

            String Texte = "LOST";
            MonCanvas->Font->Color = (TColor)RGB(255, 254, 255);
            MonCanvas->TextOut(x+1, y+1, Texte);
            MonCanvas->Font->Color = clBlack;
            MonCanvas->TextOut(x, y, Texte);
        }
        if ((P2Choix == 1 && P1Choix == 1) ||
            (P2Choix == 2 && P1Choix == 2) ||
            (P2Choix == 3 && P1Choix == 3))
        {
            Ties++;
            Tie->Caption=Ties;

            String Texte = "TIE";
            MonCanvas->Font->Color = (TColor)RGB(255, 254, 255);
            MonCanvas->TextOut(x+1, y+1, Texte);
            MonCanvas->Font->Color = clBlack;
            MonCanvas->TextOut(x, y, Texte);
        }

        // On réactive pour une nouvelle joute
        P1Choix = 0;
        P2Choix = 0;
        // On enable les boutons pour pouvoir jouer à nouveau
        Roche1->Enabled = true;
        Papier1->Enabled = true;
        Ciseaux1->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Reception(TCustomWinSocket *Socket)
{
    String LText = Socket->ReceiveText();

    if (LText == "!ChoixEvoyer$1" || LText == "!ChoixEvoyer$2" || LText == "!ChoixEvoyer$3")
    {
        if (LText == "!ChoixEvoyer$1")
        {
            P2Choix = 1;
        }
        if (LText == "!ChoixEvoyer$2")
        {
            P2Choix = 2;
        }
        if (LText == "!ChoixEvoyer$3")
        {
            P2Choix = 3;
        }

        Compare();
        StatusBar1->Panels->Items[0]->Text = "Waiting for you";
    }
    else if (LText == "éèNewGameéè")
    {
        // NewGame1Click(NULL);
        Win->Caption = "0";       // On met l'affichage à zéro
        Lost->Caption = "0";
        Tie->Caption = "0";
        Wins = 0;                 // On met les scores à zéro
        Losts = 0;
        Ties = 0;
        // On enlève les mains pour mettre le logo
        GLancer->Canvas->FillRect(Rect(0, 0, GLancer->Width, GLancer->Height));
        Logo->Visible = true;     // Remet le titre (logo)
    }
    else
    {
        Memo2->Lines->Add(NickServer + ": " + LText);     // Met le texte dans Memo2
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Play(int AChoice)
{
    // On enlève toutes les mains
    GLancer->Canvas->FillRect(Rect(0, 0, GLancer->Width, GLancer->Height));
    Logo->Visible = false; // Enlève le titre

    P1Choix = AChoice;     // Choix du joueur UN

    if (IsServer == true)
    {
        ServerSocket->Socket->Connections[0]->SendText(
            AnsiString("!ChoixEvoyer$") + P1Choix);}    // On envoie des instructions au Serveur
    else
    {
        ClientSocket->Socket->SendText(
            AnsiString("!ChoixEvoyer$") + P1Choix);}    // On envoie des instructions au client

    if ((ClientSocket->Active == true || IsServer == true)) // Joue contre un vrai joueur
    {
        StatusBar1->Panels->Items[0]->Text = "Waiting for opponent";
        // On disable les boutons pour que le joueur attente l'autre joueur
        Roche1->Enabled = false;
        Papier1->Enabled = false;
        Ciseaux1->Enabled = false;
        Compare();
    }
    else
    {                       // On joue contre le CPU
        P2Choix = random(3) + 1;    // Choix du computer, super AI
        Compare();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Quitter1Click(TObject *Sender)
{
    Close(); // Ferme le programme
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Disconnectec1Click(TObject *Sender)
{
    Listen(true); // On se met en mode d'écoute
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SendClick(TObject *Sender)
{
  if ((ClientSocket->Active == true || IsServer == true))
  {
     if (IsServer == true)
     {
        ServerSocket->Socket->Connections[0]->SendText(Memo1->Text);
        Memo2->Lines->Add("You: " + Memo1->Text);     //Met le texte dans Memo2
     }
         // On envoie la dernière ligne de Memo1 par le Serveur
     else
     {
        ClientSocket->Socket->SendText(Memo1->Text);
        Memo2->Lines->Add("You: " + Memo1->Text);     // Met le texte dans Memo2
     }
        // On envoie la dernière ligne de Memo1 par le client

     Memo1->Clear();   // Efface la zone de message
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Connecttoopponent1Click(TObject *Sender)
{
    if (InputQuery("Connect to Opponent", "IP number of your opponent:", IPServer) == true)
    // Ouvre une boîte de saisie pour entrer une valeur dans Serveur
    {
        if (IPServer.IsEmpty() == false)
        {
            ConnectServer(IPServer);
            NewGame1Click(NULL);            // On fait une nouvelle game
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocketError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    // Écrit un message d'erreur
    ShowMessage(AnsiString("Error connecting to: ") + IPServer + ".");
    ErrorCode = 0;
    Listen(true);         //On est en écoute
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocketRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
    Reception(Socket);    // Réception d'un message
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocketAccept(TObject *Sender,
      TCustomWinSocket *Socket)
{
    // Se produit dans un socket serveur immédiatement après l'acceptation de la
    // connexion avec un socket client.
    IsServer = true; // On met IsServer à VRAI, on est client et connecté
    StatusBar1->Panels->Items[0]->Text = "Connect to: " + Socket->RemoteAddress;
    Disconnectec1->Enabled = true;
    NickServer = "Opponent";         // Versus Distant
    // C'est ici que l'on envoie les setting du serveur
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocketClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    Memo2->Lines->Clear();        // Efface les lignes de Memo2 (Réception)
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocketClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    Listen(true);         // On est en écoute
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
    Reception(Socket);    // Réception d'un message
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocketConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    StatusBar1->Panels->Items[0]->Text = "Connect to: " + Socket->RemoteHost;
    // Écrit dans la bar d'état l'adresse à la quelle il tente de se connecter
    Disconnectec1->Enabled = true;
    NickServer = "Opponent";         // Versus Distant
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocketDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    Listen(true);        //On est en écoute
}
//---------------------------------------------------------------------------

void __fastcall TForm1::About1Click(TObject *Sender)
{
    AboutBox->ShowModal();  // Affiche le About
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NewGame1Click(TObject *Sender)
{
    if ((ClientSocket->Active == true || IsServer == true)) // Joue online
    {
        if (IsServer == true)
        {
            ServerSocket->Socket->Connections[0]->SendText(
                AnsiString("éèNewGameéè"));
        }    // On envoie des instructions au Serveur
        else
        {
            ClientSocket->Socket->SendText(
                AnsiString("éèNewGameéè"));
        }    // On envoie des instructions au client
    }

    // Reset les comptes de moves
    StatsJoueur.Roche = 0;
    StatsJoueur.Papier = 0;
    StatsJoueur.Ciseaux = 0;
    Win->Caption = "0";       // On met l'affichage à zéro
    Lost->Caption = "0";
    Tie->Caption = "0";
    Wins = 0;                 // On met les scores à zéro
    Losts = 0;
    Ties = 0;
    // On enlève les mains pour mettre le logo
    GLancer->Canvas->FillRect(Rect(0, 0, GLancer->Width, GLancer->Height));
    Logo->Visible = true;     // Remet le titre (logo)
    // Si on avait fait un choix avant d'être déconnecter, on enable tout
    Roche1->Enabled = true;
    Papier1->Enabled = true;
    Ciseaux1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HelpTopic1Click(TObject *Sender)
{
    Application->HelpFile = "rps.hlp";           // Donne le nom du fichier
    Application->HelpCommand(HELP_CONTENTS, 0);  // Affichage de l'aide
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Roche1Click(TObject *Sender)
{
    if (Son == true && FileExists("rock.wav") == true)
    {
        sndPlaySound(L"rock.wav", SND_ASYNC);
    }
    StatsJoueur.Roche++; // Compte le nombre de Roche
    Play(1); // On choisi Roche
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Papier1Click(TObject *Sender)
{
    if (Son == true && FileExists("paper.wav") == true)
    {
        sndPlaySound(L"paper.wav", SND_ASYNC);
    }
    StatsJoueur.Papier++; // Compte le nombre de Papier
    Play(2); // On choisi Papier
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Ciseaux1Click(TObject *Sender)
{
    if (Son == true && FileExists("scissors.wav") == true)
    {
        sndPlaySound(L"scissors.wav", SND_ASYNC);
    }
    StatsJoueur.Ciseaux++; // Compte le nombre de Ciseaux
    Play(3); // On choisi Ciseaux
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Sound1Click(TObject *Sender)
{
    Sound1->Checked = !Sound1->Checked;
    Son = Sound1->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PlayerMidiNotify(TObject *Sender)
{
    // C'est ici que l'on fait looper la musique
    // Play déclanche un PlayerMidi->Notify = true;
    if (Musique == true)
    {
        PlayerMidi->Play();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Music1Click(TObject *Sender)
{
    Music1->Checked = !Music1->Checked;
    if (Music1->Checked == true)
    {
        // Start music
        Musique = true;
        try
        {
             PlayerMidi->Open();
             PlayerMidi->Play();
        }
        catch ( ... )
        {
        }
    }
    else
    {
        // Stop music
        Musique = false;
        PlayerMidi->Stop();
        PlayerMidi->Close();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Statistics1Click(TObject *Sender)
{
    const float Total = Ties + Wins + Losts;
    ShowMessage(AnsiString("Wining ratio : ") + Wins/Total*100 + "%\nNumber of Round : "+ Total+ "\nNumber of Rock: "+ StatsJoueur.Roche + "\nNumber of Paper :" + StatsJoueur.Papier + "\nNumber of Cissors :" + StatsJoueur.Ciseaux);
}
//---------------------------------------------------------------------------

