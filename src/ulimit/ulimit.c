#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

void print_limit(int resource, char *name) {
  struct rlimit limit;
  if (getrlimit(resource, &limit) == -1) {
    perror("getrlimit");
    exit(EXIT_FAILURE);
  }
  printf("%s: ", name);
  if (limit.rlim_cur == RLIM_INFINITY) {
    printf("unlimited\n");
  } else {
    printf("%ld\n", limit.rlim_cur);
  }
}

// A function to set the limit of a resource
void set_limit(int resource, char *name, long value) {
  struct rlimit limit;
  limit.rlim_cur = value;
  limit.rlim_max = value;
  if (setrlimit(resource, &limit) == -1) {
    perror("byteshell: setrlimit");
  }
  printf("Set %s to %ld\n", name, value);
}

void show_all_limits() {
  print_limit(RLIMIT_CPU, "cpu time");
  print_limit(RLIMIT_FSIZE, "file size");
  print_limit(RLIMIT_DATA, "data seg size");
  print_limit(RLIMIT_STACK, "stack size");
  print_limit(RLIMIT_CORE, "core file size");
  print_limit(RLIMIT_NOFILE, "max file descriptors");
  print_limit(RLIMIT_AS, "address space limit");
}

void show_limit(char option) {
  switch (option) {
    case 't':
      print_limit(RLIMIT_CPU, "cpu time");
      break;
    case 'f':
      print_limit(RLIMIT_FSIZE, "file size");
      break;
    case 'd':
      print_limit(RLIMIT_DATA, "data seg size");
      break;
    case 's':
      print_limit(RLIMIT_STACK, "stack size");
      break;
    case 'c':
      print_limit(RLIMIT_CORE, "core file size");
      break;
    case 'n':
      print_limit(RLIMIT_NOFILE, "max file descriptors");
      break;
    case 'v':
      print_limit(RLIMIT_AS, "address space limit");
      break;
    default:
      fprintf(stderr, "Unknown option: %c\n", option);
  }
}

void set_limit_option(char option, long value) {
  switch (option) {
    case 't':
      set_limit(RLIMIT_CPU, "cpu time", value);
      break;
    case 'f':
      set_limit(RLIMIT_FSIZE, "file size", value);
      break;
    case 'd':
      set_limit(RLIMIT_DATA, "data seg size", value);
      break;
    case 's':
      set_limit(RLIMIT_STACK, "stack size", value);
      break;
    case 'c':
      set_limit(RLIMIT_CORE, "core file size", value);
      break;
    case 'n':
      set_limit(RLIMIT_NOFILE, "max file descriptors", value);
      break;
    case 'v':
      set_limit(RLIMIT_AS, "address space limit", value);
      break;
    default:
      fprintf(stderr, "Unknown option: %c\n", option);
  }
}