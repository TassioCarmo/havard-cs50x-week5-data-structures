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
1 // Implements a list of numbers with an array of fixed size
2
3 #include <stdio.h>
4
5 int main(void)
6 {
7   // List of size 3
8   int list[3];
9
10   // Initialize list with numbers
11  list[0] = 1;
12  list[1] = 2;
13  list[2] = 3;
14
15  // Print list
16  for (int i = 0; i < 3; i++)
17  {
18      printf("%i\n", list[i]);
19  }
20 }

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
}
```


## Linked lists

With a linked list, we have the tradeoff of needing to allocate more memory for each value and pointer, in order to spend less time adding values. (When we copy an array, we do need to allocate more memory, but we free the old array once we finish copying it.)

![image](https://user-images.githubusercontent.com/31789624/199869997-abd5aec2-6c0b-40c9-9598-b6c6358b1ece.png)


![image](https://user-images.githubusercontent.com/31789624/199870012-0c20739a-d055-43aa-ad99-9963a642eb38.png)

We use nodes, which is a component of a data structure encapsulates some information. We can implement a node with a struct:
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
if (n != NULL)
{
    n->number = 1;
    n->next = NULL;
}

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

list->next = n;

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



This is bad , because you will orphan the rest of the list

<code>list = n;</code>


do this
```
n->next = list;
list = n;
```

## Trees

### binary search tree

preserved the upsides of dynamic memory allocation, giving the ability to just add another element, add another element, add another element. But retain the power of binary search

 
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
other 

Time complexity of searching in linked list O(n)

Time complexity of inserting data in linked list O(n) if sorting and o(1) if not


linked list can you remember only remember the next node in the list

An array has a very specific meaning. It's memory that's contiguous, back, to back, to back.

malloc uses space from the heap, which was drawn at the top of the picture, pointing down. 

There's also stack memory, which is where all of your local variables go. And where all of the memory used by individual functions go. And that was drawn in the picture is working its way up. That's just an artist's rendition of direction. 

The compiler, essentially, will also help keep track of which values are valid or not inside of the stack. Or really the underlying code that you've written will keep track of that for you. So it's managed for you at that point. 

You never have to free pointers, per se. You should only free addresses that were returned to you by malloc.
