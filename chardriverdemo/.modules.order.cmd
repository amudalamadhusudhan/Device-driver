cmd_/home/madhusudhan/Desktop/Device-driver/chardriver/modules.order := {   echo /home/madhusudhan/Desktop/Device-driver/chardriver/chardriver.ko;   echo /home/madhusudhan/Desktop/Device-driver/chardriver/dynamicchar.ko; :; } | awk '!x[$$0]++' - > /home/madhusudhan/Desktop/Device-driver/chardriver/modules.order