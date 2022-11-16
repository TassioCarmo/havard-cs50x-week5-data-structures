# Introduction to data structures

## What did i learn

if you have an array a specific size and wants to add more data, it becomes problematic because the computer might have already puts some garbage data next to it

<img src = "https://user-images.githubusercontent.com/31789624/199865763-74afb38f-da44-4661-b174-a73cf11f60fd.png">

and inserting takes O(n) because you have to copy over all the existing data into the new array into a new array

<code>int list[3];  // puts on the memory on the stack automatically</code>  
<code>int *list = malloc(sizeof(int);  // puts on heap</code>  

And only on the heap you can ask for more memory and give it back


- struct to create custom data types
- . to access fields, or values, in a structure
- * to go to an address in memory pointed to by a pointer
- -> to access fields in a structure pointed to by a pointer



## Growing arrays
```
// Implements a list of numbers with an array of fixed size

 #include <stdio.h>
int main(void)
 {
  // List of size 3
   int list[3];

   // Initialize list with numbers
  list[0] = 1;
  list[1] = 2;
  list[2] = 3;

  // Print list
  for (int i = 0; i < 3; i++)
  {
   printf("%i\n", list[i]);
  }
 }

--------------------------------------------------

// Implements a list of numbers with an array of dynamic size
#include <stdio.h>
#include <stdlib.h>
  
int main(void)
{
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }
  
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
// List of size 4
int *tmp = malloc(4 * sizeof(int));
if (tmp == NULL)
{
    free(list);
    return 1;
}
// Copy list of size 3 into list of size 4
for (int i = 0; i < 3; i++)
{
    tmp[i] = list[i];
}
// Add number to list of size 4
tmp[3] = 4;

// Free list of size 3
free(list);

// Remember list of size 4
list = tmp;
// Print list
for (int i = 0; i < 4; i++)
{
    printf("%i\n", list[i]);
}
// Free list
free(list);
return 0;

/* First, we’ll allocate enough memory for three integers and point to the first one with int *list. 
*  (If malloc fails, our pointer will be null, and we’ll exit our  program with return 1.)
*
* Since arrays in C are equivalent to pointers, we can use the same notation to set the values in our list with list[0], list[1],
* and list[2]. The compiler will perform the correct pointer arithmetic to set values at the right addresses.
*/
```
realock
```
#include <stdio.h>
#include <stdlib.h>
  
int main(void)
{ 
    // Dynamically allocate an array of size 3
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }
  
    // Assign three numbers to that array
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // Time passes

    // Resize old array to be of size 4
    int *tmp = realloc(list, 4 * sizeof(int));
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    // Add fourth number to new array
    tmp[3] = 4;

    // Remember new array
    list = tmp;

    // Print new array
    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    // Free new array
    free(list);
    return 0;
    
    
 /* After we allocate enough memory for four integers, we need a temporary pointer, tmp,
 * since we need to copy values from our original list into the new chunk of  memory.
 * (If malloc fails, we’ll free the original memory and exit our program with return 1.)
 */
// We’ll use a for loop to copy the values from list, and set the final value in tmp.

}
```


## Linked lists

linked list, we can store a list of values in different parts of memory:

with that we have a tradeoff of needing to allocate more memory for each value and pointer, in order to spend less time adding values. (When we copy an array, we do need to allocate more memory, but we free the old array once we finish copying it.)

![image](https://user-images.githubusercontent.com/31789624/199869997-abd5aec2-6c0b-40c9-9598-b6c6358b1ece.png)


![image](https://user-images.githubusercontent.com/31789624/199870012-0c20739a-d055-43aa-ad99-9963a642eb38.png)

**Nodes** , which is a component of a data structure encapsulates some information. We can implement a node with a struct:
```
typedef struct node
{
    int number;
    struct node *next;
}

node;
```
We can build a linked list in code starting with our struct. First, we’ll want to remember an empty list, so we can use the null pointer: <code>node *list = NULL;</code>. To add a node, we’ll first need to allocate some memory:


<code>node *n = malloc(sizeof(node));</code>

```
if (n != NULL)
{
    n->number = 1;
    n->next = NULL;
}
```
- Since n is a pointer, we need to go to the node there first, and then use the . operator to set a value, so instead of (*n).number, we can write <code>n->number</code>, which has the same effect.


Finally, our list needs to point to the node: list = n;:

![image](https://user-images.githubusercontent.com/31789624/200134359-6c7fda3e-0da1-4009-9e91-90f595c9316d.png)



## Growing linked lists

To add to the list, we’ll create a new node the same way by allocating more memory:
```
n = malloc(sizeof(node));
if (n != NULL)
{
    n->number = 2;
    n->next = NULL;
}
```

n is a temporary variable we use to point to this new node:

![image](https://user-images.githubusercontent.com/31789624/200134384-c9700bbe-c004-4ea0-8f36-55bf4c54e43f.png)

And now we need to update the pointer in our first node to point to our new n, since we want to maintain a sorted list:

<code>list->next = n;</code>

![image](https://user-images.githubusercontent.com/31789624/200134401-72b7f558-b076-4eae-a10c-e527628b8e3c.png)

To add a third node, we’ll allocate more memory again:
```
node *n = malloc(sizeof(node));
if (n != NULL)
{
    n->number = 3;
    n->next = NULL;
}
```

![image](https://user-images.githubusercontent.com/31789624/200134422-18390149-2b39-4620-a169-4e1e675f32ba.png)

To insert this node in our list, we’ll want to follow the next pointer in the first node that list points to (the node with value 1), then setting the next pointer in that node (with value 2) to point to the new node:

<code>list->next->next = n;</code>

-------------------------------------------------

This is bad , because you will orphan the rest of the list

<code>list = n;</code>


do this
```
n->next = list;
list = n;
```

## Tree

- Every node needs 3 pieces of data. A number and now 2 pointers. 
- there's that trade off . Where, if you want to save time, you've got to give something if you start giving space. And you start using more space, you can speed up time. 
- If you free the node you are on first you're not allowed to touch the left child tree or the right child tree. Because the memory address is no longer valid at that point. 
- Each node has at most two children, or nodes it is pointing to.
- preserved the upsides of dynamic memory allocation, giving the ability to just add another element, add another element, add another element. But retain the power of binary search
- You can retain and remember this entire tree just by pointing at the root node. One variable can hang on to the whole tree. 

 
![image](https://user-images.githubusercontent.com/31789624/200136810-e709cc28-9070-44fc-ae2f-a20fd132d6b3.png)

- Each node has not one but two pointers to other nodes. All the values to the left of a node are smaller, and all the values of nodes to the right are greater, which allows this to be used as a binary search tree.
- Each node has at most two children, or nodes it is pointing to.
- And like a linked list, we’ll want to keep a pointer to just the beginning of the list, but in this case we want to point to the root, or topmost node of the tree (the 4).
- To search for a number, we’ll start at the root node, and be able to recursively search the left or right subtree.
- The height of this tree is 3, or, since each parent node has up to two children.

```
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node;

int main(void)
{
    // Tree of size 0
    node *tree = NULL;
  
    // Add number to list
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 2;
    n->left = NULL;
    n->right = NULL;
    tree = n;

// Add number to list
n = malloc(sizeof(node));
if (n == NULL)
{
    free_tree(tree);
    return 1;
}
n->number = 3;
n->left = NULL;
n->right = NULL;
tree->right = n;

// Print tree
print_tree(tree);

// Free tree
free_tree(tree);
return 0;
}
void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    print_tree(root->left);
    printf("%i\n", root->number);
    print_tree(root->right);
}


```

### Binary search if tree

binary search tree is a tree where the root is greater than its left child and smaller than its right child

```
binary search:

bool search(node *tree, int number)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (number < tree->number)
    {
        return search(tree->left, number);
    }
    else if (number > tree->number)
    {
        return search(tree->right, number);
    }
    else if (number == tree->number)
    {
        return true;
    }
}

```
time complexity

O(log n) if you  maintain the balance of the tree. otherwise Both, in certain search, could actually devolve into , big O of n. 


## Hash table

is a data structure that allows us to associate keys with values. It looks like an array, where we can jump to each location by its index:

![image](https://user-images.githubusercontent.com/31789624/200137768-c2e02785-1135-4d00-bc57-aa7c5f429f0a.png)


![image](https://user-images.githubusercontent.com/31789624/200137775-17477467-2807-41e0-ae64-26bd6df0dd12.png)

think of these 26 locations, now in the context of a hash table, is what we'll call them buckets. So buckets into which you can put values. 

```

typedef struct node
{
    char word[LONGEST_WORD + 1];
    struct node *next;
}
node;

```
Each node will have an array of characters already allocated, of maximum size LONGEST_WORD + 1, called word, that it’s storing. Then, a next pointer will point to another node, if there is one.

```
node *hash_table[NUMBER_OF_BUCKETS];
```

 The hash table will be an array of pointers to nodes, with NUMBER_OF_BUCKETS as its size.
 

Hash table could be thought An array whose elements are linked lists

A hash function is generally something that takes as input, a string, a number, whatever, and produces as output a location in our context. Like a number 0 through 25. Or 0 through 16,000. Or whatever the number of buckets you want is, it's going to just tell you where to put that input at a specific location. 

Theoretically it's O(O) but in practice is much more faster than an linked list

### Trie  short for “retrieval”

 is a tree with arrays as nodes

![image](https://user-images.githubusercontent.com/31789624/200139461-81667c56-8280-4572-a1fc-57bb1e11e8ec.png)

```
typedef struct node
{
    bool is_word;
    struct node *children[SIZE_OF_ALPHABET];
}
node;

```


- At each node, or array, we’ll have a boolean value that indicates if it’s a valid word (whether or not it should be green). Then, we’ll have an array of SIZE_OF_ALPHABET pointers to other nodes, called children.

- the height of our tree is the length of the longest word we want to store.
- And even if our data structure has lots of words, the maximum lookup time will be just the length of the word we’re looking for. This might be a fixed maximum, so we have a constant time O(1),, for searching and insertion.
- The cost for this, though, is that we need lots of memory to store mostly null pointers.


## Pros and cons Data structures

### Array
- Insertion is bad –lots of shifting to fit an element in the middle
- Deletion is bad –lots of shifting after removing an element
- Lookup is great –random access, constant time
- Relatively easy to sort
- Relatively small size-wise
- Stuck with a fixed size, no flexibility

### Linked lists
- Insertion is easy –just tack onto the front
- Deletion is easy –once you find the element
- Lookup is bad –have to rely on linear search
- Relatively difficult to sort –unless you’re willing to compromise on super-fast insertion and instead sort as you construct
- Relatively small size-wise (not as small as arrays)

### Hash tables
- Insertion is a two-step process –hash, then add
- Deletion is easy –once you find the element
- Lookup is on average better than with linked lists because you have the benefit of a real-world constant factor
- Not an ideal data structure if sorting is the goal –just use an array
- Can run the gamut of size

### Tries
- Insertion is complex –a lot of dynamic memory allocation, but gets easier as you go
- Deletion is easy –just free a node
- Lookup is fast –not quite as fast as an array, but almost
- Already sorted –sorts as you build in almost all situations
- Rapidly becomes huge, even with very little data present, not great if space is at a premium


## other 

Time complexity of searching in linked list O(n)

Time complexity of inserting data in linked list O(n) if sorting and o(1) if not

recursion tends to work in lockstep with t these kinds of data structures(trees). 

linked list can you remember only remember the next node in the list

An array has a very specific meaning. It's memory that's contiguous, back, to back, to back.

malloc uses space from the heap, which was drawn at the top of the picture, pointing down. 

There's also stack memory, which is where all of your local variables go. And where all of the memory used by individual functions go. And that was drawn in the picture is working its way up. That's just an artist's rendition of direction. 

The compiler, essentially, will also help keep track of which values are valid or not inside of the stack. Or really the underlying code that you've written will keep track of that for you. So it's managed for you at that point. 

You never have to free pointers, per se. You should only free addresses that were returned to you by malloc.

Return means quit

The arrow operator ( (-->>) makes this process easier. It’s an
operator that does two things back to back:
- First, it dereferences the pointer on the left side of the operator.
- Second, it accesses the field on the right side of the operator.


Either you're going to minimize space or you're going to minimize time. 

It's not really possible to get truly the best of both worlds. You have to decide where the inflection point is for the device you're writing software for, how much memory it has, how expensive it is. And again, taking all of these things into account. 
