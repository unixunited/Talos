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
// File: stdafx.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ========================================================================= //
// A single point of access for needed headers.
// ========================================================================= //

#ifndef __STDAFX_HPP__
#define __STDAFX_HPP__

// ========================================================================= //

// My own files.
#include "Typedefs.hpp"
#include "Core/HelperFunctions.hpp"
#include "Core/Assert.hpp"
#include "Log/Log.hpp"
#include "Rendering/GraphicsSettings.hpp"

// C++.
#include <list>
#include <map>
#include <stack>
#include <thread>

// Boost.
#include <boost/variant.hpp>

// Ogre3D.
#include <Ogre.h>

// SDL.
#include <SDL.h>
#include <SDL_syswm.h>

// CEGUI.
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

// Define NDEBUG for PhysX in release mode.
#ifndef _DEBUG
#define NDEBUG
#endif

// PhysX.
#include <PxPhysicsAPI.h>

// RakNet.
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <BitStream.h>
#include <GetTime.h>

// irrKlang.
#include <irrKlang.h>

#ifdef WIN32
#define _WINSOCKAPI_ // Prevent automatic inclusion of winsock.h.
#endif

// ========================================================================= //

#endif

// ========================================================================= //