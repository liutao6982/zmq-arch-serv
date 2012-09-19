// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#include "ExcImpl.hpp"

ExcImpl::ExcImpl(std::string& type)
{
	//TODO ... eg. log
}

void ExcImpl::addFactoryCase(std::string& type, CreateImplFunc func)
{
	RefectFactory::getInstance().addFactoryCase(type, func);
}

