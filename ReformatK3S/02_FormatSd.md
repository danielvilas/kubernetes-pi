# Format from scratch

## Create Masterpi 

Serverpi will be the RaspberryPi 3 with the SD of 64GB

```
#in a Mac or another linux
brew install pv
sudo su

diskutil list
# the SD is in disk2
diskutil umountdisk disk2
sudo sh -c "dd if=2020-02-13-raspbian-buster-full.img bs=1024k | pv| dd bs=1024k of=/dev/rdisk2"
touch /Volumes/boot/ssh
diskutil eject disk2

#connect the Rpi and wait, Router gives .46
ssh pi@192.168.1.46
raspberry
passwd
Sudo raspi-config
    change HostName to (masterpi)
    Change Boot to Cli
	Change TZ to Madrid
	change Wifi ES
    Enable ssh
	Enable VNC
	Expand FS
ssh pi@192.168.1.46
sudo nano /etc/dhcpcd.conf #Config to ip .10
sudo reboot
ssh pi@masterpi.local
sudo apt-get update -y
sudo apt-get upgrade -y
sudo apt-get dist-upgrade -y
sudo apt-get autoremove
sudo reboot

```

## Nodepi1
 With USB reader

```
diskutil list
# the SD is in disk2
diskutil umountdisk disk2
sudo sh -c "dd if=2020-02-13-raspbian-buster-full.img bs=1024k | pv| dd bs=1024k of=/dev/rdisk2"

#connect the Rpi and wait, Router gives .42
ssh pi@192.168.1.42
raspberry
ls /boot
passwd
sudo raspi-config
	Change Hostname nodepi1
	Boot Cli
	TZ Madrid
	wifi ES
	SSH yes
	I2C yes
	Expand FS
sudo nano /etc/dhcpcd.conf #ip .11
sudo reboot
ssh pi@nodepi1.local
sudo apt-get update -y
sudo apt-get upgrade -y
sudo apt-get dist-upgrade -y
sudo apt-get autoremove
```

## Nodepi2
 With USB reader

```
diskutil list
# the SD is in disk2
diskutil umountdisk disk2
sudo sh -c "dd if=2020-02-13-raspbian-buster-full.img bs=1024k | pv| dd bs=1024k of=/dev/rdisk2"

#connect the Rpi and wait, Router gives .45
ssh pi@192.168.1.45
raspberry
ls /boot
passwd
Sudo raspi-config
    change HostName to (nodepi2)
    Change Boot to Cli
	Change TZ to Madrid
	change Wifi ES
    Enable ssh
	Enable VNC
	Expand FS
ssh pi@192.168.1.45
sudo nano /etc/dhcpcd.conf #Config to ip .12
sudo reboot
ssh pi@masterpi.local
sudo apt-get update -y
sudo apt-get upgrade -y
sudo apt-get dist-upgrade -y
sudo apt-get autoremove
sudo reboot

```

## Nodepi3
```
diskutil list
# the SD is in disk2
diskutil umountdisk disk2
sudo sh -c "dd if=2020-02-13-raspbian-buster-full.img bs=1024k | pv| dd bs=1024k of=/dev/rdisk2"

#connect the Rpi and wait, Router gives .44
ssh pi@192.168.1.44
raspberry
ls /boot
passwd
Sudo raspi-config
    change HostName to (nodepi2)
    Change Boot to Cli
	Change TZ to Madrid
	change Wifi ES
    Enable ssh
	Enable VNC
	Expand FS
ssh pi@192.168.1.44
sudo nano /etc/dhcpcd.conf #Config to ip .13
sudo reboot
ssh pi@masterpi.local
sudo apt-get update -y
sudo apt-get upgrade -y
sudo apt-get dist-upgrade -y
sudo apt-get autoremove
sudo reboot
```

## Config

Applied CFG of `/etc/dhcpcd.conf`
```
# Example static IP configuration:
interface eth0
static ip_address=192.168.1.2/24
#static ip6_address=fd51:42f8:caae:d92e::ff/64
static routers=192.168.1.1
static domain_name_servers=192.168.1.2 8.8.8.8 
static domain_name=local
static domain_search=local picluster
```
search network

```
for i in {1..254} ;do (ping 192.168.1.$i -c 1 -w 5  >/dev/null && echo "192.168.1.$i" &) ;done
```
Distribute auth Keys

```
ssh serverpi.local
scp -r .ssh pi@masterpi.local:.ssh
scp -r .ssh pi@nodepi1.local:.ssh
scp -r .ssh pi@nodepi2.local:.ssh
scp -r .ssh pi@nodepi3.local:.ssh
```