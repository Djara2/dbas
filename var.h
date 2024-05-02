#include <stdbool.h>

#ifndef VAR_H
#define VAR_H

#define MODULUS     1021
#define COEFFICIENT 1013 

unsigned int hash_string(char string[]);

/* primitives, required to discern what to do with size 8 (pointer) variable,
   for example, if size = 8 and primitive = INT, then it is an array (integer pointer) */
enum var_types {BYTE, CHAR, SHORT, USHORT, INT, UINT, FLOAT, DOUBLE, VOID};

typedef struct var
{
	char   name[32];   // (1) Variables are not renamed, so fixed-length.
	size_t size;       // (2) e.g. 4 if regular int or 8 if int pointer (check type attribute)
	char   type;       // (3) e.g. regular int if size = 4 and type = int, otherwise integer pointer
	bool   is_pointer; /* (4) handle ambiguous case of size = 8 and type = DOUBLE. Maybe a pointer,
			          or maybe not. Pointer and double have same size.                   */
	void   *value;     // (5) void ptr resolved with size and type attributes
}var;

/* Data type for storing variables in hashmap for
 * fast lookup */
typedef struct var_entry
{
	unsigned short key; /* determined according to length attr of hashmap
			       at insertion time. Var's name attribute is used
			       for calculating hash */
	var       *value;
	var_entry *next;    // linear chaining
} var_entry;


typedef struct var_table
{
	var_entry *entries[MODULUS]; /* as per modulus, can only hold 1021 slots
                                        and then extra from linear chaining   */
	unsigned short length;
} var_table;

/* Matches the size of a variable to compatible
   variable types, e.g. 4 bytes may be casted 
   as byte, char, short, ushort, int, or uint */
enum var_types match_var(var* v);

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
