# CPractice

Some exercises I wrote to brush up on my old C knowledge.  There are several modules, 
each of which needs to be invoked with a command line argument.  4 arguments/modules are 
available:

1) -h           is just "Hello World"

2) -t           is a simple temperature conversion routine

3) -s string    does a binary search for "string" in a list of fruits.  The fruits are 
                hard-coded, so don't even try a vegetable.  Meats are definitely off-limits.
                
4) -c filename  prints out a cross-referenced, alphabetical list of the words in a file; 
                stores the word, the # times each word appears, and the line numbers on 
                which it appears; the info is stored in a tree structure, and in the end 
                written into a convenient array (and to the screen, twice - once from the
                tree structure and once from the array).
               
You can write the arguments as -hts string -c filename
