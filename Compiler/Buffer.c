/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa / George Kriger / Abdullah Kadri
************************************************************
*/

/*
***********************************************************
* File name: buffer.c
* Compiler: MS Visual Studio 2022
* Author: Dylan Carroll / Mohammed Abdulla
* Course: CST 8152 – Compilers, Lab Section: 012
* Assignment: A12.
* Date: Jan 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer (A12)
************************************************************
*/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Buffer.h"
#endif

/*
***********************************************************
* Function name: bCreate
* Purpose: Creates the buffer according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Dylan Carroll / Mohammed Abdulla
* History/Versions: Ver 2.1
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to Buffer)
* Algorithm: Allocation of memory according to inicial (default) values.
* TO_DO: 
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

BufferPointer bCreate(tokyo_int size, tokyo_int increment, tokyo_int mode) {
	
	BufferPointer b;
	
	
	b = (BufferPointer)calloc(1, sizeof(Buffer));
	if (!b) { /* determine if b is null before it can break the malloc statement*/
		printf("allocation error");
		return NULL;
	}
	if (!size) { /* detect non existant size value */
		b->size = BUFFER_DEFAULT_SIZE;
		b->increment = BUFFER_DEFAULT_INCREMENT;
	}
	else { /* if recived params normally */
		b->size = size;
		b->increment = increment;
		b->mode = mode;
	}
		b->string = (tokyo_chr*)malloc(b->size);
	if (!b->string) { /*Checking if the memory has been properly allocated(check for 0 or void)*/
		free(b);
		printf("b has been allocated incorrectly...");
		return NULL;
	}
	if (!increment) { /*check for fixed mode from increment being present or not*/
		b->mode = MODE_FIXED;
	}
	b->flags = TOKYO_DEFAULT_FLAG; //Set all flags to default incase issue has occured with resetting
	return b;
}

/*
***********************************************************
* Function name: bAddChar
* Purpose: Adds a char to buffer
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   ch = char to be added
* Return value:
*	bPointer (pointer to Buffer)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
																																																																																																																																																		#pragma warning( disable : 6001)
BufferPointer bAddChar(BufferPointer const pBuffer, tokyo_chr ch) { /* Often source of crashing issues */
	tokyo_int newSize = 0;
	char* clone;
	if (!pBuffer) { 
		return NULL;
	}
	if (bGetWritePos(pBuffer) >= pBuffer->size) { /*When the write position is at or exceeds the maximum size*/
		pBuffer->flags |= SET_FULL;
	}
	if (bIsFull(pBuffer)) { /* check for the full bit being set */
		pBuffer->flags &= RST_RLB;
		switch (pBuffer->mode) {
		case MODE_FIXED:
			return NULL; //no point in reallocation as fixed size does not change
			break;
		case MODE_ADDIT:
			newSize = pBuffer->size + pBuffer->increment; // Calculate new size to be given
			if (newSize < 0 || newSize > TOKYO_MAX_SIZE) { // Before using in memory allocation, check if it is valid to avoid pointer go boom
				printf("sizeError");
				return NULL;
			}
			pBuffer->size = newSize;
			clone = (char*)realloc(pBuffer->string, newSize);
			if (!clone) {
				printf("Memory Reallocation Error...");
				return NULL;
			}

			if (pBuffer->string != clone) {
				pBuffer->flags |= SET_RLB;
			}
			pBuffer->string = clone;
			pBuffer->flags &= RST_FULL; /*reset full bit after assigning additional storage*/

			break;
		case MODE_MULTI:
			newSize = pBuffer->size * pBuffer->increment; /* Error here -> the number being generated is too large in m operation mode while reading Tokyo_big -> deemed a normal thing to happen  */
			if (newSize < 0 || newSize > TOKYO_MAX_SIZE) { // Before using in memory allocation, check if it is valid to avoid pointer go boom
				return NULL;
			}
			pBuffer->size = newSize;
			clone = (char*)realloc(pBuffer->string, newSize);
			if (!clone) {
				printf("Memory Reallocation Error...");
				return NULL;
			}
			if (pBuffer->string != clone) {
				pBuffer->flags |= SET_RLB;
			}
			pBuffer->string = clone;
			pBuffer->flags &= RST_FULL; /*reset full bit after assigning additional storage*/

			break;

		}
	}
	

	pBuffer->string[pBuffer->position.writePos++] = ch;

	return pBuffer;
}

