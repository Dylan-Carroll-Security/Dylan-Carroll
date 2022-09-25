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
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Author: Dylan Carroll
* Course: CST 8152 – Compilers, Lab Section: 012
* Assignment: A22.
* Date: Mar 13 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 30   /* variable identifier length */
#define ERR_LEN 50  /* error message length */
#define NUM_LEN 15   /* maximum number of digits for IL */

#define RTE_CODE 1   /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
/*no int float or variable identifiers present at this location for a complete language*/
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	STR_T,		/*  2: String literal token */
	LPR_T,		/*  3: Left parenthesis token */
	RPR_T,		/*  4: Right parenthesis token */
	LBR_T,		/*  5: Left brace token */
	RBR_T,		/*  6: Right brace token */
	KW_T,		/*  7: Keyword token */
	EOS_T,		/*  8: End of statement (semicolon) */
	RTE_T,		/*  9: Run-time error token */
	SEOF_T,		/* 10: Source end-of-file token */
	AVID_T,
	REL
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	tokyo_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	tokyo_int intValue;						/* integer literal attribute (value) */
	tokyo_int keywordIndex;					/* keyword index in the keyword table */
	tokyo_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	tokyo_flt floatValue;					/* floating-point literal attribute (value) */
	tokyo_chr idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	tokyo_chr errLexeme[ERR_LEN + 1];		/* error token attribite */
	tokyo_int  AVID;
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	tokyo_flg flags;			/* Flags information */
	union {
		tokyo_int intValue;				/* Integer value */
		tokyo_flt floatValue;			/* Float value */
		tokyo_nul* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	tokyo_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, @comment@ , ',' , ';' , '-' , '+' , '*' , '/', ## , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Error states and illegal state */
#define ES  6		/* Error state with no retract */
#define ER  7		/* Error state with retract */
#define IS -1		/* Illegal state */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 11

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '&'
#define CHRCOL4 '\"'

/* These constants will be used on VID / MID function */
#define MNIDPREFIX '&'

/* TO_DO: Transition table - type of states defined in separate table */
static tokyo_int transitionTable[][TABLE_COLUMNS] = {

	/*{  0,  1,  2,  3,  4,  5,  6,  7,  8 } */
	/* State 0 */{  1,  2, ES, IS,  7,  6,  6, IS, IS },
	/* State 1 */{  1,  1,  4, IS,  1,  1,  1,  5,  5 }, 
	/* State 2 */{  2,  2,  4, IS , 2,  2,  2,  5,  5 }, 
	/* State 3 */{ IS, IS, IS, IS, IS, IS, IS, IS, IS }, 
	/* State 4 */{ IS, IS, IS, IS, IS, IS, IS, IS, IS }, //Adjusted transition tables due to previous table containing logical errors
	/* State 5 */{ IS, IS, IS, IS, IS, IS, IS, IS, IS },
	/* State 6 */{ ES, ES,  8, IS,  5,  5,  5, 12,  7 }, 
	/* State 7 */{ ES, ES,  8, IS, ES,  9,  3, 11,  8 }, 
	/* State 8 */{ IS, IS, IS, IS, IS, IS, IS, IS, IS }, 
	/* State 9 */{ ES, ES, 12, IS,  9,  9, ES, ES, 12 },
	/* State 10 */{ IS, IS, IS, IS, IS, IS, IS, IS, IS },
	/* State 11 */{ 11, 11, 13, IS, 11, 11, 11, 11, 13 },
	/* State 12 */{ IS, IS, IS, IS, IS, IS, IS, IS, IS }, 
	/* State 13 */{ IS, IS, IS, IS, IS, IS, IS, IS, IS }
	
};

/* Define accepting states types */
#define NOAS	3		/* not accepting state */
#define ASNR	2		/* accepting state with no retract */
#define ASWR	1		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static tokyo_int stateType[] = {
	 ASWR, 
	 NOAS,
	 NOAS, 
	 ASNR, 
	 ASNR, 
	 ASWR, 
	 ASWR, 
	 NOAS, 
     ASWR, 
     NOAS, 
	 NOAS, 
	 NOAS, 
	 ASWR, 
	 ASWR 
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
tokyo_int startScanner(BufferPointer psc_buf);
static tokyo_int nextClass(tokyo_chr c);			/* character class function */
static tokyo_int nextState(tokyo_int, tokyo_chr);		/* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(tokyo_chr* lexeme);

/* Declare accepting states functions */
Token funcSL	(tokyo_chr lexeme[]);
Token funcID	(tokyo_chr lexeme[]);
Token funcKEY	(tokyo_chr lexeme[]);
Token funcErr	(tokyo_chr lexeme[]);
Token funcAVID  (tokyo_chr lexeme[]);
/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */


static PTR_ACCFUN finalStateTable[] = {
	  NULL,
	  NULL,
	  NULL,
	  funcErr,
      funcSL,
	  funcAVID, //custom variable idenifier function
	  NULL,
	  NULL,
	  funcKEY,//decimal integer
	  NULL,
	  NULL,
	  NULL,
	  funcKEY, //decimal
	  funcKEY //float
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/


#define KWT_SIZE 9


static tokyo_chr* keywordTable[KWT_SIZE] = {
	"int",
	"float",
	"String",
	"if",
	"else if",
	"else",
	"while",
	"main",
	"print"
	
	
};

#endif
