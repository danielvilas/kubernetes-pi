# K3S install

## Pre-Requisites
* Download this repo `git clone https://github.com/danielvilas/kubernetes-pi/`
* Be in the masterpi folder `cd kubernetes-pi/k3s`
* Have an SSH key generated `ssh-keygen`


## K3S -requisities

As required by [K3S on Raspberry Pi](https://docs.k3s.io/advanced#raspberry-pi) we need to modify the boot.cmd for tha we will use the 
rpi_boot_config role

```
# Check the ping
ansible -i ../hosts all -m ping
ansible-playbook -i ../hosts 00_reqs.yaml


```

## Install on the master
```
sh 01_launch-k3s.sh
```

## Distribute KubeConfig
```
ssh masterpi.local
scp $USER@masterpi.local:./.kube/config k3s.config
kubectl --kubeconfig=k3s.config get nodes
```

## Install DashBoard
```

ansible-playbook -i ../hosts 02_InstallHelm.yaml
ansible-playbook -i ../hosts 03_certmanager.yaml
ansible-playbook -i ../hosts 04_clusterca.yaml
ansible-playbook -i ../hosts 05_dashboard.yaml

```