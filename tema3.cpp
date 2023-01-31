#include "lab_m1/tema3/tema3.h"
#include "lab_m1/tema3/transform3D.h"


#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


tema3::tema3()
{
}


tema3::~tema3()
{
}

void tema3::Init()
{
    cameraP = new implemented::Camera_tema3();
    cameraP->Set(glm::vec3(0, 10, 8), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    projectionP = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    string sourceTexture = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "textures");

    Texture2D* iron = new Texture2D();
    iron->Load2D(PATH_JOIN(sourceTexture, "iron.jpg").c_str(), GL_REPEAT);
    mapTextures["iron"] = iron;

    Texture2D* trunk = new Texture2D();
    trunk->Load2D(PATH_JOIN(sourceTexture, "trunk.jpg").c_str(), GL_REPEAT);
    mapTextures["trunk"] = trunk;

    Texture2D* leaf = new Texture2D();
    leaf->Load2D(PATH_JOIN(sourceTexture, "leaf.jpg").c_str(), GL_REPEAT);
    mapTextures["leaf"] = leaf;

    Texture2D* rock = new Texture2D();
    rock->Load2D(PATH_JOIN(sourceTexture, "rock.jpg").c_str(), GL_REPEAT);
    mapTextures["rock"] = rock;

    Texture2D* snow = new Texture2D();
    snow->Load2D(PATH_JOIN(sourceTexture, "snow.jpg").c_str(), GL_REPEAT);
    mapTextures["snow"] = snow;

    Texture2D* gift = new Texture2D();
    gift->Load2D(PATH_JOIN(sourceTexture, "gift.jpg").c_str(), GL_REPEAT);
    mapTextures["gift"] = gift;

    Texture2D* blue = new Texture2D();
    blue->Load2D(PATH_JOIN(sourceTexture, "blue.jpg").c_str(), GL_REPEAT);
    mapTextures["blue"] = blue;

    Texture2D* green = new Texture2D();
    green->Load2D(PATH_JOIN(sourceTexture, "green.jpg").c_str(), GL_REPEAT);
    mapTextures["green"] = green;


    Mesh* box = new Mesh("box");
    box->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[box->GetMeshID()] = box;

    Mesh* cone = new Mesh("cone");
    cone->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cone.obj");
    meshes[cone->GetMeshID()] = cone;

    Mesh* sphere = new Mesh("sphere");
    sphere->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
    meshes[sphere->GetMeshID()] = sphere;

    Mesh* plane = new Mesh("plane");
    plane->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
    meshes[plane->GetMeshID()] = plane;


    Shader* shader = new Shader("MyShader");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;

    for (int i = 0; i < 50; i++)
    {
        randomObj[i].obj = rand() % objFreq;
        int a = rand() % 40;
        int b = rand() % 40;

        float y = (20 - a) * sin(steep);
        float z = (a - 20) * cos(steep);
        float x = b - 20;
        randomObj[i].poz = glm::vec3(x, y, z);

        if (randomObj[i].obj == 0)
        {
            light_type[i] = 0;
            light_poz[i] = glm::vec3(x, y + 0.5, z);
            light_color[i] = glm::vec3(0, 1, 1);
        }
        else if (randomObj[i].obj == 3)
        {
            light_type[i] = 3;
            light_poz[i] = glm::vec3(x, y + 1, z);
            light_color[i] = glm::vec3(0, 1, 0);
        }
        else if(randomObj[i].obj == 1)
        {
            light_type[i] = 1;
            light_poz[i] = glm::vec3(x - 1.5, y + 4, z);
            light_color[i] = glm::vec3(1, 1, 0.4);
        }
        else
        {
            light_type[i] = -1;
        }
    }
            
}


