// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "mbed.h"

#include <stddef.h>
#include "TCPSocket.h"  // mbed OS5
#include "tcpsocket_c.h"
#include "mbed_netif.h"


TCPSOCKET_HANDLE tcpsocket_create(void)
{
    EthernetInterface *pNetIf = mbed_netif_get_netif();
    if (pNetIf != NULL) {
        return new TCPSocket(pNetIf);
    }

    return NULL;
}

void tcpsocket_set_blocking(TCPSOCKET_HANDLE tcpSocketHandle, bool blocking, unsigned int timeout)
{
    TCPSocket* tsc = (TCPSocket*)tcpSocketHandle;
    tsc->set_blocking(blocking);
    tsc->set_timeout(timeout);
}

void tcpsocket_destroy(TCPSOCKET_HANDLE tcpSocketHandle)
{
    delete (TCPSocket*)tcpSocketHandle;
}

int tcpsocket_connect(TCPSOCKET_HANDLE tcpSocketHandle, const char* host, const int port)
{
    TCPSocket* tsc = (TCPSocket*)tcpSocketHandle;
    return tsc->connect(host, port);
}

void tcpsocket_close(TCPSOCKET_HANDLE tcpSocketHandle)
{
    TCPSocket* tsc = (TCPSocket*)tcpSocketHandle;
    tsc->close();
}

int tcpsocket_send(TCPSOCKET_HANDLE tcpSocketHandle, const char* data, int length)
{
    TCPSocket* tsc = (TCPSocket*)tcpSocketHandle;
    return tsc->send((char*)data, length);
}

int tcpsocket_recv(TCPSOCKET_HANDLE tcpSocketHandle, char* data, int length)
{
    TCPSocket* tsc = (TCPSocket*)tcpSocketHandle;
    return tsc->recv(data, length);
}

