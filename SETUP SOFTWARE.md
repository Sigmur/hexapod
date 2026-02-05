# SOFTWARE & SYSTEM SETUP

## 1) Hardware
Overall, i spent ~30€ on the whole thing, shipping included.

- **Raspberry pi Zero** | ~20€<br>
    I used an old 1.1 with a BCM2835 (32bits 1core 1GhZ) & 512MB of ram.<br>
    New ones (Pi Zero 2) retails for ~20€ & have a BCM2710A1 64bits with 4 cores 1GhZ & roughly 30/40% faster than the one i'm using.<br>
    A good alternative can be an Orange Pi Zero 2, better processor , wifi & USB-C for roughly the same price (~23/25€)
- **8+ Go SD card** | ~10€<br>
    Got a new sandisk 64go for 10€, i'd advise to get a reliable branded one for fast transfer speed & reliability

**(optionals)**<br>
Even tho you can setup the OS with auto wifi connection, it's good to have a backup plan when the thing doesn't want to connect anymore<br>
- **female to female USB A adapter** | ~1€<br>
    Make your own micro USB to USB-A adapter ! : 
    - micro USB to USB-A cable (you probably have 10 laying around)
    - female to female USB-A
    - USB-A Keyboard
- **USB-C to USB-A adapter** | 1€<br>
    Same thing as the one above, if you chose to go the Orange Pi route
- **mini HDMI to HDMI adapter** | ~2€<br>
    Grab a straight, regular one. Don't be like me and get stuck with a weird one that do a 90° corner right in front of the USB ports

## 2) OS Image setup

### Raspberry Pi Zero :
First we need to install the OS on the SD card, grab the Raspberry Pi imager at : <br>
https://www.raspberrypi.com/software/<br>
Then, run the thing  : 
- **Device** : Select the correct device, Pi Zero or Pi Zero 2 in our case
- **OS** : Raspberry Pi OS (other) > Raspberry Pi OS Lite<br> No GUI and somewhat lighter with all the regular stuff we need. There are "better" options but this is quick and easy and will work out of the box.
- **Storage** : Select your SD card, it'll be wiped so be careful.
- **Customization**
  - **Hostname** : "Sigpod", that's mine, you do you. That's what you'll be looking for in your LAN to get the ip adress once it's connected.
  - **Localisation** : Fill as you want
  - **User** : Setup a default user with password ofc
  - **Wi-Fi** : Important part, setup a Wifi network so the thing will auto connect once installed.
  - **Remote access** : Enable SSH, password or key if you feel like it, you'll need this to access your Pi over Wifi without a keyboard or mouse
  - **Raspberry Pi Connect** : Raspberry's remote connection stuff, i use regular SSH so i won't bother with that.
- **The rest is just writing and validating the image**<br>

### Orange Pi - Dietpi :<br>
http://www.orangepi.org/orangepiwiki/index.php/Orange_Pi_Zero_2W#Download_the_development_board_image_and_related_information<br>

I used dietpi, i wanted a very light image with no GUI<br>
Flashed the SD card using Balena Etcher<br>
After flashing, a new folder will be available, edit the various config files to add wifi access<br>
In dietpi.txt : <br>
```
AUTO_SETUP_NET_ETHERNET_ENABLED=0
AUTO_SETUP_NET_WIFI_ENABLED=1
AUTO_SETUP_NET_HOSTNAME=Sigpod
CONFIG_SERIAL_CONSOLE_ENABLE=0
```
In dietpiEnv.txt : `overlays=i2c0`<br>
in dietpi-wifi.txt : fill your wifi infos in these fields<br>
```
aWIFI_SSID[0]
aWIFI_KEY[0]
```

YOU'LL NEED A KEYBOARD AND SCREEN TO FINISH THE SETUP<br>
At one point you can select software to be installed, look in the list and add WiringPi
If it asks, disable the Serial UART port, apparently this can conflict with I2C and other stuff in the GPIO
Last thing, 

### Orange Pi - OrangePi OS (arch)
sudo pacman -S git
sudo pacman -S g++
sudo pacman -S i2c-tools

## 3) First boot and remote access

