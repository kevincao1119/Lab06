#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ifttt.h"
#include <ctype.h>
#include <fcntl.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define low "lowest temperature is "
#define high "highest temperature is "
#define nows "current temperature is "


int main(int argc, char *argv[])
{
 FILE *fd;      /*file pointer*/
 int n,first,last; /*y is current, first is boolean,last is last t*/
 double y, low,high;
char buf[500];
 char *temp;    /* temp pointer*/
 char l[100], cur[100],h[100];    /*different temp message store space*/
 time_t start = time(NULL);  /*current time*/
 int next = start+1;           /* iterator in loop*/
 first =0;                       /* boolean false*/
 while(start < next){
 if((fd = fopen("/sys/bus/w1/devices/28-0213133656aa/w1_slave", "r")) == (FILE *)NULL) {
 perror("Error: Failed to Open w1_slave file");
 (void) exit(1);
 }
 n = fread(buf, 1, 100, fd);
 if(n == 0) {
 perror("Error: No Arguments Found");
 exit(1);
 }
 buf[n] = '\0';          
 fprintf(stdout, "Read '%s'\n",buf+69);   /*location after 69char is temp show in screen*/
 (void) fclose(fd);
 temp = buf+69;/*temp print after 29750, then start print 2 after +69*/ 
 printf("Temp: %s",temp);
 y = atof(temp);       /*change from char to int*/
 y=y/1000;
 printf("Integer Y: %.1f\n",y);
 if(first == 0){  
	low = y;
	high = y;
	first =1;
	last = y;
	sprintf(l,"Lowest Temp: %d C",low/1000);
	sprintf(cur,"Current Temp: %d C",y/1000);
	sprintf(h,"Highest Temp: %d C",high/1000);
	ifttt("https://maker.ifttt.com/trigger/112/with/key/bxK2Vz1Sd9_Qiq2mF8RqrQ", l,cur, h);
	}
 else{
	if(y <low){low = y;}
	else if(y>high){high = y;}
	else if(((last-low)>=1000) ||((high-last)>=1000)){
	sprintf(l,"Lowest Temp: %d C",low/1000);
        sprintf(cur,"Current Temp: %d C",y/1000);
        sprintf(h,"Highest Temp: %d C",high/1000);
	  ifttt("https://maker.ifttt.com/trigger/112/with/key/bxK2Vz1Sd9_Qiq2mF8RqrQ", l,cur, h);
	  last = y;
	}
	
	}
 printf("High: %.1f Current: %.1f Low: %.1f\n",high,y,low);
 start = time(NULL);
 next = start+1;                    /*reassign the next to make loop continue*/
}
 return 0;
}
