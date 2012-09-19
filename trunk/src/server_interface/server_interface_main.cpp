// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#include <boost/asio.hpp>
#include "message_server.hpp"

#include "../zmq_connection_pool/ZmqConnectionPool.hpp"

#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: server_interface router-domain <port>\n";
			std::cerr << "eg:    server viewin-cc 5031\n";
			getchar();
			return 1;
		}
		google::InitGoogleLogging("1");
		google::SetLogDestination(google::GLOG_INFO, argv[0]);

		boost::asio::io_service io_service;

		zmq::context_t context(1);
		ZmqConnectionPool zmq_connection_pool(context,
			ZmqConnectionPool::CONNECTIONS_NUM, argv[1]);
	
		boost::asio::ip::tcp::endpoint endpoint(
			boost::asio::ip::tcp::v4(),
			atoi(argv[2]));

		message_server_ptr server(
			new message_server(io_service, endpoint, zmq_connection_pool));

		server->run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}