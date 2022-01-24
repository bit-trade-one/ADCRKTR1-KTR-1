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

int VRvol = 0;  // センサーからの値を格納する変数

void setup() {
  //ブザーピンを入力として初期化します
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(LED1, OUTPUT);
  //アナログ入力ピンは宣言しなくても入力できる
}

void loop() {
  VRvol = analogRead(VR);    // アナログピンを読み取る
  VRvol = map(VRvol, 0, 1023, 220, 880); //値を丸める
  if (digitalRead(SW1) == HIGH) {
    tone(BUZZ, VRvol); 
  } else if (digitalRead(SW2) == HIGH) {
    // BUZZをオフにします：
    for (int i = VRvol; i >= 150; i--) {
      tone(BUZZ, i, 10); delay(10);
    }
  } else {
    noTone(BUZZ);
  }
}
