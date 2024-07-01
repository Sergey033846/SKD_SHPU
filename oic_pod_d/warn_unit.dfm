object WarningForm: TWarningForm
  Left = 306
  Top = 150
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1046#1091#1088#1085#1072#1083' '#1090#1088#1077#1074#1086#1075' '#1080' '#1089#1086#1073#1099#1090#1080#1081
  ClientHeight = 386
  ClientWidth = 436
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object StringGrid: TStringGrid
    Left = 0
    Top = 0
    Width = 436
    Height = 353
    Align = alTop
    ColCount = 3
    DefaultRowHeight = 15
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing]
    TabOrder = 0
    ColWidths = (
      30
      84
      312)
  end
  object BitBtn2: TBitBtn
    Left = 360
    Top = 360
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1047#1072#1082#1088#1099#1090#1100
    ModalResult = 2
    TabOrder = 1
    OnClick = BitBtn2Click
    NumGlyphs = 2
  end
  object BitBtn1: TBitBtn
    Left = 248
    Top = 360
    Width = 75
    Height = 25
    Caption = #1051#1077#1075#1077#1085#1076#1072
    TabOrder = 2
    OnClick = BitBtn1Click
  end
end
