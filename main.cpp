
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
  
  //testEvent1 has subscriber : B,C,D 
  //testEvent2 has subscriber : C,D 
  //testEvent3 has subscriber : D 
  myEventManager->subscribe("testEvent1", obj1, &B::listener);
  myEventManager->subscribe("testEvent1", obj2, &C::listener);
  myEventManager->subscribe("testEvent1", obj3, &D::listener);
  
  myEventManager->subscribe("testEvent2", obj2, &C::listener);
  myEventManager->subscribe("testEvent2", obj3, &D::listener);
  
  myEventManager->subscribe("testEvent3", obj3, &D::listenerV1);
  
  myEventManager->execute("testEvent1");
  myEventManager->execute("testEvent2");  
  myEventManager->execute("testEvent3");
  
  
  myEventManager->unsubscribe("testEvent1");

  //testEvent1 has no subscriber 
  //testEvent2 has subscriber : C,D 
  //testEvent3 has subscriber : D   
  myEventManager->execute("testEvent1");
  myEventManager->execute("testEvent2");  
  myEventManager->execute("testEvent3"); 
  
  return 0;
}

