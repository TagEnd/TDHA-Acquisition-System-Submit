/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : LWIP.h
  * Description        : This file provides code for the configuration
  *                      of the LWIP.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *************************************************************************

  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __mx_lwip_H
#define __mx_lwip_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lwip/opt.h"
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"
#include "ethernetif.h"

/* Includes for RTOS ---------------------------------------------------------*/
#if WITH_RTOS
#include "lwip/tcpip.h"
#endif /* WITH_RTOS */

/* USER CODE BEGIN 0 */
#define LWIP_MAX_DHCP_TRIES		4

#define TCP_CLIENT_PORT 8085

//tcp服务器连接状�???
enum tcp_client_states
{
	ES_TCPCLIENT_NONE = 0,		//没有连接
	ES_TCPCLIENT_CONNECTED,		//连接到服务器�??? 
	ES_TCPCLIENT_CLOSING,		//关闭连接
}; 

//LWIP回调函数使用的结构体
struct tcp_client_struct
{
	uint8_t state;               //当前连接�???
	struct tcp_pcb *pcb;    //指向当前的pcb
	struct pbuf *p;         //指向接收/或传输的pbuf
};  
typedef struct  
{
	uint8_t mac[6];      //MAC地址
	uint8_t remoteip[4];	//远端主机IP地址 
	uint8_t ip[4];       //本机IP地址
	uint8_t netmask[4]; 	//子网掩码
	uint8_t gateway[4]; 	//默认网关的IP地址
	
	__IO uint8_t dhcpstatus;	//dhcp状�?? 
					//0,未获取DHCP地址;
					//1,进入DHCP获取状�??
					//2,成功获取DHCP地址
					//0XFF,获取失败.
}__lwip_dev;
extern __lwip_dev lwipdev;	//lwip控制结构�???


/* USER CODE END 0 */

/* Global Variables ----------------------------------------------------------*/
extern ETH_HandleTypeDef heth;

/* LWIP init function */
void MX_LWIP_Init(void);

#if !WITH_RTOS
/* USER CODE BEGIN 1 */
/* Function defined in lwip.c to:
 *   - Read a received packet from the Ethernet buffers
 *   - Send it to the lwIP stack for handling
 *   - Handle timeouts if NO_SYS_NO_TIMERS not set
 */
void MX_LWIP_Process(void);

void TCP_Client_Init(void);

static err_t tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err);

static err_t tcp_client_recv(void *arg,struct tcp_pcb *tpcb,struct pbuf *p,err_t err);

static err_t tcp_client_send(void *arg, struct tcp_pcb *tpcb);

static void tcp_client_error(void *arg,err_t err);
// err_t tcp_client_poll(void *arg, struct tcp_pcb *tpcb);

err_t LWIP_Send_data(void *array, uint16_t len, uint8_t Channel);


/* USER CODE END 1 */
#endif /* WITH_RTOS */

#ifdef __cplusplus
}
#endif
#endif /*__ mx_lwip_H */

/**
  * @}
  */

/**
  * @}
  */
