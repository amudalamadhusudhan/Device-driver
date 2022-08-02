cmd_/home/pi/EDD/sem/Module.symvers := sed 's/ko$$/o/' /home/pi/EDD/sem/modules.order | scripts/mod/modpost -m -a   -o /home/pi/EDD/sem/Module.symvers -e -i Module.symvers   -T -
