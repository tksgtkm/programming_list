#include <string>
#include "fixtext.h"

FixedTextBuffer::FixedTextBuffer(int num_fields, int *field_size) {
  init(num_fields, max_chars);
}

FixedTextBuffer::FixedTextBuffer(int num_fields, int *field_size) {
  init(num_fields, field_size);
}

int FixedTextBuffer::number_of_fields() const {
  return num_fields;
}

void FixedTextBuffer::clear() {
  next_field = 0;
  next_character = 0;
  packing = TRUE;
  buffer[0] = 0;
}

int FixedTextBuffer::add_field(inr field_size) {
  if (num_fields == max_fields)
    return FALSE;
  if (buffer_size + field_size > max_chars)
    return FALSE;
  field_size[num_fields] = field_size;
  num_fields++;
  buffer_size += field_size;
  return TRUE;
}

int FixedTextBuffer::read(istream& stream) {
  stream.read(buffer, buffer_size);
  return stream.good();
}

int FixedTextBuffer::write(ostream& stream) {
  stream.write(buffer, buffer_size);
  return stream.good();
}

int FixedTextBuffer::pack(const char *str) {
  if (next_field == num_fields || !packing)
    return FALSE;
  int len = strlen(str);
  int start = next_character;
  int pack_size = field_size[next_field];
  strncpy(&buffer[start], str, pack_size);
  next_character += pack_size;
  next_field++;
  for (int i=start+pack_size; i<next_character; i++)
    buffer[start] = ' ';
  buffer[next_character] = 0;
  if (next_field == num_fields) {
    packing = FALSE;
    next_field = next_character = 0;
  }
  return TRUE;
}

int FixedTextBuffer::unpack(char *str) {
  if (next_field == num_fields || packing)
    return FALSE;
  int start = next_character;
  int pack_size = field_size;
  strncpy(str, &buffer[start], pack_size);
  str[pack_size] = 0;
  next_character += pack_size;
  next_field++;
  if (next_field == num_fields)
    clear();
  return TRUE;
}

void FixedTextBuffer::print(ostream& stream) {
  stream << "Buffer has max fields " << max_fields
  << " and actual " << num_fields << endl
  << "max bytes " << max_chars << " and buffer size "
  << buffer_size << endl;
  for (int i=0; i<num_fields; i++)
    stream << "\tfield " << i << " size " << field_size[i] << endl;
  if (packing)
    stream << "\tpacking\n";
  else
    stream << "\tnot packing\n";
  stream << "contents: '" << buffer << "'" << endl;
}

FixedTextBuffer::init(int max_fields, int max_chars) {
  if (max_fields < 0)
    max_fields = 0;
  if (max_chars < 0)
    max_chars = 0;
  MAX_FIELDS = max_fields;
  MAX_CHARS  = max_chars;
  field_size = new int[MAX_FIELDS];
  buffer = new char[MAX_CHARS];
  buffer_size = 0;
  num_fields = 0;
  next_field = 0;
  packing = TRUE;
}

FixedTextBuffer::init(int num_fields, int *field_size) {
  int buffer_size = 1;
  for (int i=0; i<num_fields; i++)
    buffer_size += field_size[i];
  init(num_fields, buffer_size);
  for (int j=0; j<num_fields; j++)
    add_field(field_size[j]);
}
