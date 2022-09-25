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
* File name: compilers.h
* Compiler: MS Visual Studio 2022
* Author: Dylan Carroll
* Course: CST 8152 � Compilers, Lab Section: 012
* Assignment: A22.
* Date: Mar 13 2022
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainBuffer(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/* Logical constants - adapt for your language */
#define TOKYO_TRUE	1
#define TOKYO_FALSE 0

/* You should add your own constant definitions here */
#define TOKYO_MAX_SIZE				SHRT_MAX-1	/* maximum capacity */ 

/*
------------------------------------------------------------
Data types definitions
------------------------------------------------------------
*/
/* TO_DO: Define your typedefs */
typedef char			tokyo_chr;
typedef short			tokyo_int;
typedef float			tokyo_flt;
typedef void			tokyo_nul;

typedef unsigned char	tokyo_bol;
typedef unsigned char	tokyo_flg;

typedef long			tokyo_lng;
typedef double			tokyo_dbl;

/*
------------------------------------------------------------
Programs:
1: Buffer - invokes MainBuffer code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_BUFFER	= '1',
	PGM_SCANNER = '2',
	PGM_PARSER	= '3'
};

/*
------------------------------------------------------------
Main functions signatures
(Codes will be updated during next assignments)
------------------------------------------------------------
*/
tokyo_int mainBuffer	(tokyo_int argc, tokyo_chr** argv);

tokyo_int mainScanner	(tokyo_int argc, tokyo_chr** argv);
/*
tokyo_int mainParser	(tokyo_int argc, tokyo_chr** argv);
*/
#endif
