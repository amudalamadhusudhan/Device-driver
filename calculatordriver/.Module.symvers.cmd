cmd_/home/madhusudhan/Desktop/Device-driver/calculatordriver/Module.symvers := sed 's/\.ko$$/\.o/' /home/madhusudhan/Desktop/Device-driver/calculatordriver/modules.order | scripts/mod/modpost -m -a  -o /home/madhusudhan/Desktop/Device-driver/calculatordriver/Module.symvers -e -i Module.symvers   -T -
