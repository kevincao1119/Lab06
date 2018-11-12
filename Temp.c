#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ifttt.h"
int main(int argc, char *argv[])
{
 FILE *fd;
 int n, first, last;
 double y, high, low;
 char buf[101];
 char *temp;
 char l[50], cur[50],h[50];
 time_t start = time(NULL);
 int next = start+1;
 first =0;
 while(start < next){
 if((fd = fopen("/sys/bus/w1/devices/28-021312c431aa/w1_slave", "r")) == (FILE *)NULL) {
 perror("Error: Failed to Open w1_slave file");
 (void) exit(1);
 }
 n = fread(buf, 1, 100, fd);
 if(n == 0) {
 perror("Error: No Arguments Found");
 exit(1);
 }
 buf[n] = '\0';
 fprintf(stdout, "Read %s\n",buf+69);
 (void) fclose(fd);
 temp = buf+69;
 printf("Temp: %s",temp);
 y = atof(temp);
 y=y/1000;
 printf("Integer Y: %.1f\n",y);
 if(first == 0){
	low = y;
	high = y;
	first =1;
	last = y;
	sprintf(l,"Lowest Temp: %.1f C",low);
	sprintf(cur,"Current Temp: %.1f C",y);
	sprintf(h,"Highest Temp: %.1f C",high);
	ifttt("https://maker.ifttt.com/trigger/666/with/key/_A-qdtIfEaA8ZoeM3Fgkq", l,cur, h);
	}
 else{
	if(y <low){low = y;}
	if(y>high){high = y;}
	if(((last-y)>=1) ||((y-last)>=1)){
	sprintf(l,"Lowest Temp: %.1f C",low);
	sprintf(cur,"Current Temp: %.1f C",y);
	sprintf(h,"Highest Temp: %.1f C",high);
	ifttt("https://maker.ifttt.com/trigger/666/with/key/_A-qdtIfEaA8ZoeM3Fgkq", l,cur, h);
	last = y;
	}
	}
 printf("High: %.1f Current: %.1f Low: %.1f\n",high,y,low);
 start = time(NULL);
 next = start+1;
}
 return 0;
}
