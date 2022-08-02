cmd_/home/pi/EDD/sem/modules.order := {   echo /home/pi/EDD/sem/driver.ko; :; } | awk '!x[$$0]++' - > /home/pi/EDD/sem/modules.order
