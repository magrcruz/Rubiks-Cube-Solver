//https://github.com/clifordjoshy/thistlethwaite-rubiks
#include "rubiks.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
using namespace std;
Color getColor(char c){
    switch(c){
        case 'W': return WHITE;
        case 'Y': return YELLOW;
        case 'B': return BLUE;
        case 'G': return GREEN;
        case 'R': return RED;
        case 'O': return ORANGE; 
    }
    exit(0);
}

char getColorCharacter(int c){
    switch(c){
        case WHITE: return 'W';
        case YELLOW: return 'Y';
        case BLUE: return 'B';
        case GREEN: return 'G';
        case RED: return 'R';
        case ORANGE: return 'O'; 
    }
    exit(0);
}

std::string getMoveString(const Move &m){
    switch(m){
        case U: return "U";
        case D: return "D";
        case F: return "F";
        case B: return "B";
        case L: return "L";
        case R: return "R";
        case U2: return "U2";
        case D2: return "D2";
        case F2: return "F2";
        case B2: return "B2";
        case L2: return "L2";
        case R2: return "R2";
    }
    return "";
}

std::string optimiseMoveString(std::string &moveString){
    int mStart = 0;
    std::string movePrev, optimised;

    for(int i = 0; i < moveString.size(); ++i){
        if(moveString[i] == ' '){
            auto moveCurrent = moveString.substr(mStart, i - mStart);

            if(movePrev[0] == moveCurrent[0]){
                movePrev.clear();

                if(moveCurrent[1] == '2' || movePrev[1] == '2'){
                    optimised.push_back(moveCurrent[0]);
                    optimised += "\' ";    //L L2 become L'
                } else {
                    movePrev.push_back(moveCurrent[0]);
                    movePrev += "2 ";    //L L becomes L2
                }                
            
            } else {
                optimised += movePrev;
                movePrev = moveCurrent + ' ';
            }

            mStart = i + 1;
        }
    }

    return optimised + movePrev;
}

std::string getMoveListString(const std::vector<Move> &moveList){
    std::string moveSequenceString;

    for(auto &m : moveList){
        moveSequenceString += getMoveString(m)+' ';
    }
    return moveSequenceString;
}

void readData(FaceArray &faces, Color centres[], string str){
    cout << "Entrada: " << str << endl;
    int i, j;
    //std::cout<<"Type faces UDFBLR\n";
    for(i = 0; i < 6; ++i){
        string c = str.substr(i*9,9);
        //std::cin>>c[0]>>c[1]>>c[2]>>c[3]>>c[4]>>c[5]>>c[6]>>c[7]>>c[8];
        faces[i] <<= 4;
        faces[i] |= getColor(c[0]);
        faces[i] <<= 4;
        faces[i] |= getColor(c[1]);
        faces[i] <<= 4;
        faces[i] |= getColor(c[2]);
        faces[i] <<= 4;
        faces[i] |= getColor(c[5]);
        faces[i] <<= 4;
        faces[i] |= getColor(c[8]);
        faces[i] <<= 4;
        faces[i] |= getColor(c[7]);
        faces[i] <<= 4;
        faces[i] |= getColor(c[6]);
        faces[i] <<= 4;
        faces[i] |= getColor(c[3]);

        centres[i] = getColor(c[4]);
    }
}

void printCube(const FaceArray &faces, Color centres[]){
    std::cout<<std::endl;
    std::cout<<"-----Printing Cube-----"<<std::endl;
    for(int i = 0; i < 6; ++i){
        char c[9];
        uint_fast32_t face = faces[i];
        
        c[3] = getColorCharacter(face & 0xF);
        face = face>>4;
        c[6] = getColorCharacter(face & 0xF);
        face = face>>4;
        c[7] = getColorCharacter(face & 0xF);
        face = face>>4;
        c[8] = getColorCharacter(face & 0xF);
        face = face>>4;
        c[5] = getColorCharacter(face & 0xF);
        face = face>>4;
        c[2] = getColorCharacter(face & 0xF);
        face = face>>4;
        c[1] = getColorCharacter(face & 0xF);
        face = face>>4;
        c[0] = getColorCharacter(face & 0xF);
        c[4] = getColorCharacter(centres[i]);

        for(int j = 0; j < 9; ++j)
            std::cout<<c[j];

        std::cout<<std::endl;
    }
    std::cout<<"-----------------------"<<std::endl;
}

string solver(string estado){
    permutations.clear();
    FaceArray faces{0, 0, 0, 0, 0, 0};
    Color centres[6];  //U, D, F, B, L, R
    
    readData(faces, centres, estado);

    std::cout<<"Initialising..";
    initialiseSolver(centres);

    printCube(faces, centres);

    std::string moveString;

    auto moves = getStage1Moves(faces, centres);
    auto stageString = getMoveListString(moves);
    std::cout<<"Stage 1 Moves: "<<stageString;
    doMoveList(faces, moves);
    moveString += stageString;

    //printCube(faces, centres);

    moves = getStage2Moves(faces, centres);
    stageString = getMoveListString(moves);
    std::cout<<"Stage 2 Moves: "<<stageString;
    doMoveList(faces, moves);
    moveString += stageString;

    //printCube(faces, centres);

    moves = getStage3Moves(faces, centres);
    stageString = getMoveListString(moves);
    std::cout<<"Stage 3 Moves: "<<stageString;
    doMoveList(faces, moves);
    moveString += stageString;

    //printCube(faces, centres);

    moves = getStage4Moves(faces, centres);
    stageString = getMoveListString(moves);
    std::cout<<"Stage 4 Moves: "<<stageString;
    doMoveList(faces, moves);
    moveString += stageString;

    std::cout<<"\n\nSolution: "<<moveString<<std::endl;

    return moveString;
}
