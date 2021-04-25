#ifndef NPJH_MAPREDUCE_RPC_RPC_H_
#define NPJH_MAPREDUCE_RPC_RPC_H_

#include <string>

namespace npjh {

typedef int (*on_input_event)(int sockfd, std::string& input);
typedef int (*on_output_event)(int sockfd);

class RPC {
 public:
  RPC(int port);
  ~RPC() {}
  void RegisterEventHandler(on_input_event input_handler,
                            on_output_event output_handler) {
    on_input_event_handler_ = input_handler;
    on_output_event_handler_ = output_handler;
  }

  // Server
  int StartServer();

  // Client
  int IssueRPCRequest(const char* ip, int port);

 private:
  int epfd_, sockfd_;

  on_input_event on_input_event_handler_;
  on_output_event on_output_event_handler_;

  const int MAX_EVENTS = 1024;
  const int MAXLINE = 1024;
  const int LISTENQ = 10;

  int setnonblocking(int fd);
};

}  // namespace npjh

#endif
