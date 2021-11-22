#ifndef DEBUG_C_INCLUDED
#define DEBUG_C_INCLUDED

#define DEBUG_C_ON 1
//1 para depurar, 0 para não depurar.
    #if defined DEBUG_C_ON && DEBUG_C_ON == 1
        #define debug(x) {printf(x);}
        #define debugf(x) { x; }
    #else
        #define debug(x) {}
        #define debugf(x) {}
    #endif
#endif