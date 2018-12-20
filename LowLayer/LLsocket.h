/*
 *  LLsocket.h
 *  mqtt-gateway
 *
 * Created by Ahmed Tourk on 04/09/2018.
 * Copyright © 2018 AhmedTourk. All rights reserved.
 */

#ifndef LLsocket_h
#define LLsocket_h

/*
 INCLUDES
 */
#include <sys/socket.h>

/* TODO: Check if this could be de-coupled from socket wrapper */
#include <netinet/ip.h>

#include "LLstd.h"
/*
 MACROS
 */
#define INVALID_SOCKET (-1)

/*
 TYPEDEFS
 */

/*
 APIs
 */
PUBLIC int32_t LLS_CreateServer(int32_t serverPort, int32_t maxPendingConnections);
PUBLIC void LLS_TearConnection(int32_t socketDescriptor);
PUBLIC bool LLS_ConnectToServer(int32_t *socketDescriptor, uint32_t ip, uint16_t port);
/* TODO: Implement the function
 PUBLIC bool LLS_RecvMessage(int32_t peerSocket, char *recvBuffer, size_t numBytesToRecv);
 */


#endif /* LLsocket_h */
