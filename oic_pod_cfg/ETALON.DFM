object EtalonForm: TEtalonForm
  Left = 280
  Top = 239
  BorderStyle = bsDialog
  Caption = #1069#1090#1072#1083#1086#1085#1085#1099#1077' '#1076#1080#1072#1075#1088#1072#1084#1084#1099' '#1089#1082#1086#1088#1086#1089#1090#1080
  ClientHeight = 122
  ClientWidth = 305
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object RadioGroup1: TRadioGroup
    Left = 144
    Top = 8
    Width = 153
    Height = 65
    Caption = ' '#1057#1082#1086#1088#1086#1089#1090#1085#1086#1081' '#1088#1077#1078#1080#1084' '
    ItemIndex = 0
    Items.Strings = (
      #1088#1072#1079#1075#1086#1085
      #1090#1086#1088#1084#1086#1078#1077#1085#1080#1077)
    TabOrder = 1
  end
  object RadioGroup2: TRadioGroup
    Left = 8
    Top = 8
    Width = 129
    Height = 105
    Caption = ' '#1056#1077#1078#1080#1084' '#1088#1072#1073#1086#1090#1099' '#1064#1055#1052' '
    ItemIndex = 0
    Items.Strings = (
      #1056#1043
      #1056#1051
      #1056#1056
      #1056#1054)
    TabOrder = 0
  end
  object Button9: TButton
    Left = 144
    Top = 88
    Width = 75
    Height = 25
    Caption = #1042#1099#1073#1088#1072#1090#1100
    TabOrder = 2
    OnClick = Button9Click
  end
  object Button10: TButton
    Left = 224
    Top = 88
    Width = 75
    Height = 25
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 3
    OnClick = Button10Click
  end
end
