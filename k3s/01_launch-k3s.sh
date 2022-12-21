#!/bin/sh
git clone https://github.com/k3s-io/k3s-ansible

cd k3s-ansible
ansible-playbook -i ../mycluster/hosts.ini site.yml
cd ..
rm -rf k3s-ansible 