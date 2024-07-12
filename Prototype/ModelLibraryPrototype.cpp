/**
 * Prototype Design Pattern
 *
 * In this example, a library for 3D modeling is set up. The library contains multiple
 * reference objects, such as table, chair, human, etc. The user can create new object
 * by click-and-drag the reference object from the library into the workspace.
 *
 */

#include <iostream>
#include <string>
#include <unordered_map>

/**
 * Reference Object (prototype interface) is the interface for all the reference 
 * objects in library
 */
class ModelObject
{
protected:
    std::string object_name_;
    int object_size_;

public:
    ModelObject() {}
    ModelObject(std::string object_name) : object_name_(object_name) {}

    virtual ~ModelObject() {}
    virtual ModelObject *CloneObject() const = 0;
    virtual void SetSize(int object_size) {
        this->object_size_ = object_size;
        std::cout << "Object " << object_name_ << "'s size is set to " << object_size << std::endl;
    }
};

/**
 * Reference Table Object (concrete prototype 1)
 */
class ModelTableObject : public ModelObject
{
private:
    int table_size_;

public:
    ModelTableObject(std::string object_name, int object_size) : ModelObject(object_name), table_size_(object_size) {}

    ModelObject *CloneObject() const override {
        return new ModelTableObject(*this);
    }
};

/**
 * Reference Chair Object (concrete prototype 2)
 */
class ModelChairObject : public ModelObject
{
private:
    int chair_size_;

public:
    ModelChairObject(std::string object_name, int object_size) : ModelObject(object_name), chair_size_(object_size) {}

    ModelObject *CloneObject() const override {
        return new ModelChairObject(*this);
    }
};

/**
 * Model Library contains multiple reference objects
*/
class ModelLibrary {
  private:
    std::unordered_map<std::string, ModelObject *, std::hash<std::string>> reference_objects_;

  public:
    ModelLibrary() {
        reference_objects_["Table"] = new ModelTableObject("Table object", 60);
        reference_objects_["Chair"] = new ModelChairObject("Chair object", 40);
    }

    ~ModelLibrary() {
        delete reference_objects_["Table"];
        delete reference_objects_["Chair"];
    }

    ModelObject *CreateModelObject(std::string model_type) {
        return reference_objects_[model_type]->CloneObject();
    }
};


/**
 * Client code
*/
void Client(ModelLibrary &model_library) {
    std::cout << "Start to create a table\n";

    ModelObject *model_object = model_library.CreateModelObject("Table");
    model_object->SetSize(10);
    delete model_object;

    std::cout << "\n";
    
    std::cout << "Start to create a chair\n";

    model_object = model_library.CreateModelObject("Chair");
    model_object->SetSize(50);

    delete model_object;

    std::cout << "\n";
    
    std::cout << "Start to create another chair\n";

    model_object = model_library.CreateModelObject("Chair");
    model_object->SetSize(80);

    delete model_object;
}

int main() {
    ModelLibrary *model_library = new ModelLibrary();
    Client(*model_library);
    delete model_library;

    return 0;
}