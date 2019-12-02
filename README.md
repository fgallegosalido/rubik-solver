# rubik-solver
A program that solves a Rubik's cube

# Instructions
To compile the program, first download the repository and move to it by doing:

```bash
$> git clone https://github.com/fgallegosalido/rubik-solver.git
$> cd rubik-solver
```

Now execute the next commands to compile the executables:

```bash
$> mkdir build
$> cd build
$> conan install ..
$> cmake .. -DCMAKE_BUILD_TYPE=Release
$> make
```

# Requirements
These are the versions the project is compiled with, but lower versions may work:

* GCC 9.2.1
* CMake 3.16.0
* Conan 1.20.4

# Contributions
You can always collaborate in the project by adding new algorithms, new methods, reporting bugs, etc.

If you just want to collaborate by adding new algorithms that I can use for new solving methods, just add them in the file `include/cube_algorithms.hpp` under the `algorithms::the_method_name` namespace (if you're not sure how to add them, just follow how tha other algorithms are declared).
