#pragma once
#include "stdc++.h"
/* user interface */
class IPublisher;
// effective modern c++ item 19 ！！！！ shared_ptr with this 
class ISubscriber : public enable_shared_from_this<ISubscriber>
{
public:
	virtual ~ISubscriber() {}
	virtual void DoAttach(shared_ptr<IPublisher> newPublisher) = 0;
	virtual void AddPublisher(shared_ptr<IPublisher>iuser) = 0;
	virtual void DoDetach(shared_ptr<IPublisher> somePublisher) = 0;
	virtual void Recovery(shared_ptr<IPublisher> somePublisher) = 0;
	virtual void Run() = 0;
};

class IPublisher : public enable_shared_from_this<IPublisher>
{
public:
	virtual ~IPublisher() {}
	virtual void UsePattern() = 0;

	virtual void Attach(shared_ptr<ISubscriber> newSubscriber)
	{
		m_subsciberList.push_back(newSubscriber);
		NotifyNew(newSubscriber);
	}

	virtual void Detach(shared_ptr<ISubscriber> manager)
	{
		m_subsciberList.remove(manager);
	}

	virtual void NotifyAll()
	{
		for (auto manager =  m_subsciberList.begin(); manager != m_subsciberList.end(); ++manager)
		{
			(*manager)->AddPublisher(shared_from_this());
		}
	}

	virtual void NotifyNew(shared_ptr<ISubscriber> newSubscriber)
	{
		newSubscriber->AddPublisher(shared_from_this());
	}
	
private:
	list<shared_ptr<ISubscriber>> m_subsciberList;
	
};


class Subscriber :public ISubscriber
{
public:
	virtual void DoAttach(shared_ptr<IPublisher> newPublisher) override
	{
		newPublisher->Attach(shared_from_this());
	}

	virtual void DoDetach(shared_ptr<IPublisher> somePublisher) override
	{
		somePublisher->Detach(shared_from_this());
	}

	virtual void AddPublisher(shared_ptr<IPublisher> publisher) override
	{
		publisherList.push_back(publisher);
	}

	virtual void Recovery(shared_ptr<IPublisher> somePublisher) override
	{
		publisherList.remove(somePublisher);
	}

	virtual void Run() override
	{
		for (auto it = publisherList.begin(); it != publisherList.end(); ++it)
		{
			(*it)->UsePattern();
			cout << "-------------------------------------------------------\n\n\n\n";
		}
	}

	~Subscriber() {}

private:
	list<shared_ptr<IPublisher>> publisherList;
};
