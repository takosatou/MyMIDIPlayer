# A Simple MIDI file player using M5Stack Core and USB module

Copyright (C) 2023 Takashi Satou
Released under the LGPL-2.1 License

Files in src/MD_MIDIFile/ are based on MajicDesigns/MD_MIDIFile <https://github.com/MajicDesigns/MD_MIDIFile>, that are released under the LGPL-2.1 License.

## Dependent Libraries
- USB Host Shield Library 2.0
- YuuichiAkagawa/USBH_MIDI <https://github.com/tanakamasayuki/efont>
- taakamasayuki/efont <https://github.com/tanakamasayuki/efont>

## Settings in SD card
### index.csv
You need to place `index.csv` file in the root directory of the SD card.

Example
```
Group,Title,Filename
[設定],ピアノモード,0
[設定],リピート,0
[設定],NSX-39モード,0
クラシック,ドビュッシー アラベスク1,arabe1.mid
クラシック,ドビュッシー 月の光,bergam3.mid
クラシック,ドビュッシー 亜麻色の髪の乙女,prelude8.mid
クラシック,ショパン ノクターン,chno0902.mid
バッハ,メヌエット,menuett.mid
バッハ,アリア,air.mid
バッハ,シャコンヌ,vp2-5cha.mid
...
,,
```

The first line is for the titles of columns: `Group,Title,Filename`.

The following three lines are for setting modes.
```
[設定],ピアノモード,0
[設定],リピート,0
[設定],NSX-39モード,0
```

Then you may write the group, title and filename of a song for each line.

The last line must be `,,` to indicate the end of file.

### *.mid files

MIDI files (`*.mid`) should be placed in the root directory as well as `index.csv`.

## Settings
![cap000](https://github.com/takosatou/MyMIDIPlayer/assets/52827488/acfa0971-1eb8-4d6d-8ac5-026441b04e00)
![cap001](https://github.com/takosatou/MyMIDIPlayer/assets/52827488/42c63f9f-0c76-45cb-bcc0-29c86250f0e4)

- ピアノモード Piano mode --- All instruments are conveted to piano. This is for Digital Piano that can use only piano voices.
- リピート Repeat mode --- Select 全曲 all / 1曲 one song / なし no repeat.
- NSX-39 mode --- Remap 1ch to 16ch, because 1ch in NSX-39 is reserved for Hatsune Miku's voice.

## Selecting the group
Using the left and right buttons to select a group, then press the center button to enter the group.
![cap002](https://github.com/takosatou/MyMIDIPlayer/assets/52827488/40bafa59-fae7-4e52-90f7-4d71ed3b78f1)

## Playing the song
Using the left and right buttons to select a song, then press the center button to play the song.
![cap006](https://github.com/takosatou/MyMIDIPlayer/assets/52827488/51d2988e-ef83-4027-ba29-90f930a9731a)

During playback, you can press the buttons:
### Left button --- Toggle piano mode
![cap010](https://github.com/takosatou/MyMIDIPlayer/assets/52827488/54f3ab0c-3521-46eb-a6c7-361ed10c8cba)
![cap011](https://github.com/takosatou/MyMIDIPlayer/assets/52827488/4c692a3f-d02f-4090-852c-e8bb838e0792)

### Center button --- Stop playing the song
### Right button --- change repeat mode
![cap007](https://github.com/takosatou/MyMIDIPlayer/assets/52827488/0841f036-5127-481b-a4c2-b2935c9d80af)
![cap008](https://github.com/takosatou/MyMIDIPlayer/assets/52827488/c2cceec0-6a42-419b-b33f-919870a50164)
![cap009](https://github.com/takosatou/MyMIDIPlayer/assets/52827488/73f5f7d4-7035-473f-bc08-d256ab4496da)



  
