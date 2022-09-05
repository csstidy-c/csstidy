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
 
#ifndef HEADER_CSS_BACKGROUND
#define HEADER_CSS_BACKGROUND 

#include <map>     // for map
#include <string>  // for string
#include <vector>  // for vector
template <class keyT, class valT> class umap;

// Dissolves the background property
std::map<std::string,std::string> dissolve_short_bg(const std::string istring);

// Same as explode, but not within a string
std::vector<std::string> explode_ws(char sep, std::string istring);

void merge_bg(umap<std::string,std::string>& css_input);

#endif // HEADER_CSS_BACKGROUND
