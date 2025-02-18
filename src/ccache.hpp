// Copyright (C) 2002-2007 Andrew Tridgell
// Copyright (C) 2009-2021 Joel Rosdahl and other contributors
//
// See doc/AUTHORS.adoc for a complete list of contributors.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 51
// Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#pragma once

#include "Config.hpp"

#include <functional>
#include <string>
#include <string_view>

class Context;

extern const char CCACHE_NAME[];
extern const char CCACHE_VERSION[];

using FindExecutableFunction =
  std::function<std::string(const Context& ctx,
                            const std::string& name,
                            const std::string& exclude_name)>;

int ccache_main(int argc, const char* const* argv);

// Tested by unit tests.
void find_compiler(Context& ctx,
                   const FindExecutableFunction& find_executable_function);
CompilerType guess_compiler(std::string_view path);
