What is Bootforth?
------------------

Bootforth is:
- A framework for prototyping your own forth system
- Example code for doing a C based forth system
- A system for compiling a real Forth system(Bootstrapping)
- A minimal forth system
  - No libs
    - Which means that no libraries for networking, games,
      multimedia, websites, services, file formats, sound
      and etc. are supplied
  - No floating point numbers
  - No foreign function interface
  - Not really any bells or whistles
- An indirect threaded Forth system(as far as I know)
- Portable, it should compile under any C compiler(hopefully)
  - But it's not intended to be very fast, because it's portable
    without much feature baggage. 
    But: It's still fast enough for our neurons(Alan Kay)
  - Features like using optimized routines or using special
    facilities of the OS reduce portability or increase
    complexity, both aren't intended by Bootforth
- Small & uncomplicated
  - ANSI C
    - Or trying at least to use ANSI C
  - Depending only on well supported C libraries which are
    hopefully: string, stdlib and stdio
  - No autoconf configuration system instead good old Makefiles
    - Because it only makes sense for bigger projects and it
      depends too much on the current version of it which
      means that it brings complexity into the compilation
      process, which isn't intended for Bootforth
    - Which puts automatically a nice size limit on it,
      so Bootforth can't grow over the size of understanability
      (Well yes it can, but then it's not understandable anymore)

Bootforth isn't:
- A full blown Forth system
  - Like gforth, which has thousands of words
  - It is intended that when the words are listed on screen,
    they don't need to be scrolled to see all of them
- Damn fast, it does only linking, no optimization or usage
  of real opcodes(machine code) at all, just pseudo cpu code(VM).
  - 'Pseudo cpu code' just means a kind of indirect threading code
- One of those fancy programming languages with a 
  Garbage Collector
- Something like Java, C#, Python, Factor, Perl, Ruby, etc.
  - It's more something like say C or Assembler


The idea behind Bootforth
-------------------------

Because of so much dialects of Forth, no difference if they
are or were a standard or not. Writing a Forth System in
Forth isn't so easy, because you mostly have the limitations
of the host system in the result system. To solve that there
is bootforth. A Forth system framework in C with a collection of 
primitives and a relative easy way to define your own
Forth words, so that you have a base for your real implementation
of your own Forth System.


Directories
-----------

doc/       -- Documentation
tests/     -- Some tests during development, not all are up to date 
scratch/   -- Some play code during development, not all was written
              in Bootforth(Experiments)
snippets/  -- Forth code snippets for your inspiration
templates/ -- Templates for creating your own Forth Interpreter
samples/   -- Some example Forth Interpreters


Licenses
--------

All the code of BootForth is under the GPL, that means the C source
and header files in the current directory. 


Warranty/Guaranty
-----------------

BootForth is/was a hobby project for me which I want to share
with other people. So you can imagine, that this doesn't comes
with any warranty and yes that's true. BootForth doesn't come
with ANY warranty, functionality isn't granted or that it doesn't
harm you or anything else which would have a value for you or any
other person. 

I repeat it doesn't come with any warranty/guaranty, when
you use it, you are on your own.


Dependencies
------------

* an ANSI C compiler
  - Works so far with:
    * gcc
      - 4.1.2
      - probably all versions
    * tcc
      - 0.9.23
      - probably all versions
* C standard library: string.h, stdio.h, stdlib.h 
* ASCII Input
