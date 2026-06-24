#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

#include <vector>
#include "../cube/Cube.h"
#include "../cube/Moves.h"

class AnimationController
{
private:
    std::vector<Move> moves;
    size_t currentIndex = 0;
    float timer = 0.0f;
    float speedMultiplier = 1.0f;
    bool playing = false;

public:
    void start(const std::vector<Move>& moveSequence)
    {
        moves = moveSequence;
        currentIndex = 0;
        timer = 0.0f;
        playing = !moves.empty();
    }

    void stop()
    {
        playing = false;
        currentIndex = 0;
        moves.clear();
    }

    void setSpeed(float speed)
    {
        speedMultiplier = speed;
    }

    bool isPlaying() const
    {
        return playing;
    }

    void update(float dt, Cube& cube)
    {
        if (!playing || currentIndex >= moves.size()) return;

        timer += dt;
        float stepTime = 1.0f / speedMultiplier;

        if (timer >= stepTime)
        {
            cube.applyMove(moves[currentIndex]);
            currentIndex++;
            timer = 0.0f;

            if (currentIndex >= moves.size())
            {
                playing = false;
            }
        }
    }
};

#endif