#include "p2p_staking.h"

// Sets the first screen to display.
void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    const context_t *context = (const context_t *) msg->pluginContext;
    // msg->name will be the upper sentence displayed on the screen.
    // msg->version will be the lower sentence displayed on the screen.

    msg->result = ETH_PLUGIN_RESULT_OK;

    // For the first screen, display the plugin name.
    strlcpy(msg->name, "p2p.org", msg->nameLength);
    switch (context->selectorIndex) {
        case DO_DEPOSIT:
            strlcpy(msg->version, "Stake", msg->versionLength);
            break;
        case DO_WITHDRAW:
            strlcpy(msg->version, "Unstake", msg->versionLength);
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
