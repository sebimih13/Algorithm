# Algorithm

This project was designed to graphically visualize the search for a path in a two-dimensional array using two elementary search algorithms:                
+ BFS (Breadth-First Search)
+ DFS (Depth-First Search)

<br />

The project aims to show the efficiency and complexity of the algorithms, each having advantages and disadvantages depending on the matrix configuration.

<br />

# Technologies used

+	C++
+	OpenGL - [GLFW](https://www.glfw.org/) compiled from source code
+	OpenGL Mathematics - [GLM](https://glm.g-truc.net/0.9.9/index.html)
+	[GLAD](https://glad.dav1d.de/)
+	[FreeType](https://freetype.org/)

<br />

# Symbols

<p align="center">
  <img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/Path.png">
</p>

Symbol  | Description
------------------------------------------------------------------------------------- | -------------
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/Start.PNG">  | Starting point
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/End.PNG">    | Ending point
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/BlackBlock.PNG">  | Square that can be traversed by the algorithm
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/GreenBlock.PNG">  | Square that cannot be traversed by the algorithm
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/RedBlock.PNG">    | This square was traversed by the algorithm to search for the path to the end
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/PinkBlock.PNG">   | The square is part of the path determined by the algorithm

<br />

# Controls

Input  | Description
------------------------------------------------------------------------------------- | -------------
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/MouseLeftKey.png">    | Left click to add a green square or to operate one of the buttons in the program interface 
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/MouseRightKey.png">   | Right click to delete one of the green squares

<br />

# Functionality

The user has to choose one of the two methods to find a path (BFS or DFS) and configure the following parameters: the beginning and the end of the path and the squares that can be traversed by the algorithm. With all this information the algorithm will solve the maze configuration and display to the user the squares traversed to determine the path and the solution found to reach the destination from the starting point. If a path cannot be found, the program will display only the squares traversed.


<br /> <br />
<p align="center">
  <img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/draw.gif">
</p>

<br /> <br />

### BFS                       DFS
<img align="left" src="https://github.com/sebimih13/Algorithm/blob/main/Resource/BFS.gif">
<img align="right" src="https://github.com/sebimih13/Algorithm/blob/main/Resource/DFS.gif">

