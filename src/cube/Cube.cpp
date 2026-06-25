#include "Cube.h"
#include "Moves.h"
#include <iostream>
#include <algorithm>

using namespace std;

Cube::Cube() { rec = false; reset(); }

void printFace(const char* face)
{
    for (int i = 0; i < 9; i++) {
        cout << face[i] << " ";
        if ((i + 1) % 3 == 0) cout << endl;
    }
}

void Cube::display() const
{
    cout << "\nUP\n"; printFace(U_face);
    cout << "\nDOWN\n"; printFace(D_face);
    cout << "\nFRONT\n"; printFace(F_face);
    cout << "\nBACK\n"; printFace(B_face);
    cout << "\nLEFT\n"; printFace(L_face);
    cout << "\nRIGHT\n"; printFace(R_face);
}

void Cube::rotateFaceClockwise(char face[9])
{
    char temp[9];
    copy(face, face + 9, temp);
    face[0] = temp[6]; face[1] = temp[3]; face[2] = temp[0];
    face[3] = temp[7]; face[4] = temp[4]; face[5] = temp[1];
    face[6] = temp[8]; face[7] = temp[5]; face[8] = temp[2];
}

void Cube::U()
{
    char temp[3] = { F_face[0], F_face[1], F_face[2] };
    F_face[0] = L_face[0]; F_face[1] = L_face[1]; F_face[2] = L_face[2];
    L_face[0] = B_face[0]; L_face[1] = B_face[1]; L_face[2] = B_face[2];
    B_face[0] = R_face[0]; B_face[1] = R_face[1]; B_face[2] = R_face[2];
    R_face[0] = temp[0];   R_face[1] = temp[1];   R_face[2] = temp[2];
    rotateFaceClockwise(U_face);
}
void Cube::Ui() { U(); U(); U(); }
void Cube::U2() { U(); U(); }

void Cube::D()
{
    char temp[3] = { F_face[6], F_face[7], F_face[8] };
    F_face[6] = R_face[6]; F_face[7] = R_face[7]; F_face[8] = R_face[8];
    R_face[6] = B_face[6]; R_face[7] = B_face[7]; R_face[8] = B_face[8];
    B_face[6] = L_face[6]; B_face[7] = L_face[7]; B_face[8] = L_face[8];
    L_face[6] = temp[0];   L_face[7] = temp[1];   L_face[8] = temp[2];
    rotateFaceClockwise(D_face);
}
void Cube::Di() { D(); D(); D(); }
void Cube::D2() { D(); D(); }

void Cube::R()
{
    char temp[3] = { U_face[2], U_face[5], U_face[8] };
    U_face[2] = F_face[2]; U_face[5] = F_face[5]; U_face[8] = F_face[8];
    F_face[2] = D_face[2]; F_face[5] = D_face[5]; F_face[8] = D_face[8];
    D_face[2] = B_face[6]; D_face[5] = B_face[3]; D_face[8] = B_face[0];
    B_face[6] = temp[0];   B_face[3] = temp[1];   B_face[0] = temp[2];
    rotateFaceClockwise(R_face);
}
void Cube::Ri() { R(); R(); R(); }
void Cube::R2() { R(); R(); }

void Cube::L()
{
    char temp[3] = { U_face[0], U_face[3], U_face[6] };
    U_face[0] = B_face[8]; U_face[3] = B_face[5]; U_face[6] = B_face[2];
    B_face[8] = D_face[0]; B_face[5] = D_face[3]; B_face[2] = D_face[6];
    D_face[0] = F_face[0]; D_face[3] = F_face[3]; D_face[6] = F_face[6];
    F_face[0] = temp[0];   F_face[3] = temp[1];   F_face[6] = temp[2];
    rotateFaceClockwise(L_face);
}
void Cube::Li() { L(); L(); L(); }
void Cube::L2() { L(); L(); }

void Cube::F()
{
    char temp[3] = { U_face[6], U_face[7], U_face[8] };
    U_face[6] = L_face[8]; U_face[7] = L_face[5]; U_face[8] = L_face[2];
    L_face[8] = D_face[2]; L_face[5] = D_face[1]; L_face[2] = D_face[0];
    D_face[2] = R_face[0]; D_face[1] = R_face[3]; D_face[0] = R_face[6];
    R_face[0] = temp[0];   R_face[3] = temp[1];   R_face[6] = temp[2];
    rotateFaceClockwise(F_face);
}
void Cube::Fi() { F(); F(); F(); }
void Cube::F2() { F(); F(); }

void Cube::B()
{
    char temp[3] = { U_face[0], U_face[1], U_face[2] };
    U_face[0] = R_face[2]; U_face[1] = R_face[5]; U_face[2] = R_face[8];
    R_face[2] = D_face[8]; R_face[5] = D_face[7]; R_face[8] = D_face[6];
    D_face[8] = L_face[6]; D_face[7] = L_face[3]; D_face[6] = L_face[0];
    L_face[6] = temp[0];   L_face[3] = temp[1];   L_face[0] = temp[2];
    rotateFaceClockwise(B_face);
}
void Cube::Bi() { B(); B(); B(); }
void Cube::B2() { B(); B(); }

bool Cube::isSolved() const
{
    char u = U_face[4], d = D_face[4], f = F_face[4], b = B_face[4], l = L_face[4], r = R_face[4];
    for (int i = 0; i < 9; i++) {
        if (U_face[i] != u || D_face[i] != d || F_face[i] != f ||
            B_face[i] != b || L_face[i] != l || R_face[i] != r) return false;
    }
    return true;
}

void Cube::reset()
{
    fill(U_face, U_face + 9, 'W'); fill(D_face, D_face + 9, 'Y');
    fill(F_face, F_face + 9, 'G'); fill(B_face, B_face + 9, 'B');
    fill(L_face, L_face + 9, 'O'); fill(R_face, R_face + 9, 'R');
    moveHistory.clear();
}

void Cube::applyMove(Move move)
{
    switch (move)
    {
        case Move::U:  U();  break; case Move::Ui: Ui(); break; case Move::U2: U2(); break;
        case Move::D:  D();  break; case Move::Di: Di(); break; case Move::D2: D2(); break;
        case Move::R:  R();  break; case Move::Ri: Ri(); break; case Move::R2: R2(); break;
        case Move::L:  L();  break; case Move::Li: Li(); break; case Move::L2: L2(); break;
        case Move::F:  F();  break; case Move::Fi: Fi(); break; case Move::F2: F2(); break;
        case Move::B:  B();  break; case Move::Bi: Bi(); break; case Move::B2: B2(); break;
    }
    if (rec) moveHistory.push_back(move);
}

const vector<Move>& Cube::getMoveHistory() const { return moveHistory; }

void Cube::printMoveHistory() const
{
    for (Move move : moveHistory) cout << moveToString(move) << " ";
    cout << endl;
}

string Cube::encodeState() const
{
    string state; state.reserve(54);
    for(int i=0; i<9; ++i) state += U_face[i];
    for(int i=0; i<9; ++i) state += D_face[i];
    for(int i=0; i<9; ++i) state += F_face[i];
    for(int i=0; i<9; ++i) state += B_face[i];
    for(int i=0; i<9; ++i) state += L_face[i];
    for(int i=0; i<9; ++i) state += R_face[i];
    return state;
}