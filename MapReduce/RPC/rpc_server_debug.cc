#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#include "RPC.h"

int WriteServer(int sockfd) {
  const char* s = "this is response";
  write(sockfd, s, strlen(s));
  return 0;
}

int Echo(int sockfd, std::string& input) {
  std::cout << input << std::endl;
  std::cout << sockfd << std::endl;
  WriteServer(sockfd);
  return 0;
}

int main(int argc, char* argv[]) {
  npjh::RPC rpc_server(11994);
  rpc_server.RegisterEventHandler(&Echo, &WriteServer);
  rpc_server.StartServer();
  return 0;
}