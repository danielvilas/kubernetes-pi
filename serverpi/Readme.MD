# Creation
After a Failed SD on serverPi, Updated a new clean install with full update (lite version, are servers)

Meanwhile, serverpi was installed on other rpi (quick access backup) and renamed from serverpi.local to serverpi-old.local.
Also the ip was changed to 192.168.1.3 'sudo nano /etc/dhcpcd.conf'

## Pre-Requisites

* Download this repo `git clone https://github.com/danielvilas/kubernetes-pi/`
* Be in the serverpi folder `cd kubernetes-pi/serverpi`

## Install newer image on Debian

Change /dev/sdb for your current device

```
sudo apt install pv
curl https://downloads.raspberrypi.org/raspios_lite_arm64/images/raspios_lite_arm64-2022-09-26/2022-09-22-raspios-bullseye-arm64-lite.img.xz -o 2022-09-22-raspios-bullseye-arm64-lite.img.xz

xz -d 2022-09-22-raspios-bullseye-arm64-lite.img.xz

sudo ../shared/writeImage.sh 2022-09-22-raspios-bullseye-arm64-lite.img /dev/sdb serverpi  $USER raspberry

sudo parted /dev/sdb "resizepart 2 64GB"
sudo e2fsck -f /dev/sdb2
sudo resize2fs /dev/sdb2
sudo e2fsck -f /dev/sdb2

```
The ẁriteImage.sh` script will dump the image to the SD, repartion the SD to 32GB and create the bootfiles to start with a new user, with the same user as the current one.

## Configure the new machine
Launch on the pi and connect to do the configuration. The writeimage creates an user wiht the same of the current one and password "raspberry".
```
ssh-keygen -f "/home/$USER/.ssh/known_hosts" -R "raspberrypi.local"
ssh raspberrypi.local 
#inside the raspi configure de password and the pi with raspi-config
passwd
sudo raspi-config
    System
        change HostName to (serverpi)
        Change Boot to Cli
    Interface
        Enable ssh
    Locale
        TimeZone Europe/Madrid
	    WifiCountry Es
	reboot no
sudo nano /etc/dhcpcd.conf #Config to ip .2
#reboot once configured
ssh-keygen -f "/home/$USER/.ssh/known_hosts" -R "serverpi.local"
ssh pi@serverpi.local
sudo apt update -y
sudo apt upgrade -y
sudo apt dist-upgrade -y
sudo apt full-upgrade -y
sudo apt autoremove
sudo reboot
```

## Create a SSH Key and distribute
```
# on your machine with this repo downoladed

# Generate a ssh key and store it as authorized.key
ssh-keygen
scp ~/.ssh/id_rsa.pub serverpi.local:.
ssh serverpi.local "sh -c 'mkdir -p .ssh && cat id_rsa.pub>.ssh/authorized_keys'"

# Distribute private and Test, don't need pwd
scp ~/.ssh/id_rsa serverpi.local:./.ssh

scp ~/.ssh/authorized_keys pi@serverpi-old.local:./.ssh/authorized_keys
```

## Install CoreDNS

Only execute the ansible playbook
```
ansible-playbook -i ../hosts -l server coredns.yml

ssh serverpi.local dig picluster
ping grafana.apps.picluster
```

## Http Server
The actual contents have been not used in a long time, will backup and copied to the pi user

This is a personal service, already backup on pi@serverpi-old:./html
```
ssh pi@serverpi.local
scp -r pi@192.168.1.3:./html .

```

## Amule
The amule is not currently in use. Forget and install it via podman when needed.
## MiniDNLA
With Stream Services is no longer needed. Forget and install it via podman when needed.

## Common User
Optionally, create a basic User `daniel` and copy .ssh config for autologin

```
ssh pi@serverpi.local
sudo su
adduser daniel
exit
sudo usermod daniel -G sudo
exit
ssh daniel@serverpi.local
scp -r daniel@192.168.1.3:.ssh .

## Example of /etc/dhcpcd.conf
Applied CFG of `/etc/dhcpcd.conf`
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