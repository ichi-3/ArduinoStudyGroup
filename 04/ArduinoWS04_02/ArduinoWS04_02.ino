#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x00, 0x50, 0xC2, 0x97, 0x20, 0xAF }; // ここは MAC アドレス
//IPAddress ip(192,168,1, 92); // ここは IP アドレス
byte server[] = { 153,121,53,226 }; // 接続サイトIPアドレス

EthernetClient client;

const int analogInPin = A0;  // アナログ入力ピン
const int ledPin01 = 9; // LEDピン01
int sensorValue = 0;        // センサ読み取り値
int outputValue = 0;        // 出力値
int seatID= 25 ;   //座席ID
int threshold = 250;  //圧力センサしきい値

void setup() {
  Serial.begin(9600);
  pinMode(ledPin01, OUTPUT);
  digitalWrite(ledPin01,LOW);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    //Ethernet.begin(mac, ip);
  }
  delay(1000);    
}

void loop() {

  //センサ値読み取り
  sensorValue = analogRead(analogInPin);
  Serial.print("sensorValue = ");
  Serial.println(sensorValue);
  //温度センサの値を温度( ℃ )に変換(小数点第1位を送付するため10倍の値にしています。)
  outputValue = sensorValue * 10;
  outputValue = sensorValue * 0.48;
  Serial.print("outputValue = ");
  Serial.println(outputValue);

  //サイトに接続＆データ受け渡し
  Serial.println("connecting...");
  if (client.connect(server, 80)) {
    digitalWrite(ledPin01,LOW);
    Serial.println("connected");
    client.print("GET /arduino_ws042/database/update.php?seat_id=");
    client.print(seatID);
    client.print("&temp=");
    client.print(outputValue);   
    client.println(" HTTP/1.0");
    client.println();
    //上記ではclientに以下のような文字列を書き込んでいます。
    //"GET /arduino_ws04_02/database/update.php?seat_id=1&on=263  HTTP/1.0"
    //これはWebブラウザで以下のようにアクセスするのと同じです。
    //http://153.121.53.226/arduino_ws04_02/database/update.php?seat_id=1&temp=263
    
    delay(100);  //100秒待機    
    client.stop();
  } else {
    Serial.println("connection failed");
    digitalWrite(ledPin01,HIGH);
  }
  delay(3000);  //サーバ負荷低減のための待機
}
