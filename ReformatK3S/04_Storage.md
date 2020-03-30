# Install a GlusterFS as Storage
As Shared Storage we gona use an GlusterFS Storage

## Servers

```
ssh pi@masterpi sudo apt-get install glusterfs-server -y
ssh pi@nodepi1 sudo apt-get install glusterfs-server -y
ssh pi@nodepi2 sudo apt-get install glusterfs-server -y
ssh pi@nodepi3 sudo apt-get install glusterfs-server -y

ssh pi@masterpi sudo systemctl enable glusterd
ssh pi@nodepi1 sudo systemctl enable glusterd
ssh pi@nodepi2 sudo systemctl enable glusterd
ssh pi@nodepi3 sudo systemctl enable glusterd

ssh pi@masterpi sudo systemctl disable dphys-swapfile.service
ssh pi@nodepi1 sudo systemctl disable dphys-swapfile.service 
ssh pi@nodepi2 sudo systemctl disable dphys-swapfile.service 
ssh pi@nodepi3 sudo systemctl disable dphys-swapfile.service

ssh pi@masterpi sudo reboot 
ssh pi@nodepi1 sudo reboot 
ssh pi@nodepi2 sudo reboot 
ssh pi@nodepi3 sudo reboot

ssh pi@masterpi sudo mkdir -p /data/brick1/gv_kubesystem ; \
ssh pi@nodepi1 sudo mkdir -p /data/brick1/gv_kubesystem ; \
ssh pi@nodepi2 sudo mkdir -p /data/brick1/gv_kubesystem ; \
ssh pi@nodepi3 sudo mkdir -p /data/brick1/gv_kubesystem
```

## Create the volume
```
ssh pi@masterpi.local
sudo gluster peer probe masterpi.local
sudo gluster peer probe nodepi1.local
sudo gluster peer probe nodepi2.local
sudo gluster peer probe nodepi3.local

sudo gluster volume create gv_kubesystem replica 4 masterpi.local:/data/brick1/gv_kubesystem nodepi1.local:/data/brick1/gv_kubesystem nodepi2.local:/data/brick1/gv_kubesystem nodepi3.local:/data/brick1/gv_kubesystem force
sudo gluster volume start gv_kubesystem
exit
sudo apt-get install glusterfs-client -y
sudo mount -t glusterfs masterpi.local:/gv_kubesystem /mnt
sudo umount /mnt
kubectl apply -f 06_glusterfs/00_glusterfs_ep.json -n kube-system
kubectl apply -f 06_glusterfs/01_glusterfs_service.json -n kube-system
```

## Create the Storage and automount to the cluster
```

ssh pi@masterpi sudo mkdir -p /var/lib/rancher/k3s/storage ; \
ssh pi@nodepi1 sudo mkdir -p /var/lib/rancher/k3s/storage ; \
ssh pi@nodepi2 sudo mkdir -p /var/lib/rancher/k3s/storage ; \
ssh pi@nodepi3 sudo mkdir -p /var/lib/rancher/k3s/storage


ssh pi@masterpi
sudo sh -c "echo masterpi.local:/gv_kubesystem /var/lib/rancher/k3s/storage glusterfs defaults,noatime 0 1 >> /etc/fstab"
sudo mount /var/lib/rancher/k3s/storage
sudo reboot

ssh pi@nodepi1
sudo sh -c "echo nodepi1.local:/gv_kubesystem /var/lib/rancher/k3s/storage glusterfs defaults,_netdev,noauto,x-systemd.automount 0 1 >> /etc/fstab"
sudo mount /var/lib/rancher/k3s/storage
sudo reboot


ssh pi@nodepi2
sudo sh -c "echo nodepi2.local:/gv_kubesystem /var/lib/rancher/k3s/storage glusterfs defaults,_netdev,noauto,x-systemd.automount 0 1 >> /etc/fstab"
sudo mount /var/lib/rancher/k3s/storage
sudo reboot

ssh pi@nodepi3
sudo sh -c "echo nodepi3.local:/gv_kubesystem /var/lib/rancher/k3s/storage glusterfs defaults,_netdev,noauto,x-systemd.automount 0 1 >> /etc/fstab"
mount /var/lib/rancher/k3s/storage
sudo reboot

ssh pi@masterpi sudo mount | grep /var/lib/rancher/k3s/storage
ssh pi@nodepi1 sudo mount | grep /var/lib/rancher/k3s/storage
ssh pi@nodepi2 sudo mount | grep /var/lib/rancher/k3s/storage
ssh pi@nodepi3 sudo mount | grep /var/lib/rancher/k3s/storage

```