void tema3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void tema3::PoleMesh(glm::mat4 Model)
{
    glm::mat4 mat = glm::mat4(1);
    mat *= Model;
    mat *= transform3D::Translate(0, 2, 0);
    mat *= transform3D::Scale(0.2, 4, 0.2);
    RenderSimpleMesh(meshes["box"], shaders["MyShader"], mat, mapTextures["iron"]);

    mat = glm::mat4(1);
    mat *= Model;
    mat *= transform3D::Translate(0, 4, 0);
    mat *= transform3D::Scale(2, 0.25, 0.25);
    RenderSimpleMesh(meshes["box"], shaders["MyShader"], mat, mapTextures["iron"]);
}
void tema3::TreeMesh(glm::mat4 Model)
{
    glm::mat4 mat = glm::mat4(1);
    mat *= Model;
    mat *= transform3D::Translate(0, 0.7, 0);
    mat *= transform3D::Scale(0.3, 1.4, 0.3);
    RenderSimpleMesh(meshes["box"], shaders["MyShader"], mat, mapTextures["trunk"]);

    mat = glm::mat4(1);
    mat *= Model;
    mat *= transform3D::Translate(0, 1.6, 0);
    mat *= transform3D::Scale(0.8, 0.8, 0.8);
    RenderSimpleMesh(meshes["cone"], shaders["MyShader"], mat, mapTextures["leaf"]);

    mat = glm::mat4(1);
    mat *= Model;
    mat *= transform3D::Translate(0, 2.1, 0);
    mat *= transform3D::Scale(0.7, 0.7, 0.7);
    RenderSimpleMesh(meshes["cone"], shaders["MyShader"], mat, mapTextures["leaf"]);
}
void tema3::ManMesh(glm::mat4 Model)
{
    glm::mat4 mat = glm::mat4(1);
    mat *= Model;
    mat *= transform3D::Translate(0, 0.71, 0);
    mat *= transform3D::RotateOX(steep);
    mat *= transform3D::RotateOY(3.14 - dir);
    mat *= transform3D::Scale(0.6, 1.4, 0.6);
    RenderSimpleMesh(meshes["box"], shaders["MyShader"], mat, mapTextures["blue"]);

    mat = glm::mat4(1);
    mat *= Model;
    mat *= transform3D::Translate(-0.25, 0.025, 0);
    mat *= transform3D::RotateOX(steep);
    mat *= transform3D::RotateOY(3.14 - dir);
    mat *= transform3D::Scale(0.15, 0.05, 2);
    RenderSimpleMesh(meshes["box"], shaders["MyShader"], mat, mapTextures["green"]);

    mat = glm::mat4(1);
    mat *= Model;
    mat *= transform3D::Translate(0.25, 0.025, 0);
    mat *= transform3D::RotateOX(steep);
    mat *= transform3D::RotateOY(3.14 - dir);
    mat *= transform3D::Scale(0.15, 0.05, 2);
    RenderSimpleMesh(meshes["box"], shaders["MyShader"], mat, mapTextures["green"]);
}
void tema3::RockMesh(glm::mat4 Model)
{
    glm::mat4 mat = glm::mat4(1);
    mat *= Model;
    mat *= transform3D::Translate(0, 0.2, 0);
    mat *= transform3D::Scale(0.8, 0.7, 0.5);
    RenderSimpleMesh(meshes["sphere"], shaders["MyShader"], mat, mapTextures["rock"]);

    mat = glm::mat4(1);
    mat *= Model;
    mat *= transform3D::Translate(0.5, 0.2, 0);
    mat *= transform3D::Scale(0.6, 0.8, 0.7);
    RenderSimpleMesh(meshes["sphere"], shaders["MyShader"], mat, mapTextures["rock"]);
}
void tema3::SnowMesh(glm::mat4 Model)
{
    glm::mat4 mat = glm::mat4(1);
    mat *= Model;
    mat *= transform3D::RotateOX(steep);
    text_rotate = 1;
    RenderSimpleMesh(meshes["plane"], shaders["MyShader"], mat, mapTextures["snow"]);
    text_rotate = 0;
}
void tema3::GiftMesh(glm::mat4 Model)
{
    glm::mat4 mat = glm::mat4(1);
    mat *= Model;
    mat *= transform3D::Translate(0, 0.3, 0);
    mat *= transform3D::RotateOX(steep);
    mat *= transform3D::Scale(0.6, 0.6, 0.6);
    RenderSimpleMesh(meshes["box"], shaders["MyShader"], mat, mapTextures["gift"]);
}
void tema3::RenderScene()
{
    for (int i = 0; i < 50; i++)
    {
        if (distance(randomObj[i].poz, glm::vec3(xMan, yMan, zMan)) > 20)
        {
            int a, b;
            if (rand() % 2)
            {
                a = rand() % 5;
                a += 15;
                if (rand() % 2)
                    a *= -1;
                b = rand() % 20;
                if (rand() % 2)
                    b *= -1;
            }
            else
            {
                b = rand() % 5;
                b += 15;
                if (rand() % 2)
                    b *= -1;
                a = rand() % 20;
                if (rand() % 2)
                    a *= -1;
            }
            float y = yMan + (-1 * a) * sin(steep);
            float z = zMan + a * cos(steep);
            float x = xMan + b;

            randomObj[i].obj = rand() % objFreq;
            randomObj[i].poz = glm::vec3(x, y, z);
            if (randomObj[i].obj == 0)
            {
                light_type[i] = 0;
                light_poz[i] = glm::vec3(x, y + 0.5, z);
                light_color[i] = glm::vec3(0, 1, 1);
            }
            else if (randomObj[i].obj == 3)
            {
                light_type[i] = 3;
                light_poz[i] = glm::vec3(x, y + 1, z);
                light_color[i] = glm::vec3(0, 1, 0);
            }
            else if (randomObj[i].obj == 1)
            {
                light_type[i] = 1;
                light_poz[i] = glm::vec3(x - 1.5, y + 4, z);
                light_color[i] = glm::vec3(1, 1, 0.4);
            }
            else
            {
                light_type[i] = -1;
            }
        }
        else
        {
            glm::vec3 poz = randomObj[i].poz;

            if (randomObj[i].obj == 0)
                GiftMesh(transform3D::Translate(poz.x, poz.y, poz.z));
            if (randomObj[i].obj == 1)
                PoleMesh(transform3D::Translate(poz.x, poz.y, poz.z));
            if (randomObj[i].obj == 2)
                RockMesh(transform3D::Translate(poz.x, poz.y, poz.z));
            if (randomObj[i].obj == 3)
                TreeMesh(transform3D::Translate(poz.x, poz.y, poz.z));
        }
    }
    ManMesh(transform3D::Translate(xMan, yMan, zMan));
    SnowMesh(transform3D::Translate(xMan, yMan, zMan));
}
void tema3::Update(float deltaTimeSeconds)
{
    
    if (start)
    {
        xMan += speed * sin(dir) * deltaTimeSeconds;
        yMan += speed * cos(dir) * deltaTimeSeconds;
        zMan -= speed * cos(dir) * tan(1.57 - steep) * deltaTimeSeconds;

        cameraP->TranslateRight(speed * sin(dir) * deltaTimeSeconds);
        cameraP->TranslateUpward(speed * cos(dir) * deltaTimeSeconds);
        cameraP->MoveForward(speed * cos(dir) * tan(1.57 - steep) * deltaTimeSeconds);

        checkColision();
    }
    RenderScene();
}
void tema3::checkColision()
{
    for (int i = 0; i < 50; i++)
    {
        if (distance(randomObj[i].poz, glm::vec3(xMan, yMan, zMan)) < 0.7)
        {
            if (randomObj[i].obj == 0)
            {
                points++;
                randomObj[i].poz = glm::vec3(0, 0, 100);
            }
            else
            {
                cout << "///////////////////////////\n\n";
                cout << "Points: " << points << "\n\n";
                cout << "///////////////////////////\n\n";
                start = false;
                points = 0;
                randomObj[i].poz = glm::vec3(0, 0, 100);
            }
        }
    }
}


