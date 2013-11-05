A solution for the Strip Packing Problem with C++
=================================================

Here is an implementation of a genetics algorithm for the `strip strip packing` over `galib` library for `C++`. To run our program you'll need to install the library and then compile the program as follow.


GALIB Installation
------------------

Download the `galib247.tgz` and place it in your `Ubuntu`. Then unpackage it and install. You'll need to remove the example 17 compilation, it gives an error.

 	$ tar xvfz galib247.tgz -C .
 	$ cd galib247/
 	$ nano examples/makefile // Remove the example17 of line 22
 	$ make
 	$ sudo make install

There you go!


STRIPPACKGA Running
-------------------

Just type `make` then run it with `./bin/strippackingproblem.run`