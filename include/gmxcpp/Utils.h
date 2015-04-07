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

/** @file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date December 5, 2014
 * @brief Some useful functions for processing trajectories
 * @details This file has some helper functions for calculating things like
 * distances, periodic boundary conditions, etc. This file must be included in
 * your code to use the functions and is located at 'gmxcpp/Utils.h'.
 */

#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sys/stat.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

#include "gmxcpp/coordinates.h"
#include "gmxcpp/triclinicbox.h"
#include "gmxcpp/xdrfile.h"
#include "gmxcpp/xdrfile_xtc.h"

using namespace std;

/**
 * @brief Adjusts for periodic boundary condition
 * @details User passes a vector, most likely a vector pointing from one atom
 * to another in the simulation. This function adjusts the vector such that if
 * it is longer than 1/2 the box size it accounts for the periodic boundary.
 * @param a Vector to be passed.
 * @param box The box dimensions.
 * @return Vector after pbc accounted for.
 */
coordinates pbc(coordinates a, triclinicbox box);

/** @brief Calculates the cross product.
 * @details Gets the cross product between vectors a and b and returns it.
 * @param a First vector to be crossed.
 * @param b Second vector to be crossed.
 * @return The resultant vector of the cross of a and b.
 */
coordinates cross(coordinates a, coordinates b);

/** @brief Calculates the distance between atom a and atom b.
 * @return Distance
 * @param a First atom in distance calculation
 * @param b Second atom in distance calculation
 * @param box Box dimensions
 */
double distance(coordinates a, coordinates b, triclinicbox box);

/** @brief Calculates the distance squared between atom a and atom b.
 * @return Distance
 * @param a First atom in distance squared calculation
 * @param b Second atom in distance squared calculation
 * @param box Box dimensions
 */
double distance2(coordinates a, coordinates b, triclinicbox box);

/** @brief Calculates the dot product between two vectors
 * @param a First vector in dot product
 * @param b Second vector in dot product
 * @return Dot product of a and b
 */
double dot(coordinates a, coordinates b);

/** @brief Calculates the magnitude of a vector
 * @return Magnitude
 * @param x Vector for which magnitude is desired
 */
double magnitude(coordinates x);

/** @brief Checks if a file exists
 * @param filename Name of the file to check
 * @return Whether or not the file exists
 */
bool fileExists(string filename);

/** @brief Calculates the volume of simulation box
 * @param box Box dimensions
 * @return Volume of box
 */
double volume(triclinicbox box);

/** Prints out coordinates cleanly with << */
ostream& operator<<(ostream &os, coordinates xyz);

/** Prints out box coordinates cleanly with << */
ostream& operator<<(ostream &os, triclinicbox box);

/** @brief Generates a random point on a sphere.
 * @param center The center of the sphere.
 * @param r The radius of the sphere.
 * @return The coordinates of the random point.
 */
coordinates gen_sphere_point(coordinates center, double r);

/** @brief Generates a random point on a sphere at the origin.
 * @param r The radius of the sphere.
 * @return The coordinates of the random point.
 */
coordinates gen_sphere_point(double r);

/** @brief Generates a random point on a unit sphere at the origin.
 * @return The coordinates of the random point.
 */
coordinates gen_sphere_point();

/** @brief Gets the acceptance ratio of randomly generated point on a sphere.
 * @details Points are randomly generated around all sites listed in the sites
 * vector at distance r away from each site. The resulting ratio is sum of the number
 * of points accepted per points generated. In other words each site will have
 * rand_n points generated. The points that are closest to that site compared to
 * the other sites are accepted. The ratio for that site is accepted/rand_n. The
 * sum of this ratio is what is returned. This can be useful in calculating
 * surface areas or volumes of a group of atoms or molecules. See get_surf_area.
 * @param sites The coordinates of sites in the group / molecule. For example,
 * the carbons in an alkane.
 * @param r The radius to be used in determining the surface area. For example, to
 * determine the SASA use the appropriate radius.
 * @param rand_n The number of randomly generated points to be used for each
 * site.
 * @param box The box dimensions for the frame in question.
 * @param area The total surface area of the group / molecule.
 */

double get_sphere_accept_ratio(vector <coordinates> sites, double r, double rand_n, triclinicbox box);

/** @brief Gets the surface area of a group of atoms.
 * @details Gets the surface area of a group of atoms (could be a molecule)
 * defined by vector of coordinates. Randomly generated points on a sphere of
 * radius r are used at each site in order to get an acceptance ratio. The
 * surface area contributed from each site is simply the surface area of a
 * sphere multiplied by the acceptance ratio for that site. The total surface
 * area is the sum of the surface areas for each site.
 * @param sites The coordinates of sites in the group / molecule. For example,
 * the carbons in an alkane.
 * @param r The radius to be used in determining the surface area. For example, to
 * determine the SASA use the appropriate radius.
 * @param rand_n The number of randomly generated points to be used for each
 * site.
 * @param box The box dimensions for the frame in question.
 * @param area The total surface area of the group / molecule.
 */
double get_surf_area(vector <coordinates> sites, double r, double rand_n, triclinicbox box);

#endif
