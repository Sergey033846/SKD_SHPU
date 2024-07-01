object SmenaForm: TSmenaForm
  Left = 388
  Top = 217
  ActiveControl = Button1
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = #1053#1072#1095#1072#1083#1086' '#1089#1084#1077#1085#1099
  ClientHeight = 92
  ClientWidth = 271
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
    Left = 24
    Top = 16
    Width = 55
    Height = 13
    Caption = #1052#1072#1096#1080#1085#1080#1089#1090':'
  end
  object Label2: TLabel
    Left = 16
    Top = 40
    Width = 64
    Height = 13
    Caption = #1043#1086#1088'. '#1084#1072#1089#1090#1077#1088':'
  end
  object Button1: TButton
    Left = 112
    Top = 64
    Width = 75
    Height = 25
    Caption = #1053#1072#1095#1072#1090#1100
    ModalResult = 1
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 192
    Top = 64
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 1
    OnClick = Button2Click
  end
  object ComboBox1: TComboBox
    Left = 88
    Top = 13
    Width = 169
    Height = 21
    ItemHeight = 13
    Sorted = True
    TabOrder = 2
  end
  object ComboBox2: TComboBox
    Left = 88
    Top = 37
    Width = 169
    Height = 21
    ItemHeight = 13
    Sorted = True
    TabOrder = 3
  end
end
