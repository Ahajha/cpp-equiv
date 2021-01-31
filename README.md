# cpp-equiv
A C++20 header-only equivalence relation library

## Intended use of this library:
Creating equivalence relations with indexes as elements, merging elements and testing for equivalence. Also supports adding and removing elements from existing equivalence relations, comparing fine-ness, creating all equivalence relations of a given size, and other auxilary functions/methods.

## Examples:
An example program is provided in /examples, the tests in /test can also be useful.

## How to include this library:
Only the contents of the /include folder are needed to use this library. The files immediately in the folder are the ones that can be included.

### equiv_relation
provides the base functionality

### equiv_relation_hash
provides a hash function for eq_relation

### equiv_relation_store
provides means for storing and accessing equivalence relations in a central location, if many references to them are needed and memory is a concern.

These files can either be including the exact path, or by linking the directory as a library path with the compiler, and using <equiv_relation>, <equiv_relation_hash>, or <equiv_relation_store>.

## Other Thoughts:
I opted for the MIT licence for this library, as I wanted to be fairly permissive with it. That said, if you do use it in a project, all I ask is you give me credit and let me know you've used it, I'm quite interested in what others can do with this!
