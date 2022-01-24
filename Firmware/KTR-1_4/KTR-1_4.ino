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

void KTR_1_straight() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void KTR_1_back() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void KTR_1_Turn_left() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void KTR_1_Turn_right() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void KTR_1_brake() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, HIGH);
}

void KTR_1_Coasting() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
}

void loop() {
  if (digitalRead(SW1) == HIGH && digitalRead(SW2) == HIGH ) {
    KTR_1_brake();
    while(true){
       if (digitalRead(SW1) == LOW && digitalRead(SW2) == LOW ) break;
    }
  }else if (digitalRead(SW1) == HIGH && digitalRead(SW2) == LOW) {
    KTR_1_straight();
  }else if (digitalRead(SW1) == LOW && digitalRead(SW2) == HIGH) {
   KTR_1_back();
  }
}
