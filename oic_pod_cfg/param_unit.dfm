object ParamForm: TParamForm
  Left = 277
  Top = 159
  ActiveControl = ArcDirEdit
  BorderStyle = bsDialog
  Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1089#1080#1089#1090#1077#1084#1099
  ClientHeight = 341
  ClientWidth = 345
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
  object PageControl1: TPageControl
    Left = 8
    Top = 8
    Width = 329
    Height = 297
    ActivePage = TabSheet3
    TabIndex = 2
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #1054#1089#1085#1086#1074#1085#1099#1077
      object GroupBox1: TGroupBox
        Left = 8
        Top = 8
        Width = 305
        Height = 81
        Caption = ' '#1057#1090#1074#1086#1083' '
        TabOrder = 0
        object Label1: TLabel
          Left = 16
          Top = 24
          Width = 97
          Height = 13
          Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1088#1091#1076#1085#1080#1082#1072':'
        end
        object Label2: TLabel
          Left = 16
          Top = 48
          Width = 91
          Height = 13
          Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1089#1090#1074#1086#1083#1072':'
        end
        object RudNameEdit: TComboBox
          Left = 128
          Top = 22
          Width = 161
          Height = 21
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 0
          Text = #1061#1086#1083#1073#1080#1085#1089#1082#1080#1081
          Items.Strings = (
            #1061#1086#1083#1073#1080#1085#1089#1082#1080#1081)
        end
        object StvolNameEdit: TComboBox
          Left = 128
          Top = 46
          Width = 161
          Height = 21
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 1
          Text = #1042#1089#1087#1086#1084#1086#1075#1072#1090#1077#1083#1100#1085#1099#1081
          Items.Strings = (
            #1042#1089#1087#1086#1084#1086#1075#1072#1090#1077#1083#1100#1085#1099#1081
            #1043#1083#1072#1074#1085#1099#1081)
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1042#1088#1077#1084#1103
      ImageIndex = 1
      object GroupBox2: TGroupBox
        Left = 8
        Top = 8
        Width = 305
        Height = 81
        Caption = ' '#1048#1085#1090#1077#1088#1074#1072#1083#1099' '
        TabOrder = 0
        object Label3: TLabel
          Left = 16
          Top = 24
          Width = 132
          Height = 13
          Caption = #1054#1073#1085#1086#1074#1083#1077#1085#1080#1077' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1080':'
        end
        object Label4: TLabel
          Left = 16
          Top = 48
          Width = 137
          Height = 13
          Caption = #1055#1077#1088#1080#1086#1076#1080#1095#1085#1086#1089#1090#1100' '#1072#1088#1093#1080#1074#1072#1094#1080#1080':'
        end
        object Label5: TLabel
          Left = 256
          Top = 24
          Width = 14
          Height = 13
          Caption = #1084#1089
        end
        object Label6: TLabel
          Left = 256
          Top = 48
          Width = 14
          Height = 13
          Caption = #1084#1089
        end
        object RefrTimeEdit: TCSpinEdit
          Left = 176
          Top = 22
          Width = 73
          Height = 22
          Increment = 100
          TabOrder = 0
        end
        object ArcTimeEdit: TCSpinEdit
          Left = 176
          Top = 46
          Width = 73
          Height = 22
          Increment = 100
          TabOrder = 1
        end
      end
      object GroupBox3: TGroupBox
        Left = 8
        Top = 96
        Width = 305
        Height = 105
        Caption = ' '#1057#1084#1077#1085#1072' '
        TabOrder = 1
        object Label7: TLabel
          Left = 16
          Top = 24
          Width = 48
          Height = 13
          Caption = #1044#1085#1077#1074#1085#1072#1103':'
        end
        object Label8: TLabel
          Left = 184
          Top = 24
          Width = 12
          Height = 13
          Caption = #1076#1086
        end
        object Label9: TLabel
          Left = 80
          Top = 24
          Width = 6
          Height = 13
          Caption = #1089
        end
        object Label10: TLabel
          Left = 16
          Top = 48
          Width = 40
          Height = 13
          Caption = #1053#1086#1095#1085#1072#1103':'
        end
        object Label11: TLabel
          Left = 80
          Top = 48
          Width = 6
          Height = 13
          Caption = #1089
        end
        object Label12: TLabel
          Left = 184
          Top = 48
          Width = 12
          Height = 13
          Caption = #1076#1086
        end
        object DayTime1: TCSpinEdit
          Left = 96
          Top = 22
          Width = 73
          Height = 22
          AutoSize = False
          MaxValue = 23
          TabOrder = 0
        end
        object NightTime1: TCSpinEdit
          Left = 96
          Top = 46
          Width = 73
          Height = 22
          AutoSize = False
          MaxValue = 23
          TabOrder = 1
        end
        object NightTime2: TCSpinEdit
          Left = 208
          Top = 46
          Width = 73
          Height = 22
          AutoSize = False
          MaxValue = 23
          TabOrder = 2
        end
        object DayTime2: TCSpinEdit
          Left = 208
          Top = 22
          Width = 73
          Height = 22
          AutoSize = False
          MaxValue = 23
          TabOrder = 3
        end
        object dtPeresmEdit: TLabeledEdit
          Left = 208
          Top = 72
          Width = 73
          Height = 21
          EditLabel.Width = 106
          EditLabel.Height = 13
          EditLabel.Caption = 'dt '#1087#1077#1088#1077#1089#1084#1077#1085#1082#1080' ('#1084#1080#1085'):'
          LabelPosition = lpLeft
          LabelSpacing = 9
          TabOrder = 4
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = #1050#1072#1090#1072#1083#1086#1075#1080
      ImageIndex = 2
      object GroupBox4: TGroupBox
        Left = 8
        Top = 8
        Width = 305
        Height = 153
        TabOrder = 0
        object Label13: TLabel
          Left = 16
          Top = 24
          Width = 41
          Height = 13
          Caption = #1040#1088#1093#1080#1074#1099':'
        end
        object Label14: TLabel
          Left = 16
          Top = 48
          Width = 98
          Height = 13
          Caption = #1057#1080#1089#1090#1077#1084#1085#1099#1077' '#1092#1072#1081#1083#1099':'
        end
        object SpeedButton1: TSpeedButton
          Left = 283
          Top = 24
          Width = 15
          Height = 15
          Caption = '...'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          OnClick = SpeedButton1Click
        end
        object SpeedButton2: TSpeedButton
          Left = 283
          Top = 48
          Width = 15
          Height = 15
          Caption = '...'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          OnClick = SpeedButton2Click
        end
        object Label15: TLabel
          Left = 16
          Top = 72
          Width = 88
          Height = 13
          Caption = #1043#1088#1072#1092#1080#1082#1072' '#1080' '#1079#1074#1091#1082#1080':'
        end
        object SpeedButton3: TSpeedButton
          Left = 282
          Top = 72
          Width = 15
          Height = 15
          Caption = '...'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          OnClick = SpeedButton3Click
        end
        object Label16: TLabel
          Left = 16
          Top = 96
          Width = 82
          Height = 13
          Caption = #1040#1088#1093#1080#1074#1072#1090#1086#1088' RAR:'
        end
        object SpeedButton4: TSpeedButton
          Left = 282
          Top = 96
          Width = 15
          Height = 15
          Caption = '...'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          OnClick = SpeedButton4Click
        end
        object Label17: TLabel
          Left = 16
          Top = 120
          Width = 64
          Height = 13
          Caption = 'FLASH-'#1076#1080#1089#1082':'
        end
        object SpeedButton5: TSpeedButton
          Left = 282
          Top = 120
          Width = 15
          Height = 15
          Caption = '...'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          OnClick = SpeedButton5Click
        end
        object ArcDirEdit: TEdit
          Left = 128
          Top = 22
          Width = 153
          Height = 21
          TabOrder = 0
        end
        object SysDirEdit: TEdit
          Left = 128
          Top = 46
          Width = 153
          Height = 21
          TabOrder = 1
        end
        object MediaDirEdit: TEdit
          Left = 128
          Top = 70
          Width = 153
          Height = 21
          TabOrder = 2
        end
        object RARDirEdit: TEdit
          Left = 128
          Top = 94
          Width = 153
          Height = 21
          TabOrder = 3
        end
        object FlashDirEdit: TEdit
          Left = 128
          Top = 118
          Width = 153
          Height = 21
          TabOrder = 4
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = #1057#1074#1103#1079#1100
      ImageIndex = 3
      object COMRadioGroup: TRadioGroup
        Left = 8
        Top = 8
        Width = 145
        Height = 113
        Caption = ' COM-'#1087#1086#1088#1090' '
        ItemIndex = 0
        Items.Strings = (
          'COM1'
          'COM2'
          'COM3'
          'COM4')
        TabOrder = 0
      end
      object DIALRadioGroup: TRadioGroup
        Left = 160
        Top = 8
        Width = 153
        Height = 73
        Caption = ' '#1053#1072#1073#1086#1088' '#1085#1086#1084#1077#1088#1072' '
        ItemIndex = 1
        Items.Strings = (
          #1090#1086#1085#1086#1074#1099#1081
          #1087#1091#1083#1100#1089#1086#1074#1099#1081)
        TabOrder = 1
      end
    end
  end
  object OkButton: TBitBtn
    Left = 184
    Top = 312
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 1
    OnClick = OkButtonClick
    NumGlyphs = 2
  end
  object CancelButton: TBitBtn
    Left = 264
    Top = 312
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1047#1072#1082#1088#1099#1090#1100
    ModalResult = 2
    TabOrder = 2
    NumGlyphs = 2
  end
end
