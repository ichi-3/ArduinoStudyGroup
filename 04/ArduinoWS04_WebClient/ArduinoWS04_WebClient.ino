
/*
 第4回Arduino勉強会
 Web client（9ページ目）
*/

#include <SPI.h>            // イーサネットシールドはSPIでArduinoと通信するのでSPI用ヘッダファイルを読み込む
#include <Ethernet.h>       // イーサネットを使用するためのヘッダファイル読み込み

// MACアドレスの指定（各自の環境に併せて書き換えます）
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//IPAddress server(74,125,232,128);  // DNSを使用しない場合は直接指定する
char server[] = "www.google.com";    // Googleのアドレスを指定

// IPアドレスを直接指定する場合はここに記入する
//IPAddress ip(192, 168, 0, 177);

// 接続クライアントの名前宣言
EthernetClient client;

// 初期化
void setup() {
    // シリアル通信の開始（通信速度9600bps）
    Serial.begin(9600);
    while (!Serial) {
        ;
    }

    // ネットワークに接続する
    if (Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");

        // DHCP不使用の場合はコメントを外してIPを固定して接続する
        //Ethernet.begin(mac, ip);
  }
    delay(1000);
    Serial.println("connecting...");

    // サイトに接続する
    if (client.connect(server, 80)) {
        Serial.println("connected");

        client.println("GET /search?q=arduino HTTP/1.1");
        client.println("Host: www.google.com");
        client.println("Connection: close");
        client.println();
    } else {
        Serial.println("connection failed");
    }
}

// メイン処理の記述
void loop()
{
    if (client.available()) {
        char c = client.read();
        Serial.print(c);
    }

    if (!client.connected()) {
        Serial.println();
        Serial.println("disconnecting.");
        client.stop();

        while (true);
    }
}
