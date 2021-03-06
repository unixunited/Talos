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
// File: EngineState.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ========================================================================= //
// Implements EngineState class.
// ========================================================================= //

#include "EngineState.hpp"
#include "World/World.hpp"

// ========================================================================= //

EngineState::EngineState(void) :
m_subject(),
m_world(new World()),
m_ui(nullptr),
m_active(false)
{

}

// ========================================================================= //

EngineState::~EngineState(void)
{

}

// ========================================================================= //