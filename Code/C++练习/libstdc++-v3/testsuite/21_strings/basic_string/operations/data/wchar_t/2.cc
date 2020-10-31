// Copyright (C) 2016 Free Software Foundation, Inc.
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

// { dg-options "-std=gnu++17" }
// { dg-do run { target c++17 } }

// C++17 21.3.1.7 [string.ops] string operations

#include <string>
#include <testsuite_hooks.h>

void
test01()
{
  std::wstring s;
  wchar_t* p = s.data();
  VERIFY( *p == L'\0' );
  s = L"a string that is longer than a short string";
  p = s.data();
  VERIFY( p == &s.front() );
}

int
main()
{
  test01();
}
