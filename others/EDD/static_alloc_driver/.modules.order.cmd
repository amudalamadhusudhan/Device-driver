cmd_/home/pi/EDD/static_alloc_driver/modules.order := {   echo /home/pi/EDD/static_alloc_driver/driver.ko; :; } | awk '!x[$$0]++' - > /home/pi/EDD/static_alloc_driver/modules.order
