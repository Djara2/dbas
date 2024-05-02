#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "var.h"

unsigned int hash_string(char string[])
{
	unsigned short len = strlen(string);
	unsigned int hash = 0;
	for(short i = 0; i < len; i++)
		hash += (unsigned int) string[i];

	hash *= COEFFICIENT;
	hash /= MODULUS;
	return hash;
}

/* ALREADY PROVIDED BY HEADER, BUT LEFT FOR REFERENCE
enum var_types {BYTE, CHAR, SHORT, USHORT, INT, UINT, FLOAT, DOUBLE};

typedef struct var
{
	char   name[32];
	size_t size;
	char   type;
	void   *value; // void ptr resolved with size attribute
}var;

DATA TYPE FOR STORING VARIABLES IN HASHMAP FOR
FAST LOOKUP 
typedef struct var_entry
{
	unsigned short key;    determined according to length attr of hashmap
			       at insertion time. Var's name attribute is used
			       for calculating hash
	var       *value;
	var_entry *next;    // linear chaining
} var_entry;


typedef struct var_table
{
	var_entry *entries[MODULUS];    as per modulus, can only hold 1021 slots
                                        and then extra from linear chaining  
	unsigned short length;
} var_table;
*/

/* Matches the size of a variable to compatible
   variable types, e.g. 4 bytes may be casted 
   as byte, char, short, ushort, int, or uint */
enum var_types match_var(var* v)
{
	switch(v->size)
	{
		case 0:
			return NONE;
			break;
		case 1: 
			return BYTE;
			break;
		case 2:
			return SHORT;
			break;
		case 4:
			return INT; // alternatively FLOAT or UINT
			break;
		case 8:
			return DOUBLE; // alternatively POINTER (64-bit implementation)
			break;	
		default:
			
	}
}

var* mkvar(char name[], size_t size);

/* For use with var_remove (table function).
   Returns true if successful and false otherwise. */
bool delvar(var *v);

/* search hashmap for variable. Do NOT implement contains
 * feature, but just return variable directly if it exists
 * or NULL if not found. Unnecessary performance overhead 
 * to check for variabl and THEN access */
var* var_lookup(var_table *table, char name[]);

/* Uses mkvar as helper function, then inserts into variable table.
   Returns true if successful and false otherwise.               */
bool var_insert(var_table *table, char name[]);

#endif

