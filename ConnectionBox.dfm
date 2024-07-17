object Form2: TForm2
  Left = 572
  Top = 430
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  ClientHeight = 219
  ClientWidth = 458
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poScreenCenter
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 209
    Height = 153
    Caption = 'IP number of your opponent'
    TabOrder = 0
    object cmdPaste: TButton
      Left = 48
      Top = 112
      Width = 113
      Height = 25
      Caption = 'Paste from clipboard'
      TabOrder = 1
      OnClick = cmdPasteClick
    end
    object txtOpponentIP: TEdit
      Left = 8
      Top = 32
      Width = 193
      Height = 21
      TabOrder = 0
    end
  end
  object GroupBox2: TGroupBox
    Left = 240
    Top = 8
    Width = 209
    Height = 153
    Caption = 'Your own IP numbers'
    TabOrder = 1
    object cmdCopy: TButton
      Left = 52
      Top = 112
      Width = 105
      Height = 25
      Caption = 'Copy to clipboard'
      TabOrder = 1
    end
    object lstMyIP: TListBox
      Left = 8
      Top = 24
      Width = 193
      Height = 65
      ItemHeight = 13
      TabOrder = 0
    end
  end
  object cmdConnect: TButton
    Left = 240
    Top = 184
    Width = 97
    Height = 25
    Caption = 'Connect'
    Default = True
    ModalResult = 1
    TabOrder = 2
    OnClick = CmdConnectClick
  end
  object cmdCancel: TButton
    Left = 353
    Top = 184
    Width = 97
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
  end
end
