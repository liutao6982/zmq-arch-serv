// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#ifndef __ZMQ_TOOL_HPP__
#define __ZMQ_TOOL_HPP__

char* zmq_new_string(const std::string& str, size_t& len)
{
	len = str.length();
	char *_string_copy = new char[len + 1];
	memcpy(_string_copy, str.c_str(), len);
	_string_copy[len] = 0;
	len++;
	return _string_copy;
}

void zmq_free(void *data, void *hint)
{
	delete[] (char *)data;
}
#endif