#include "../include/stormscript.h"

void sts::newScope(int *y, std::vector<stsvars> *vars, std::vector<stsfunc> *functions) {
    int oldfsize = functions->size();
    int oldvsize = vars->size();

    for (*y; *y < expressions.size() && expressions[*y].tktype != CLOSEDCURL; *y += 1) {
        
        switch(expressions[*y].t) { // don't need to worry about TOKEN and ENDEXPR because they will be handled inside of functions
            case BUILTIN: 
                runBuiltin(y, vars, functions);
                break;
            case UNKNOWN: 
                runUnknown(y, vars, functions);
                break;
        }
    
    }

    if (oldfsize > 0)
        functions->erase(functions->begin() + oldfsize, functions->end());
    if (oldvsize > 0)
        vars->erase(vars->begin()+oldvsize, vars->end());
}