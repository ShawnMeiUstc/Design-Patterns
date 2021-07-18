#pragma once
/* user interface */
class IPublisher;

class ISubscriber
{
public:
	virtual ~ISubscriber() {}
	virtual void DoAttach(IPublisher* newPublisher) = 0;
	virtual void AddPublisher(IPublisher* iuser) = 0;
	virtual void DoDetach(IPublisher* somePublisher) = 0;
	virtual void Recovery(IPublisher* somePublisher) = 0;
	virtual void Run() = 0;
};

class IPublisher
{
public:
	virtual ~IPublisher() {}
	virtual void UsePattern() = 0;

	virtual void Attach(ISubscriber* newSubscriber)
	{
		m_subsciberList.push_back(newSubscriber);
		NotifyNew(newSubscriber);
	}

	virtual void Detach(ISubscriber* manager)
	{
		m_subsciberList.remove(manager);
	}

	virtual void NotifyAll()
	{
		for (ISubscriber* manager : m_subsciberList)
		{
			manager->AddPublisher(this);
		}
	}

	virtual void NotifyNew(ISubscriber* newSubscriber)
	{
		newSubscriber->AddPublisher(this);
	}
private:
	list<ISubscriber*> m_subsciberList;
};


class Subscriber :public ISubscriber
{
public:
	virtual void DoAttach(IPublisher* newPublisher) override
	{
		newPublisher->Attach(this);
	}

	virtual void DoDetach(IPublisher* somePublisher) override
	{
		somePublisher->Detach(this);
	}

	virtual void AddPublisher(IPublisher* publisher) override
	{
		publisherList.push_back(publisher);
	}

	virtual void Recovery(IPublisher* somePublisher) override
	{
		publisherList.remove(somePublisher);
	}

	virtual void Run() override
	{
		for (auto it : publisherList)
		{
			it->UsePattern();
			cout << "-------------------------------------------------------\n\n\n\n";
		}
	}

	~Subscriber() {}

private:
	list<IPublisher*> publisherList;
};
