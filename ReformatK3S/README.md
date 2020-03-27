# Reformat to K3S
A new RPi 4 wiht 4GBRAM comes to the family and it is time to update all the system


The machines will be:

| Node 	    | Model 	    | IP 	        | names(local) 	| names(picluster)      | Functions                             	|
|------     |------         |----	        |-------	    |-----------	        |-----------                                |
|Router   	|ISP Brand     	|192.168.1.1   	|gw.local      	|gw.picluster          	|Router, DHCP, DNS, NAT                     |
|Manager    |Rpi 4 +128GB   |192.168.1.2  	|serverpi.local |kubemaster.picluster   |CoreDns, Ssh Server, Amule, mlnet, apache  |
|Master     |Rpi 3 +64GB    |192.168.1.10  	|masterpi.local |kubemaster.picluster   |Kubelet master, UPS_HAT 1.1, glusterfsd    |
|Node1      |Rpi 3 +32GB    |192.168.1.11  	|nodepi1.local  |kubenode1.picluster    |Kubelet Node, UPS_HAT 1.1, glusterfsd      |
|Node2      |Rpi 3 +32GB    |192.168.1.12  	|nodepi2.local  |kubenode2.picluster    |Kubelet Node, UPS_HAT 1.0, glusterfsd      |
|Node3      |Rpi 3 +32GB    |192.168.1.13  	|nodepi3.local  |kubenode3.picluster    |Kubelet Node, UPS_HAT 1.0, glusterfsd      |

Additionally the `*.apps.picluster` DNS will be appointed to `Node1`, `Node2` & `Node3`. And the ingress service will be published as well on those IPs. 


Steps
*  [Create ServerPi](00_ServerPi.md) from Old ServerPi that will be the Master Node
*  [Recover Multimedia Services](01_MultiMedia.md) from Old ServerPi to serverPi
*  [Create SD for Cluster](02_FormatSd.md) from Old ServerPi to serverPi
*  [Install K3S](02_k3s.md) from Old ServerPi to serverPi
