char MELODY[] = {
// Piano
  1, // 1	00	Acoustic Piano	アコースティックピアノ
  1, // 2	01	Bright Piano	ブライトピアノ
  1, // 3	02	Electric Grand Piano	エレクトリック・グランドピアノ
  1, // 4	03	Honky-tonk Piano	ホンキートンクピアノ
  1, // 5	04	Electric Piano	エレクトリックピアノ
  1, // 6	05	Electric Piano 2	FMエレクトリックピアノ
  1, // 7	06	Harpsichord	ハープシコード
  1, // 8	07	Clavi	クラビネット
// Chromatic Percussion
  1, // 9	08	Celesta	チェレスタ
  1, // 10	09	Glockenspiel	グロッケンシュピール
  1, // 11	0A	Music box	オルゴール
  1, // 12	0B	Vibraphone	ヴィブラフォン
  1, // 13	0C	Marimba	マリンバ
  1, // 14	0D	Xylophone	シロフォン
  1, // 15	0E	Tubular Bell	チューブラーベル
  1, // 16	0F	Dulcimer	ダルシマー
// Organ
  1, // 17	10	Drawbar Organ	ドローバーオルガン
  1, // 18	11	Percussive Organ	パーカッシブオルガン
  1, // 19	12	Rock Organ	ロックオルガン
  1, // 20	13	Church organ	チャーチオルガン
  1, // 21	14	Reed organ	リードオルガン
  1, // 22	15	Accordion	アコーディオン
  1, // 23	16	Harmonica	ハーモニカ
  1, // 24	17	Tango Accordion	タンゴアコーディオン
// Guitar
  1, // 25	18	Acoustic Guitar (nylon)	アコースティックギター（ナイロン弦）
  1, // 26	19	Acoustic Guitar (steel)	アコースティックギター（スチール弦）
  1, // 27	1A	Electric Guitar (jazz)	ジャズギター
  1, // 28	1B	Electric Guitar (clean)	クリーンギター
  1, // 29	1C	Electric Guitar (muted)	ミュートギター
  1, // 30	1D	Overdriven Guitar	オーバードライブギター
  1, // 31	1E	Distortion Guitar	ディストーションギター
  1, // 32	1F	Guitar harmonics	ギターハーモニクス
// Bass
  1, // 33	20	Acoustic Bass	アコースティックベース
  1, // 34	21	Electric Bass (finger)	フィンガー・ベース
  1, // 35	22	Electric Bass (pick)	ピック・ベース
  1, // 36	23	Fretless Bass	フレットレスベース
  1, // 37	24	Slap Bass 1	スラップベース 1
  1, // 38	25	Slap Bass 2	スラップベース 2
  1, // 39	26	Synth Bass 1	シンセベース 1
  1, // 40	27	Synth Bass 2	シンセベース 2
// Strings
  1, // 41	28	Violin	ヴァイオリン
  1, // 42	29	Viola	ヴィオラ
  1, // 43	2A	Cello	チェロ
  1, // 44	2B	Double bass	コントラバス
  1, // 45	2C	Tremolo Strings	トレモロ
  1, // 46	2D	Pizzicato Strings	ピッチカート
  1, // 47	2E	Orchestral Harp	ハープ
  1, // 48	2F	Timpani	ティンパニ
// Ensemble
  1, // 49	30	String Ensemble 1	ストリングアンサンブル
  1, // 50	31	String Ensemble 2	スローストリングアンサンブル
  1, // 51	32	Synth Strings 1	シンセストリングス
  1, // 52	33	Synth Strings 2	シンセストリングス2
  1, // 53	34	Voice Aahs	声「アー」
  1, // 54	35	Voice Oohs	声「ドゥー」
  1, // 55	36	Synth Voice	シンセヴォイス
  1, // 56	37	Orchestra Hit	オーケストラヒット
// Brass
  1, // 57	38	Trumpet	トランペット
  1, // 58	39	Trombone	トロンボーン
  1, // 59	3A	Tuba	チューバ
  1, // 60	3B	Muted Trumpet	ミュートトランペット
  1, // 61	3C	French horn	フレンチ・ホルン
  1, // 62	3D	Brass Section	ブラスセクション
  1, // 63	3E	Synth Brass 1	シンセブラス 1
  1, // 64	3F	Synth Brass 2	シンセブラス 2
// Reed
  1, // 65	40	Soprano Sax	ソプラノサックス
  1, // 66	41	Alto Sax	アルトサックス
  1, // 67	42	Tenor Sax	テナーサックス
  1, // 68	43	Baritone Sax	バリトンサックス
  1, // 69	44	Oboe	オーボエ
  1, // 70	45	English Horn	イングリッシュホルン
  1, // 71	46	Bassoon	ファゴット
  1, // 72	47	Clarinet	クラリネット
// Pipe
  1, // 73	48	Piccolo	ピッコロ
  1, // 74	49	Flute	フルート
  1, // 75	4A	Recorder	リコーダー
  1, // 76	4B	Pan Flute	パンフルート
  1, // 77	4C	Blown Bottle	ブロウンボトル（吹きガラス瓶）
  1, // 78	4D	Shakuhachi	尺八
  1, // 79	4E	Whistle	口笛
  1, // 80	4F	Ocarina	オカリナ
// Synth Lead
  1, // 81	50	Lead 1 (square)	正方波
  1, // 82	51	Lead 2 (sawtooth)	ノコギリ波
  1, // 83	52	Lead 3 (calliope)	カリオペリード
  1, // 84	53	Lead 4 (chiff)	チフリード
  1, // 85	54	Lead 5 (charang)	チャランゴリード
  1, // 86	55	Lead 6 (voice)	声リード
  1, // 87	56	Lead 7 (fifths)	フィフスズリード
  1, // 88	57	Lead 8 (bass + lead)	ベース + リード
// Synth Pad
  1, // 89	58	Pad 1 (Fantasia)	ファンタジア
  1, // 90	59	Pad 2 (warm)	ウォーム
  1, // 91	5A	Pad 3 (polysynth)	ポリシンセ
  1, // 92	5B	Pad 4 (choir)	クワイア
  1, // 93	5C	Pad 5 (bowed)	ボウ
  1, // 94	5D	Pad 6 (metallic)	メタリック
  1, // 95	5E	Pad 7 (halo)	ハロー
  1, // 96	5F	Pad 8 (sweep)	スウィープ
// Synth Effects
  0, // 97	60	FX 1 (rain)	雨
  0, // 98	61	FX 2 (soundtrack)	サウンドトラック
  0, // 99	62	FX 3 (crystal)	クリスタル
  0, // 100	63	FX 4 (atmosphere)	アトモスフィア
  0, // 101	64	FX 5 (brightness)	ブライトネス
  0, // 102	65	FX 6 (goblins)	ゴブリン
  0, // 103	66	FX 7 (echoes)	エコー[要曖昧さ回避]
  0, // 104	67	FX 8 (sci-fi)	サイファイ
// Ethnic
  1, // 105	68	Sitar	シタール
  1, // 106	69	Banjo	バンジョー
  1, // 107	6A	Shamisen	三味線
  1, // 108	6B	Koto	琴
  1, // 109	6C	Kalimba	カリンバ
  1, // 110	6D	Bagpipe	バグパイプ
  1, // 111	6E	Fiddle	フィドル
  1, // 112	6F	Shanai	シャハナーイ
// Percussive
  0, // 113	70	Tinkle Bell	ティンクルベル
  0, // 114	71	Agogo	アゴゴ
  0, // 115	72	Steel Drums	スチールドラム
  0, // 116	73	Woodblock	ウッドブロック
  0, // 117	74	Taiko Drum	太鼓
  0, // 118	75	Melodic Tom	メロディックタム
  0, // 119	76	Synth Drum	シンセドラム
  0, // 120	77	Reverse Cymbal	逆シンバル
 // Sound effects
  0, // 121	78	Guitar Fret Noise	ギターフレットノイズ
  0, // 122	79	Breath Noise	ブレスノイズ
  0, // 123	7A	Seashore	海岸
  0, // 124	7B	Bird Tweet	鳥の囀り
  0, // 125	7C	Telephone Ring	電話のベル
  0, // 126	7D	Helicopter	ヘリコプター
  0, // 127	7E	Applause	拍手
  0, // 128	7F	Gunshot
};
