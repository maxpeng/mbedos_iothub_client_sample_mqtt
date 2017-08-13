// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TCPSOCKET_C_H
#define TCPSOCKET_C_H

#ifdef __cplusplus
extern "C" {
#endif

	typedef void* TCPSOCKET_HANDLE;

	TCPSOCKET_HANDLE tcpsocket_create(void);
	void tcpsocket_set_blocking(TCPSOCKET_HANDLE tcpSocketHandle, bool blocking, unsigned int timeout);
	void tcpsocket_destroy(TCPSOCKET_HANDLE tcpSocketHandle);
	int tcpsocket_connect(TCPSOCKET_HANDLE tcpSocketHandle, const char* host, const int port);
	bool tcpsocket_is_connected(TCPSOCKET_HANDLE tcpSocketHandle);
	void tcpsocket_close(TCPSOCKET_HANDLE tcpSocketHandle);
	int tcpsocket_send(TCPSOCKET_HANDLE tcpSocketHandle, const char* data, int length);
	int tcpsocket_recv(TCPSOCKET_HANDLE tcpSocketHandle, char* data, int length);

#ifdef __cplusplus
}
#endif

#endif /* TCPSOCKET_C_H */