/*
***********************************************************
* Function name: bClear
* Purpose: Clears the buffer
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_bol bClear(BufferPointer const pBuffer) { 
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL){
		printf("Buffer is empty\n");
		return TOKYO_FALSE;
	}
	pBuffer->position.writePos = pBuffer->position.markPos = pBuffer->position.readPos = 0;
	
	
	pBuffer->flags &= TOKYO_DEFAULT_FLAG;
	
	return TOKYO_TRUE;
}

/*
***********************************************************
* Function name: bDestroy
* Purpose: Releases the buffer address
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_bol bDestroy(BufferPointer const pBuffer) { 
	/* TO_DO: Defensive programming */

	if (!pBuffer) {
		return TOKYO_FALSE;
	}
	else {

		free(pBuffer->string);
		free(pBuffer);
	}
	return TOKYO_TRUE;
}

/*
***********************************************************
* Function name: bIsFull
* Purpose: Checks if buffer is full
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_bol bIsFull(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL){
		printf("Buffer error\n"); 
		return TOKYO_FALSE;
	}

	/* TO_DO: Check flag if buffer is FUL */
	
	if ((pBuffer->flags & CHK_FULL) == CHK_FULL) {
		return TOKYO_TRUE;
	}
	else {
		return TOKYO_FALSE;
	}
}

/*
***********************************************************
* Function name: bGetWritePos
* Purpose: Returns the position of char to be added
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	addcPosition value
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_int bGetWritePos(BufferPointer const pBuffer) { 
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL){
		printf("Buffer error\n"); 
		return TOKYO_FALSE;
	}

	return pBuffer->position.writePos;
}

/*
***********************************************************																																																																																																																													
* Function name: bGetSize
* Purpose: Returns the current buffer capacity
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_int bGetSize(BufferPointer const pBuffer) { 
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL){
		printf("Buffer error\n"); 
		return TOKYO_FALSE;
	}

	return pBuffer->size;
}

/*
***********************************************************
* Function name: bGetMode
* Purpose: Returns the operational mode
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_int bGetMode(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL){
		printf("Buffer error\n"); 
		return TOKYO_FALSE;
	}

	return pBuffer->mode;
}


/*
***********************************************************
* Function name: bGetMarkPos
* Purpose: Returns the position of mark in the buffer
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	mark offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_int bGetMarkPos(BufferPointer const pBuffer) { 
	/* TO_DO: Defensive programming */
	if(!pBuffer){
		printf("Buffer error\n"); 
		return 0;
	}

	return pBuffer->position.markPos;
}


/*
***********************************************************
* Function name: bSetMark
* Purpose: Adjust the position of mark in the buffer
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_bol bSetMark(BufferPointer const pBuffer, tokyo_int mark) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL){
		printf("Buffer error\n"); 
		return TOKYO_FALSE;
	}
	
	/* TO_DO: Adjust the mark */
	return TOKYO_TRUE;
}

/*
***********************************************************
* Function name: bPrint
* Purpose: Prints the string in the buffer.
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_int bPrint(BufferPointer const pBuffer) {
	tokyo_int size = 1;
	tokyo_chr c;
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL){
		printf("Buffer error\n"); 
		return 0;
	}

	c = bGetChar(pBuffer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	if (CHK_EOB == (pBuffer->flags & CHK_EOB)) {
		return size;
	}
	while (c>0) {
		/* TO_DO: Adjust size */
		size++;
		printf("%c", c);
		c = bGetChar(pBuffer);
	}
	if (size<0 || size>TOKYO_MAX_SIZE) {
		return 0;
	}
	return size;
}

