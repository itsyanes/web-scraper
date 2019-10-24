## Array Lists

These functions are built to lessen the burden of having to manage dynamic arrays. They add a simple way of managing a list of pointers to focus on what is more important in an application.

### Description

This Module provides ArrayLists which rely on allocation/reallocation to keep the smallest memory footprint possible. You may provide any data pointer to an ArrayList, and they will be kept in memory by the list. Keep in mind the list will only keep the pointer and will not attempt to copy the data it references so it is preferable if those pointers reference heap chunks (allocated via malloc()). Otherwise, the chunks will be freed automatically at the end of their lifetime (end of function call for example) and the pointers stored will reference corrupted memory (= undefined behavior). The destroy function will provide a hook for you to free the objects you passed to the list, so you don't have to keep an inventory of all the pointers that reference allocated memory if you added them to an ArrayList. The ArrayList keeps the order in which you inserted item inside of it. ArrayList structures contain a pointer to a Prototype object that contains a pointer to all ArrayList methods. Therefore, all ArrayList methods are accessed through their Prototype as shown in the examples below.

### Table of Contents

#### Functions

Provided functions related to ArrayLists

1. [newArrayList](#newarraylist)

#### Properties

Members of the ArrayList struct.


