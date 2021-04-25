#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#include "RPC.h"

int Echo(int sockfd, std::string& input) {
  std::cout << input << std::endl;
  std::cout << sockfd << std::endl;
  return 0;
}
int WriteServer(int sockfd) {
  const char* s = "this is a request";
  write(sockfd, s, strlen(s));
  return 0;
}

int main(int argc, char* argv[]) {
  npjh::RPC rpc_client(11995);
  rpc_client.RegisterEventHandler(&Echo, &WriteServer);
  rpc_client.IssueRPCRequest("127.0.0.1", 11994);
  return 0;
}