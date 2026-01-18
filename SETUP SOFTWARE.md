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

### Orange Pi :<br>
http://www.orangepi.org/orangepiwiki/index.php/Orange_Pi_Zero_2W#Download_the_development_board_image_and_related_information<br>
**Todo when it arrives in the mail**

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
reboot
</code>

### 4.2) Libraries :

#### WiringP - GPIO
https://github.com/WiringPi/WiringPi

<code>
cd<br>
git clone https://github.com/WiringPi/WiringPi.git<br>
./build debian<br>
mv debian-template/*.deb .<br>
sudo apt install ./wiringpi_*.deb
</code>

#### PCA9685 - PWM drivers
https://github.com/Reinbert/pca9685

First, enable I2C<br>
<code>
sudo raspi-config<br>
 -> Select "Interface Options"<br>
 -> Enable "I2C"<br>
</code>

Then install the PCA9685 library<br>
<code>
cd<br>
git clone https://github.com/Reinbert/pca9685.git<br>
cd pca9685/src
sudo make install
</code>

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