// ========================================================================= //
// Talos - A 3D game engine with network multiplayer.
// Copyright(C) 2015 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
// File: EntityPool.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ========================================================================= //
// Defines EntityPool class.
// ========================================================================= //

#ifndef __ENTITYPOOL_HPP__
#define __ENTITYPOOL_HPP__

// ========================================================================= //

#include "Entity.hpp"

// ========================================================================= //
// Stores Entity objects in contiguous memory and accesses them in constant
// time.
class EntityPool
{
    friend class World;

public:
    // Allocates pool array, sets the next pointer of each Entity.
    explicit EntityPool(const int size);

    // Deallocates pool array.
    ~EntityPool(void);

    // Acquires the next available Entity, sets the ID and returns it.
    EntityPtr create(void);

    // Sets the next available Entity to the provided pointer.
    void destroy(EntityPtr);

private:
    EntityPtr m_pool;
    EntityPtr m_firstAvail;
    EntityID m_idCounter;
    int m_poolSize;
};

// ========================================================================= //

#endif

// ========================================================================= //