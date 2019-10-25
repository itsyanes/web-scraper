## Array Lists

These functions are built to lessen the burden of having to manage dynamic arrays. They add a simple way of managing a list of pointers to focus on what is more important in an application.

### Description

This Module provides ArrayLists which rely on allocation/reallocation to keep the smallest memory footprint possible. You may provide any data pointer to an ArrayList, and they will be kept in memory by the list. Keep in mind the list will only keep the pointer and will not attempt to copy the data it references so it is preferable if those pointers reference heap chunks (allocated via malloc()). Otherwise, the chunks will be freed automatically at the end of their lifetime (end of function call for example) and the pointers stored will reference corrupted memory (= undefined behavior). The destroy function will provide a hook for you to free the objects you passed to the list, so you don't have to keep an inventory of all the pointers that reference allocated memory, if you added them to an ArrayList. Most ArrayList methods will return shallow copies of ArrayList and do not modifiy the provided ArrayList directly. Remember that only one ArrayList needs to free the referenced object, the other need to pass NULL as the hook parameter whilst calling destroy. Note that the ArrayList keeps the order in which you inserted item inside of it. ArrayList structures contain a pointer to a Prototype object that contains a pointer to all ArrayList methods. Therefore, all ArrayList methods are accessed through their Prototype as shown in the examples below.

### Table of Contents

#### Functions

Provided functions related to ArrayLists.

1. [newArrayList](#newarraylist)

#### Properties

Members of the ArrayList struct.

1. [_list](#_list)
1. [_blocks](#_blocks)
1. [size](#size)
1. [proto](#proto)

#### Prototype Methods

Methods of the prototype of ArrayList.

1. [push](#push)
1. [pop](#pop)
1. [fill](#fill)

## Contents

### newArrayList

Allocates a new instance of ArrayList.

**Returns:** an empty ArrayList instance.

##### Example

```c
ArrayList *list = newArrayList();
```

### _list

Pointer to the list of pointers stored in-memory. For internal use only.

### _blocks

Number of blocks of memory used by this ArrayList instance. For internal use only.

### size

The number of elements contained in this ArrayList. You may read it but never write to it!

##### Example

```c
ArrayList *list = newArrayList();
printf("%d", list->size);
//prints 0
```

### proto

Pointer to the ArrayList's prototype containing all methods.

##### Example

```c
ArrayList *list = newArrayList();
list->proto->someMethod();
//calls a method named someMethod from the prototype
```

### push

Adds an element at the end of list.

**Parameters:** 
- list (ArrayList *): a pointer to an ArrayList.
- value (void *): a pointer to the element to add.

**Returns:** the pointer to the ArrayList.

##### Example

```c
char *ptr = malloc(3000);
ArrayList *list = newArrayList();
list->proto->push(list, ptr);
//adds ptr at the end of the list
```

### pop

Removes the last element of the list. You may free it once your application doesn't need it anymore.

**Parameters:** 
- list (ArrayList *): a pointer to an ArrayList.

**Returns:** a pointer to the removed element.

##### Example

```c
ArrayList *list = newArrayList();
list->proto->push(ptr1);
list->proto->push(ptr2);
void *removed = list->proto->pop(list);
//removes ptr2 from the list and returns it.
```

### fill

Retuns a shallow copy of this ArrayList filled from start index to end index excluded, with the pointer passed as parameter.
Start index must be smaller than end index and end index must be smaller or equal to the list's size, otherwise a pointer to the original list is returned.

**Parameters:** 
- list (ArrayList *): a pointer to an ArrayList.
- value (void *): a pointer to the element to fill the list with.
- start (size_t): starting index.
- end (size_t): ending index.

**Returns:** a pointer to a shallow copy of the filled ArrayList.

##### Example

```c
ArrayList *list = newArrayList();
list->proto->push(ptr1);
list->proto->push(ptr2);
list->proto->fill(list, ptr1, 0, 2);
//list is now composed from 2 pointers: ptr1 ptr1.
```
