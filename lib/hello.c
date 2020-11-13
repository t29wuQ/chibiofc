#include "chibiofc.h"

typedef struct ofp_hello ofp_hello;
struct ofp_hello {
};

typedef enum {
    OFPHET_VERSIONBITMAP = 1,
} ofp_hello_elem_type;

typedef struct ofp_hello_elem_header ofp_hello_elem_header;
struct ofp_hello_elem_header {
    uint16_t type;
    uint16_t length;
};

typedef struct ofp_hello_elem_versionbitmap ofp_hello_elem_versionbitmap;
struct ofp_hello_elem_versionbitmap {
    uint16_t type;
    uint16_t length;
    uint32_t bitmap;
};

ofp_hello_elem_versionbitmap *create_ofpt_hello() {
    ofp_hello_elem_versionbitmap *elem = malloc(sizeof(ofp_hello_elem_versionbitmap));
    elem->type = OFPHET_VERSIONBITMAP;
    elem->length = 8;
    elem->length = htons(elem->length);
    elem->bitmap = 0x40; // OpenFlow1.5 only
    elem->bitmap = htonl(elem->bitmap);
    return elem;
}

ofp_data *parse_ofpt_hello(const unsigned char *msg) {
    ofp_hello_elem_versionbitmap *elem = create_ofpt_hello();
    ofp_data *data = malloc(sizeof(ofp_data));
    data->data = (unsigned char *)elem;
    data->length = elem->length;
    return data;
}

