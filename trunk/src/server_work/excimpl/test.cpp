// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#include "test.hpp"


//建议实现在动态库中便于程序更新
DEF_IMPL(test1)
{
	//printf("%s\n", _input.c_str());
	_output = "hello world1";

	//return do_test1(_input, _output);

	return 1;
}

DEF_IMPL(test2)
{
	//printf("%s\n", _input.c_str());
	_output = "hello world2";
	return 1;
}
DEF_IMPL(test3)
{
	//printf("%s\n", _input.c_str());
	_output = "hello world3";
	return 1;
}
DEF_IMPL(test4)
{
	//printf("%s\n", _input.c_str());
	_output = "hello world4";
	return 1;
}
DEF_IMPL(test5)
{
	//printf("%s\n", _input.c_str());
	_output = "hello world5";
	return 1;
}