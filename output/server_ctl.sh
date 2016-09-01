#!/bin/bash

ROOT_PATH=$(pwd)
SERVER=$ROOT_PATH/udp_server
CONF=$ROOT_PATH/server.conf
IP=''
PORT=''

function init()
{
	IP=$(grep -iE '^SERVER_IP' $CONF | awk -F : '{print $NF}')
    PORT=$(grep -iE '^SERVER_PORT' $CONF | awk -F : '{print $NF}')
}

function main()
{
	init
	$SERVER "$IP" "$PORT"
}

main
