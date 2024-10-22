#include <UsbKeyboard.h>
#define KeyNum 11 // 按鍵數量
const byte KeyPin[KeyNum] = {A5, A4, A3, A2, A1, A0, 13, 12, 11, 7, 8}; // 設定腳位
const byte KeyCode[KeyNum] = {KEY_D, KEY_F, KEY_J, KEY_K, KEY_G, KEY_H, KEY_B, KEY_Q, KEY_W, KEY_O, KEY_P}; // 對應鍵值
byte Key[KeyNum], PastKey[KeyNum], pressNum;
int Time, var;
bool trigger;
void setup() {
  for (var = 0; var < KeyNum; var++) pinMode(KeyPin[var], INPUT_PULLUP); // 所有腳位設定為上拉電阻
  for (var = 0; var < 1000; var++) { // 不加此段開機會機率失敗
    UsbKeyboard.update();
    delay(1);
  }
}
void loop() {
  Time++;
  if (Time > 1000) { // 防止閒置太久導致斷線
    UsbKeyboard.keyUp(KEY_SPACE);
    Time = 0;
  }
  pressNum = 0;
  for (var = 0; var < KeyNum; var++) {
    if (!digitalRead(KeyPin[var]) && pressNum < 6) {
      pressNum++;
      Key[var] = 1;
    }
    else Key[var] = 0;
  }
  trigger = 0;
  for (var = 0; var < KeyNum; var++) if (PastKey[var] != Key[var]) trigger = 1;
  if (trigger) {
    if (pressNum == 6) for (var = 6; var < KeyNum; var++) UsbKeyboard.keyUp(KeyCode[var]);
    for (var = 0; var < KeyNum; var++) {
      if (Key[var]) UsbKeyboard.keyDown(KeyCode[var]);
      else UsbKeyboard.keyUp(KeyCode[var]);
    }
    for (var = 0; var < KeyNum; var++) PastKey[var] = Key[var];
    Time = 0;
  }
}