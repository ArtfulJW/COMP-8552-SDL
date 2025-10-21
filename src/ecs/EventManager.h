//
// Created by super on 2025-10-02.
//

#ifndef COMP_8552_WEEK1_CLION_EVENTMANAGER_H
#define COMP_8552_WEEK1_CLION_EVENTMANAGER_H
#include <functional>

#include "Entity.h"

struct CollisionEvent
{
    Entity* entityA = nullptr;
    Entity* entityB = nullptr;
};

class EventManager
{
    public:
    // template<typename EventType>
    // void emit(const EventType& event)
    // {
    //     // Retrieve the list of subscribers to certain events
    //     auto& listeners = getListeners<EventType>();
    //
    //     // Look through all the subscribers to this event
    //     for (auto& listener : listeners)
    //     {
    //         // Invoke the function
    //         listener(event);
    //     }
    // }

    void emit(const CollisionEvent &collision) const {
        for (const auto& listener : collisionListeners) {
            listener(collision);
        }
    }

    // template<typename EventType>
    // void subscribe(std::function<void(const EventType&)> callback)
    // {
    //     // Pass in the callback wrapper/subscription to the list of subscriptions.
    //     getListeners<EventType>().push_back(callback);
    // }

    void subscribe(std::function<void(const CollisionEvent&)> callback) {
        collisionListeners.emplace_back(callback);
    }

private:

    // Each event type essentially has its own std::vector of listeners without us having to manage it explicitly.
    // This is done using the static local
    // std::function<void(const EventType&)> is the callable wrapper. Can hold anything that can be called like afunction (lamda, free function, functor)
    // template<typename EventType>
    // std::vector<std::function<void(const EventType&)>>& getListeners()
    // {
    //     static std::vector<std::function<void(const EventType&)>> listeners;
    //     return listeners;
    // }

    std::vector<std::function<void(const CollisionEvent&)>> collisionListeners;
};

#endif //COMP_8552_WEEK1_CLION_EVENTMANAGER_H