cmd_/home/madhusudhan/Desktop/Device-driver/waitQ/Module.symvers := sed 's/\.ko$$/\.o/' /home/madhusudhan/Desktop/Device-driver/waitQ/modules.order | scripts/mod/modpost -m -a  -o /home/madhusudhan/Desktop/Device-driver/waitQ/Module.symvers -e -i Module.symvers   -T -