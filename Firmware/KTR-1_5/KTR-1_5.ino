const int LED1 = 14;
const int LED2 = 15;
const int BUZZ = 5;
const int Trig = 7;
const int AIN1 = 3;
const int AIN2 = 6;
const int BIN1 = 9;
const int BIN2 = 10;
const int VR = A0;
const int SW1 = A1;
const int SW2 = A2;
const int ECHO = 8;

//bool HC_SR04_test = false;

int HC_SR04_mm() {
  float duration, distance;
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 2) * 0.340;
  return (int)distance;

}


void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(ECHO, INPUT);
}
void loop() {
  Serial.print("HC_SR04_mm:");
  Serial.print(HC_SR04_mm());
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(100);
  Serial.println(",");

  if (HC_SR04_mm() < 100) {
//    if (HC_SR04_test == false) {
      tone(BUZZ, 440, 50); delay(50);
      delay(50);
//      HC_SR04_test = true ;
  
//  } else if (HC_SR04_mm() >= 100) {
//    HC_SR04_test = false ;
  }
}
