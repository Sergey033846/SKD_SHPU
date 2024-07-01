object PasswForm: TPasswForm
  Left = 192
  Top = 107
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = #1055#1072#1088#1086#1083#1100
  ClientHeight = 189
  ClientWidth = 104
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object SpeedButton1: TSpeedButton
    Left = 72
    Top = 128
    Width = 23
    Height = 22
    Caption = 'C'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    OnClick = SpeedButton1Click
  end
  object Button1: TButton
    Left = 8
    Top = 32
    Width = 25
    Height = 25
    Caption = '1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 40
    Top = 32
    Width = 25
    Height = 25
    Caption = '2'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 72
    Top = 32
    Width = 25
    Height = 25
    Caption = '3'
    TabOrder = 2
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 8
    Top = 64
    Width = 25
    Height = 25
    Caption = '4'
    TabOrder = 3
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 40
    Top = 64
    Width = 25
    Height = 25
    Caption = '5'
    TabOrder = 4
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 72
    Top = 64
    Width = 25
    Height = 25
    Caption = '6'
    TabOrder = 5
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 8
    Top = 96
    Width = 25
    Height = 25
    Caption = '7'
    TabOrder = 6
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 40
    Top = 96
    Width = 25
    Height = 25
    Caption = '8'
    TabOrder = 7
    OnClick = Button8Click
  end
  object Button9: TButton
    Left = 72
    Top = 96
    Width = 25
    Height = 25
    Caption = '9'
    TabOrder = 8
    OnClick = Button9Click
  end
  object Button10: TButton
    Left = 8
    Top = 128
    Width = 25
    Height = 25
    Caption = '0'
    TabOrder = 9
    OnClick = Button10Click
  end
  object Edit1: TEdit
    Left = 8
    Top = 6
    Width = 89
    Height = 21
    TabStop = False
    PasswordChar = '*'
    ReadOnly = True
    TabOrder = 10
  end
  object BitBtn1: TBitBtn
    Left = 8
    Top = 160
    Width = 41
    Height = 25
    Caption = #1044#1072
    Default = True
    ModalResult = 1
    TabOrder = 11
    NumGlyphs = 2
  end
  object BitBtn2: TBitBtn
    Left = 56
    Top = 160
    Width = 41
    Height = 25
    Cancel = True
    Caption = #1053#1077#1090
    ModalResult = 2
    TabOrder = 12
    NumGlyphs = 2
  end
end
