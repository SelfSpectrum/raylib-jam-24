#ifndef GAME_H
#define GAME_H

typedef enum State {
    STATE_MAINMENU = 0,
    STATE_INTRO = 1,
    STATE_ROOMTRANS = 2
};
typedef struct StateData {
    State state;
} StateData;

void ChangeState() {
}

#endif
