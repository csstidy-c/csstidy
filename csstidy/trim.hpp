/*
 * Copyright 2005, 2006, 2007 Florian Schmitz
 *
 * This file is part of CSSTidy.
 *
 *  CSSTidy is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   CSSTidy is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 * 
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
 
#ifndef HEADER_CSS_TRIM
#define HEADER_CSS_TRIM 

#include <string>    // for string

// Removes whitespace at the end and beginning of a string
const std::string trim(const std::string istring);

// Removes whitespace at the beginning of a string
const std::string ltrim(const std::string istring);

// Removes whitespace at the end of a string
const std::string rtrim(const std::string istring);
const std::string rtrim(const std::string istring, const std::string chars);

// Removes HTML tags
std::string strip_tags(std::string istring);

#endif // HEADER_CSS_TRIM
