//from http://www.raspberrypiwiki.com/images/d/d7/Ups-hat-c.zip
#include <unistd.h>			// close read write
#include <stdio.h>			// printf
#include <fcntl.h>			// open
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <getopt.h>

#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "influxdb.h"

static volatile bool need_exit = false;

#define VREG 2
#define CREG 4
#define BUFSIZE	16
#define DEV "/dev/i2c-1"
#define ADRS 0x36
/*
export MONITORING_INFLUXDB_SERVICE_HOST=10.107.124.204
export MONITORING_INFLUXDB_SERVICE_PORT=8086
export MY_NODE_NAME=nodepi1
*/


static int readReg(int busfd, __uint16_t reg, unsigned char *buf, int bufsize)
{
    unsigned char reg_buf[2];

    reg_buf[0] = (reg >> 0) & 0xFF;
    reg_buf[1] = (reg >> 8) & 0xFF;

    int ret = write(busfd, reg_buf, 2);

    if (ret < 0) {
        printf("Write failed trying to read reg: %04x (0x%02x 0x%02x)\n", reg, reg_buf[0], reg_buf[1], reg);
        return ret;
    }

    return read(busfd, buf, bufsize);
}

int onePass(unsigned short vOpt, unsigned short cOpt,influx_client_t* client,char* node){
    printf("Reading\n");
    int bus = 1;
    unsigned char buf[BUFSIZE] = {0};

    int busfd;
    if ((busfd = open(DEV, O_RDWR)) < 0) {
        printf("can't open %s (running as root?)\n",DEV);
        return(-1);
    }

    int ret = ioctl(busfd, I2C_SLAVE, ADRS);
    if (ret < 0)
        printf("i2c device initialisation failed\n");

    if (ret < 0) return(-1);

    readReg(busfd, VREG, buf, 2);

    int hi,lo;
    hi = buf[0];
    lo = buf[1];
    int v = (hi << 8)+lo;
    float fv=(((float)v)* 78.125 / 1000000.0);
    if (vOpt) {
		printf("%fV ",fv);
	}

    readReg(busfd, CREG, buf, 2);
    hi = buf[0];
    lo = buf[1];
    int c = (hi << 8)+lo;
    float fc=((float)c) / 256.0;
    if (!cOpt && !vOpt) {
		printf("%i",(int)(fc));
	}
	
	if (cOpt) {
		printf("%f%%",fc);
	}

	printf("\n");

    close(busfd);
    post_http(client,
        INFLUX_MEAS("battery"),
        INFLUX_TAG("nodename", node),
        INFLUX_F_FLT("voltage", fv, 2),
        INFLUX_F_FLT("capacity", fc, 2),
        //INFLUX_TS(1512722735522840439),
        INFLUX_END);
}

long long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // caculate milliseconds
    //printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}


static void on_sigint(int unused)
{
    fprintf(stderr,"Cleaning and exiting\n");
    need_exit = true;
}


int main(int argc, char **argv)
{
    unsigned short vOpt = 0, cOpt = 0;
    int o;
    printf("UPS Starting v0.0.2\n");
    signal(SIGINT, &on_sigint);
    siginterrupt(SIGINT, true);
    signal(SIGTERM, &on_sigint);
    siginterrupt(SIGTERM, true);


    while ((o = getopt (argc, argv, "vc")) != -1) {
        switch (o)
        {
        case 'v':
            vOpt = 1;
            break;
        case 'c':
            cOpt = 1;
            break;
        }
    }

    influx_client_t c;
    c.host = strdup(getenv ("MONITORING_INFLUXDB_SERVICE_HOST"));
    //printf("%s:%s\n",c.host,getenv ("MONITORING_INFLUXDB_SERVICE_PORT"));
    c.port = atoi(getenv ("MONITORING_INFLUXDB_SERVICE_PORT"));
    printf("influxdb at %s:%i\n",c.host,c.port);
    c.db = "k8s";
    c.usr="";
    c.pwd="";


    char* node_name = getenv("MY_NODE_NAME");
    printf("running on: %s\n",node_name);
    while(!need_exit){
        long long currentTs = current_timestamp();
        int ret= onePass(vOpt,cOpt,&c,node_name);
        //if (ret !=0) return 0;
        long long wait = 1000 + currentTs - current_timestamp();
        fflush(stdout);
        //printf("wait: %d \n",wait);
        if(wait>0) {
            //Prevents infinite wait on debug
            usleep(wait*1000);
        } 
        else
            fprintf(stderr,"lost\n");
    }

    return 0;

}
