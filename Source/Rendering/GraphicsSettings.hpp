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
// File: GraphicsSettings.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ========================================================================= //
// Defines Graphics struct and enumerates graphics setting values.
// ========================================================================= //

#ifndef __GRAPHICSSETTINGS_HPP__
#define __GRAPHICSSETTINGS_HPP__

// ========================================================================= //
// Graphics settings for rendering engine.
struct Graphics{

    enum Setting{
        Off = 0,
        Abysmal,
        Low,
        Medium,
        High,

        On
    };

    Setting meshes;
    Setting textures;
    Setting shadows;
    Setting ssao;
    Setting ocean;
    Setting sky;

    // Default initialize setting values.
    explicit Graphics(void) :
        meshes(Setting::Off),
        textures(Setting::Off),
        shadows(Setting::Off),
        ssao(Setting::Off),
        ocean(Setting::Off),
        sky(Setting::Off)
    { }
};

// ========================================================================= //

#endif

// ========================================================================= //