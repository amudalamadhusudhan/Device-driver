cmd_/home/madhusudhan/Desktop/Device-driver/spinlock/Module.symvers := sed 's/\.ko$$/\.o/' /home/madhusudhan/Desktop/Device-driver/spinlock/modules.order | scripts/mod/modpost -m -a  -o /home/madhusudhan/Desktop/Device-driver/spinlock/Module.symvers -e -i Module.symvers   -T -