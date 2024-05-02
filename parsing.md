🔑 Type inference is used by default. You must specify the full type of the variable if you want an explicit amount of memory allocated.

# Naming Variables

Variable names may only be 31 characters long.

Variable names will initially be accepted even if they have illegal characters. Those characters will simply just be ignored when the variable is created. For example, *a variable named \*ptr.with^bad\*symbols* will simply be acknowledged as a void pointer identified by the name _ptrwithbadsymbols_. 

# Types

**Pointers:** A variable is a pointer if the FIRST character in its name is a \*. These pointer asterisks will be stripped from the name when the variable is created and inserted into the variable table.

**Arrays:** All arrays are pointers by default. A token can be detected as an array if it ends with []. 

**Shorts and Integers:** A numeric literal without a decimal point is interpreted as a SHORT by default, if the size is less than 32,767 (maximum value for signed short). If the number is larger than the short max, it will be interpreted as a 32-bit integer. There is no mechanism to prevent overflow if the number is greater than the maximum value for a signed integer. **Longs are not currently implemented, and the program will NEVER assume you want an unsigned value.** To get an unsigned value, you must specify the full type of the variable.
