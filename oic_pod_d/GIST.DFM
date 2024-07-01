object GistForm: TGistForm
  Left = 1
  Top = 94
  Width = 1010
  Height = 614
  Caption = #1043#1080#1089#1090#1086#1075#1088#1072#1084#1084#1099' '#1073#1072#1083#1072#1085#1089#1072' '
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
  object VagonChart: TDBChart
    Left = 0
    Top = 0
    Width = 330
    Height = 273
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      #1042#1099#1076#1072#1085#1086)
    Legend.Visible = False
    TabOrder = 0
    object Series1: TBarSeries
      Marks.ArrowLength = 20
      Marks.Visible = True
      SeriesColor = clGreen
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Bar'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object RTPChart: TDBChart
    Left = 336
    Top = 0
    Width = 330
    Height = 273
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1087#1088#1077#1076#1086#1093#1088#1072#1085#1080#1090#1077#1083#1100#1085#1099#1093' '#1090#1086#1088#1084#1086#1078#1077#1085#1080#1081)
    Legend.Visible = False
    TabOrder = 1
    object Series2: TBarSeries
      Marks.ArrowLength = 20
      Marks.Visible = True
      SeriesColor = clRed
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Bar'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object CPChart: TDBChart
    Left = 672
    Top = 0
    Width = 330
    Height = 273
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      #1062#1080#1082#1083#1086#1074' '#1087#1086#1076#1098#1077#1084#1072)
    Legend.Visible = False
    TabOrder = 2
    object Series3: TBarSeries
      Marks.ArrowLength = 20
      Marks.Visible = True
      SeriesColor = clYellow
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Bar'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object PChart: TDBChart
    Left = 0
    Top = 280
    Width = 330
    Height = 273
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      #1069#1083#1077#1082#1090#1088#1086#1101#1085#1077#1088#1075#1080#1103' ('#1088#1072#1089#1093#1086#1076')')
    Legend.Visible = False
    TabOrder = 3
    object Series4: TBarSeries
      Marks.ArrowLength = 20
      Marks.Visible = True
      SeriesColor = 16744448
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Bar'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object MHChart: TDBChart
    Left = 336
    Top = 280
    Width = 330
    Height = 273
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      #1052#1086#1090#1086#1095#1072#1089#1099)
    Legend.Visible = False
    TabOrder = 4
    object Series5: TBarSeries
      Marks.ArrowLength = 20
      Marks.Visible = True
      SeriesColor = 33023
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Bar'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object LChart: TDBChart
    Left = 672
    Top = 280
    Width = 330
    Height = 273
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      #1055#1088#1086#1081#1076#1077#1085#1085#1099#1081' '#1087#1091#1090#1100)
    Legend.Visible = False
    TabOrder = 5
    object Series6: TBarSeries
      Marks.ArrowLength = 20
      Marks.Visible = True
      SeriesColor = 16512
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Bar'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object CloseButton: TBitBtn
    Left = 926
    Top = 560
    Width = 75
    Height = 25
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 6
    OnClick = CloseButtonClick
    NumGlyphs = 2
  end
end
