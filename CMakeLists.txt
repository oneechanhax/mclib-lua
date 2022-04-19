
# Libpdraw: A Versitile GUI for use with a primitive drawing system!
# Copyright (C) 2022 Rebekah Rowe
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# libpdraw
cmake_minimum_required (VERSION 3.20)
project (mclib-lua VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

#find_package(Doxygen)
add_subdirectory(lib/mclib/)
find_package(Lua51 REQUIRED)
message(STATUS "GOt: ${LUA_INCLUDE_DIR}")
file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(mclib-lua SHARED ${sources})
target_include_directories(mclib-lua PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/" "${CMAKE_CURRENT_SOURCE_DIR}/lib/mclib/mclib/include/" ${LUA_INCLUDE_DIR}/lua5.1/ "${CMAKE_CURRENT_SOURCE_DIR}/lib/luaaa")
target_link_libraries(mclib-lua PRIVATE mclib ${LUA_LIBRARIES})

