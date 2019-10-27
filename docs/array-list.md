## Array Lists

These functions are built to lessen the burden of having to manage dynamic arrays. They add a simple way of managing a list of pointers to focus on what is more important in an application.

### Description

This Module provides ArrayLists which rely on allocation/reallocation to keep the smallest memory footprint possible. You may provide any data pointer to an ArrayList, and they will be kept in memory by the list. Keep in mind the list will only keep the pointer and will not attempt to copy the data it references so it is preferable if those pointers reference heap chunks (allocated via malloc()). Otherwise, the chunks will be freed automatically at the end of their lifetime (end of function call for example) and the pointers stored will reference corrupted memory (= undefined behavior). The destroy function will provide a hook for you to free the objects you passed to the list, so you don't have to keep an inventory of all the pointers that reference allocated memory, if you added them to an ArrayList. Most ArrayList methods will return shallow copies of ArrayList and do not modifiy the provided ArrayList directly. Remember that only one ArrayList needs to free the referenced objects, the others need to pass NULL as the hook parameter whilst calling destroy. Note that the ArrayList keeps the order in which you inserted item inside of it. ArrayList structures contain a pointer to a Prototype object that contains a pointer to all ArrayList methods. Therefore, all ArrayList methods are accessed through their Prototype as shown in the examples below.

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
1. [clone](#clone)
1. [get](#get)
1. [set](#set)
1. [concat](#concat)
1. [every](#every)
1. [filter](#filter)
1. [find](#find)
1. [findIndex](#findIndex)
1. [forEach](#forEach)
1. [includes](#includes)
1. [indexOf](#indexOf)
1. [map](#map)
1. [reduce](#reduce)
1. [slice](#slice)
1. [some](#some)
1. [sort](#sort)
1. [destroy](#destroy)

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
- value (void *): the element to add.

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

**Returns:** the removed element.

##### Example

```c
ArrayList *list = newArrayList();
list->proto->push(list, ptr1);
list->proto->push(list, ptr2);
void *removed = list->proto->pop(list);
//removes ptr2 from the list and returns it.
```

### fill

Retuns a shallow copy of this ArrayList filled from start index to end index excluded with the pointer passed as parameter.
Start index must be smaller than end index and end index must be smaller or equal to the list's size, otherwise a pointer to the original list is returned.

**Parameters:** 
- list (ArrayList *): a pointer to an ArrayList.
- value (void *): a pointer to the element to fill the list with.
- start (size_t): starting index.
- end (size_t): ending index.

**Returns:** a pointer to a shallow copy of the filled ArrayList if parameters are valid, otherwise a pointer to the original list.

##### Example

```c
ArrayList *list = newArrayList();
list->proto->push(list, ptr1);
list->proto->push(list, ptr2);
ArrayList *list2 = list->proto->fill(list, ptr1, 0, 2);
//list2 is composed from 2 pointers: ptr1 ptr1.
```

### clone

Retuns a shallow copy of this ArrayList.

**Parameters:** 
- list (ArrayList *): a pointer to an ArrayList.

**Returns:** a pointer to a shallow copy of the filled ArrayList.

##### Example

```c
ArrayList *list = newArrayList();
list->proto->push(list, ptr1);
list->proto->push(list, ptr2);
ArrayList *list2 = list->proto->clone(list);
//list2 is composed from 2 pointers: ptr1 ptr2.
```

### get

Returns the element at the given index. If index is out of the ArrayList boundaries NULL is returned.

**Parameters:** 
- list (ArrayList *): a pointer to an ArrayList.
- index (size_t): the index of the element to retrieve.

**Returns:** the data pointer at the given index or NULL.

##### Example

```c
list->proto->get(list, 0);
// retrives pointer at index 0.
```

### set

Modifies the element at the given index. If index is out of the ArrayList boundaries, nothing happens. Set directly modifies the passed ArrayList.

**Parameters:** 
- list (ArrayList *): a pointer to an ArrayList.
- index (size_t): the index of the element to retrieve.
- value (void *): a data pointer to replace the target with.

**Returns:** void.

##### Example

```c
list->proto->set(list, 0, ptr);
// changes value of the element at position 0 of the list to ptr.
```

### concat

Merges two ArrayLists. It doesn't modify either of the ArrayList and instead returns a new ArrayList.

**Parameters:** 
- list (ArrayList *): a pointer to the first ArrayList.
- list2 (ArrayList *): a pointer to the second ArrayList.

**Returns:** a pointer to the result ArrayList.

##### Example

```c
ArrayList *list = newArrayList();
list->proto->push(list, ptr1);
ArrayList *list2 = newArrayList();
list2->proto->push(list2, ptr2);
ArrayList *res = list->proto->concat(list, list2);
// res contains ptr1 and ptr2.
```

### every

Tests whether all elements in the ArrayList pass the test implemented by the provided function.

**Parameters:** 
- list (ArrayList *): a pointer to the ArrayList.
- predicate (bool (*)(void *, size_t)): a pointer to a function returning a boolean. It will be called for each element of the ArrayList: the first parameter is the element and the second its index.

**Returns:** true if all elements pass the test, false otherwise.

##### Example

```c
bool test(void *e, size_t i)
{
    return strlen((char *)e) == 4;
}

ArrayList *list = newArrayList();
list->proto->push(list, "toto");
list->proto->push(list, "titi");
list->proto->every(list, test);
// returns true
// Warning: string literals where used for the sake of this example, replace them with heap-allocated strings in real world development!
```

### filter

Creates a new ArrayList with all elements that pass the test implemented by the provided function.

**Parameters:** 
- list (ArrayList *): a pointer to the ArrayList.
- predicate (bool (*)(void *, size_t)): a pointer to a function returning a boolean. It will be called for each element of the provided ArrayList: the first parameter is the element and the second its index.

**Returns:** an ArrayList containing all the element that passed the test.

##### Example

```c
bool test(void *e, size_t i)
{
    return strlen((char *)e) == 4;
}

ArrayList *list = newArrayList();
list->proto->push(list, "toto");
list->proto->push(list, "titi");
list->proto->push(list, "tatas");
ArrayList *res = list->proto->filter(list, test);
// res contains pointer to "toto" & "titi"
// Warning: string literals where used for the sake of this example, replace them with heap-allocated strings in real world development!
```

### find

Returns the value of the first element in the provided ArrayList that satisfies the provided testing function or otherwise NULL.

**Parameters:** 
- list (ArrayList *): a pointer to the ArrayList.
- predicate (bool (*)(void *, size_t)): a pointer to a function returning a boolean. It will be called for each element of the ArrayList: the first parameter is the element and the second its index.

**Returns:** the first element satisfying the provided test or NULL if no element passed the test.

##### Example

```c
bool test(void *e, size_t i)
{
    return strstr((char *)e, "ti") != NULL;
}

ArrayList *list = newArrayList();
list->proto->push(list, "toto");
list->proto->push(list, "titi");
list->proto->push(list, "tatas");
list->proto->push(list, "titis");
list->proto->find(list, test);
// returns the pointer to "titi"
// Warning: string literals where used for the sake of this example, replace them with heap-allocated strings in real world development!
```

### findIndex

Returns the index of the first element in the provided ArrayList that satisfies the provided testing function or otherwise -1.

**Parameters:** 
- list (ArrayList *): a pointer to the ArrayList.
- predicate (bool (*)(void *, size_t)): a pointer to a function returning a boolean. It will be called for each element of the ArrayList: the first parameter is the element and the second its index.

**Returns:** the index of the first element satisfying the provided test or -1 if no element passed the test.

##### Example

```c
bool test(void *e, size_t i)
{
    return strstr((char *)e, "ti") != NULL;
}

ArrayList *list = newArrayList();
list->proto->push(list, "toto");
list->proto->push(list, "titi");
list->proto->push(list, "tatas");
list->proto->push(list, "titis");
list->proto->findIndex(list, test);
// returns 1
// Warning: string literals where used for the sake of this example, replace them with heap-allocated strings in real world development!
```

### forEach

Executes a provided function once for each ArrayList element.

**Parameters:** 
- list (ArrayList *): a pointer to the ArrayList.
- callback (void (*)(void *, size_t)): a pointer to a procedure. It will be called for each element of the ArrayList: the first parameter is the element and the second its index.

**Returns:** void.

##### Example

```c
bool callback(void *e, size_t i)
{
    puts((char *)e);
}

ArrayList *list = newArrayList();
list->proto->push(list, "toto");
list->proto->push(list, "titi");
list->proto->push(list, "tatas");
list->proto->push(list, "titis");
list->proto->forEach(list, callback);
// prints each element of the list
// Warning: string literals where used for the sake of this example, replace them with heap-allocated strings in real world development!
```

### includes

Checks if the provided ArrayList contains the given element.

**Parameters:** 
- list (ArrayList *): a pointer to an ArrayList.
- value (void *): a data pointer to search the list for.

**Returns:** true if it contains the provided element, false otherwise.

##### Example

```c
list->push(list, ptr);
list->proto->includes(list, ptr);
// returns true
```

### indexOf

Returns the first index at which a given element can be found in the ArrayList, or -1 if it is not present.

**Parameters:** 
- list (ArrayList *): a pointer to an ArrayList.
- value (void *): a data pointer to search the list for.

**Returns:** the index of the element if it can be found within the list, -1 otherwise.

##### Example

```c
list->push(list, ptr);
list->proto->indexOf(list, ptr);
// returns 0
```

### map

Creates a new ArrayList with the results of calling a provided function on every element in the calling ArrayList.

**Parameters:** 
- list (ArrayList *): a pointer to the ArrayList.
- mapper (void *(*)(void *, size_t)): a pointer to a function that produces an element of the new list. It will be called for each element of the provided ArrayList: the first parameter is the element and the second its index.

**Returns:** a pointer to the new ArrayList.

##### Example

```c
void *mapper(void *e, size_t i)
{
    char *new = malloc(10);
    sprintf(new, "%s%s", e, "ta");
    return new;
}

ArrayList *list = newArrayList();
list->proto->push(list, "toto");
list->proto->push(list, "titi");
ArrayList *res = list->proto->map(list, mapper);
// res contains pointers to "totota" & "titita"
// Warning: string literals where used for the sake of this example, replace them with heap-allocated strings in real world development!
```

### reduce

Executes a reducer function (that you provide) on each element of the ArrayList, resulting in a single output value.

**Parameters:** 
- list (ArrayList *): a pointer to the ArrayList.
- reducer (void *(*)(void *, void *)): a pointer to a function to execute on each element in the provided ArrayList. The first parameter is the accumulator (it accumulates the reducer's return values, it is the accumulated value previously returned in the last invocation of the reducer) and the second is the current element.
- initialValue (void *): it is the value the accumulator will be set to before beginning to apply the reducer on each element of the ArrayList.

**Returns:** the single value that results from the reduction.

##### Example

```c
void *reducer(void *acc, void *e)
{
  *(int *)acc = *(int *)acc + *(int *)e;
  return acc;
}

int t = 3;
int u = 4;
int v = 5;
ArrayList *list = newArrayList();
list->proto->push(list, &t);
list->proto->push(list, &u);
list->proto->push(list, &v);
int *res = malloc(sizeof(int));
*res = 0;
list->proto->reduce(list, reducer, res);
// *res is now equal to 12
```

### slice

Retuns a shallow copy of this ArrayList from start index to end index excluded.
Start index must be smaller than end index and end index must be smaller or equal to the list's size, otherwise a pointer to the original list is returned.

**Parameters:** 
- list (ArrayList *): a pointer to an ArrayList.
- start (size_t): starting index.
- end (size_t): ending index.

**Returns:** a pointer to a shallow copy of the sliced ArrayList if parameters are valid, otherwise a pointer to the original list.

##### Example

```c
ArrayList *list = newArrayList();
list->proto->push(list, ptr1);
list->proto->push(list, ptr2);
ArrayList *list2 = list->proto->slice(list, ptr1, 1, 2);
//list2 is composed from 1 pointer: ptr2
```

### some

Tests whether at least one element in the ArrayList pass the test implemented by the provided function.

**Parameters:** 
- list (ArrayList *): a pointer to the ArrayList.
- predicate (bool (*)(void *, size_t)): a pointer to a function returning a boolean. It will be called for each element of the ArrayList: the first parameter is the element and the second its index.

**Returns:** true if at least one element pass the test, false otherwise.

##### Example

```c
bool test(void *e, size_t i)
{
    return strlen((char *)e) == 4;
}

ArrayList *list = newArrayList();
list->proto->push(list, "toto");
list->proto->push(list, "titi");
list->proto->some(list, test);
// returns true
// Warning: string literals where used for the sake of this example, replace them with heap-allocated strings in real world development!
```

### sort

Sorts the element of an ArrayList. This function directly modifies the provided ArrayList.

**Parameters:** 
- list (ArrayList *): a pointer to an ArrayList.
- sortFunc (size_t (*)(void *)): a function that must return a positive integer to specify a sort order. It will be called for each element: the first parameter is the current element.

**Returns:** a pointer to the sorted ArrayList.

##### Example

```c
size_t sort(void *e)
{
  return *(int *)e;
}

int v = 5;
int u = 4;
int t = 3;

ArrayList *list = newArrayList();
list->proto->push(list, &v);
list->proto->push(list, &u);
list->proto->push(list, &t);
list->proto->sort(list, sort);
// list: t -> 3, u -> 4, v -> 5
```

### destroy

Deallocates the ArrayList instance.

**Parameters:** 
- list (ArrayList *): a pointer to the ArrayList instance.
- hook (void (*)(void *)): a hook to deallocate the elements that were passed to this list, set this to NULL if you don't want to do anything in particular. It will be called for each element of the list.

**Returns:** void.

##### Example

```c
void hook(void *e)
{
    free(e);
}

char *t = malloc(30);
char *u = malloc(30);
strcpy(t, "totototiti");
strcpy(u, "tatatett");
ArrayList *list = newArrayList();
list->proto->push(list, t);
list->proto->push(list, u);
list->proto->destroy(list, hook);
// deallocates list and calls free on t and u.
```
