## Rotation

### Building

To build this project:
```
git submodule init
git submodule update
mkdir build && cd build
cmake ..
make
```
This should generate:
* Rotation3D_run - actual program
* Rotation3D_tst - testing program
* doc_doxygen - documentation of code

## Program

### VectorAction and MatrixAction

Program use overload operator of standard vector and matrix as two-dimensional vector.

### Menu

Menu is declared in main. Supports operation like rotation, translation or animation. 

### Tests

There are 18 tests which testing Rectangular, VectorAction and MatrixAction.

### Doxygen 

After make project in build folder should appear doc_doxygen folder with html and latex documentation.

### More rectangular at once

Program draw 3 more figures which every rotate in other axis.