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
1. [split](#split)
1. [subString](#substring)
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
String *new = wrapString("toto");
```

### string

Pointer to the string stored in-memory. You may read its value but never write to it!

##### Example

```c
String *str = wrapString("toto");
puts(str->string);
//prints "toto" to stdout
```

### proto

Pointer to the String's prototype containing all methods.

##### Example

```c
String *str = wrapString("toto");
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
String *str = wrapString("toto");
str->proto->length(str);
//returns 4
```

### destroy

Deallocates the String instance.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** void.

##### Example

```c
String *str = wrapString("toto");
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
str->proto->build(str, "%s is %d", "titi", 12);
puts(str->string);
//prints "titi is 12"
```

### charAt

Returns the char at the given position of the String.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.
- index (size_t): the index of the char to retrieve.

**Returns:** 0 if the index is greater than the string's length - 1 or the value of the char at the given position.

##### Example

```c
String *str = wrapString("toto");
char t = str->proto->charAt(str, 2);
//t's value is 't'
```

### indexOf

Deallocates the String instance.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** void.

##### Example

```c
String *str = wrapString("toto");
str->proto->destroy(str);
//deallocates str
```

### destroy

Deallocates the String instance.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** void.

##### Example

```c
String *str = wrapString("toto");
str->proto->destroy(str);
//deallocates str
```

### destroy

Deallocates the String instance.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** void.

##### Example

```c
String *str = wrapString("toto");
str->proto->destroy(str);
//deallocates str
```

### destroy

Deallocates the String instance.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** void.

##### Example

```c
String *str = wrapString("toto");
str->proto->destroy(str);
//deallocates str
```

### destroy

Deallocates the String instance.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** void.

##### Example

```c
String *str = wrapString("toto");
str->proto->destroy(str);
//deallocates str
```

### destroy

Deallocates the String instance.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** void.

##### Example

```c
String *str = wrapString("toto");
str->proto->destroy(str);
//deallocates str
```

### destroy

Deallocates the String instance.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** void.

##### Example

```c
String *str = wrapString("toto");
str->proto->destroy(str);
//deallocates str
```

### destroy

Deallocates the String instance.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** void.

##### Example

```c
String *str = wrapString("toto");
str->proto->destroy(str);
//deallocates str
```

### destroy

Deallocates the String instance.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** void.

##### Example

```c
String *str = wrapString("toto");
str->proto->destroy(str);
//deallocates str
```

### destroy

Deallocates the String instance.

**Parameters:** 
- wrapper (String *): a pointer to a String wrapper.

**Returns:** void.

##### Example

```c
String *str = wrapString("toto");
str->proto->destroy(str);
//deallocates str
```