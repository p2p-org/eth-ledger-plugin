#include "p2p_staking.h"

void handle_provide_token(void *parameters) {
    ethPluginProvideInfo_t *msg = (ethPluginProvideInfo_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;
    (void) context;

    msg->result = ETH_PLUGIN_RESULT_OK;
}
