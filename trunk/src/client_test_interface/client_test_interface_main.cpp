// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#include <zmq.hpp>

#include <iostream>
#include <string>  

#include <Windows.h>

#include "../zmq_connection_pool/ZmqConnectionPool.hpp"

#include <base/zmq_tool.hpp>


#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

int main (int argc, char* argv[])
{    
	if (argc != 2)
	{
		printf(
			"Usage: client_test_interface router-domain/ip \n"
			"eg:    client_test_interface viewin-cc\n"
			"		client_test_interface 192.168.16.234\n");
		getchar();
		return 1;
	}

	google::InitGoogleLogging("1");
	google::SetLogDestination(google::GLOG_INFO, argv[0]);

	zmq::context_t context(1);

	ZmqConnectionPool zmq_connection_pool(context, 
		ZmqConnectionPool::CONNECTIONS_NUM, argv[1]);

	ZmqConnectionPtr zmq_connection_ptr;

	for( int request = 0 ; ; request++)
	{
		zmq_connection_pool.newConection(zmq_connection_ptr);
		std::string test_str(
			"{\"jid\":\"905714444@hzdomain/HZUMD1\","
			"\"type\":\"test1\","
			"\"state\":\"\","
			"\"errorcode\":\"\","
			"\"sessionid\":\"whosyourdaddy\","
			"\"data\":{"
				"\"lng\":119307396,"
				"\"lat\":29420824,"
				"\"gridx\":27243,"
				"\"gridy\":13579}}");
		//std::string test_str("aaa");
		test_str[47] = request % 5 + 0x31;
		zmq::message_t message((void*)test_str.c_str(), test_str.length() + 1, NULL);
		zmq_connection_ptr->send(message);

		message.rebuild();
	
		zmq::pollitem_t item =
			{ *zmq_connection_ptr, 0, ZMQ_POLLIN, 0 };

		int rc,i = 0;

		while ((rc = zmq::poll (&item, 1, 5000)) != 1)
		{
			if(i++ > 10)
				break;
		}

		if (rc == 1 &&item.revents & ZMQ_POLLIN)
		{
			zmq_connection_ptr->recv(&message);
		}
		else
		{
			std::cout << "reconnected..." << std::endl;
			zmq_connection_ptr->close();
			zmq_connection_ptr = zmq_connection_pool.CreateConection();
		}

		if (request%1000 == 0)
		{
			std::cout << request << std::endl;
		}
		zmq_connection_pool.releaseConection(zmq_connection_ptr);
	}
}