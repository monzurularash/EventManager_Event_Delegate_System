# EventManager_Event_Delegate_System

A simple implementation of generic and type-safe event-delegate system in C++11.
This EventManager allows any callback function from listener class to subscribe to any event.


How to Use:
A sample application (main.cpp) is provided for test.

snippet from sample test-application:
```
#include "EventManager.h"

class B {
public:
  void listener() {
    printf("Listener of B called\n");
  }

};

class C {
public:
  void listener() {
    printf("Listener of C called\n");
  }
};

class D {
public:
  void listener() {
    printf("Listener of D called\n");
  }
  void listenerV1() {
    printf("Listener2 of D called\n");
  }
};

int main() {

  
  B *obj1 = new B;
  C *obj2 = new C;
  D *obj3 = new D;
  
  EventManager *myEventManager = EventManager::Instance();
  myEventManager->createEvent("testEvent1");
  myEventManager->createEvent("testEvent2");  
  myEventManager->createEvent("testEvent3");  

  myEventManager->subscribe("testEvent1", obj1, &B::listener);
  myEventManager->subscribe("testEvent1", obj2, &C::listener);
  myEventManager->subscribe("testEvent1", obj3, &D::listener);
  
  myEventManager->subscribe("testEvent2", obj2, &C::listener);
  myEventManager->subscribe("testEvent2", obj3, &D::listener);
  myEventManager->subscribe("testEvent3", obj3, &D::listenerV1);
  
  myEventManager->execute("testEvent1");
  myEventManager->execute("testEvent2");  
  myEventManager->execute("testEvent3");
  
  
  return 0;
}
```

***
The EventManager can be used as a header only file (discarding the .cpp), if you have C++17, and you modify the following in the header:
change the line:
static EventManager *_Instance;
//Change this to:
inline static EventManager *_Instance;
***
