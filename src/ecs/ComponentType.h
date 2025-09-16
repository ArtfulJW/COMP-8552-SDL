//
// Created by User on 9/16/2025.
//

#ifndef COMP_8552_WEEK1_CLION_COMPONENTTYPE_H
#define COMP_8552_WEEK1_CLION_COMPONENTTYPE_H

#include <cstddef>

/*
 * Creating Type alias for std::size_t
 * size_t is designed to represent sizes and indices because it's unsigned and very large (long, long).
 */
using ComponentTypeID = std::size_t;

/*
 * Free function
 * Each cpp file that includes this header (ComponentType.h) would get its own causing linker error.
 * Using inline merges them into one definition.
 *
 * Global number generator; returns a number everytime we call it
 * Making it static means it keeps its value through multiple calls of this function.
 */
inline ComponentTypeID getComponentTypeID() {
    static ComponentTypeID id = 0;
    return id++;
}

/*
 * Overloaded function because they have different function signatures
 * Template functions are by default, inline.
 *
 * getComponentTypeID<Position>() -> always return 0
 * getComponentTypeID<Health>() -> always return 1
 * A static local variable is only ever created and initialized once.
 */
template <typename T>
ComponentTypeID getComponentTypeID() {
    static ComponentTypeID typeID = getComponentTypeID();
    return typeID;
}

#endif //COMP_8552_WEEK1_CLION_COMPONENTTYPE_H