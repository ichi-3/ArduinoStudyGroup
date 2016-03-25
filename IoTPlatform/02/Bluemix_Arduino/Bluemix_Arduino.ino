
/*
 IoTプラットホーム活用勉強会
 Bluemix-Arduino連携（6ページ目）
*/

#include <SPI.h>
#include <Ethernet.h>
//#include <Ethernet2.h>       // Ethernetシールドv2の場合はこちらを使う
#include <PubSubClient.h>

// MACアドレス
byte mac[]    = {0x90, 0xA2, 0xDA, 0x0F, 0xFB, 0x21 };
// デバイスID（MACアドレス）
char macstr[] = "90a2da0ffb21";

// char servername[]="（組織ID）.messaging.internetofthings.ibmcloud.com";
char servername[]="w15sdv.messaging.internetofthings.ibmcloud.com";
// String clientName = String("d:（組織ID）:（デバイスタイプ）:") + macstr;
String clientName = String("d:w15sdv:Arduino:") + macstr;
// String topicName = String("iot-2/evt/（イベント名）/fmt/json");
String topicName = String("iot-2/evt/status/fmt/json");
char username[]="use-token-auth";
// char password[]="（認証トークンの値）";
char password[]="9wVx0Lj5+BYer*rGas";

int sendDuration = 3000;       // データ送信間隔

const int analogInPin = A2;    // アナログ入力ピン
int sensorValue01 = 0;         // センサ読み取り値
const float s = 1.0;           // 彩度
const float v = 0.3;           // 明度
int r,g,b;                     // RGB値
const int PinR = 5;            // R出力ピン番号
const int PinG = 9;            // G出力ピン番号
const int PinB = 6;            // B出力ピン番号

// イーサネットクライアント
EthernetClient ethClient;
// MQTTクライアント
PubSubClient client(servername, 1883, 0, ethClient);

// 初期化
void setup() {
    // シリアル通信の開始（通信速度9600bps）
    Serial.begin(9600);
    Serial.println("Serial begin");
    // ネットワークに接続する
    if (Ethernet.begin(mac) == 0) {
        Serial.print("Failed to configure Ethernet using DHCP");
    }

    // カラーLEDピンのピンモードを出力に設定
    pinMode(PinR,OUTPUT);
    pinMode(PinG,OUTPUT);
    pinMode(PinB,OUTPUT);

    delay(1000);
}

// メイン処理の記述
void loop() {
    char clientStr[40];
    clientName.toCharArray(clientStr,40);
    char topicStr[26];
    topicName.toCharArray(topicStr,26);

    // センサ値読み取り
    sensorValue01 = analogRead(analogInPin);
    Serial.print("sensorValue01 = ");
    Serial.println(sensorValue01);
    // フルカラーLEDを光らせる
    brightFcLED(sensorValue01);

    if (!client.connected()) {
        Serial.print("Trying to connect to: ");
        Serial.println(clientStr);
        client.connect(clientStr,username,password);
    }

    if (client.connected() ) {
        String json = buildJson();
        char jsonStr[200];
        json.toCharArray(jsonStr,200);
        boolean pubresult = client.publish(topicStr,jsonStr);

        Serial.print("attempt to send ");
        Serial.println(jsonStr);
        Serial.print("to ");
        Serial.println(topicStr);
    
        if (pubresult) {
            Serial.println("successfully sent");
        } else {
            Serial.println("unsuccessfully sent");
        }
    }
    delay(sendDuration);
}

/*/////////////////////////////////////////////////////////////////
Bluemixへの送信用Json文字列を作成する関数
/////////////////////////////////////////////////////////////////*/
String buildJson() {
    String data = "{";
    data+="\n";
    data+= "\"d\": {";
    data+="\n";
    data+="\"myName\": \"Arduino Sensors\",";
    data+="\n";
    data+="\"Sensor01\": ";
    data+=(int)sensorValue01;
    data+="\n";
    data+="}";
    data+="\n";
    data+="}";
    return data;
}

/*/////////////////////////////////////////////////////////////////
引数を元にフルカラーLEDを(赤〜青に)光らせる関数
/////////////////////////////////////////////////////////////////*/
void brightFcLED(int sensorVal) {
    // センサの値を色相の赤〜青(0~239)に変換する
    int h = map( sensorVal , 0 , 1023 , 0 , 239);
  
    // HSV(色相・彩度・明度)からRGBを計算
    hsv2rgb( h , s , v);
    analogWrite( PinR , 255 - r);
    analogWrite( PinG , 255 - g);
    analogWrite( PinB , 255 - b);
}

/*/////////////////////////////////////////////////////////////////
HSV(色相・彩度・明度)からRGBを計算する関数
RGBの戻り値はグローバル変数に記述
/////////////////////////////////////////////////////////////////*/
void hsv2rgb(int h , float s , float v) {
    int i , lr , lg , lb , vi;
    int p1 , p2 , p3;
    float f;
    i = (int)(h / 60.0);
    f = h / 60.0 - i; 
    p1 = (int)(v * (1.0 - s) * 255.0);
    p2 = (int)(v * (1.0 - s * f) * 255.0);
    p3 = (int)(v * (1.0 - s * (1.0 - f)) * 255.0);
    vi = (int)(v * 255.0);        
    if(i == 0) {lr = vi ; lg = p3 ; lb = p1;}
    if(i == 1) {lr = p2 ; lg = vi ; lb = p1;}
    if(i == 2) {lr = p1 ; lg = vi ; lb = p3;}
    if(i == 3) {lr = p1 ; lg = p2 ; lb = vi;}
    if(i == 4) {lr = p3 ; lg = p1 ; lb = vi;}
    if(i == 5) {lr = vi ; lg = p1 ; lb = p2;}
    r = lr;
    g = lg;
    b = lb;
}


