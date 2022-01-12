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

byte mode_flag = 0 ;
boolean US_100_test = false;

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
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
}

void KTR_1_Turn_right() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void KTR_1_break() {
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
long US_100() {
  //US-100 URL:https://www.instructables.com/Simple-Arduino-and-HC-SR04-Example/
  long duration, distance;
  digitalWrite(Trig, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(Trig, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 2) / 29.1;
  return distance;
}

int VRvol() {
  int VRvol ;
  VRvol = analogRead(VR);
  VRvol = map(VRvol, 0, 1023, 440, 932);
  return VRvol;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(VR, INPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(ECHO, INPUT);

  tone(BUZZ, 440, 50); delay(50);
  delay(50);
  tone(BUZZ, 440, 50); delay(50);
  delay(50);

  //LED test
  for (int i = 0; i <= 2; i++) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    delay(100);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    delay(100);
  }
  delay(500);
  if (digitalRead(SW1) == HIGH && digitalRead(SW2) == LOW) {
    mode_flag = 1 ;
  }
  if (digitalRead(SW1) == LOW && digitalRead(SW2) == HIGH) {
    mode_flag = 2 ;
  }
  if (digitalRead(SW1) == HIGH && digitalRead(SW2) == HIGH) {
    mode_flag = 3 ;
  }
  if (mode_flag == 1) {
    for (int i = 0; i <= 4; i++) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      delay(100);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      delay(100);
    }
  } else if (mode_flag == 2) {
    for (int i = 0; i <= 4; i++) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      delay(100);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      delay(100);
    }
  } else if (mode_flag == 3) {
    for (int i = 0; i <= 4; i++) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      delay(100);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      delay(100);
    }
  }
  tone(BUZZ, 880, 750); delay(750);
  delay(1000);
}

void loop() {

  if (mode_flag == 0 ) {
    if (digitalRead(SW1) == HIGH) {
      KTR_1_straight();
    }
    if (digitalRead(SW2) == HIGH) {
      KTR_1_back();
    }
    if (US_100() < 10) {
      KTR_1_break();
    }

  } else if (mode_flag == 1 ) {
    if (US_100() < 10 &&  US_100() >= 6) {  //
      KTR_1_Coasting();
    } else if (US_100() < 6) {  //
      KTR_1_back();
    } else {
      KTR_1_straight();
    }
  }  else if (mode_flag == 2 ) {
    KTR_1_Coasting();
  }  else if (mode_flag == 3 ) {
    KTR_1_Coasting();
  }



  //SW-LED
  if (digitalRead(SW1) == HIGH) {
    digitalWrite(LED1, HIGH);
  } else {
    digitalWrite(LED1, LOW);
  }

  if (digitalRead(SW2) == HIGH) {
    digitalWrite(LED2, HIGH);
  } else {
    digitalWrite(LED2, LOW);
  }


  //VR スピーカテスト
  if (digitalRead(SW1) == HIGH && digitalRead(SW2) == HIGH) {
    tone(BUZZ, VRvol());
    KTR_1_break();
    delay(500);
  } else {
    noTone(BUZZ);
  }

  //US-100テスト
  if (US_100() < 10) {
    if (US_100_test == false) {
      tone(BUZZ, 440, 50); delay(50);
      delay(50);
      US_100_test = true ;
    }
  } else if (US_100() >= 10) {
    US_100_test = false ;
  }
}
