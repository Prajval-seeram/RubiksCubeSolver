#include "Renderer.h"

#include "raylib.h"

Color getColor(char c)
{
    switch(c)
    {
        case 'W': return WHITE;
        case 'Y': return YELLOW;
        case 'G': return GREEN;
        case 'B': return BLUE;
        case 'O': return ORANGE;
        case 'R': return RED;

        default: return GRAY;
    }
}

static void drawFace(
    const std::vector<char>& face,
    int startX,
    int startY,
    int size
)
{
    for(int row = 0; row < 3; row++)
    {
        for(int col = 0; col < 3; col++)
        {
            int idx = row * 3 + col;

            DrawRectangle(
                startX + col * size,
                startY + row * size,
                size,
                size,
                getColor(face[idx])
            );

            DrawRectangleLines(
                startX + col * size,
                startY + row * size,
                size,
                size,
                BLACK
            );
        }
    }
}

void Renderer::drawCube(
    const Cube& cube
)
{
    const int s = 40;

    drawFace(
        cube.getUFace(),
        240,
        40,
        s
    );

    drawFace(
        cube.getLFace(),
        120,
        160,
        s
    );

    drawFace(
        cube.getFFace(),
        240,
        160,
        s
    );

    drawFace(
        cube.getRFace(),
        360,
        160,
        s
    );

    drawFace(
        cube.getBFace(),
        480,
        160,
        s
    );

    drawFace(
        cube.getDFace(),
        240,
        280,
        s
    );
}