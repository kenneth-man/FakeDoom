# https://learnopengl.com/

## Graphics pipeline
- ### 2 main parts:
	- ### Transform 3D coordinates into 2D coordinates
	- ### Transform the 2D coordinates into colored pixels

- ### The graphics pipeline has several steps where each step requires the output of the previous step as its input. Graphics cards have many processing cores to quickly process data in parallel within the graphics pipeline. The processing cores run small programs on the GPU for each step of the pipeline. These small programs are called ***shaders***.

- ### Certain shaders are configurable which allows us to write our own shaders. Giving fine-grained control over specific parts of the pipeline and because they run on the GPU, they also save us valuable CPU time. Shaders are written in the ***OpenGL Shading Language (GLSL)***

![](./imgs/graphics%20pipeline.png)

- ### ***Vertex*** = A collection of data per 3D coordinate

- ### ***Fragment*** = All the data that's required for OpenGL to render a single pixel

- ### In modern OpenGL we are required to define these shaders, because there are no defaults
	- ### ***Vertex***
	- ### ***Fragment***

- ### ***Normalized Device Coordinates (NDC)*** = x, y and z values between -1.0 to 1.0. Any coordinates that fall outside this range will be discarded/clipped and won't be visible on your screen

![](./imgs/linking%20vertex%20attributes.png)

### (an ***attribute*** is a input in vertices e.g. positions, colors, normals, texture coordinate etc.)

- ### Vertex Buffer Objects (VBOs):
	- ### VBOs are OpenGL buffer objects that store vertex data, such as vertex positions, colors, normals, and so on.
	- ### They are efficient because they reside in the GPU's memory.
	- ### Using VBOs allows for faster rendering as the data is already on the GPU, reducing the need to send data back and forth between the CPU and GPU.

- ### Vertex Array Objects (VAOs):
	- ### VAOs are OpenGL objects that store multiple VBOs and their associated vertex attribute configurations.
	- ### They allow you to set up and switch between different vertex attribute configurations with a single bind call.
	- ### VAOs remember all the state specified via glVertexAttribPointer and glEnableVertexAttribArray, so you don't need to reissue those calls every time you want to render a different object.
	- ### They help in organizing and encapsulating the vertex attribute configurations for rendering.

- ### Element Buffer Objects (EBOs):
	- ### EBOs are OpenGL buffer objects that store indices that tells OpenGL how to connect the vertices and which vertices to draw.
	- ### They allow you to re-use vertices, which can save memory and reduce the amount of data sent to the GPU.
	- ### They also allow you to draw more complex shapes by reusing vertices.

![](./imgs/element%20buffer%20object.png)

![](./imgs/element%20buffer%20object%202.png)

# Up to here - https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.2.hello_triangle_indexed/hello_triangle_indexed.cpp