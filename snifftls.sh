#!/bin/bash

echo "Starting TLS SNI sniffing on wlan0..."
/usr/bin/sudo /usr/bin/tshark -i wlan0 -Y "tls.handshake.extensions_server_name" -T fields -e tls.handshake.extensions_server_name
