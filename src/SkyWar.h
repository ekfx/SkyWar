#ifndef SKYWAR_H
#define SKYWAR_H

#include "Program.h"

constexpr int ENTITIES_MAX = 4; // 5 of each type
constexpr int PARTICLES_MAX = 512; // 5 of each type
constexpr float VELOCITY_INCREMENT = 4.5f;
constexpr float ANGLE_INCREMENT = 120.125f;
constexpr float PARTICLE_INCREMENT = 1.01f;

class SkyWar : public Program {
private:
    //////////////////////////////////////////////////////////////////////
    // Logic
    //////////////////////////////////////////////////////////////////////

    /*
        ECS 
        Entity-Component-System

        A system that runs at unknown data at a known strcture;
        Like:
        We have a Ship -> have a structure;
        We have a structure -> position, matrix and angle
        We need to move that data, but we dont need to know
        what and where this data is from; so:
        structured data Ship 
        structured treatment function
    */

    struct Ship {  
        // Generic Struct for a Ship, that handles position, matrix
        // and others. 
        glm::mat4 mat{ glm::mat4(1.0f) };
        glm::vec3 pos{ glm::vec3(1.0f) };
        f32       degInc{};
        f32       velInc{};
        i8        life{100};
        bool      active;
    };

    struct Dot {
        // Class for bullets: just a white dot in the shader with blur and
        // ray.
        glm::vec3 dirVec{ glm::vec3(1.0f) }; // -> direction vector;
        bool            active{0};
    };

    /*
        To calculate the direction, thinks that we have our player, tha
        player is something like X(1) and Y(1), you know that is a position
        and is a information that every enemie wants to throw a bullet. with
        the position of our player and the position of our enemie, we can 
        trace a line and get a vector, with that we can extract the angle, rotate
        and then fire the gun of the enemie.
    */

    Texture Background;
    std::vector<Dot> Particles;
    std::vector<Ship> Entities; // a object inside is managed by its index.
    std::pair<Texture, i32> PlayerShip; 

    // I think it's better have just one object to texture
    // than have multiple GLuint to just one Texture.
    // even that needs to bind every texture one by one
    std::pair<Texture, std::vector<i32>> BossShip; // -> SmallShip
    std::pair<Texture, std::vector<i32>> BigShip; // -> SmallShip
    std::pair<Texture, std::vector<i32>> MediumShip; // -> SmallShip
    std::pair<Texture, std::vector<i32>> SmallShip; // -> SmallShip

    i32 SetUpIndex(std::pair<Texture, std::vector<i32>>& ship_target, const i32& current_index) {
        i32 j;
        for (i32 i = 0; i <= ENTITIES_MAX; i++) {
            ship_target.second.push_back(current_index + i);
            j = current_index + i;
        }
        return j++;
    }

    void RotateMatrix(const i32& index, std::vector<Ship>& ship_target, const f32& degrees) {
        ship_target.at(index).mat = glm::rotate(ship_target.at(index).mat, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void RotateMatrix(Ship& ship_target, const f32& degrees) {
        ship_target.mat = glm::rotate(ship_target.mat, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void TranslateMatrix(const i32& index, std::vector<Ship>& ship_target, const i32& axis, const f32& inc) {
        if (axis == ENGINE::AXIS::X_AXIS) {
            ship_target.at(index).mat = glm::translate(ship_target.at(index).mat, glm::vec3(inc, 0.0f, 0.0f));
        } else if (axis == ENGINE::AXIS::Y_AXIS) {
            ship_target.at(index).mat = glm::translate(ship_target.at(index).mat, glm::vec3(0.0f, inc, 0.0f));
        }
    }

    void TranslateMatrix(Ship& ship_target, const glm::vec3& increment_vec) {
            ship_target.mat = glm::translate(ship_target.mat, increment_vec);
    }

    void ScaleMatrix(const i32& index, std::vector<Ship>& ship_target, const glm::vec3& scale) {
        ship_target.at(index).mat = glm::scale(ship_target.at(index).mat, scale);
    }

    void ScaleMatrix(Ship& ship_target, const glm::vec3& scale) {
            ship_target.mat = glm::scale(ship_target.mat, scale);
    }

    void ScaleMatrix(std::vector<Ship>& ship_target, const glm::vec3& scale) {
        for (auto& member : ship_target) {
            member.mat = glm::scale(member.mat, scale);
        }    
    }

    i32 GetUnactiveParticleID(std::vector<Dot> particle_list) {
        i32 i = 0;
        for (const auto& member : particle_list) {
            if (!member.active) return i;
            i++;
        }
        return 0; // error, but is better get back to first position than return size
    }

    void Shoot(const Ship& origin, std::vector<Dot>& particle_list) {
        const auto& id = GetUnactiveParticleID(particle_list);
        //particle_list.at(id).dirVec = glm::vec3(origin.mat[3][0], origin.mat[3][1], 0.0f);
        
        particle_list.at(id).dirVec = glm::vec3(origin.mat[3][0], origin.mat[3][1], 0.0f) * GetWindowAspectRatio() * 2.125f;
        // particle_list.at(id).dirVec += glm::vec3(origin.velInc * tan(origin.degInc), origin.velInc, 0.0f);
        particle_list.at(id).active = true;
    }

    //////////////////////////////////////////////////////////////////////
    // Graphics
    //////////////////////////////////////////////////////////////////////

    Shader GlobalShader;
    Mesh   GlobalMesh;

    // Vertex
    u32 DefaultElements[6] {
        0, 1, 2,
        2, 3, 0,
    };

    // Default Vertex
    Mesh::vertex DefaultVertex[4] {         // Padrão
        // X      Y       Z  |  R      G     B  |    U     V
        {-0.50f, -0.50f,  0.0f, 1.0f,  1.0f,  0.0f,  0.00f, 0.00f}, // bottom left
        { 0.50f, -0.50f,  0.0f, 0.0f,  0.85f, 0.0f,  1.00f, 0.00f}, // bottom right
        { 0.50f,  0.50f,  0.0f, 0.85f, 0.0f,  0.0f,  1.00f, 1.00f},  // top right
        {-0.50f,  0.50f,  0.0f, 0.0f,  0.0f,  0.85f, 0.00f, 1.00f}, // top left 
    };

public:

    bool StartMenu();
    void InitEnvironment();                         // Inicia o ambiente com COnfiguracoes personalziadas
    void Initialize();                              // inicializa RECURSOS
    void Input(GLFWwindow* window, f32 Delta);    // Entrada do jogador
    void ProcessPhysics(f32 Delta);               // processa fisica
    void Processing();                              // processamento
    void Render();                                  // render
    void Release();                                 // Deletes
};

#endif // SKYWAR_H
