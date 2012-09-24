// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#ifndef __ZMQ__MESSAGE_SESSION_HPP__
#define __ZMQ__MESSAGE_SESSION_HPP__

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "message.hpp"
#include "../zmq_connection_pool/ZmqConnectionPool.hpp"
#include "zmq_recv_loop.hpp"

typedef std::deque<message> message_queue;

class ZMQRecvLoop;

class message_session
	: public boost::enable_shared_from_this<message_session>
{
public:
	message_session(
		boost::asio::io_service& io_service,
		ZMQRecvLoop& zmq_recv_loop,
		ZmqConnectionPool& zmq_connection_pool)
		: socket_(io_service),
		io_service_(io_service),
		zmq_recv_loop_(zmq_recv_loop),
		zmq_connection_pool_(zmq_connection_pool)
	{
	}

	boost::asio::ip::tcp::socket& socket();

	void start();

	void handle_read_header(const boost::system::error_code& error);

	void handle_read_body(const boost::system::error_code& error);

	void handle_write(const boost::system::error_code& error);

	void do_send(boost::shared_ptr<zmq::message_t> message_ptr);

	void buzy_request();

	ZmqConnectionPtr getZMQConnectionPtr();
protected:

	void do_read();

private:
	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::socket socket_;
	message read_msg_;
	message_queue write_msgs_;

	ZmqConnectionPtr zmq_connection_ptr;
	
	ZMQRecvLoop& zmq_recv_loop_;

	//static zmq::context_t context;
	ZmqConnectionPool& zmq_connection_pool_;
};

#endif