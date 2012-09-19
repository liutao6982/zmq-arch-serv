// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#ifndef __ZMQ__MESSAGE_HPP__
#define __ZMQ__MESSAGE_HPP__

#include <iostream>

class message
{
public:
  enum { header_length = 4 };
  enum { max_body_length = 512 };

  message()
    : body_length_(0)
  {
	  bzero();
  }

  const char* data() const
  {
    return data_;
  }

  char* data()
  {
    return data_;
  }

  size_t length() const
  {
    return header_length + body_length_;
  }

  const char* body() const
  {
    return data_ + header_length;
  }

  char* body()
  {
    return data_ + header_length;
  }

  size_t body_length() const
  {
    return body_length_;
  }

  void body_length(size_t length)
  {
    body_length_ = length;
    if (body_length_ > max_body_length)
      body_length_ = max_body_length;
  }

  bool decode_header()
  {
    using namespace std; // For strncat and atoi.
    char header[header_length + 1] = "";
#ifdef _WIN32
#pragma   warning(disable   :   4996)
#endif
    strncat(header, data_, header_length);
    body_length_ = atoi(header);
    if (body_length_ > max_body_length)
    {
      body_length_ = 0;
      return false;
    }
    return true;
  }

  void encode_header()
  {
    using namespace std; // For sprintf and memcpy.
    char header[header_length + 1] = "";
    sprintf_s(header, "%4d", body_length_);
    memcpy(data_, header, header_length);
  }

  void bzero()
  {
	  memset(data_, 0, header_length + max_body_length);
  }

private:
  char data_[header_length + max_body_length];
  size_t body_length_;
};

#endif // MESSAGE_HPP
