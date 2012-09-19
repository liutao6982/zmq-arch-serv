// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#include "message_session.hpp"

boost::asio::ip::tcp::socket& message_session::socket()
{
	return socket_;
}

void message_session::start()
{
	boost::asio::async_read(socket_,
		boost::asio::buffer(read_msg_.data(), message::header_length),
		boost::bind(
		&message_session::handle_read_header, shared_from_this(),
		boost::asio::placeholders::error));
}

void message_session::handle_read_header(const boost::system::error_code& error)
{
	if (!error && read_msg_.decode_header())
	{
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
			boost::bind(&message_session::handle_read_body, shared_from_this(),
			boost::asio::placeholders::error));
	}
	else
	{

	}
}

void message_session::handle_read_body(const boost::system::error_code& error)
{
	if (!error)
	{
		do_read();
	}
	else
	{

	}
}

void message_session::handle_write(const boost::system::error_code& error)
{
	if (!error)
	{
		if (!write_msgs_.empty())
		{
			message msg = write_msgs_.front();
			write_msgs_.pop_front();
			boost::asio::async_write(socket_,
				boost::asio::buffer(msg.data(), msg.length()),
				boost::bind(&message_session::handle_write, shared_from_this(),
				boost::asio::placeholders::error));
		}
	}
	else
	{

	}
}
void message_session::do_send(boost::shared_ptr<zmq::message_t> message_ptr)
{
	
	std::cout << (char *)message_ptr->data() << std::endl;
	
	message msg;
	msg.body_length(message_ptr->size());
	memcpy(msg.body(), message_ptr->data(), message_ptr->size());
	msg.encode_header();
	write_msgs_.push_back(msg);
	
	handle_write(boost::system::error_code());

	//∂¡«∞œ»«Â¡„
	read_msg_.bzero();
	boost::asio::async_read(socket_,
		boost::asio::buffer(read_msg_.data(), message::header_length),
		boost::bind(&message_session::handle_read_header, shared_from_this(),
		boost::asio::placeholders::error));
}

ZmqConnectionPtr message_session::getZMQConnectionPtr()
{
	return zmq_connection_ptr;
}

void message_session::do_read()
{
	std::cout << read_msg_.body() << std::endl;
	if(zmq_connection_pool_.newConection(zmq_connection_ptr))
	{
		zmq::message_t msg(read_msg_.body(), read_msg_.body_length(), NULL);

		zmq_connection_ptr->send(msg);

		zmq_recv_loop_.addevent(shared_from_this());
	}
	else
	{
		buzy_request();
		std::cerr << "zmq connection pool empty!" << std::endl;
	}
	//io_service_.post(
	//	boost::bind(&message_session::do_send, shared_from_this(), message_ptr));
}

void message_session::buzy_request()
{
	message msg;
	char* content = "zmq connection pool empty!";
	memcpy(msg.body(), content, strlen(content));
	msg.decode_header();
	boost::asio::async_write(socket_,
		boost::asio::buffer(msg.data(), msg.length()),
		boost::bind(&message_session::handle_write, shared_from_this(),
		boost::asio::placeholders::error));
}