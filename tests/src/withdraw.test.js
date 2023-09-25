import "core-js/stable";
import "regenerator-runtime/runtime";
import { ledgerService } from "@ledgerhq/hw-app-eth";
import {
  waitForAppScreen,
  zemu,
  txFromEtherscan,
  MODELS,
  WITHDRAW_TX_DATA,
} from "./test.fixture";
import { ethers } from "ethers";

const contractAddr = "0x4e1224f513048e18e7a1883985b45dc0fe1d917e";
const pluginName = "p2p-staking";
const testNetwork = "ethereum";
const abi_path =
  `../networks/${testNetwork}/${pluginName}/abis/` + contractAddr + ".json";
const abi = require(abi_path);

MODELS.forEach((model) => {
  jest.setTimeout(20000);
  test(
    "[Nano " + model.letter + "] Withdraw stake",
    zemu(model, async (sim, eth) => {
      const contract = new ethers.Contract(contractAddr, abi);
      void contract;

      const serializedTx = txFromEtherscan(WITHDRAW_TX_DATA);
      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === 'S' ? 6 : 4;

      await waitForAppScreen(sim);
      await sim.navigateAndCompareSnapshots(".", `${model.name}_withdraw`, [
        right_clicks,
        0,
      ]);

      await tx;
    })
  );
});
