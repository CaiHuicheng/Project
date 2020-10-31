// { dg-options "-std=gnu++17" }
// { dg-do compile { target c++17 } }

// Copyright (C) 2014-2020 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

#include <system_error>
#include <future>
using namespace std;

// These tests are rather simple, the front-end tests already test
// variable templates, and the library tests for the underlying
// traits are more elaborate. These are just simple sanity tests.

static_assert(is_error_code_enum_v<future_errc>
	      && is_error_code_enum<future_errc>::value, "");

static_assert(!is_error_code_enum_v<int>
	      && !is_error_code_enum<int>::value, "");

static_assert(is_error_condition_enum_v<errc>
	      && is_error_condition_enum<errc>::value, "");

static_assert(!is_error_condition_enum_v<int>
	      && !is_error_condition_enum<int>::value, "");
