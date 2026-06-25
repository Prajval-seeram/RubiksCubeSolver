#include <iostream>
#include <iomanip>
#include <chrono>

#include "solver/Solver.h"
#include "utils/Scrambler.h"

using namespace std;

int main()
{
    Solver solver;
    Scrambler scrambler;

    cout << "\n=========================================\n";
    cout << " RUBIK'S CUBE SOLVER BENCHMARK\n";
    cout << "=========================================\n\n";

    const int testsPerDepth = 10;

    for (int depth = 11; depth <= 13; depth++)
    {
        cout << "#########################################\n";
        cout << "SCRAMBLE LENGTH = " << depth << "\n";
        cout << "#########################################\n\n";

        long long totalTime = 0;
        long long totalNodes = 0;
        long long totalSolutionLength = 0;
        int solved = 0;

        long long bestTime = LLONG_MAX;
        long long worstTime = 0;

        for (int test = 1; test <= testsPerDepth; test++)
        {
            Cube cube;

            vector<Move> scramble =
                scrambler.generateScramble(depth);

            for (Move m : scramble)
                cube.applyMove(m);

            SolveResult result =
                solver.solve(cube);

            cout << "Test "
                 << setw(2) << test
                 << " | ";

            if(result.solved)
            {
                solved++;

                totalTime += result.solveTimeMs;
                totalNodes += result.nodesExpanded;
                totalSolutionLength += result.solution.size();

                bestTime =
                    min(bestTime,
                        result.solveTimeMs);

                worstTime =
                    max(worstTime,
                        result.solveTimeMs);

                cout
                    << "Time = "
                    << setw(6)
                    << result.solveTimeMs
                    << " ms   ";

                cout
                    << "Nodes = "
                    << setw(10)
                    << result.nodesExpanded
                    << "   ";

                cout
                    << "Len = "
                    << result.solution.size();
            }
            else
            {
                cout << "FAILED";
            }

            cout << endl;
        }

        cout << "\n------------- SUMMARY -------------\n";

        cout
            << "Solved            : "
            << solved
            << "/"
            << testsPerDepth
            << endl;

        if(solved)
        {
            cout
                << "Average Time      : "
                << totalTime / solved
                << " ms\n";

            cout
                << "Best Time         : "
                << bestTime
                << " ms\n";

            cout
                << "Worst Time        : "
                << worstTime
                << " ms\n";

            cout
                << "Average Nodes     : "
                << totalNodes / solved
                << endl;

            cout
                << "Average Sol Length: "
                << fixed
                << setprecision(2)
                << (double)totalSolutionLength / solved
                << endl;
        }

        cout << "\n\n";
    }

    return 0;
}