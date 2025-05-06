cmake_minimum_required(VERSION 3.20)
project(Assignment2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment2 main.cpp hit.h material.h ray.h scene_parser.cpp scene_parser.h object3d.h
        vectors.h matrix.cpp matrix.h camera.cpp camera.h sphere.cpp sphere.h group.cpp group.h
        image.cpp image.h renderer.cpp renderer.h  plane.cpp plane.h triangle.cpp triangle.h transform.cpp transform.h)
