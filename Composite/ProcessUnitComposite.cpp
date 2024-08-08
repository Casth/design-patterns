/**
 * Composite Design Pattern
 * 
 * In this example, a certain amount of processing units are grouped according to their 
 * functionality types together into a tree structure. In this tree structure, new units
 * are created, which don't have processing task, but only serve as a grouping node in 
 * the tree. If a task is given to a unit, it will process it if it is a processing unit, 
 * or it will pass it to its children units if it is a branch unit. 
 * 
*/

#include <algorithm>
#include <iostream>
#include <list>
#include <string>

// Unit is the interface for processing units and branch units
class Unit {
  protected:
    Unit *parent_unit_;
    std::string unit_name_;

  public:
    Unit(std::string unit_name) {
        this->unit_name_ = unit_name;
    }
    virtual ~Unit() {}
    // set parent unit
    void SetParentUnit(Unit *parent_unit) {
        this->parent_unit_ = parent_unit;
    }
    // get parent unit
    Unit *GetParentUnit() const {
        return this->parent_unit_;
    }
    virtual bool IsProcessingUnit() const = 0;  // check unit type 
    virtual void AddChildUnit(Unit *child_unit) {}  // add children to unit, this method remains empty in processing units
    virtual void RemoveChildUnit(Unit *child_unit) {}  // remove children from unit, this method remains empty in processing units
    virtual std::string ProcessingOperation() const = 0;  // interface for processing operation
};


// Processing unit is a leaf node in the tree
class ProcessingUnit : public Unit {
  public:
    using Unit::Unit;
    bool IsProcessingUnit() const override {
        return true;
    }
    std::string ProcessingOperation() const override {
        return "Processe by " + this->unit_name_ + ".\n";
    }
};


// Branch unit is a composite that includes 
class BranchUnit : public Unit {
  protected:
    std::list<Unit *> child_unit_;

  public:
    using Unit::Unit;
    void AddChildUnit(Unit *child_unit) override {
        this->child_unit_.push_back(child_unit);
        child_unit->SetParentUnit(this);
    }
    void RemoveChildUnit(Unit *child_unit) override {
        child_unit_.remove(child_unit);
        child_unit->SetParentUnit(nullptr);
    }
    bool IsProcessingUnit() const override {
        return false;
    }
    std::string ProcessingOperation() const override {
        std::string result;
        for (const Unit *unit : child_unit_) {
            if (unit == child_unit_.back()) {
                result += unit->ProcessingOperation();
            } else {
                result += unit->ProcessingOperation() + " + ";
            }
        }
        return "Branch(\n" + result + "\n)";
    }
};


// Client code 1 shows the tree structure
void ClientCodeShowTree(Unit *unit) {
    std::cout << "RESULT:\n" << unit->ProcessingOperation();
}

// Client code 2 puts unit2 as child element of unit1
void ClientCodeIncludeUnit(Unit *unit1, Unit *unit2) {
    if (!(unit1->IsProcessingUnit())) {
        unit1->AddChildUnit(unit2);
    }
}

int main() {
    // create tree containing only a single leaf
    Unit *unit_standalone = new ProcessingUnit("Standalone processing unit");
    ClientCodeShowTree(unit_standalone);
    std::cout << "\n---------------------------\n\n";

    // create a tree with a root node and two branches with 3 and 2 leaves respectively
    Unit *tree = new BranchUnit("Root grouping unit");
    Unit *branch_1 = new BranchUnit("Level 1 grouping unit of branch 1");
    Unit *branch_2 = new BranchUnit("Level 1 grouping unit of branch 2");
    Unit *leaf_1 = new ProcessingUnit("Processing unit 1");
    Unit *leaf_2 = new ProcessingUnit("Processing unit 2");
    Unit *leaf_3 = new ProcessingUnit("Processing unit 3");
    Unit *leaf_4 = new ProcessingUnit("Processing unit 4");
    Unit *leaf_5 = new ProcessingUnit("Processing unit 5");
    tree->AddChildUnit(branch_1);
    tree->AddChildUnit(branch_2);
    branch_1->AddChildUnit(leaf_1);
    branch_1->AddChildUnit(leaf_2);
    branch_1->AddChildUnit(leaf_3);
    branch_2->AddChildUnit(leaf_4);
    branch_2->AddChildUnit(leaf_5);
    ClientCodeShowTree(tree);
    std::cout << "\n---------------------------\n\n";

    // small modifications to the tree: add and remove a leaf
    ClientCodeIncludeUnit(tree, unit_standalone);
    branch_1->RemoveChildUnit(leaf_2);
    ClientCodeShowTree(tree);
    std::cout << "\n---------------------------\n\n";

}