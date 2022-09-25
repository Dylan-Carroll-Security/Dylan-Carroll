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
* File name: Buffer.h
* Compiler: MS Visual Studio 2022
* Author: Dylan Carroll / Mohammed Abdulla
* Course: CST 8152 – Compilers, Lab Section: 012
* Assignment: A12.
* Date: Jan 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
************************************************************
*/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#define BUFFER_H_

/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer) */
enum BUFFERMODES {
	MODE_FIXED = 'f',
	MODE_ADDIT = 'a',
	MODE_MULTI = 'm'
};

/* TO_DO: Adjust all constants to your Language */

#define BUFFER_ERROR (-1)						/* General error message */
#define BUFFER_EOF '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (TOKYO) .................................. */

#define BUFFER_DEFAULT_SIZE			200			/* default initial buffer capacity */
#define BUFFER_DEFAULT_INCREMENT	100			/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for TOKYO  downloadable code in week3 to help*/
/* BITS                                (7654.3210) */
#define TOKYO_DEFAULT_FLAG 0x0F 	/* (0000.1111)_2 = (015)_10 */
/* TO_DO: BIT 7: REL = Relocation */

/* SET RLB: Mask: 0X80       1000.0000_2 = 80_16  128_10 */ 
/*for just bit #7*/
#define SET_RLB 0x80/*apply: or*/
#define RST_RLB 0x7F/*apply: and*/
#define CHK_RLB 0x80/*apply and*/
/* RESET: Mask: 0X7F		0111.1111_2   127  127_10*/   


/* CHECK 				*/

/* TO_DO: BIT 6: EOB = EndOfBuffer */
#define SET_EOB  0x40
#define RST_EOB  0xBF
#define CHK_EOB  0x40
/* TO_DO: BIT 5: FUL = Full */
#define SET_FULL  0X20
#define RST_FULL  0XDF
#define CHK_FULL  0X20
/* TO_DO: BIT 4: EMP = Empty */
#define SET_EMP  0x10
#define RST_EMP  0xEF
#define CHK_EMP  0x10

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (TOKYO) .................................. */



/* Offset declaration */
typedef struct position {
	tokyo_int markPos;			/* the offset (in chars) to the mark location */
	tokyo_int readPos;			/* the offset (in chars) to the get-character location */
	tokyo_int writePos;			/* the offset (in chars) to the add-character location */
} Position;

/* Buffer structure */
typedef struct buffer {
	tokyo_chr*	string;		/* pointer to the beginning of character array (character buffer) */
	tokyo_int	size;		    /* current dynamic memory size (in bytes) allocated to character buffer */
	tokyo_int	increment;		/* character array increment factor */
	tokyo_int	mode;			/* operational mode indicator */
	tokyo_flg	flags;			/* contains character array reallocation flag and end-of-buffer flag */
	Position	position;		/* Offset / position field */
} Buffer, * BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* TO_DO: Define your function declarations using your language specification */

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	bCreate(tokyo_int, tokyo_int, tokyo_int); /* make buffer -> size , mode , char*/
BufferPointer	bAddChar(BufferPointer const, tokyo_chr); /* add char in from file    - > Checking the flags while adding to see if the buffer is full */
tokyo_bol		bRetract(BufferPointer const);
tokyo_bol		bRestore(BufferPointer const);
tokyo_bol		bRecover(BufferPointer const);
tokyo_bol		bClear(BufferPointer const);
tokyo_bol		bDestroy(BufferPointer const);
tokyo_bol		bSetMark(BufferPointer const, tokyo_int);
tokyo_bol		bIsEmpty(BufferPointer const);
tokyo_bol		bIsFull(BufferPointer const);
tokyo_bol		bIsRealocated(BufferPointer const);
tokyo_int		bPrint(BufferPointer const); /*String created from addition of char*/
tokyo_int		bLoad(BufferPointer const, FILE* const);
/* Getters */
tokyo_int		bGetSize(BufferPointer const);
tokyo_int		bGetWritePos(BufferPointer const);
tokyo_int		bGetMarkPos(BufferPointer const);
tokyo_int		bGetReadPos(BufferPointer const);
tokyo_int		bGetIncrement(BufferPointer const);
tokyo_int		bGetMode(BufferPointer const);
tokyo_chr		bGetChar(BufferPointer const);
tokyo_chr*		bGetContent(BufferPointer const, tokyo_int);
tokyo_flg		bGetFlags(BufferPointer const);

#endif
