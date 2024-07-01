object CopyArcForm: TCopyArcForm
  Left = 433
  Top = 333
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1082#1072#1090#1077#1075#1086#1088#1080#1102' '#1072#1088#1093#1080#1074#1072
  ClientHeight = 101
  ClientWidth = 217
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
  object BitBtn1: TBitBtn
    Left = 8
    Top = 72
    Width = 75
    Height = 25
    Caption = #1055#1077#1088#1077#1087#1080#1089#1072#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 0
    NumGlyphs = 2
  end
  object BitBtn2: TBitBtn
    Left = 136
    Top = 72
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1047#1072#1082#1088#1099#1090#1100
    ModalResult = 2
    TabOrder = 1
    NumGlyphs = 2
  end
  object RadioGroup1: TRadioGroup
    Left = 0
    Top = 0
    Width = 217
    Height = 65
    ItemIndex = 0
    Items.Strings = (
      #1072#1082#1090#1091#1072#1083#1100#1085#1099#1081
      #1074#1089#1077' '#1082#1072#1090#1077#1075#1086#1088#1080#1080)
    TabOrder = 2
  end
end
