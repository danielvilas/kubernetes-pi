#!/bin/bash

helpUse()
{
    echo $0 img /dev/[disc] name
}

if [[ -z $1 ]]
then
    helpUse;
fi

if [[ -z $2 ]]
then
    helpUse;
fi
if [[ -z $3 ]]
then
    helpUse;
fi

IMG=$1
DISC=$2
NAME=$3

sudo umount $DISC*

sudo dd if=$IMG | pv| dd bs=1024k of=$2

sync

sudo mount ${DISC}1 /mnt 
touch /mnt/ssh
touch /mnt/$NAME
sudo umount /mnt

sudo umount $DISC*

sudo parted $DISC "resizepart 2 32GB"
sudo e2fsck -f ${DISC}2
sudo resize2fs ${DISC}2
sudo e2fsck -f ${DISC}2

exit 0;