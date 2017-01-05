/**********


Triangle subdivision - http://stackoverflow.com/questions/26790422/recursive-subdivision-on-octahedron-in-opengl
Add each triangle at bottom of recursion to vector
Copy vector into another vector, removing duplicate vertices
Read through first vector, look up its index in reduced vector to create index array
using reduced vector and index array, create VBO, VAO, and EBO

**********/