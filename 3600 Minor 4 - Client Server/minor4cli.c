/* CLIENT
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

#define NUM_PINGS 10

int main(int argc, char** argv)
{
    //Print usage if there aren't 2 args
    if(argc != 3)
    {
        printf("Usage: ./client <host> <port>\n");
        return -1;
    }

    int socket_desc;
    struct sockaddr_in srv_addr;
    char srv_msg[2000], cli_msg[2000];
    int srv_struct_len = sizeof(srv_addr);

    //Clean up any lingering bits
    memset(srv_msg, '\0', sizeof(srv_msg));
    memset(cli_msg, '\0', sizeof(cli_msg));

    //Setup file descriptor
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(socket_desc < 0)
    {
        printf("Socket error.\n");
        return -1;
    }
    //Get ip address from hostname
    char ip[50];
    memset(ip, '\0', sizeof(ip));
    struct hostent *he = gethostbyname(argv[1]);
    struct in_addr** addr_list;

    addr_list = (struct in_addr **) he->h_addr_list;
    //Get the first ip address from the list 
    strcpy(ip, inet_ntoa(*addr_list[0]));

    //Use the internet to connect to the domain's ip using the user's given port
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(atoi(argv[2]));
    srv_addr.sin_addr.s_addr = inet_addr(ip);

    //Setup timeval struct so we can track time for timeouts
    struct timeval tval;
    tval.tv_sec = 1;

    //Allow the socket to timeout after 1 sec
    setsockopt(socket_desc, SOL_SOCKET, SO_RCVTIMEO, (char*)&tval, sizeof(tval));

    //Keep track of each ping's rtt (for later analysis)
    double sent=0, recieved=0;
    double* rtt_list = malloc(sizeof(double) * NUM_PINGS);
    for(int i=0;i<NUM_PINGS;i++) rtt_list[i] = 0;


    for(int i = 0; i < NUM_PINGS; i++)
    {
        //Send a packet
        if (sendto(socket_desc, "ping", strlen("ping"), 0, (struct sockaddr*)&srv_addr, srv_struct_len) < 0)
        {
            printf("Can't send\n");
            return -1;
        }

        //Write down the time and increment the number sent
        sent++;
        clock_t clock1 = clock();

        //Wait a second for a response
        if (recvfrom(socket_desc, srv_msg, sizeof(srv_msg), 0, (struct sockaddr*)&srv_addr, &srv_struct_len) < 0)
        {
            printf("timeout\n");
            continue;
        }

        //Write down the time and increment the number recieved
        recieved++;
        clock_t clock2 = clock();

        //Get the time difference (*1000 to convert to ms)
        double rtt = 1000.0*(clock2-clock1)/CLOCKS_PER_SEC;
        
        rtt_list[i] = rtt;

        printf("%s (RTT: %.5fms)\n", srv_msg, rtt);
    }
    

    //Analyze run
    double min=9999.0, max=0, avg=0, total=0;
    int entries = 0;
    for(int i = 0; i < NUM_PINGS; i++)
    {
        double this_rtt = rtt_list[i];
        if(this_rtt == 0)
            continue;
        entries++;
        total+= this_rtt;
        if(this_rtt < min)
            min = this_rtt;
        if(this_rtt > max)
            max = this_rtt;
    }
    avg = total/entries;
    double packetloss = 100-((recieved/sent)*100.0);

    printf("| PACKETS\n| %.0f sent, %.0f recieved. %.2f%% loss.\n", sent, recieved, packetloss);
    printf("| RTT\n| min: %.3fms, max: %.3fms, average: %.3fms\n", min, max, avg);
}