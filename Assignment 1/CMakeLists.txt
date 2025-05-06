cmake_minimum_required(VERSION 3.20)
project(Assignment1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment1 main.C hit.h material.h ray.h scene_parser.C scene_parser.h object3d.h
        vectors.h matrix.C matrix.h camera.C camera.h sphere.C sphere.h group.C group.h
        image.C image.h)
