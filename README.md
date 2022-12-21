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

## Create the ServerPi node

The manager will be another Rpi, used as "main" server, will provide the CoreDNS server
("external" DNS) and several personal services for home authomation (HTTP, MiniDLNA,...)

See [ServerPi creation](serverpi/Readme.MD).

## Create the MasterPi Node and the rest of the nodes

MasterPi will have the K3S master node
See [Nodes Creation](nodes/Readme.MD)

