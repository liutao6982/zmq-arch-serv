// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)

#include "ZmqConnectionPool.hpp"

ZmqConnectionPool::ZmqConnectionPool(zmq::context_t& context, size_t size, char* server)
	: _context(context)
{
	char connect_string[256];
	sprintf_s(connect_string, "tcp://%s:5559", server);

	for (size_t i = 0; i < size ; i++)
	{
		ZmqConnectionPtr zmq_connection_ptr(new zmq::socket_t(context, ZMQ_REQ));
		zmq_connection_ptr->connect(connect_string);
		zmq_connection_queue.push(zmq_connection_ptr);
	}
}

bool ZmqConnectionPool::newConection(ZmqConnectionPtr& zmq_connection_ptr)
{
	if (!zmq_connection_queue.empty())
	{
		zmq_connection_ptr = zmq_connection_queue.front();
		zmq_connection_queue.pop();
		return true;
	}
	return false;
}

void ZmqConnectionPool::releaseConection(ZmqConnectionPtr zmq_connection_ptr)
{
	zmq_connection_queue.push(zmq_connection_ptr);
}
