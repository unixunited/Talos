// ========================================================================= //
// * Engine
// Copyright (C) 2015 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Jordan Sparks <unixunited@live.com> January 2015.
// ========================================================================= //
// File: IntroState.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ========================================================================= //
// Implements IntroState class.
// ========================================================================= //

#include "Command/Command.hpp"
#include "Component/ActorComponent.hpp"
#include "Component/ComponentMessage.hpp"
#include "Component/CameraComponent.hpp"
#include "Component/ModelComponent.hpp"
#include "Component/SceneComponent.hpp"
#include "Input/Input.hpp"
#include "IntroState.hpp"
#include "Physics/PScene.hpp"
#include "World/World.hpp"

// ========================================================================= //

IntroState::IntroState(void) :
EngineState()
{

}

// ========================================================================= //

IntroState::~IntroState(void)
{

}

// ========================================================================= //

void IntroState::enter(void)
{
	m_world.init();
	m_world.getInput()->setMode(Input::Mode::PLAYER);

	// Create scene manager.
	Ogre::SceneManager* scene = m_world.getSceneManager();

	scene->setAmbientLight(Ogre::ColourValue::White);

	scene->setSkyDome(true, "Clouds");

	m_player = m_world.createEntity();
	ActorComponentPtr actorComponent = m_world.createActorComponent();
	m_player->attachComponent(actorComponent);
	CameraComponentPtr cameraComponent = m_world.createCameraComponent();
	m_player->attachComponent(cameraComponent);
	m_player->init(m_world);

	actorComponent->attachCamera(cameraComponent->getCamera());

	m_ogre = m_world.createEntity();
	SceneComponentPtr sceneComponent = m_world.createSceneComponent();
	m_ogre->attachComponent(sceneComponent);
	ModelComponent* model = m_world.createModelComponent();
	model->setMeshFilename("ogrehead.mesh");
	m_ogre->attachComponent(model);
	m_ogre->init(m_world);

	sceneComponent->attachObject(model->getOgreEntity());
	sceneComponent->getSceneNode()->setPosition(0.f, -10.f, -50.f);

	// Setup GUI.
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

	/*CEGUI::Window* root = wmgr.createWindow("DefaultWindow", "root");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);

	CEGUI::FrameWindow* fwnd = static_cast<CEGUI::FrameWindow*>(
		wmgr.createWindow("AlfiskoSkin/FrameWindow", "testWindow"));
	root->addChild(fwnd);
	fwnd->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0.f),
		CEGUI::UDim(0.25f, 0.f)));
	fwnd->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0.f), CEGUI::UDim(0.5f, 0.f)));
	fwnd->setText("Hello world!");

	CEGUI::Window* quit = wmgr.createWindow("AlfiskoSkin/Button", "root/quit");
	quit->setText("Quit");
	quit->setSize(CEGUI::USize(CEGUI::UDim(0.15f, 0.f), CEGUI::UDim(0.05f, 0.f)));
	fwnd->addChild(quit);*/
	//quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&IntroState::quit, this));

	PxMaterial* mat = m_world.getPScene()->m_physx->createMaterial(0.5f, 0.5f, 0.1f);
	dyn = PxCreateDynamic(*m_world.getPScene()->m_physx,
										  PxTransform(PxVec3(0.f, 150.f, 0.f)),
										  PxSphereGeometry(15.f),
										  *mat,
										  PxReal(11.3f));
	//dyn->setLinearVelocity(PxVec3(0.f, 40.f, 0.f));
	m_world.getPScene()->m_scene->addActor(*dyn);

	// Plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
												  plane, 1500, 1500, 20, 20, true, 1, 10, 10, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* eGround = m_world.getSceneManager()->createEntity("GroundEntity", "ground");
	m_world.getSceneManager()->getRootSceneNode()->createChildSceneNode("GroundNode")->attachObject(eGround);
	eGround->setMaterialName("Board");
	m_world.getSceneManager()->getSceneNode("GroundNode")->translate(0.f, -50.f, 0.f);

	/*PxRigidStatic* p = PxCreatePlane(*m_world.getPScene()->m_physx,
									 PxPlane(PxVec3(0.f, 1.f, 0.f), 50.f),
									 *mat);*/
	PxRigidStatic* p = PxCreateStatic(*m_world.getPScene()->m_physx,
									  PxTransform(PxVec3(0.f, -50.f, 0.f)),
									  PxBoxGeometry(750.f, 0.5f, 750.f),
									  *mat);
	m_world.getPScene()->m_scene->addActor(*p);
}

// ========================================================================= //

void IntroState::exit(void)
{
	m_player->destroy(m_world);
	m_world.destroy();
}

// ========================================================================= //

void IntroState::update(void)
{
	if (m_active == true){
		m_world.update();

		PxReal step = 1.f / 16.f;
		m_world.getPScene()->simulate(step);

		PxTransform transform = dyn->getGlobalPose();
		PxVec3 p = transform.p;
		PxQuat q = transform.q;
		
		SceneComponentPtr s = static_cast<SceneComponentPtr>(m_ogre->getComponentPtr("SceneComponent"));

		s->getSceneNode()->setPosition(p.x, p.y, p.z);
		s->getSceneNode()->setOrientation(q.w, q.x, q.y, q.z);

		

		// Poll SDL for events.
		SDL_Event e;
		while (SDL_PollEvent(&e)){
			switch (e.type){
			default:
				break;

			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEMOTION:
			case SDL_KEYDOWN:
				{
					CommandPtr command = m_world.getInput()->handle(e);
					if (command != nullptr){
						command->execute(m_player);
					}

					if (e.key.keysym.sym == SDLK_e){
						dyn->setLinearVelocity(PxVec3(20.f, 0.f, 0.f));
					}
					else if (e.key.keysym.sym == SDLK_r){
						dyn->setLinearVelocity(PxVec3(0.f, 3.f, 20.f));
					}
				}
				break;

			case SDL_KEYUP:
				{
					CommandPtr command = m_world.getInput()->handle(e);
					if (command != nullptr){
						command->unexecute(m_player);
					}
				}
				break;

			case SDL_QUIT:
				m_subject.notify(1);
				break;
			}
		}
	}
}

// ========================================================================= //