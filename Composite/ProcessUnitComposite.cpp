/**
 * Composite Design Pattern
 * 
 * In this example, a certain amount of processing units are grouped according to their 
 * functionality together into a tree structure. In this tree structure, new category
 * units are created, which don't have processing task, but only serve as a grouping node
 * in the tree. If a task is given to a unit, it will process it if it is a processing 
 * unit, or it will pass it to its children units if it is a category unit. 
 * 
*/

// Unit is the interface for processing units and placeholder units
class Unit {

};


// Processing unit is a leaf node in the tree
class ProcessingUnit : public Unit {

};


// Category unit is a composite that includes 
class CategoryUnit : public Unit {

};


// Client
void ClientCode(Unit *unit) {

}

int main() {
    
}