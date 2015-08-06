
/*
 第4回Arduino勉強会
 温度表示サイト（20ページ目）
*/

#include <SPI.h>            // イーサネットシールドはSPIでArduinoと通信するのでSPI用ヘッダファイルを読み込む
#include <Ethernet.h>       // イーサネットを使用するためのヘッダファイル読み込み
//#include <Ethernet2.h>       // Ethernetシールドv2の場合はこちらを使う

// 定数の宣言
const int analogInPin = A0;    // アナログ入力ピン
const int ledPin01 = 9;        // LEDピン01

EthernetClient client;

// MACアドレスの指定（各自の環境に併せて書き換えます）
byte mac[] = { 0x00, 0x50, 0xC2, 0x97, 0x20, 0xAF };
// ArduinoのIPアドレス（DHCP不使用の場合はコメントを外してIPを指定）
//IPAddress ip(192,168,1, 92);
// 接続先サイトIPアドレス
byte server[] = { 153,121,53,226 };

// 変数の宣言
int sensorValue = 0;        // センサ読み取り値
int outputValue = 0;        // 出力値
int seatID= 21 ;            //座席ID
int threshold = 250;        //圧力センサ閾値

// 初期化
void setup() {
    // シリアル通信の開始（通信速度9600bps）
    Serial.begin(9600);
    pinMode(ledPin01, OUTPUT);
    digitalWrite(ledPin01,LOW);

    // ネットワークに接続する
    if (Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");

        // DHCP不使用の場合はコメントを外してIPを固定して接続する
        //Ethernet.begin(mac, ip);
    }
    delay(1000);    
}

// メイン処理の記述
void loop() {
    //センサ値読み取り
    sensorValue = analogRead(analogInPin);
    Serial.print("sensorValue = ");
    Serial.println(sensorValue);

    //温度センサの値を温度に変換(小数点第1位を送付するため10倍の値にしています。)
    outputValue = sensorValue * 10;   //整数型で計算のため、先に10を掛ける
    outputValue = outputValue * 0.48; //Arduinoのセンサ読み取り値を温度に変換する係数
    Serial.print("outputValue = ");
    Serial.println(outputValue);

    //サイトに接続する
    Serial.println("connecting...");
    if (client.connect(server, 80)) {
        
        digitalWrite(ledPin01,LOW);
        Serial.println("connected");
        
        // データ受け渡し
        client.print("GET /arduino_ws04_02/database/add.php?seat_id=");
        client.print(seatID);
        client.print("&temp=");
        client.print(outputValue);
        client.println(" HTTP/1.0");
        client.println();
    
    //上記ではclientに以下のような文字列を書き込んでいます。
    //"GET /arduino_ws04_02/database/update.php?seat_id=1&on=263  HTTP/1.0"
    //これはWebブラウザで以下のようにアクセスするのと同じです。
    //http://153.121.53.226/arduino_ws04_02/database/add.php?seat_id=1&temp=263
    
    delay(100);                        // 100秒待機    
    client.stop();
    
  } else {
    Serial.println("connection failed");
    digitalWrite(ledPin01,HIGH);
  }
  delay(3000);                        // サーバ負荷低減のための待機
}
