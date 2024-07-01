object SmenaForm: TSmenaForm
  Left = 357
  Top = 166
  ActiveControl = Button1
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = #1053#1072#1095#1072#1083#1086' '#1089#1084#1077#1085#1099
  ClientHeight = 151
  ClientWidth = 225
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 8
    Width = 55
    Height = 13
    Caption = #1052#1072#1096#1080#1085#1080#1089#1090':'
  end
  object Label2: TLabel
    Left = 8
    Top = 72
    Width = 64
    Height = 13
    Caption = #1043#1086#1088'. '#1084#1072#1089#1090#1077#1088':'
  end
  object Label3: TLabel
    Left = 16
    Top = 32
    Width = 60
    Height = 13
    Caption = #1058#1072#1073'. '#1085#1086#1084#1077#1088':'
  end
  object Label4: TLabel
    Left = 16
    Top = 96
    Width = 60
    Height = 13
    Caption = #1058#1072#1073'. '#1085#1086#1084#1077#1088':'
  end
  object SpeedButton1: TSpeedButton
    Left = 200
    Top = 32
    Width = 15
    Height = 15
    Caption = '*'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton1Click
  end
  object SpeedButton2: TSpeedButton
    Left = 200
    Top = 96
    Width = 15
    Height = 15
    Caption = '*'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton2Click
  end
  object Button1: TButton
    Left = 8
    Top = 120
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    ModalResult = 1
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 144
    Top = 120
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 5
  end
  object ComboBox1: TComboBox
    Left = 80
    Top = 5
    Width = 137
    Height = 19
    Style = csOwnerDrawFixed
    ItemHeight = 13
    Sorted = True
    TabOrder = 0
  end
  object ComboBox2: TComboBox
    Left = 80
    Top = 69
    Width = 137
    Height = 19
    Style = csOwnerDrawFixed
    ItemHeight = 13
    Sorted = True
    TabOrder = 2
  end
  object Edit1: TEdit
    Left = 80
    Top = 30
    Width = 113
    Height = 21
    TabStop = False
    PasswordChar = '*'
    ReadOnly = True
    TabOrder = 1
  end
  object Edit2: TEdit
    Left = 80
    Top = 94
    Width = 113
    Height = 21
    TabStop = False
    PasswordChar = '*'
    ReadOnly = True
    TabOrder = 3
  end
end
