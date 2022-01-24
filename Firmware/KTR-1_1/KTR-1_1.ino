void setup() {
  pinMode(14, OUTPUT);//LEDが接続されたPINを出力に設定します。
}
void loop() {
  digitalWrite(14, HIGH); //LEDが接続されたPINから５Vを出力します。
  delay(1000);//1秒待機します。
  digitalWrite(14, LOW); //LEDが接続されたPINから０Vを出力します。
  delay(1000);//1秒待機します。
}
