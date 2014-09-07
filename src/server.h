char connection_headers[5][256] = {
  {"GET / HTTP/1.1 200 OK\r\n"},
  {"Transfer-Encoding: chunked\r\n"},
  {"Server: https://github.com/tomasperezv/web-server-c\r\n"},
  {"Connection:close\r\n"},
  {"Content-Type:text/html; charset=UTF-8\r\n"}
};
