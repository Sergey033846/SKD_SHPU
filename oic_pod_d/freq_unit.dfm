object FreqForm: TFreqForm
  Left = 495
  Top = 251
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = #1044#1080#1089#1082#1088#1077#1090#1080#1079#1072#1094#1080#1103' '#1086#1087#1077#1088#1072#1090#1080#1074#1085#1086#1075#1086' '#1086#1090#1095#1077#1090#1072
  ClientHeight = 146
  ClientWidth = 278
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object RadioGroup1: TRadioGroup
    Left = 8
    Top = 8
    Width = 265
    Height = 105
    ItemIndex = 0
    Items.Strings = (
      #1074#1089#1077' '#1084#1077#1090#1082#1080
      #1082#1072#1078#1076#1072#1103' 50-'#1072#1103
      #1082#1072#1078#1076#1072#1103' 100-'#1072#1103
      #1082#1072#1078#1076#1072#1103' 200-'#1072#1103)
    TabOrder = 0
  end
  object BitBtn1: TBitBtn
    Left = 120
    Top = 120
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 1
    NumGlyphs = 2
  end
  object BitBtn2: TBitBtn
    Left = 200
    Top = 120
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1047#1072#1082#1088#1099#1090#1100
    ModalResult = 2
    TabOrder = 2
    NumGlyphs = 2
  end
end
