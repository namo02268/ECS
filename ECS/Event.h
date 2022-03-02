#pragma once

#include <iostream>
#include <list>
#include <map>

#include "IdGenerator.h"

class Event {
public:
	virtual ~Event() {}
};

class HandlerFunctionBase {
public:
	virtual ~HandlerFunctionBase() {}
	void exec(Event* event) {
		call(event);
	}

private:
	virtual void call(Event* event) = 0;
};

template<typename T, typename EventType>
class MemberFunctionHandler : public HandlerFunctionBase {

	typedef void (T::*MemberFunction)(EventType*);

private:
	// instance of system class
	T* instance;
	// member function of the above instance
	MemberFunction memberFunction;

public:
	MemberFunctionHandler(T* instance, MemberFunction memberFunction) 
		: instance{instance}, memberFunction(memberFunction) {}

	void Call(Event* event) {
		(instance->*memberFunction)(static_cast<EventType*>(event));
	}
};

using HandlerList = std::list<HandlerFunctionBase*>;

class EventHandler {
private:
	std::map<EventTypeID, HandlerList*> subscribers;

public:
	template<typename EventType>
	void publish(EventType* event) {
		auto handlers = subscribers[getEventTypeID<EventType>()];

		if (handlers == nullptr) {
			return;
		}

		for (auto& handler : *handlers) {
			if (handler != nullptr)
				handler->exec(event);
		}
	}

	template<typename T, typename EventType>
	void subscribe(T* instance, void (T::*memberFunction)(EventType*)) {
		auto handlers = subscribers[getEventTypeID<EventType>()];

		if (handlers == nullptr) {
			subscribers[getEventTypeID<EventType>()] = new HandlerList();
		}

		handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
	}
};


