
/*
 第2回Arduino勉強会
 発展：フルカラーLEDで表示（24ページ目）
*/

// 定数の宣言
const int analogInPin = A0;     // アナログ入力に使用するピン番号の定義
const int analogOutPinR = 9;    // LED（赤）に使うピンの番号の定義
const int analogOutPinG = 11;   // LED（緑）に使うピンの番号の定義
const int analogOutPinB = 10;   // LED（青）に使うピンの番号の定義

// 変数の宣言
int sensorValue = 0;            // センサーの入力値
int outputValue = 0;            // LED用出力値

// 初期化
void setup() {
  // シリアル通信の開始（通信速度9600bps）
  Serial.begin(9600);
}

// メイン処理の記述
void loop() {
  // アナログ入力値を読み取る（0〜1023）
  sensorValue = analogRead(analogInPin);
  // 値の調整：150〜700のsensorValueを0〜511に割り振ってoutputValueへ
  outputValue = map(sensorValue, 150, 700, 0, 511);
  
  // 値が半分以下の場合は、赤に近づける
  if(outputValue <= 255){
    analogWrite(analogOutPinR, 255);
    analogWrite(analogOutPinG, 255 - outputValue);
    analogWrite(analogOutPinB, outputValue);
   }
   // 値が半分より大きい場合は、青に近づける
  else{
    outputValue = outputValue - 256;
    analogWrite(analogOutPinR, 255 - outputValue);
    analogWrite(analogOutPinG, outputValue);
    analogWrite(analogOutPinB, 255);
  }

  Serial.print("sensor = " );    // 文字列「sensor=」をシリアルポートに書き出す
  Serial.print(sensorValue);     // センサー読み取り値をシリアルポートに書き出す
  Serial.print("\t output = ");  // 文字列「\t output=」をシリアルポートに書き出す
  Serial.println(outputValue);   // LED用出力値をシリアルポートに書き出す

  // 待機を2ミリ秒に増加
  delay(2);
}
