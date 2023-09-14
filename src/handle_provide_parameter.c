#include "p2p_staking.h"

static void handle_no_params(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        default:
            PRINTF("Unexpected parameter: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;
    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case DO_DEPOSIT:
            handle_no_params(msg, context);
            break;
        case DO_WITHDRAW_RESERVED_DO_NOT_USE:
            PRINTF("Withdrawal is not supported with this plugin version\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
