
const int analogInPin = A0;  // アナログ入力ピン
const int analogOutPin = 9; // アナログ出力ピン(LEDピン)

int sensorValue = 0;        // センサ読み取り値
int outputValue = 0;        // 出力値

void setup() {
  // put your setup code here, to run once:
  // シリアル開始
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //センサ値読み取り
  sensorValue = analogRead(analogInPin);
  // 入力値をマッピングして調整
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  //LEDを入力量に応じて光らせる
  analogWrite(analogOutPin, outputValue);
  // シリアルにバイトデータ形式で出力:
  Serial.write(outputValue);
  //待機
  delay(2);
}
