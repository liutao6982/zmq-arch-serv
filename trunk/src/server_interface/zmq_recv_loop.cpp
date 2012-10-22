// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#include "zmq_recv_loop.hpp"

ZMQRecvLoop::ZMQRecvLoop(boost::asio::io_service& io_service)
	:io_service_(io_service)
{

}

//此函数需要优化 或使用让出cpu策略
void ZMQRecvLoop::workloop()
{
	while (1)
	{
		if (!zmq_socket_queue.isEmpty())
		{
			boost::shared_ptr<message_session> message_session_ptr_ = 
				zmq_socket_queue.pop();


			ZmqConnectionPtr zmq_connect_ptr = 
				message_session_ptr_->getZMQConnectionPtr();

			boost::shared_ptr<zmq::message_t> message_ptr(new zmq::message_t);
			int rc = zmq_connect_ptr->recv_nonblock(message_ptr.get());

			if (rc == 0)
			{
				io_service_.post(boost::bind(
					&message_session::do_send,
					message_session_ptr_,
					message_ptr));
			}
			else if(rc == -1)
			{
				boost::mutex::scoped_lock socpedlock(mtx_);
				zmq_socket_queue.push(message_session_ptr_);
			}
			else
			{
				zmq_connect_ptr->close();
			}
		}
		else
		{
			Sleep(1);
		}
	}
}

void ZMQRecvLoop::addevent(
			boost::shared_ptr<message_session> message_session_ptr_)
{
	boost::mutex::scoped_lock socpedlock(mtx_);
	zmq_socket_queue.push(message_session_ptr_);
}