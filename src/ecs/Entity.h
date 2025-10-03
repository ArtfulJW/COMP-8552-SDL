//
// Created by User on 9/16/2025.
//

#ifndef COMP_8552_WEEK1_CLION_ENTITY_H
#define COMP_8552_WEEK1_CLION_ENTITY_H

#include <array>
#include <bitset>
#include <cstddef>

#include "ComponentType.h"

/*
 * Creates a constant that's evaluated at compile time.
 * 32 because it fits perfectly into a 32-bit integer.
 */
constexpr std::size_t MAX_COMPONENTS = 32;

/*
 * A bitset is like an array, but 1 or 0.
 * bitset[0] = 1; entity has a component
 * Bit operation are fast and work well for checking things each frame.
 */
using ComponentBitSet = std::bitset<MAX_COMPONENTS>;

/*
 * Fixed-size array, where each index is a Component (represented by void* pointer)
 * The index corresponds to the ComponentTypeID.
 * We use a fixed number of components so there's no dynamic allocation.
 */
using ComponentArray = std::array<void*, MAX_COMPONENTS>;

class Entity {
private:
    bool active = true;
    ComponentArray componentArray{};
    ComponentBitSet componentBitSet{};

public:
    bool isActive() const {
        return active;
    }

    void destroy() {
        active = false;
    }

    /*
     * Templates need to be implemeted in header
     * Entity.hasComponent<Position>() -> returns true or false.
     */
    template <typename T>
    bool hasComponent() {
        return componentBitSet[getComponentTypeID<T>()];
    }

    /*
     * Template arguement that can receive multiple arguments
     * Ex:
     * Entity.addComponent<Position>(3,4)
     * Entity.addComponent<Health>(100)
     */
    template<typename T, typename... nArgs>
    T& addComponent(nArgs&&... args) {
        // Implements Perfect Fowarding; everything is not treated as a l-value. More efficient with moves and temporaries.
        T* component(new T(std::forward<nArgs>(args)...));

        // Add the new component to the Array
        componentArray[getComponentTypeID<T>()] = component;
        componentBitSet[getComponentTypeID<T>()] = true;

        return *component;
    }

    /*
     * entity.getComponent<Health>()
     */
    template<typename T>
    T& getComponent() {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

    template<typename T>
    void deactivateComponent() {
        componentBitSet[getComponentTypeID<T>()] = false;
    }
};

#endif //COMP_8552_WEEK1_CLION_ENTITY_H