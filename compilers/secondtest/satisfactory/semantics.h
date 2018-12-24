#ifndef SEMANTICS_H
#define SEMANTICS_H

#include<iostream>
#include<string>
#include<map>
#include<sstream>

enum type { integer, boolean };

struct expression_descriptor {
	type expr_type;
	std::string expr_code;
	expression_descriptor(type t, std::string s) {
		expr_type = t;
		expr_code = s;
	}
};

struct var_data {
	int decl_row;
	type decl_type;
    std::string label;
	bool is_const = false;
	bool can_assign = true;
	var_data(){}
	var_data(int i, type t, std::string l)
	{
		decl_row = i;
		decl_type = t;
        label = l;
	}
	var_data(int i, type t, std::string l, bool c)
	{
		decl_row = i;
		decl_type = t;
        label = l;
		if (c) {
			is_const = true;
		}
	}
};

#endif
