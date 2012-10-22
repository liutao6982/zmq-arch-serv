// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#ifndef __RETECT_FACTORY_HPP__
#define __RETECT_FACTORY_HPP__

#include <string>
#include <map>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include "ExcImpl.hpp"

class RefectFactory;
class ExcImpl;
typedef boost::function<ExcImpl* (std::string&)> CreateImplFunc;
typedef boost::function<int (void)> ImplFunc;
typedef boost::shared_ptr<ExcImpl> ExcImplPtr;

class RefectFactory
{
	typedef std::map<std::string, CreateImplFunc> RefectMap;
public:
	//单例接口
	static RefectFactory& getInstance()
	{
		static RefectFactory _instance;//静态的单例 因为反射类也是静态注册的
		return _instance;
	}

	//工厂函数
	ExcImplPtr CreateExc(std::string& input);

	friend class ExcImpl;
protected:
	//工厂类静态注册反射接口
	void addFactoryCase(std::string& type, CreateImplFunc func)
	{
		_refect_map.insert(
			std::make_pair<
			std::string, 
			CreateImplFunc
			>(type, func));
	}
	RefectFactory();
	
private:
	//反射表
	RefectMap _refect_map;
	//空业务处理对象指针
	ExcImplPtr null_excImpPtr;
};

#endif