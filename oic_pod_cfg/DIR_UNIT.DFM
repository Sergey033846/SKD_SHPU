object DirForm: TDirForm
  Left = 356
  Top = 239
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1082#1072#1090#1072#1083#1086#1075
  ClientHeight = 253
  ClientWidth = 279
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
  object Label1: TLabel
    Left = 8
    Top = 10
    Width = 30
    Height = 13
    Caption = #1044#1080#1089#1082':'
  end
  object Label2: TLabel
    Left = 8
    Top = 32
    Width = 44
    Height = 13
    Caption = #1050#1072#1090#1072#1083#1086#1075':'
  end
  object Label3: TLabel
    Left = 8
    Top = 208
    Width = 118
    Height = 13
    Caption = 'D:\Projects\oic_pod_cfg'
  end
  object DirectoryListBox1: TDirectoryListBox
    Left = 16
    Top = 48
    Width = 257
    Height = 153
    DirLabel = Label3
    ItemHeight = 16
    TabOrder = 0
  end
  object DriveComboBox1: TDriveComboBox
    Left = 48
    Top = 8
    Width = 209
    Height = 19
    DirList = DirectoryListBox1
    TabOrder = 1
  end
  object BitBtn1: TBitBtn
    Left = 197
    Top = 224
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 2
    NumGlyphs = 2
  end
end
