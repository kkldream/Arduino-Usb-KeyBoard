# Arduino-Usb-KeyBoard
透過Arduino模擬鍵盤接口，免驅動，最多同時6鍵按壓。
## 環境：
* [Arduino IDE 1.0.6](arduino-1.0.6-windows.zip) (高版本編譯會失敗)
* Atmega328p (Uno、Nano、Pro mini)，其他未試過
## 材料：
* 68Ω電阻 x2 (沒有68Ω的話，用50~100Ω電阻也行)
* 2.2kΩ電阻 x1 (沒有2.2kΩ的話，用1.5k~2.2k電阻也行)
* USB連接線 x1 (一端是USB口，另一端是電線)
* 3.6V 稽納二極體 x2 (建議選用功耗0.25~0.5w的)
## 設定腳位：
in /libraries/UsbKeyboard/[usbconfig.h](libraries/UsbKeyboard/usbconfig.h)：
|參數|Arduino|<--->|USB|
|:---:|:---:|:---:|:---:|
|USB_CFG_DPLUS_BIT|D2|68Ω|D+|
|USB_CFG_DMINUS_BIT|D4|68Ω|D-|
|USB_CFG_PULLUP_BIT|D5|2.2kΩ|D-|
## 線路圖：
![電路圖](https://image.geek-workshop.com/forum/201206/12/120616mer6qi8i8smt5qs6.gif)
1. 按鍵 pinMode 設為上拉電阻模式，無須外加上拉電阻，低電位觸發。
2. 兩個68Ω的電阻起到限流和保護作用，防止在意外情況下損壞計算機的USB端口或單片機的端口。
3. 2.2kΩ電阻是上拉電阻，用於分辨總線狀態。如果上拉電阻接於D+和+5v端則是高速USB設備，接於D-與+5v端，則是低速設備。此處鍵盤傳輸速率不高，接到D-作爲低速設備即可。
4. D+和D-上的3.6V穩壓二極管D1和D2起到限制數據線上的電平的作用。因爲在USB規範中規定數據線D+和D-上的電平範圍是3.0V至3.6V，而AVR單片機的輸出電平是Vcc。如果單片機的Vcc是5V，在沒有D1和D2的情況下將造成電平不匹配，會造成在很多計算機中無法正確識別出USB設備。如果用戶系統的Vcc在3.0V至3.6V之間，就可以省略這兩個穩壓二極管。從這裏也可以看出用戶系統的Vcc必須高於3V。
## 程式：
只需修改以下：  
in /UsbKeyboard/[UsbKeyboard.ino](UsbKeyboard/UsbKeyboard.ino)：
```c++
// 按鍵數量
#define KeyNum 11
// 設定腳位
const byte KeyPin[KeyNum] = {A5, A4, A3, A2, A1, A0, 13, 12, 11, 7, 8};
// 對應鍵值
const byte KeyCode[KeyNum] = {KEY_D, KEY_F, KEY_J, KEY_K, KEY_G, KEY_H, KEY_B, KEY_Q, KEY_W, KEY_O, KEY_P};
```
主要函式：
```c++
bool keyStroke(byte key);   //發送一個鍵值
bool keyDown(byte key);     //發送按下狀態的鍵值
bool keyUp(byte key);       //發送放開狀態的鍵值
```
## 模擬鍵值：
in /libraries/UsbKeyboard/[UsbKeyboard.h](libraries/UsbKeyboard/UsbKeyboard.h)：
```c++
#define MOD_CONTROL_LEFT    0xE0
#define MOD_SHIFT_LEFT      0xE1
#define MOD_ALT_LEFT        0xE2
/*......(以下省略)......*/
```
幾乎可以模擬所有鍵值，`Power`、`Sleep`、`Pause`似乎不能
## 參考連結：
* [Arduino學習筆記A11 - Arduino模拟電腦鍵盤（基于AVR-USB的USB-HID設備）](https://www.geek-workshop.com/forum.php?mod=viewthread&tid=1137)
* [v-usb for arduino USBKeyboard](http://coopermaa2nd.blogspot.com/2011/10/v-usb-for-arduino-usbkeyboard.html?m=1)