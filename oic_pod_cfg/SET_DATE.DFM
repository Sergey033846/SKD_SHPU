object SetDateTimeForm: TSetDateTimeForm
  Left = 339
  Top = 256
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1076#1072#1090#1099' '#1080' '#1074#1088#1077#1084#1077#1085#1080
  ClientHeight = 85
  ClientWidth = 230
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
    Left = 8
    Top = 8
    Width = 29
    Height = 13
    Caption = #1044#1072#1090#1072':'
  end
  object Label2: TLabel
    Left = 128
    Top = 8
    Width = 36
    Height = 13
    Caption = #1042#1088#1077#1084#1103':'
  end
  object DatePicker: TDateTimePicker
    Left = 8
    Top = 24
    Width = 97
    Height = 21
    CalAlignment = dtaLeft
    Date = 36938.894433588
    Time = 36938.894433588
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 0
  end
  object TimePicker: TDateTimePicker
    Left = 128
    Top = 24
    Width = 97
    Height = 21
    CalAlignment = dtaLeft
    Date = 36938.894433588
    Time = 36938.894433588
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkTime
    ParseInput = False
    TabOrder = 1
  end
  object Button1: TButton
    Left = 80
    Top = 56
    Width = 75
    Height = 25
    Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100
    TabOrder = 2
    OnClick = Button1Click
  end
end
