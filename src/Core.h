#ifndef CORE_H
#define CORE_H

namespace ENGINE {
    namespace AXIS {
        constexpr int X_AXIS                    = 1;
        constexpr int Y_AXIS                    = 2;
        constexpr int Z_AXIS                    = 3;
        constexpr int W_AXIS                    = 4;
    }       

    namespace DIRECTION {       
        constexpr int FORWARD                   = 1;
        constexpr int BACKWARD                  = -1;
        constexpr int NOTHING                   = 0;
    }       

    namespace CAMERA {      
        constexpr int ORTHOGRAPHIC              = 1;
        constexpr int PERSPECTIVE               = 2;
    }       

    namespace WINDOW {      
        // Window Mode      
        constexpr int BORDERLESS                = 0;
        constexpr int FULLSCREEN                = 1;
        constexpr int WINDOWED                  = 2;

        // Background Color
        constexpr int RED_BACKGROUND            = 1;
        constexpr int BLUE_BACKGROUND           = 2;
        constexpr int GREEN_BACKGROUND          = 3;
        constexpr int BLACK_BACKGROUND          = 4;
        constexpr int WHITE_BACKGROUND          = 5;
        constexpr int GRAY_BACKGROUND           = 6;
        constexpr int GRAY_WHITE_BACKGROUND     = 7;
        constexpr int GRAY_BLACK_BACKGROUND     = 8;
        constexpr int PURPLE_BACKGROUND         = 9;
        constexpr int YELLOW_BACKGROUND         = 10;
    }

    namespace PHYSICS {
        constexpr float GRAVITY_ACCELERATION    = 9.81f; 
        constexpr float GRAVITY_ACCELERATION_8X = GRAVITY_ACCELERATION*8;  
    }

    namespace SHADER {
        constexpr int MATRIX_4                  = 0;
        constexpr int MATRIX_3                  = 1;
        constexpr int VECTOR_2                  = 2;
        constexpr int VECTOR_3                  = 3;
        constexpr int VECTOR_4                  = 4;
        constexpr int SIMPLE_VALUE              = 5;
    }
}

#endif // CORE_H