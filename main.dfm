object Form1: TForm1
  Left = 293
  Top = 165
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Stack Attack Advanced'
  ClientHeight = 500
  ClientWidth = 750
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesigned
  OnKeyDown = FormKeyDown
  OnKeyPress = FormKeyPress
  OnKeyUp = FormKeyUp
  PixelsPerInch = 96
  TextHeight = 13
  object Buffer: TImage
    Left = 0
    Top = 0
    Width = 750
    Height = 500
    Align = alClient
    Visible = False
    ExplicitLeft = 80
    ExplicitTop = 88
    ExplicitWidth = 46
    ExplicitHeight = 52
  end
  object fon: TImage
    Left = 136
    Top = 152
    Width = 49
    Height = 49
  end
  object MainMenu1: TMainMenu
    Left = 504
    Top = 72
    object start1: TMenuItem
      Caption = 'Start'
      OnClick = start1Click
    end
    object pause1: TMenuItem
      Caption = 'Pause'
      OnClick = pause1Click
    end
    object info1: TMenuItem
      Caption = 'Info'
      OnClick = info1Click
    end
    object N1: TMenuItem
      Caption = '|'
    end
    object Label1: TMenuItem
    end
    object Label2: TMenuItem
    end
    object N2: TMenuItem
      Caption = '|'
    end
    object Misia1: TMenuItem
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 250
    OnTimer = Timer1Timer
    Left = 392
    Top = 40
  end
  object Update: TTimer
    Interval = 66
    OnTimer = UpdateTimer
    Left = 176
    Top = 56
  end
end
