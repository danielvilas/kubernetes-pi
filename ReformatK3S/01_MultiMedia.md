# Multimedia Services on Master Pi

On this step we will install all the services (Amule, mlnet, apache) of our Serverpi. This is my installation and I will recover the services I Use.

# MLDonkey (Mlnet)
We will use amule for BitTorrent downloader. As some Distros uses this to sare the images.
```
#mldonkey
ssh pi@serverpi.local
sudo mkdir /export_amule
sudo sh -c "echo PARTUUID=97709164-03  /export_amule               ext4    defaults,noatime  0       1 >>/etc/fstab"
sudo mount /export_amule/ 

sudo mkdir -p /export_amule/incoming/files/books
sudo scp pi@192.168.1.3:/export_amule/incoming/files/books/* /export_amule/incoming/files/books/. 
sudo mkdir -p /export_amule/incoming/files/keil
sudo scp pi@192.168.1.3:/export_amule/incoming/files/keil/* /export_amule/incoming/files/keil/. 
sudo mkdir -p /export_amule/incoming/files/SWR
sudo scp pi@192.168.1.3:/export_amule/incoming/files/SWR/* /export_amule/incoming/files/SWR/. 

#Clean the other amule Directories
sudo mkdir -p /export_amule/incoming/directories
sudo mkdir -p /export_amule/tmp
sudo mkdir -p /export_amule/torrents/downloads
sudo mkdir -p /export_amule/torrents/incoming
sudo mkdir -p /export_amule/torrents/old
sudo mkdir -p /export_amule/torrents/seeded
sudo mkdir -p /export_amule/torrents/tracked

sudo apt-get install mldonkey-server
sudo chown mldonkey:mldonkey -R /export_amule/incoming/
sudo chown mldonkey:mldonkey -R /export_amule/tmp/
sudo chown mldonkey:mldonkey -R /export_amule/torrents/
cd ~mldonkey/
sudo service mldonkey-server stop
sudo rm -rf incoming
sudo ln -s /export_amule/incoming/ incoming
sudo rm -rf temp
sudo ln -s /export_amule/tmp/ temp
sudo rm -rf torrents
sudo ln -s /export_amule/torrents/ torrents
sudo chown mldonkey:mldonkey -R incoming
sudo chown mldonkey:mldonkey -R temp
sudo chown mldonkey:mldonkey -R torrents

sudo nano users.ini #copy the passwd from the users.ini of oldserver
sudo nano dowloads.ini #copy the cfg from oldsever
exit
```
Configure the rest of the amule trough the Admin Console on http://serverpi.local:4080

## HTTP

Now we copy  folder call "revistas" with Some webpages

```
ssh pi@serverpi.local
sudo apt-get install apache2
cd /var/wwww/html
sudo mkdir revistas
cd revistas
sudo scp -r pi@192.168.1.3:/var/www/html/revistas/* .

cd /export_amule/
sudo ln -s /var/www/html/revistas/ revistas

exit
```

## Minidnla

```
ssh pi@serverpi.local
sudo apt-get install minidlna
#connect USB with Pelis
sudo blkid /dev/sda1
sudo mkdir -p /export_amule/Pelis/Pincho
sudo sh -c "echo PARTUUID=fa2cb833-01 /export_amule/Pelis/Pincho ext4 defaults,noatime 0 1 >> /etc/fstab"
sudo mount /export_amule/Pelis/Pincho
sudo chown -R minidlna:minidlna /export_amule/Pelis/
cd /etc
sudo cp minidlna.conf minidlna.conf.bak
sudo scp pi@192.168.1.3:/etc/minidlna.conf .
sudo service minidlna restart
exit
```

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
```