- Plug the SD card in the Pi.
- Turn it on, won't work if you don't.
- Wait, be patient, grab a drink, plug a monitor if you really want to know what's going on.
- After a while, the setup will be done and it'll be connected to the Wifi if you didn't fumble when typing the long ass password.
- Now you need to find the IP adress of the Pi :
  - **If you have a screen pluged in** : it'll be showed in the post boot message
  - **If you have some kind of admin interface for your router** : You'll probably have a list of connected devices, find the hostname you specified earlier and voila.<br>While you're at it, if you're in the box admin panel add a domain that link to your Pi in the DNS settings, something like "hexapod.local". This way you can use this instead of the full IP.
- Now in a command line, try `ssh username@you.ip.addr.here`<br>ex :
  `ssh sigmur@hexapod.local` | `ssh sigmur@192.168.1.32`<br>
  If it's asking you for your password, you won.

## 4) System setup

Connet to the Pi using SSH

### 4.1) Generic regular housekeeping :
<code>
sudo apt-get update<br>
sudo apt-get upgrade<br>
sudo apt-get install git<br>
sudo apt-get install g++<br>
sudo apt-get install i2c-tools<br>
reboot
</code>

### 4.2) Libraries :

#### WiringPi - GPIO
**For Raspberry pi only**<br>
https://github.com/WiringPi/WiringPi

<code>
cd<br>
git clone https://github.com/WiringPi/WiringPi.git<br>
./build debian<br>
mv debian-template/*.deb .<br>
sudo apt install ./wiringpi_*.deb
</code>

#### WiringOP - GPIO
**For OrangePi Only**<br>
https://github.com/Sigmur/wiringOP.git

<code>
cd<br>
git clone https://github.com/Sigmur/wiringOP.git
cd wiringOP
sudo ./build clean
sudo ./build
</code>
<br>
I had to fork the base WiringOP from https://github.com/orangepi-xunlong/wiringOP
There is one little bug the original this implementation : as per the PCE9685 documentation, i init the PCA board on a high pin number : 100, then use `pwmWrite` on 100, 101, etc... one for each of the 12 servo you can drive with these boards.<br>
Basically the problem is this (@wiringOP/wiringP/wiringP.c:4438) : 
```c++
if (pin < MAX_PIN_NUM) {
    [...]
} else {
    printf("not on board :%s,%d\n", __func__, __LINE__);
    if ((node = wiringPiFindNode(pin)) != NULL) {
    if (wiringPiDebug)
        printf("Jim find node%s,%d\n", __func__, __LINE__);
    node->digitalWrite(node, pin, value);
}
```<br>
 - Each time you call a pin that is outside of the board pin count, it'll prinf `not on board :pwmWrite,4438`, should probably be within a `if (wiringPiDebug)` <br>
 - Then if it finds a node, it does a `digitalWrite` on the node, should be a `pwmWrite`.
Since i'm a coward and can't do a pull request on a stranger's repo to save my life, i just fixed the thing in my little safe corner.<br>
<br>
No shade on the base library, it's fucking great to have something to work with in the first place.

#### PCA9685 - PWM drivers
https://github.com/Reinbert/pca9685

Enable I2C<br>
**raspberry pi**<br>
<code>
sudo raspi-config<br>
 -> Select "Interface Options"<br>
 -> Enable "I2C"<br>
</code>
**Orange pi**<br>
<code>
sudo orangepi-config<br>
 -> Select "System"<br>
 -> Select "Hardware"<br>
 -> Enable "pi-i2c0"<br>
 -> Enable "pi-i2c1"<br>
</code>

Then install the PCA9685 library<br>
<code>
cd<br>
git clone https://github.com/Reinbert/pca9685.git<br>
cd pca9685/src
sudo make install
</code>

#### Lib Eigen 3.4
https://libeigen.gitlab.io/

Used in the kinematics calculations and probably already installed.<br>
`sudo apt install libeigen3-dev`

## 5) Project setup

### 5.1) Cloning the repo
Assuming this repository will be cloned in `/home/youruser`, so `/home/youruser/hexapod`<br>
<code>
cd<br>
git clone https://github.com/Sigmur/hexapod.git
</code>

### 5.2) Building the program

***WIP***<br>
In the project directory just run `make` to build using the included Makefile.<br>
The resulting executable will be in a `bin` folder created by the Makefile. `./bin/hexapod` to run it.