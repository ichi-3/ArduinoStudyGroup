
import processing.serial.*;

// myPort
Serial myPort;

int d; //直径
int fillColor;  //塗り潰し色

void setup(){
  //ウィンドウサイズの指定
  size(768, 768);
  //シリアル通信の初期化
  myPort = new Serial(this, "/dev/cu.usbmodem1451", 9600);
  myPort.clear();    //バッファのクリア
  //serialEvent()が発動するきっかけの文字列の指定
  myPort.bufferUntil(10);  //改行コード(ラインフィード)ASCIIコードで「10」
}

void draw(){
  background(0);
  fill(0,fillColor,fillColor);
  ellipse(width/2,height/2,d,d);
}

//シリアルイベント
void serialEvent(Serial p){
  delay(10);
  // シリアルバッファーを読込み
  String myString = myPort.readStringUntil(10);
  if(myString != null){
    println(myString);
    // 空白文字など余計な情報を消去
    myString = trim(myString);
    // コンマ区切りで複数の情報を読み込む
    int sensors[] = int(split(myString, ','));
    // 読み込んだ情報の数だけ、配列に格納
    if (sensors.length >= 1) {
      d = (int)map(sensors[0], 0, 1023, 0, height);
      fillColor = (int)map(sensors[1], 0, 1023, 0, 255);
    }
  }
  // 読込みが完了したら、次の情報を要求
  myPort.write('A');
}
//マウスクリックイベント
void mousePressed(){
  //開始用データ送信
  myPort.write('A');
}
