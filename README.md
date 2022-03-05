# BookstoreSimC
Henry Sotheran created a
[bookstore micro-RPG](https://twitter.com/Sotherans/status/1491570607686836230)
which I initially coded up
[in Python](https://gist.github.com/Gumnos/8b6ab546ae968fa34d0b8fc07ffc2477),
but have rewritten it here in C for speed.

It should be pretty straightforward assuming you have a C compiler installed:

    $ make
    ./bs

If you don't want the color output,
you can remove or comment out the

    #define COLOR 1

toward the top of the `bs.c` file.

It only uses standard C libraries,
so there are no dependencies,
nor is there any need to run
`./configure`
to deal with machine-specific quirks.
