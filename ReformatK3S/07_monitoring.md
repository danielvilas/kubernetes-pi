# Monitoring

```
git https://github.com/carlosedp/cluster-monitoring/
cd cluster-monitoring

vi vars.jsonnet
# enable arm-exporter
# enable k3s
# enable traefik
# change ip of master
# chane suffix
# change storage class

make vendor
make

# review yaml
kubectl apply -f manifests/setup/
kubectl apply -f manifests/

```