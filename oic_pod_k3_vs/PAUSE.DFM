object PauseForm: TPauseForm
  Left = 298
  Top = 202
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = #1055#1088#1080#1095#1080#1085#1072' '#1087#1088#1086#1089#1090#1086#1103' '#1087#1086#1076#1098#1077#1084#1072
  ClientHeight = 205
  ClientWidth = 220
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
  object BitBtn1: TBitBtn
    Left = 64
    Top = 176
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 0
    OnClick = BitBtn1Click
    NumGlyphs = 2
  end
  object BitBtn2: TBitBtn
    Left = 144
    Top = 176
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1047#1072#1082#1088#1099#1090#1100
    ModalResult = 2
    TabOrder = 1
    OnClick = BitBtn2Click
    NumGlyphs = 2
  end
  object CheckBox1: TCheckBox
    Left = 8
    Top = 8
    Width = 201
    Height = 17
    Caption = #1057#1093#1086#1076' '#1074#1072#1075#1086#1085#1072
    TabOrder = 2
  end
  object CheckBox2: TCheckBox
    Left = 8
    Top = 32
    Width = 201
    Height = 17
    Caption = #1056#1077#1084#1086#1085#1090' '#1084#1077#1093#1072#1085#1080#1079#1072#1094#1080#1080
    TabOrder = 3
  end
  object CheckBox3: TCheckBox
    Left = 8
    Top = 56
    Width = 201
    Height = 17
    Caption = #1054#1090#1089#1091#1090#1089#1090#1074#1080#1077' '#1075#1088#1091#1079#1072
    TabOrder = 4
  end
  object CheckBox4: TCheckBox
    Left = 8
    Top = 80
    Width = 201
    Height = 17
    Caption = #1054#1090#1089#1091#1090#1089#1090#1074#1080#1077' '#1087#1086#1088#1086#1078#1085#1103#1082#1072
    TabOrder = 5
  end
  object CheckBox5: TCheckBox
    Left = 8
    Top = 104
    Width = 201
    Height = 17
    Caption = #1054#1090#1089#1091#1090#1089#1090#1074#1080#1077' '#1089#1078'.'#1074#1086#1079#1076#1091#1093#1072'/'#1101#1083'.'#1101#1085#1077#1088#1075#1080#1080
    TabOrder = 6
  end
  object CheckBox6: TCheckBox
    Left = 8
    Top = 128
    Width = 201
    Height = 17
    Caption = #1055#1083#1072#1085#1086#1074#1072#1103' '#1087#1088#1086#1092#1080#1083#1072#1082#1090#1080#1082#1072
    TabOrder = 7
  end
  object CheckBox7: TCheckBox
    Left = 8
    Top = 152
    Width = 201
    Height = 17
    Caption = #1055#1088#1086#1095#1077#1077
    TabOrder = 8
  end
end
