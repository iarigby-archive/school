#ifndef SEMANTICS_H
#define SEMANTICS_H
#include <iostream>
#include <map>
#include <string>
#include <sstream>

enum type {integer, boolean};

struct var_data {
    var_data() {}
    var_data(int r, type t) {
      decl_row = r;
      var_type = t;
    }
    int decl_row;
    type var_type;
};

#endif // SEMANTICS_H
