from __future__ import print_function

import sys
import glob

from vispy import app, visuals, scene
from vispy.scene import ViewBox
from vispy.scene.visuals import Markers, Line, XYZAxis
import vispy

vispy.app.use_app(backend_name="PyQt5", call_reuse=True)
import numpy as np

import mesh_lib


class canvasCreater:
    def load_config(self):
        """
        Reads desired measurements from "config.txt" file.
        Structure described in file
        """
        measurements = []
        with open("config.txt", "r") as f:
            for line in f:
                if line.startswith("#"):
                    continue
                if len(line) < 5:
                    continue
                measurements.append(line.split())
        return measurements

    def debug(self, measurements, file_path, add_geodesic):

        # Model object
        model = mesh_lib.Model(file_path)
        model_point_coordinates = model.get_coords()

        canvas = scene.SceneCanvas(keys='interactive')
        view = canvas.central_widget.add_view()

        # all model - GREEN
        points = Markers(parent=view.scene)
        points.set_data(
            pos=model_point_coordinates,
            edge_color=None,
            face_color=(0, 1, 0, .3),
            size=5
        )

        for m in measurements:  # measurements in config file
            # parsing key vertexes and description text
            point_1 = int(m[1]) + 1
            point_2 = int(m[2]) + 1
            point_3 = int(m[3]) + 1
            text = " ".join(m[4:])

            # coordinates of key vertexes
            key_coords = model.get_coords((point_1, point_2, point_3))
            # plane that goes through all three key vertexes
            plane = mesh_lib.get_plane(key_coords)

            # key vertexes WHITE
            points = Markers()
            points.set_data(
                pos=key_coords,
                edge_color=None,
                face_color=(1, 1, 1, 1),
                size=5
            )

            # "C" - circumference
            if m[0] == "C":
                # 3 segments of path (indexes)
                p_1 = model.get_path(point_1, point_2)
                p_2 = model.get_path(point_2, point_3)
                p_3 = model.get_path(point_3, point_1)
                # full path
                path = p_1 + p_2[1:] + p_3[1:]
            # "L" - Length
            if m[0] == "L":
                # 2 segments of path (indexes)
                p_1 = model.get_path(point_1, point_2)
                p_2 = model.get_path(point_2, point_3)
                # full path
                path = p_1 + p_2[1:]

            # geodesic
            geodesic_coordinates = model.get_coords(path)
            geodesic_length = mesh_lib.get_length(geodesic_coordinates)
            print("{0}:".format(text))
            print(
                "  Geodesic distance: {0} cm".format(
                    round(100 * geodesic_length, 3)
                )
            )
            if add_geodesic:  # if debug_full
                # geodesic line - RED
                line = Line(parent=view.scene)
                line.set_data(
                    pos=geodesic_coordinates,
                    color=(1, 0, 0, 1)
                )

            # approximated
            flattened_coordinates = mesh_lib.get_projections(plane, geodesic_coordinates)
            flattened_length = mesh_lib.get_length(flattened_coordinates)
            print(
                "  Approximated distance: {0} cm".format(
                    round(100 * flattened_length, 3)
                )
            )
            # flattened line - BLUE
            line = Line(parent=view.scene)
            line.set_data(
                pos=flattened_coordinates,
                color=(0, 0, 1, 1)
            )

        view.camera = 'turntable'
        view.camera.fov = 45
        view.camera.distance = 3

        axis = XYZAxis(parent=view.scene)
        return canvas
        # app.run()

    def calculate_all(self, measurements, models_folder, results_folder):  # AAAAAAAllll of this
        # for each *.obj file in models_folder
        for model_path in glob.glob("{0}/*.obj".format(models_folder)):

            # creating model object
            model = mesh_lib.Model(model_path)

            # parsing the filenames
            model_name = model_path.split("\\")[1].split(".")[0]
            results_file = "{0}/{1}.txt".format(results_folder, model_name)

            # forming the results file
            with open(results_file, "w") as fout:

                ### Segment almost identical to debug function

                for m in measurements:

                    point_1 = int(m[1]) + 1
                    point_2 = int(m[2]) + 1
                    point_3 = int(m[3]) + 1
                    text = " ".join(m[4:])

                    key_coords = model.get_coords((point_1, point_2, point_3))
                    plane = mesh_lib.get_plane(key_coords)

                    if m[0] == "C":
                        p_1 = model.get_path(point_1, point_2)
                        p_2 = model.get_path(point_2, point_3)
                        p_3 = model.get_path(point_3, point_1)

                        path = p_1 + p_2[1:] + p_3[1:]

                    if m[0] == "L":
                        p_1 = model.get_path(point_1, point_2)
                        p_2 = model.get_path(point_2, point_3)

                        path = p_1 + p_2[1:]

                    geodesic_coordinates = model.get_coords(path)
                    flattened_coordinates = mesh_lib.get_projections(
                        plane,
                        geodesic_coordinates
                    )
                    flattened_length = mesh_lib.get_length(flattened_coordinates)
                    # output that is going to results file is formed here:
                    output = "{0}: {1} cm.\n".format(text, round(100 * flattened_length, 3))

                    # writing to file
                    fout.write(output)
            # progress displayed by print messages
            print("{0}.txt finished.".format(model_name))


if __name__ == "__main__":

    # getting info from config file
    canvasObj = canvasCreater()
    measurements = canvasObj.load_config()

    # folder names
    m_f = "models"
    r_f = "results"

    # debug or all file calculations
    if len(sys.argv) == 3 and sys.argv[1] == "debug":
        canvasObj.debug(measurements, "{0}/{1}".format(m_f, sys.argv[2]), False)
    elif len(sys.argv) == 3 and sys.argv[1] == "debug_full":
        canvasObj.debug(measurements, "{0}/{1}".format(m_f, sys.argv[2]), True)
    elif len(sys.argv) == 1:
        canvasObj.calculate_all(measurements, m_f, r_f)
    else:
        print("Wrong input format, refer to instruction manual.")

