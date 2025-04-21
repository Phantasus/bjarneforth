# Journal

## 21. April 2025

Happy easter monday, for those who care about that stuff. Today
I moved the stack into the memory, the idea is that when the stack
is stored in memory it can be serialized out when dumping the
memory to a file. For that case now stacks can be allocated with
`bf_allot_stack` and with helpers for the `bf_state`
like `bf_allot_dstack` and `bf_allot_rstack`.

Previously I added `bf_read_stack` for reading a stack from a memory
image, but discarded it as I have not yet written that part of reading
back a `bf_state` from a memory dump.

For this feature also one needs relocateable memory addresses, that
means also slowed down memory access as everything is indirectly
accessed.

## 19. April 2025

So.. getting back to this after a couple of weeks distraction in my real life.
Today I added a couple of tests for testing parsing names.

## 18. March 2025

Well, before the compiler, interpreter was broken and now it certainly is even more.
I threw out the "clever" way of storing flags into the first byte of the name
of a word field and also threw out the index based construction of a word
entirely. That stuff was always confusing and in the end it was to just
save some bytes when creating a new word in the dictionary.

I currently try to understand how the behemoth, this internal interpreter
actually works again. I mean it should be rather "easy" compared with
all other interpreters of any other programming language out there.

In forth there are words and they have fields. The real complication
of everything is the `(does)` word, used for implementing `does>`.
Which combines data and code, I try to remember how the memory layout
was supposed to be in a forth system.

Forth uses normally a treaded code technique in interpreting code,
back then when I wrote this code I wanted to make it more conforming to
this style. But I remember I had some troubles, which is why I chose to
implement some "opcodes", which would not be there in a pure threaded code
style.

And here again I write down a little bit about word dictionaries in
forth. I looked up https://wiki.forth-ev.de/lib/exe/fetch.php/projects:movingforth:brad_rodriguez-forth_v16_all_for_pictures_a4.pdf

So, we have different kinds of words:

- `link`, they execute other words inside.
- `literal`, literals are constants, they put data on the stack when executed.
- `does`, handles the behavior of a does word, where data and code are combined.

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
