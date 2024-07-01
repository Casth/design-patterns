# design-patterns

## Creational Design Patterns
Creational design patterns provide object creation mechanisms, which increase flexibility and reuse of existing code. Five patterns are explained: factory, abstract factory, builder, prototype, singleton.
- ✅ **Factory method** reduces the coupling between the constructor and the product by defining interfaces for them. New constructor and product objects (following the interfaces) can be instantiated without affecting existing code.
- ✅ **Abstract factory** is similar to factory method, and extends the constructor's ability to constructing a family of various products via defined interfaces. The coupling between the constructor and the product is loose.
- ✅ **Builder** separates the construction steps of a complex product from its representing (material, color, and further variants). Therefore, same construction process can be followed to created different variants of product.
- ⌛️ **Prototype** allows to create instance of objects by calling the "clone" method defined in the interface.
- 📌 **Singleton** allows only one instance of a class by defining the interface with a single point of access to the instance.

---

## Structural Design Patterns
Structural design patterns explain how to assemble objects and classes into larger structures, while keeping these structures flexible and efficient. Seven patterns are described: adapter, bridge, composite, decorator, facade, flyweight, proxy.
- **Adapter** converts the interface of a class into another interface that the client expects.
- ✅ **Bridge** extracts the abstraction (high-level functionality such as feature) from its implementation, and defines the abstraction and the implementation in a class and an interface respectively. As result, the abstraction and the implementation can vary independently.
- 📌 **Composite** creates tree-like structure consisting of containers and leave using the same interface. This enables the uniformed (recursive) call of the elements in the tree independently from their classes (container or leaf).
- **Decorator** adds additional functionality dynamically to an object by wrapping the object recursively.
- **Facade** creates a unified interface to multiple interfaces of a subsystem, which makes the subsystem easier to use.
- 📌 **Flyweight** reduces the memory usage by separating the intrinsic (value varies rarely) and extrinsic (value varies frequently) attributes. The flyweight class contains only intrinsic attributes. Only unique flyweight object are allowed to instantiate, which will then be extended with different extrinsic attributes.
- **Proxy** adds pre-processing functionality to an existing service while keeping the interfaces to the client identical as the original service.

---

## Behavioral Design Patterns
Behavioral design patterns are concerned with algorithms and assignment of responsibilities between objects. 10 patterns are described: chain of responsibility (CoR), command, iterator, mediator, memento, observer, state, strategy, template method, visitor.
- **Chain of responsibility (CoR)** chains multiple handlers of request and lets them decide either to process the request or pass it to the next handler in the chain.
- **Command** turns request between sender and receiver into stand-alone object that carries request arguments, and therefore decouples the sender and receiver.
- **Iterator** decouples the data collection from the real data operation by turning the data operation into an object (iterator). The real data structure is hidden to the client.
- **Mediator** directs all communications among the components to a single mediator, not allowing direct communication between the components. At event, components notify the mediator, which then decides the component(s) to do the work.
- **Memento** initializes the capturing and storing of an object's internal states from the object itself, and keeps them in a stack of mementos. Later, the states can be restored from the mementos.
- **Observer** realizes the publisher-subscriber relationship. The publisher keeps a dynamic (changeable in runtime) list of the subscribers, and notifies them at associated changes.
- **State** allows a class to have state-specific behaviors by encapsulating each state and its associated operations as an object. 
- **Strategy** allows a class to use various algorithms by defining a family of algorithms, and encapsulates each one as an object, with all algorithm objects independent from each other.
- **Template method** defines a skeleton of operations, and defers the detailed definition of the operations in the subclasses.
- **Visitor** allows to apply different variants of the same operation on objects of different classes. Depending on the object's class, the corresponding operation variant will be called.