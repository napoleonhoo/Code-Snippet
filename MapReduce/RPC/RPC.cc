#include "RPC.h"

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "Common/Log.h"

namespace npjh {

RPC::RPC(int port) {
  epfd_ = epoll_create(1024);
  sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in localaddr;
  bzero(&localaddr, sizeof(localaddr));
  localaddr.sin_family = AF_INET;
  const char *local_addr = "127.0.0.1";
  inet_aton(local_addr, &(localaddr.sin_addr));
  localaddr.sin_port = htons(port);
  bind(sockfd_, (struct sockaddr *)&localaddr, sizeof(localaddr));
  // setnonblocking(sockfd_);
};

int RPC::StartServer() {
  listen(sockfd_, LISTENQ);
  struct epoll_event ev;
  ev.data.fd = sockfd_;
  ev.events = EPOLLIN | EPOLLET;
  epoll_ctl(epfd_, EPOLL_CTL_ADD, sockfd_, &ev);
  struct epoll_event events[20];

  while (true) {
    int nfds = epoll_wait(epfd_, events, 20, 500);

    for (int i = 0; i < nfds; ++i) {
      if (events[i].data.fd == sockfd_) {
        socklen_t clilen;
        struct sockaddr_in clientaddr;
        int connfd = accept(sockfd_, (struct sockaddr *)&clientaddr, &clilen);
        if (connfd < 0) {
          return -2;
        }
        // setnonblocking(connfd);
        char *str = inet_ntoa(clientaddr.sin_addr);
        ev.data.fd = connfd;
        ev.events = EPOLLIN | EPOLLET;
        epoll_ctl(epfd_, EPOLL_CTL_ADD, connfd, &ev);
        LOG_DEBUG("accept\n");

      } else if (events[i].events & EPOLLIN) {
        int infd;
        if ((infd = events[i].data.fd) < 0) continue;
        // while (true) {
        char line[MAXLINE];
        ssize_t n = read(infd, line, MAXLINE);
        if (n < 0) {
          if (errno == ECONNRESET) {
            close(infd);
            events[i].data.fd = -1;
          } else {
            close(infd);
          }
          continue;
        } else if (n == 0) {
          close(infd);
          events[i].data.fd = -1;
          continue;
        }
        line[n] = '\n';
        std::string input(line, n + 1);
        on_input_event_handler_(infd, input);
        // }
        ev.data.fd = infd;
        ev.events = EPOLLOUT | EPOLLET;
      } else if (events[i].events & EPOLLOUT) {
        int outfd = events[i].data.fd;
        // write(sockfd, line, n);
        on_output_event_handler_(outfd);
        ev.data.fd = outfd;
        ev.events = EPOLLIN | EPOLLET;
        epoll_ctl(epfd_, EPOLL_CTL_MOD, outfd, &ev);
      } else if ((events[i].events & EPOLLERR) ||
                 (events[i].events & EPOLLHUP)) {
        close(sockfd_);
      } else if (events[i].events & EPOLLRDHUP) {
        close(sockfd_);
      }
    }
  }
  return 0;
}

int RPC::IssueRPCRequest(const char *ip, int port) {
  struct sockaddr_in serveraddr;
  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  const char *server_addr = ip;
  inet_aton(server_addr, &(serveraddr.sin_addr));
  serveraddr.sin_port = htons(port);
  if (0 !=
      connect(sockfd_, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) {
    LOG_DEBUG("connect failed, %s.\n", strerror(errno));
    return -1;
  }

  struct epoll_event ev;
  ev.data.fd = sockfd_;
  ev.events = EPOLLIN | EPOLLET;
  epoll_ctl(epfd_, EPOLL_CTL_ADD, sockfd_, &ev);
  struct epoll_event events[20];

  on_output_event_handler_(sockfd_);

  while (true) {
    int nfds = epoll_wait(epfd_, events, 20, 500);

    for (int i = 0; i < nfds; ++i) {
      if (events[i].events & EPOLLIN) {
        int infd;
        if ((infd = events[i].data.fd) < 0) continue;
        // while (true) {
        char line[MAXLINE];
        ssize_t n = read(infd, line, MAXLINE);
        if (n < 0) {
          if (errno == ECONNRESET) {
            close(infd);
            events[i].data.fd = -1;
          } else {
          }
        } else if (n == 0) {
          close(infd);
          events[i].data.fd = -1;
        }
        line[n] = '\n';
        std::string input(line, n + 1);
        on_input_event_handler_(infd, input);
        // }
        ev.data.fd = infd;
        ev.events = EPOLLOUT | EPOLLET;
      } else if (events[i].events & EPOLLOUT) {
        int outfd = events[i].data.fd;
        // write(sockfd, line, n);
        on_output_event_handler_(outfd);
        ev.data.fd = outfd;
        ev.events = EPOLLIN | EPOLLET;
        epoll_ctl(epfd_, EPOLL_CTL_MOD, outfd, &ev);
      } else if ((events[i].events & EPOLLERR) ||
                 (events[i].events & EPOLLHUP)) {
        close(sockfd_);
      } else if (events[i].events & EPOLLRDHUP) {
        close(sockfd_);
      }
    }
  }
  return 0;
}

int RPC::setnonblocking(int fd) {
  int flags = fcntl(fd, F_GETFL, 0);
  if (flags < 0) {
    return -1;
  }
  int r = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  if (r < 0) {
    return -2;
  }
  return 0;
}

}  // namespace npjh