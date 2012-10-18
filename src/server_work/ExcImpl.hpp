// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)

#ifndef __EXC_IMPL_HPP__
#define __EXC_IMPL_HPP__

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include "refect_factory.hpp"

//业务实现基类 业务类继承此类
class ExcImpl
{
	typedef boost::function<ExcImpl* (std::string&)> CreateImplFunc;
	typedef boost::function<int (void)> ImplFunc;
public:
	//@input 流程码
	ExcImpl(std::string& type);

	//业务执行接口 处理业务
	virtual int do_excute(std::string& _input) =0;
	
	//输出接口
	const std::string& getOutput() const
	{
		return _output;
	}

protected:
	//注册工厂接口 注工厂类已声明为友元类
	static void addFactoryCase(std::string& type, CreateImplFunc func);

	std::string _output;
	//std::string _input;
private:

};

#endif