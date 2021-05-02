#include <string>
#include "lentext.h"

LengthTextBuffer::LengthTextBuffer(int max_bytes) {
  init(max_bytes);
}

void LengthTextBuffer::clear() {
  next_byte = 0;
  buffer_size = 0;
}

int LengthTextBuffer::read(istream& stream) {
  clear();
  stream.read(&buffer_size, sizeof(buffer_size));
  if (stream.fail())
    return FALSE;
  if (buffer_size > max_bytes)
    return FALSE;
  stream.read(buffer, buffer_size);
  return stream.good();
}

int LengthTextBuffer::write(ostream& stream) const {
  stream.write(&buffer_size, sizeof(buffer_size));
  stream.write(buffer, buffer_size);
  return stream.good();
}

int LengthTextBuffer::pack(const char *str, short size) {
  short len;
  if (size >= 0)
    len = size;
  else
    len = strlen(str);
  if (len > strlen(str))
    return FALSE;
  int start = next_byte;
  next_byte += (len + sizeof(len));
  if (next_byte > max_bytes)
    return FALSE;
  memcpy(&buffer[start], &len, sizeof(len));
  strncpy(&buffer[start+sizeof(len)], str, len);
  buffer_size = next_byte;
  return TRUE;
}

int LengthTextBuffer::unpack(char *str) {
  short len;
  if (next_byte >= buffer_size)
    return FALSE;
  int start = next_byte;
  memcpy(&len, &Buffer[start], sizeof(short));
  next_byte += len + sizeof(short);
  if (next_byte > buffer_size)
    return FALSE;
  strncpy(str, &buffer[start+sizeof(short)], len);
  str[len] = 0;
  return TRUE;
}

void LengthTextBuffer::print(ostream& stream) const {
  stream << "Buffer has characters " << max_bytes << " and Buffer size " << buffer_size << endl;
}

LengthTextBuffer::init(int max_bytes) {
  if (max_bytes < 0)
    max_bytes = 0;
  MAX_BYTES = max_bytes;
  buffer = new char[MAX_BYTES];
  clear();
}
