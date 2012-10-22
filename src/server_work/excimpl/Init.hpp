// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)

#ifndef __INIT_HPP__
#define __INIT_HPP__

#include <iostream>

#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

void sys_init()
{
	google::InitGoogleLogging("1");
	google::SetLogDestination(google::GLOG_INFO, "1");
}

void init()
{

}


#endif