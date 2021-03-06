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
// File: PhysicsScene.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ========================================================================= //
// Implements PhysicsScene class.
// ========================================================================= //

#include "Cooker.hpp"
#include "Core/Talos.hpp"
#include "PDebugDrawer.hpp"
#include "PScene.hpp"

// ========================================================================= //

PScene::PScene(const std::shared_ptr<Physics> physics) :
m_physx(physics->m_physx),
m_scene(nullptr),
m_defaultMaterial(nullptr),
m_cpuDispatcher(nullptr),
m_controllerManager(nullptr),
m_debugDrawer(nullptr),
m_useDebugDrawer(false),
m_cooker(new Cooker(physics->m_physx, physics->m_cookingInterface))
{
    
}

// ========================================================================= //

PScene::~PScene(void)
{

}

// ========================================================================= //

const bool PScene::init(void)
{
    PxSceneDesc desc(m_physx->getTolerancesScale());
    desc.gravity = PxVec3(0.f, -9.81f, 0.f);

    if (!desc.cpuDispatcher){
        m_cpuDispatcher = PxDefaultCpuDispatcherCreate(4);
        if (!m_cpuDispatcher){
            return false;
        }
        desc.cpuDispatcher = m_cpuDispatcher;
    }

    if (!desc.filterShader){
        desc.filterShader = PxDefaultSimulationFilterShader;
    }

#ifdef PX_WINDOWS
    // CUDA...
#endif

    // Create the physX scene.
    m_scene = m_physx->createScene(desc);
    if (!m_scene){
        return false;
    }

    // Create default material.
    m_defaultMaterial = m_physx->createMaterial(0.5f, 0.5f, 0.1f);
    m_cooker->setDefaultMaterial(m_defaultMaterial);

    // Create character controller manager.
    m_controllerManager = PxCreateControllerManager(*m_scene);

    return true;
}

// ========================================================================= //

void PScene::destroy(void)
{
    m_controllerManager->release();
    m_defaultMaterial->release();
    m_scene->release();
    m_cpuDispatcher->release();
}

// ========================================================================= //

void PScene::simulate(PxReal speed)
{
    /*const PxReal step = 1.0f / 
        static_cast<PxReal>(Talos::MS_PER_UPDATE) * 
        speed;*/
    const PxReal step = 1.f / Talos::MS_PER_UPDATE;

    m_scene->simulate(step);
    m_scene->fetchResults(true);

    if (m_useDebugDrawer){
        m_debugDrawer->update();
    }
}

// ========================================================================= //

void PScene::loadDebugDrawer(void)
{
    m_debugDrawer.reset(new PDebugDrawer());
    m_useDebugDrawer = true;
}

// ========================================================================= //

void PScene::addToDebugDrawer(PxRigidActor* actor, 
                              PxGeometry& geometry)
{
    Assert(m_debugDrawer != nullptr, "Un-allocated debug drawer");

    m_debugDrawer->add(actor, geometry);
}

// ========================================================================= //

bool PScene::raycast(Ray& ray)
{
    PxQueryFilterData fd;
    fd.flags |= ray.flags;

    return m_scene->raycast(ray.origin,
                            ray.dir,
                            ray.dist,
                            ray.hit,
                            PxHitFlags(PxHitFlag::eDEFAULT),
                            fd);
}

// ========================================================================= //

// Getters:

// ========================================================================= //

PxPhysics* PScene::getSDK(void) const
{
    return m_physx;
}

// ========================================================================= //

PxScene* PScene::getScene(void) const
{
    return m_scene;
}

// ========================================================================= //

PxMaterial* PScene::getDefaultMaterial(void) const
{
    return m_defaultMaterial;
}

// ========================================================================= //

PxControllerManager* PScene::getControllerManager(void) const
{
    return m_controllerManager;
}

// ========================================================================= //

const bool PScene::isUsingDebugDrawer(void) const
{
    return m_useDebugDrawer;
}

// ========================================================================= //

std::shared_ptr<Cooker> PScene::getCooker(void) const
{
    return m_cooker;
}

// ========================================================================= //