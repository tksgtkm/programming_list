
#include "util.h"

const unsigned char *print_name(const unsigned char *msg, const unsigned char *p, const unsigned char *end) {

  if (p + 2 > end) {
    fprintf(stderr, "End of message.\n");
    exit(1);
  }

  if ((*p & 0xC0) == 0xC0) {
    const int k = ((*p & 0x3F) << 8) + p[1];
    
  }
}
