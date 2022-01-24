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
boolean HC_SR04_test = false;

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
int HC_SR04_mm() {
  float duration, distance;
  int time_out = 8000;
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duration = pulseIn(ECHO, HIGH, time_out);
  distance = (duration / 2) * 0.340;
  return (int)distance;

}

int VRvol() {
  int VRvol ;
  VRvol = analogRead(VR);
  VRvol = map(VRvol, 0, 1023, 440, 932);
  return VRvol;
}

void setup() {
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
    if (HC_SR04_mm() < 100) {
      KTR_1_brake();
    }

  } else if (mode_flag == 1 ) {
    if (HC_SR04_mm() < 100 &&  HC_SR04_mm() >= 60) {  //
      KTR_1_Coasting();
    } else if (HC_SR04_mm() < 60) {  //
      KTR_1_back();
    } else {
      KTR_1_straight();
    }
  }  else if (mode_flag == 2 ) {
    KTR_1_Coasting();
  }  else if (mode_flag == 3 ) {
    while (true) {//自律走行
      if (digitalRead(SW1) == HIGH) {
        digitalWrite(LED1, HIGH);
        KTR_1_straight();
        while (true) {//自律走行ループ
          static int Turn_90 = 1005;
          static int Turn_180 = 2010 ;
          static int Go_straight = 1000 ;

          if (HC_SR04_mm() < 80) {//壁回避開始
            digitalWrite(LED2, HIGH);
            KTR_1_brake(); delay(1000);

            KTR_1_Turn_left(); delay(Turn_90);
            KTR_1_brake(); delay(500);
            int Turn_left_Distance = HC_SR04_mm();
            tone(BUZZ, 440, 100);

            KTR_1_Turn_right(); delay(Turn_180);
            KTR_1_brake(); delay(500);
            int Turn_right_Distance = HC_SR04_mm();
            tone(BUZZ, 440, 100);

            KTR_1_Turn_left(); delay(Turn_90);
            KTR_1_brake(); delay(500);

            if (Turn_left_Distance < 150 && Turn_right_Distance < 150) {//3方向囲まれていたら
              Serial.println("Error");
              tone(BUZZ, 960, 1000);
              for (int i = 0; i <= 5; i++) {//エラー出力
                digitalWrite(LED2, LOW);
                delay(100);
                digitalWrite(LED2, HIGH);
                delay(100);
              }
              digitalWrite(LED1, LOW);
              digitalWrite(LED2, LOW);
              break;//自律走行ループ終了

            } else {

              if (Turn_left_Distance >= Turn_right_Distance) {//90度横左のほうが遠かったら
                Serial.println("left_GO");
                KTR_1_Turn_left(); delay(Turn_90);

                KTR_1_brake(); delay(500);

                while (true) { //壁の縁調査開始
                  KTR_1_straight(); delay(Go_straight);
                  KTR_1_Turn_right(); delay(Turn_90);
                  KTR_1_brake(); delay(100);
                  if (HC_SR04_mm() >= 150) {
                    tone(BUZZ, 440, 100);
                    KTR_1_Turn_left(); delay(Turn_90);
                    KTR_1_straight(); delay(Go_straight);
                    KTR_1_Turn_right(); delay(Turn_90);
                    tone(BUZZ, 440, 100);
                    break;//壁の縁発見し抜ける
                  } else {
                    KTR_1_Turn_left(); delay(Turn_90);
                  }
                }
                digitalWrite(LED2, LOW);//壁回避終了
                KTR_1_straight();

              } else {//90度横右のほうが遠かったら
                Serial.println("right_GO");
                KTR_1_Turn_right(); delay(Turn_90);

                KTR_1_brake(); delay(500);

                while (true) { //壁の縁調査
                  KTR_1_straight(); delay(Go_straight);
                  KTR_1_Turn_left(); delay(Turn_90);
                  KTR_1_brake(); delay(100);
                  if (HC_SR04_mm() >= 150) {
                    tone(BUZZ, 440, 100);
                    KTR_1_Turn_right(); delay(Turn_90);
                    KTR_1_straight(); delay(Go_straight);
                    KTR_1_Turn_left(); delay(Turn_90);
                    tone(BUZZ, 440, 100);
                    break;//壁の縁発見し抜ける
                  } else {
                    KTR_1_Turn_right(); delay(Turn_90);
                  }
                }
                digitalWrite(LED2, LOW);
                KTR_1_straight();
              }
            }
          }
        }
      }
    }
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
    KTR_1_brake();
    delay(500);
  } else {
    noTone(BUZZ);
  }

  //HC_SR04テスト
  if (HC_SR04_mm() < 100) {
    if (HC_SR04_test == false) {
      tone(BUZZ, 440, 50); delay(50);
      delay(50);
      HC_SR04_test = true ;
    }
  } else if (HC_SR04_mm() >= 100) {
    HC_SR04_test = false ;
  }
}
