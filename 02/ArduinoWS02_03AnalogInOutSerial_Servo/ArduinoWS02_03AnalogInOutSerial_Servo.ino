
/*
 第2回Arduino勉強会
 出力装置を変えてみよう②（21ページ目）
*/

#include <Servo.h>

// 変数の宣言
const int analogInPin = A0;    // アナログ入力に使用するピン番号の定義
const int analogOutPin = 9;    // LEDに使うピンの番号の定義

// 変数の宣言
int sensorValue = 0;           // センサー入力値
int outputValue = 0;           // LED用出力値
Servo myservo;                 // サーボの変数名の宣言

// 初期化
void setup() {
  // シリアル通信の開始（通信速度9600bps）
  Serial.begin(9600);
  // サーボ制御ピンを割り当て
  myservo.attach(analogOutPin);
}

// メイン処理の記述
void loop() {
  // アナログ入力値を読み取る（0〜1023）
  sensorValue = analogRead(analogInPin);
  // 値の調整：150〜700のsensorValueを0〜180に割り振ってoutputValueへ
  outputValue = map(sensorValue, 170, 700, 0, 180);

  // サーボの回転角度を指示
  myservo.write(outputValue);

  Serial.print("sensor = " );    // 文字列「sensor=」をシリアルポートに書き出す
  Serial.print(sensorValue);     // センサー読み取り値をシリアルポートに書き出す
  Serial.print("\t output = ");  // 文字列「\t output=」をシリアルポートに書き出す
  Serial.println(outputValue);   // LED用出力値をシリアルポートに書き出す

  // 待機を100ミリ秒に増加
  delay(100);
}
