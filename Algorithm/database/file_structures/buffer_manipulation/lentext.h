#include <iostream>

class LengthTextBuffer {
public:
  LengthTextBuffer(int max_bytes = 1000);
  void clear();
  int read(istream&);
  int write(ostream&);
  int pack(const char *, short size = -1);
  int unpack(char *);
  void print(char *);
  int init(int max_bytes = 1000);
private:
  char *buffer;
  int buffer_size;
  int MAX_BYTES;
  int next_byte;
};
