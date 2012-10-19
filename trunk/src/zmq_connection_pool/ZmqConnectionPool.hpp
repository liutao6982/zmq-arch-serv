// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)

#ifndef __ZMQ__CONNECTION_POOL_HPP__
#define __ZMQ__CONNECTION_POOL_HPP__
#include <iostream>
#include <zmq.hpp>
#include <boost/shared_ptr.hpp>
#include <base/BlockingQueue.hpp>


typedef boost::shared_ptr<zmq::socket_t> ZmqConnectionPtr;

class ZmqConnectionPool
{
public:
	enum{CONNECTIONS_NUM = 1};

	ZmqConnectionPool(zmq::context_t& context, size_t size, char* server);

	bool newConection(ZmqConnectionPtr& zmq_connection_ptr);

	void releaseConection(ZmqConnectionPtr zmq_connection_ptr);

	ZmqConnectionPtr CreateConection();

	size_t size() const
	{
		return zmq_connection_queue.size();
	}

	std::string getConnString() const;

protected:
private:

	std::string conn_str;
	zmq::context_t& _context;
	CCTool::BlockingQueue<ZmqConnectionPtr> zmq_connection_queue;
};

#endif