#include <iostream.h>

class FixedTextBuffer {
public:
  FixedTextBuffer(int max_fields, int max_chars=1000);
  FixedTextBuffer(int num_fields, int *field_size);

  int number_of_fields() const;
  void clear();
  int add_field(int field_size);
  int read(istream&);
  int write(ostream&);
  int pack(const char *);
  int unpack(char *);
  void print(ostream&);
  int init(int num_fields, int max_chars=1000);
  int init(int num_fields, int *field_size);

private:
  char *buffer;
  int buffer_size;
  int *field_size;
  int max_fields;
  int max_chars;
  int num_fields;
  int next_field;
  int num_field_values;
  int packing;
  int next_character;
};
