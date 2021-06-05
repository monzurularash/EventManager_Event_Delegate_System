#ifndef EventManager_EventManager_h
#define EventManager_EventManager_h

#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;

    // Abstract class for EventCallback to notify of a change
    class EventCallbackBase {
    public:
        virtual void execute() = 0;
    };
    
    // Event Handler class : Handles Callback
    template <typename T>
    class EventCallback : public EventCallbackBase{
        
        
    public:
        // Object of the Listener
        T *m_object;
        // Function for callback
        void (T::*m_fptr)(void);
        
        EventCallback(T *obj, void (T::*func)(void) ) {
            m_object = obj;
            m_fptr = func;
        }
        
        void execute() {
            (m_object->*m_fptr)();
        }
    };
    
    // class to create a event
    class Event {
        // To store all listeners of the event
        // An array would work, using a map just to keep track of listener count (not essential)
        
        std::map<int, EventCallbackBase*> EventCallbackMap;
        
        
        int count;
    public:
        
        Event(){
            count = 0;
        }
        
        template <typename T>
        void addListener(T *obj, void (T::*func)(void)) {
            
            EventCallbackBase *EventCallbackBase_p = new EventCallback<T>(obj, func); // every-time a listener subscribes, a callback_object will created and the address will be added to the map
            EventCallbackMap[count] = EventCallbackBase_p;
            count++;
            cout << "subscriber count" << count << endl; ;
            
        }
        
        void execute() {

            for (auto it = EventCallbackMap.begin(); it != EventCallbackMap.end(); ++it) {
                it->second->execute();
            }
        }
        
        
        void removeAllListener() {
            // I can unsubscribe all lister from an event in one go, not by listener (CURRENT LIMITATION)
           for ( auto it = EventCallbackMap.begin(); it !=EventCallbackMap.end(); ++it){
               delete it->second;
               EventCallbackMap.erase(it);
           }
        }
   
    };
    
    // TOP level Event Manager Class, will be used by user application
    class EventManager {
        
        std::map <string, Event*> EventTable;
        
        static EventManager *_Instance;
        
        EventManager(){};
    public:
        static EventManager* Instance() {
            if (!_Instance) {
                _Instance = new EventManager();
            }
            return _Instance;
        }
        
        void createEvent(string name) {

            if (EventTable.find(name) != EventTable.end()){
                return;
            }
            else{
                EventTable[name] = new Event();
            }
            
        }
        
        template <typename T>
        bool subscribe(string name, T *obj, void (T::*func)(void)) {
            
            if (EventTable.find(name) != EventTable.end()){
                EventTable[name]->addListener(obj, func);
                return true;
            }            
            else
                return false;
        }
        
        void execute(string name) {

            if (EventTable.find(name) != EventTable.end()){
                EventTable[name]->execute();
            }  
        }
        
        bool unsubscribe(string name) {
            
            if (EventTable.find(name) != EventTable.end()){
                EventTable[name]->removeAllListener();
                return true;
            }            
            else
                return false;
        }
        
        void destroyEvent(string name) {

            if (EventTable.find(name) != EventTable.end()){
                return;
            }
            else{
                delete EventTable[name];
            }
            
        }
        
    };


#endif
