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

bool SW1_State = 0;         //プッシュボタンステータスを読み取るための変数

void setup() {
  // LEDピンを出力として初期化します
  pinMode(LED1, OUTPUT);
  //押しボタンピンを入力として初期化します
  pinMode(SW1, INPUT);
}

void loop() {
  //プッシュボタン値の状態を読み取ります
  SW1_State = digitalRead(SW1);

 //押しボタンが押されているかどうかを確認します。
  if (SW1_State == HIGH) {
    // LEDを5回点滅させます。
    for (int i=0; i <= 4; i++){
    digitalWrite(LED1, HIGH);
    delay(250);
    digitalWrite(LED1, LOW);
    delay(250);
   }
  } else {
    // LEDをオフにします：
    digitalWrite(LED1, LOW);
  }
}
