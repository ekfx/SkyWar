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
    std::cout << "PlayerShip: " << index << std::endl;
    index++;

    std::cout << "SmallShip -> " << index << std::endl;
    index = SetUpIndex(SmallShip, index);
    std::cout << "MediumShip -> " << index << std::endl;
    index = SetUpIndex(MediumShip, index);
    std::cout << "BigShip -> " << index << std::endl;
    index = SetUpIndex(BigShip, index);
    std::cout << "bossShip -> " << index << std::endl;
    index = SetUpIndex(BossShip, index);

    PlayerShip.first.CreateBasicTexture(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR, "../assets/playerShip.png", false, false);
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 0);

    BigShip.first.CreateBasicTexture(GL_TEXTURE1, GL_TEXTURE_2D, GL_LINEAR, "../assets/bigShip.png", true, false);
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 1);

    MediumShip.first.CreateBasicTexture(GL_TEXTURE2, GL_TEXTURE_2D, GL_LINEAR, "../assets/mediumShip.png", true, false);
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 2);

    SmallShip.first.CreateBasicTexture(GL_TEXTURE3, GL_TEXTURE_2D, GL_LINEAR, "../assets/smallShip.png", true, false);
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 3);
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

    if (Keyboard::isKeyPressed(GLFW_KEY_SPACE) || Mouse::IsButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        if (_Timer.UpdateTick(_Clock, 320.0f)) {
            const auto& id = GetUnactiveParticleID(Particles);
            Particles.at(id).dirVec = glm::vec3(Entities.at(PlayerShip.second).mat[3][0], Entities.at(PlayerShip.second).mat[3][0], 0.0f);
            Particles.at(id).dirVec = glm::vec3((Entities.at(PlayerShip.second).velInc * tan(Entities.at(PlayerShip.second).degInc), Entities.at(PlayerShip.second).velInc, 0.0f));
            Particles.at(id).active = true;
        }
    }
}

void SkyWar::ProcessPhysics(f32 Delta) 
{
    RotateMatrix(Entities.at(PlayerShip.second), Entities.at(PlayerShip.second).degInc);
    TranslateMatrix(Entities.at(PlayerShip.second), glm::vec3(0.0f, Entities.at(PlayerShip.second).velInc, 0.0f) * Delta);

    // Particles is not specific from a object.
    for (auto& member : Particles) {
        if (member.active) {
            member.dirVec = glm::vec3(member.dirVec) + (PARTICLE_INCREMENT * Delta);
            std::cout << "X: " << member.dirVec.x << "Y: " << member.dirVec.y << std::endl;
        }
    }
}

void SkyWar::Processing() 
{
    _Camera.Reset();
    _Camera.SetProjection(ENGINE::CAMERA::ORTHOGRAPHIC, GetWindowWidth(), GetWindowHeight());
    _Camera.Translate(0.0f, 0.0f, -1.0f);
    // _Camera.Zoom(-0.125f);

    GlobalShader.SetUniform<ENGINE::SHADER::MATRIX_4, glm::mat4>("view", _Camera.GetCameraMat4());
    GlobalShader.SetUniform<ENGINE::SHADER::MATRIX_4, glm::mat4>("projection", _Camera.GetProjectionMat4());
}

void SkyWar::Render() 
{
    GlobalShader.Use();
    GlobalShader.SetUniform<ENGINE::SHADER::VECTOR_2, glm::vec2>("screenRes", glm::vec2(GetWindowWidth(), GetWindowHeight()));
    glBindVertexArray(GlobalMesh.GetVAO());

    // Particles
    for (auto& member : Particles) {
        if (member.active) {
            GlobalShader.SetUniform<ENGINE::SHADER::VECTOR_3, glm::vec3>("particleDot", member.dirVec);
            if ((member.dirVec.x > GetWindowAspectRatio() || member.dirVec.x < -GetWindowAspectRatio()) || (member.dirVec.y > +1.0f || member.dirVec.y < -1.0f)) {
                member.active = false;
            }
        }
    }
    
    glBindTexture(GL_TEXTURE0, PlayerShip.first.GetTextureID());
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 0);
    GlobalShader.SetUniform<ENGINE::SHADER::MATRIX_4, glm::mat4>("model", glm::scale(Entities.at(PlayerShip.second).mat, glm::vec3(0.125f)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE1, BigShip.first.GetTextureID());
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 1);
    for (auto& index : BigShip.second) {
        GlobalShader.SetUniform<ENGINE::SHADER::MATRIX_4, glm::mat4>("model", glm::scale(Entities.at(index).mat, glm::vec3(0.125f)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
        //system("pause");
    }

        glBindTexture(GL_TEXTURE2, MediumShip.first.GetTextureID());
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 2);
    for (auto& index : MediumShip.second) {
        GlobalShader.SetUniform<ENGINE::SHADER::MATRIX_4, glm::mat4>("model", glm::scale(Entities.at(index).mat, glm::vec3(0.125f)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
        //system("pause");
    }

        glBindTexture(GL_TEXTURE3, SmallShip.first.GetTextureID());
    GlobalShader.SetUniform<ENGINE::SHADER::SIMPLE_VALUE, i32>("TexSlot", 3);
    for (auto& index : SmallShip.second) {
        GlobalShader.SetUniform<ENGINE::SHADER::MATRIX_4, glm::mat4>("model", glm::scale(Entities.at(index).mat, glm::vec3(0.125f)));
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
