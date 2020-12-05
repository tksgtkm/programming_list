
#include "util.h"

const unsigned char *print_name(const unsigned char *msg, const unsigned char *p, const unsigned char *end) {

  if (p + 2 > end) {
    fprintf(stderr, "End of message.\n");
    exit(1);
  }

  if ((*p & 0xC0) == 0xC0) {
    const int k = ((*p & 0x3F) << 8) + p[1];
    p += 2;
    printf(" (pointer %d) ", k);
    print_name(msg, msg+k, end);
    return p;
  } else {
    const int len = *p++;
    if (p + len + 1 > end) {
      fprintf(stderr, "End of message.\n");
      exit(1);
    }
    printf("%.*s", len, p);
    p += len;
    if (*p) {
      printf(".");
      return print_name(msg, p, end);
    } else {
      return p+1;
    }
  }
}

void print_dns_message(const char *message, int msg_length) {

  if (msg_length < 12) {
    fprintf(stderr, "Message is too short to be valid.\n");
    exit(1);
  }

  const unsigned char *msg = (const unsigned char *)message;

  printf("ID = %0X %0X\n", msg[0], msg[1]);

  const int qr = (msg[2] & 0x80) >> 7;
  printf("QR = %d %s\n", qr, qr ? "response" : "query");

  const int opcode = (msg[2] & 0x78) >> 3;
  printf("QPCODE = %d ", opcode);
  switch(opcode) {
    case 0: printf("standard\n"); break;
    case 1: printf("reverse\n"); break;
    case 2: printf("status\n",); break;
    default printf("?\n"); break;
  }

  const int aa = (msg[2] & 0x04) >> 2;
  printf("AA = %d %s\n", aa, aa ? "authoritative" : "");

  const int tc = (msg[2] & 0x02) >> 1;
  printf("TC = %d %s\n", tc, tc ? "message truncated" : "");

  const int rd = (msg[2] & 0x01);
  printf("RD = %d %s\n", rd, rd ? "recursion desired" : "");

  if (qr) {
    const int rcode = msg[3] & 0x07;
    printf("RCODE = %d ", rcode);
    switch(rcode) {
      case 0: printf("success\n"); break;
      case 1: printf("format error\n"); break;
      case 2: printf("server failure\n"); break;
      case 3: printf("name error\n"); break;
      case 4: printf("not implemented\n"); break;
      case 5: printf("refused\n"); break;
    }
    if (rcode != 0) return;
  }

  const int qdcount = (msg[4] << 8) + msg[5];
  const int ancount = (msg[6] << 8) + msg[7];
  const int nscount = (msg[8] << 8) + msg[9];
  const int arcount = (msg[10] << 8) + msg[11];

  printf("QDCOUNT = %d\n", qdcount);
  printf("ANCOUNT = %d\n", ancount);
  printf("NSCOUNT = %d\n", nscount);
  printf("ARCOUNT = %d\n", arcount);

  
}
