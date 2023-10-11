#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

#define NUMBER_COL 4
#define NUMBER_OBJ 3

#define BUNNY_MESH "bunny"
#define ARCHER_MESH "archer"
#define TEAPOT_MESH "teapot"

#define BUNNY_DIM 0.3f
#define ARCHER_DIM 0.01f
#define TEAPOT_DIM 2.0f

#define DY_PRESS_DIST 0.05f
#define DX_PRESS_DIST 0.05f
#define DZ_PRESS_DIST 0.05f

#define BOX_MAX_DY 1.f

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1()
{
    // TODO(student): Never forget to initialize class variables!
    changeClearColour();
    changeObject();
}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.
    {
        Mesh* box = new Mesh("box");
        box->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[box->GetMeshID()] = box;

        Mesh* bunnyMesh = new Mesh("bunny");
        bunnyMesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "animals"), "bunny.obj");
        meshes[BUNNY_MESH] = bunnyMesh;

        Mesh* archerMesh = new Mesh("archer");
        archerMesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Characters\\Archer"), "Archer.fbx");
        meshes[ARCHER_MESH] = archerMesh;

        Mesh* teapotMesh = new Mesh("teapot");
        teapotMesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Primitives"), "teapot.obj");
        meshes[TEAPOT_MESH] = teapotMesh;

        _color = 0;
        _object = 0;
        dx = 0.f;
        dy = 0.f;
        dz = 0.f;
        _obj_str = BUNNY_MESH;
        _obj_dim = BUNNY_DIM;
        boxDY = 0.f;
        box_jumping = false;
    }

    // TODO(student): Load some more meshes. The value of RESOURCE_PATH::MODELS
    // is actually a path on disk, go there and you will find more meshes.

}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    if (box_jumping) {
        boxDY += 0.1f;
        if (boxDY >= BOX_MAX_DY) {
            box_jumping = false;
        }
    } else {
        if (boxDY > 0) {
            boxDY -= 0.1f;
        }
    }

    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    glClearColor(red, green, blue, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object
    RenderMesh(meshes["box"], glm::vec3(1, boxDY, 0), glm::vec3(0.5f));

    //// Render the object again but with different properties
    //RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

    // Render the object
    RenderMesh(meshes[_obj_str], glm::vec3(dx, dy, dz), glm::vec3(_obj_dim));

    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.
}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // TODO(student): Add some key hold events that will let you move
    
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.
    
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {

        if (window->KeyHold(GLFW_KEY_W)) {
            dy += DY_PRESS_DIST;
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            dy -= DY_PRESS_DIST;
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            dx -= DX_PRESS_DIST;
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            dx += DX_PRESS_DIST;
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            dz -= DZ_PRESS_DIST;
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            dz += DZ_PRESS_DIST;
        }

    }
}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_F) {
        // TODO(student): Change the values of the color components.
        _color = (_color + 1);

        _color >= NUMBER_COL ? _color = 0 : _color;

        changeClearColour();
    }

    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.
    if (key == GLFW_KEY_G) {
        _object = (_object + 1);

        _object >= NUMBER_OBJ ? _object = 0 : _object;

        changeObject();
    }

    if (key == GLFW_KEY_H) {
        box_jumping = true;
    }

}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}


void Lab1::changeObject()
{
    switch (_object)
    {
    case 1:
        _obj_str = ARCHER_MESH;
        _obj_dim = ARCHER_DIM;
        break;

    case 2:
        _obj_str = TEAPOT_MESH;
        _obj_dim = TEAPOT_DIM;
        break;

    default:
        _obj_str = BUNNY_MESH;
        _obj_dim = BUNNY_DIM;
        break;
    }
}

void Lab1::changeClearColour()
{
	switch (_color)
	    {
	    case 1:
		    red	= 0.100f;
		    green	= 0.05f;
		    blue	= 0.200f;
		    break;
	
	    case 2:
		    red	= 0.120f;
		    green	= 0.08f;
		    blue	= 0.400f;
		    break;
	
	    case 3:
		    red	= 0.180f;
		    green	= 0.3f;
		    blue	= 0.6f;
		    break;

	    default:
		    red	= 0.f;
		    green	= 0.f;
		    blue	= 0.f;
		    break;
	    }
}
