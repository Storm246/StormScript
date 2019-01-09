#include "../include/stormscript.h"

void sts::interp(string fname,int psize, char *argv[], int argc){
    prs = parse(prg);

    globvars.resize(globvars.size()+1);
    for (int x = 1; x<=argc-1; x++){
        globvars.back().type='l';
        globvars.back().vals.resize(globvars[globvars.size()-1].vals.size()+1);
        globvars.back().vals.back().type = 's';
        globvars.back().vals.back().val=argv[x];
        globvars.back().name="arg";
        globvars.back().glob=1;
    }
    
    for (int x = 0; x<prs.size(); x++){
        if (prs[x]=="lib"){
            names.resize(names.size()+1);
            x++;
            names[names.size()-1]=prs[x];
        }


        else if (prs[x]=="type") { // declares a class
            classes.resize(classes.size()+1);
            classes[classes.size()-1].declare(&x, this);
        }

        else if (prs[x]=="mod") {
            x++;
            addmodule(&x);
        }

        else if (prs[x]=="set") {
            x++;
            set(prs[x], prs[x+2], x);
            x+=2;
        }
        else if (prs[x]=="func"){
            functions.resize(functions.size()+1);
            x++;
            functions.back().name=prs[x];
            x++;

            if (prs[x]=="=>") {
                x++;
                std::vector<stsvars> args;

                while (prs[x]!="{") {
                    args.resize(args.size()+1);

                    args[args.size()-1].name = prs[x];
                    
                    x++;
                }
                x++;
                functions.back().args=args;
            }
            
            functions[functions.size()-1].linestarted=x;
            int endreq = 1;
            while (endreq != 0) {
                if ((prs[x]=="}") || (prs[x]=="loop"))
                    endreq--;
                else if (((prs[x]=="if") && (prs[x-1]!="else")) || (prs[x]=="else"))
                    endreq++;
                x++;
            }
            x--;
            if (prs[x]=="loop")
                x+=2;
        }
        else if (prs[x]=="do"){
            exec(&x, ((psize==-1) ? -2 : -1), {}, {});
        }
        else if ((prs[x]!=";") && (prs[x][0]!='\0')){
            error(1, prs[x]);
        }
    }
}   