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
double gettemp(int fd, char *buff);

int main(int argc, char *argv[])
{
 FILE *fd;
 int n, first, last;
 double y, high, low;
 char buf[500];
 char *temp;
 char l[100], cur[100],h[100];
 time_t start = time(NULL);
 int next = start+1;
 first =0;
 while(start < next){
 if((fd = fopen("/sys/bus/w1/devices/28-0023984300c5/w1_slave", "r")) == (FILE *)NULL) {
 perror("Error: Failed to Open w1_slave file");
 (void) exit(1);
 }
 n = fread(buf, 1, 100, fd);//eads data from the given stream fd into the array pointed to, by ptr--buf
 if(n == 0) {
 perror("Error: No Arguments Found");
 exit(1);
 }
 buf[n] = '\0';
 fprintf(stdout, "Read %s\n",buf+69);//sends formatted output to a stream,printing output on the main output device for the session
 (void) fclose(fd);//closes the stream. All buffers are flushed.
 temp = buf+69;
 printf("Temp: %s",temp);
 y = atof(temp); //converts the string argument str to a floating-point number
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
	ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/dhiJR-IZGw4iy-XaJAqJSfy8ArgkPMFFGVC94n0Wrl4", l,cur, h);
	}
 else{
	if(y <low){low = y;}
	if(y>high){high = y;}
	if(((last-y)>=1) ||((y-last)>=1)){
	sprintf(l,"Lowest Temp: %.1f C",low);
	sprintf(cur,"Current Temp: %.1f C",y);
	sprintf(h,"Highest Temp: %.1f C",high);
	ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/dhiJR-IZGw4iy-XaJAqJSfy8ArgkPMFFGVC94n0Wrl4", l,cur, h);
	last = y;
	}
	}
 printf("High: %.1f Current: %.1f Low: %.1f\n",high,y,low);
 start = time(NULL);
 next = start+1;
}
 return 0;
}
