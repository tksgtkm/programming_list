
#include "util.h"

const char *get_content_type(const char* path) {
  const char *last_dot = strchr(path, '.');
  if (last_dot) {
    if (strcmp(last_dot, ".css") == 0) return "text/css";
    if (strcmp(last_dot, ".csv") == 0) return "text/csv";
    if (strcmp(last_dot, ".gif") == 0) return "image/gif";
    if (strcmp(last_dot, ".htm") == 0) return "text/html";
    if (strcmp(last_dot, ".html") == 0) return "text/html";
    if (strcmp(last_dot, ".ico") == 0) return "image/x-icon";
    if (strcmp(last_dot, ".jpeg") == 0) return "image/jpeg";
    if (strcmp(last_dot, ".jpg") == 0) return "image/jpeg";
    if (strcmp(last_dot, ".js") == 0) return "application/javascript";
    if (strcmp(last_dot, ".json") == 0) return "application/json";
    if (strcmp(last_dot, ".png") == 0) return "image/png";
    if (strcmp(last_dot, ".pdf") == 0) return "application/pdf";
    if (strcmp(last_dot, ".svg") == 0) return "image/svg+xml";
    if (strcmp(last_dot, ".txt") == 0) return "text/plain";
  }
  return "application/octet-stream";
}

SOCKET create_socket(const char* host, const char *port) {
  printf("Configuring local address...\n");
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo *bind_address;
  getaddrinfo(host, port, &hints, &bind_address);

  printf("Creating socket...\n");
  SOCKET socket_listen;
  socket_listen = socket(bind_adderss->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
  
}
