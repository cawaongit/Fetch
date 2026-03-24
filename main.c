#include <arpa/inet.h>
#include <ifaddrs.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
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

void os() {}

void host() {
  // You can get the host product name into
  // /sys/devices/virtual/dmi/id/product_name
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

void packages() {}

void shell() {}

void display() {}

void wm() { printf("WM: (%s)\n", getenv("XDG_SESSION_TYPE")); }

void theme() {}

void font() {}

void cursor() {}

void terminal() {}

void terminalFont() {}

void cpu() {
  // You can get the cpu infos with /proc/cpuinfo
}

void gpu() {}

void memory() {
  // You can get the memory infos with sysinfo and /proc/meminfo
  struct sysinfo memory;
  sysinfo(&memory);
  printf("Memory: %ld GiB / %ld GiB ()\n", memory.totalhigh,
         memory.totalram / 1024 / 1024 / 1024);
}

void swap() {}

void disk() {}

void localIp() {
  struct ifaddrs *ifap, *ifa;
  struct sockaddr_in *sa;
  char *addr;

  getifaddrs(&ifap);
  for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) {
      sa = (struct sockaddr_in *)ifa->ifa_addr;
      addr = inet_ntoa(sa->sin_addr);
      printf("Local IP (%s): %s\n", ifa->ifa_name, addr);
    }
  }

  freeifaddrs(ifap);
}

void locale() { printf("Locale: %s", setlocale(LC_ALL, "")); }

int main() {
  // printf(ANSI_COLOR_RED "F" ANSI_COLOR_RED);
  hostname();
  os();
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
  locale();
  return 0;
}
