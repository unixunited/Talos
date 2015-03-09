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
// File: CollisionComponent.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ========================================================================= //
// Defines CollisionComponent class.
// ========================================================================= //

#ifndef __COLLISIONCOMPONENT_HPP__
#define __COLLISIONCOMPONENT_HPP__

// ========================================================================= //

#include "Component.hpp"

// ========================================================================= //

using namespace physx;

// ========================================================================= //
// A static collision object in the physics simulation.
class CollisionComponent : public Component
{
public:
    // Default initializes member data.
    explicit CollisionComponent(void);

    // Empty destructor.
    virtual ~CollisionComponent(void) override;

    // Methods of creating collision volume.
    enum class Type{
        Box,
        Mesh,
        Plane
    };

    // Empty.
    virtual void init(World& world) override;

    // Initializes PhysX actor, adds to World's PxScene.
    virtual void init(World& world,
                      EntityPtr entity);

    // Removes PhysX actor from World's PxScene.
    virtual void destroy(World& world) override;

    // Retrieves the actor's position and orientation, applies them to the
    // attached SceneComponent for rendering.
    virtual void update(World& world) override;

    // Empty.
    virtual void message(const ComponentMessage& msg) override;

    // Getters:

    // Returns position in form of Ogre::Vector3.
    const Ogre::Vector3 getPosition(void) const;

    // Returns position in form of Ogre::Quaternion.
    const Ogre::Quaternion getOrientation(void) const;

    // Setters:

    // Sets type of collision
    void setType(const Type& type);

private:
    PxRigidStatic* m_rigidActor;
    Type m_type;
    EntityID m_entityID;
};

// ========================================================================= //

// Setters:

inline void CollisionComponent::setType(const Type& type){
    m_type = type;
}

// ========================================================================= //

#endif

// ========================================================================= //