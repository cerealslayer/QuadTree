# QuadTree

Quad Tree implemantation, Cubes are randomly placed within a quad range, if more than 4 cubes are inside a quad, the tree recursivly splits the quad into 4 equal quads untill less than 4 cubes exist in each quad. This type of algorithem would be used to cull objects in order to save proccessing power in graphics/video game programming, using this algorithem we would only have to render the quads (and the objects within) that are inside the users/players view frustum instead of having to check each individual object

![Quad](https://user-images.githubusercontent.com/43095260/85777869-adc37a00-b72a-11ea-9a4f-5bdcf6c3e6e3.PNG)
