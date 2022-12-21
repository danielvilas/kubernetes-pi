#!/bin/bash

helpUse()
{
    echo $0 img /dev/{disc} name [User] [passwd]
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

PIUSER=$USER
PASSWORD=raspberry

if [[ -z $4 ]]
then
    PIUSER=$USER
else
    PIUSER=$4
fi

if [[ -z $5 ]]
then
    PASSWORD=raspberry
else
    PASSWORD=$5
fi
echo  Generating user $PIUSER/$PASSWORD

sudo umount $DISC*

dd if=$IMG | pv| dd bs=1024k of=$2

sync


pass=$(echo $PASSWORD | openssl passwd -6 -stdin)

mount ${DISC}1 /mnt 
touch /mnt/ssh
touch /mnt/$NAME
echo "$PIUSER:$pass">/mnt/userconf
cat /mnt/userconf
umount /mnt

umount $DISC*

parted $DISC "resizepart 2 32GB"
e2fsck -f ${DISC}2
resize2fs ${DISC}2
e2fsck -f ${DISC}2

exit 0;