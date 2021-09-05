import controlP5.*;

ControlP5 p5; 
Button GOButton;
Button STOPButton;
int xcoordinate;
int ycoordinate;
int hcoordinate;
int wcoordinate;
int scoordinate;
import processing.serial.*;
Serial myPort;
String inString;


void setup() { 
  size(800, 600); 
  p5 = new ControlP5(this);

  GOButton = p5.addButton("GO");

  GOButton.setPosition(100, 500);
  GOButton.setSize(200, 100);

  STOPButton = p5.addButton("STOP");

  STOPButton.setPosition(400, 500);
  STOPButton.setSize(200, 100);

  printArray(Serial.list());
  myPort = new Serial(this, "COM3", 9600);
  myPort.write("+++");
  delay(1100);
  myPort.write("ATID 3002, CH C, CN");
  delay(1100);
  myPort.bufferUntil(10);
}
void draw() {
  background(255, 255, 255, 255);
  rect(xcoordinate, ycoordinate, wcoordinate, hcoordinate);
}
public void controlEvent( ControlEvent ev ) {

  if ( ev.isFrom( GOButton ) ) {
    println("Button: GO");
    myPort.write( 'g' );

    myPort.write('\n');
  }
  if ( ev.isFrom( STOPButton ) ) {
    println("Button: STOP");
    myPort.write( 's' );

    myPort.write('\n');
  }
}

void serialEvent(Serial p) {
  inString = p.readString();
  println(inString);
  if (inString.charAt(0) == 'x') {
    inString = trim(inString);

    inString = inString.substring(1);

    xcoordinate = Integer.parseInt(inString);
    println(xcoordinate);
  }
  else if (inString.charAt(0) == 'y') {
    inString = trim(inString);

    inString = inString.substring(1);

    ycoordinate = Integer.parseInt(inString);
    println(ycoordinate);
  }
  else if (inString.charAt(0) == 'h') {
    inString = trim(inString);

    inString = inString.substring(1);

    hcoordinate = Integer.parseInt(inString);
    println(hcoordinate);
  }
  else if (inString.charAt(0) == 'w') {
    inString = trim(inString);

    inString = inString.substring(1);

    wcoordinate = Integer.parseInt(inString);
    println(wcoordinate);
  }
  else if (inString.charAt(0) == 's') {
    inString = trim(inString);

    inString = inString.substring(1);

    scoordinate = Integer.parseInt(inString);
    println(scoordinate);
  }
  
}
