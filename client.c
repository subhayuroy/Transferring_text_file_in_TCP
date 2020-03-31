//
// Created by subhayu_roy on 4/1/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    if(argc<2)
    {
        fprintf(stderr,"Port number not provided\n");
        exit(1);
    }
    int sockfd, newsockfd, portno, n;
    char buffer[255];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd<0)
        error("Error opening Socket.\n");

    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
        error("Binding Failed\n");

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
        error("Error on accepting\n");

    FILE *f;
    int words =0;
    char c;
    f= fopen("nameoffile.txt", "r");

    while (c=getc(f)!= EOF)
    {
        fscanf(f,"%s",buffer);
        if (isspace(c) || c == '\t')
            words++;
    }

    write(sockfd,&words, sizeof(int));
    rewind(f);

    char ch;
    while (ch != EOF)
    {
        fscanf(f,"%s",buffer);
        write(sockfd,buffer,255);
        ch = fgetc(f);
    }
    printf("The file has been sent.\n");

    close(newsockfd);
    close(sockfd);
    return 0;
}