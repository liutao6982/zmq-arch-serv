#ifndef __BASE_ZMQ_TOOL_HPP__
#define __BASE_ZMQ_TOOL_HPP__

#include <zmq.hpp>

namespace CCTool{
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
		char *_string_copy = new char[len];
		memcpy(_string_copy, str.c_str(), len);
		return _string_copy;
	}

	void zmq_free(void *data, void *hint)
	{
		delete[] (char *)data;
	}
}

#endif