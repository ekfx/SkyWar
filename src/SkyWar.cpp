#include "SkyWar.h"

bool SkyWar::StartMenu() {
    return true;
}

void SkyWar::InitEnvironment() 
{
    SetBackgroundColor(ENGINE::WINDOW::BLACK_BACKGROUND);
    SetVSync(false);	
}

void SkyWar::Initialize() 
{
    GlobalShader.CreateBasicShaders("../shaders/shaders.vert", "../shaders/shaders.frag");
    GlobalMesh.CreateMesh(DefaultVertex, sizeof(DefaultVertex), DefaultElements, sizeof(DefaultElements), true, true, false, true);
    
    Particles.reserve(PARTICLES_MAX);
    for (auto i = 0; i < Particles.capacity(); i++) {
        Particles.push_back({});
    }
    
    Entities.reserve(1 + (ENTITIES_MAX * 4)); // adjust the capacity;
    for (auto i = 0; i < Entities.capacity(); i++) {
        Entities.push_back({});
    }
    
    i32 index = 0;   // considering the previous command has been executed successfully
    PlayerShip.second = index;
    index++;
    
    index = SetUpIndex(SmallShip, index);
    index = SetUpIndex(MediumShip, index);
    index = SetUpIndex(BigShip, index);
    index = SetUpIndex(BossShip, index);
    
    PlayerShip.first.CreateBasicTexture(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR, "../assets/playerShip.png", false, false);
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 0);
    
    BigShip.first.CreateBasicTexture(GL_TEXTURE1, GL_TEXTURE_2D, GL_LINEAR, "../assets/bigShip.png", true, false);
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 1);
    
    MediumShip.first.CreateBasicTexture(GL_TEXTURE2, GL_TEXTURE_2D, GL_LINEAR, "../assets/mediumShip.png", true, false);
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 2);
    
    SmallShip.first.CreateBasicTexture(GL_TEXTURE3, GL_TEXTURE_2D, GL_LINEAR, "../assets/smallShip.png", true, false);
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 3);
    
    Background.CreateBasicTexture(GL_TEXTURE4, GL_TEXTURE_2D, GL_LINEAR, "../assets/background_.png", true, false);
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 4);

    ScaleMatrix(Entities, glm::vec3(0.06125f));
}

void SkyWar::Input(GLFWwindow* window, f32 Delta) 
{
    if (Keyboard::isKeyPressed(GLFW_KEY_W)) {
        Entities.at(PlayerShip.second).velInc += ((-VELOCITY_INCREMENT) * Delta);
    } else if (Keyboard::isKeyPressed(GLFW_KEY_S)) {
        Entities.at(PlayerShip.second).velInc += (VELOCITY_INCREMENT * Delta);
    } else {
        //Entities.at(PlayerShip.second).velInc *= (0.99f * Delta);
    }

    if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
        Entities.at(PlayerShip.second).degInc += (ANGLE_INCREMENT * Delta);
    } else if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
        Entities.at(PlayerShip.second).degInc += ((-ANGLE_INCREMENT) * Delta);
    } else {
        Entities.at(PlayerShip.second).degInc *= (0.99f * Delta);
    }

    if (Keyboard::isKeyPressed(GLFW_KEY_SPACE)) {
        if (_Timer.UpdateTick(_Clock, 120.0f)) {
            Shoot(Entities.at(PlayerShip.second), Particles);
        }
    }
}

void SkyWar::ProcessPhysics(f32 Delta) 
{
    RotateMatrix(Entities.at(PlayerShip.second), Entities.at(PlayerShip.second).degInc * Delta);
    TranslateMatrix(Entities.at(PlayerShip.second), glm::vec3(0.0f, Entities.at(PlayerShip.second).velInc, 0.0f) * Delta);

    // Particles is not specific from a object.
    for (auto& member : Particles) {
        if (member.active) {
            // member.dirVec = (glm::vec3(Entities.at(PlayerShip.second).velInc * tan(Entities.at(PlayerShip.second).degInc), Entities.at(PlayerShip.second).velInc, 0.0f)) * (PARTICLE_INCREMENT * Delta);

            // This line gets the exactly player position, already converted with aspect ratio and 2.125f.
            // member.dirVec = glm::vec3(Entities.at(PlayerShip.second).mat[3][0], Entities.at(PlayerShip.second).mat[3][1], 0.0f) * GetWindowAspectRatio() * 2.125f;

            member.dirVec = glm::vec3(member.dirVec) * PARTICLE_INCREMENT;
        }
    }
}

