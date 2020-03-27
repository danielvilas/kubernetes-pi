# Format from scratch

## Create Serverpi 

Serverpi will be the RaspberryPi 4 (4GB) with the SD of 128GB

First create Server Pi and partition the SD to 64GB root + 64 GB the export_amule
```
#in a Mac or another linux
brew install pv
sudo su

diskutil list
# the SD is in disk1
diskutil umountdisk disk2
sudo dd if=2020-02-13-raspbian-buster-full.img bs=1024k | pv| dd bs=1024k of=/dev/rdisk2
touch /Volumes/boot/ssh
diskutil eject disk2

# in this case used the old Serverpi (Rpi3 + 64GB SD)
ssh serverpi.local
sudo parted /dev/sdb
	print
	resizepart 2 64GB
	mkpart p ext4 64.0GB 128GB  
	quit
sync
sudo resize2fs /dev/sdb2
sudo mkfs.ext4 /dev/sdb3
Sudo umount /dev/sdb1
Sudo umount /dev/sdb2
Sudo umount /dev/sdb3
exit
#agin on the mac
#connect the Rpi4 and wait, Router gives .39
ssh pi@192.168.1.39
raspberry
passwd
Sudo raspi-config
        change HostName to (serverpi)
        Change Boot to Cli
	Change TZ to Madrid
        Enable ssh
	Enable VNC
	WifiCountry Es
	reboot no

sudo nano /etc/dhcpcd.conf #Config to ip .2
exit #host mac
```
In another Console change Serverpi to serverold
```
Ssh 192.168.1.2
Sudo raspi-config
	Change HostName to serverold
sudo nano /etc/dhcpcd.conf #ip .3
Sudo reboot
#host mac
``` 
At this point the old ServerPi is in the .3 with the name serverold.
``` 
ssh pi@192.168.1.39
Sudo reboot
#host mac 
Rm ~/.ssh/known_hosts 
Ssh pi@192.168.1.2
sudo apt-get update -y
sudo apt-get dist-upgrade -y
sudo apt-get upgrade -y
sudo apt autoremove -y
exit
```
## coredns
The next point is to install the core DNS
```
Ssh pi@192.168.1.2
wget https://github.com/coredns/coredns/releases/download/v1.6.7/coredns_1.6.7_linux_arm.tgz
scp pi@192.168.1.3:/export_amule/Pelis/Backup/coredns.tar.gz .
scp pi@192.168.1.3:/etc/systemd/system/coredns.service .
sudo mkdir /etc/coredns
cd /etc/coredns
sudo tar -xvzf ~/coredns.tar.gz
cd
sudo cp coredns.service /etc/systemd/system/coredns.service 
cd /usr/bin
sudo cd /usr/bin
cd /usr/bin
sudo tar -xvzf ~/coredns_1.6.7_linux_arm.tgz 
sudo systemctl daemon-reload 
sudo service coredns start
sudo systemctl enable coredns
Exit
Ping grafana.apps.picluster
```

Wiht those steps we have the Serverpi Running, and the Old serverpi still running in another IP/DNS

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