# Monitoring
Now is time to add an influx to monitore the batteries.

## Influx & Grafana
```
kubectl apply -f 07_Heapster/00_InfluxDB.yaml -n kube-system
kubectl apply -f 09_grafana/grafana.yaml -n kube-system
```

At this point got an network error, update the legacy (should be first steps)
```
ssh pi@masterpi.local sudo update-alternatives --set iptables /usr/sbin/iptables-legacy
ssh pi@masterpi.local sudo update-alternatives --set ip6tables /usr/sbin/ip6tables-legacy
ssh pi@masterpi.local sudo reboot 

ssh pi@nodepi1.local sudo update-alternatives --set iptables /usr/sbin/iptables-legacy ; \
ssh pi@nodepi1.local sudo update-alternatives --set ip6tables /usr/sbin/ip6tables-legacy ; \
ssh pi@nodepi1.local sudo reboot 

ssh pi@nodepi2.local sudo update-alternatives --set iptables /usr/sbin/iptables-legacy ; \
ssh pi@nodepi2.local sudo update-alternatives --set ip6tables /usr/sbin/ip6tables-legacy ; \
ssh pi@nodepi2.local sudo reboot 

ssh pi@nodepi3.local sudo update-alternatives --set iptables /usr/sbin/iptables-legacy ; \
ssh pi@nodepi3.local sudo update-alternatives --set ip6tables /usr/sbin/ip6tables-legacy ; \
ssh pi@nodepi3.local sudo reboot 

```
## Battery Monitor

```
kubectl label nodes nodepi1 UpsHat=yes ;\
kubectl label nodes nodepi2 UpsHat=yes ;\
kubectl label nodes nodepi3 UpsHat=yes ;\
kubectl label nodes masterpi UpsHat=yes ;\
kubectl apply -f 08_I2CBatery/01_deploy.yaml

kubectl get service -n kube-system monitoring-influxdb 
ssh pi@masterpi curl http://[cluser ip from previous]:8086/query -d q="CREATE DATABASE k8s" 
```
Connect to the Grafana on (http://grafana.apps.picluster) and configure the Database (http://monitoring-influx:8086) db k8s
