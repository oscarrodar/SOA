#ifndef FILE_COMMON_H
#define FILE_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "network.h"

// Error handling prototypes
void unix_error(char *msg);

int Open_listenfd(int port);

int Accept(int s, struct sockaddr *addr, socklen_t *addrlen);

void Close(int fd);

size_t getline_from_fd(const int fd, char *t, size_t maxlen);

#endif /* !FILE_COMMON_H ! */
