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

	void call(Event* event) {
		(instance->*memberFunction)(static_cast<EventType*>(event));
	}
};

using HandlerList = std::list<std::unique_ptr<HandlerFunctionBase>>;

class EventHandler {
private:
	std::map<EventTypeID, std::unique_ptr<HandlerList>> subscribers;

public:
	template<typename EventType>
	void publish(EventType* event) {
		if (subscribers[getEventTypeID<EventType>()] == nullptr) {
			return;
		}

		for (auto& handler : *subscribers[getEventTypeID<EventType>()]) {
			if (handler != nullptr)
				handler->exec(event);
		}
	}

	template<typename T, typename EventType>
	void subscribe(T* instance, void (T::*memberFunction)(EventType*)) {
		if (subscribers[getEventTypeID<EventType>()] == nullptr) {
			subscribers[getEventTypeID<EventType>()] = std::make_unique<HandlerList>();
		}

		subscribers[getEventTypeID<EventType>()]->push_back(std::make_unique<MemberFunctionHandler<T, EventType>>(instance, memberFunction));
	}
};


