#pragma once

namespace Core {
namespace Key {
    enum {
        SPACE      = 32,
        ESCAPE     = 256,
        ENTER      = 257,
        TAB        = 258,
        BACKSPACE  = 259,
        INSERT     = 260,
        DELETE     = 261,
        
        RIGHT      = 262,
        LEFT       = 263,
        DOWN       = 264,
        UP         = 265,
        
        A = 65, B, C, D, E, F, G, H, I, J, K, L, M, 
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        
        NUM_0 = 48, NUM_1, NUM_2, NUM_3, NUM_4, 
        NUM_5, NUM_6, NUM_7, NUM_8, NUM_9
    };
}

namespace Mouse {
    enum {
        BUTTON_LEFT   = 0,
        BUTTON_RIGHT  = 1,
        BUTTON_MIDDLE = 2
    };
}
} 
