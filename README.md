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
open terminal-> $ ssh pi@ip addess
enter password of rpi
In rpi terminal->$ sudo raspi-config
Open interface enable ssh and vnc
install vnc for linux open it enter ip adress you can access the remote display

# module

![Screenshot from 2022-06-24 19-17-36](https://user-images.githubusercontent.com/105910992/175550909-ab254f2c-78b6-4d3e-b500-37240ce13cd9.png)
![Screenshot from 2022-06-24 19-18-31](https://user-images.githubusercontent.com/105910992/175550954-cbc4e2de-bb55-424c-990e-3d50e9f63d9b.png)
![Screenshot from 2022-06-24 19-18-41](https://user-images.githubusercontent.com/105910992/175550982-ad3f78d0-b37a-4bbc-9125-8609c5c61cf6.png)
