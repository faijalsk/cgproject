2D Shape Transformation GUI
This C++ project provides a GUI-based application for performing basic 2D transformations on geometric shapes (Triangle, Rectangle, Circle) using the BGI graphics library. The application enables users to create shapes and apply translation, rotation, and scaling transformations interactively.

Features
Shape Selection: Choose between Triangle, Rectangle, and Circle.
Input Interface: Intuitive input boxes with cursor and text display for user-friendly input.
Transformations:
Translation: Shift the shape to a new position.
Rotation: Rotate the shape by a specified angle around its center.
Scaling: Resize the shape with independent scaling factors for X and Y axes.
Files
main.cpp: Contains all source code for the GUI and shape transformation functionalities.
Prerequisites
Turbo C++ or equivalent compiler with support for the BGI graphics library.
BGI Graphics Library files (usually graphics.h and associated .lib files).
Compilation Instructions
Ensure Turbo C++ is installed and configured to use the BGI graphics library.
Add graphics.h to your project's include path.
Compile and run the main.cpp file in Turbo C++ or an environment compatible with the BGI library.
Usage
Run the application. The main menu provides the following options:

1. New Shape: Select and enter the coordinates for a Triangle, Rectangle, or Circle.
2. Translate: Enter values to shift the shape along the X and Y axes.
3. Rotate: Specify an angle to rotate the shape around its center.
4. Scale: Enter scaling factors to resize the shape.
5. Exit: Close the application.
Select an option by entering the corresponding number and pressing Enter.

After each transformation, the shape updates to show the result. Press any key to continue after viewing.
