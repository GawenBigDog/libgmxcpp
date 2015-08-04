/*
 * libgmxcpp
 * Copyright (C) 2015 James W. Barnett <jbarnet4@tulane.edu>
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * The full license is located in a text file titled "LICENSE" in the root
 * directory of the source.
 *
 */

/**@file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date December 5, 2014
 * @brief Header for Frame class
 */

#ifndef FRAME_H
#define FRAME_H
#include "gmxcpp/xdrfile.h"
#include "gmxcpp/xdrfile_xtc.h"
#include "gmxcpp/Index.h"
#include "gmxcpp/Utils.h"
#include "gmxcpp/coordinates.h"
#include "gmxcpp/triclinicbox.h"

/**
 * @brief Class with information on one trajectory frame.
 *
 * @details A Frame contains the information on the time, the step, and the
 * coordinates and box for that time/step. rvec and matrix types come
 * from the xdrfile library. rvec is actually a float matrix with three
 * elements. It is pointer here so that later it will be initialized
 * as an array containing the coordinates of all of the atoms of the frame.
 * The matrix type is just a 3 x 3 array. Frame objects are usually not created
 * on their own, but instead are created as a vector in a Trajectory object.
 */

class Frame {
public:
/** Number of atoms in the system */
int natoms;
/** Simulation step corresponding with this frame. */
int step;
/** Simulation time (picoseconds) corresponding with this frame. */
float time;
/** Coordinates for all atoms in this frame. */
vector <coordinates> x;
/** Box dimensions for this frame. matrix comes from libxdrfile. */
triclinicbox box;

/** @brief A constructor where the private data for the object is set.
 * @param step The step number corresponding with this simulation frame.
 * @param time The time (in picoseconds) corresponding with this
 * simulation frame.
 * @param box The box dimensions for this frame.
 * @param x The coordinates of every atom in this frame.
 * @param natoms The number of atoms in the system.
 * */
Frame(int step, float time, matrix box, rvec *x, int natoms);

};

#endif
