#include <SDL.h>
#include "../Defines.h"

#include "Cannon.h"

Cannon::Cannon() {
    shape.h = shape.w = 50;
    shape.x = SCREEN_WIDTH - shape.w / 2;
    shape.y = SCREEN_HEIGHT / 2 - shape.h / 2;

    balls.clear();
    color = Color(15, 24, 211, 150);
}

void Cannon::shoot(int x, int y) {
    x -= SCREEN_WIDTH; y -= SCREEN_HEIGHT / 2;

    Ball *newBall = new Ball(SCREEN_WIDTH - 50 / 2, SCREEN_HEIGHT / 2 - 50 / 2);

    double tt = double(newBall->getSpeed()) / sqrt(x*x + y*y);
    newBall->update_velocity(tt * x, tt * y);

    //newBall->update_velocity(5, 8);

    balls.push_back(newBall);
    //printf("%d\n", balls.size());
}

void Cannon::update() {
    for (int i = 0; i < balls.size(); i++) {
        if (balls[i] == 0) continue;
        balls[i]->update();
        //printf("%d\n", balls[i]->touchedWall);
        if (balls[i]->touchedWall == 4) balls[i] = NULL;
    }
}

void Cannon::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &shape);

    //printf("%d\n", balls.size());
    for (Ball *ball : balls) {
        //printf("h");
        if (ball == NULL) continue;
        ball->draw(renderer);
    }
}