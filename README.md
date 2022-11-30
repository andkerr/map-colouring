Here's a little C routine demonstrating the [4-colour theorem](https://mathworld.wolfram.com/Four-ColorTheorem.html): every planar graph can be coloured in such a way that no neighbouring regions have the same colour.

After compiling, `colouring.c` accepts a 0-indexed edge list that labels
each vertex with an integer directly from STDIN. If you want to work with a
more descriptive edge list that uses non-integer labels for each vertex, 
run `processing.py`, which will convert your list to integers-only format and
pass it to the colouring routine.

NOTE: This routine only works with connected graphs right now.
