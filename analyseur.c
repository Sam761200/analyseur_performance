#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Déclaration des fonctions
void print_cpu_usage();
void print_memory_usage();
void print_disk_activity();
void print_network_usage();

int main()
{
    printf("Performance System Analyzer\n");

    while (1)
    {
        print_cpu_usage();
        print_memory_usage();
        print_disk_activity();
        print_network_usage();

        sleep(1);        // Pause d'une seconde entre chaque mesure
        system("clear"); // Nettoie la console pour la prochaine mesure
    }

    return 0;
}

void print_cpu_usage()
{
    FILE *file;
    char buffer[256];
    unsigned long long int user, nice, system, idle, iowait, irq, softirq;

    file = fopen("/proc/stat", "r");
    if (file == NULL)
    {
        perror("Failed to open /proc/stat");
        return;
    }

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "cpu  %llu %llu %llu %llu %llu %llu %llu", &user, &nice, &system, &idle, &iowait, &irq, &softirq);
    fclose(file);

    unsigned long long int total_idle = idle + iowait;
    unsigned long long int total_non_idle = user + nice + system + irq + softirq;
    unsigned long long int total = total_idle + total_non_idle;

    static unsigned long long int prev_total = 0, prev_idle = 0;
    double cpu_percentage = 0.0;

    if (prev_total != 0)
    {
        double total_d = total - prev_total;
        double idle_d = total_idle - prev_idle;
        cpu_percentage = (total_d - idle_d) / total_d * 100.0;
    }

    printf("CPU Usage: %.2f%%\n", cpu_percentage);

    prev_total = total;
    prev_idle = total_idle;
}

void print_memory_usage()
{
    FILE *file;
    char line[256];
    unsigned long total_memory = 0;
    unsigned long free_memory = 0;
    unsigned long available_memory = 0;
    unsigned long buffers = 0;
    unsigned long cached = 0;

    file = fopen("/proc/meminfo", "r");
    if (file == NULL)
    {
        perror("Failed to open /proc/meminfo");
        return;
    }

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "MemTotal: %lu kB", &total_memory);
        sscanf(line, "MemFree: %lu kB", &free_memory);
        sscanf(line, "MemAvailable: %lu kB", &available_memory);
        sscanf(line, "Buffers: %lu kB", &buffers);
        sscanf(line, "Cached: %lu kB", &cached);
    }
    fclose(file);

    unsigned long used_memory = total_memory - free_memory - buffers - cached;
    double memory_usage_percentage = (double)used_memory / total_memory * 100.0;

    printf("Memory Usage: Total: %lu kB, Used: %lu kB (%.2f%%)\n", total_memory, used_memory, memory_usage_percentage);
}

void print_disk_activity()
{
    FILE *file;
    char line[256];
    char device[32];
    unsigned long reads, writes;

    file = fopen("/proc/diskstats", "r");
    if (file == NULL)
    {
        perror("Failed to open /proc/diskstats");
        return;
    }

    printf("Disk Activity:\n");
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "   8       0 %s %*d %*d %lu %*d %*d %*d %lu %*d %*d %*d %*d", device, &reads, &writes) == 3)
        {
            printf("Device: %s, Reads: %lu, Writes: %lu\n", device, reads, writes);
        }
    }
    fclose(file);
}

void print_network_usage()
{
    FILE *file;
    char line[1024];
    char interface[20];
    unsigned long long int rx_bytes, tx_bytes;

    file = fopen("/proc/net/dev", "r");
    if (file == NULL)
    {
        perror("Failed to open /proc/net/dev");
        return;
    }

    fgets(line, sizeof(line), file); // Lire les en-têtes
    fgets(line, sizeof(line), file); // Ignorer la seconde ligne d'en-têtes

    printf("Network Usage:\n");
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%[^:]: %llu %*d %*d %*d %*d %*d %*d %*d %llu", interface, &rx_bytes, &tx_bytes) == 3)
        {
            printf("%s: Received: %llu bytes, Transmitted: %llu bytes\n", interface, rx_bytes, tx_bytes);
        }
    }
    fclose(file);
}
