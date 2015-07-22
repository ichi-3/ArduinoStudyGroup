
/*
 第3回Arduino勉強会
 センサのビジュアライズ（12ページ目）
*/

// 定数の宣言
const int analogInPin = A0;  // アナログ入力ピン
const int analogOutPin = 9; // アナログ出力ピン(LEDピン)
// 変数の宣言
int sensorValue = 0;        // センサ読み取り値
int outputValue = 0;        // 出力値

// 初期化
void setup() {
  // シリアル開始
  Serial.begin(9600);
}

// メイン処理の記述
void loop() {
  //センサ値読み取り
  sensorValue = analogRead(analogInPin);
  // 値の調整：0〜1023のsensorValueを0〜255に割り振ってoutputValueへ
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  //LEDを入力量に応じて光らせる
  analogWrite(analogOutPin, outputValue);
  // シリアルにバイトデータ形式で出力:
  Serial.write(outputValue);
  // 待機
  delay(2);
}
