#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema3/lab_camera.h"


namespace m1
{
    class tema3 : public gfxc::SimpleScene
    {
     public:
        tema3();
        ~tema3();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void RenderScene();
        void checkColision();
        void PoleMesh(glm::mat4 Model);
        void TreeMesh(glm::mat4 Model);
        void RockMesh(glm::mat4 Model);
        void GiftMesh(glm::mat4 Model);
        void ManMesh(glm::mat4 Model);
        void SnowMesh(glm::mat4 Model);
       
        

     protected:
        implemented::Camera_tema3 *cameraP;
        glm::mat4 projectionP;


        std::unordered_map<std::string, Texture2D*> mapTextures;
        int text_rotate = 0;
        float steep = 0.3;
        float dir = 3.14;
        float speed = 1;
        float xMan=0, yMan=0, zMan=0;
        bool start = false;
        int points = 0;
        
        int objFreq = 4; //lower nr => more frequent
        struct Obj
        {
            int obj;
            glm::vec3 poz;
        }randomObj[50];

        int light_type[50];
        glm::vec3 light_poz[50];
        glm::vec3 light_color[50];
    };
}   // namespace m1
