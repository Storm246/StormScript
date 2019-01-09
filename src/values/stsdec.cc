#include "../include/stormscript.h"

/*
stsdec.cc: basic type declarations
*/

void stsvars::assignlist(sts *stsscript, std::vector<stsvars> vars, int *line) {
    sts script = *stsscript;
    int y = *line;
    std::vector<string> prs = script.prs;

    vals.erase(vals.begin(), vals.end());
    y++;
    while (prs[y]!="]") { // add variables to list
        vals.push_back(script.getval(vars, &y));
        y++;
    }
    y++;

    *line = y;
    *stsscript = script;
}


stsvars sts::declare(int *line, std::vector<stsvars> *vars) { //variable declarations
    char type;
    int y = *line+1;
    stsvars new_var = getval(*vars, new int(y));

    cout << new_var.type << '\n';

    new_var.name = prs[*line];
    // bad idea to pop back the line, just pop back the var

    new_var.name.pop_back();

    type = new_var.type;
    switch (type) {
        case 's':   new_var.length = new_var.val.size();
            vars->push_back(stsvars());
            vars->back().name = new_var.name + "|length";
            vars->back().val = std::to_string(new_var.length);
            vars->back().type = 'i';
            break;
        case 'l':   new_var.assignlist(this, *vars, &y);
            new_var.length = new_var.vals.size();
            vars->push_back(stsvars());
            vars->back().name = new_var.name + "|length";
            vars->back().val = std::to_string(new_var.length);
            vars->back().type = 'i';
            break;
    }
    *line = y;
    
    return new_var;
}