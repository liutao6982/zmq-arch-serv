// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#ifndef __ZMQ__MESSAGE_SERVER_HPP__
#define __ZMQ__MESSAGE_SERVER_HPP__

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "message_session.hpp"
#include "zmq_recv_loop.hpp"

class message_server
{
public:
  message_server(boost::asio::io_service& io_service,
      const boost::asio::ip::tcp::endpoint& endpoint,
	  ZmqConnectionPool& zmq_connection_pool)
    : io_service_(io_service),
      acceptor_(io_service, endpoint),
	  zmq_recv_loop_(io_service),
	  zmq_connection_pool_(zmq_connection_pool)
  {
    boost::shared_ptr<message_session> new_session(
		new message_session(io_service_, zmq_recv_loop_, zmq_connection_pool_));

    acceptor_.async_accept(new_session->socket(),
        boost::bind(&message_server::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void handle_accept(boost::shared_ptr<message_session> session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      session->start();
      boost::shared_ptr<message_session> new_session(
		  new message_session(io_service_, zmq_recv_loop_, zmq_connection_pool_));

      acceptor_.async_accept(new_session->socket(),
         boost::bind(&message_server::handle_accept, this, new_session,
           boost::asio::placeholders::error));
    }
  }

  void run()
  {
	  boost::thread zmq_loop(boost::bind(&ZMQRecvLoop::workloop, &zmq_recv_loop_));
	  io_service_.run();
  }

private:
  boost::asio::io_service& io_service_;
  boost::asio::ip::tcp::acceptor acceptor_;
  ZMQRecvLoop zmq_recv_loop_;
  ZmqConnectionPool& zmq_connection_pool_;
};

typedef boost::shared_ptr<message_server> message_server_ptr;

//----------------------------------------------------------------------


#endif