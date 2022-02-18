FDF ("fils de fer" in french - translates to english as "wireframe")

This project is about creating a simplified 3D graphic representation of a relief landscape.

Introduction:

The representation in 3D of a landscape is a critical aspect of modern mapping. For example, in these times of spatial exploration, to have a 3D representation of Mars is a prerequisite condition to its conquest. As another example, comparing various 3D repre- sentations of an area of high tectonic activity will allow you to better understand these phenomena and their evolution, and as a result, be better prepared.

Objectives:

In this project, I discovered the basics of graphic programming, and in particular how to place points in space, how to join them with segments, and most importantly how to observe the scene from a particular viewpoint.
I discovered my first graphic library: miniLibX. This library was developed internally (42) and includes the minimum necessary to open a window, light a pixel and deal with events linked to this window: keyboard and mouse. This project introduced me to “events” programming.

Instructions:

- clone repository recursively:

git clone --recurse-submodules https://github.com/tomkr-01/06_fdf.git

- build

make all

- lauch

./fdf <mapname>.<suffix>

For execution the program requires a text file that contains a map. The map must be properly formatted, as in that it can only contain signed 32-bit integer numbers seperated by spaces and each line must contain the same amount of numbers.

Example:

$>cat 42.fdf
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
$>./fdf 42.txt

!!! still needs screenshot :) !!!