// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
//定义业务处理类
#define DEF_CLASS(name) \
class name :public ExcImpl\
{\
public:\
	name(std::string& type);\
	int do_excute(std::string& _input);\
protected:\
private:\
	static ExcImpl* CreateThis(std::string& input)\
	{\
		return new name(input);\
	}\
	friend class Reg_refect_##name;\
	static Reg_refect_##name reg_refect;\
};\
class Reg_refect_##name\
{\
public:\
	Reg_refect_##name()\
	{\
		CreateImplFunc create_impl_func = boost::bind(&name::CreateThis, _1);\
		ExcImpl::addFactoryCase(std::string(#name), create_impl_func);\
	}\
};

//实现业务处理函数
#define DEF_IMPL(name) \
name::name(std::string& type): ExcImpl(type)\
{\
}\
Reg_refect_##name name::reg_refect;\
int name::do_excute(std::string& _input)