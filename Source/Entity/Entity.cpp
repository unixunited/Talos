// ========================================================================= //
// * Engine
// Copyright (C) 2015 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Jordan Sparks <unixunited@live.com> January 2015.
// ========================================================================= //
// File: Entity.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ========================================================================= //
// Defines Entity class.
// ========================================================================= //

#include "Component/ActorComponent.hpp"
#include "Component/ComponentMessage.hpp"
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
	for (ComponentList::iterator itr = m_components.begin();
		 itr != m_components.end();
		 ++itr){
		(*itr)->init(this, world);
	}
}

// ========================================================================= //

void Entity::destroy(World& world)
{
	for (ComponentList::iterator itr = m_components.begin();
		 itr != m_components.end();
		 ++itr){
		(*itr)->destroy(this, world);
	}
}

// ========================================================================= //

void Entity::update(World& world)
{
	for (ComponentList::iterator itr = m_components.begin();
		 itr != m_components.end();
		 ++itr){
		(*itr)->update(this, world);
	}
}

// ========================================================================= //

ComponentPtr Entity::attachComponent(const ComponentPtr component)
{
	m_components.push_back(component);
	return component;
}

// ========================================================================= //

void Entity::detachComponent(const ComponentPtr component)
{
	for (ComponentList::iterator itr = m_components.begin();
		 itr != m_components.end();){
		if (*itr == component){
			itr = m_components.erase(itr);
		}
		else{
			++itr;
		}
	}
}

// ========================================================================= //

const bool Entity::checkComponents(void) const
{
	for (ComponentList::const_iterator itr = m_components.begin();
		 itr != m_components.end();
		 ++itr){
		if ((*itr)->isInitialized() == false){
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
	for (ComponentList::iterator itr = m_components.begin();
		 itr != m_components.end();
		 ++itr){
		(*itr)->message(msg);
	}
}

// ========================================================================= //

ComponentPtr Entity::getComponentPtr(const unsigned int type) const
{
	// Must use a const_iterator since this function is bitwise constant.
	for (ComponentList::const_iterator itr = m_components.begin();
		 itr != m_components.end();
		 ++itr){
		// Determine if Component's name matches. This is considerably more
		// efficient than run-time dynamic type checking.
		if ((*itr)->getType() == type){
			return *itr;
		}
	}

	return nullptr;
}

// ========================================================================= //

ActorComponentPtr Entity::getActorComponent(void) const
{
	return static_cast<ActorComponentPtr>(
		this->getComponentPtr(Component::Type::Actor));
}

// ========================================================================= //