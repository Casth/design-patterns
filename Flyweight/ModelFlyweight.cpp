/**
 * Flyweight Design Pattern
 * 
 * In this example, a 3D scene creation software is shown. It can create thousands of objects such as trees, 
 * houses, etc. In order to reduce memeory usage, the common (intrisic) attributes of the objects are modeled 
 * as Flyweight, such as color, texture. The individual (extrinsic) attributes are modeled as unique states, 
 * such as position, size, etc.
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

struct IntrinsicState {
    std::string color_;
    std::string texture_;

    IntrinsicState(const std::string &color, const std::string &texture) 
        : color_(color), texture_(texture) {}
};

struct ExtrinsicState {
    std::string position_;
    std::string size_;
    
    ExtrinsicState(const std::string &position, const std::string size) 
        : position_(position), size_(size) {}
};

class ModelFlyweight {
  private:
    IntrinsicState *intrinsic_state_;

  public:
    ModelFlyweight(const IntrinsicState *intrinsic_state) : intrinsic_state_(new IntrinsicState(*intrinsic_state)) {}
    ModelFlyweight(const ModelFlyweight &other) : intrinsic_state_(new IntrinsicState(*other.intrinsic_state_)) {}
    ~ModelFlyweight() {
        delete intrinsic_state_;
    }
    IntrinsicState *intrinsic_state() const {
        return intrinsic_state_;
    }
    void Operation (const ExtrinsicState &extrinsic_state) const {
        std::cout << "Shared (" << intrinsic_state_->color_ << ", " << intrinsic_state_->texture_ << ") and unique ("
                  << extrinsic_state.position_ << ", " << extrinsic_state.size_ << ") state. \n";
    }
};

class ModelFlyweightFactory {
  private:
    std::unordered_map<std::string, ModelFlyweight> model_flyweights_;
    std::string GetKey(const IntrinsicState &intrinsic_state) const {
        return intrinsic_state.color_ + "_" + intrinsic_state.texture_;
    }
  public:
    ModelFlyweightFactory(std::initializer_list<IntrinsicState> intrinsic_state_list) {
        for (const IntrinsicState &intrinsic_state : intrinsic_state_list) {
            this->model_flyweights_.insert(std::make_pair<std::string, ModelFlyweight>(this->GetKey(intrinsic_state), ModelFlyweight(&intrinsic_state)));
        }
    }

    ModelFlyweight GetFlyweight (const IntrinsicState &intrinsic_state) {
        std::string key = this->GetKey(intrinsic_state);
        if (this->model_flyweights_.find(key) == this->model_flyweights_.end()) {
            std::cout << "FlyweightFactory: Can't find a flyweight, creating new one.\n";
            this->model_flyweights_.insert(std::make_pair(key, ModelFlyweight(&intrinsic_state)));
        } else {
            std::cout << "FlyweightFactory: Reuse existing flyewight.\n";
        }
        return this->model_flyweights_.at(key);
    }
    void ListFlyweights() const {
        size_t count = this->model_flyweights_.size();
        std::cout << "FlyweightFactory: " << count << " flyweights.\n";
        for (std::pair<std::string, ModelFlyweight> pair : this->model_flyweights_) {
            std::cout << pair.first << "\n";
        }
    }
};