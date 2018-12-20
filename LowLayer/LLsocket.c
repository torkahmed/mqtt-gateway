/*
 * LLsocket.c
 * mqtt-gateway
 *
 * Created by Ahmed Tourk on 04/09/2018.
 * Copyright © 2018 AhmedTourk. All rights reserved.
 */

/*
 * INCLUDES
 */

#include <unistd.h>
#include <stdio.h>

#include "LLsocket.h"

/*
 * MACROS
 */


/*
 * GLOBAL VARIABLES
 */


/*
 * PRIVATE FUNCTION DECLARATION
 */


/*
 * PRIVATE FUNCTION IMPLEMENTATION
 */


/*
 * PUBLIC FUNCTIONS
 */

PUBLIC int32_t LLS_CreateServer(int32_t serverPort, int32_t maxPendingConnections)
{
    int32_t serverSocket = INVALID_SOCKET;
    struct sockaddr_in serverSockAddr;
    
    /* Step 1: Create a TCP Socket */
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if(serverSocket < 0)
    {
        fprintf(stderr, "[E] Could Not Create Server Socket\n");
        return INVALID_SOCKET;
    }
    
    /* Step 2: Bind */
    serverSockAddr.sin_family = AF_INET;
    serverSockAddr.sin_port = htons(serverPort);
    serverSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if ( bind(serverSocket, (struct sockaddr *) &serverSockAddr, sizeof(serverSockAddr)) < 0 )
    {
        fprintf(stderr, "[E] Could Not Bind to Server Socket\n");
        return INVALID_SOCKET;
    }
    
    /* Step 3: Listen */
    if ( listen(serverSocket, maxPendingConnections) < 0)
    {
        fprintf(stderr, "[E] Could Not Listen on Server Socket\n");
        return INVALID_SOCKET;
    }
    
    fprintf(stdout, "[I] Server Socket Created %d on Port %d\n", serverSocket, serverPort);
    fflush(stdout);
    return serverSocket;
}

PUBLIC void LLS_TearConnection(int32_t socketDescriptor)
{
    fprintf(stdout, "[I] Closing Socket %d\n", socketDescriptor);
    fflush(stdout);
    shutdown(socketDescriptor, SHUT_RDWR);
    close(socketDescriptor);
}

PUBLIC bool LLS_ConnectToServer(int32_t *socketDescriptor, uint32_t ip, uint16_t port)
{
    struct sockaddr_in sockAddrIn;
    int32_t clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if(clientSocket < 0)
    {
        fprintf(stderr, "[E] Could not Create Client Socket\n");
        return false;
    }
    
    fprintf(stdout, "[I] Client Socket Created %d\n", clientSocket);
    fflush(stdout);
    
    
    sockAddrIn.sin_family = AF_INET;
    sockAddrIn.sin_port = htons(port);
    sockAddrIn.sin_addr.s_addr = ip;
    
    if (connect(clientSocket, (const struct sockaddr*) &sockAddrIn, sizeof(sockAddrIn)) != 0)
    {
        fprintf(stderr, "[E] Could not Connect to Server Socket, Closing Client Socket\n");
        close(clientSocket);
        return false;
    }
    
    fprintf(stdout, "[I] Client Connected to Server\n");
    fflush(stdout);
    *socketDescriptor = clientSocket;
    return true;
    
}
