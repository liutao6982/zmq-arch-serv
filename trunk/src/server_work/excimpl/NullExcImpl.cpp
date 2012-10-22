// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#include "NullExcImpl.hpp"

DEF_IMPL(NullExcImpl)
{

	//grep  日志中查关键字NullExcImpl可查看输入
	printf("%s\n", _input.c_str());
	_output = "NullExcImpl";
	return 1;
}