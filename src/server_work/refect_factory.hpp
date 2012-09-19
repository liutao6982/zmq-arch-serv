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
	//�����ӿ�
	static RefectFactory& getInstance()
	{
		static RefectFactory _instance;//�����Ǿ�̬�� ������Ҳ�Ǿ�̬ע���
		return _instance;
	}

	//��������
	ExcImplPtr CreateExc(std::string& input);

	friend class ExcImpl;
protected:
	//�����ྲ̬ע�ᷴ��ӿ�
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
	//�����
	RefectMap _refect_map;
	//��ҵ�������ָ��
	ExcImplPtr null_excImpPtr;
};

#endif