void SkyWar::Processing() 
{
    _Camera.Reset();
    _Camera.SetProjection(ENGINE::CAMERA::ORTHOGRAPHIC, GetWindowWidth(), GetWindowHeight());
    _Camera.Translate(0.0f, 0.0f, -1.0f);
    _Camera.Zoom(4.0f);

    GlobalShader.SetUniform<ENGINE::SHADER::MATRIX_4, glm::mat4>("view", _Camera.GetCameraMat4());
    GlobalShader.SetUniform<ENGINE::SHADER::MATRIX_4, glm::mat4>("projection", _Camera.GetProjectionMat4());
}

void SkyWar::Render() 
{
    GlobalShader.Use();
    GlobalShader.SetUniform<ENGINE::SHADER::VECTOR_2, glm::vec2>("screenRes", glm::vec2(GetWindowWidth(), GetWindowHeight()));
    glBindVertexArray(GlobalMesh.GetVAO());

    glBindTexture(GL_TEXTURE4, Background.GetTextureID());
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 4);
    GlobalShader.SetUniform<ENGINE::SHADER::MATRIX_4, glm::mat4>("model", glm::scale(glm::mat4(1.0f), glm::vec3(10.0)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    // Particles
    size_t activeP = 0;
    for (auto& member : Particles) {
        if (member.active) {
            GlobalShader.SetUniform<ENGINE::SHADER::VECTOR_3, glm::vec3>("particleDot", member.dirVec);
            if ((member.dirVec.x > GetWindowAspectRatio() || member.dirVec.x < -GetWindowAspectRatio()) || (member.dirVec.y > +1.0f || member.dirVec.y < -1.0f)) {
                member.active = false;
            }
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
            std::cout << "\r[" << activeP << "] is activated. Position X" << member.dirVec.x << " - Y: " << member.dirVec.y;
        }
        activeP++;
    }
    
    glBindTexture(GL_TEXTURE0, PlayerShip.first.GetTextureID());
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 0);
    GlobalShader.SetUniform<ENGINE::SHADER::MATRIX_4, glm::mat4>("model", Entities.at(PlayerShip.second).mat);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE1, BigShip.first.GetTextureID());
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 1);
    for (auto& index : BigShip.second) {
        GlobalShader.SetUniform<ENGINE::SHADER::MATRIX_4, glm::mat4>("model", Entities.at(index).mat);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
        //system("pause");
    }

        glBindTexture(GL_TEXTURE2, MediumShip.first.GetTextureID());
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 2);
    for (auto& index : MediumShip.second) {
        GlobalShader.SetUniform<ENGINE::SHADER::MATRIX_4, glm::mat4>("model", Entities.at(index).mat);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
        //system("pause");
    }

        glBindTexture(GL_TEXTURE3, SmallShip.first.GetTextureID());
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 3);
    for (auto& index : SmallShip.second) {
        GlobalShader.SetUniform<ENGINE::SHADER::MATRIX_4, glm::mat4>("model", Entities.at(index).mat);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
        //system("pause");
    }


    // Function for all objects in that vector
    for (auto& member : Entities) {
    }
}

void SkyWar::Release() 
{   
    GlobalMesh.ReleaseBuffers();
    GlobalShader.ReleaseShaders();
    PlayerShip.first.ReleaseTexture();
    BossShip.first.ReleaseTexture();
    BigShip.first.ReleaseTexture();
    MediumShip.first.ReleaseTexture();
    SmallShip.first.ReleaseTexture();
}
