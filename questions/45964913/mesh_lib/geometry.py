# backwards compatibility imports that allow using both python 2 and 3
from __future__ import print_function
from __future__ import division

import numpy as np

def get_plane(coords):
    """
    three reference points points in form
    
    np.array(
    [
      [x_1, y_1, z_1],
      [x_2, y_2, z_2],
      [x_3, y_3, z_3]
    ]
    )
    
    make sure that three points are not in one line
      as this "breaks" math used here.
    """

    # variables expanded
    x_1, y_1, z_1 = coords[0]
    x_2, y_2, z_2 = coords[1]
    x_3, y_3, z_3 = coords[2]
    
    # first we get vectors between points:
    # p_1 to p_2
    r_12 = x_2-x_1, y_2-y_1, z_2-z_1
    # p_1 to p_3
    r_13 = x_3-x_1, y_3-y_1, z_3-z_1

    # Now we compute the normal vector of the plane
    n = (
        r_12[1]*r_13[2] - r_12[2]*r_13[1],
        r_12[2]*r_13[0] - r_12[0]*r_13[2],
        r_12[0]*r_13[1] - r_12[1]*r_13[0],
        )

    # We add values to get plane equation
    plane = (
        n[0],
        n[1],
        n[2],
        n[0]*x_1+n[1]*y_1+n[2]*z_1
        )
    return plane

def get_point_projection(plane, p):
    """
    plane - defined by plane equation parameters
    p - point np.array([x, y, z])
    """
    # plane equation parameters expanded
    a, b, c, d = plane

    # original point coordinates expanded as (x0, y0, z0)
    x0, y0, z0 = p

    # now we need any point on a plane
    # let's denote it (px, py, pz)
    # try/except clauses that take care of potential errors with zero division
    try:
        px, py, pz = 0, 0, d/c
    except ZeroDivisionError:
        try:
            px, py, pz = 0, d/b, 0
        except ZeroDivisionError:
            px, py, pz = d/a, 0, 0

    # parameter t that is intermediate step in calculation of projection
    t = (a*px-a*x0 + b*py-b*y0 + c*pz-c*z0)/(a**2+b**2+c**2)

    # point projected on the plane has coordinates (x, y, z)
    x = x0+t*a
    y = y0+t*b
    z = z0+t*c

    return np.array((x, y, z), dtype=float)

def get_projections(plane, coords):
    """
    plane - defined by plane equation parameters

    coords - array of point coordinates shaped as follows:
    np.array(
        [
            [x_1, y_1, z_1],
            [x_2, y_2, z_2],
            [x_3, y_3, z_3],
            ...
        ]
    )
    """
    projections = np.array(
        list(
            map(
                lambda p: get_point_projection(plane, p),
                coords
                )
            ),
        dtype=float
    )
    return projections

def get_length(coords):
    """
    calculates length of a line connecting all points in:
    coords - points shaped as follows
    np.array(
        [
            [x_1, y_1, z_1],
            [x_2, y_2, z_2],
            [x_3, y_3, z_3]
            ...
        ]
    )
    """
    length = 0
    for i in range(1, coords.shape[0]):
        # coords[i] point i
        # coords[i-1] point i-1

        length += np.linalg.norm(coords[i]-coords[i-1])
    return length


