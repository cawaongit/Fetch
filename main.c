#include <arpa/inet.h>
#include <ifaddrs.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h>

#define ANSI_COLOR_BLACK "\x1b[30m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_WHITE "\x1b[37"
#define ANSI_COLOR_YELLOW "\x1b[33m"

void hostname() {
  // You can get hostname via /etc/hostname or /proc/sys/kernel/hostname
  char hostname[1024];
  gethostname(hostname, sizeof(hostname));
  printf("%s@%s\n", getlogin(), hostname);
}

void os() {
  // OS infos can be found in /etc/os-release
  FILE *file = fopen("/etc/os-release", "r");

  char line[256];

  if (file != NULL) {
    while (fgets(line, sizeof(line), file)) {
      printf("%s", line);
    }

    fclose(file);
  } else {
    fprintf(stderr, "Unable to read /etc/os-release");
  }

  printf("OS: %s\n");
}

void host() {
  // You can get the host product name into
  // /sys/devices/virtual/dmi/id/product_name
  printf("Host: %s\n");
}

void kernel() {
  struct utsname kernel;
  uname(&kernel);
  printf("Kernel: %s %s\n", kernel.sysname, kernel.release);
}

void uptime() {
  struct sysinfo uptime;
  sysinfo(&uptime);
  printf("Uptime: ");
  if (uptime.uptime >= 3600) {
    printf("%ld hours, ", uptime.uptime / 3600);
  }
  printf("%ld mins\n", uptime.uptime);
}

void packages() { printf("Packages: %s\n"); }

void shell() { printf("Shell: %s\n"); }

void display() {}

void wm() { printf("WM: (%s)\n", getenv("XDG_SESSION_TYPE")); }

void theme() { printf("Theme: %s\n"); }

void font() { printf("Font: %s\n"); }

void cursor() { printf("Cursor: %s\n"); }

void terminal() { printf("Terminal: %s\n"); }

void terminalFont() { printf("Terminal Font: %s\n"); }

void cpu() {
  // You can get the cpu infos with /proc/cpuinfo
  printf("CPU: %s\n");
}

void gpu() { printf("GPU: %s\n"); }

void memory() {
  // You can get the memory infos with sysinfo and /proc/meminfo
  struct sysinfo memory;
  sysinfo(&memory);
  printf("Memory: %ld GiB / %ld GiB ()\n", memory.totalhigh,
         memory.totalram / 1024 / 1024 / 1024);
}

void swap() { printf("Swap: %s\n"); }

void disk() { printf("Disk: %s\n"); }

void localIp() {
  struct ifaddrs *ifap, *ifa;
  struct sockaddr_in *sa;
  char *addr;

  getifaddrs(&ifap);
  for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) {
      sa = (struct sockaddr_in *)ifa->ifa_addr;
      addr = inet_ntoa(sa->sin_addr);
      printf("Local IP (%s): %s/%s\n", ifa->ifa_name, addr);
    }
  }

  freeifaddrs(ifap);
}

void battery() {
  // Only printed when used on laptop
  FILE *model_name_file = fopen("/sys/class/power_supply/BAT0/model_name", "r");
  char model_name[256];

  FILE *capacity_file = fopen("/sys/class/power_supply/BAT0/capacity", "r");
  char capacity[256];

  if (model_name_file != NULL) {
    while (fgets(model_name, sizeof(model_name), model_name_file)) {
      model_name[strcspn(model_name, "\n")] = '\0';
      printf("Battery (%s): ", model_name);
    }
  }

  if (capacity_file != NULL) {
    while (fgets(capacity, sizeof(capacity), capacity_file)) {
      capacity[strcspn(capacity, "\n")] = '\0';
      printf("%s%%\n", capacity);
    }
    fclose(capacity_file);
  } else {
    // fprintf(stderr, "Unable to read /etc/os-release");
  }
};

void locale() { printf("Locale: %s", setlocale(LC_ALL, "")); }

int main() {
  // printf(ANSI_COLOR_RED "F" ANSI_COLOR_RED);
  hostname();
  // os();
  host();
  kernel();
  uptime();
  packages();
  shell();
  display();
  wm();
  theme();
  font();
  cursor();
  terminal();
  terminalFont();
  cpu();
  gpu();
  memory();
  swap();
  disk();
  localIp();
  battery();
  locale();
  return 0;
}
