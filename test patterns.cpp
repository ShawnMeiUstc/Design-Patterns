#include "template method.h"
#include "decorator pattern.h"
#include "bridge pattern.h"
#include "factory pattern.h"
#include "abstract factory.h"



int main()
{
	IPublisher* pUser1 = new TemplateMethodPublisher();
	IPublisher* pUser2 = new DecoratorPatternPublisher();
	IPublisher* pUser3 = new BridgePatternPublisher();
	IPublisher* pUser4 = new FactoryPatternPublisher();
	IPublisher* pUser5 = new AbstractFactoryPublisher();


	ISubscriber* subscriber = new Subscriber();

	subscriber->DoAttach(pUser1);
	subscriber->DoAttach(pUser2);
	subscriber->DoAttach(pUser3);
	subscriber->DoAttach(pUser4);
	subscriber->DoAttach(pUser5);


	subscriber->Run();
}