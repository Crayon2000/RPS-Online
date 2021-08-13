//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "About.h"
#include "ConnectionBox.h"
#include <System.IniFiles.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
        , FPlayer1Choice(TPlayerMove::None) // On a rien choisi encore
        , FPlayer2Choice(TPlayerMove::None) // L'adversaire n'a rien choisi encore
        , FTieCount(0)
        , FWinCount(0)
        , FLostCount(0)
{
    Caption = "RPS Online";

    String Temp_IPServer;

    // Read settings from .ini file
    TIniFile *LIniFile = NULL;
    try
    {
        LIniFile = new TIniFile(ChangeFileExt(Application->ExeName, ".ini"));
        Temp_IPServer   = LIniFile->ReadString ( "Setting", "IP", "192.168.0.2" );
        FMusicEnabled   = LIniFile->ReadBool   ( "Setting", "Music", true );
        FSoundEnabled   = LIniFile->ReadBool   ( "Setting", "Sound", true);
        PortCom         = LIniFile->ReadInteger( "Setting", "Port", 1024 );
    }
    __finally
    {
        delete LIniFile;
    }

    // Prend les paramètres que ICQ envoie (Détection d'arguments)
    // Arguments: ip_address user_name
    IPServer = ParamStr(1);
    NickServer = ParamStr(2);

    // Sert a faire un vrai Random
    randomize();

    // Met les numéros de Port par défaut
    ClientSocket->Port = PortCom;
    ServerSocket->Port = PortCom;

    // Audio
    PlayerMidi->FileName = ExtractFilePath(Application->ExeName) + "\\rps.mid"; // Spécifie le fichier son
    Music1->Checked = !FMusicEnabled; // Par défaut on met de la musique (true=musique)
    Music1Click(NULL);
    Sound1->Checked = !FSoundEnabled; // Par défaut on met du son (true=son)
    Sound1Click(NULL);

    // On load les images du fichier RES
    LoadPng(Logo->Picture->Bitmap, "PNG_TITLE");

    ImRoche2 = new Graphics::TBitmap();
    LoadPng(ImRoche2, "PNG_ROCK");
    ImPapier2 = new Graphics::TBitmap();
    LoadPng(ImPapier2, "PNG_PAPER");
    ImCiseaux2 = new Graphics::TBitmap();
    LoadPng(ImCiseaux2, "PNG_SCISSORS");

    ImRoche = new Graphics::TBitmap();
    ImRoche->Assign(ImRoche2);
    FlipImageH(ImRoche);
    ImPapier = new Graphics::TBitmap();
    ImPapier->Assign(ImPapier2);
    FlipImageH(ImPapier);
    ImCiseaux = new Graphics::TBitmap();
    ImCiseaux->Assign(ImCiseaux2);
    FlipImageH(ImCiseaux);

    // On réutilise les mêmes images
    Roche1->Glyph = ImRoche;
    Papier1->Glyph = ImPapier;
    Ciseaux1->Glyph = ImCiseaux;

    // Met les valeurs par défaut
    if (IPServer.IsEmpty() == true)
    {   // S'il n'y a rien d'écrit
        IPServer = Temp_IPServer;
        Listen(true);
    }
    else
    {
        ConnectServer(IPServer);
    }

    if (NickServer.IsEmpty() == true)
    {   // S'il n'y a rien d'écrit
        NickServer = "CPU Opponent"; // Versus Distant
    }
}
//---------------------------------------------------------------------------

