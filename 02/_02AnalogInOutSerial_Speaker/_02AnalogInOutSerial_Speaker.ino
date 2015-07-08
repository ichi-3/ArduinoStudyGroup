
/*
 第2回Arduino勉強会
 出力装置を変えてみよう①（18ページ目）
*/

// 定数の宣言
const int analogInPin = A0;    // アナログ入力に使用するピン番号の定義
const int analogOutPin = 9;    // LEDに使うピンの番号の定義

// 変数の宣言
int sensorValue = 0;           // センサー入力値
int outputValue = 0;           // LED用出力値

// 初期化
void setup() {
  // シリアル通信の開始（通信速度9600bps）
  Serial.begin(9600);
}

// メイン処理の記述
void loop() {
  // アナログ入力値を読み取る（0〜1023）
  sensorValue = analogRead(analogInPin);
  // 値の調整：150〜700のsensorValueを20〜1000に割り振ってoutputValueへ
  outputValue = map(sensorValue, 150, 700, 20, 1000);

  // アナログ出力ピンから指定の周波数の波形出力する関数
  tone(analogOutPin, outputValue);

  Serial.print("sensor = " );    // 文字列「sensor=」をシリアルポートに書き出す
  Serial.print(sensorValue);     // センサー読み取り値をシリアルポートに書き出す
  Serial.print("\t output = ");  // 文字列「\t output=」をシリアルポートに書き出す
  Serial.println(outputValue);   // LED用出力値をシリアルポートに書き出す

  // 2ミリ秒待機
  delay(2);
}
