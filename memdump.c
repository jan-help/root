#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void memdump(char *fmt, char *data, int len);

int
main(int argc, char *argv[])
{
  if (argc == 2) {
    char data[512];
    int n = 0;

    memset(data, '\0', sizeof(data));

    while (n < sizeof(data)) {
      int nn = read(0, data + n, sizeof(data) - n);

      if (nn <= 0)
        break;

      n += nn;
    }

    memdump(argv[1], data, n);
  } else {
    printf("Usage: memdump [format]\n");
    exit(1);
  }

  exit(0);
}

void
memdump(char *fmt, char *data, int len)
{
  for (int j = 0; fmt[j] != '\0'; j++) {
    char format = fmt[j];

    if (format == 'S') {
      while (len > 0 && *data != '\0') {
        printf("%c", *data);
        data++;
        len--;
      }
      printf("\n");
      return;
    }

    int required;

    if (format == 'i') {
      required = 4;
    } else if (format == 'p' || format == 's') {
      required = 8;
    } else if (format == 'h') {
      required = 2;
    } else if (format == 'c') {
      required = 1;
    } else {
      printf("memdump: unsupported format '%c'\n", format);
      return;
    }

    if (len < required) {
      printf("memdump: not enough data for '%c'\n", format);
      return;
    }

    if (format == 'i') {
      int value;
      memmove(&value, data, required);
      printf("%d\n", value);
    } else if (format == 'p') {
      uint64 value;
      memmove(&value, data, required);
      printf("%lx\n", value);
    } else if (format == 'h') {
      short value;
      memmove(&value, data, required);
      printf("%d\n", (int)value);
    } else if (format == 'c') {
      printf("%c\n", *data);
    } else if (format == 's') {
      char *string;
      memmove(&string, data, required);
      printf("%s\n", string);
    }

    data += required;
    len -= required;
  }
}