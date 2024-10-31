#ifndef GAME_H
#define GAME_H

#include "../../raylib/src/raylib.h"

#if defined(PLATFORM_WEB)
    #define CUSTOM_MODAL_DIALOGS       // Force custom modal dialogs usage
    #include <emscripten/emscripten.h> // Emscripten library - LLVM to JavaScript compiler
#endif

#include <stdio.h>  // Required for: printf()
#include <stdlib.h> // Required for: 
#include <string.h> // Required for: 

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
// Simple log system to avoid printf() calls if required
// NOTE: Avoiding those calls, also avoids const strings memory usage
#define SUPPORT_LOG_INFO
#if defined(SUPPORT_LOG_INFO)
    #define LOG(...) printf(__VA_ARGS__)
#else
    #define LOG(...)
#endif
#define COLOR_1  CLITERAL(Color){ 132, 208, 125, 255 }
#define COLOR_2  CLITERAL(Color){ 210, 94, 112, 255 }
#define COLOR_3  CLITERAL(Color){ 94, 120, 93, 255 }
#define COLOR_4  CLITERAL(Color){ 155, 8, 19, 255 }
#define COLOR_5  CLITERAL(Color){ 239, 230, 223, 255 }
#define COLOR_6  CLITERAL(Color){ 85, 90, 86, 255 }
#define COLOR_7  CLITERAL(Color){ 62, 73, 67, 255 }
#define COLOR_8  CLITERAL(Color){ 37, 43, 37, 255 }

// TODO: Define your custom data types here

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum { 
    SCREEN_LOGO = 0, 
    SCREEN_TITLE = 1, 
    SCREEN_ROOMFRONT = 2, 
    SCREEN_ROOMLEFT = 3, 
    SCREEN_ROOMRIGHT = 4, 
    SCREEN_ROOMBACK = 5, 
    SCREEN_ROOMTOP = 6, 
    SCREEN_RADIO = 7, 
    SCREEN_CONTROLPANE = 8, 
    SCREEN_ENDING
} GameScreen;

typedef struct SafeTexture {
    Texture2D tex;
    bool init;
} SafeTexture;
typedef struct Sprite {
    int textureIndex; // Índice de la textura en el array del estado para extraer el sprite
    Rectangle source; // Origen del sprite dentro de la textura
    Rectangle dest; // Rectángulo de destino, que establece posición y escala del sprite
    Vector2 origin; // Posición del pivote en la textura
    float rotation; // Rotacion aplicada a la textura respecto al pivote
    bool shader; // ¿Dibujar animable dentro del modo sombreador?
} Sprite;
typedef struct StateData {
    GameScreen screen;
    SafeTexture textures[4];
    Sprite bg; // Sprite para usar de fondo
    int wall;
    bool lookCeil;
    bool onMachine;
} StateData;

StateData LoadState(void);
void UnloadState(StateData *state);
void Menu(StateData *state);
void ChangeSelection(StateData *state);
void ChangeScreen(StateData *state, GameScreen screen);

#endif
