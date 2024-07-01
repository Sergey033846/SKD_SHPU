object AddShedForm: TAddShedForm
  Left = 366
  Top = 245
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'AddShedForm'
  ClientHeight = 139
  ClientWidth = 341
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
  object Label2: TLabel
    Left = 128
    Top = 8
    Width = 33
    Height = 13
    Caption = #1057#1090#1074#1086#1083':'
  end
  object Label1: TLabel
    Left = 128
    Top = 48
    Width = 53
    Height = 13
    Caption = #1044#1077#1081#1089#1090#1074#1080#1077':'
  end
  object TimeEdit: TLabeledEdit
    Left = 8
    Top = 24
    Width = 105
    Height = 21
    EditLabel.Width = 36
    EditLabel.Height = 13
    EditLabel.Caption = #1042#1088#1077#1084#1103':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    MaxLength = 19
    TabOrder = 0
  end
  object StvolEdit: TComboBox
    Left = 128
    Top = 24
    Width = 209
    Height = 21
    ItemHeight = 13
    MaxLength = 29
    TabOrder = 1
    Items.Strings = (
      #1042#1089#1087#1086#1084#1086#1075#1072#1090#1077#1083#1100#1085#1099#1081
      #1043#1083#1072#1074#1085#1099#1081)
  end
  object PhoneEdit: TLabeledEdit
    Left = 8
    Top = 64
    Width = 105
    Height = 21
    EditLabel.Width = 48
    EditLabel.Height = 13
    EditLabel.Caption = #1058#1077#1083#1077#1092#1086#1085':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    MaxLength = 9
    TabOrder = 2
  end
  object BitBtn1: TBitBtn
    Left = 184
    Top = 112
    Width = 73
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 5
    NumGlyphs = 2
  end
  object BitBtn2: TBitBtn
    Left = 264
    Top = 112
    Width = 73
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 6
    NumGlyphs = 2
  end
  object ActionEdit: TComboBox
    Left = 128
    Top = 64
    Width = 209
    Height = 21
    ItemHeight = 13
    MaxLength = 19
    TabOrder = 3
    Items.Strings = (
      #1087#1086#1083#1091#1095#1077#1085#1080#1077' '#1072#1082#1090#1091#1072#1083#1100#1085#1086#1075#1086' '#1072#1088#1093#1080#1074#1072' '#1089#1084#1077#1085#1099
      #1087#1086#1083#1091#1095#1077#1085#1080#1077' '#1072#1082#1090#1091#1072#1083#1100#1085#1086#1081' '#1089#1090#1072#1090#1080#1089#1090#1080#1082#1080
      #1087#1086#1083#1091#1095#1077#1085#1080#1077' <'#1079#1072#1073#1099#1090#1099#1093'> '#1072#1088#1093#1080#1074#1086#1074)
  end
  object BlockCheckBox: TCheckBox
    Left = 128
    Top = 88
    Width = 137
    Height = 17
    Caption = #1079#1072#1087#1088#1077#1090' '#1074#1099#1087#1086#1083#1085#1077#1085#1080#1103
    TabOrder = 4
  end
end
