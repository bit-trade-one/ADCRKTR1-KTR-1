# ADCRKTR1-KTR-1 よくある質問

## Q.KTR-1とArduinoIDEで通信ができなくなってしまいました。
### A.下記に直す手順を示します。
KTR-1本体よりPro Microを外してください。  
GNDとRSTピンをドライバーなどの導体で素早く2回ショートさせてください。  
数秒COMポートが現れるのでそこを指定して  
ArduinoIDEから空のプログラムを書き込んでください。  
失敗した場合GNDとRSTピンを導体でショートさせるところからやり直してください。   
  
【参考】Sparkfunのトラブルシューティングも合わせて御覧ください。  
https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/troubleshooting-and-faq