void tema3::FrameEnd()
{
    //DrawCoordinateSystem(cameraP->GetViewMatrix(), projectionP);
}


void tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);

    int loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(cameraP->GetViewMatrix()));

    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionP));

    if (text_rotate == 1)
    {
        int loc_active = glGetUniformLocation(shader->program, "text_rotate");
        glUniform1i(loc_active, 1);
    }
    else
    {
        int loc_active = glGetUniformLocation(shader->program, "text_rotate");
        glUniform1i(loc_active, 0);
    }

    int loc_deltaX = glGetUniformLocation(shader->program, "deltaX");
    glUniform1f(loc_deltaX, xMan/50);
    int loc_deltaY = glGetUniformLocation(shader->program, "deltaY");
    glUniform1f(loc_deltaY, sqrt(yMan*yMan + zMan*zMan)/50);

    if (texture1)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        int loc_tex1 = glGetUniformLocation(shader->program, "texture_1");
        glUniform1i(loc_tex1, 0);
    }
    int loc_ka = glGetUniformLocation(shader->program, "ka");
    glUniform1f(loc_ka, 0.5);
    int loc_kd = glGetUniformLocation(shader->program, "kd");
    glUniform1f(loc_kd, 0.5);
    int loc_ks = glGetUniformLocation(shader->program, "ks");
    glUniform1f(loc_ks, 0.5);
    int loc_shine = glGetUniformLocation(shader->program, "shine");
    glUniform1i(loc_shine, 20);

    int loc_sun = glGetUniformLocation(shader->program, "sun_direction");
    glUniform3f(loc_sun, 0, -1, 0);
    glm::vec3 eyePosition = cameraP->position;
    int loc_eye = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(loc_eye, eyePosition.x, eyePosition.y, eyePosition.z);

    int loc_type = glGetUniformLocation(shader->program, "all_types");
    glUniform1iv(loc_type, 50, light_type);
    int loc_pos = glGetUniformLocation(shader->program, "all_positions");
    glUniform3fv(loc_pos, 50, glm::value_ptr(light_poz[0]));
    int loc_colors = glGetUniformLocation(shader->program, "all_colors");
    glUniform3fv(loc_colors, 50, glm::value_ptr(light_color[0]));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void tema3::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 6.0f;
        if (window->KeyHold(GLFW_KEY_W)) {
            cameraP->MoveForward(deltaTime * cameraSpeed);
        }
        if (window->KeyHold(GLFW_KEY_A)) {
            cameraP->TranslateRight(-deltaTime * cameraSpeed);
        }
        if (window->KeyHold(GLFW_KEY_S)) {
            cameraP->MoveForward(-deltaTime * cameraSpeed);
        }
        if (window->KeyHold(GLFW_KEY_D)) {
            cameraP->TranslateRight(deltaTime * cameraSpeed);
        }
        if (window->KeyHold(GLFW_KEY_Q)) {
            cameraP->TranslateUpward(-deltaTime * cameraSpeed);
        }
        if (window->KeyHold(GLFW_KEY_E)) {
            cameraP->TranslateUpward(deltaTime * cameraSpeed);
        }
    }
    if (window->KeyHold(GLFW_KEY_A)) {
        dir += 1 * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        dir += -1 * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_M)) {
    xMan += speed * sin(dir) * deltaTime;
yMan += speed * cos(dir) * deltaTime;
zMan -= speed * cos(dir) * tan(1.57 - steep) * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_SPACE)) {
        start = true;
    }
}


void tema3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            cameraP->RotateFirstPerson_OX(-sensivityOX * deltaY);
            cameraP->RotateFirstPerson_OY(-sensivityOY * deltaX);
        }
        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            cameraP->RotateThirdPerson_OX(-sensivityOX * deltaY);
            cameraP->RotateThirdPerson_OY(-sensivityOY * deltaX);
        }
    }
    float dX = deltaX;
    dir -= dX / 300;
    if (dir < 1.6)
        dir = 1.6;
    if (dir > 4.6)
        dir = 4.6;
}


void tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void tema3::OnWindowResize(int width, int height)
{
}
