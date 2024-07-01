object CommConfigForm: TCommConfigForm
  Left = 392
  Top = 283
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1089#1074#1103#1079#1080
  ClientHeight = 117
  ClientWidth = 279
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
    Left = 8
    Top = 8
    Width = 129
    Height = 73
    Caption = ' COM-'#1087#1086#1088#1090' '
    ItemIndex = 0
    Items.Strings = (
      'COM1'
      'COM2')
    TabOrder = 0
  end
  object RadioGroup2: TRadioGroup
    Left = 144
    Top = 8
    Width = 129
    Height = 73
    Caption = ' '#1053#1072#1073#1086#1088' '#1085#1086#1084#1077#1088#1072' '
    ItemIndex = 1
    Items.Strings = (
      #1090#1086#1085#1086#1074#1099#1081
      #1087#1091#1083#1100#1089#1086#1074#1099#1081)
    TabOrder = 1
  end
  object BitBtn1: TBitBtn
    Left = 120
    Top = 88
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 2
    NumGlyphs = 2
  end
  object BitBtn2: TBitBtn
    Left = 200
    Top = 88
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 3
    NumGlyphs = 2
  end
end
