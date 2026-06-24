#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "AnimationController.h"
#include "Button.h"
#include "../solver/SolveResult.h"
#include <string>
#include <vector>

class Visualizer
{
private:
    AnimationController animController;
    SolveResult currentResult;
    std::string appStatus = "Idle";
    std::string scrambleStr = "";
    std::string solutionStr = "";
    std::string inputBuffer = "";
    float currentSpeed = 1.0f;

public:
    void run();
};

#endif