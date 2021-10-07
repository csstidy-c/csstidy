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
 
#ifndef HEADER_CSSTIDY
#define HEADER_CSSTIDY 

#include <map>             // for map
#include <string>          // for string, basic_string
#include <vector>          // for vector
#include "datastruct.hpp"  // for token, css_struct, message_type, token_type

class csstidy 
{ 
	public: 
		int         properties,selectors,input_size,output_size;
		std::string charset,namesp, css_level;
		std::vector<std::string>             import, csstemplate;
		std::map<int, std::vector<message> > logs;
		std::map<std::string, int>           settings;
	
	private:
		css_struct    css;
		std::vector<token> csstokens;
		std::string        tokens, cur_selector, cur_at, cur_property, cur_function, cur_sub_value, cur_value, cur_string;
		int           line;
		std::vector<int>   sel_separate;

		void add_token(const token_type ttype, const std::string data, const bool force = false);
		void _convert_raw_css();
		
		// Add a message to the message log
		void log(const std::string msg, const message_type type, int iline = 0);
		
		int _seeknocomment(const int key, const int move);
		std::string _htmlsp(const std::string istring, const bool plain);
		std::string optimise_subvalue(std::string subvalue, const std::string property, const std::string function);
		void explode_selectors();
		
		// Parses unicode notations
		std::string unicode(std::string& istring,int& i);
		
		// Checks if the chat in istring at i is a token
		bool is_token(std::string& istring,const int i);
						
	public:
	    csstidy();
	    	
		// Adds a property-value pair to an existing CSS structure
		void add(const std::string& media, const std::string& selector, const std::string& property, const std::string& value);
	    void copy(const std::string media, const std::string selector, const std::string media_new, const std::string selector_new);
	
		// Prints CSS code
		void print_css(std::string filename = "");
		
		// Parse a piece of CSS code
		void parse_css(std::string css_input);
		
		/* Merges properties like margin */
		void merge_4value_shorthands(std::string media, std::string selector);
		
		/* Dissolves properties like padding:10px 10px 10px to padding-top:10px;padding-bottom:10px;... */
		std::map<std::string,std::string> dissolve_4value_shorthands(std::string property, std::string value);
};
	    
#endif // HEADER_CSSTIDY
