#ifndef __TCPCLIENT_H__
#define __TCPCLIENT_H__

#include "lwip/netif.h"
#include "lwip/ip.h"
#include "lwip/tcp.h"
#include "lwip/init.h"
#include "netif/etharp.h"
#include "lwip/udp.h"
#include "lwip/pbuf.h"
#include <stdio.h>	
#include <string.h>
#include "main.h"
#include "lwip.h"



// typedef struct  
// {
// 	uint8_t mac[6];      //MAC地址
// 	uint8_t remoteip[4];	//远端主机IP地址 
// 	uint8_t ip[4];       //本机IP地址
// 	uint8_t netmask[4]; 	//子网掩码
// 	uint8_t gateway[4]; 	//默认网关的IP地址
	
// 	__IO uint8_t dhcpstatus;	//dhcp状态 
// 					//0,未获取DHCP地址;
// 					//1,进入DHCP获取状态
// 					//2,成功获取DHCP地址
// 					//0XFF,获取失败.
// }__lwip_dev;
// extern __lwip_dev lwipdev;	//lwip控制结构体



// void TCP_Client_Init(void);


// static err_t client_send(void *arg, struct tcp_pcb *tpcb);   //发送函数，调用了tcp_write函数


// static err_t client_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);


// static err_t client_connected(void *arg, struct tcp_pcb *pcb, err_t err);





#endif 