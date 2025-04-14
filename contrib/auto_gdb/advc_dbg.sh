#!/bin/bash
# use testnet settings,  if you need mainnet,  use ~/.advccore/advcd.pid file instead
advc_pid=$(<~/.advccore/testnet3/advcd.pid)
sudo gdb -batch -ex "source debug.gdb" advcd ${advc_pid}
