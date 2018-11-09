from __future__ import print_function # backwards compatibility
from __future__ import division

# heap queue data structure from standard python libraries
# used for the search algorithm
import heapq

import numpy as np

def dijkstra(vertexes_dict, start_i, target_i):
    """dijkstra function
    vertexes - vertex data structure
    start_i - index of starting vertex in data structure
    target_i - index of end vertex in data structure
    """
    # forming a data structure for a search
    vertexes = {}
    for v in vertexes_dict:
        vertexes[v] = {
            "dist":float("inf"),
            "vertex":vertexes_dict[v]
            }

    frontier = [] # search frontier

    looked_at = set() # indexes of vertexes that heve been observed

    # frontier is ordered by path length to start vertex i.e. Dijkstra

    # heap queue   frontier  (priority,  index)
    heapq.heappush(frontier, (0, start_i))

    # in data structure distance to start is 0
    vertexes[start_i]["dist"] = 0
    # in data structure path to start is just it's index
    vertexes[start_i]["path"] = [start_i]

    # iterative search from start to target
    while (frontier):

        # getting next vertex from heap queue
        # fisrt argument is priority, we don't need it anymore
        # so it's assigned to variable _ and ignored
        _, v_i = heapq.heappop(frontier)

        # local variable just for cenvenience
        vertex = vertexes[v_i]["vertex"]

        if v_i == target_i: # if we have found the target

            # path length and path is returned
            return vertexes[v_i]["dist"], vertexes[v_i]["path"]

        # if vertex has already been observed we ignore it
        if vertex.index in looked_at:
            continue
        # adding vertex to observed set
        looked_at.add(vertex.index)

        for n in vertex.get_neighbors():
            if n.index in looked_at:
                continue
            new_dist = vertexes[v_i]["dist"]+vertex.get_dist_to(n)
            if new_dist < vertexes[n.index]["dist"]:
                vertexes[n.index]["dist"] = new_dist
                vertexes[n.index]["path"] = vertexes[v_i]["path"] + [n.index]
            
            heapq.heappush(frontier,(new_dist, n.index))

    # if code gets to this place that means no path has been found
    # as this should not happen an error is raised with description
    raise Exception(
        "No path found between vertex: {0} and vertex: {1}".format(
                start_i,
                target_i
            )
        )


# Vertex class
class Vertex(object):
    """
    Vertex class used for one vertex/node in a graph
    contains index, coordinates, and list of neighbor vertexes
    """
    def __init__(self, index, x, y, z):
        """index - integer index of vertex
        x, y, z - float, cartesian coordinates"""
        self.index = index
        self.coords = np.array((x, y, z), dtype=float)
        self.neighbors = []

    def add_neighbors(self, n):
        """method to add neighbors to vertex.
        if graph is undirected neighbor relations
        have to be added to both ends of egde"""

        # if passed value is no Vertex an Error is created
        assert isinstance(n, Vertex)

        # if Vertex is already added as a neighbor
        # if is ignored
        if n not in self.neighbors:

            # neighbor list is appended with new neighbor value
            self.neighbors.append(n)

    def get_coords(self):
        """
        returns np.array([x,y,z]) coordinates of vertex/node
        """
        return self.coords

    def get_neighbors(self):
        """returns all neighbors"""
        for n in self.neighbors:
            yield n

    def get_dist_to(self, b):
        """calculates the linear distance to another Vertex object"""

        # Cartesian distance is calculated
        return np.linalg.norm(self.coords-b.coords)


class Model(object):
    """
    Model class to store *obj file mesh
    """
    def __init__(self, file_path):
        """
        Reads *.obj file and creates Model object
        Model is represented by a dictionary of vertex objects
          with relations with other vertexes via edges.
        Faces not implemented as they are not needed.
        """
        self.vertexes = {}
        # as we read lines we number indexes
        # in *.obj file they are numbered starting at 1
        # so within this code same notation is used
        # onle when the user inputs node numbers they are adjusted to notation
        # from Meshlab
        v_index = 1

        with open(file_path, "r") as fin:

            for line in fin:

                line_list = line.split()
                if len(line_list) == 0:
                    continue
                
                if line_list[0] == "v": # begins with v if describes vertex

                    vertex = Vertex(
                        v_index, # "telling vertex its index"
                        # strings, vertex conderts to float
                        line_list[1], # x
                        line_list[2], # y
                        line_list[3]  # z
                        )
                    self.vertexes[v_index] = vertex # add vertex to dictionary
                    v_index += 1 # index increment

                elif line_list[0] == "f": # begins with f it describes a face
                    a_i = int(line_list[1]) # vertex index 1
                    b_i = int(line_list[2]) # vertex index 2
                    c_i = int(line_list[3]) # vertex index 3

                    a = self.vertexes[a_i] # vertex objcet 1
                    b = self.vertexes[b_i] # vertex objcet 2
                    c = self.vertexes[c_i] # vertex objcet 3

                    # 6 neighbor relations in one triangular face
                    a.add_neighbors(b)
                    a.add_neighbors(c)

                    b.add_neighbors(a)
                    b.add_neighbors(c)

                    c.add_neighbors(a)
                    c.add_neighbors(b)

    def get_coords(self, vertex_list=None):
        """
        If no parameter passed returns coordinates of all vertexes
        if a list of indexes passed then their coordinates returned
        returned values shaped like this
        [
          [x_1, y_1, z_1],
          [x_2, y_2, z_2],
          [x_3, y_3, z_3],
           ...
        ]
        """

        if vertex_list is not None:
            coords = np.empty((len(vertex_list),3), dtype=float)
            for i, vert in enumerate(vertex_list):
                coords[i] = self.vertexes[vert].get_coords()
        else:
            coords = np.empty((len(self),3), dtype=float)
            for i, vert in enumerate(sorted(self.vertexes)):
                coords[i] = self.vertexes[vert].get_coords()
        return coords

    def get_edges(self):
        all_edges = set()

        for vert in self.vertexes:
            v = self.vertexes[vert]

            for e in v.get_neighbors():
                all_edges.add(sorted([v.index, e.index]))

        return np.array(list(all_edges), dtype=int)

    def __len__(self):
        return len(self.vertexes)

    def get_path(self, start_i, end_i):
        """
        returns the indexes of shortest path along the shortest path
        uses Dijkstra algorithm
        """
        _, path = dijkstra(self.vertexes, start_i, end_i)
        return path
