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
 
#ifndef HEADER_CSS_OPT
#define HEADER_CSS_OPT

#include <string>          // for string
#include "datastruct.hpp"  // for sstore

// Color compression function. Converts all rgb() values to #-values and uses the short-form if possible. Also replaces color names and codes.
std::string cut_color(std::string color);

// Compresses shorthand values. Example: margin:1px 1px 1px 1px -> margin:1px
std::string shorthand(std::string value);

// Compresses numbers (ie. 1.0 -> 1 or 1.100 -> 1.1 
std::string compress_numbers(std::string subvalue, std::string property = "", std::string function = "");

// Checks if the next word in a string from pos is a CSS property
bool property_is_next(std::string istring, const int pos);

// Compress font-weight
int c_font_weight(std::string& value);

// Merges selectors which have the same properties
void merge_selectors(sstore& input);

#endif // HEADER_CSS_OPT
