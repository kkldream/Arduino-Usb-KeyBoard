# Arduino-Usb-KeyBoard
### 使用環境、材料：
* Arduino 1.0.6
* 68Ω電阻 x2 (沒有68Ω的話，用50~100Ω電阻也行)
* 2.2kΩ電阻 x1 (沒有2.2kΩ的話，用1.5k~2.2k電阻也行)
* USB連接線（一端是USB口，另一端是電線）x1
* 3.6v 穩壓管（建議選用功耗0.25~0.5w的）x2

### usbconfig.h：
|Arduino|USB|
|---|---|
|USB_CFG_DPLUS_BIT：D2|D+|
|USB_CFG_DMINUS_BIT：D4|D-|
|USB_CFG_PULLUP_BIT：D5|D-|

### 電路圖：
![電路圖](https://image.geek-workshop.com/forum/201206/12/120616mer6qi8i8smt5qs6.gif)

### 參考連結：
https://www.geek-workshop.com/forum.php?mod=viewthread&tid=1137
http://coopermaa2nd.blogspot.com/2011/10/v-usb-for-arduino-usbkeyboard.html?m=1