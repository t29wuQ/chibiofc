#include "chibiofc.h"

ofp_data *parse_ofpt_echo_request(unsigned char *msg) {
    ofp_data *data = malloc(sizeof(ofp_data));
    data->data = msg;
    data->length = 0;
    return data;
}
