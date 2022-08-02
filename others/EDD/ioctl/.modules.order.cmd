cmd_/home/pi/EDD/ioctl/modules.order := {   echo /home/pi/EDD/ioctl/driver.ko; :; } | awk '!x[$$0]++' - > /home/pi/EDD/ioctl/modules.order
