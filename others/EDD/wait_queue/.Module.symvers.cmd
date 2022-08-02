cmd_/home/pi/EDD/wait_queue/Module.symvers := sed 's/ko$$/o/' /home/pi/EDD/wait_queue/modules.order | scripts/mod/modpost -m -a   -o /home/pi/EDD/wait_queue/Module.symvers -e -i Module.symvers   -T -
