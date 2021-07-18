#pragma once
#include "template method.h"
#include "decorator pattern.h"
#include "bridge pattern.h"
#include "factory pattern.h"
#include "abstract factory.h"
#include "prototype pattern.h"
#include "builder pattern.h"

namespace User {
	vector<unique_ptr<IPublisher*>> m_publishers;
	ISubscriber* subscriber = new Subscriber();

	void Init() {
		m_publishers.push_back(make_unique<IPublisher*>(new TemplateMethodPublisher()));
		m_publishers.push_back(make_unique<IPublisher*>(new DecoratorPatternPublisher()));
		m_publishers.push_back(make_unique<IPublisher*>(new BridgePatternPublisher()));
		m_publishers.push_back(make_unique<IPublisher*>(new FactoryPatternPublisher()));
		m_publishers.push_back(make_unique<IPublisher*>(new AbstractFactoryPublisher()));
		m_publishers.push_back(make_unique<IPublisher*>(new PrototypePatternPublisher()));
		m_publishers.push_back(make_unique<IPublisher*>(new BuiderPatternPublisher()));
	}

	void DoAttach() {
		for (auto iter = m_publishers.begin(); iter != m_publishers.end(); ++iter) {
			subscriber->DoAttach(*iter->get());
		}
	}


	



}
	