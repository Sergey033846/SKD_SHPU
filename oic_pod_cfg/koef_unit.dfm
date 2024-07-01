object KoefForm: TKoefForm
  Left = 290
  Top = 169
  BorderStyle = bsDialog
  Caption = #1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1099
  ClientHeight = 440
  ClientWidth = 535
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
  object OkButton: TButton
    Left = 376
    Top = 408
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    TabOrder = 1
    OnClick = OkButtonClick
  end
  object NoButton: TButton
    Left = 456
    Top = 408
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 2
    OnClick = NoButtonClick
  end
  object GroupBox2: TGroupBox
    Left = 360
    Top = 24
    Width = 169
    Height = 73
    Caption = ' '#1047#1072#1074#1080#1089#1080#1084#1086#1089#1090#1080' '
    TabOrder = 0
    object Label9: TLabel
      Left = 16
      Top = 20
      Width = 51
      Height = 13
      Caption = '1 '#1084'/'#1089' ~ '#1042':'
    end
    object Label59: TLabel
      Left = 16
      Top = 44
      Width = 75
      Height = 13
      Caption = '1 '#1084'/'#1089' ~ '#1080#1084#1087'/'#1089':'
    end
    object Edit60: TEdit
      Left = 104
      Top = 17
      Width = 49
      Height = 21
      TabOrder = 0
      Text = '32'
    end
    object Edit57: TEdit
      Left = 104
      Top = 41
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '250'
    end
  end
  object GroupBox3: TGroupBox
    Left = 360
    Top = 104
    Width = 170
    Height = 193
    TabOrder = 3
    object Label10: TLabel
      Left = 16
      Top = 164
      Width = 91
      Height = 13
      Caption = #1044#1083#1080#1085#1072' '#1089#1090#1074#1086#1083#1072' ('#1084'):'
    end
    object Label62: TLabel
      Left = 16
      Top = 20
      Width = 34
      Height = 13
      Caption = #1055#1055' - 0:'
    end
    object Label63: TLabel
      Left = 16
      Top = 44
      Width = 24
      Height = 13
      Caption = '0 - 1:'
    end
    object Label64: TLabel
      Left = 16
      Top = 68
      Width = 24
      Height = 13
      Caption = '1 - 2:'
    end
    object Label65: TLabel
      Left = 16
      Top = 92
      Width = 24
      Height = 13
      Caption = '2 - 3:'
    end
    object Label66: TLabel
      Left = 16
      Top = 116
      Width = 24
      Height = 13
      Caption = '3 - 4:'
    end
    object Label67: TLabel
      Left = 16
      Top = 140
      Width = 24
      Height = 13
      Caption = '4 - 5:'
    end
    object LMAXEdit: TEdit
      Left = 112
      Top = 161
      Width = 49
      Height = 21
      TabOrder = 0
      Text = '300'
    end
    object Edit61: TEdit
      Left = 56
      Top = 17
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '50'
    end
    object Edit62: TEdit
      Left = 56
      Top = 41
      Width = 49
      Height = 21
      TabOrder = 2
      Text = '50'
    end
    object Edit63: TEdit
      Left = 56
      Top = 65
      Width = 49
      Height = 21
      TabOrder = 3
      Text = '50'
    end
    object Edit64: TEdit
      Left = 56
      Top = 89
      Width = 49
      Height = 21
      TabOrder = 4
      Text = '50'
    end
    object Edit65: TEdit
      Left = 56
      Top = 113
      Width = 49
      Height = 21
      TabOrder = 5
      Text = '50'
    end
    object Edit66: TEdit
      Left = 56
      Top = 137
      Width = 49
      Height = 21
      TabOrder = 6
      Text = '50'
    end
  end
  object PageControl1: TPageControl
    Left = 8
    Top = 8
    Width = 345
    Height = 337
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 4
    object TabSheet1: TTabSheet
      Caption = #1056#1043
      object Label43: TLabel
        Left = 232
        Top = 208
        Width = 41
        Height = 13
        Caption = 'dL '#1079#1072#1084'.:'
      end
      object Label44: TLabel
        Left = 232
        Top = 184
        Width = 44
        Height = 13
        Caption = 'dL '#1088#1072#1079#1075'.:'
      end
      object Label51: TLabel
        Left = 232
        Top = 232
        Width = 45
        Height = 13
        Caption = 'dV '#1088#1072#1079#1075'.:'
      end
      object Label52: TLabel
        Left = 232
        Top = 256
        Width = 42
        Height = 13
        Caption = 'dV '#1079#1072#1084'.:'
      end
      object GroupBox5: TGroupBox
        Left = 8
        Top = 8
        Width = 321
        Height = 145
        Caption = ' '#1057#1082#1086#1088#1086#1089#1090#1100' ('#1091#1089#1082#1086#1088#1077#1085#1080#1103') - '#1085#1086#1088#1084'. '#1088#1077#1078#1080#1084' '
        TabOrder = 0
        object Label13: TLabel
          Left = 16
          Top = 24
          Width = 57
          Height = 13
          Caption = 'Vmax ('#1084'/'#1089'):'
        end
        object Label14: TLabel
          Left = 16
          Top = 48
          Width = 69
          Height = 13
          Caption = 'a '#1079#1072#1084'. ('#1084'/'#1089'2):'
        end
        object Label15: TLabel
          Left = 16
          Top = 72
          Width = 72
          Height = 13
          Caption = 'a '#1088#1072#1079#1075'. ('#1084'/'#1089'2):'
        end
        object Label16: TLabel
          Left = 16
          Top = 96
          Width = 65
          Height = 13
          Caption = 'a '#1086#1090#1093'. ('#1084'/'#1089'2):'
        end
        object Label17: TLabel
          Left = 168
          Top = 48
          Width = 52
          Height = 13
          Caption = 'L '#1079#1072#1084'. ('#1084'):'
        end
        object Label18: TLabel
          Left = 168
          Top = 72
          Width = 55
          Height = 13
          Caption = 'L '#1088#1072#1079#1075'. ('#1084'):'
        end
        object Label19: TLabel
          Left = 168
          Top = 96
          Width = 48
          Height = 13
          Caption = 'L '#1086#1090#1093'. ('#1084'):'
        end
        object Label20: TLabel
          Left = 168
          Top = 120
          Width = 49
          Height = 13
          Caption = 'L '#1076#1086#1090'. ('#1084'):'
        end
        object Edit1: TEdit
          Left = 96
          Top = 21
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '5'
        end
        object Edit2: TEdit
          Left = 96
          Top = 45
          Width = 49
          Height = 21
          TabOrder = 1
          Text = '0,625'
        end
        object Edit3: TEdit
          Left = 96
          Top = 69
          Width = 49
          Height = 21
          TabOrder = 2
          Text = '0,52'
        end
        object Edit4: TEdit
          Left = 96
          Top = 93
          Width = 49
          Height = 21
          TabOrder = 3
          Text = '0,25'
        end
        object Edit5: TEdit
          Left = 232
          Top = 45
          Width = 49
          Height = 21
          TabOrder = 4
          Text = '19,7'
        end
        object Edit6: TEdit
          Left = 232
          Top = 69
          Width = 49
          Height = 21
          TabOrder = 5
          Text = '24'
        end
        object Edit7: TEdit
          Left = 232
          Top = 93
          Width = 49
          Height = 21
          TabOrder = 6
          Text = '2'
        end
        object Edit8: TEdit
          Left = 232
          Top = 117
          Width = 49
          Height = 21
          TabOrder = 7
          Text = '2'
        end
      end
      object Edit41: TEdit
        Left = 280
        Top = 181
        Width = 49
        Height = 21
        TabOrder = 1
        Text = '5'
      end
      object Edit42: TEdit
        Left = 280
        Top = 205
        Width = 49
        Height = 21
        TabOrder = 2
        Text = '5'
      end
      object Edit49: TEdit
        Left = 280
        Top = 229
        Width = 49
        Height = 21
        TabOrder = 3
        Text = '5'
      end
      object Edit50: TEdit
        Left = 280
        Top = 253
        Width = 49
        Height = 21
        TabOrder = 4
        Text = '5'
      end
      object GroupBox6: TGroupBox
        Left = 8
        Top = 164
        Width = 218
        Height = 125
        Caption = ' '#1054#1090#1082#1083#1086#1085#1077#1085#1080#1103' (%) '
        TabOrder = 5
        object Label21: TLabel
          Left = 8
          Top = 20
          Width = 140
          Height = 13
          Caption = #1057#1080#1075#1085'. ('#1090#1086#1088#1084#1086#1078#1077#1085#1080#1077'-'#1088#1072#1079#1075#1086#1085'):'
        end
        object Label22: TLabel
          Left = 8
          Top = 44
          Width = 138
          Height = 13
          Caption = #1047#1072#1097'. ('#1090#1086#1088#1084#1086#1078#1077#1085#1080#1077'-'#1088#1072#1079#1075#1086#1085'):'
        end
        object Label72: TLabel
          Left = 8
          Top = 68
          Width = 113
          Height = 13
          Caption = #1057#1080#1075#1085'. ('#1076#1086#1090#1103#1078#1082#1072'-'#1086#1090#1093#1086#1076'):'
        end
        object Label73: TLabel
          Left = 8
          Top = 92
          Width = 111
          Height = 13
          Caption = #1047#1072#1097'. ('#1076#1086#1090#1103#1078#1082#1072'-'#1086#1090#1093#1086#1076'):'
        end
        object Edit18: TEdit
          Left = 152
          Top = 17
          Width = 57
          Height = 21
          TabOrder = 0
          Text = '5'
        end
        object Edit19: TEdit
          Left = 152
          Top = 41
          Width = 57
          Height = 21
          TabOrder = 1
          Text = '5'
        end
        object Edit71: TEdit
          Left = 152
          Top = 65
          Width = 57
          Height = 21
          TabOrder = 2
          Text = '5'
        end
        object Edit72: TEdit
          Left = 152
          Top = 89
          Width = 57
          Height = 21
          TabOrder = 3
          Text = '5'
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1056#1051
      ImageIndex = 1
      object Label45: TLabel
        Left = 232
        Top = 184
        Width = 44
        Height = 13
        Caption = 'dL '#1088#1072#1079#1075'.:'
      end
      object Label46: TLabel
        Left = 232
        Top = 208
        Width = 41
        Height = 13
        Caption = 'dL '#1079#1072#1084'.:'
      end
      object Label53: TLabel
        Left = 232
        Top = 232
        Width = 45
        Height = 13
        Caption = 'dV '#1088#1072#1079#1075'.:'
      end
      object Label54: TLabel
        Left = 232
        Top = 256
        Width = 42
        Height = 13
        Caption = 'dV '#1079#1072#1084'.:'
      end
      object GroupBox1: TGroupBox
        Left = 8
        Top = 8
        Width = 321
        Height = 145
        Caption = ' '#1057#1082#1086#1088#1086#1089#1090#1100' ('#1091#1089#1082#1086#1088#1077#1085#1080#1103') - '#1085#1086#1088#1084'. '#1088#1077#1078#1080#1084' '
        TabOrder = 0
        object Label1: TLabel
          Left = 16
          Top = 24
          Width = 57
          Height = 13
          Caption = 'Vmax ('#1084'/'#1089'):'
        end
        object Label2: TLabel
          Left = 16
          Top = 48
          Width = 69
          Height = 13
          Caption = 'a '#1079#1072#1084'. ('#1084'/'#1089'2):'
        end
        object Label3: TLabel
          Left = 16
          Top = 72
          Width = 72
          Height = 13
          Caption = 'a '#1088#1072#1079#1075'. ('#1084'/'#1089'2):'
        end
        object Label4: TLabel
          Left = 16
          Top = 96
          Width = 65
          Height = 13
          Caption = 'a '#1086#1090#1093'. ('#1084'/'#1089'2):'
        end
        object Label5: TLabel
          Left = 168
          Top = 48
          Width = 52
          Height = 13
          Caption = 'L '#1079#1072#1084'. ('#1084'):'
        end
        object Label6: TLabel
          Left = 168
          Top = 72
          Width = 55
          Height = 13
          Caption = 'L '#1088#1072#1079#1075'. ('#1084'):'
        end
        object Label7: TLabel
          Left = 168
          Top = 96
          Width = 48
          Height = 13
          Caption = 'L '#1086#1090#1093'. ('#1084'):'
        end
        object Label8: TLabel
          Left = 168
          Top = 120
          Width = 49
          Height = 13
          Caption = 'L '#1076#1086#1090'. ('#1084'):'
        end
        object Edit9: TEdit
          Left = 96
          Top = 21
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '5'
        end
        object Edit10: TEdit
          Left = 96
          Top = 45
          Width = 49
          Height = 21
          TabOrder = 1
          Text = '0,625'
        end
        object Edit11: TEdit
          Left = 96
          Top = 69
          Width = 49
          Height = 21
          TabOrder = 2
          Text = '0,52'
        end
        object Edit12: TEdit
          Left = 96
          Top = 93
          Width = 49
          Height = 21
          TabOrder = 3
          Text = '0,25'
        end
        object Edit13: TEdit
          Left = 232
          Top = 45
          Width = 49
          Height = 21
          TabOrder = 4
          Text = '19,7'
        end
        object Edit14: TEdit
          Left = 232
          Top = 69
          Width = 49
          Height = 21
          TabOrder = 5
          Text = '24'
        end
        object Edit15: TEdit
          Left = 232
          Top = 93
          Width = 49
          Height = 21
          TabOrder = 6
          Text = '2'
        end
        object Edit16: TEdit
          Left = 232
          Top = 117
          Width = 49
          Height = 21
          TabOrder = 7
          Text = '2'
        end
      end
      object Edit43: TEdit
        Left = 280
        Top = 181
        Width = 49
        Height = 21
        TabOrder = 1
        Text = '5'
      end
      object Edit44: TEdit
        Left = 280
        Top = 205
        Width = 49
        Height = 21
        TabOrder = 2
        Text = '5'
      end
      object Edit51: TEdit
        Left = 280
        Top = 229
        Width = 49
        Height = 21
        TabOrder = 3
        Text = '5'
      end
      object Edit52: TEdit
        Left = 280
        Top = 253
        Width = 49
        Height = 21
        TabOrder = 4
        Text = '5'
      end
      object GroupBox4: TGroupBox
        Left = 8
        Top = 164
        Width = 218
        Height = 125
        Caption = ' '#1054#1090#1082#1083#1086#1085#1077#1085#1080#1103' (%) '
        TabOrder = 5
        object Label11: TLabel
          Left = 8
          Top = 20
          Width = 140
          Height = 13
          Caption = #1057#1080#1075#1085'. ('#1090#1086#1088#1084#1086#1078#1077#1085#1080#1077'-'#1088#1072#1079#1075#1086#1085'):'
        end
        object Label12: TLabel
          Left = 8
          Top = 44
          Width = 138
          Height = 13
          Caption = #1047#1072#1097'. ('#1090#1086#1088#1084#1086#1078#1077#1085#1080#1077'-'#1088#1072#1079#1075#1086#1085'):'
        end
        object Label70: TLabel
          Left = 8
          Top = 68
          Width = 113
          Height = 13
          Caption = #1057#1080#1075#1085'. ('#1076#1086#1090#1103#1078#1082#1072'-'#1086#1090#1093#1086#1076'):'
        end
        object Label71: TLabel
          Left = 8
          Top = 92
          Width = 111
          Height = 13
          Caption = #1047#1072#1097'. ('#1076#1086#1090#1103#1078#1082#1072'-'#1086#1090#1093#1086#1076'):'
        end
        object Edit17: TEdit
          Left = 152
          Top = 17
          Width = 57
          Height = 21
          TabOrder = 0
          Text = '5'
        end
        object Edit20: TEdit
          Left = 152
          Top = 41
          Width = 57
          Height = 21
          TabOrder = 1
          Text = '5'
        end
        object Edit69: TEdit
          Left = 152
          Top = 65
          Width = 57
          Height = 21
          TabOrder = 2
          Text = '5'
        end
        object Edit70: TEdit
          Left = 152
          Top = 89
          Width = 57
          Height = 21
          TabOrder = 3
          Text = '5'
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = #1056#1056
      ImageIndex = 2
      object Label47: TLabel
        Left = 232
        Top = 184
        Width = 44
        Height = 13
        Caption = 'dL '#1088#1072#1079#1075'.:'
      end
      object Label48: TLabel
        Left = 232
        Top = 208
        Width = 41
        Height = 13
        Caption = 'dL '#1079#1072#1084'.:'
      end
      object Label57: TLabel
        Left = 232
        Top = 232
        Width = 45
        Height = 13
        Caption = 'dV '#1088#1072#1079#1075'.:'
      end
      object Label58: TLabel
        Left = 232
        Top = 256
        Width = 42
        Height = 13
        Caption = 'dV '#1079#1072#1084'.:'
      end
      object GroupBox7: TGroupBox
        Left = 8
        Top = 8
        Width = 321
        Height = 145
        Caption = ' '#1057#1082#1086#1088#1086#1089#1090#1100' ('#1091#1089#1082#1086#1088#1077#1085#1080#1103') - '#1085#1086#1088#1084'. '#1088#1077#1078#1080#1084' '
        TabOrder = 0
        object Label23: TLabel
          Left = 16
          Top = 24
          Width = 57
          Height = 13
          Caption = 'Vmax ('#1084'/'#1089'):'
        end
        object Label24: TLabel
          Left = 16
          Top = 48
          Width = 69
          Height = 13
          Caption = 'a '#1079#1072#1084'. ('#1084'/'#1089'2):'
        end
        object Label25: TLabel
          Left = 16
          Top = 72
          Width = 72
          Height = 13
          Caption = 'a '#1088#1072#1079#1075'. ('#1084'/'#1089'2):'
        end
        object Label26: TLabel
          Left = 16
          Top = 96
          Width = 65
          Height = 13
          Caption = 'a '#1086#1090#1093'. ('#1084'/'#1089'2):'
        end
        object Label27: TLabel
          Left = 168
          Top = 48
          Width = 52
          Height = 13
          Caption = 'L '#1079#1072#1084'. ('#1084'):'
        end
        object Label28: TLabel
          Left = 168
          Top = 72
          Width = 55
          Height = 13
          Caption = 'L '#1088#1072#1079#1075'. ('#1084'):'
        end
        object Label29: TLabel
          Left = 168
          Top = 96
          Width = 48
          Height = 13
          Caption = 'L '#1086#1090#1093'. ('#1084'):'
        end
        object Label30: TLabel
          Left = 168
          Top = 120
          Width = 49
          Height = 13
          Caption = 'L '#1076#1086#1090'. ('#1084'):'
        end
        object Edit21: TEdit
          Left = 96
          Top = 21
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '5'
        end
        object Edit22: TEdit
          Left = 96
          Top = 45
          Width = 49
          Height = 21
          TabOrder = 1
          Text = '0,625'
        end
        object Edit23: TEdit
          Left = 96
          Top = 69
          Width = 49
          Height = 21
          TabOrder = 2
          Text = '0,52'
        end
        object Edit24: TEdit
          Left = 96
          Top = 93
          Width = 49
          Height = 21
          TabOrder = 3
          Text = '0,25'
        end
        object Edit25: TEdit
          Left = 232
          Top = 45
          Width = 49
          Height = 21
          TabOrder = 4
          Text = '19,7'
        end
        object Edit26: TEdit
          Left = 232
          Top = 69
          Width = 49
          Height = 21
          TabOrder = 5
          Text = '24'
        end
        object Edit27: TEdit
          Left = 232
          Top = 93
          Width = 49
          Height = 21
          TabOrder = 6
          Text = '2'
        end
        object Edit28: TEdit
          Left = 232
          Top = 117
          Width = 49
          Height = 21
          TabOrder = 7
          Text = '2'
        end
      end
      object Edit45: TEdit
        Left = 280
        Top = 181
        Width = 49
        Height = 21
        TabOrder = 1
        Text = '5'
      end
      object Edit46: TEdit
        Left = 280
        Top = 205
        Width = 49
        Height = 21
        TabOrder = 2
        Text = '5'
      end
      object Edit55: TEdit
        Left = 280
        Top = 229
        Width = 49
        Height = 21
        TabOrder = 3
        Text = '5'
      end
      object Edit56: TEdit
        Left = 280
        Top = 253
        Width = 49
        Height = 21
        TabOrder = 4
        Text = '5'
      end
      object GroupBox8: TGroupBox
        Left = 8
        Top = 164
        Width = 218
        Height = 125
        Caption = ' '#1054#1090#1082#1083#1086#1085#1077#1085#1080#1103' (%) '
        TabOrder = 5
        object Label31: TLabel
          Left = 8
          Top = 20
          Width = 140
          Height = 13
          Caption = #1057#1080#1075#1085'. ('#1090#1086#1088#1084#1086#1078#1077#1085#1080#1077'-'#1088#1072#1079#1075#1086#1085'):'
        end
        object Label32: TLabel
          Left = 8
          Top = 44
          Width = 138
          Height = 13
          Caption = #1047#1072#1097'. ('#1090#1086#1088#1084#1086#1078#1077#1085#1080#1077'-'#1088#1072#1079#1075#1086#1085'):'
        end
        object Label68: TLabel
          Left = 8
          Top = 68
          Width = 113
          Height = 13
          Caption = #1057#1080#1075#1085'. ('#1076#1086#1090#1103#1078#1082#1072'-'#1086#1090#1093#1086#1076'):'
        end
        object Label69: TLabel
          Left = 8
          Top = 92
          Width = 111
          Height = 13
          Caption = #1047#1072#1097'. ('#1076#1086#1090#1103#1078#1082#1072'-'#1086#1090#1093#1086#1076'):'
        end
        object Edit29: TEdit
          Left = 152
          Top = 17
          Width = 57
          Height = 21
          TabOrder = 0
          Text = '5'
        end
        object Edit30: TEdit
          Left = 152
          Top = 41
          Width = 57
          Height = 21
          TabOrder = 1
          Text = '5'
        end
        object Edit67: TEdit
          Left = 152
          Top = 65
          Width = 57
          Height = 21
          TabOrder = 2
          Text = '5'
        end
        object Edit68: TEdit
          Left = 152
          Top = 89
          Width = 57
          Height = 21
          TabOrder = 3
          Text = '5'
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = #1056#1054
      ImageIndex = 3
      object Label49: TLabel
        Left = 232
        Top = 184
        Width = 44
        Height = 13
        Caption = 'dL '#1088#1072#1079#1075'.:'
      end
      object Label50: TLabel
        Left = 232
        Top = 208
        Width = 41
        Height = 13
        Caption = 'dL '#1079#1072#1084'.:'
      end
      object Label55: TLabel
        Left = 232
        Top = 232
        Width = 45
        Height = 13
        Caption = 'dV '#1088#1072#1079#1075'.:'
      end
      object Label56: TLabel
        Left = 232
        Top = 256
        Width = 42
        Height = 13
        Caption = 'dV '#1079#1072#1084'.:'
      end
      object GroupBox9: TGroupBox
        Left = 8
        Top = 8
        Width = 321
        Height = 145
        Caption = ' '#1057#1082#1086#1088#1086#1089#1090#1100' ('#1091#1089#1082#1086#1088#1077#1085#1080#1103') - '#1085#1086#1088#1084'. '#1088#1077#1078#1080#1084' '
        TabOrder = 0
        object Label33: TLabel
          Left = 16
          Top = 24
          Width = 57
          Height = 13
          Caption = 'Vmax ('#1084'/'#1089'):'
        end
        object Label34: TLabel
          Left = 16
          Top = 48
          Width = 69
          Height = 13
          Caption = 'a '#1079#1072#1084'. ('#1084'/'#1089'2):'
        end
        object Label35: TLabel
          Left = 16
          Top = 72
          Width = 72
          Height = 13
          Caption = 'a '#1088#1072#1079#1075'. ('#1084'/'#1089'2):'
        end
        object Label36: TLabel
          Left = 16
          Top = 96
          Width = 65
          Height = 13
          Caption = 'a '#1086#1090#1093'. ('#1084'/'#1089'2):'
        end
        object Label37: TLabel
          Left = 168
          Top = 48
          Width = 52
          Height = 13
          Caption = 'L '#1079#1072#1084'. ('#1084'):'
        end
        object Label38: TLabel
          Left = 168
          Top = 72
          Width = 55
          Height = 13
          Caption = 'L '#1088#1072#1079#1075'. ('#1084'):'
        end
        object Label39: TLabel
          Left = 168
          Top = 96
          Width = 48
          Height = 13
          Caption = 'L '#1086#1090#1093'. ('#1084'):'
        end
        object Label40: TLabel
          Left = 168
          Top = 120
          Width = 49
          Height = 13
          Caption = 'L '#1076#1086#1090'. ('#1084'):'
        end
        object Edit31: TEdit
          Left = 96
          Top = 21
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '5'
        end
        object Edit32: TEdit
          Left = 96
          Top = 45
          Width = 49
          Height = 21
          TabOrder = 1
          Text = '0,625'
        end
        object Edit33: TEdit
          Left = 96
          Top = 69
          Width = 49
          Height = 21
          TabOrder = 2
          Text = '0,52'
        end
        object Edit34: TEdit
          Left = 96
          Top = 93
          Width = 49
          Height = 21
          TabOrder = 3
          Text = '0,25'
        end
        object Edit35: TEdit
          Left = 232
          Top = 45
          Width = 49
          Height = 21
          TabOrder = 4
          Text = '19,7'
        end
        object Edit36: TEdit
          Left = 232
          Top = 69
          Width = 49
          Height = 21
          TabOrder = 5
          Text = '24'
        end
        object Edit37: TEdit
          Left = 232
          Top = 93
          Width = 49
          Height = 21
          TabOrder = 6
          Text = '2'
        end
        object Edit38: TEdit
          Left = 232
          Top = 117
          Width = 49
          Height = 21
          TabOrder = 7
          Text = '2'
        end
      end
      object GroupBox10: TGroupBox
        Left = 8
        Top = 164
        Width = 218
        Height = 125
        Caption = ' '#1054#1090#1082#1083#1086#1085#1077#1085#1080#1103' (%) '
        TabOrder = 1
        object Label41: TLabel
          Left = 8
          Top = 20
          Width = 140
          Height = 13
          Caption = #1057#1080#1075#1085'. ('#1090#1086#1088#1084#1086#1078#1077#1085#1080#1077'-'#1088#1072#1079#1075#1086#1085'):'
        end
        object Label42: TLabel
          Left = 8
          Top = 44
          Width = 138
          Height = 13
          Caption = #1047#1072#1097'. ('#1090#1086#1088#1084#1086#1078#1077#1085#1080#1077'-'#1088#1072#1079#1075#1086#1085'):'
        end
        object Label60: TLabel
          Left = 8
          Top = 68
          Width = 113
          Height = 13
          Caption = #1057#1080#1075#1085'. ('#1076#1086#1090#1103#1078#1082#1072'-'#1086#1090#1093#1086#1076'):'
        end
        object Label61: TLabel
          Left = 8
          Top = 92
          Width = 111
          Height = 13
          Caption = #1047#1072#1097'. ('#1076#1086#1090#1103#1078#1082#1072'-'#1086#1090#1093#1086#1076'):'
        end
        object Edit39: TEdit
          Left = 152
          Top = 17
          Width = 57
          Height = 21
          TabOrder = 0
          Text = '5'
        end
        object Edit40: TEdit
          Left = 152
          Top = 41
          Width = 57
          Height = 21
          TabOrder = 1
          Text = '5'
        end
        object Edit58: TEdit
          Left = 152
          Top = 65
          Width = 57
          Height = 21
          TabOrder = 2
          Text = '5'
        end
        object Edit59: TEdit
          Left = 152
          Top = 89
          Width = 57
          Height = 21
          TabOrder = 3
          Text = '5'
        end
      end
      object Edit47: TEdit
        Left = 280
        Top = 181
        Width = 49
        Height = 21
        TabOrder = 2
        Text = '5'
      end
      object Edit48: TEdit
        Left = 280
        Top = 205
        Width = 49
        Height = 21
        TabOrder = 3
        Text = '5'
      end
      object Edit53: TEdit
        Left = 280
        Top = 229
        Width = 49
        Height = 21
        TabOrder = 4
        Text = '5'
      end
      object Edit54: TEdit
        Left = 280
        Top = 253
        Width = 49
        Height = 21
        TabOrder = 5
        Text = '5'
      end
    end
  end
  object GroupBox11: TGroupBox
    Left = 360
    Top = 304
    Width = 169
    Height = 49
    TabOrder = 5
    object Label75: TLabel
      Left = 16
      Top = 20
      Width = 83
      Height = 13
      Caption = 'dh '#1085#1077#1076#1086#1077#1079#1076#1072' ('#1084'):'
    end
    object Edit74: TEdit
      Left = 104
      Top = 17
      Width = 49
      Height = 21
      TabOrder = 0
      Text = '250'
    end
  end
end
