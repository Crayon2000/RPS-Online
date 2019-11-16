object AboutBox: TAboutBox
  Left = 335
  Top = 246
  BorderStyle = bsDialog
  Caption = 'About RPS Online'
  ClientHeight = 213
  ClientWidth = 282
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 265
    Height = 161
    BevelInner = bvRaised
    BevelOuter = bvLowered
    ParentColor = True
    TabOrder = 0
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
      Width = 93
      Height = 20
      Caption = 'RPS Online'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      IsControl = True
    end
    object Version: TLabel
      Left = 88
      Top = 40
      Width = 83
      Height = 13
      Caption = 'Version beta 1.02'
      IsControl = True
    end
    object Copyright: TLabel
      Left = 8
      Top = 80
      Width = 189
      Height = 13
      Caption = 'Copyright 2001-2002 Crayon Application'
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
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsUnderline]
      ParentFont = False
      WordWrap = True
      OnClick = CommentsClick
      IsControl = True
    end
    object Label1: TLabel
      Left = 8
      Top = 104
      Width = 144
      Height = 13
      Caption = 'For more info or to report bugs:'
    end
  end
  object OKButton: TButton
    Left = 111
    Top = 180
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
end
