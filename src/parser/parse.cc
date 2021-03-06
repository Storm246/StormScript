#include "../stormscript.h"
#include "../sts_files.h"
#include "sts_parser.h"

/*
the interpreter parses the file and calls functions in other files
*/
void parse() {
	int y = 0;
	
	while (y!=parserProgram.size()){
		int z = 0;
		bool inquotes = false;
		if (program.expressions.size() > 0)
			program.expressions.resize(program.expressions.size()+1);
		
		while (parserProgram[y][0]==' ')
			parserProgram[y].erase(parserProgram[y].begin());
		

		while (z!=parserProgram[y].size()){
			if (parserProgram[y][z]=='"'){
				if (inquotes == false)
					inquotes = true;
				else
					inquotes = false;
			}

			// this is what checks for chars to remove from prs version
			if (((parserProgram[y][z]==' ') || (parserProgram[y][z]=='\n') || (parserProgram[y][z]=='(') || (parserProgram[y][z]==')')) && (inquotes==false)){
				if ((program.expressions.back().contents.size() != 0))
					program.expressions.resize(program.expressions.size()+1);
				z++;
				program.expressions.back().line = y;
				continue;
			}
			else if ((parserProgram[y][z]=='#')) // line comment
				break;
			else if  (((parserProgram[y][z]==';') || (parserProgram[y][z]=='}') || (parserProgram[y][z]=='{')) && (inquotes==false)) {
				program.expressions.resize(program.expressions.size() + 1);
				program.expressions.back() = string(1,parserProgram[y][z]);
				program.expressions.back().line = y;
				break;
			}
			else if (((parserProgram[y][z]=='+') || (parserProgram[y][z]=='-') || (parserProgram[y][z]=='*') || ((parserProgram[y][z]=='/') && (program.expressions[program.expressions.size()-2].contents!="mod")) || (parserProgram[y][z]=='[') || (parserProgram[y][z]==',') || (parserProgram[y][z]==']') || (parserProgram[y][z] == ':') || (parserProgram[y][z] == '.')) && (inquotes==false)) {
				program.expressions.push_back( string(1,parserProgram[y][z]) );
				program.expressions.back().line = y;
				program.expressions.resize(program.expressions.size()+1);
			}
			else if ((parserProgram[y][z]=='\t')  && (inquotes==false)) {
				z++;
				program.expressions.back().line = y;
				continue;
			}
			else {
				if (program.expressions.size() == 0)
					program.expressions.push_back(expression());
				program.expressions.back().contents+=parserProgram[y][z];
			}
			program.expressions.back().line = y;
			z++;
		}
		y++;
	}

	for (int i = 0; i < program.expressions.size(); i++) {
		if ((program.expressions[i].contents=="\0") || (program.expressions[i].contents.size() == 0) || (program.expressions[i].contents=="\n") || 
			(program.expressions[i].contents.size() == 1 && program.expressions[i].contents[0] == 0)) { //this part makes sure that the last empty line is not parsed at all
			program.expressions.erase(program.expressions.begin() + i);
			i--; // we want to subtract one so that the parser does leave one of two consecutive blank expressions
		}
	 }

	evaluateProgram();
}
