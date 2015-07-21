import processing.serial.*;

Serial myPort;
int d; //

void setup(){
  size(768, 768);
  d=3;  //
  myPort = new Serial(this, "/dev/tty.usbmodem1451", 9600);
}

void draw(){
  background(0);
  fill(0, 255, 255);
  ellipse(width/2,height/2,d,d);
  delay(50);
}

void serialEvent(Serial p){
  d = p.read();
  println(d);
  if(d<10){
    d=10;
  }
}
