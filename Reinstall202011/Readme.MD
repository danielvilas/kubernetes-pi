# Reinstall
After a Failed SO Updated a new clean install with full update

## Install newer image on Debian
```
sudo apt install pv
curl https://downloads.raspberrypi.org/raspios_lite_armhf/images/raspios_lite_armhf-2020-08-24/2020-08-20-raspios-buster-armhf-lite.zip -o 2020-08-20-raspios-buster-armhf-lite.zip 

unzip 2020-08-20-raspios-buster-armhf-lite.zip 
cat /proc/partitions
sudo ./writeImage.sh 2020-08-20-raspios-buster-armhf-lite.img /dev/sdb nodepi1
```
A partir de aqui seguir las guias de ReformatKS desde el punto 02_FormatSd.md
