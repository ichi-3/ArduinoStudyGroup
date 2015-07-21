
// LEDに使うデジタルピンの番号の定義
const int ledPin01 = 9;
// シリアルで読み取った文字列を格納する変数
char received;

void setup() {
    // シリアル通信の開始
    Serial.begin(9600);
    // LED用のピンを出力に設定
    pinMode(ledPin01, OUTPUT);
}

void loop() {
    // 条件分岐：もしも、シリアルに何か届いていたら
    if (Serial.available() > 0) {
        // 1バイト読み込んで文字に変換
        received = (char)Serial.read();
        // 読み込んだ文字をPCに送り返す
        Serial.println(received);
        // LEDを点ける（LEDピンの電圧をHIGHにする）
        digitalWrite(ledPin01,HIGH);
        // 1000ミリ秒待機
        delay(1000);
        // LEDを消す（LEDピンの電圧をLOWにする）
        digitalWrite(ledPin01,LOW);
    }
}
