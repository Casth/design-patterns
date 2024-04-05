#include <iostream>
#include <string>

class Car {
  public:
    virtual ~Car() {};
    virtual std::string ShowLevel() const = 0;
};

class LowEndCar : public Car {
  public:
    std::string ShowLevel() const override {
        return "(Low end car)";
    }
};

class HighEndCar : public Car {
  public:
    std::string ShowLevel() const override {
        return "(High end car)";
    }
};




class Factory {
  public:
    virtual ~Factory() {};
    virtual Car* FactoryMethod() const = 0;

    std::string CarCheck() const {
        Car* car = this->FactoryMethod();
        std::string result = "Factory has produced " + car->ShowLevel();
        delete car;
        return result;
    }
};

class LowEndFactory : public Factory {
  public:
    Car* FactoryMethod() const override {
        return new LowEndCar();
    }
};

class HighEndFactory : public Factory {
  public:
    Car* FactoryMethod() const override {
        return new HighEndCar();
    }
};



void ClientCode(const Factory& factory) {
    std::cout << "Client: build a car with interface.\n"
              << factory.CarCheck() << std::endl;
}


int main() {
    std::cout << "App: Launch with low end car.\n";
    Factory* factory_low_end = new LowEndFactory();
    ClientCode(*factory_low_end);
    std::cout << std::endl;

    std::cout << "App: Launch with high end car.\n";
    Factory* factory_high_end = new HighEndFactory();
    ClientCode(*factory_high_end);

    delete factory_low_end;
    delete factory_high_end;
    return 0;
}