#include "chibiofc.h"
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>

static uint32_t xid;

ofp_header *create_ofp_header(uint8_t type, uint16_t length) {
    ofp_header *header = malloc(sizeof(ofp_header));
    header->version = 0x06;
    header->type = type;
    header->length = 8 + length;
    header->length = htons(header->length);
    header->xid = xid;
    header->xid = htonl(header->xid);
    return header;
}

ofp_data *parse_ofp_header(unsigned char *msg) {
    struct ofp_header *header = (struct ofp_header *)msg;
    xid = header->xid;

    if (header->version > 0x06) {
        exit(1);
    }

    msg += sizeof(ofp_header);
    ofp_data *data;
    ofp_data *res = malloc(sizeof(ofp_data));
    uint8_t type;
    switch (header->type) {
        case OFPT_HELLO:
            type = OFPT_HELLO;
            data = parse_ofpt_hello(msg);
            break;
        default:
            fprintf(stderr, "hello");
            res->data = NULL;
            res->length = 0;
            return res;
    }

    header = create_ofp_header(type, data->length);

    res->data = malloc(header->length);
    res->length = header->length;

    memcpy(res->data, header, sizeof(ofp_header));
    memcpy(res->data + sizeof(ofp_header), data->data, data->length);

    free(header);
    free(data->data);
    free(data);

    return res;
}

int run(int tcp_port) {
    int server_soc;
    int client_soc;
    struct sockaddr_in server;
    struct sockaddr_in client;

    server_soc = socket(AF_INET, SOCK_STREAM, 0);
    if ((server_soc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(tcp_port);
    server.sin_addr.s_addr = INADDR_ANY;
    bind(server_soc, (struct sockaddr *)&server, sizeof(server));
    listen(server_soc, 4096);

    unsigned char *buf = malloc(1500);
    for(;;) {
        socklen_t len = sizeof(client);
        client_soc = accept(server_soc, (struct sockaddr *)&client, &len);

        pid_t pid = fork();

        if (pid == 0) {
            int n = read(client_soc, buf, sizeof(buf));
            if (n < 0) {
                fprintf(stderr, "load error");
                exit(1);
            }
            fprintf(stderr, "data %dbyte \n", n);

            ofp_data *res = parse_ofp_header(buf); 
            if (res->length != 0)
                write(client_soc, res->data, res->length);

            free(buf);
            free(res->data);
            free(res);
            // close(client_soc);
        } else if (pid < 0) {
            exit(1);
        }
    }

    return 0;
}

