#include "tcpclient.h"
// __lwip_dev lwipdev;						//lwip控制结构体 
// struct netif lwip_netif;				//定义一个全局的网络接口


// void TCP_Client_Init(void)
// {
//     struct tcp_pcb *client_pcb = NULL; // 这一句一定要放在里面，否则会没用
//     ip4_addr_t server_ip;              // 因为客户端要主动去连接服务器，所以要知道服务器的IP地址
//     /* 创建一个TCP控制块  */
//     client_pcb = tcp_new();

//     IP4_ADDR(&server_ip, DEST_IP_ADDR0, DEST_IP_ADDR1, DEST_IP_ADDR2, DEST_IP_ADDR3); // 合并IP地址

//     printf("客户端开始连接!\n");

//     // 开始连接
//     tcp_connect(client_pcb, &server_ip, TCP_CLIENT_PORT, client_connected);
//     ip_set_option(client_pcb, SOF_KEEPALIVE);

//     printf("已经调用了tcp_connect函数\n");

//     // 注册异常处理
//     tcp_err(client_pcb, client_err);
//     printf("已经注册异常处理函数\n");
// }