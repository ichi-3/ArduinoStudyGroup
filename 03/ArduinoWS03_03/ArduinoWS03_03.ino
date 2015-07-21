
const int analogInPin = A0;  // アナログ入力ピン
const int analogOutPin = 9; // アナログ出力ピン(LEDピン)
int sensorValue = 0;        // センサ読み取り値
int outputValue = 0;        // 出力値
int inByte;                 //シリアル読み取り値

void setup() {
  Serial.begin(9600);   // シリアル開始
  Serial.write(0);      // データ初回送信
}

void loop() {
  // もし、データを受信していたら
  if (Serial.available() > 0) {
    // 1バイト読み込み:
    inByte = Serial.read();
    //LEDを読み込んだ値で光らせる
    analogWrite(analogOutPin, inByte);
    //センサ値読み取り
    sensorValue = analogRead(analogInPin);
    // 入力値をマッピングして調整
    outputValue = map(sensorValue, 0, 1023, 0, 255);
    // シリアルにバイトデータ形式で出力:
    Serial.write(outputValue);
  } 
  delay(2);//待機
}
