const int left_neg = 4;
const int left_pos = 5;
const int right_neg = 7;
const int right_pos = 6;
const int LEYE = A4; 
const int REYE = A3; 
const int WHEELEYE = 2;
const int US_TRIG = 9;
const int US_ECHO = 8;

double prev = 0;
double current = 0;
double prev_wheel = 0;
volatile long spoke_count = 0;  
bool past_wheel = false;
const double diam = 20.42;
double rotations = 0;

double distance = 0;
bool has_moved = false;
int distanceUS = 0;
long duration;


void setup() {
  Serial.begin(9600);
  pinMode(right_neg, OUTPUT);
  pinMode(right_pos, OUTPUT);
  pinMode(left_neg, OUTPUT);
  pinMode(left_pos, OUTPUT);
  pinMode( LEYE, INPUT );
  pinMode( REYE, INPUT );
  pinMode( US_TRIG, OUTPUT);
  pinMode( US_ECHO, INPUT); 
  attachInterrupt( digitalPinToInterrupt(WHEELEYE), SpokeCount, RISING); 
  pinMode(WHEELEYE, INPUT); 
  delay(  1000  );  //  Guard 
  Serial.print("+++");  
  delay(  1000  );
  Serial.println("ATID  3002, CH  C,  CN");
  delay(  1000  );  
  while(  Serial.read() !=  -1  );
  
 
 

}
void SpokeCount(){ // interupt which counts when spoke is detected
   spoke_count = spoke_count + 1;
   
}

void CheckSerial(){
   if (Serial.available())  { 
      char  inChar  = (char)Serial.read();
      if (inChar == 'g'){
        has_moved = true;  
        Serial.println("Started : Wireless go");
        
      }
       if (inChar == 's'){
        has_moved = false;  
        Serial.println("Stopped : Wireless stop");
      }
  }
}

void MoveStraight(){
  analogWrite(left_neg,0);
  analogWrite(left_pos,100);
  analogWrite(right_neg,0);
  analogWrite(right_pos,115);
}

void TurnLeft(){
  analogWrite(left_neg,0);
  analogWrite(left_pos,30);
  analogWrite(right_neg,0);
  analogWrite(right_pos, 200);
}

void TurnRight(){
  analogWrite(right_neg,0);
  analogWrite(right_pos,40);
  analogWrite(left_neg,0);
  analogWrite(left_pos,180);
}

void Stop(){
  analogWrite(left_neg,0);
  analogWrite(left_pos,0);
  analogWrite(right_neg,0);
  analogWrite(right_pos,0); 
}

void MeasureUS(){
 
  
  digitalWrite( US_TRIG, LOW );
  delayMicroseconds(2);

  digitalWrite( US_TRIG, HIGH );
  delayMicroseconds(10  );
  digitalWrite( US_TRIG, LOW );
  duration = pulseIn( US_ECHO, HIGH );
  distanceUS = duration/58;
}

void Report(){
  rotations = (double(spoke_count) / 5);
 // circumference of 20.42cm on the 6.5cm diam wheels
 distance += (rotations * diam) / 100;
// Serial.println(spoke_count);
// Serial.println(vel);
 Serial.println(distance);
 
 spoke_count = 0;
 prev_wheel = current;
}

void loop() {
  
 CheckSerial();
 if (has_moved == true){
 bool Leftsees = digitalRead(LEYE);
 bool Rightsees = digitalRead(REYE);
 if (Leftsees && Rightsees){
  MoveStraight();
//  Serial.print("Sees both eyes\n");
 }
 else if (!Leftsees && !Rightsees){
  MoveStraight();
//  Serial.print("Sees neither of eyes\n");
 }
 else if (!Leftsees){
  TurnLeft();
//  Serial.print("sees left eye\n");
 }
 else if (!Rightsees){
  TurnRight();
//  Serial.print("sees right eye\n");
 }
 //delay(25);
 current = millis();
 if (((current - prev)) >= 50){
    prev = current;
    MeasureUS();
  if (distanceUS <= 10){
    Serial.println("Stopped : US object");
    while (distanceUS <= 10){
      Stop();
      MeasureUS();
    }
  }
// Serial.println(distance);
 }

// Serial.println(spoke_count);
if ((current - prev_wheel) >= 1000){
 Report();
}

 
 delay(25);
 }
 else if (has_moved == false) {
  Stop();
 }
}




