#include "p2p_staking.h"

static void handle_deposit_ui_preview(ethQueryContractUI_t *msg, context_t *context) {
    (void) context;
    strlcpy(msg->title, "Stake", msg->titleLength);

    const uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
    uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;

    amountToString(eth_amount, eth_amount_size, WEI_TO_ETHER, "ETH", msg->msg, msg->msgLength);
}

static void handle_deposit_ui(ethQueryContractUI_t *msg, context_t *context) {
    msg->result = ETH_PLUGIN_RESULT_OK;
    switch (msg->screenIndex) {
        case 0:
            handle_deposit_ui_preview(msg, context);
            break;

        default:
            PRINTF("Received a screen index out of bounds: %d", msg->screenIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_withdraw_ui_preview(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Unstake", msg->titleLength);

    strlcpy(msg->msg, "ETH", msg->msgLength);
}

static void handle_withdraw_ui(ethQueryContractUI_t *msg, context_t *context) {
    msg->result = ETH_PLUGIN_RESULT_OK;
    switch (msg->screenIndex) {
        case 0:
            handle_withdraw_ui_preview(msg, context);
            break;

        default:
            PRINTF("Received a screen index out of bounds: %d", msg->screenIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case DO_DEPOSIT:
            handle_deposit_ui(msg, context);
            break;
        case DO_WITHDRAW:
            handle_withdraw_ui(msg, context);
            break;
        // Keep this
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
}
