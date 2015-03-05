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
// File: PhysicsComponent.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ========================================================================= //
// Implements StaticPhysicsComponent class.
// ========================================================================= //

#include "Entity/Entity.hpp"
#include "Physics/PScene.hpp"
#include "PhysicsComponent.hpp"
#include "SceneComponent.hpp"
#include "World/World.hpp"

// ========================================================================= //

PhysicsComponent::PhysicsComponent(void) :
Component(),
m_sActor(nullptr),
m_dActor(nullptr),
m_actor(nullptr),
m_mat(nullptr)
{
    
}

// ========================================================================= //

PhysicsComponent::~PhysicsComponent(void)
{

}

// ========================================================================= //

void PhysicsComponent::init(World&)
{

}

// ========================================================================= //

void PhysicsComponent::init(World& world, 
                            EntityPtr entity,
                            const Type type,
                            PxGeometry& geometry,
                            const PxReal staticFriction,
                            const PxReal dynamicFriction,
                            const PxReal restitution,
                            const PxReal density)
{
    // Create the physics material.
    if (staticFriction == 0.5f &&
        dynamicFriction == 0.5f &&
        restitution == 0.1f){
        // Use default if no material parameters were specified/changed.
        m_mat = world.getPScene()->getDefaultMaterial();
    }
    else{
        // Create a new material.
        m_mat = world.getPScene()->getSDK()->createMaterial(staticFriction,
                                                            dynamicFriction,
                                                            restitution);
    }

    // Create a static PhysX actor.
    if (type == Type::STATIC){
        m_sActor = PxCreateStatic(*world.getPScene()->getSDK(),
                                  PxTransform(PxVec3(0.f, 0.f, 0.f)),
                                  geometry,
                                  *m_mat);

        world.getPScene()->getScene()->addActor(*m_sActor);
        m_actor = m_sActor;
    }
    // Create a dynamic PhysX actor.
    else if(type == Type::DYNAMIC){
        m_dActor = PxCreateDynamic(*world.getPScene()->getSDK(),
                                   PxTransform(PxVec3(0.f, 0.f, 0.f)),
                                   geometry,
                                   *m_mat,
                                   density);
        
        world.getPScene()->getScene()->addActor(*m_dActor);
        m_actor = m_dActor;
    }

    if (m_actor != nullptr){
        // @TODO: Set to entity ID?
        m_actor->userData = static_cast<EntityPtr>(entity);

        // Add to debug drawer if activated.
        if (world.getPScene()->isUsingDebugDrawer()){
            world.getPScene()->addToDebugDrawer(m_actor, geometry);
        }        
    }

    // @TODO: Set user data of actor to EntityPtr?

    /*PxRigidStatic* p = PxCreatePlane(*m_world.getPScene()->m_physx,
    PxPlane(PxVec3(0.f, 1.f, 0.f), 50.f),
    *mat);*/

    this->setInitialized(true);
}

// ========================================================================= //

void PhysicsComponent::destroy(World& world)
{
    Assert(m_actor != nullptr, "Null m_actor!");

    world.getPScene()->getScene()->removeActor(*m_actor);

    this->setInitialized(false);
}

// ========================================================================= //

void PhysicsComponent::update(World& world)
{
    
}

// ========================================================================= //

void PhysicsComponent::message(const ComponentMessage&)
{

}

// ========================================================================= //

void PhysicsComponent::setPosition(const PxReal x, 
                                   const PxReal y , 
                                   const PxReal z)
{
    PxTransform transform = m_actor->getGlobalPose();

    transform.p.x = x;
    transform.p.y = y;
    transform.p.z = z;

    m_actor->setGlobalPose(transform, true);
}

// ========================================================================= //

// Sets PhysX pose orientation to this quaternion.
void PhysicsComponent::setOrientation(const PxReal w, 
                                      const PxReal x, 
                                      const PxReal y,
                                      const PxReal z)
{
    PxTransform transform = m_actor->getGlobalPose();

    transform.q.w = w;
    transform.q.x = x;
    transform.q.y = y;
    transform.q.z = z;

    m_actor->setGlobalPose(transform, true);
}

// ========================================================================= //

void PhysicsComponent::translate(const PxReal dx, 
                                 const PxReal dy, 
                                 const PxReal dz)
{
    PxTransform transform = m_actor->getGlobalPose();

    transform.p.x += dx;
    transform.p.y += dy;
    transform.p.z += dz;

    m_actor->setGlobalPose(transform, true);
}

// ========================================================================= //

void PhysicsComponent::rotate(const PxReal dx,
                              const PxReal dy,
                              const PxReal dz)
{
    // @TODO: This doesn't worK!
    PxTransform transform = m_actor->getGlobalPose();

    PxVec3 v(dx, dy, dz);
    //v.normalize();
    transform.rotate(v);

    m_actor->setGlobalPose(transform, true);
}

// ========================================================================= //

