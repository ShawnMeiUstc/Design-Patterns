#include "template method.h"
#include "decorator pattern.h"
#include "bridge pattern.h"
#include "factory pattern.h"
#include "abstract factory.h"
#include "prototype pattern.h"

int main()
{
	IPublisher* pUser1 = new TemplateMethodPublisher();
	IPublisher* pUser2 = new DecoratorPatternPublisher();
	IPublisher* pUser3 = new BridgePatternPublisher();
	IPublisher* pUser4 = new FactoryPatternPublisher();
	IPublisher* pUser5 = new AbstractFactoryPublisher();
	IPublisher* pUser6 = new PrototypePatternPublisher();
 
	ISubscriber* subscriber = new Subscriber();

	subscriber->DoAttach(pUser1);
	subscriber->DoAttach(pUser2);
	subscriber->DoAttach(pUser3);
	subscriber->DoAttach(pUser4);
	subscriber->DoAttach(pUser5);
	subscriber->DoAttach(pUser6);


	subscriber->Run();
}