#include "mbed_netif.h"


static EthernetInterface d_eth_iface;


EthernetInterface *mbed_netif_get_netif()
{
    return &d_eth_iface;
}
