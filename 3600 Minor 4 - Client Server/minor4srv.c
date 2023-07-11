/* SERVER
*   Minor 4     by Austin Carlin
*   ajc0325     austincarlin@my.unt.edu  
*   3600.003    11/7/2021   
*/
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char** argv)
{
    //Print usage if there isn't a single arg
    if(argc != 2)
    {
        printf("Usage: ./server <port>\n");
        return -1;
    }

    time_t t;
    srand((unsigned) time(&t));

    struct sockaddr_in srv_addr;
    struct sockaddr_in cli_addr;
    char srv_msg[2000], cli_msg[2000];
    int cli_struct_len = sizeof(cli_addr);

    //Clean up any lingering bits
    memset(srv_msg, '\0', sizeof(srv_msg));
    memset(cli_msg, '\0', sizeof(cli_msg));

    //Setup file descriptor
    int socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(socket_desc < 0)
    {
        printf("Socket error");
        return -1;
    }
    
    //use the internet, use whatever IP we've got, and use the user's given port
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(atoi(argv[1]));
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

    //Binding error protection
    int on = 1; 
	setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    if(bind(socket_desc, (struct sockaddr*)&srv_addr, sizeof(srv_addr)) < 0){
        printf("Port bind error\n");
        return -1;
    }

    printf("listening...\n");
    while(1){
        // Receive client's message:
        if (recvfrom(socket_desc, cli_msg, sizeof(cli_msg), 0, (struct sockaddr*)&cli_addr, &cli_struct_len) < 0)
        {
            printf("timeout\n");
            return -1;
        }

        //Roll the dice to see if we eat the packet
        int packetRoll = rand() % 10;
        if(packetRoll <= 2) //random numbers will be 0, 1, 2... 9
        {
            printf("Eating packet. It was very yummy.\n");
            //If we do eat the packet, restart the while loop! Do not send a response. they don't DESERVE a response :c
            continue;
        }

        printf("Msg from client: \"%s\"\n", cli_msg);
        //Send out our response
        if (sendto(socket_desc, "pong", strlen("pong"), 0, (struct sockaddr*)&cli_addr, cli_struct_len) < 0)
        {
            printf("Can't send\n");
            return -1;
        }
    }
}