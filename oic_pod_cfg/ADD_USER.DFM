object AddUserForm: TAddUserForm
  Left = 423
  Top = 173
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103
  ClientHeight = 182
  ClientWidth = 222
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
    Left = 8
    Top = 56
    Width = 125
    Height = 13
    Caption = #1050#1072#1090#1077#1075#1086#1088#1080#1103' '#1087#1086#1083#1100#1079#1086#1074#1072#1085#1080#1103':'
  end
  object NameEdit: TLabeledEdit
    Left = 8
    Top = 24
    Width = 209
    Height = 21
    EditLabel.Width = 25
    EditLabel.Height = 13
    EditLabel.Caption = #1048#1084#1103':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    MaxLength = 19
    TabOrder = 0
  end
  object BitBtn1: TBitBtn
    Left = 8
    Top = 152
    Width = 73
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 3
    NumGlyphs = 2
  end
  object BitBtn2: TBitBtn
    Left = 144
    Top = 152
    Width = 73
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 4
    NumGlyphs = 2
  end
  object GroupEdit: TComboBox
    Left = 8
    Top = 72
    Width = 209
    Height = 21
    ItemHeight = 13
    MaxLength = 19
    TabOrder = 1
    Items.Strings = (
      #1084#1072#1096#1080#1085#1080#1089#1090
      #1084#1072#1089#1090#1077#1088
      #1072#1076#1084#1080#1085#1080#1089#1090#1088#1072#1090#1086#1088
      #1076#1080#1089#1087#1077#1090#1095#1077#1088)
  end
  object PasswordEdit: TLabeledEdit
    Left = 8
    Top = 120
    Width = 209
    Height = 21
    EditLabel.Width = 41
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1072#1088#1086#1083#1100':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    MaxLength = 9
    PasswordChar = '*'
    TabOrder = 2
  end
end
