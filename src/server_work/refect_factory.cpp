// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#include "refect_factory.hpp"
#include "excimpl/NullExcImpl.hpp"
#include <json/json.h>

ExcImplPtr RefectFactory::CreateExc(std::string& _type)
{
	//构造业务处理类
	RefectMap::iterator it = _refect_map.find(_type);
	if (it != _refect_map.end())
	{
		ExcImplPtr exc_impl_ptr((it->second)(_type));
		return  exc_impl_ptr;
	}
	return null_excImpPtr;
}

RefectFactory::RefectFactory():
	null_excImpPtr(new NullExcImpl(std::string("there is no this type!")))
{

}