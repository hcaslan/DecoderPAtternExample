#include <string>
#include <iostream>

class Car //Our Abstract base class
{
protected:
    std::string _str;
public:
    Car()
    {
        _str = "Unknown Car";
    }

    virtual std::string getDescription()
    {
        return _str;
    }

    virtual double getCost() = 0;

    virtual ~Car()
    {
        std::cout << "~Car()\n";
    }
};

class OptionsDecorator : public Car //Decorator Base class
{
public:
    virtual std::string getDescription() = 0;

    virtual ~OptionsDecorator()
    {
        std::cout << "~OptionsDecorator()\n";
    }
};


class CarModel1 : public Car
{
public:
    CarModel1()
    {
        _str = "CarModel1";
    }
    virtual double getCost()
    {
        return 31000.23;
    }

    ~CarModel1()
    {
        std::cout << "~CarModel1()\n";
    }
};


class Navigation : public OptionsDecorator
{
    Car* _b;
public:
    Navigation(Car* b)
    {
        _b = b;
    }
    std::string getDescription()
    {
        return _b->getDescription() + ", Navigation";
    }

    double getCost()
    {
        return 300.56 + _b->getCost();
    }
    ~Navigation()
    {
        std::cout << "~Navigation()\n";
        delete _b;
    }
};

class PremiumSoundSystem : public OptionsDecorator
{
    Car* _b;
public:
    PremiumSoundSystem(Car* b)
    {
        _b = b;
    }
    std::string getDescription()
    {
        return _b->getDescription() + ", PremiumSoundSystem";
    }

    double getCost()
    {
        return 0.30 + _b->getCost();
    }
    ~PremiumSoundSystem()
    {
        std::cout << "~PremiumSoundSystem()\n";
        delete _b;
    }
};

class ManualTransmission : public OptionsDecorator
{
    Car* _b;
public:
    ManualTransmission(Car* b)
    {
        _b = b;
    }
    std::string getDescription()
    {
        return _b->getDescription() + ", ManualTransmission";
    }

    double getCost()
    {
        return 0.30 + _b->getCost();
    }
    ~ManualTransmission()
    {
        std::cout << "~ManualTransmission()\n";
        delete _b;
    }
};

int main()
{
    //Create our Car that we want to buy
    Car* b = new CarModel1();

    std::cout << "Base model of " << b->getDescription() << " costs $" << b->getCost() << "\n";

    //Who wants base model let's add some more features

    b = new Navigation(b);
    std::cout << b->getDescription() << " will cost you $" << b->getCost() << "\n";
    b = new PremiumSoundSystem(b);
    b = new ManualTransmission(b);
    std::cout << b->getDescription() << " will cost you $" << b->getCost() << "\n";

    // WARNING! Here we leak the CarModel1, Navigation and PremiumSoundSystem objects!
    // Either we delete them explicitly or rewrite the Decorators to take 
    // ownership and delete their Cars when destroyed.
    delete b;

    return 0;
}