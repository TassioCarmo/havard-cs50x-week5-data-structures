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

Linked lists

![image](https://user-images.githubusercontent.com/31789624/199869997-abd5aec2-6c0b-40c9-9598-b6c6358b1ece.png)


![image](https://user-images.githubusercontent.com/31789624/199870012-0c20739a-d055-43aa-ad99-9963a642eb38.png)

An array has a very specific meaning. It's memory that's contiguous, back, to back, to back.

it stores the data and an pointer

Using more space save time and consarve space loses times , that is the trade off

We’ll call the group of boxes with a value and pointer a node, a component of a data structure encapsulates some information. We can implement a node with a struct:
```
typedef struct node
{
    int number;
    struct node *next;
}
node;
```
 - We start this struct with typedef struct node so that we can refer to a struct node inside our struct.
 - Then, we’ll have an int called number, for the value we want to store, and then a pointer to the next node with struct node. (We haven’t fully defined node yet, so the compiler needs to know it’s a custom struct still.)
 - Finally, node at the end lets us use just node in the rest of our program.

<code>node *n = malloc(sizeof(node));</code>




other 

malloc uses space from the heap, which was drawn at the top of the picture, pointing down. 

There's also stack memory, which is where all of your local variables go. And where all of the memory used by individual functions go. And that was drawn in the picture is working its way up. That's just an artist's rendition of direction. 

The compiler, essentially, will also help keep track of which values are valid or not inside of the stack. Or really the underlying code that you've written will keep track of that for you. So it's managed for you at that point. 
