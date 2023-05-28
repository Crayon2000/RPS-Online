object AboutBox: TAboutBox
  Left = 335
  Top = 246
  BorderStyle = bsDialog
  ClientHeight = 213
  ClientWidth = 282
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
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
      Width = 60
      Height = 13
      Caption = 'Version 2.0.0'
      IsControl = True
    end
    object Copyright: TLabel
      Left = 8
      Top = 80
      Width = 195
      Height = 13
      Caption = 'Copyright 2001-2023 Crayon Application'
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
    object Label1: TLabel
      Left = 8
      Top = 104
      Width = 153
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
