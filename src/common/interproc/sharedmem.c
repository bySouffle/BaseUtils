/****************************************************************************************************************************
*
*   文 件 名 ： sharedmem.c 
*   文件描述 ：  
*   创建日期 ：2019年4月11日
*   版本号 ：   
*   负责人 ： Zhangsheng 
*   其 他 ：
*   修改日志 ：
*
****************************************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <regex.h>
#include <stdarg.h>	/* ANSI C header file */
#include <syslog.h> 	/* for syslog() */
#include <errno.h>
#include <signal.h>
#include <pthread.h>

#include <getopt.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <asm/types.h>
#include <arpa/inet.h>
#include <linux/kernel.h>
#include <linux/netlink.h>
#include <linux/ethtool.h>
#include <linux/rtnetlink.h>
#include <linux/sockios.h>
#include <linux/if_ether.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/io.h>
#include <net/if_arp.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>

#include "sharedmem.h"

void * sharedmem_malloc(int mSize)
{
	//共享的管理区
	void * pSharedmem = NULL;
	if((pSharedmem = (void *)mmap(NULL, mSize, MM_MODE, MM_FLAGS, -1, 0)) == MAP_FAILED)
		err_sys("semaphore mmap error");

	bzero(pSharedmem, mSize);
	iLog("sharedmem malloc addr[0x%x + %d]", pSharedmem, mSize);
	
	return pSharedmem;
}


void sharedmem_release(void * pSharedmem, int mSize)
{
	if(pSharedmem == NULL || pSharedmem == MAP_FAILED)
		return;
	
	if(munmap(pSharedmem, mSize) == -1)
		err_sys("munmap error");

	iLog("sharedmem release addr[0x%x + %d]", pSharedmem, mSize);
	
	return;
}

