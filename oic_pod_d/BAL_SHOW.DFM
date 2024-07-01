object BalRepForm: TBalRepForm
  Left = 58
  Top = 124
  BorderStyle = bsDialog
  Caption = #1041#1072#1083#1072#1085#1089' '#1088#1072#1073#1086#1090#1099' '#1064#1055#1052
  ClientHeight = 475
  ClientWidth = 897
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid2: TDBGrid
    Left = 0
    Top = 0
    Width = 897
    Height = 441
    DataSource = DataSource3
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'Rudnik'
        Title.Alignment = taCenter
        Title.Caption = #1056#1091#1076#1085#1080#1082
        Width = 107
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'Stvol'
        Title.Alignment = taCenter
        Title.Caption = #1057#1090#1074#1086#1083
        Width = 106
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'Year111'
        Title.Alignment = taCenter
        Title.Caption = #1043#1086#1076
        Width = 55
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'HalfYear111'
        Title.Alignment = taCenter
        Title.Caption = #1055#1086#1083#1091#1075#1086#1076#1080#1077
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'Quarter111'
        Title.Alignment = taCenter
        Title.Caption = #1050#1074#1072#1088#1090#1072#1083
        Width = 54
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'Month111'
        Title.Alignment = taCenter
        Title.Caption = #1052#1077#1089#1103#1094
        Width = 45
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'Day111'
        Title.Alignment = taCenter
        Title.Caption = #1044#1077#1085#1100
        Width = 39
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'Smena111'
        Title.Alignment = taCenter
        Title.Caption = #1057#1084#1077#1085#1072
        Width = 45
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'SUM OF Vagon'
        Title.Alignment = taCenter
        Title.Caption = #1042#1099#1076#1072#1085#1086
        Width = 59
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'SUM OF RTP'
        Title.Alignment = taCenter
        Title.Caption = #1056#1058#1055
        Width = 46
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'SUM OF CP'
        Title.Alignment = taCenter
        Title.Caption = #1062#1080#1082#1083#1086#1074
        Width = 55
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'SUM OF P'
        Title.Alignment = taCenter
        Title.Caption = #1069#1083'. '#1101#1085#1077#1088#1075#1080#1103
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'SUM OF MH'
        Title.Alignment = taCenter
        Title.Caption = #1052#1086#1090#1086#1095#1072#1089#1099
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'SUM OF L'
        Title.Alignment = taCenter
        Title.Caption = #1055#1091#1090#1100
        Visible = True
      end>
  end
  object BitBtn2: TBitBtn
    Left = 822
    Top = 448
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1047#1072#1082#1088#1099#1090#1100
    ModalResult = 2
    TabOrder = 1
    NumGlyphs = 2
  end
  object GistButton: TBitBtn
    Left = 600
    Top = 448
    Width = 97
    Height = 25
    Caption = #1044#1080#1072#1075#1088#1072#1084#1084#1099
    TabOrder = 2
    OnClick = GistButtonClick
    Glyph.Data = {
      26040000424D2604000000000000360000002800000012000000120000000100
      180000000000F003000000000000000000000000000000000000D6DBDED6DBDE
      D6DBDED6DBDED6DBDED6DBDED6DBDED6DBDED6DBDED6DBDED6DBDED6DBDED6DB
      DED6DBDED6DBDED6DBDED6DBDED6DBDE0000D6DBDE4A4D4A4A4D4A4A4D4A4A4D
      4A4A4D4A4A4D4A4A4D4A4A4D4A4A4D4A4A4D4A4A4D4A4A4D4A4A4D4A4A4D4AD6
      DBDED6DBDED6DBDE0000D6DBDE4A4D4AA5A6A5FFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4A4D4AD6DBDED6DBDE
      0000D6DBDE4A4D4AD6D3D64A4D4A4A4D4A4A4D4AFFFFFF4A4D4A4A4D4A4A4D4A
      A5A6A54A4D4A4A4D4A4A4D4A4A4D4AA5A6A54A4D4AD6DBDE0000D6DBDE4A4D4A
      A5A6A54A4D4AFF4D4AFF4D4A4A4D4A4A4D4A4AFFFF4AFFFF4A4D4A4A4D4A4A4D
      FF4A4DFF4A4DA54A4D4A4A4D4AD6DBDE0000D6DBDE4A4D4AA5A6A54A4D4AFF4D
      4AFF4D4AA54D4A4A4D4A4AFFFF4AFFFF4AA6A54A4D4A4A4DFF4A4DFF4A4DA54A
      4D4AD6DBDED6DBDE0000D6DBDE4A4D4AA5A6A54A4D4AFF4D4AFF4D4AA54D4A4A
      4D4A4AFFFF4AFFFF4AA6A54A4D4A4A4DFF4A4DFF4A4DA54A4D4AD6DBDED6DBDE
      0000D6DBDE4A4D4AA5A6A54A4D4AFF4D4AFF4D4AA54D4A4A4D4A4AFFFF4AFFFF
      4AA6A54A4D4A4A4DFF4A4DFF4A4DA54A4D4AD6DBDED6DBDE0000D6DBDE4A4D4A
      A5A6A54A4D4AFF4D4AFF4D4AA54D4A4A4D4A4AFFFF4AFFFF4AA6A54A4D4A4A4D
      FF4A4DFF4A4DA54A4D4AD6DBDED6DBDE0000D6DBDE4A4D4AD6D3D64A4D4AFF4D
      4AFF4D4AA54D4A4A4D4A4AFFFF4AFFFF4AA6A54A4D4A4A4DFF4A4DFF4A4DA54A
      4D4AD6DBDED6DBDE0000D6DBDE4A4D4AA5A6A5D6D3D64A4D4A4A4D4A4A4D4A4A
      4D4A4AFFFF4AFFFF4AA6A54A4D4A4A4DFF4A4DFF4A4DA54A4D4AD6DBDED6DBDE
      0000D6DBDE4A4D4AD6D3D6A5A6A54A4D4AD6DBDED6DBDE4A4D4A4AFFFF4AFFFF
      4AA6A54A4D4A4A4DFF4A4DFF4A4DA54A4D4AD6DBDED6DBDE0000D6DBDE4A4D4A
      A5A6A5D6D3D64A4D4AD6DBDED6DBDE4A4D4A4AFFFF4AFFFF4AA6A54A4D4A4A4D
      4A4A4DFF4A4DA54A4D4AD6DBDED6DBDE0000D6DBDE4A4D4AFFFFFFA5A6A54A4D
      4AD6DBDED6DBDE4A4D4A4AFFFF4AFFFF4AA6A54A4D4AD6DBDE4A4D4A4A4D4A4A
      4D4AD6DBDED6DBDE0000D6DBDED6DBDE4A4D4AFFFFFF4A4D4AD6DBDED6DBDE4A
      4D4A4AFFFF4AFFFFD6D3D64A4D4AD6DBDED6DBDED6DBDED6DBDED6DBDED6DBDE
      0000D6DBDED6DBDED6DBDE4A4D4A4A4D4AD6DBDED6DBDED6DBDE4A4D4A4A4D4A
      4A4D4A4A4D4AD6DBDED6DBDED6DBDED6DBDED6DBDED6DBDE0000D6DBDED6DBDE
      D6DBDED6DBDE4A4D4AD6DBDED6DBDED6DBDED6DBDED6DBDED6DBDED6DBDED6DB
      DED6DBDED6DBDED6DBDED6DBDED6DBDE0000D6DBDED6DBDED6DBDED6DBDED6DB
      DED6DBDED6DBDED6DBDED6DBDED6DBDED6DBDED6DBDED6DBDED6DBDED6DBDED6
      DBDED6DBDED6DBDE0000}
  end
  object BitBtn1: TBitBtn
    Left = 496
    Top = 448
    Width = 97
    Height = 25
    Caption = 'Excel'
    TabOrder = 3
    OnClick = BitBtn1Click
  end
  object Table2: TTable
    FieldDefs = <
      item
        Name = 'Year111'
        DataType = ftString
        Size = 5
      end
      item
        Name = 'HalfYear111'
        DataType = ftString
        Size = 5
      end
      item
        Name = 'Quarter111'
        DataType = ftString
        Size = 5
      end
      item
        Name = 'Month111'
        DataType = ftString
        Size = 5
      end
      item
        Name = 'Day111'
        DataType = ftString
        Size = 5
      end
      item
        Name = 'Smena111'
        DataType = ftString
        Size = 5
      end
      item
        Name = 'Rudnik'
        DataType = ftString
        Size = 30
      end
      item
        Name = 'Stvol'
        DataType = ftString
        Size = 30
      end
      item
        Name = 'Vagon'
        DataType = ftInteger
      end
      item
        Name = 'RTP'
        DataType = ftInteger
      end
      item
        Name = 'CP'
        DataType = ftInteger
      end
      item
        Name = 'P'
        DataType = ftFloat
      end
      item
        Name = 'MH'
        DataType = ftFloat
      end
      item
        Name = 'L'
        DataType = ftFloat
      end>
    StoreDefs = True
    Left = 48
    Top = 48
  end
  object DataSource2: TDataSource
    DataSet = Table2
    Left = 16
    Top = 48
  end
  object DataSource3: TDataSource
    DataSet = Query1
    Left = 240
    Top = 48
  end
  object Query1: TQuery
    AutoCalcFields = False
    DataSource = DataSource2
    Left = 272
    Top = 48
  end
  object Table1: TTable
    DatabaseName = 'c:\projects\oic_pod_d'
    TableName = 'balans.DB'
    Left = 144
    Top = 48
  end
end
