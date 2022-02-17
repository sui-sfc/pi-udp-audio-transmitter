# pi-udp-audio-transmitter
raspberrypi zero wで動作確認済み

初回のみ
```
edit /boot/config.txt:
dtoverlay=dwc2

edit /etc/modules:
dwc2
libcomposite
```
コンパイル設定
```
gcc sender.c -lpulse -lpulse-simple
```
起動方法
```
sudo ./uac1_gadget.sh
python3 sender.py
```
