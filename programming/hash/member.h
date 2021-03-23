#ifndef __Member
#define __Member

typedef struct {
  int no;
  char name[20];
} Member;

#define MEMBER_NO 1
#define MEMBER_NAME 2

int member_no_cmp(const Member *x, const Member *y);

int member_name_cmp(const Member *x, const Member *y);

void print_member(const Member *x);

void print_ln_member(const Member *x);

Member scan_member(const char *message, int sw);

#endif
