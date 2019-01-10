# UPS Hat continous monitoring

This directory contains an program to monitor the UPS HAT and publish the data (Voltage and Capacity) to the influx DB for Monitoring Kubernetes.

Need to have installed the influx db with heapster from "https://github.com/danielvilas/kubernetes-pi" the image needs three environmental variables: MONITORING_INFLUXDB_SERVICE_HOST MONITORING_INFLUXDB_SERVICE_PORT MY_NODE_NAME

InfluxDB variables are instantited by Kubernetes, and MY_NODE_NAME injected on the Template, see https://github.com/danielvilas/kubernetes-pi/blob/master/08_I2CBatery/01_deploy.yaml

This program is based on the official code from http://www.raspberrypiwiki.com/images/d/d7/Ups-hat-c.zip

build.yaml contains the steps to compile, create the image and push to the docker hub repository. If needed modify the image name with your id. 
to execute:
```
ansible-playbook -i buildhosts -u pi build.yaml
```

Manual Steps:
```
gcc main.c -o ups-hat-influx
docker build -t <repo>/ups-hat-influx:<version> .
docker login <repo>
docker push
```