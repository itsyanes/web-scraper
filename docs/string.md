## Strings

This functions are built on top of string.h functions. They add a smoother way of handling strings without having to worry too much about the underlying constraints of C strings.

### Description

This Module provides String not to be confused with string. string are just a macro for char * whereas String is a higher-level wrapper for string instances. String structures contain a pointer to a Prototype object that contains a pointer to all String methods. Therefore, all String methods are accessed through its Prototype as shown in the examples below.

### Table of Contents

#### Functions

Provided functions related to Strings.

1. [newString](#newstring)
1. [wrapString](#wrapstring)

#### Properties

Members of the String struct.

1. [string](#string)
1. [proto](#proto)

#### Prototype Methods

Methods of the prototype of String.

1. [length](#length)
1. [destroy](#destroy)
1. [build](#build)
1. [charAt](#charat)
1. [indexOf](#indexof)
1. [lastIndexOf](#lastindexof)
1. [concat](#concat)
1. [startsWith](#startswith)
1. [endsWith](#endswith)
1. [includes](#includes)
1. [replace](#replace)
1. [reverse](#reverse)
1. [trim](#trim)
1. [slice](#slice)
1. [clone](#clone)
1. [toString](#tostring)

## Contents

### newString

Allocates a new instance of String.

**Returns:** a String instance pointing to an empty string.

##### Example

```c
String *new = newString();
```

### wrapString

Allocates a new instance of String with the string given in parameter.

**Parameters:** 
- string (string): the value to set the pointed string to.

**Returns:** a String instance pointing to a copy of the string given in parameter.

##### Example

```c
String *new = wrapString("foo");
```

### string

Pointer to the string stored in-memory. You may read its value but never write to it!

##### Example

```c
String *str = wrapString("foo");
puts(str->string);
//prints "foo" to stdout
```

### proto

Pointer to the String's prototype containing all methods.

##### Example

```c
String *str = wrapString("foo");
str->proto->someMethod();
//calls a method named someMethod from the prototype
```

### length

Returns the length of the String.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** an integer that represents the length of the string.

##### Example

```c
String *str = wrapString("foo");
str->proto->length(str);
//returns 3
```

### destroy

Deallocates the String instance.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** void.

##### Example

```c
String *str = wrapString("foo");
str->proto->destroy(str);
//deallocates str
```

### build

Builds a string following a given format. build is a variadic function: meaning it can receive a non-fix amount of parameters. It is very similar to sprintf.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.
- format (string): the format of the String to build.
- ... (any): additional parameters matching the format to supply for the builder.

**Returns:** a pointer to the String.

##### Example

```c
String *str = newString();
str->proto->build(str, "%s is %d", "bar", 12);
puts(str->string);
//prints "bar is 12"
```

### charAt

Returns the char at the given position of the String.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.
- index (size_t): the index of the char to retrieve.

**Returns:** 0 if the index is greater than the string's length - 1 or the value of the char at the given position.

##### Example

```c
String *str = wrapString("foo");
char t = str->proto->charAt(str, 2);
//t's value is 'o'
```

### indexOf

Returns the first occurence of the char given as a parameter in the string.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.
- element (char): the char to find.

**Returns:** the index of the char or -1 if it isn't present in the string.

##### Example

```c
String *str = wrapString("foo");
str->proto->indexOf(str, 'o');
//returns 1
```

### lastIndexOf

Returns the last occurence of the char given as a parameter in the string.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.
- element (char): the char to find.

**Returns:** the index of the char or -1 if it isn't present in the string.

##### Example

```c
String *str = wrapString("foo");
str->proto->lastIndexOf(str, 'o');
//returns 2
```

### concat

Appends a string to the String instance.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.
- source (string): the string to append.

**Returns:** a pointer to the String.

##### Example

```c
String *str = wrapString("foo");
str->proto->concat(str, "bar");
puts(str->string);
//prints "foobar"
```

### startsWith

Checks if a String starts with the string passed as parameter.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.
- comparator (string): the string to compare to.

**Returns:** true if the String starts with the comparator, false otherwise.

##### Example

```c
String *str = wrapString("foo");
str->proto->startsWith(str, "fo");
//returns true
```

### endsWith

Checks if a String ends with the string passed as parameter.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.
- comparator (string): the string to compare to.

**Returns:** true if the String ends with the comparator, false otherwise.

##### Example

```c
String *str = wrapString("foo");
str->proto->endsWith(str, "oo");
//returns true
```

### includes

Checks if a String contains the string passed as parameter.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.
- comparator (string): the string to compare to.

**Returns:** true if the String contains the comparator, false otherwise.

##### Example

```c
String *str = wrapString("foobar");
str->proto->includes(str, "ob");
//returns true
```

### replace

Replaces all ocurrences of the first substring with the second substring in the String.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.
- substr (string): the substring to look for in the String.
- newSubstr (string): the substring to replace each occurence with.

**Returns:** A pointer to the String.

##### Example

```c
String *str = wrapString("foobarfoobar");
str->proto->replace(str, "foo", "bar");
puts(str->string);
//prints "barbarbarbar"
```

### reverse

Reverses the order of every character of the String.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** a pointer to the reversed String.

##### Example

```c
String *str = wrapString("foo");
str->proto->reverse(str);
puts(str->string)
//prints "oof"
```

### trim

Removes every space, tab, newline characters at both the beginning and the end of this String.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** a pointer to the modified String.

##### Example

```c
String *str = wrapString("  foo  ");
str->proto->trim(str);
puts(str->string);
//prints "foo"
```

### slice

Returns the substring between the indexes passed as parameter.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.
- start (size_t): the index of the start of the portion to be cut.
- end (size_t): the index of the end of the portion to be cut (the character at the index of the ending position is not included).

**Returns:** A pointer to a newly allocated instance of String (remember to deallocate both !).

##### Example

```c
String *str = wrapString("foobar");
String *new = str->proto->slice(str, 1, 4);
puts(new->string);
//prints "oob"
```

### clone

Returns a deep copy of the String.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** A pointer to a newly allocated instance of String (remember to deallocate both !).

##### Example

```c
String *str = wrapString("foobar");
String *new = str->proto->clone(str);
puts(new->string);
//prints "foobar"
```

### toString

Destroy the Wrapper and returns the string: a simple pointer to memory.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** A pointer to the string. It is your duty to perform a free() on this string.

##### Example

```c
String *str = wrapString("foobar");
string st = str->proto->toString(str);
puts(st);
//prints "foobar"
```