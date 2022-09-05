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
 
#ifndef HEADER_CSS_MISC
#define HEADER_CSS_MISC 

#include <string>  // for string
#include <vector>  // for vector

// Checks if a charcter is escaped
bool escaped(const std::string &istring, int pos);

// Returns a char of a string at pos but checks the string-length before
char s_at(const std::string &istring, int pos);

// Splits a string at e
std::vector<std::string> explode(const std::string e, std::string s, const bool check = false);

// Implodes a string at e
std::string implode(const std::string e, const std::vector<std::string> s);

// Builds a compact value string, inserting spaces only where necessary
std::string build_value(const std::vector<std::string> subvalues);

// Replaces <find> with <replace> in <str>
std::string str_replace(const std::string find, const std::string replace, std::string str);

// Replaces all values of <find> with <replace> in <str>
std::string str_replace(const std::vector<std::string>& find, const std::string replace, std::string str);

// Checks if a string exists in a string-array
bool in_char_arr(const char* haystack, const char needle);
bool in_str_array(const std::string& haystack, const char needle);
bool in_str_array(const std::vector<std::string>& haystack, const std::string needle);

// Replaces certain chars with their entities
std::string htmlspecialchars(std::string istring, int quotes = 0);

// Rounds a float value
float round(const float &number, const int num_digits);

// Replacement for max (so that I don't have to include unnecessary things)
int max(const int i1, const int i2);

/* isspace() and isdigit() do not work correctly with UTF-8 strings */
bool ctype_space(const char c);
bool ctype_digit(const char c);
bool ctype_xdigit(char c);
bool ctype_alpha(char c);

/* Unserialise string arrays */
std::vector<std::string> unserialise_sa(const std::string istring);

/* Serialise a string */
std::string serialise_sa(const std::string istring);

#endif // HEADER_CSS_MISC
