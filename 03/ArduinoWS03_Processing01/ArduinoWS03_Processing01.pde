
// シリアルクラスをインポート（決まり文句）
import processing.serial.*;

Serial myPort;      // シリアルポートの名前を定義
int d;              // 円の直径

void setup() {
  size(768, 768);   // 画面サイズ
  d=3;              // 円の直径の初期値
  // 円を描画する（X座標,Y座標,X経,Y経）
  myPort = new Serial(this, "/dev/tty.usbmodem1451", 9600);
}

void draw() {
  // 背景色の設定（黒）
  background(0);
  // 塗りつぶし色の設定（R,G,B）
  fill(0, 255, 255);
  // 円を描画する
  ellipse(width/2,height/2,d,d);
  // 50ミリ秒待機
  delay(50);
}

void serialEvent(Serial p) {
  // シリアルを1バイト読み込み直径に設定
  d = p.read();
  // デバッグ出力に直径を出力
  println(d);
  // 直径の値が10未満なら直径を10に設定、10以上ならそのまま
  if(d<10) {
    d=10;
  }
}
