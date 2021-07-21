#pragma once
#include "template method.h"
#include "decorator pattern.h"
#include "bridge pattern.h"
#include "factory pattern.h"
#include "abstract factory.h"
#include "prototype pattern.h"
#include "builder pattern.h"
#include "observer pattern.h"

class User {
public:
	static User& GetUserInstance() {
		static User instance;
		return instance;
	}

	void Run() {
		subscriber->Run();
	}

	User(const User&) = delete;
	User operator=(const User&) = delete;

private:
	vector<shared_ptr<IPublisher>> m_publishers;
	shared_ptr<ISubscriber> subscriber = make_shared<Subscriber>();

	User() { 
		Init(); 
		DoAttach();
	}

	void Init() {
		m_publishers.push_back(make_shared<TemplateMethodPublisher>());
		m_publishers.push_back(make_shared<DecoratorPatternPublisher>());
		m_publishers.push_back(make_shared<BridgePatternPublisher>());
		m_publishers.push_back(make_shared<FactoryPatternPublisher>());
		m_publishers.push_back(make_shared<AbstractFactoryPublisher>());
		m_publishers.push_back(make_shared<PrototypePatternPublisher>());
		m_publishers.push_back(make_shared<BuiderPatternPublisher>());
		m_publishers.push_back(make_shared<ObserverPatternPublisher>());
	}

	void DoAttach() {
		for (auto iter = m_publishers.begin(); iter != m_publishers.end(); ++iter) {
			subscriber->DoAttach(*iter);
		}
	}
	
};
	