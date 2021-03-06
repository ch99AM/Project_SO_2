#include "fifo_server.h"
//#include "../sobel/sobel.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <zlib.h>
#include <dirent.h>
#define MAXCHAR 1000
#define PORT 8081
char *storage_directory_ = "./fifo_storage";
int init_fifo_server(void){
    int fd =0, confd = 0,b,tot;
    struct sockaddr_in serv_addr;
    struct sockaddr_in client;
    memset(&client, '0', sizeof(client));
    char str[100];
    int len = sizeof(client);
    char buff[1025];
    int num;
    char filename[100];
    int valor_predominante = 0;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("=> Socket creado\n");
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(buff, '0', sizeof(buff));
    memset(filename, '0', sizeof(filename));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);
    bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(fd, 100000);
    int counter = 0;
    confd = accept(fd, (struct sockaddr*)&client, &len);
    while (1)
    {
        printf("\n=> El IP del cliente es: %s\n", inet_ntop(AF_INET, &client.sin_addr, str, sizeof(str)));
        printf("=> EL id del cliente es: %i\n", confd);
        read(confd, filename, 256);
        char str[100];
        sprintf(str, "%d", counter);
        strcat(str, filename);
        FILE* fp = fopen(str, "wb");
        if (fp != NULL)
        {
            while((b = recv(confd, buff, 1024,0))> 0 ) {
		            tot+=b;
		            fwrite(buff, 1, b, fp);
		    }
            printf("=> Su peso es de: %d bytes.\n",tot);
		    if (b<0)
		        perror("Receiving");
		    
            tot = 0;
            //strcat(storage_directory_, filename);
            process_image(storage_directory_);
            memset(buff, '0', sizeof(buff));
        }
        fclose(fp);
        printf("Uno más\n");
        counter++;
        
    }
    
}
void process_image(char* file_name){
    //Use sobel function...
    printf("Processing the image %s with sobel algorithm\n", file_name);
}