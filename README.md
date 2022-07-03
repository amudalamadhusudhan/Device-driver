# Device-driver

steps to access Raspberrypi
Steps to flash Raspbian OS onto sd card:

On Host(ubuntu) :

 Open terminal

     $snap install rpi-imager

     $rpi-imager

  Choose OS :  Raspberry Pi OS (other) => raspberry pi OS LITE 32-bit
     Choose storage : choose your sd card
     Open settings enable ssh and wlan provide details of hotspot
     Click on write and then click on yes - This will take some time.

 After completing flashing image plug out sd card and insert sd card again.

     cd /media/<user-name>/rootfs
     cd etc/wpa_supplicant/
     sudo vim wpa_supplicant.conf

  write the file below code wpa_supplicant.conf save it
     $cd /media/<user-name>/boot

     $touch ssh

     $touch wpa_supplicant.conf

     $vim wpa_supplicant.conf

    Write the following code in wpa_supplicant.conf file and save it.

          country=IN
           ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
           network={
                    ssid="OnePlus"
                    psk="123456789"
                    key_mgmt=WPA-PSK
                    }
Plug out the SD card and insert into your raspberry pi board.
Board will start booting
both laptop and mobile has to be connect to same network to acess the ip adreess
after compition of booting api connect to your wifi check your hotpot device manager
open angry ip scanner scan 192.168.154.0 to 255 you can find rasberripi ip address copy it

open terminal of rpi

 $ssh pi@ip addess
 enter password of rpi

 $sudo raspi-config ,
 Open interface enable ssh and vnc
install vnc for linux open it enter ip adress you can access the remote display

# Corss Compiler & Kernel Environment for rpi4
Steps for cross compiling Kernel :
On Host(Ubuntu) :
Install Required dependencies :

sudo apt install git bc bison flex libssl-dev make libc6-dev libncurses5-dev
Install 32-bit Toolchain :

sudo apt install crossbuild-essential-armhf
Download / clone Kernel source

mkdir rpi
cd rpi
git clone --depth=1 --branch rpi-5.15.y https://github.com/raspberrypi/linux
cd linux
Apply the config file of rpi4 :

Check config file for your board(rpi4) using below command.
ls arch/arm/configs
Default config file for rpi4 is bcm2711_defconfig.
Now apply config file using below command.
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2711_defconfig
Build Kernel image & Kernel modules for rpi4 :

make -j8 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules
Result of above command :
ls arch/arm/boot
Zimage  # This is the result.
Plug in your SD Card to your HOST PC(Ubuntu) :

cp arch/arm/boot/zImage /media/<user_name of your PC>/boot
Install modules onto rootfs partition (or "/") of SD Card

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=<path-to-sdcard-rootfs-partition> modules_install

sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- modules_install  # It will install 5.15.45-v7l+ into "ls /lib/modules"
Example in my PC :
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=/media/madhusudhan/rootfs modules_install
Modules get install in rootfs/lib/modules path.
Configuring config.txt to boot our new Kernel.

cd /media/<user-name>/boot
Open config.txt :
vim config.txt
Add below line at the end of the file and save file.
kernel=zImage
if ssh & "wpa_supplicant.conf" files are not in your boot partition then follow steps-2 of flashing raspbian OS.

Plug out your SD Card and insert into your Raspberry pi board.

Board will start booting and access it trough ssh pi@ipadress

# module

linux:~$make

linux:~$sudo -s

linux:~#insmod hello.ko

linux:~#dmesg

linux:~#lsmod

linux:~#rmmod hello
 
device file creation-> sudo  mknod 777 -m /dev/drivername c majorno minorno 

![Screenshot from 2022-06-24 19-17-36](https://user-images.githubusercontent.com/105910992/175550909-ab254f2c-78b6-4d3e-b500-37240ce13cd9.png)
![Screenshot from 2022-06-25 19-39-23](https://user-images.githubusercontent.com/105910992/175831863-79ac4834-1f7f-4ba4-a434-ab2ac712fa90.png)
# calc driver
![Screenshot from 2022-07-02 00-01-29](https://user-images.githubusercontent.com/105910992/176952863-c8f266e3-1f0c-4736-a16e-e4edc82424f2.png)
# char driver
 ![Screenshot from 2022-06-25 19-38-07](https://user-images.githubusercontent.com/105910992/176953098-cd718cdc-9aed-40cb-8caa-f84e425bfda7.png)

 
