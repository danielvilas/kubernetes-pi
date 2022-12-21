#!/bin/bash

helpUse()
{
    echo $0 server
}

if [[ -z $1 ]]
then
    helpUse;
    exit 1
fi
ssh-keygen -f "/home/daniel/.ssh/known_hosts" -R "$1.local"

scp ~/.ssh/id_rsa.pub $1.local:.
ssh $1.local "sh -c 'mkdir -p .ssh && cat id_rsa.pub>.ssh/authorized_keys'"

# Distribute private and Test, don't need pwd
scp ~/.ssh/id_rsa $1.local:./.ssh
