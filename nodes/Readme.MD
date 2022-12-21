# Creation of Masterpi and the rest of the nodes
MasterPi is the node that will run K3S 
NodePi1, NodePi2, NodePi3, will be workers of the cluster

The process must be repeted for all the nodes, changing the name and the IP

## Pre-Requisites
* Download this repo `git clone https://github.com/danielvilas/kubernetes-pi/`
* Be in the masterpi folder `cd kubernetes-pi/masterpi`
* Have an SSH key generated `ssh-keygen`

## 1.- Install newer image on Debian

Change /dev/sdb for your current device

```
sudo apt install pv
# Download
curl https://downloads.raspberrypi.org/raspios_lite_arm64/images/raspios_lite_arm64-2022-09-26/2022-09-22-raspios-bullseye-arm64-lite.img.xz -o 2022-09-22-raspios-bullseye-arm64-lite.img.xz
xz -d 2022-09-22-raspios-bullseye-arm64-lite.img.xz
# Or get from serverpi
# mv ../serverpi/2022-09-22-raspios-bullseye-arm64-lite.img .

sudo ../shared/writeImage.sh 2022-09-22-raspios-bullseye-arm64-lite.img /dev/sdb masterpi  $USER raspberry
#sudo ../shared/writeImage.sh 2022-09-22-raspios-bullseye-arm64-lite.img /dev/sdb nodepi1  $USER raspberry
#sudo ../shared/writeImage.sh 2022-09-22-raspios-bullseye-arm64-lite.img /dev/sdb nodepi2  $USER raspberry
#sudo ../shared/writeImage.sh 2022-09-22-raspios-bullseye-arm64-lite.img /dev/sdb nodepi3  $USER raspberry

```
The ẁriteImage.sh` script will dump the image to the SD, repartion the SD to 32GB and create the bootfiles to start with a new user, with the same user as the current one.

## 2.- Configure the new machine
Launch on the pi and connect to do the configuration. The writeimage creates an user wiht the same of the current one and password "raspberry".
```
ssh-keygen -f "/home/$USER/.ssh/known_hosts" -R "raspberrypi.local"
ssh raspberrypi.local 
#inside the raspi configure de password and the pi with raspi-config
passwd
sudo raspi-config
    System
        change HostName to (masterpi, nodepi1,... as )
        Change Boot to Cli
    Interface
        Enable ssh
    Locale
        TimeZone Europe/Madrid
	    WifiCountry Es
	reboot no
sudo nano /etc/dhcpcd.conf #Config to ip .10 (11, 12, 13,..)
#reboot once configured

```

## 3.- Distribute ssh key

From your machine (with a SSH Key, generated)
```
../shared/distributeKey.sh masterpi
#../shared/distributeKey.sh nodepi1
#../shared/distributeKey.sh nodepi2
#../shared/distributeKey.sh nodepi3
```

## 4.- Repeat for workers

Repeat steps 1 to 3 for the 3 worker nodes, changing the name and ip for each node

## 5.- Update  all with ansible

```
ansible-playbook -i ../hosts 00_update.yaml

```




## Example static IP configuration:
```
interface eth0
static ip_address=192.168.1.2/24
#static ip6_address=fd51:42f8:caae:d92e::ff/64
static routers=192.168.1.1
static domain_name=local
static domain_search=local picluster
static domain_name_servers=192.168.1.2 8.8.8.8 8.8.4.4
```