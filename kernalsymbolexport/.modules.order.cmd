cmd_/home/madhusudhan/Desktop/Device-driver/kernalsymbolexport/modules.order := {   echo /home/madhusudhan/Desktop/Device-driver/kernalsymbolexport/module2.ko;   echo /home/madhusudhan/Desktop/Device-driver/kernalsymbolexport/export.ko; :; } | awk '!x[$$0]++' - > /home/madhusudhan/Desktop/Device-driver/kernalsymbolexport/modules.order