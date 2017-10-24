# Introduction #

`SizeGripItem` is a size grip `QGraphicsItem` for interactively resizing
other `QGraphicsItem` objects. It draws a size grip with 8 interactive
handles around its parent so that it can be interactively resized.

# Installation #

There is no installation procedure. To use `SizeGripItem` in your own project,
just copy the `SizeGripItem.h` and `SizeGripItem.cpp` files and add them to
your build.

# Usage #

SizeGripItem is designed to resize its parent item. You add a `SizeGripItem`
to another `QGraphicsItem` simply by setting that item to be the
`SizeGripItem`'s parent.

When you create a new `SizeGripItem`, you must pass its constructor a pointer
to an instance of a subclass of the `SizeGripItem::Resizer` class.
`SizeGripItem::Resizer` is an abstract class with a pure virtual `operator()`
with the following signature:

```c++
void operator()(QGraphicsItem* item, const QRectF& rect)
```

A subclass of `SizeGripItem::Resizer` must implement `operator()` with the
signature above so that `item` is resized to fit `rect` when a call to the
operator is made. `rect` corresponds to the rectangle described by the
`SizeGripItem`'s handles and its coordinates are in the `SizeGripItem`'s
coordinate system.

`SizeGripItem` instances take ownership of the `SizeGripItem::Resizer` pointer
passed to them on construction, which means that pointer is deleted when
the `SizeGripItem` is destroyed.

# Example Code #

The `demo/` directory provides example code for using `SizeGripItem`. You can
build and run the demo using CMake >=2.8.0 as follows (assuming you are
at the project's root directory):

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ ./demo/sizegripitemdemo

# License #

SizeGripItem is under the MIT license. See LICENSE for details.
