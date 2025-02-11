#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define INTERFACE "wlan1"  // Change this if your adapter is different
#define MONITOR_INTERFACE "wlan1mon"
#define LOG_FILE "snifftls.log"

// Function to execute shell commands
void run_command(const char *cmd) {
    printf("[*] Executing: %s\n", cmd);
    int status = system(cmd);
    if (status == -1) {
        perror("system command failed");
        exit(1);
    }
}

// Cleanup function when exiting
void cleanup(int sig) {
    printf("\n[*] Stopping sniffing and restoring WiFi mode...\n");
    char restore_cmd[128];
    snprintf(restore_cmd, sizeof(restore_cmd), "sudo airmon-ng stop %s", MONITOR_INTERFACE);
    run_command(restore_cmd);
    printf("[*] Exiting...\n");
    exit(0);
}

int main() {
    printf("[*] Enabling monitor mode on %s...\n", INTERFACE);
    char start_mon_cmd[128];
    snprintf(start_mon_cmd, sizeof(start_mon_cmd), "sudo airmon-ng start %s", INTERFACE);
    run_command(start_mon_cmd);

    printf("[*] Starting TLS SNI sniffing on %s...\n", MONITOR_INTERFACE);
    char sniff_cmd[256];
    snprintf(sniff_cmd, sizeof(sniff_cmd),
             "sudo tshark -i %s -Y \"tls.handshake.extensions_server_name\" -T fields -e tls.handshake.extensions_server_name | tee -a %s",
             MONITOR_INTERFACE, LOG_FILE);

    // Handle CTRL+C to restore WiFi mode on exit
    signal(SIGINT, cleanup);

    // Run sniffing command
    run_command(sniff_cmd);

    return 0;
}
