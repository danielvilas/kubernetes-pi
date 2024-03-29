# kubernetes-pi

Simple ansible scripts for install a Kubernetes Cluster in several Raspberry Pi 3b

Based on vanilla guide of https://github.com/alexellis/k8s-on-raspbian   @2018/12/27
NFS based on the https://github.com/carlosedp/kubernetes-arm/tree/master/3-NFS_Storage


## Pre-reqs:

* You must use an RPi 3 or 4 for use with Kubernetes
* I'm assuming you're using wired ethernet (Wi-Fi also works, but it's not recommended)
* all nodes have static ip
* And the locale set
* A dns server is installed and configured to publish the picluster domain
* In all nodes the file /boot/cmdline.txt has the cpuset line
```
cgroup_enable=cpuset cgroup_memory=1 cgroup_enable=memory
```

For this tutorial the ips and machines are:
```
Router -> 192.168.1.1 -> (gateway)
Manager -> 192.168.1.2 -> serverpi.local (a linux server), serverpi.kubemaster
Master -> 192.168.1.10 -> masterpi.local, kubemaster.picluster 
Node1  -> 192.168.1.11 -> nodepi1.local, kubenode1.picluster
Node2  -> 192.168.1.12 -> nodepi2.local, kubenode2.picluster
```
Edit inventory file (hosts) as needed

You can install the coreDns with
```
ansible-playbook -u pi -i hosts -l server coredns.yml
```
## Install Kubernetes
```
#Configure the hosts
ansible-playbook -i hosts -u pi 00_install_deps.yaml

#Create the cluster
ansible-playbook -i hosts -u pi 01_init_master.yaml
#Use the output to fill the parameters
ansible-playbook -i hosts -u pi -e token="tokenparam" -e caCertHash="certHashParam" 02_init_nodes.yaml 

#Complete the cluster deployment
ansible-playbook -i hosts -u pi 03_basic_init.yaml

#Wait until daemons reloads and install services
ansible-playbook -i hosts -u pi 04_deploy_traefik.yaml
ansible-playbook -i hosts -u pi 05_deploy_dashboard.yaml
ansible-playbook -i hosts -u pi 06_deploy_storage.yaml
ansible-playbook -i hosts -u pi 07_deploy_heapster.yaml

#Optional, enable master as scheludable node
kubectl taint nodes --all node-role.kubernetes.io/master-

#Configure Hat
kubectl label nodes nodepi1 UpsHat=yes
kubectl label nodes nodepi2 UpsHat=yes
kubectl apply -f 08_I2CBatery/01_deploy.yaml

#update
sudo rpi-update
sudo update-alternatives --set iptables /usr/sbin/iptables-legacy
sudo update-alternatives --set ip6tables /usr/sbin/ip6tables-legacy
sudo reboot


```


