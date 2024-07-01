object AddNodeForm: TAddNodeForm
  Left = 324
  Top = 221
  ActiveControl = XEdit
  BorderIcons = [biMinimize, biMaximize]
  BorderStyle = bsToolWindow
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1091#1079#1083#1072
  ClientHeight = 102
  ClientWidth = 215
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
    Left = 24
    Top = 16
    Width = 41
    Height = 13
    Caption = 'X ('#1087#1091#1090#1100'):'
  end
  object Label2: TLabel
    Left = 24
    Top = 40
    Width = 66
    Height = 13
    Caption = 'Y ('#1089#1082#1086#1088#1086#1089#1090#1100'):'
  end
  object XEdit: TEdit
    Left = 112
    Top = 13
    Width = 81
    Height = 21
    TabOrder = 0
    Text = '0'
  end
  object YEdit: TEdit
    Left = 112
    Top = 37
    Width = 81
    Height = 21
    TabOrder = 1
    Text = '0'
  end
  object BitBtn1: TBitBtn
    Left = 16
    Top = 72
    Width = 81
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 2
    NumGlyphs = 2
  end
  object BitBtn2: TBitBtn
    Left = 120
    Top = 72
    Width = 83
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 3
    NumGlyphs = 2
  end
end
