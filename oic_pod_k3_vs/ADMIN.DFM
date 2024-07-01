object AdminForm: TAdminForm
  Left = 451
  Top = 349
  Width = 252
  Height = 87
  Caption = #1042#1077#1088#1089#1080#1103
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
    Left = 0
    Top = 0
    Width = 137
    Height = 57
    TabOrder = 0
  end
  object HardRadioButton: TRadioButton
    Left = 16
    Top = 16
    Width = 113
    Height = 17
    Caption = #1076#1083#1103' CPU686E'
    TabOrder = 1
  end
  object ProgRadioButton: TRadioButton
    Left = 16
    Top = 32
    Width = 113
    Height = 17
    Caption = #1090#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1077
    Checked = True
    TabOrder = 2
    TabStop = True
  end
  object Button1: TButton
    Left = 144
    Top = 32
    Width = 97
    Height = 25
    Caption = #1040#1056#1052' '#1084#1072#1096#1080#1085#1080#1089#1090#1072
    TabOrder = 3
    OnClick = Button1Click
  end
end
