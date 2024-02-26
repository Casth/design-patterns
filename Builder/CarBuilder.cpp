#include <iostream>
#include <string>
#include <vector>

// product
class Car {
public:
    std::vector<std::string> parts_;
    void ListParts() const {
        std::cout << "Car parts: ";
        for (int i = 0; i < parts_.size(); i++) {
            if (parts_[i] == parts_.back()) {
                std::cout << parts_[i];
            }
            else {
                std::cout << parts_[i] << ", ";
            }
        }
        std::cout << "\n\n";
    }
};


// builder
class CarBuilder {
public:
    virtual ~CarBuilder(){}
    virtual void ProduceBody() const = 0;
    virtual void ProduceEngine() const = 0;
    virtual void ProduceSeat() const = 0;
    virtual void ProduceWheel() const = 0;
};


// concrete builder for small car
class SmallCarBuilder : public CarBuilder {
private:
    Car* car;

public:
    SmallCarBuilder() {
        this->Reset();
    }

    ~SmallCarBuilder() {
        delete car;
    }

    void Reset() {
        this->car = new Car();
    }

    void ProduceBody() const override {
        this->car->parts_.push_back("Small body");
    }

    void ProduceEngine() const override {
        this->car->parts_.push_back("Small engine");
    }

    void ProduceSeat() const override {
        this->car->parts_.push_back("Normal seat");
    }

    void ProduceWheel() const override {
        this->car->parts_.push_back("Normal wheel");
    }

    Car* GetCar() {
        Car* result = this->car;
        this->Reset();
        return result;
    }
};


// concrete builder for large car
class LargeCarBuilder : public CarBuilder {
private:
    Car* car;

public:
    LargeCarBuilder() {
        this->Reset();
    }

    ~LargeCarBuilder() {
        delete car;
    }

    void Reset() {
        this->car = new Car();
    }

    void ProduceBody() const override {
        this->car->parts_.push_back("Large body");
    }

    void ProduceEngine() const override {
        this->car->parts_.push_back("Large engine");
    }

    void ProduceSeat() const override {
        this->car->parts_.push_back("Normal seat");
    }

    void ProduceWheel() const override {
        this->car->parts_.push_back("Normal wheel");
    }

    Car* GetCar() {
        Car* result = this->car;
        this->Reset();
        return result;
    }
};


// director
class Director {
private:
    CarBuilder* car_builder;

public:
    void set_builder(CarBuilder* car_builder) {
        this-> car_builder = car_builder;
    }

    void BuildLowLevelCar() {
        this->car_builder->ProduceBody();
        this->car_builder->ProduceEngine();
        this->car_builder->ProduceSeat();
        this->car_builder->ProduceWheel();
    }

    void BuildHighLevelCar() {
        this->car_builder->ProduceBody();
        this->car_builder->ProduceEngine();
        this->car_builder->ProduceSeat();
        this->car_builder->ProduceSeat();
        this->car_builder->ProduceSeat();
        this->car_builder->ProduceSeat();
        this->car_builder->ProduceWheel();
    }
};


// client
void ClientCode(Director& director) {
    SmallCarBuilder* small_car_builder = new SmallCarBuilder();
    director.set_builder(small_car_builder);
    std::cout << "Small low level car:\n";
    director.BuildLowLevelCar();

    Car* low_lvl_car = small_car_builder->GetCar();
    low_lvl_car->ListParts();
    delete low_lvl_car;

    
    std::cout << "Small high level car:\n";
    director.BuildHighLevelCar();

    Car* high_lvl_car = small_car_builder->GetCar();
    high_lvl_car->ListParts();
    delete high_lvl_car;



    
    LargeCarBuilder* large_car_builder = new LargeCarBuilder();
    director.set_builder(large_car_builder);
    std::cout << "Large low level car:\n";
    director.BuildLowLevelCar();

    low_lvl_car = large_car_builder->GetCar();
    low_lvl_car->ListParts();
    delete low_lvl_car;

    
    std::cout << "Large high level car:\n";
    director.BuildHighLevelCar();

    high_lvl_car = large_car_builder->GetCar();
    high_lvl_car->ListParts();
    delete high_lvl_car;
}


int main() {
    Director* director = new Director();
    ClientCode(*director);
    delete director;
    return 0;
}