# Journal

## 15. March 2025

Ok, let's recapitulate shallowly what I did the last days. I refactored the
`bf_stack`, `bf_state`, `bf_stream` and `bf_memory`. I basically added tests
to them. And moved the multiple primitives into their own specific module
file of a group which defines what they "do". So all stack helpers into `bf_stack_prim`,
all math into `bf_stack_math`, etc.

This is to make it easier to test them and curate them. My plan is to take a couple
of them out, then "clean" them, test them and continue with the rest. That way
I can build a full testing framework for this project and also ensure that all
parts fit together.

The way I did that is maybe not ideal, as I did not move in small iterations, which
I would do with a running software, but here the code does not produce a working system
anyway.

On the cell. Previously I smashed all the pointers, signed, unsigned values into the
cell, which is the classical forth unit. The cell is stored 1:1 into memory and represents
the all-encompassing calculation unit. Forth symply does not care about types, it's
all an int and a memory address to it.

I tried to to adapt it with `intptr_t`, but this alone did not yield yet the result I wanted,
but maybe I made a mistake and just using `intptr_t` would be the thing to do. I think
at least an `union` of `intptr_t` and `uintptr_t` is the minimum for a cell. Let's see...

## 12. March 2025

Basically taking on again of the stuff, which I almost again abandoned.
This code was lying around, I tried to get it running again and then was not very happy
about how it was structured, especially as this is supposed to be some kind of portfolio
application, which reminds me of past greatness.

In the meantime a couple of things have changed and type conversions are not so appreciated
anymore as they were back then more common.

So I need to do a bigger refactor of this project! Yikes!
