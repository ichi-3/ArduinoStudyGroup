#include <Adafruit_NeoPixel.h>  //テープLEDライブラリのAdafruit_NeoPixelの読み込み
#define LED_NUM 5 
#define TAPE_CONTROL 6

//テープLEDライブラリのAdafruit_NeoPixelのインスタンス作成
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NUM, TAPE_CONTROL, NEO_GRB + NEO_KHZ800);

float s = 1.0;  //彩度
float v = 0.50;  //明度
int r,g,b;  //RGB値

int rgbSts[LED_NUM][3]; //各LEDのRGB値記録用配列
int setCntr;  //現在操作中のLED番号

int buttonLedPin = 9; //単色LED用ピン番号
bool interruptStat;   //割り込みステータス

void setup() {
  //現在操作中のLED番号の初期化
  setCntr=0;
  //LEDのRGB情報の初期化
  for(int i=0; i<LED_NUM; i++) {
    rgbSts[i][0] = 0;
    rgbSts[i][1] = 0;
    rgbSts[i][2] = 0;
  }

  //テープLED制御の開始
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  //デバッグ用シリアル通信の初期化
  Serial.begin(9600);
  Serial.print("LEDs: ");
  Serial.println(strip.numPixels());  
  
  //割り込みを設定：割り込み番号0(Pin2),呼び出す関数 interrupt(),モード 電圧の立ち上がり
  attachInterrupt(0, interrupt, RISING);
  //割り込みフラグの初期化
  interruptStat = false;
  
  //単色LEDピンのピンモードを出力に設定
  pinMode(buttonLedPin,OUTPUT);

}

void loop() {
  //割り込みがあったかチェック
  if(interruptStat){
    //カウンターアップ
    setCntr++;
    //LED個数を超えていた場合0にする
    setCntr=setCntr % LED_NUM;
    //単色LEDを目印として光らせる
    digitalWrite(buttonLedPin,HIGH);
    delay(300);
    digitalWrite(buttonLedPin,LOW);
    //割り込みフラグをリセット
    interruptStat=false;  
  }

  //ボリューム抵抗の読み取り
  int temp01 = analogRead(A0);
  //デバッグ用にPCへシリアルで送信
  Serial.print("A0: ");
  Serial.print(temp01);
  
  //読み取ったリューム抵抗の値から色相を計算
  int h = map(temp01, 0, 1023, 360);
  //デバッグ用にPCへシリアルで送信  
  Serial.print(" _ h: ");
  Serial.print(h);
  //HSV(色相・彩度・明度)からRGBを計算
  hsv2rgb(h,s,v);
  //デバッグ用にPCへシリアルで送信  
  Serial.print(" _ r: ");
  Serial.print(r); 
  Serial.print(" _ g: ");
  Serial.print(g); 
  Serial.print(" _ b: ");
  Serial.println(b); 

  //求めたRGB値を現在操作中のLED番号に設定
  rgbSts[setCntr][0] = r;
  rgbSts[setCntr][1] = g;
  rgbSts[setCntr][2] = b;
  
  //LED発光させる
  strip.setPixelColor(setCntr, rgbSts[setCntr][0], rgbSts[setCntr][1], rgbSts[setCntr][2]);
  //設定を反映させる
  strip.show();

  delay(100);
}

/*/////////////////////////////////////////////////////////////////
HSV(色相・彩度・明度)からRGBを計算する関数
RGBの戻り値はグローバル変数に記述
/////////////////////////////////////////////////////////////////*/
void hsv2rgb(int h , float s , float v){
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

/*/////////////////////////////////////////////////////////////////
割り込み処理で呼ばれる関数
割り込みがあったことを示すフラグを立てる
/////////////////////////////////////////////////////////////////*/
void interrupt() {
  interruptStat = true;
}
