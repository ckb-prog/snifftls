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
