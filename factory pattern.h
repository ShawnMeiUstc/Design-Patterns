#pragma once
#include "ipublisher and isubscriber.h"
/**
 * The Product interface declares the operations that all concrete products must
 * implement.
 */

class AbstractProduct {
public:
    virtual ~AbstractProduct() {}
    virtual std::string Operation() const = 0;
};

/**
 * Concrete Products provide various implementations of the Product interface.
 */
class ConcreteProduct1 : public AbstractProduct {
public:
    std::string Operation() const override {
        return "{Result of the ConcreteProduct1}";
    }
};
class ConcreteProduct2 : public AbstractProduct {
public:
    std::string Operation() const override {
        return "{Result of the ConcreteProduct2}";
    }
};

/**
 * The Creator class declares the factory method that is supposed to return an
 * object of a Product class. The Creator's subclasses usually provide the
 * implementation of this method.
 */

class Creator {
    /**
     * Note that the Creator may also provide some default implementation of the
     * factory method.
     */
public:
    virtual ~Creator() {};
    virtual unique_ptr<AbstractProduct> FactoryMethod() const = 0;
    /**
     * Also note that, despite its name, the Creator's primary responsibility is
     * not creating products. Usually, it contains some core business logic that
     * relies on Product objects, returned by the factory method. Subclasses can
     * indirectly change that business logic by overriding the factory method and
     * returning a different type of product from it.
     */

    std::string SomeOperation() const {
        // Call the factory method to create a Product object.
        unique_ptr<AbstractProduct> product = this->FactoryMethod();
        // Now, use the product.
        std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
        return result;
    }
};

/**
 * Concrete Creators override the factory method in order to change the
 * resulting product's type.
 */
class ConcreteCreator1 : public Creator {
    /**
     * Note that the signature of the method still uses the abstract product type,
     * even though the concrete product is actually returned from the method. This
     * way the Creator can stay independent of concrete product classes.
     */
public:
    virtual unique_ptr<AbstractProduct> FactoryMethod() const override {
        return make_unique<ConcreteProduct1>();
    }
};

class ConcreteCreator2 : public Creator {
public:
    virtual unique_ptr<AbstractProduct> FactoryMethod() const override {
        return make_unique<ConcreteProduct2>();
    }
};

/**
 * The client code works with an instance of a concrete creator, albeit through
 * its base interface. As long as the client keeps working with the creator via
 * the base interface, you can pass it any creator's subclass.
 */
void ClientCode(const Creator& creator) {
    // ...
    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
        << creator.SomeOperation() << std::endl;
    // ...
}

/**
 * The Application picks a creator's type depending on the configuration or
 * environment.
 */

class FactoryPatternPublisher final : public IPublisher
{
public:
    virtual void UsePattern() override
    {
        cout << "===============>>>>>>> Test Factory Pattern <<<<<<<===============\n";
        std::cout << "App: Launched with the ConcreteCreator1.\n";
        unique_ptr<Creator> creator = make_unique<ConcreteCreator1>();
        ClientCode(*creator);
        std::cout << std::endl;
        std::cout << "App: Launched with the ConcreteCreator2.\n";
        unique_ptr<Creator> creator2 = make_unique<ConcreteCreator2>();
        ClientCode(*creator2);
    }
};
