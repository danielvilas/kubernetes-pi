# Reinstall
After a Failed SD on serverPi, Updated a new clean install with full update (lite version, are servers)

Meanwhile, serverpi was installed on other rpi (quick access backup) and renamed from serverpi.local to serverpi-old.local.
Also the ip was changed to 192.168.1.3 'sudo nano /etc/dhcpcd.conf'

## Install newer image on Debian
```
sudo apt install pv
curl https://downloads.raspberrypi.org/raspios_lite_arm64/images/raspios_lite_arm64-2022-09-26/2022-09-22-raspios-bullseye-arm64-lite.img.xz -o 2022-09-22-raspios-bullseye-arm64-lite.img.xz

xz -d 2022-09-22-raspios-bullseye-arm64-lite.img.xz
cat /proc/partitions
sudo ./writeImage.sh 2022-09-22-raspios-bullseye-arm64-lite.img /dev/sdb serverpi
```

## Configure the new machine
Launch on the pi and connect to do the configuration. The writeimage creates an user pi password raspberry
```
ssh-keygen -f "/home/$USER/.ssh/known_hosts" -R "raspberrypi.local"
ssh pi@raspberrypi.local 
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

## Install CoreDNS

```
# on your machine with this repo downolad

# Generate a ssh key and store it as authorized.key
ssh-keygen
scp ~/.ssh/id_rsa.pub pi@serverpi.local:.
ssh pi@serverpi.local "sh -c 'mkdir -p .ssh && cat id_rsa.pub>.ssh/authorized_keys'"
# Test don't need pwd
scp ~/.ssh/id_rsa pi@serverpi.local:./.ssh

ansible-playbook -u pi -i hosts -l server coredns.yml

ssh pi@serverpi.local
cd /etc/coredns
scp ~/.ssh/authorized_keys pi@serverpi-old.local:./.ssh/authorized_keys
sudo scp pi@serverpi-old.local:/etc/coredns/Corefile .
sudo scp pi@serverpi-old.local:/etc/coredns/db.local .
sudo scp pi@serverpi-old.local:/etc/coredns/db.picluster .

sudo apt-get install dnsutils
dig picluster
ping grafana.apps.picluster
```

## Http Server
The actual contents have been not used in a long time, will backup and copied to the pi user
```
ssh pi@serverpi-old.local
cd /var/www/html/
sudo tar -cvzf books.tgz books
sudo rm -rf books
cd revistas 

sudo tar -cvzf cles.tgz cles
sudo rm -f cles

sudo tar -cvzf craftsman.tgz craftsman && sudo rm -rf craftsman
sudo tar -cvzf LR.tgz LR && sudo rm -rf LR
sudo tar -cvzf MR.tgz MR && sudo rm -rf MR
sudo tar -cvzf mrr.tgz mrr && sudo rm -rf mrr
sudo tar -cvzf rwm.tgz rwm && sudo rm -rf rwm
sudo tar -cvzf twm.tgz twm && sudo rm -rf twm

exit
ssh pi@serverpi.local 
scp -r pi@192.168.1.3:/var/www/html .

```

## Amule
The amule is not currently in use. Forget and install it via podman when needed.
## MiniDNLA
With Stream Services is no longer needed. Forget and install it via podman when needed.

## Common User
Last, create an stadard User `daniel` and copy .ssh config for autologin

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
# Example static IP configuration:
interface eth0
static ip_address=192.168.1.2/24
#static ip6_address=fd51:42f8:caae:d92e::ff/64
static routers=192.168.1.1
static domain_name=local
static domain_search=local picluster
static domain_name_servers=192.168.1.2 8.8.8.8 8.8.4.4
```