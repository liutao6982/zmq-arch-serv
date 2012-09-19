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

//ҵ��ʵ�ֻ��� ҵ����̳д���
class ExcImpl
{
	typedef boost::function<ExcImpl* (std::string&)> CreateImplFunc;
	typedef boost::function<int (void)> ImplFunc;
public:
	//@input ��������json�ַ���
	ExcImpl(std::string& type);

	//ҵ��ִ�нӿ� ����ҵ��
	virtual int do_excute(std::string& _input) =0;
	
	//����ӿ�
	const std::string& getOutput() const
	{
		return _output;
	}

protected:
	//ע�Ṥ���ӿ� ע������������Ϊ��Ԫ��
	static void addFactoryCase(std::string& type, CreateImplFunc func);

	std::string _output;
	//std::string _input;
private:

};

#endif