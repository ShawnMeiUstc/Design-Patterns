#pragma once
#include "stdc++.h"
#include "iuser.h"
/**
 * Each distinct product of a product family should have a base interface. All
 * variants of the product must implement this interface.
 */

class AbstractChair {
public:
    virtual ~AbstractChair() {}
    virtual std::string OperationChair() const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
class ModernChair : public AbstractChair {
public:
    std::string OperationChair() const override {
        return "{Result of the ModernChair}";
    }
};
class TraditionalChair : public AbstractChair {
public:
    std::string OperationChair() const override {
        return "{Result of the TraditionalChair}";
    }
};

/**
 * Here's the the base interface of another product. All products can interact
 * with each other, but proper interaction is possible only between products of
 * the same concrete variant.
 */

class AbstractSofa {
public:
    virtual ~AbstractSofa() {}
    virtual std::string OperationSofa(const AbstractChair &chair) const = 0;
};

/**
 * Concrete Products provide various implementations of the Product interface.
 */
class ModernSofa : public AbstractSofa {
public:
    std::string OperationSofa(const AbstractChair& chair) const override {
        return "Composition of : {Result of the ModernSofa} + " + chair.OperationChair();
    }
};
class TraditionalSofa : public AbstractSofa {
public:
    std::string OperationSofa(const AbstractChair& chair) const override {
        return "Composition of : {Result of the TraditionalSofa} + " + chair.OperationChair();
    }
};


/**
 * The Creator class declares the factory method that is supposed to return an
 * object of a Product class. The Creator's subclasses usually provide the
 * implementation of this method.
 */

class AbstarctCreator {
    /**
     * Note that the Creator may also provide some default implementation of the
     * factory method.
     */
public:
    virtual ~AbstarctCreator() {};
    virtual AbstractChair* ChairMethod() const = 0;
    virtual AbstractSofa* SofaMethod() const = 0;
};

/**
 * Concrete Creators override the factory method in order to change the
 * resulting product's type.
 */
class ModernCreator : public AbstarctCreator {
    /**
     * Note that the signature of the method still uses the abstract product type,
     * even though the concrete product is actually returned from the method. This
     * way the Creator can stay independent of concrete product classes.
     */
public:
    virtual AbstractChair* ChairMethod() const override {
        return new ModernChair();
    }
    virtual AbstractSofa* SofaMethod() const {
        return new ModernSofa();
    }
};


class TraditionalCreator : public AbstarctCreator {
public:
    virtual AbstractChair* ChairMethod() const override {
        return new TraditionalChair();
    }
    virtual AbstractSofa* SofaMethod() const {
        return new TraditionalSofa();
    }
};

/**
 * The client code works with an instance of a concrete creator, albeit through
 * its base interface. As long as the client keeps working with the creator via
 * the base interface, you can pass it any creator's subclass.
 */
void ClientCode(const AbstarctCreator& creator) {
    AbstractChair *chair = creator.ChairMethod();
    AbstractSofa* sofa = creator.SofaMethod();
    cout << chair->OperationChair() << endl;
    cout << sofa->OperationSofa(*chair) << endl;
    delete chair;
    delete sofa;
}

/**
 * The Application picks a creator's type depending on the configuration or
 * environment.
 */

class AbstractFactoryPublisher final : public IPublisher
{
public:
    virtual void UsePattern() override
    {
        cout << "===============>>>>>>> Test Abstract Factory<<<<<<<===============\n";
        std::cout << "Client: Testing client code with the first factory type:\n";
        AbstarctCreator* modern = new ModernCreator();
        ClientCode(*modern);
        delete modern;
        std::cout << std::endl;
        std::cout << "Client: Testing the same client code with the second factory type:\n";
        AbstarctCreator* traditional = new TraditionalCreator();
        ClientCode(*traditional);
        delete traditional;
    }
};
