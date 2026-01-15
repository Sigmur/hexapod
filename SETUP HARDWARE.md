# HARDWARE SETUP

## 1) Hardware list

### Chassis
https://makerworld.com/en/models/1973965-hexapod-spider-robot-with-servo-arduino<br>
The whole print took ~1.5kg of PETG but i overdid some infills, you can achive it for less.
The provided board plate is ~25g

### Computer
- Pi Zero 2, Raspberry or Orange. See "SETUP SOFTWARE.md" for more details

### Power
- 3x 18650 Li-Ion battery
- 3S 12v 20A BMS
- XL4016 Voltage Regulator<br>
    To convert the 12v BMS output to 7.2v for the servos
- Mini360 Buck converter<br>
    To convert the 12v BMS output to 5v for the Pi
### Movement
- MG996R Servo, **180°**
- 6x Servo cable extention, 5/10 cm<br>
    Regular servo cable are too short for the servos at the end of the leg
- 2x PCA9685 servo board<br>
    To drive the 18 servos using I2C
### Misc hardware
- 695 low profile bearings
- ~100 M3 x 6mm bolts
- ~100 M3 x 10mm bolts
- 18650 3x series battery holder<br>
    optional but highly recommended

## 2) Power wiring

***WIP***<br>
### 2.1) BMS
Battery holder is a big help<br>
Wire BMS balance leads accordingly, 0v, 4.2v, 8.4v, 12.6v<br>
On these BMS, + & - terminals are common charge & discharge<br>

### 2.2) Charging & on/off switch
Connect charging board directly on the BMS **+** & **-** terminals<br>

## 3) Logic wiring
***WIP***<br>
