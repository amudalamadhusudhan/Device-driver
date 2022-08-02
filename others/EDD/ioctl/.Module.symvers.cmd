cmd_/home/pi/EDD/ioctl/Module.symvers := sed 's/ko$$/o/' /home/pi/EDD/ioctl/modules.order | scripts/mod/modpost -m -a   -o /home/pi/EDD/ioctl/Module.symvers -e -i Module.symvers   -T -
