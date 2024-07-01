object DiagRTPForm: TDiagRTPForm
  Left = 74
  Top = 96
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = #1044#1080#1072#1075#1088#1072#1084#1084#1099' '#1055#1058
  ClientHeight = 413
  ClientWidth = 752
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StringGrid: TStringGrid
    Left = 0
    Top = 0
    Width = 752
    Height = 353
    Align = alTop
    ColCount = 11
    DefaultRowHeight = 15
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing]
    TabOrder = 0
    ColWidths = (
      30
      84
      82
      74
      80
      57
      64
      64
      64
      64
      64)
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 360
    Width = 169
    Height = 49
    Caption = ' '#1054#1090#1095#1077#1090#1099' '
    TabOrder = 1
    object RepIstButton: TBitBtn
      Left = 88
      Top = 16
      Width = 75
      Height = 25
      Caption = 'I'#1089#1090
      TabOrder = 0
      OnClick = RepIstButtonClick
    end
    object RepUtgButton: TBitBtn
      Left = 8
      Top = 16
      Width = 75
      Height = 25
      Caption = 'U'#1090#1075
      TabOrder = 1
      OnClick = RepUtgButtonClick
    end
  end
  object CloseButton: TBitBtn
    Left = 664
    Top = 384
    Width = 83
    Height = 25
    Cancel = True
    Caption = #1047#1072#1082#1088#1099#1090#1100
    ModalResult = 2
    TabOrder = 2
    OnClick = CloseButtonClick
    NumGlyphs = 2
  end
end
