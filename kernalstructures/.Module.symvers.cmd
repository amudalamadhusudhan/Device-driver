cmd_/home/madhusudhan/Desktop/Device-driver/kernalstructures/Module.symvers := sed 's/\.ko$$/\.o/' /home/madhusudhan/Desktop/Device-driver/kernalstructures/modules.order | scripts/mod/modpost -m -a  -o /home/madhusudhan/Desktop/Device-driver/kernalstructures/Module.symvers -e -i Module.symvers   -T -
