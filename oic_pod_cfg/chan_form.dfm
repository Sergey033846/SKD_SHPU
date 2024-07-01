object ChannelForm: TChannelForm
  Left = 234
  Top = 187
  BorderStyle = bsDialog
  Caption = #1050#1086#1085#1092#1080#1075#1091#1088#1072#1090#1086#1088' '#1082#1072#1085#1072#1083#1086#1074
  ClientHeight = 308
  ClientWidth = 485
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
  object MainParametersBox: TGroupBox
    Left = 8
    Top = 8
    Width = 281
    Height = 225
    Caption = ' '#1054#1089#1085#1086#1074#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099' '
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 0
    object IDLabel: TLabel
      Left = 16
      Top = 24
      Width = 122
      Height = 13
      Caption = #1048#1076#1077#1085#1090#1080#1092#1080#1082#1072#1090#1086#1088' '#1082#1072#1085#1072#1083#1072':'
    end
    object CaptionLabel: TLabel
      Left = 16
      Top = 48
      Width = 79
      Height = 13
      Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077':'
    end
    object TypeLabel: TLabel
      Left = 16
      Top = 72
      Width = 61
      Height = 13
      Caption = #1058#1080#1087' '#1082#1072#1085#1072#1083#1072':'
    end
    object DimensionLabel: TLabel
      Left = 16
      Top = 96
      Width = 61
      Height = 13
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077':'
    end
    object MINDimLabel: TLabel
      Left = 16
      Top = 153
      Width = 73
      Height = 26
      Caption = 'MIN '#1079#1085#1072#1095#1077#1085#1080#1077' '#1080#1079#1084#1077#1088#1077#1085#1080#1103':'
      WordWrap = True
    end
    object MAXDimLabel: TLabel
      Left = 16
      Top = 187
      Width = 73
      Height = 26
      Caption = 'MAX '#1079#1085#1072#1095#1077#1085#1080#1077' '#1080#1079#1084#1077#1088#1077#1085#1080#1103':'
      WordWrap = True
    end
    object KindDimLabel: TLabel
      Left = 16
      Top = 121
      Width = 59
      Height = 26
      Caption = #1045#1076#1080#1085#1080#1094#1072' '#1080#1079#1084#1077#1088#1077#1085#1080#1103':'
      WordWrap = True
    end
    object CaptionEdit: TEdit
      Left = 104
      Top = 46
      Width = 161
      Height = 21
      TabOrder = 1
    end
    object TypeEdit: TComboBox
      Left = 104
      Top = 70
      Width = 161
      Height = 19
      Style = csOwnerDrawFixed
      ItemHeight = 13
      TabOrder = 2
      Items.Strings = (
        #1076#1080#1089#1082#1088#1077#1090#1085#1099#1081
        #1072#1085#1072#1083#1086#1075#1086#1074#1099#1081
        #1089#1095#1077#1090#1095#1080#1082
        #1087#1088#1086#1075#1088#1072#1084#1084#1085#1099#1081
        #1091#1087#1088#1072#1074#1083#1077#1085#1080#1077
        #1088#1077#1079#1077#1088#1074)
    end
    object DimensionEdit: TComboBox
      Left = 104
      Top = 94
      Width = 161
      Height = 19
      Style = csOwnerDrawFixed
      ItemHeight = 13
      TabOrder = 3
      Items.Strings = (
        #1086#1090#1089#1091#1090#1089#1090#1074#1091#1077#1090
        #1074#1082#1083#1102#1095#1077#1085#1086
        #1086#1090#1082#1083#1102#1095#1077#1085#1086
        'U'
        'I'
        'P'
        #1089#1082#1086#1088#1086#1089#1090#1100)
    end
    object IDEdit: TCSpinEdit
      Left = 144
      Top = 22
      Width = 121
      Height = 22
      EditorEnabled = False
      MaxValue = 100
      ReadOnly = True
      TabOrder = 0
    end
    object MINDimEdit: TEdit
      Left = 104
      Top = 158
      Width = 161
      Height = 21
      TabOrder = 5
    end
    object MAXDimEdit: TEdit
      Left = 104
      Top = 190
      Width = 161
      Height = 21
      TabOrder = 6
    end
    object KindDimEdit: TComboBox
      Left = 104
      Top = 126
      Width = 161
      Height = 19
      Style = csOwnerDrawFixed
      ItemHeight = 13
      TabOrder = 4
      Items.Strings = (
        #1086#1090#1089#1091#1090#1089#1090#1074#1091#1077#1090
        'B'
        'mB'
        'A'
        'mA'
        #1042#1090
        #1082#1042#1090)
    end
  end
  object VisualBox: TGroupBox
    Left = 296
    Top = 8
    Width = 185
    Height = 65
    Caption = ' '#1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1103' '
    TabOrder = 1
    object ColorLabel: TLabel
      Left = 16
      Top = 18
      Width = 34
      Height = 13
      Caption = #1062#1074#1077#1090'1:'
    end
    object Label6: TLabel
      Left = 16
      Top = 42
      Width = 34
      Height = 13
      Caption = #1062#1074#1077#1090'2:'
    end
    object ActColorEdit: TColorBox
      Left = 56
      Top = 14
      Width = 121
      Height = 22
      Style = [cbStandardColors, cbPrettyNames]
      ItemHeight = 16
      TabOrder = 0
    end
    object NActColorEdit: TColorBox
      Left = 56
      Top = 38
      Width = 121
      Height = 22
      Style = [cbStandardColors, cbPrettyNames]
      ItemHeight = 16
      TabOrder = 1
    end
  end
  object SystemBox: TGroupBox
    Left = 296
    Top = 80
    Width = 185
    Height = 57
    Caption = ' '#1057#1080#1089#1090#1077#1084#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099' '
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 2
    object FPGALabel: TLabel
      Left = 16
      Top = 24
      Width = 31
      Height = 13
      Caption = 'FPGA:'
    end
    object NChannelLabel: TLabel
      Left = 112
      Top = 24
      Width = 9
      Height = 13
      Caption = 'n:'
    end
    object FPGAEdit: TCSpinEdit
      Left = 56
      Top = 22
      Width = 33
      Height = 22
      EditorEnabled = False
      MaxValue = 4
      MinValue = 1
      TabOrder = 0
      Value = 1
    end
    object NChannelEdit: TCSpinEdit
      Left = 128
      Top = 22
      Width = 41
      Height = 22
      MaxValue = 100
      TabOrder = 1
    end
  end
  object OkButton: TButton
    Left = 328
    Top = 279
    Width = 153
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    ModalResult = 1
    TabOrder = 3
    OnClick = OkButtonClick
  end
  object AnalogBox: TGroupBox
    Left = 294
    Top = 200
    Width = 187
    Height = 73
    Caption = ' '#1051#1080#1085#1077#1081#1085#1086#1077' '#1087#1088#1077#1086#1073#1088#1072#1079#1086#1074#1072#1085#1080#1077' '
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 4
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 9
      Height = 13
      Caption = 'a:'
    end
    object Label2: TLabel
      Left = 104
      Top = 24
      Width = 9
      Height = 13
      Caption = 'b:'
    end
    object Label3: TLabel
      Left = 16
      Top = 48
      Width = 9
      Height = 13
      Caption = 'k:'
    end
    object Label4: TLabel
      Left = 104
      Top = 48
      Width = 68
      Height = 13
      Caption = 'y = (ax + b) * k'
    end
    object aEdit: TEdit
      Left = 32
      Top = 20
      Width = 49
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object bEdit: TEdit
      Left = 120
      Top = 20
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object kEdit: TEdit
      Left = 32
      Top = 44
      Width = 49
      Height = 21
      TabOrder = 2
      Text = '0'
    end
  end
  object CounterBox: TGroupBox
    Left = 294
    Top = 144
    Width = 187
    Height = 49
    Caption = ' '#1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1089#1095#1077#1090#1095#1080#1082#1072' '
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 5
    object Label5: TLabel
      Left = 16
      Top = 24
      Width = 81
      Height = 13
      Caption = #1062#1077#1085#1072' '#1080#1084#1087#1091#1083#1100#1089#1072':'
    end
    object impEdit: TEdit
      Left = 104
      Top = 20
      Width = 65
      Height = 21
      TabOrder = 0
      Text = '0'
    end
  end
  object TransBox: TGroupBox
    Left = 8
    Top = 240
    Width = 281
    Height = 65
    Caption = ' '#1058#1088#1072#1085#1089#1092#1086#1088#1084#1072#1094#1080#1103' '
    TabOrder = 6
    object Label7: TLabel
      Left = 16
      Top = 24
      Width = 73
      Height = 13
      Caption = #1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090':'
    end
    object KTransEdit: TEdit
      Left = 104
      Top = 22
      Width = 161
      Height = 21
      TabOrder = 0
    end
  end
end
