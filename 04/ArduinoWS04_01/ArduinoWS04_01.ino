
/*
 第4回Arduino勉強会
 座席表サイト（15ページ目）
*/

#include <SPI.h>
#include <Ethernet.h>
//#include <Ethernet2.h>       // Ethernetシールドv2の場合はこちらを使う

// 定数の宣言
const int analogInPin = A0;    // アナログ入力ピン
const int ledPin01 = 9;        // LEDピン01

EthernetClient client;

// MACアドレス
byte mac[] = { 0x00, 0x50, 0xC2, 0x97, 0x20, 0xAF };
// ArduinoのIPアドレス（DHCP不使用の場合はコメントを外してIPを指定）
//IPAddress ip(192,168,1, 92);
// 接続先サイトIPアドレス
byte server[] = { 153,121,53,226 };

// 変数の宣言
int sensorValue = 0;        // センサ読み取り値
int outputValue = 0;        // 出力値
int seatID= 25;             //座席ID
int threshold = 250;        //圧力センサしきい値

// 初期化
void setup() {
    // シリアル通信の開始（通信速度9600bps）
    Serial.begin(9600);
    pinMode(ledPin01, OUTPUT);
    digitalWrite(ledPin01,LOW);

    // ネットワークに接続する
    if (Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");
        
        //DHCP不使用の場合はコメントを外してIPを固定して接続する
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

    //圧力センサの値で着席/離席判断
    if(sensorValue < threshold){
        outputValue = 0;            // 離席
    }else{
        outputValue = 1;            // 着席
    }

    //サイトに接続
    Serial.println("connecting...");
    if (client.connect(server, 80)) {

        Serial.println("connected");
        digitalWrite(ledPin01,LOW);
        
        // データ受け渡し
        client.print("GET /arduino_ws04_01/database/update.php?seat_id=");
        client.print(seatID);
        client.print("&on=");
        client.print(outputValue);   
        client.println(" HTTP/1.0");
        client.println();

        //上記ではclientに以下の文字列を書き込んでいます。
        //"GET /arduino_ws04_01/database/update.php?seat_id=1&on=1  HTTP/1.0"
        //これはWebブラウザで以下のようにアクセスするのと同じです。
        //http://153.121.53.226/arduino_ws04_01/database/update.php?seat_id=1&on=1
    
        delay(100);                    // 100秒待機    
        client.stop();

    } else {
        Serial.println("connection failed");
        digitalWrite(ledPin01,HIGH);
    }
    delay(3000);                   // サーバ負荷低減のための待機
}
