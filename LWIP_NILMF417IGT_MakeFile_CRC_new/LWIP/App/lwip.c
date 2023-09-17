/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : LWIP.c
 * Description        : This file provides initialization code for LWIP
 *                      middleWare.
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
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "lwip.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#if defined(__CC_ARM) /* MDK ARM Compiler */
#include "lwip/sio.h"
#endif /* MDK ARM Compiler */
#include "ethernetif.h"

/* USER CODE BEGIN 0 */
#include "tcp.h"
#include "ad7606.h"
/* USER CODE END 0 */
/* Private function prototypes -----------------------------------------------*/
/* ETH Variables initialization ----------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN 1 */
struct dhcp *dhcp;
__lwip_dev lwipdev; // lwip控制结构�?????????????????????

static struct tcp_pcb *client_pcb = NULL;

/* USER CODE END 1 */

/* Variables Initialization */
struct netif gnetif;
ip4_addr_t ipaddr;
ip4_addr_t netmask;
ip4_addr_t gw;
uint8_t IP_ADDRESS[4];
uint8_t NETMASK_ADDRESS[4];
uint8_t GATEWAY_ADDRESS[4];

/* USER CODE BEGIN 2 */
void TCP_Client_Init(void)
{
  // dhcp = netif_dhcp_data(&gnetif);
  // printf("DHCP IP address: %s\r\n", ip4addr_ntoa(&dhcp->offered_ip_addr));
  // printf("DHCP Subnet mask: %s\r\n", ip4addr_ntoa(&dhcp->offered_sn_mask));
  // printf("DHCP Default gateway: %s\r\n", ip4addr_ntoa(&dhcp->offered_gw_addr));
  // 43.138.40.137
  // lwipdev.remoteip[0] = 43;
  // lwipdev.remoteip[1] = 138;
  // lwipdev.remoteip[2] = 40;
  // lwipdev.remoteip[3] = 137;
  // 有线
  lwipdev.remoteip[0] = 192;
  lwipdev.remoteip[1] = 168;
  lwipdev.remoteip[2] = 8;
  lwipdev.remoteip[3] = 4;

  // 无线
  // lwipdev.remoteip[0] = 192;
  // lwipdev.remoteip[1] = 168;
  // lwipdev.remoteip[2] = 8;
  // lwipdev.remoteip[3] = 5;

  ip4_addr_t server_ip;
  client_pcb = tcp_new();
  IP4_ADDR(&server_ip, lwipdev.remoteip[0], lwipdev.remoteip[1], lwipdev.remoteip[2], lwipdev.remoteip[3]);
  printf("client start connect!\n");
  err_t err = tcp_connect(client_pcb, &server_ip, TCP_CLIENT_PORT, tcp_client_connected);
  printf("tcp_connect!! = %d\r\n", err);
  tcp_err(client_pcb, tcp_client_error);
}

err_t LWIP_Send_data(void *array, uint16_t len, uint8_t Channel)
{
  int i;
  err_t err_status;

  err_status = tcp_write(client_pcb, array, len, 1);
  // tcp_sndbuf();
  tcp_output(client_pcb);

  return err_status;
}

static void tcp_client_error(void *arg, err_t err)
{
  printf("connect error!! = %d\r\n", err);
  printf("restart connect!!\r\n");

  // 连接失败的时候释放TCP控制块的内存
  printf("close connect\r\n");
  tcp_close(client_pcb);

  // 重新连接
  printf("restart Init\r\n");

  TCP_Client_Init();
}

static err_t tcp_client_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
  if (p != NULL)
  {
    uint8_t RecvBuff[20];
    tcp_recved(tpcb, p->tot_len);

    MEMCPY(RecvBuff, p->payload, p->tot_len);
    uint8_t index;
    if (RecvBuff[1] == 0xff && RecvBuff[2] == 0xfafa)
    {
      index = RecvBuff[4];

      for (int i = 0; i < 30; i++)
      {
        if (SendDataBuff[i][12] == index)
        {
          uint16_t len = SendBufLen;
          uint8_t res;
          res = LWIP_Send_data(SendDataBuff[i], len, 1);

          break;
        }
      }
    }

    memset(p->payload, 0, p->tot_len);
    pbuf_free(p);
  }
  else if (err == ERR_OK)
  {
    printf("server has been disconnected!\n");
    tcp_close(tpcb);
    TCP_Client_Init();
  }
  return ERR_OK;
}

static err_t tcp_client_send(void *arg, struct tcp_pcb *tpcb)
{
  uint8_t send_buf[] = "This is a TCP Client test...\n";

  tcp_write(tpcb, send_buf, sizeof(send_buf), 1);
  return ERR_OK;
}

// lwIP TCP连接建立后调用回调函
static err_t tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err)
{
  printf("connected ok!\n");

  // tcp_poll(tpcb, tcp_client_send, 2);

  tcp_recv(tpcb, tcp_client_recv);
  return ERR_OK;
}

/* USER CODE END 2 */

/**
 * LwIP initialization function
 */
