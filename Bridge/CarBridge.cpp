#include <iostream>
#include <string>

/**
 * The DriverAssistanceSystem defines the interface for classes for the implementation
 * of the vairous driver assistance systems.
*/
class DriverAssistanceSystem {
  public:
    virtual ~DriverAssistanceSystem() {}
    virtual std::string LongitudinalControlSubsystem() const = 0;
    virtual std::string LateralControlSubsystem() const = 0;
};

/**
 * The DriverAssistanceSystemSupplierA defines a concrete implementation of driver
 * assistance system, which comes from supplier A.
*/
class DriverAssistanceSystemSupplierA : public DriverAssistanceSystem {
  public:
    std::string LongitudinalControlSubsystem() const override {
        return "Driver assistance system of supplier A: 1x front radar + 1x front camera.\n";
    }
    std::string LateralControlSubsystem() const override {
        return "Driver assistance system of supplier A: 3x rear radars + 4 side radars.\n";
    }
};

/**
 * The DriverAssistanceSystemSupplierB defines a concrete implementation of driver
 * assistance system, which comes from supplier B.
*/
class DriverAssistanceSystemSupplierB : public DriverAssistanceSystem {
  public:
    std::string LongitudinalControlSubsystem() const override {
        return "Driver assistance system of supplier B: 2x front radars + 1x front camera.\n";
    }
    std::string LateralControlSubsystem() const override {
        return "Driver assistance system of supplier B: 2x rear radars + 2 side radars.\n";
    }
};

/**
 * The DriverAssistanceFeature defines the interface for the abstraction part, which
 * corresponds to the features built in the vehicle.
*/
class DriverAssistanceFeature {
  protected:
    DriverAssistanceSystem* driver_assistance_system_;

  public:
    DriverAssistanceFeature(DriverAssistanceSystem* driver_assistance_system) : driver_assistance_system_(driver_assistance_system) {
    }

    virtual ~DriverAssistanceFeature() {
    }

    virtual std::string AssistanceOperation() const {
        return "Driver assistance feature is realized with: \n" +
               this->driver_assistance_system_->LongitudinalControlSubsystem() +
               this->driver_assistance_system_->LateralControlSubsystem();
    }
};

/**
 * The ExtendedDriverAssistanceFeature is an extended abstraction / feature of the driver
 * assistance feature, in which the accuracy of all sensors (radars and cameras) are improved. 
*/
class ExtendedDriverAssistanceFeature : public DriverAssistanceFeature {
  public:
    ExtendedDriverAssistanceFeature(DriverAssistanceSystem* driver_assistance_system) : DriverAssistanceFeature(driver_assistance_system) {
    }

    std::string AssistanceOperation() const override {
        return "Extended driver assistance feature is realized with: \n" +
               this->driver_assistance_system_->LongitudinalControlSubsystem() +
               this->driver_assistance_system_->LateralControlSubsystem() +
               "with higher accuracy on all radars and camaras.\n";
    }
};

/**
 * The client code only depends on the DriverAssistanceFeature class (abstraction).
*/
void ClientCode(const DriverAssistanceFeature& driver_assistance_feature) {
    std::cout << driver_assistance_feature.AssistanceOperation();
}

/**
 * main code
*/
int main() {
    DriverAssistanceSystem* da_system = new DriverAssistanceSystemSupplierA;
    DriverAssistanceFeature* da_feature = new DriverAssistanceFeature(da_system);
    ClientCode(*da_feature);
    std::cout << std::endl;
    delete da_system;
    delete da_feature;
    
    da_system = new DriverAssistanceSystemSupplierB;
    da_feature = new ExtendedDriverAssistanceFeature(da_system);
    ClientCode(*da_feature);
    std::cout << std::endl;
    delete da_system;
    delete da_feature;
    
    da_system = new DriverAssistanceSystemSupplierA;
    da_feature = new ExtendedDriverAssistanceFeature(da_system);
    ClientCode(*da_feature);
    std::cout << std::endl;
    delete da_system;
    delete da_feature;

    return 0;
}