__fastcall TForm1::~TForm1()
{
    try
    {
        // Write settings to .ini file
        TIniFile *LIniFile = NULL;
        try
        {
            LIniFile = new TIniFile(ChangeFileExt(Application->ExeName, ".ini"));
            LIniFile->WriteString ( "Setting", "IP", IPServer );
            LIniFile->WriteBool   ( "Setting", "Music", FMusicEnabled ); // 0 = Off
            LIniFile->WriteBool   ( "Setting", "Sound", FSoundEnabled ); // 1 = On
        }
        __finally
        {
            delete LIniFile;
        }
    }
    catch(...)
    {
        // No exception allowed in destructor
    }

    // On récupère la mémoire
    delete ImRoche;
    delete ImPapier;
    delete ImCiseaux;
    delete ImRoche2;
    delete ImPapier2;
    delete ImCiseaux2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConnectServer(const String IP)
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
    TCanvas *LCanvas = GLancer->Canvas;
    SetBkMode(LCanvas->Handle, TRANSPARENT);
    LCanvas->Font->Name = "Arial";
    LCanvas->Font->Size = 30;
    LCanvas->Font->Style = TFontStyles() << TFontStyle::fsBold;
    SetTextAlign (LCanvas->Handle, TA_CENTER);

    int x = GLancer->Width; // Emplacement des images
    int y = GLancer->Height - 10;

    if (FPlayer1Choice != TPlayerMove::None && FPlayer2Choice != TPlayerMove::None)
    {
        // Affichage des mains Joueurs DEUX et UN
        switch ( FPlayer2Choice )
        {
            case TPlayerMove::Rock:
                LCanvas->Draw(x-ImRoche2->Width , y-ImRoche2->Height+7, ImRoche2);
                break;
            case TPlayerMove::Paper:
                LCanvas->Draw(x-ImPapier2->Width , y-ImRoche2->Height+16, ImPapier2);
                break;
            case TPlayerMove::Scissors:
                LCanvas->Draw(x-ImCiseaux->Width , y-ImRoche2->Height+8, ImCiseaux2);
                break;
            default:
                break;
        }
        switch ( FPlayer1Choice )
        {
            case TPlayerMove::Rock:
                LCanvas->Draw(0, y-ImRoche2->Height+7, ImRoche);
                break;
            case TPlayerMove::Paper:
                LCanvas->Draw(0, y-ImRoche2->Height+16, ImPapier);
                break;
            case TPlayerMove::Scissors:
                LCanvas->Draw(0, y-ImRoche2->Height+8, ImCiseaux);
                break;
            default:
                break;
        }

        x = GLancer->Width / 2; // Emplacement du texte
        y = 0;

        String LText;

        // Détermine si c'est une victoire, défaite ou nulle
        if ((FPlayer1Choice == TPlayerMove::Rock && FPlayer2Choice == TPlayerMove::Scissors) ||
            (FPlayer1Choice == TPlayerMove::Paper && FPlayer2Choice == TPlayerMove::Rock) ||
            (FPlayer1Choice == TPlayerMove::Scissors && FPlayer2Choice == TPlayerMove::Paper))
        {
            FWinCount++;
            Win->Caption = FWinCount;

            LText = "WIN";
        }
        if ((FPlayer2Choice == TPlayerMove::Rock && FPlayer1Choice == TPlayerMove::Scissors) ||
            (FPlayer2Choice == TPlayerMove::Paper && FPlayer1Choice == TPlayerMove::Rock) ||
            (FPlayer2Choice == TPlayerMove::Scissors && FPlayer1Choice == TPlayerMove::Paper))
        {
            FLostCount++;
            Lost->Caption = FLostCount;

            LText = "LOST";
        }
        if ((FPlayer2Choice == TPlayerMove::Rock && FPlayer1Choice == TPlayerMove::Rock) ||
            (FPlayer2Choice == TPlayerMove::Paper && FPlayer1Choice == TPlayerMove::Paper) ||
            (FPlayer2Choice == TPlayerMove::Scissors && FPlayer1Choice == TPlayerMove::Scissors))
        {
            FTieCount++;
            Tie->Caption = FTieCount;

            LText = "TIE";
        }

        // Output text
        LCanvas->Font->Color = static_cast<TColor>(RGB(255, 254, 255));
        LCanvas->TextOut(x + 1, y + 1, LText);
        LCanvas->Font->Color = clBlack;
        LCanvas->TextOut(x, y, LText);

        // On réactive pour une nouvelle joute
        FPlayer1Choice = TPlayerMove::None;
        FPlayer2Choice = TPlayerMove::None;

        // On enable les boutons pour pouvoir jouer à nouveau
        Roche1->Enabled = true;
        Papier1->Enabled = true;
        Ciseaux1->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Reception(TCustomWinSocket *Socket)
{
    TBytes LBytes;
    // ReceiveLength is not guaranteed to be accurate, so we add 100 more bytes
    LBytes.Length = Socket->ReceiveLength() + 100;

    int LRecCount = Socket->ReceiveBuf(&LBytes[0], LBytes.Length);
    if(LRecCount <= 0)
    {   // Nothing received
        return;
    }
    const String LText = TEncoding::UTF8->GetString(LBytes, 0, LRecCount);

    if (LText == "!ChoixEvoyer$1" || LText == "!ChoixEvoyer$2" || LText == "!ChoixEvoyer$3")
    {
        if (LText == "!ChoixEvoyer$1")
        {
            FPlayer2Choice = TPlayerMove::Rock;
        }
        else if (LText == "!ChoixEvoyer$2")
        {
            FPlayer2Choice = TPlayerMove::Paper;
        }
        else if (LText == "!ChoixEvoyer$3")
        {
            FPlayer2Choice = TPlayerMove::Scissors;
        }
        else
        {
            throw Exception("Invalid choice!");
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
        FWinCount = 0;                 // On met les scores à zéro
        FLostCount = 0;
        FTieCount = 0;
        // On enlève les mains pour mettre le logo
        GLancer->Canvas->FillRect(Rect(0, 0, GLancer->Width, GLancer->Height));
        Logo->Visible = true; // Remet le titre (logo)
    }
    else
    {
        Memo2->Lines->Add(NickServer + ": " + LText); // Met le texte dans Memo2
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Play(TPlayerMove AChoice)
{
    // On enlève toutes les mains
    GLancer->Canvas->FillRect(Rect(0, 0, GLancer->Width, GLancer->Height));
    Logo->Visible = false; // Enlève le titre

    FPlayer1Choice = AChoice; // Choix du joueur UN

    TBytes LBytes = TEncoding::UTF8->GetBytes(String("!ChoixEvoyer$") + static_cast<int>(FPlayer1Choice));
    if (IsServer == true)
    {   // On envoie des instructions au Serveur
        ServerSocket->Socket->Connections[0]->SendBuf(&LBytes[0], LBytes.Length);
    }
    else
    {   // On envoie des instructions au client
        ClientSocket->Socket->SendBuf(&LBytes[0], LBytes.Length);
    }

    if (ClientSocket->Active == true || IsServer == true) // Joue contre un vrai joueur
    {
        StatusBar1->Panels->Items[0]->Text = "Waiting for opponent";
        // On disable les boutons pour que le joueur attende l'autre joueur
        Roche1->Enabled = false;
        Papier1->Enabled = false;
        Ciseaux1->Enabled = false;
        Compare();
    }
    else
    {                       // On joue contre le CPU
        FPlayer2Choice = TPlayerMove(random(3) + 1);    // Choix du computer, super AI
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
    if (Memo1->Text.IsEmpty() == true)
    {
        return;
    }
    if ((ClientSocket->Active == true || IsServer == true))
    {
        TBytes LBytes = TEncoding::UTF8->GetBytes(Memo1->Text);
        if (IsServer == true)
        {  // On envoie la dernière ligne de Memo1 par le Serveur
            ServerSocket->Socket->Connections[0]->SendBuf(&LBytes[0], LBytes.Length);
        }
        else
        {  // On envoie la dernière ligne de Memo1 par le client
            ClientSocket->Socket->SendBuf(&LBytes[0], LBytes.Length);
        }
        Memo2->Lines->Add("You: " + Memo1->Text); // Met le texte dans Memo2
        Memo1->Clear(); // Efface la zone de message
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Connecttoopponent1Click(TObject *Sender)
{
    TForm2 *LConnectionBox = NULL;
    try
    {
        LConnectionBox = new TForm2(NULL, &IPServer);
        const int LReturn = LConnectionBox->ShowModal();
        if(LReturn == mrOk && IPServer.IsEmpty() == false)
        {
            ConnectServer(IPServer);
            NewGame1Click(NULL); // On fait une nouvelle game
        }
    }
    __finally
    {
        delete LConnectionBox;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocketError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    // Écrit un message d'erreur
    ShowMessage(String("Error connecting to: ") + IPServer + ".");
    ErrorCode = 0;
    Listen(true); // On est en écoute
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocketRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
    Reception(Socket); // Réception d'un message
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
    NickServer = "Opponent"; // Versus Distant
    // C'est ici que l'on envoie les setting du serveur
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocketClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    Memo2->Lines->Clear(); // Efface les lignes de Memo2 (Réception)
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocketClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    Listen(true); // On est en écoute
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
    Reception(Socket); // Réception d'un message
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocketConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    StatusBar1->Panels->Items[0]->Text = "Connect to: " + Socket->RemoteHost;
    // Écrit dans la bar d'état l'adresse à la quelle il tente de se connecter
    Disconnectec1->Enabled = true;
    NickServer = "Opponent"; // Versus Distant
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocketDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    Listen(true); // On est en écoute
}
//---------------------------------------------------------------------------

void __fastcall TForm1::About1Click(TObject *Sender)
{
    AboutBox->ShowModal(); // Affiche le About
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NewGame1Click(TObject *Sender)
{
    if ((ClientSocket->Active == true || IsServer == true)) // Joue online
    {
        TBytes LBytes = TEncoding::UTF8->GetBytes("éèNewGameéè");
        if (IsServer == true)
        {   // On envoie des instructions au Serveur
            ServerSocket->Socket->Connections[0]->SendBuf(&LBytes[0], LBytes.Length);
        }
        else
        {   // On envoie des instructions au client
            ClientSocket->Socket->SendBuf(&LBytes[0], LBytes.Length);
        }
    }

    // Reset les comptes de moves
    FPlayerStats.Reset();
    // On met l'affichage à zéro
    Win->Caption = "0";
    Lost->Caption = "0";
    Tie->Caption = "0";
    // On met les scores à zéro
    FWinCount = 0;
    FLostCount = 0;
    FTieCount = 0;
    // On enlève les mains pour mettre le logo
    GLancer->Canvas->FillRect(Rect(0, 0, GLancer->Width, GLancer->Height));
    Logo->Visible = true; // Remet le titre (logo)
    // Si on avait fait un choix avant d'être déconnecter, on enable tout
    Roche1->Enabled = true;
    Papier1->Enabled = true;
    Ciseaux1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HelpTopic1Click(TObject *Sender)
{
    ShellExecute(Handle,
                 L"open",
                 L"https://crayon2000.github.io/RPS-Online",
                 NULL, NULL, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Roche1Click(TObject *Sender)
{
    if (FSoundEnabled == true)
    {
        PlaySound(L"rock.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
    }
    FPlayerStats.Rock++; // Compte le nombre de Roche
    Play(TPlayerMove::Rock); // On choisi Roche
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Papier1Click(TObject *Sender)
{
    if (FSoundEnabled == true)
    {
        PlaySound(L"paper.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
    }
    FPlayerStats.Paper++; // Compte le nombre de Papier
    Play(TPlayerMove::Paper); // On choisi Papier
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Ciseaux1Click(TObject *Sender)
{
    if (FSoundEnabled == true)
    {
        PlaySound(L"scissors.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
    }
    FPlayerStats.Scissors++; // Compte le nombre de Ciseaux
    Play(TPlayerMove::Scissors); // On choisi Ciseaux
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Sound1Click(TObject *Sender)
{
    Sound1->Checked = !Sound1->Checked;
    FSoundEnabled = Sound1->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PlayerMidiNotify(TObject *Sender)
{
    // C'est ici que l'on fait looper la musique
    // Play déclanche un PlayerMidi->Notify = true;
    if (FMusicEnabled == true)
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
        FMusicEnabled = true;
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
        FMusicEnabled = false;
        PlayerMidi->Stop();
        PlayerMidi->Close();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Statistics1Click(TObject *Sender)
{
    const float Total = FTieCount + FWinCount + FLostCount;
    ShowMessage(String("Winning ratio: ") + FWinCount/Total*100 + "%\nNumber of Round: " + Total + "\nNumber of Rock: " + FPlayerStats.Rock + "\nNumber of Paper: " + FPlayerStats.Paper + "\nNumber of Cissors: " + FPlayerStats.Scissors);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LoadPng(Graphics::TBitmap *ABitmapImage, const String AIdentifier)
{
    Pngimage::TPngImage* PngImage = new Pngimage::TPngImage;
    try
    {
        PngImage->LoadFromResourceName((NativeUInt)HInstance, AIdentifier);
        ABitmapImage->Assign(PngImage);
    }
    __finally
    {
        delete PngImage;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FlipImageH(Graphics::TBitmap *AImage)
{
    const TRect LSourceRect = Rect(0, 0, AImage->Width, AImage->Height);
    AImage->Canvas->CopyRect(Rect(AImage->Width - 1, 0, -1, AImage->Height),
        AImage->Canvas, LSourceRect);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FlipImageV(Graphics::TBitmap *AImage)
{
    const TRect LSourceRect = Rect(0, 0, AImage->Width, AImage->Height);
    AImage->Canvas->CopyRect(Rect(0, AImage->Height - 1, AImage->Width, -1),
        AImage->Canvas, LSourceRect);
}
//---------------------------------------------------------------------------

