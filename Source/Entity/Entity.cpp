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
// File: Entity.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ========================================================================= //
// Defines Entity class.
// ========================================================================= //

#include "Component/ActorComponent.hpp"
#include "Component/CameraComponent.hpp"
#include "Component/ComponentMessage.hpp"
#include "Component/LightComponent.hpp"
#include "Component/ModelComponent.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Component/SceneComponent.hpp"
#include "Entity.hpp"

// ========================================================================= //

Entity::Entity(void) :
m_components(),
m_id(0),
m_next(nullptr)
{
    
}

// ========================================================================= //

Entity::~Entity(void)
{

}

// ========================================================================= //

void Entity::init(World& world)
{
    
}

// ========================================================================= //

void Entity::destroy(World& world)
{
    for (auto& itr : m_components){
        itr.second->destroy(this, world);
    }
}

// ========================================================================= //

void Entity::update(World& world)
{
    for (auto& itr : m_components){
        itr.second->update(this, world);
    }
}

// ========================================================================= //

ComponentPtr Entity::attachComponent(const ComponentPtr component)
{
    // Insert new ComponentPtr into hash table.
    m_components[&typeid(*component)] = component;

    // Notify all attached components of newly attached component.
    for (auto& itr : m_components){
        itr.second->onComponentAttached(component);
    }

    return component;
}

// ========================================================================= //

void Entity::detachComponent(const ComponentPtr component)
{
    m_components.erase(&typeid(*component));
    m_components[&typeid(*component)] = nullptr;
}

// ========================================================================= //

const bool Entity::checkComponents(void)
{
    for (auto& itr : m_components){
        if (itr.second->isInitialized() == false){
            return false;
        }
    }

    return true;
}

// ========================================================================= //

void Entity::message(const ComponentMessage& msg)
{
    Assert(msg.type != ComponentMessageType::NIL, "NIL Entity message!");

    // Broadcast to all attached components.
    for (auto& itr : m_components){
        itr.second->message(msg);
    }
}

// ========================================================================= //