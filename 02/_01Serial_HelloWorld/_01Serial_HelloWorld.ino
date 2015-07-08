
/*
 第2回Arduino勉強会
 シリアルモニタを使ってみよう（7ページ目）
*/

// 初期化
void setup() {
  // シリアル通信の開始（通信速度9600bps）
  Serial.begin(9600);
}

// メイン処理の記述
void loop() {
  // シリアルに文字列"Hello,world!"を書き出す
  Serial.println("Hello, world!");
  // 300ミリ秒待機する
  delay(300);
}
