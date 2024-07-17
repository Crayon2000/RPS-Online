object Form1: TForm1
  Left = 369
  Top = 246
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  ClientHeight = 403
  ClientWidth = 505
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  Position = poScreenCenter
  TextHeight = 13
  object CardPanel1: TCardPanel
    Left = 0
    Top = 0
    Width = 505
    Height = 403
    Align = alClient
    ActiveCard = Card2
    Caption = 'CardPanel1'
    TabOrder = 0
    ExplicitLeft = 25
    ExplicitTop = 26
    ExplicitWidth = 300
    ExplicitHeight = 200
    object Card1: TCard
      Left = 1
      Top = 1
      Width = 503
      Height = 401
      Caption = 'Game'
      CardIndex = 0
      TabOrder = 0
      ExplicitLeft = 169
      ExplicitTop = 62
      ExplicitWidth = 298
      ExplicitHeight = 198
      object BoxYou: TGroupBox
        Left = 7
        Top = 0
        Width = 105
        Height = 209
        Caption = 'Play'
        TabOrder = 0
        object Roche1: TSpeedButton
          Left = 8
          Top = 16
          Width = 89
          Height = 57
          OnClick = Roche1Click
        end
        object Papier1: TSpeedButton
          Left = 8
          Top = 80
          Width = 89
          Height = 57
          OnClick = Papier1Click
        end
        object Ciseaux1: TSpeedButton
          Left = 8
          Top = 144
          Width = 89
          Height = 57
          OnClick = Ciseaux1Click
        end
      end
      object GroupBox1: TGroupBox
        Left = 6
        Top = 215
        Width = 489
        Height = 161
        Caption = 'Chat'
        TabOrder = 1
        DesignSize = (
          489
          161)
        object Memo2: TMemo
          Left = 8
          Top = 64
          Width = 473
          Height = 89
          ScrollBars = ssVertical
          TabOrder = 2
        end
        object Memo1: TEdit
          Left = 8
          Top = 24
          Width = 369
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
        end
        object Send: TButton
          Left = 392
          Top = 24
          Width = 89
          Height = 25
          Anchors = [akTop, akRight]
          Caption = 'Send'
          Default = True
          TabOrder = 1
          OnClick = SendClick
        end
        object PlayerMidi: TMediaPlayer
          Left = 24
          Top = 104
          Width = 113
          Height = 25
          ColoredButtons = []
          EnabledButtons = [btPlay, btPause, btStop, btNext, btPrev, btStep, btBack]
          VisibleButtons = [btPlay, btStop, btNext, btPrev]
          AutoOpen = True
          DeviceType = dtSequencer
          DoubleBuffered = True
          Visible = False
          ParentDoubleBuffered = False
          ParentShowHint = False
          ShowHint = False
          TabOrder = 3
          TabStop = False
          OnNotify = PlayerMidiNotify
        end
      end
      object Panel1: TPanel
        Left = 118
        Top = 8
        Width = 377
        Height = 201
        BevelOuter = bvLowered
        TabOrder = 2
        object Logo: TImage
          Left = 128
          Top = 16
          Width = 241
          Height = 169
          Center = True
          Stretch = True
        end
        object Label1: TLabel
          Left = 16
          Top = 72
          Width = 105
          Height = 22
          Alignment = taCenter
          AutoSize = False
          Caption = 'LOSSES'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label2: TLabel
          Left = 16
          Top = 8
          Width = 105
          Height = 22
          Alignment = taCenter
          AutoSize = False
          Caption = 'WINS'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object GLancer: TImage
          Left = 137
          Top = 16
          Width = 224
          Height = 129
          Center = True
          Transparent = True
        end
        object Label3: TLabel
          Left = 16
          Top = 136
          Width = 105
          Height = 22
          Alignment = taCenter
          AutoSize = False
          Caption = 'TIES'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Win: TPanel
          Left = 16
          Top = 32
          Width = 105
          Height = 33
          BevelOuter = bvLowered
          Caption = '0'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -24
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
        end
        object Lost: TPanel
          Left = 16
          Top = 96
          Width = 105
          Height = 33
          BevelOuter = bvLowered
          Caption = '0'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -24
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
        object Tie: TPanel
          Left = 16
          Top = 160
          Width = 105
          Height = 33
          BevelOuter = bvLowered
          Caption = '0'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -24
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
      end
      object StatusBar1: TStatusBar
        Left = 0
        Top = 382
        Width = 503
        Height = 19
        Panels = <
          item
            Width = 50
          end>
        SizeGrip = False
        ExplicitTop = 374
        ExplicitWidth = 488
      end
    end
    object Card2: TCard
      Left = 1
      Top = 1
      Width = 503
      Height = 401
      Caption = 'About'
      CardIndex = 1
      TabOrder = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 185
      ExplicitHeight = 41
      object Label8: TLabel
        AlignWithMargins = True
        Left = 8
        Top = 8
        Width = 487
        Height = 25
        Margins.Left = 8
        Margins.Top = 8
        Margins.Right = 8
        Margins.Bottom = 8
        Align = alTop
        Caption = 'About RPS Online'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ExplicitWidth = 166
      end
      object Panel2: TPanel
        AlignWithMargins = True
        Left = 8
        Top = 49
        Width = 487
        Height = 161
        Margins.Left = 8
        Margins.Top = 8
        Margins.Right = 8
        Margins.Bottom = 8
        Align = alTop
        BevelInner = bvRaised
        BevelOuter = bvLowered
        ParentColor = True
        TabOrder = 0
        ExplicitLeft = 16
        ExplicitTop = 16
        ExplicitWidth = 265
        object ProgramIcon: TImage
          Left = 16
          Top = 16
          Width = 43
          Height = 40
          AutoSize = True
          Transparent = True
          IsControl = True
        end
        object ProductName: TLabel
          Left = 88
          Top = 16
          Width = 90
          Height = 19
          Caption = 'RPS Online'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          IsControl = True
        end
        object Version: TLabel
          Left = 88
          Top = 40
          Width = 64
          Height = 13
          Caption = 'Version 2.0.0'
          IsControl = True
        end
        object Copyright: TLabel
          Left = 8
          Top = 80
          Width = 195
          Height = 13
          Caption = 'Copyright 2001-2024 Crayon Application'
          IsControl = True
        end
        object Comments: TLabel
          Left = 8
          Top = 120
          Width = 120
          Height = 13
          Cursor = crHandPoint
          Caption = 'crayon1@rocketmail.com'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlue
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsUnderline]
          ParentFont = False
          WordWrap = True
          OnClick = CommentsClick
          IsControl = True
        end
        object Label7: TLabel
          Left = 8
          Top = 104
          Width = 153
          Height = 13
          Caption = 'For more info or to report bugs:'
        end
      end
      object GroupBox3: TGroupBox
        AlignWithMargins = True
        Left = 8
        Top = 226
        Width = 487
        Height = 79
        Margins.Left = 8
        Margins.Top = 8
        Margins.Right = 8
        Margins.Bottom = 8
        Align = alTop
        Caption = 'Help'
        TabOrder = 1
        ExplicitLeft = 0
        ExplicitTop = 218
        ExplicitWidth = 503
        object Button1: TButton
          Left = 16
          Top = 32
          Width = 112
          Height = 25
          Caption = 'View Online'
          TabOrder = 0
          OnClick = Button1Click
        end
      end
    end
    object Card3: TCard
      Left = 1
      Top = 1
      Width = 503
      Height = 401
      Caption = 'Host'
      CardIndex = 2
      TabOrder = 2
      ExplicitLeft = 0
      ExplicitTop = 0
    end
    object Card4: TCard
      Left = 1
      Top = 1
      Width = 503
      Height = 401
      Caption = 'Join'
      CardIndex = 3
      TabOrder = 3
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 185
      ExplicitHeight = 41
    end
    object Card5: TCard
      Left = 1
      Top = 1
      Width = 503
      Height = 401
      Caption = 'Settings'
      CardIndex = 4
      TabOrder = 4
      ExplicitLeft = 17
      ExplicitTop = -87
      object Label6: TLabel
        AlignWithMargins = True
        Left = 8
        Top = 8
        Width = 487
        Height = 25
        Margins.Left = 8
        Margins.Top = 8
        Margins.Right = 8
        Margins.Bottom = 8
        Align = alTop
        Caption = 'Settings'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ExplicitWidth = 75
      end
      object GroupBox2: TGroupBox
        AlignWithMargins = True
        Left = 8
        Top = 49
        Width = 487
        Height = 81
        Margins.Left = 8
        Margins.Top = 8
        Margins.Right = 8
        Margins.Bottom = 8
        Align = alTop
        Caption = 'Audio'
        TabOrder = 0
        ExplicitLeft = 0
        ExplicitTop = 160
        object Label4: TLabel
          Left = 16
          Top = 23
          Width = 26
          Height = 13
          Caption = 'Music'
        end
        object Label5: TLabel
          Left = 16
          Top = 49
          Width = 30
          Height = 13
          Caption = 'Sound'
        end
        object SwitchMusic: TToggleSwitch
          Left = 80
          Top = 16
          Width = 72
          Height = 20
          TabOrder = 0
          OnClick = SwitchMusicClick
        end
        object SwitchSound: TToggleSwitch
          Left = 80
          Top = 42
          Width = 72
          Height = 20
          TabOrder = 1
          OnClick = SwitchSoundClick
        end
      end
    end
  end
  object ServerSocket: TServerSocket
    Active = False
    Port = 1024
    ServerType = stNonBlocking
    OnAccept = ServerSocketAccept
    OnClientConnect = ServerSocketClientConnect
    OnClientDisconnect = ServerSocketClientDisconnect
    OnClientRead = ServerSocketClientRead
    Left = 264
    Top = 344
  end
  object ClientSocket: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 1024
    OnConnect = ClientSocketConnect
    OnDisconnect = ClientSocketDisconnect
    OnRead = ClientSocketRead
    OnError = ClientSocketError
    Left = 232
    Top = 344
  end
  object MainMenu1: TMainMenu
    Left = 352
    Top = 344
    object File1: TMenuItem
      Caption = '&Game'
      object NewGame1: TMenuItem
        Caption = '&New'
        ShortCut = 113
        OnClick = NewGame1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Statistics1: TMenuItem
        Caption = '&Statistics'
        Visible = False
        OnClick = Statistics1Click
      end
      object N3: TMenuItem
        Caption = '-'
        Visible = False
      end
      object Quitter1: TMenuItem
        Caption = 'E&xit'
        OnClick = Quitter1Click
      end
    end
    object Network1: TMenuItem
      Caption = '&Network'
      object Connecttoopponent1: TMenuItem
        Caption = '&Connect to Opponent...'
        OnClick = Connecttoopponent1Click
      end
      object Disconnectec1: TMenuItem
        Caption = '&Disconnect'
        Enabled = False
        OnClick = Disconnectec1Click
      end
    end
  end
end
