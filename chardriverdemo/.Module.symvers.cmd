cmd_/home/madhusudhan/Desktop/Device-driver/chardriver/Module.symvers := sed 's/\.ko$$/\.o/' /home/madhusudhan/Desktop/Device-driver/chardriver/modules.order | scripts/mod/modpost -m -a  -o /home/madhusudhan/Desktop/Device-driver/chardriver/Module.symvers -e -i Module.symvers   -T -