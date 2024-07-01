object MsgForm: TMsgForm
  Left = 291
  Top = 333
  ActiveControl = BitBtn1
  BorderStyle = bsDialog
  Caption = #1055#1088#1077#1076#1091#1087#1088#1077#1078#1076#1077#1085#1080#1077
  ClientHeight = 94
  ClientWidth = 287
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 287
    Height = 57
    Align = alTop
    ReadOnly = True
    TabOrder = 0
  end
  object BitBtn1: TBitBtn
    Left = 200
    Top = 64
    Width = 83
    Height = 25
    TabOrder = 1
    OnClick = BitBtn1Click
    Kind = bkOK
  end
end
