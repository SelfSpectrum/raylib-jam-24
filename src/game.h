#ifndef GAME_H
#define GAME_H

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct SafeTexture {
    Texture2D tex;
    bool init;
};
struct Sprite {
    int textureIndex; // Índice de la textura en el array del estado para extraer el sprite
    Rectangle source; // Origen del sprite dentro de la textura
    Rectangle dest; // Rectángulo de destino, que establece posición y escala del sprite
    Vector2 origin; // Posición del pivote en la textura
    float rotation; // Rotacion aplicada a la textura respecto al pivote
    bool shader; // ¿Dibujar animable dentro del modo sombreador?
};
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
typedef struct StateData {
    GameScreen screen;
    SafeTexture textures[4];
    Sprite bg; // Sprite para usar de fondo
} StateData;

StateData StartState(void);
void EndState(StateData *state);
void ChangeScreen(StateData *state, GameScreen screen);
void SetBG();

#endif
