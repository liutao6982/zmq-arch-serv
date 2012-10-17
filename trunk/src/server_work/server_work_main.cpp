// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#include <iostream>
#include <zmq.hpp>
#include <json/json.h>

#include "refect_factory.hpp"
#include "ExcImpl.hpp"

#include <base/QuitCtrl.hpp>

#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

int excute(ExcImplPtr exc_impl_ptr, std::string& input)//deal with null point error 
{
	assert(exc_impl_ptr);
	return exc_impl_ptr->do_excute(input);
}

void do_error_list_str(int error_no,std::string& output)
{
	switch(error_no)
	{
	case -1:
		output = "type error!";
		break;
	default:
		output = "unkown error!";
	}
}

std::string zmq_message_construct_string(zmq::message_t& message)
{
	size_t len = message.size();
	char* str = new char[len + 1];
	memcpy(str, message.data(), len);
	str[len] = 0;

	std::string ret(str);
	delete[] str;
	return ret;
}

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

void QuitDlay(int time)
{
	for (int i = time ;i > 0 ; i--)
	{
		printf("Normal Quit! %d...\r",i);
		Sleep(1000);
	}
}

std::string gettype(std::string& input)
{
	std::string _type("NullExcImpl");
	
	Json::Value json_value;
	Json::Reader json_reader;
	
	//解析json
	if (json_reader.parse(input, json_value)
		&& json_value.isObject())
	{
		_type = json_value["type"].asString();
	}
	return _type;
}

int main(int argc, char* argv[])
{
	//解析参数
	char connect_string[256];
	if (argc != 2)
	{
		printf(
			"Usage: server_work router-domain/ip \n"
			"eg:    server_work viewin-cc\n"
			"		server_work 192.168.16.234\n");
		getchar();
		return 1;
	}
	else
	{
		sprintf_s(connect_string, "tcp://%s:5560", argv[1]);
	}

	google::InitGoogleLogging("1");
	google::SetLogDestination(google::GLOG_INFO, argv[0]);

	//业务主循环
	zmq::context_t context(1);

	zmq::socket_t responder(context, ZMQ_REP);
	responder.connect(connect_string);

	CCTool::QuitCtrl quit_ctrl;

	std::string ret_info;

	while(quit_ctrl.getState() != CCTool::QuitCtrl::quit)
	{
		//  Wait for next request from client
		zmq::message_t request;//  Wait for next request from client        
		responder.recv (&request);

		std::string input = zmq_message_construct_string(request);
		std::string output;

		std::string type = gettype(input);
		
		ExcImplPtr exc_impl_ptr =
			RefectFactory::getInstance().CreateExc(type);

		int ret;
		if ((ret = excute(exc_impl_ptr, input)) > 0)
		{
			output = exc_impl_ptr->getOutput();
			//std::cout << output << std::endl;
		}
		else
		{
			//error list
			do_error_list_str(ret, ret_info);
			std::cout << ret_info << std::endl;
		}

		size_t len;
		char *_string_copy = zmq_new_string(output, len);
		//  Send reply back to client
		request.rebuild(_string_copy, len, zmq_free);
		responder.send(request);
	}
	responder.close();
	QuitDlay(5);
	
	return 0;
}