/*
***********************************************************
* Function name: bLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   fi = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_int bLoad(BufferPointer const pBuffer, FILE* const fi) {
	tokyo_int size = 1;
	tokyo_chr c;
	

	if(pBuffer == NULL){
		printf("Buffer error\n"); 
		return 0;
	}

	c = (tokyo_chr)fgetc(fi);
	while (!feof(fi)) {
		if (!bAddChar(pBuffer, c)) {
			ungetc(c, fi);
			
			return BUFFER_ERROR;
		}
		c = (char)fgetc(fi);
		size++;
		
	}
	if (size<0 || size>TOKYO_MAX_SIZE) {
		printf("bLoad Size error");
		return 0;
	}
	
	return size;
}

/*
***********************************************************
* Function name: bIsEmpty
* Purpose: Checks if buffer is empty.
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_bol bIsEmpty(BufferPointer const pBuffer) { /*Check the flags to determine if it is empty */
	
	if(!pBuffer){
		printf("Buffer error\n"); 
		return TOKYO_FALSE;
	}

	
	if(pBuffer->flags == CHK_EMP){
		printf("Buffer is empty\n");
		return TOKYO_TRUE;
	}

	return TOKYO_FALSE;
}

/*
***********************************************************
* Function name: bGetChar
* Purpose: Returns the char in the getC position.
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_chr bGetChar(BufferPointer const pBuffer) {
	if (!pBuffer) {
		printf("Buffer error\n");
		return TOKYO_FALSE;
	}

	pBuffer->flags &= RST_EOB;
	return pBuffer->string[pBuffer->position.readPos++];
}


/*
***********************************************************
* Function name: bRecover
* Purpose: Rewinds the buffer.
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_bol bRecover(BufferPointer const pBuffer) {
	if(!pBuffer){
		printf("Buffer error\n"); 
		return TOKYO_FALSE;
	}

	pBuffer->position.readPos = 0;
	pBuffer->position.markPos = 0;
	return TOKYO_TRUE;
}


/*
***********************************************************
* Function name: bRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_bol bRetract(BufferPointer const pBuffer) {
	
	if(pBuffer == NULL){
		printf("Buffer error\n"); 
		return TOKYO_FALSE;
	}

	pBuffer->position.readPos--;
	return TOKYO_TRUE;
}


/*
***********************************************************
* Function name: bRestore
* Purpose: Resets the buffer.
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_bol bRestore(BufferPointer const pBuffer) {
	
	if(pBuffer == NULL){
		printf("Buffer error\n"); 
		return TOKYO_FALSE;
	}

	pBuffer->position.readPos = pBuffer->position.markPos;
	return TOKYO_TRUE;
}


/*
***********************************************************
* Function name: bGetReadPos
* Purpose: Returns the value of getCPosition.
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	The readPos offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_int bGetReadPos(BufferPointer const pBuffer) {

	if(pBuffer == NULL){
		printf("Buffer error\n"); 
		return TOKYO_FALSE;
	}

	return pBuffer->position.readPos;
}


/*
***********************************************************
* Function name: bGetIncrement
* Purpose: Returns the buffer increment.
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_int bGetIncrement(BufferPointer const pBuffer) {
	
	if(pBuffer == NULL){
		printf("Buffer error\n"); 
		return TOKYO_FALSE;
	}

	return pBuffer->increment;
}


/*
***********************************************************
* Function name: bGetContent
* Purpose: Returns the pointer to String.
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
tokyo_chr* bGetContent(BufferPointer const pBuffer, tokyo_int pos) {
	
	if(pBuffer == NULL){
		printf("Buffer error\n"); 
		return TOKYO_FALSE;
	}


	return pBuffer->string + pos;
}


/*
***********************************************************
* Function name: bGetFlags
* Purpose: Returns the entire flags of Buffer.
* Author: Dylan Carroll / Mohammed Abdulla
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
#define FLAGS_
#undef FLAGS_
#ifndef FLAGS_
tokyo_flg bGetFlags(BufferPointer const pBuffer) {
	if (pBuffer == NULL) {
		printf("Buffer error\n");
		return TOKYO_FALSE;
	}
	return pBuffer->flags;
}
#else
#define bGetFlags(pBuffer) ((pBuffer)?(pBuffer->flags):(RT_FAIL_1))
#endif
