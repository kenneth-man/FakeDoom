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