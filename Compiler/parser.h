/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa / George Kriger / Abdullah Kadri
************************************************************
*/

/*
************************************************************
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Author: Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013, 014]
* Assignment: A12, A22, A32.
* Date: Jan 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef BUFFER_H_
#include "Buffer.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
tokyo_int syntaxErrorNumber = 0;
extern Buffer* stringLiteralTable;
extern tokyo_int line;
extern Token tokenizer();
extern tokyo_chr* keywordTable[];

#define STR_LANGNAME "tokyo"


/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	Int,
	Float,
	String,
	If,
	Else_If,
	Else,
	While,
	main,
	input,
	print /* my keywords are also keywords in c ... quotes may be required */
};

/* Function definitions */
tokyo_nul startParser();
tokyo_nul matchToken(tokyo_int, tokyo_int);
tokyo_nul syncErrorHandler(tokyo_int);
tokyo_nul printError();

/* TODO: Place ALL non-terminal function declarations */
tokyo_nul assignmentExpression();
tokyo_nul assignmentStatement();
tokyo_nul codeSession();
tokyo_nul dataSession();
tokyo_nul optVarListDeclarations();
tokyo_nul optionalStatements();
tokyo_nul outputStatement();
tokyo_nul outputVariableList();
tokyo_nul program();
tokyo_nul statement();
tokyo_nul statements();
tokyo_nul statementsPrime();
tokyo_nul locateOperator();
#endif
