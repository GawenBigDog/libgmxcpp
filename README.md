#libgmxcpp

This is a small library used for reading in Gromacs files (.xtc and .ndx) for
use in analyzing the results. This basically interfaces with the xdrfile and implements an object-oriented style.

##Requirements

The [libxdrfile](ftp://ftp.gromacs.org/pub/contrib/xdrfile-1.1.1.tar.gz) library is required. It will need to be 
enabled as a shared library.

##Installation

To install do:

```bash
    $ wget https://github.com/wesbarnett/libgmxcpp/archive/v1.0.tar.gz
    $ tar xvzf v1.0.tar.gz
    $ cd libgmxcpp-1.0
    $ ./configure
    $ make
    # make install
```

Check out the example program in the example directory. To compile it do the
following in the example directory:

```bash
    $ make
```

Then you can run the program on an example xtc file and ndx file.

##Usage

See the example file as well as the comments in the source. 

The main idea is that you create a Trajectory object which contains all the
information from both the .xtc file (and optionally .ndx file). Trajectory
object methods are then used for analyzing the data.

###Construction

First, you should create a Trajectory object:

```c++
// Creates a Trajectory object with "traj.xtc" and "index.ndx"
// The index file is optional
// Both arguments are C++ strings
Trajectory traj("traj.xtc","index.ndx");
```

You could also make it a pointer:

```c++
Trajectory *traj = new Trajectory("traj.xtc","index.ndx");
```

In that case just remember to use "->" instead of "." when calling its methods.

Upon construction of a Trajectory object both the xtc file and the index file
are read into memory. The following sections detail how to access the data.

###Atomic Coordinates

To get the coordinates of an atom use GetXYZ() method:

```c++
rvec a; // rvec comes from xdrfile library and is a three dimensional float array
// Gets the 2nd atom of the 3rd frame of index group "C"
// Arguments are frame, group name, atom number, rvec variable with coordinates stored
traj.GetXYZ(2,"C",1,a);

// You can reverse the first two arguments:
traj.GetXYZ("C",2,1,a);

// You can omit the group, getting the 2nd atom in the entire system
traj.GetXYZ(2,1,a);
```

To print out the coordinates you would then do:

```c++
// X, Y, and Z are constants in Utils.h, equiv. to 0, 1, and 2
cout << a[X] << " " << a[Y] << " " << a[Z] << endl;
```

Usually you'll throw GetXYZ in a couple of loops to access the data you need.

###Box Dimensions

To get the box dimensions use GetBox() method:

```c++
matrix box; // matrix is a three by three float array from xdrfile library
// Gets the box dimensions from the first frame:
traj.GetBox(0,box);
```

###Number of Frames

To get the number of frames in the simulation use GetNFrames():

```c++
int nframes = traj.GetNFrames();
```

###Number of Atoms
To get the number of atoms in the entire system use GetNAtoms():

```c++
int natoms = traj.GetNAtoms();
```

To get the size (number of atoms in) a specific group pass the index name as an
argument:

```c++
// Gets the number of atoms in group "SOL"
int solsize = traj.GetNAtoms("SOL"):
```


###Time and Step
To get the time (in ps) corresponding with a frame use GetTime(*frame*):

```c++
// Gets the time of the 5th frame
float time = traj.GetTime(4);
```

To get the step for a frame use GetStep(*frame*):

```c++
// Gets the step corresponding with the 5th frame
int step = traj.GetStep(4);
```
