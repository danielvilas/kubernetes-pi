# Finishing touches

Install an emqx
```
kubectl apply -f 10_Emqx/00_deploy.yaml
```
Configure auto reboot on Mondays

```
ssh pi@masterpi 
sudo sh -c "echo FSCKFIX=yes >>  /etc/default/rcS"
crontab -e
0 0 * * 1 sudo touch /forcefsck && sudo /sbin/reboot
exit

ssh pi@nodepi1
sudo sh -c "echo FSCKFIX=yes >>  /etc/default/rcS"
crontab -e
15 0 * * 1 sudo touch /forcefsck && sudo /sbin/reboot
exit

ssh pi@nodepi2
sudo sh -c "echo FSCKFIX=yes >>  /etc/default/rcS"
crontab -e
30 0 * * 1 sudo touch /forcefsck && sudo /sbin/reboot
exit

ssh pi@nodepi3
sudo sh -c "echo FSCKFIX=yes >>  /etc/default/rcS"
crontab -e
45 0 * * 1 sudo touch /forcefsck && sudo /sbin/reboot
exit
```