void MX_LWIP_Init(void)
{
  /* IP addresses initialization */
  IP_ADDRESS[0] = 192;
  IP_ADDRESS[1] = 168;
  IP_ADDRESS[2] = 8;
  IP_ADDRESS[3] = 156;
  NETMASK_ADDRESS[0] = 255;
  NETMASK_ADDRESS[1] = 255;
  NETMASK_ADDRESS[2] = 255;
  NETMASK_ADDRESS[3] = 0;
  GATEWAY_ADDRESS[0] = 192;
  GATEWAY_ADDRESS[1] = 168;
  GATEWAY_ADDRESS[2] = 8;
  GATEWAY_ADDRESS[3] = 1;

  /* USER CODE BEGIN IP_ADDRESSES */
  /* USER CODE END IP_ADDRESSES */

  /* Initilialize the LwIP stack without RTOS */
  lwip_init();

  /* IP addresses initialization without DHCP (IPv4) */
  IP4_ADDR(&ipaddr, IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);
  IP4_ADDR(&netmask, NETMASK_ADDRESS[0], NETMASK_ADDRESS[1], NETMASK_ADDRESS[2], NETMASK_ADDRESS[3]);
  IP4_ADDR(&gw, GATEWAY_ADDRESS[0], GATEWAY_ADDRESS[1], GATEWAY_ADDRESS[2], GATEWAY_ADDRESS[3]);

  /* add the network interface (IPv4/IPv6) without RTOS */
  netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);

  /* Registers the default network interface */
  netif_set_default(&gnetif);

  if (netif_is_link_up(&gnetif))
  {
    /* When the netif is fully configured this function must be called */
    netif_set_up(&gnetif);
  }
  else
  {
    /* When the netif link is down this function must be called */
    netif_set_down(&gnetif);
  }

  /* Set the link callback function, this function is called on change of link status*/
  netif_set_link_callback(&gnetif, ethernetif_update_config);

  /* Create the Ethernet link handler thread */

  /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

#ifdef USE_OBSOLETE_USER_CODE_SECTION_4
/* Kept to help code migration. (See new 4_1, 4_2... sections) */
/* Avoid to use this user section which will become obsolete. */
/* USER CODE BEGIN 4 */
/* USER CODE END 4 */
#endif

/**
 * ----------------------------------------------------------------------
 * Function given to help user to continue LwIP Initialization
 * Up to user to complete or change this function ...
 * Up to user to call this function in main.c in while (1) of main(void)
 *-----------------------------------------------------------------------
 * Read a received packet from the Ethernet buffers
 * Send it to the lwIP stack for handling
 * Handle timeouts if LWIP_TIMERS is set and without RTOS
 * Handle the llink status if LWIP_NETIF_LINK_CALLBACK is set and without RTOS
 */
void MX_LWIP_Process(void)
{
  /* USER CODE BEGIN 4_1 */
  ethernetif_set_link(&gnetif);
  /* USER CODE END 4_1 */
  ethernetif_input(&gnetif);

  /* USER CODE BEGIN 4_2 */
  /* USER CODE END 4_2 */
  /* Handle timeouts */
  sys_check_timeouts();

  /* USER CODE BEGIN 4_3 */
  // ethernetif_set_link(&gnetif);
  /* USER CODE END 4_3 */
}

#if defined(__CC_ARM) /* MDK ARM Compiler */
/**
 * Opens a serial device for communication.
 *
 * @param devnum device number
 * @return handle to serial device if successful, NULL otherwise
 */
sio_fd_t sio_open(u8_t devnum)
{
  sio_fd_t sd;

  /* USER CODE BEGIN 7 */
  sd = 0; // dummy code
          /* USER CODE END 7 */

  return sd;
}

/**
 * Sends a single character to the serial device.
 *
 * @param c character to send
 * @param fd serial device handle
 *
 * @note This function will block until the character can be sent.
 */
void sio_send(u8_t c, sio_fd_t fd)
{
  /* USER CODE BEGIN 8 */
  /* USER CODE END 8 */
}

/**
 * Reads from the serial device.
 *
 * @param fd serial device handle
 * @param data pointer to data buffer for receiving
 * @param len maximum length (in bytes) of data to receive
 * @return number of bytes actually received - may be 0 if aborted by sio_read_abort
 *
 * @note This function will block until data can be received. The blocking
 * can be cancelled by calling sio_read_abort().
 */
u32_t sio_read(sio_fd_t fd, u8_t *data, u32_t len)
{
  u32_t recved_bytes;

  /* USER CODE BEGIN 9 */
  recved_bytes = 0; // dummy code
                    /* USER CODE END 9 */
  return recved_bytes;
}

/**
 * Tries to read from the serial device. Same as sio_read but returns
 * immediately if no data is available and never blocks.
 *
 * @param fd serial device handle
 * @param data pointer to data buffer for receiving
 * @param len maximum length (in bytes) of data to receive
 * @return number of bytes actually received
 */
u32_t sio_tryread(sio_fd_t fd, u8_t *data, u32_t len)
{
  u32_t recved_bytes;

  /* USER CODE BEGIN 10 */
  recved_bytes = 0; // dummy code
                    /* USER CODE END 10 */
  return recved_bytes;
}
#endif /* MDK ARM Compiler */
