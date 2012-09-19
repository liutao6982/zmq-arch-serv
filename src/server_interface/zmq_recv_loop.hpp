// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#ifndef __ZMQ__RECV_LOOP_HPP__
#define __ZMQ__RECV_LOOP_HPP__


#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>

#include "message_session.hpp"
#include "base/BlockingQueue.hpp"

#include "../zmq_connection_pool/ZmqConnectionPool.hpp"

class message_session;

class ZMQRecvLoop
{
public:
	ZMQRecvLoop(boost::asio::io_service& io_service);

	void workloop();

	void addevent(boost::shared_ptr<message_session> message_session_ptr_);

protected:
private:
	boost::asio::io_service& io_service_;
	CCTool::BlockingQueue<boost::shared_ptr<message_session> > zmq_socket_queue;
	boost::mutex mtx_;
};

#endif