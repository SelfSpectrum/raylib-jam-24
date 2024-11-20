#ifndef GAME_H
#define GAME_H

#include "../../raylib/src/raylib.h"

#if defined(PLATFORM_WEB)
    #define CUSTOM_MODAL_DIALOGS       // Force custom modal dialogs usage
    #include <emscripten/emscripten.h> // Emscripten library - LLVM to JavaScript compiler
#endif

#include <stdio.h>  // Required for: sprintf()
#include <stdlib.h> // Required for:
#include <string.h> // Required for: strcpy()
#include <math.h> // Required for: atan()

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
#define TEX_SIZE 4
#define OBJ_SIZE 5

// TODO: Define your custom data types here

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum GameScreen
{ 
    SCREEN_LOGO_BLINK = 0,
    SCREEN_LOGO_LEFT_TOP = 1,
    SCREEN_LOGO_RIGHT_BOTTOM = 2,
    SCREEN_LOGO_LETTER = 3,
    SCREEN_LOGO_CROMABER = 4,
    SCREEN_TITLE = 5,
    SCREEN_BRIEF = 6,
    SCREEN_ROOM = 7,
    SCREEN_CEILING = 8,
    SCREEN_RADIO = 9,
    SCREEN_CONTROL_PANEL = 10,
    SCREEN_ENDING = 11
} GameScreen;
typedef enum ButtonState
{
    BUTTONSTATE_INVALID = 0,
    BUTTONSTATE_OFF = 1,
    BUTTONSTATE_HOVER = 2,
    BUTTONSTATE_PRESS = 3
} ButtonState;

typedef struct Sprite
{
    int textureIndex; // Índice de la textura en el array del estado para extraer el sprite
    Rectangle source; // Origen del sprite dentro de la textura
    Rectangle dest; // Rectángulo de destino, que establece posición y escala del sprite
    Vector2 origin; // Posición del pivote en la textura
    float rotation; // Rotacion aplicada a la textura respecto al pivote
} Sprite;
typedef struct Interactuable
{
    Sprite sprite; // Sprite del objeto interactuable
    Sprite spriteOn; // Sprite del objeto interactuable
    ButtonState state; // Si es que este es un objeto válido para dibujar e interactuar, Si es que el cursor está flotando por encima del objeto, Si el cursor está presionando el botón
} Interactuable;
typedef struct StateData
{
    GameScreen screen;
    // Muy útil para la animación del logo
    int logoPositionX;
    int logoPositionY;
    int framesCounter; // Contador de frames, útil para cosas temporizadas
    int letterCount; // Contador de letras, útil para presentar cosas letra a letra
    Rectangle sideRect; 
    // Útil para el juego en general
    Texture textures[TEX_SIZE]; // Texturas
    Interactuable interactuable[OBJ_SIZE];
    Sprite bg; // Sprite para usar de fondo
    Color bgColor;
    int wall; // Pared la que se está viendo en cada momento
    Vector2 mousePos; // Posición del cursor
    // Debug
    char screenId[64]; 
} StateData;

StateData LoadState(void);
void UnloadState(StateData *state);
void ChangeSelection(StateData *state);
void ChangeScreen(StateData *state, GameScreen screen);
void UpdateState(StateData *state);
void UpdateInteractuable(StateData *state);
void DrawState(StateData *state);
void DrawInteractuable(StateData *state);
float HeavisideEasing(float value, float step);

#endif
