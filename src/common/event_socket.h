// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2015 Haomai Wang <haomaiwang@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software
 * Foundation.  See file COPYING.
 *
 */

#ifndef CEPH_COMMON_EVENT_SOCKET_H
#define CEPH_COMMON_EVENT_SOCKET_H

#include "include/event_type.h"

class EventSocket {
  int socket;
  int type;

 public:
  EventSocket(): socket(-1), type(EVENT_SOCKET_TYPE_NONE) {}
  bool is_valid() const { return socket != -1; }
  int init(int fd, int t) {
#ifdef HAVE_EVENTFD
    if (t == EVENT_SOCKET_TYPE_EVENTFD) {
      socket = fd;
      type = t;
      return 0;
    }
#endif
    return -1;
  }
  int notify() {
    switch (type) {
      case EVENT_SOCKET_TYPE_EVENTFD:
      {
        uint64_t value = 1;
        return write(socket, &value, sizeof (value));
      }
      default:
      {
        return -1;
      }
    }
  }
};

#endif
