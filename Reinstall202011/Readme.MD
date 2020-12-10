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

```
curl -sfL https://get.k3s.io | K3S_URL=https://masterpi.local:6443 K3S_TOKEN=K101410b0a0d35b3ed7e43b25291417d1ff7fb8ccf3306d79134c30d091303b22b9::server:56586400927c3c97881bbd44e3fe03b5 sh -
```
