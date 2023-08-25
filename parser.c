/* Noah Reynolds
Simon Tran
Franco Molina
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compiler.h"

#define MAX_CODE_LENGTH 200
#define MAX_SYMBOL_COUNT 50
#define MAX_REG_COUNT 10

// generated code
instruction *code;
int cIndex;

// symbol table
symbol *table;
int tIndex;

int symidx;

int level;
int listIndex;
int registerCounter;


// Tells the program, what error it says.
int errorType;

lexeme token;
lexeme *List;
int listIndex;

lexeme token;

int errorType;

void program(lexeme* list);
void block(lexeme *list);
int varDeclaration(lexeme *list);
void procedureDeclaration(lexeme* list);
void statement(lexeme *list);
void condition(lexeme *list);
void expression(lexeme *list);
void term(lexeme *list);
void factor(lexeme *list);
lexeme getToken(lexeme *list);
void emit(int opname, int reg, int level, int mvalue);
void addToSymbolTable(int k, char n[], int s, int l, int a, int m);
void mark();
int multipledeclarationcheck(char name[]);
int findsymbol(char name[], int kind);
void printparseerror(int err_code);
void printsymboltable();
void printassemblycode();

instruction *parse(lexeme *list, int printTable, int printCode)
{
	// set up program variables
	registerCounter = -1;
	code = malloc(sizeof(instruction) * MAX_CODE_LENGTH);
	cIndex = 0;
	table = malloc(sizeof(symbol) * MAX_SYMBOL_COUNT);
	tIndex = 0;
	listIndex = 0;
	errorType = 0;
	List = list;
	program(List);
	if(errorType != 0)
	{
		printparseerror(errorType);
	}
	// print off table and code
	if (printTable)
		printsymboltable();
	if (printCode)
		printassemblycode();

	// mark the end of the code
	code[cIndex].opcode = -1;
	return code;
}

void program(lexeme* list)
{
	int i;
	emit(7,0,0,0);
	addToSymbolTable(3,"main",0,0,0,0);
	level = -1;
	block(list);
	if(list[listIndex].type != periodsym)
		{
			errorType = 1;
			return;
		}
	emit(11,0,0,0);
	code[0].m = table[0].addr;

	for(i = 0;i < cIndex;i++)
	{
		if(code[i].opcode == 5)
		{
			code[i].m = table[code[i.m]].addr;
		}
	}
}

void block(lexeme *list)
{
	level++;
	int procIndex = tIndex - 1;
	int x = varDeclaration(list);
	if(errorType != 0)
		return;
	procedureDeclaration(list);
	if(errorType != 0)
		return;
	table[procIndex].addr = cIndex;
	emit(6,0,0,x);
	statement(list);
	mark();
	level--;
}

int varDeclaration(lexeme *list)
{
	int memorySize = 3;
	char *symbolName;
	int arraySize;
	if(list[listIndex].type == varsym)
	{
		do {
			listIndex++;
			if(list[listIndex].type != identsym)
			{
				errorType = 2;
				return 0;
			}
			if(multipledeclarationcheck(list[listIndex].name) != -1)
			{
				errorType = 3;
				return 0;
			}
			strcpy(symbolName,list[listIndex].name);
			listIndex++;
			if(list[listIndex].type == lbracketsym)
			{
				listIndex++;
				if(list[listIndex].type != numbersym || (list[listIndex].value == 0))
				{
					errorType = 4;
					return 0;
				}
				arraySize = list[listIndex].value;
				listIndex++;
				if(list[listIndex].type == subsym || list[listIndex].type == modsym || list[listIndex].type == multsym || list[listIndex].type == divsym || list[listIndex].type == addsym)
				{
					errorType = 4;
					return 0;
				}
				else if(list[listIndex].type != rbracketsym)
				{
					errorType = 5;
					return 0;
				}

				listIndex++;
				addToSymbolTable(2,symbolName,arraySize,level,memorySize,0);
				memorySize += arraySize;
			}
			else
			{
				addToSymbolTable(1,symbolName,0,level,memorySize,0);
				memorySize++;
			}

		}while(list[listIndex].type == commasym);
		if(list[listIndex].type == identsym)
		{
			errorType = 6;
			return 0;
		}
		else if(list[listIndex].type != semicolonsym)
		{
			errorType = 7;
			return 0;
		}
		listIndex++;
	}
	else
		return memorySize;

}

void procedureDeclaration(lexeme* list)
{
	char *procName;
	while(list[listIndex].type == procsym)
	{
		listIndex++;
		if(list[listIndex].type != identsym)
		{
			errorType = 2;
			return;
		}
		else if(multipledeclarationcheck(list[listIndex].name) != -1)
		{
			errorType = 3;
			return;
		}
		strcpy(procName,list[listIndex].name);
		listIndex++;
		if(list[listIndex].type != semicolonsym)
		{
			errorType = 8;
			return;
		}
		listIndex++;
		addToSymbolTable(3,procName,0,level,0,0);
		block(list);
		if(list[listIndex].type != semicolonsym)
		{
			errorType = 7;
			return;
		}
		emit(2,0,0,0);
	}
}

void statement(lexeme *list)
{
	// Assignment
	char* symbolname;
	int symidx;
	int arrayidxreg;
	int jpcidx;
	int jmpidx;

	if(list[listIndex].type == assignsym)
	{
		symbolname = list[listIndex].name;
		listIndex++;
		if(list[listIndex].type == lbracketsym)
		{
			listIndex++;
			symidx = findsymbol(symbolname, 2);
			if(symidx == -1)
			{
				if(findsymbol(symbolname, 1) != -1)
				{
					errorType = 11;
					return;
				}
				else if(findsymbol(symbolname, 3) != -1)
				{
					errorType = 9;
					return;
				}
				else
				{
					errorType = 10;
					return;
				}
			}
			expression(list);
			arrayidxreg = registerCounter;
			if(list[listIndex].type != rbracketsym)
			{
				errorType = 5;
				return;
			}
			listIndex++;
			if(list[listIndex].type != assignsym)
			{
				errorType = 13;
				return;
			}
			listIndex++;
			expression(list);
			registerCounter++;
			if(registerCounter >= 10)
			{
				errorType = 14;
				return;
			}
			emit(1, registerCounter, 0, table[symidx].addr);
			emit(13, arrayidxreg, arrayidxreg, registerCounter);
			registerCounter--;
			emit(4, registerCounter, level - table[symidx].level, arrayidxreg);
			registerCounter -= 2;
		}
		else
		{
			symidx = findsymbol(symbolname, 1);
			if(symidx != -1)
			{
				if(findsymbol(symbolname, 2) != -1)
				{
					errorType = 12;
					return;
				}
				else if(findsymbol(symbolname, 3) != -1)
				{
					errorType = 9;
					return;
				}
				else
				{
					errorType = 10;
					return;
				}
			}
			registerCounter++;
			if(registerCounter >= 10)
			{
				errorType = 14;
				return;
			}
			emit(1, registerCounter, 0, table[symidx]);
			int varlocreg = registerCounter;
			if(list[listIndex].type != assignsym)
			{
				errorType = 13;
				return;
			}
			listIndex++;
			expression(list);
			emit(4, registerCounter, level - table[symidx].level, varlocreg);
			registerCounter -= 2;
		}
		listIndex++;
	}

	// CALL
	if(list[listIndex].type == callsym)
	{
		listIndex++;
		if(list[listIndex].type != identsym)
		{
			errorType = 15;
			return;
		}
		symidx = findsymbol(list[listIndex].name, 3);
		if(symidx == -1)
		{
			if(findsymbol(list[listIndex].name, 1) != -1|| findsymbol(list[listIndex].name, 2) != -1)
			{
				errorType = 15;
				return;
			}
			else
			{
				errorType = 10;
				return;
			}
		}
		emit(5, 0, level - table[symidx], symidx);
		listIndex++;
	}
	// begin-end
	if(list[listIndex].type == beginsym)
	{
		do {
			listIndex++;
			statement(list);
		} while(list[listIndex].type == semicolonsym);
		if(list[listIndex].type != endsym)
		{
			if(list[listIndex].type == identsym || list[listIndex].type == callsym || list[listIndex].type == beginsym ||
			list[listIndex].type == ifsym || list[listIndex].type == dosym || list[listIndex].type == readsym || list[listIndex].type == writesym)
			{
				errorType = 16;
				return;
			}
			else
			{
				errorType = 17;
				return;
			}
		}
		listIndex++;
	}

	// IF
	if(list[listIndex].type == ifsym)
	{
		listIndex++;
		condition(list);
		jpcidx = cIndex;
		emit(8, registerCounter, 0, 0);
		registerCounter--;
		if(list[listIndex].type != questionsym)
		{
			errorType = 18;
			return;
		}
		listIndex++;
		statement(list);
		if(list[listIndex].type == colonsym)
		{
			listIndex++;
			jmpidx = cIndex;
			emit(7, 0, 0, 0);
			code[jmpidx].m = cIndex;
		}
		else
			code[jmpidx].m = cIndex;
	}
	// do while
	if(list[listIndex].type == dosym)
	{
		listIndex++;
		int loopidx = cIndex;
		statement(list);
		if(list[listIndex].type != whilesym)
		{
			errorType = 19;
			return;
		}
		listIndex++;
		condition(list);
		registerCounter++;
		if(registerCounter >= 10)
		{
			errorType = 14;
			return;
		}
		emit(1, registerCounter, 0, 0);
		emit(18, registerCounter - 1, registerCounter - 1, registerCounter);
		registerCounter--;
		emit(8, registerCounter, 0, loopidx);
		registerCounter--;
	}
	// READ
	if(list[listIndex].type == readsym)
	{
		if(list[listIndex].type != identsym)
		{
			errorType = 20;
			return;
		}
		symbolname = list[listIndex].name;
		listIndex++;
		if(list[listIndex].type == lbracketsym)
		{
			listIndex++;
			symidx = findsymbol(symbolname, 2);
			if(symidx == -1)
			{
				if(findsymbol(symbolname, 1) != -1)
				{
					errorType = 11;
					return;
				}
				else if(findsymbol(symbolname, 3) != -1)
				{
					errorType = 9;
					return;
				}
				else
				{
					errorType = 10;
					return;
				}
			}
			expression(list);
			arrayidxreg = registerCounter;
			if(list[listIndex].type != rbracketsym)
			{
				errorType = 5;
				return;
			}
			listIndex++;
			registerCounter++;
			if(registerCounter >= 10)
			{
				errorType = 14;
				return;
			}
			emit(10, registerCounter, 0, 0);
			registerCounter++;
			if(registerCounter >= 10)
			{
				errorType = 14;
				return;
			}
			emit(1, registerCounter, 0, table[symidx].addr);
			emit(13, arrayidxreg, arrayidxreg, registerCounter);
			registerCounter--;
			emit(4, registerCounter, level - table[symidx].level, arrayidxreg);
			registerCounter -= 2;
		}
		else
		{
			symidx = findsymbol(symbolname, 1);
			if(symidx != -1)
			{
				if(findsymbol(symbolname, 2) != -1)
				{
					errorType = 12;
					return;
				}
				else if(findsymbol(symbolname, 3) != -1)
				{
					errorType = 9;
					return;
				}
				else
				{
					errorType = 10;
					return;
				}
			}
			registerCounter++;
			if(registerCounter >= 10)
			{
				errorType = 14;
				return;
			}
			emit(4, registerCounter, 0, table[symidx].addr);
			registerCounter++;
			if(registerCounter >= 10)
			{
				errorType = 14;
				return;
			}
			emit(10, registerCounter, 0, 0);
			int varlocreg = registerCounter;
			emit(4, registerCounter, level - table[symidx].level, varlocreg);
			registerCounter--;
		}
	}
	// WRITE
	if(list[listIndex].type == writesym)
	{
		listIndex++;
		expression(list);
		emit(9, registerCounter, 0, 0);
		registerCounter++;
		if(registerCounter >= 10)
		{
			errorType = 14;
			return;
		}
	}
}

void condition(lexeme *list)
{
	if(list[listIndex].type == identsym)
	{
			emit(20, registerCounter, 0, 0);

			getToken(list);
			expression(list);


	}
	else
	{
			getToken(list);
			expression(list);

			if(list[listIndex].type != lsssym && list[listIndex].type != gtrsym && list[listIndex].type != leqsym && list[listIndex].type != geqsym && list[listIndex].type != eqlsym && list[listIndex].type != neqsym)
				{
					printparseerror(20);
					errorType = 20;
					return;
				}


			int opr = list[listIndex].type;
			getToken(list);
			expression(list);



			emit(relOP(opr), registerCounter - 2, registerCounter - 2, registerCounter - 1);
			registerCounter -= 2;
	}
	return;
}

void expression(lexeme *list)
{
	int opr;
	if(list[listIndex].type == addsym || list[listIndex].type == subsym)
	{
			opr = list[listIndex].type;
			getToken(list);
			term(list);

			if(opr == subsym)
					emit(30, registerCounter - 1, registerCounter - 1, 0);
	}
	else
			term(list);

	while(list[listIndex].type == addsym || list[listIndex].type == subsym)
	{
			opr = list[listIndex].type;
			term(list);

			if(opr == addsym)
					emit(32, registerCounter - 2, registerCounter - 2, registerCounter - 1);
			else
					emit(30, registerCounter - 2, registerCounter - 2, registerCounter - 1);
			registerCounter--;
	}
	return;
}

void term(lexeme *list)
{
	factor(list);
	while(list[listIndex].type == multsym || list[listIndex].type == divsym ||
	list[listIndex].type == modsym)
	{
		if(list[listIndex].type == multsym)
		{
			listIndex++;
			factor(list);
			emit(15, registerCounter - 1, registerCounter - 1, registerCounter);
			registerCounter--;
		}
		else if (list[listIndex].type == divsym)
		{
			listIndex++;
			factor(list);
			emit(16, registerCounter - 1, registerCounter - 1, registerCounter);
			registerCounter--;
		}
		else
		{
			listIndex++;
			factor(list);
			emit(17, registerCounter - 1, registerCounter - 1, registerCounter);
			registerCounter--;
		}
	}
}

void factor(lexeme *list)
{
	char* symbolname;
	int arrayidxreg;
	int varlocreg;
	if(list[listIndex].type = identsym)
	{
		symbolname = list[listIndex].name;
		listIndex++;
		if(list[listIndex].type = lbracketsym)
		{
			listIndex++;
			symidx = findsymbol(symbolname, 2);
			if(symidx == -1)
			{
				if(findsymbol(symbolname, 1) != -1)
				{
					errorType = 11;
					return;
				}
				else if(findsymbol(symbolname, 3) != -1)
				{
					errorType = 9;
					return;
				}
				else
				{
					errorType = 10;
					return;
				}
			}
			expression(list);
			arrayidxreg = registerCounter;
			if(list[listIndex].type != rbracketsym)
			{
				errorType = 5;
				return;
			}
			registerCounter++;
			if(registerCounter >= 10)
			{
				errorType = 14;
				return;
			};
			emit(1, registerCounter, 0, table[symidx].addr);
			emit(13, arrayidxreg, arrayidxreg, registerCounter);
			registerCounter--;
			emit(3, registerCounter, level - table[symidx].level, arrayidxreg);
			listIndex++;
		}
		else
		{
			symidx = findsymbol(symbolname, 1);
			if(symidx != -1)
			{
				if(findsymbol(symbolname, 2) != -1)
				{
					errorType = 12;
					return;
				}
				else if(findsymbol(symbolname, 3) != -1)
				{
					errorType = 9;
					return;
				}
				else
				{
					errorType = 10;
					return;
				}
			}
			registerCounter++;
			if(registerCounter >= 10)
			{
				errorType = 14;
				return;
			}
			emit(1, registerCounter, 0, table[symidx].addr);
			varlocreg = registerCounter;
			emit(3, registerCounter, level - table[symidx].level, varlocreg);
		}
	}
	else if(list[listIndex].type = numbersym)
	{
		registerCounter++;
		if(registerCounter >= 10)
		{
			errorType = 14;
			return;
		}
		emit(1, registerCounter, 0, list[listIndex].value);
		listIndex++;
	}
	else if(list[listIndex].type = lparenthesissym)
	{
		listIndex++;
		expression(list);
		if(list[listIndex].type != rbracketsym)
		{
			errorType = 23;
			return;
		}
		listIndex++;
	}
	else
	{
		errorType = 24;
		return;
	}
}


lexeme getToken(lexeme *list)
{
	lexeme token = list[listIndex];
	listIndex++;
	return token;
}
void emit(int opname, int reg, int level, int mvalue)
{
	code[cIndex].opcode = opname;
	code[cIndex].r = reg;
	code[cIndex].l = level;
	code[cIndex].m = mvalue;
	cIndex++;
}

void addToSymbolTable(int k, char n[], int s, int l, int a, int m)
{
	table[tIndex].kind = k;
	strcpy(table[tIndex].name, n);
	table[tIndex].size = s;
	table[tIndex].level = l;
	table[tIndex].addr = a;
	table[tIndex].mark = m;
	tIndex++;
}

void mark()
{
	int i;
	for (i = tIndex - 1; i >= 0; i--)
	{
		if (table[i].mark == 1)
			continue;
		if (table[i].level < level)
			return;
		table[i].mark = 1;
	}
}

int multipledeclarationcheck(char name[])
{
	int i;
	for (i = 0; i < tIndex; i++)
		if (table[i].mark == 0 && table[i].level == level && strcmp(name, table[i].name) == 0)
			return i;
	return -1;
}

int findsymbol(char name[], int kind)
{
	int i;
	int max_idx = -1;
	int max_lvl = -1;
	for (i = 0; i < tIndex; i++)
	{
		if (table[i].mark == 0 && table[i].kind == kind && strcmp(name, table[i].name) == 0)
		{
			if (max_idx == -1 || table[i].level > max_lvl)
			{
				max_idx = i;
				max_lvl = table[i].level;
			}
		}
	}
	return max_idx;
}

void printparseerror(int err_code)
{
	switch (err_code)
	{
		case 1:
			printf("Parser Error: Program must be closed by a period\n");
			break;
		case 2:
			printf("Parser Error: Symbol names must be identifiers\n");
			break;
		case 3:
			printf("Parser Error: Confliciting symbol declarations\n");
			break;
		case 4:
			printf("Parser Error: Array sizes must be given as a single, nonzero number\n");
			break;
		case 5:
			printf("Parser Error: [ must be followed by ]\n");
			break;
		case 6:
			printf("Parser Error: Multiple symbols in var declaration must be separated by commas\n");
			break;
		case 7:
			printf("Parser Error: Symbol declarations should close with a semicolon\n");
			break;
		case 8:
			printf("Parser Error: Procedure declarations should contain a semicolon before the body of the procedure begins\n");
			break;
		case 9:
			printf("Parser Error: Procedures may not be assigned to, read, or used in arithmetic\n");
			break;
		case 10:
			printf("Parser Error: Undeclared identifier\n");
			break;
		case 11:
			printf("Parser Error: Variables cannot be indexed\n");
			break;
		case 12:
			printf("Parserr Error: Arrays must be indexed\n");
			break;
		case 13:
			printf("Parser Error: Assignment operator missing\n");
			break;
		case 14:
			printf("Parser Error: Register Overflow Error\n");
			break;
		case 15:
			printf("Parser Error: call must be followed by a procedure identifier\n");
			break;
		case 16:
			printf("Parser Error: Statements within begin-end must be separated by a semicolon\n");
			break;
		case 17:
			printf("Parser Error: begin must be followed by end\n");
			break;
		case 18:
			printf("Parser Error: if must be followed by ?\n");
			break;
		case 19:
			printf("Parser Error: do must be followed by while\n");
			break;
		case 20:
			printf("Parser Error: read must be followed by a var or array identifier\n");
			break;
		case 21:
			printf("Parser Error: Relational operator missing from condition\n");
			break;
		case 22:
			printf("Parser Error: Bad arithmetic\n");
			break;
		case 23:
			printf("Parser Error: ( must be followed by )\n");
			break;
		case 24:
			printf("Parser Error: Arithmetic expressions may only contain arithmetic operators, numbers, parentheses, and variables\n");
			break;
		default:
			printf("Implementation Error: unrecognized error code\n");
			break;
	}

	free(code);
	free(table);
}

void printsymboltable()
{
	int i;
	printf("Symbol Table:\n");
	printf("Kind | Name        | Size | Level | Address | Mark\n");
	printf("---------------------------------------------------\n");
	for (i = 0; i < tIndex; i++)
		printf("%4d | %11s | %5d | %4d | %5d | %5d\n", table[i].kind, table[i].name, table[i].size, table[i].level, table[i].addr, table[i].mark);

	free(table);
	table = NULL;
}

void printassemblycode()
{
	int i;
	printf("Line\tOP Code\tOP Name\tR\tL\tM\n");
	for (i = 0; i < cIndex; i++)
	{
		printf("%d\t", i);
		printf("%d\t", code[i].opcode);
		switch (code[i].opcode)
		{
			case 1:
				printf("LIT\t");
				break;
			case 2:
				printf("RET\t");
				break;
			case 3:
				printf("LOD\t");
				break;
			case 4:
				printf("STO\t");
				break;
			case 5:
				printf("CAL\t");
				break;
			case 6:
				printf("INC\t");
				break;
			case 7:
				printf("JMP\t");
				break;
			case 8:
				printf("JPC\t");
				break;
			case 9:
				printf("WRT\t");
				break;
			case 10:
				printf("RED\t");
				break;
			case 11:
				printf("HLT\t");
				break;
			case 12:
				printf("NEG\t");
				break;
			case 13:
				printf("ADD\t");
				break;
			case 14:
				printf("SUB\t");
				break;
			case 15:
				printf("MUL\t");
				break;
			case 16:
				printf("DIV\t");
				break;
			case 17:
				printf("MOD\t");
				break;
			case 18:
				printf("EQL\t");
				break;
			case 19:
				printf("NEQ\t");
				break;
			case 20:
				printf("LSS\t");
				break;
			case 21:
				printf("LEQ\t");
				break;
			case 22:
				printf("GTR\t");
				break;
			case 23:
				printf("GEQ\t");
				break;
			default:
				printf("err\t");
				break;
		}
		printf("%d\t%d\t%d\n", code[i].r, code[i].l, code[i].m);
	}

	if (table != NULL)
		free(table);
}
