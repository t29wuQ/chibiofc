#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

typedef struct ofp_header ofp_header;
struct ofp_header {
    uint8_t version;
    uint8_t type;
    uint16_t length;
    uint32_t xid;
};

typedef struct ofp_data ofp_data;
struct ofp_data {
    unsigned char *data;
    uint16_t length;
};

typedef enum {
    OFPT_HELLO,
    OFPT_ERROR,
    OFPT_ECHO_REQUEST,
    OFPT_ECHO_REPLY,
    OFPT_EXPERIMENTER,
    OFPT_FEATURE_REQUEST,
    OFPT_FEATURE_REPLY,
    OFPT_GET_CONFIG_REQUEST,
    OFPT_GET_CONFIG_REPLY,
    OFPT_SET_CONFIG,
    OFPT_PACKET_IN,
    OFPT_FLOW_REMOVED,
    OFPT_PORT_STATUS,
    OFPT_PACKET_OUT,
    OFPT_FLOW_MOD,
    OFPT_GROUP_MOD,
    OFPT_PORT_MOD,
    OFPT_TABLE_MOD,
    OFPT_MULTIPART_REQUEST,
    OFPT_MULTIPART_REPLY,
    OFPT_BARRIER_REEQUEST,
    OFPT_BARRIER_REPLY,
    OFPT_ROLE_REQUEST,
    OFPT_ROLE_REPLY,
    OFPT_GET_ASYNC_REQUEST,
    OFPT_GET_ASYNC_REPLY,
    OFPT_SET_ASYNC,
    OFPT_METER_MOD,
    OFPT_ROLE_STATUS,
    OFPT_TABLE_STATUS,
    OFPT_REQUESTFORWARD,
    OFPT_BUNDLE_CONTROL,
    OFPT_BUNDLE_ADD_MESSAGE,
    OFPT_CONTROLLER_STATUS,
} ofp_type;

int run(int tcp_port);
ofp_header *create_ofp_header(uint8_t type, uint16_t length);
ofp_data *parse_ofpt_hello(const unsigned char *msg);
