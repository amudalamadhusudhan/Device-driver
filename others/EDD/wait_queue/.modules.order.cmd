cmd_/home/pi/EDD/wait_queue/modules.order := {   echo /home/pi/EDD/wait_queue/driver.ko; :; } | awk '!x[$$0]++' - > /home/pi/EDD/wait_queue/modules.order
