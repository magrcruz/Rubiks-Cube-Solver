#include <array>
#include <vector>
#include <cstdint>
#include<set>
#include<iostream>

#define F_UP 0
#define F_DOWN 1
#define F_FRONT 2
#define F_BACK 3
#define F_LEFT 4
#define F_RIGHT 5

typedef std::array<uint_fast32_t, 6> FaceArray;

enum Color{WHITE, YELLOW, BLUE, GREEN, RED, ORANGE};

//two non affecting moves are separated by 2 ie U + 2 -> D
//all '2' moves are odd. ie U2 is 1, D2 is 3
//all single moves are even
//NONE for passing to DFS start
enum Move{U = 0, U2 = 1, D = 2, D2 = 3, F = 10, F2 = 11, B = 12, B2 = 13, L = 20, L2 = 21, R = 22, R2 = 23, NONE = 50};

/* rubiks cube should be read as 

            a b c  <--U
            d e f
            g h i
            _____
    a b c | a b c | a b c | a b c
    d e f | d e f | d e f | d e f
    g h i | g h i | g h i | g h i
            _____
            a b c
            d e f
            g h i

*/

/* rubiks cube is stored as 

            0 1 2  <--U
            7   3
            6 5 4
            _____
    0 1 2 | 0 1 2 | 0 1 2 | 0 1 2
    7   3 | 7   3 | 7   3 | 7   3
    6 5 4 | 6 5 4 | 6 5 4 | 6 5 4
            _____
            0 1 2
            7   3
            6 5 4

*/

void doMove(const Move &move, FaceArray &faces);
void doMoveList(FaceArray &faces, const std::vector<Move> &moveList);

void initialiseSolver(const Color centres[6]);

std::vector<Move> getStage1Moves(const FaceArray &faces, const Color centres[6]);
std::vector<Move> getStage2Moves(const FaceArray &faces, const Color centres[6]);
std::vector<Move> getStage3Moves(const FaceArray &faces, const Color centres[6]);
std::vector<Move> getStage4Moves(const FaceArray &faces, const Color centres[6]);

bool isAllEdgesGood(const FaceArray &faces, const Color centres[6]);
bool isStage2Goal(const FaceArray &faces, const Color centres[6]);
bool isStage3Goal(const FaceArray &faces, const Color centres[6]);
bool isSolved(const FaceArray &faces, const Color centres[6]);


std::set<uint_fast64_t> permutations;

bool doDFS(const int searchDepth, std::vector<Move> &moveList, 
        const std::array<Move, 6> &availableMoves, const FaceArray &faces, const Color centres[6], 
        bool (*isStageGoal)(const FaceArray &faces, const Color centres[6]), const Move &lastMove){

    if(searchDepth == 0){
        return false;
    }

    for(auto &m: availableMoves){

        //repeating U2 takes back to base state
        if(lastMove%2 && m == lastMove)    //if its double move and equal to current move
            continue;
        //no need to do after B after F. since F after B will be the same state
        if(m - lastMove == 2)       //if non affecting moves
            continue;
        
        auto facesCopy = faces;

        doMove(m, facesCopy);
        if(isStageGoal(facesCopy, centres)){
            moveList.insert(moveList.begin(), m);
            return true;
        }

        if(doDFS(searchDepth - 1, moveList, availableMoves, facesCopy, centres, isStageGoal, m)){
            moveList.insert(moveList.begin(), m);
            return true;
        }
        
    }

    return false;
}

std::vector<Move> doIDDFS(const std::array<Move, 6> &availableMoves, 
        const FaceArray &faces, const Color centres[6], 
        bool (*isStageGoal)(const FaceArray &faces, const Color centres[6])){

    std::vector<Move> moveList;
    std::cout<<std::endl<<"IDDFS Depth: 1";
    int searchDepth = 1;
    while(!doDFS(searchDepth, moveList, availableMoves, faces, centres, isStageGoal, NONE)){
        ++searchDepth;
        std::cout<<". "<<searchDepth;
    }
    std::cout<<". Complete"<<std::endl;

    return moveList;
}


Color getSquareColor(const FaceArray &faces, int faceIndex, int cubieIndex){
    int shiftBits = 4 * (7 - cubieIndex);
    int cubieColor = (faces[faceIndex]>>shiftBits) & 0xF;
    return static_cast<Color>(cubieColor);
}

//returns the face index for a particular color
int getFace(const Color centres[6], Color faceColor){
    for(int i = 0; i < 6; ++i){
        if(faceColor == centres[i])
            return i;
    }
    return -1;
}

//returns the index of an edge cubie of given face and color
int getEdgeCubieIndex(const Color centres[6], int cubieFaceIndex, const Color &edgeColor){
    switch(cubieFaceIndex){
        case F_FRONT:{
            if(edgeColor == centres[F_UP])
                return 1;
            if(edgeColor == centres[F_RIGHT])
                return 3;
            if(edgeColor == centres[F_DOWN])
                return 5;
            if(edgeColor == centres[F_LEFT])
                return 7;
            break;
        }        
        case F_BACK:{
            if(edgeColor == centres[F_UP])
                return 1;
            if(edgeColor == centres[F_RIGHT])
                return 7;
            if(edgeColor == centres[F_DOWN])
                return 5;
            if(edgeColor == centres[F_LEFT])
                return 3;
            break;
        }        
        case F_UP:{
            if(edgeColor == centres[F_FRONT])
                return 5;
            if(edgeColor == centres[F_RIGHT])
                return 3;
            if(edgeColor == centres[F_BACK])
                return 1;
            if(edgeColor == centres[F_LEFT])
                return 7;
            break;
        }        
        case F_DOWN:{
            if(edgeColor == centres[F_FRONT])
                return 1;
            if(edgeColor == centres[F_RIGHT])
                return 3;
            if(edgeColor == centres[F_BACK])
                return 5;
            if(edgeColor == centres[F_LEFT])
                return 7;
            break;
        }
        case F_LEFT:{
            if(edgeColor == centres[F_UP])
                return 1;
            if(edgeColor == centres[F_BACK])
                return 7;
            if(edgeColor == centres[F_DOWN])
                return 5;
            if(edgeColor == centres[F_FRONT])
                return 3;
            break;
        }
        case F_RIGHT:{
            if(edgeColor == centres[F_UP])
                return 1;
            if(edgeColor == centres[F_BACK])
                return 3;
            if(edgeColor == centres[F_DOWN])
                return 5;
            if(edgeColor == centres[F_FRONT])
                return 7;
            break;
        }
    }
    return -1;
}

uint_fast64_t makePermutation(const FaceArray &faces){
    uint_fast64_t perm = 0;
    for(auto &f: {F_LEFT, F_FRONT, F_RIGHT, F_BACK}){
        for(int i = 0; i <=6; i+=2){
            perm = (perm << 4) | getSquareColor(faces, f, i);
        }
    }
    return perm;
}

bool isInitialiseStageGoal(const FaceArray &faces, const Color centres[6]){
    auto perm = makePermutation(faces);
    if(permutations.count(perm) == 0){
        permutations.insert(perm);

        if(permutations.size() == 96)   //there are 96 possible permutations
            return true;
    }

    return false;
}

//generate the 96 permutations obtained by 180 degree turns from solved state. (for g3 condition)
void initialiseSolver(const Color centres[6]){
    FaceArray solvedState;
    for(int i = 0; i < 6; ++i){
        uint_fast32_t face = 0;
        for(int j = 0; j < 8; ++j){
            face = (face<<4) | centres[i];
        }
        solvedState[i] = face;
    }
    std::array<Move, 6> availableMoves{L2, R2, F2, B2, U2, D2};
    doIDDFS(availableMoves, solvedState, centres, isInitialiseStageGoal);
}

void doMove(const Move &move, FaceArray &faces){
    switch(move){
        case U2: doMove(U, faces);
        case U:{
            //90 degree clockwise twist. roll the last 8 bits to front
            faces[F_UP] = (faces[F_UP]>>8) | ((faces[F_UP]&0xFF)<<24);

            uint_fast32_t F_value = faces[F_FRONT]&0xFFF00000;
            faces[F_FRONT] = (faces[F_FRONT]&0x000FFFFF) | (faces[F_RIGHT]&0xFFF00000);
            faces[F_RIGHT] = (faces[F_RIGHT]&0x000FFFFF) | (faces[F_BACK]&0xFFF00000);
            faces[F_BACK] = (faces[F_BACK]&0x000FFFFF) | (faces[F_LEFT]&0xFFF00000);
            faces[F_LEFT] = (faces[F_LEFT]&0x000FFFFF) | F_value;
            break;
        }

        case D2: doMove(D, faces);
        case D:{
            faces[F_DOWN] = (faces[F_DOWN]>>8) | ((faces[F_DOWN]&0xFF)<<24);

            uint_fast32_t F_value = faces[F_FRONT]&0x0000FFF0;
            faces[F_FRONT] = (faces[F_FRONT]&0xFFFF000F) | (faces[F_LEFT]&0x0000FFF0);
            faces[F_LEFT] = (faces[F_LEFT]&0xFFFF000F) | (faces[F_BACK]&0x0000FFF0);
            faces[F_BACK] = (faces[F_BACK]&0xFFFF000F) | (faces[F_RIGHT]&0x0000FFF0);
            faces[F_RIGHT] = (faces[F_RIGHT]&0xFFFF000F) | F_value;
            break;
        }

        case F2: doMove(F, faces);
        case F:{
            faces[F_FRONT] = (faces[F_FRONT]>>8) | ((faces[F_FRONT]&0xFF)<<24);

            uint_fast32_t F_value = faces[F_UP]&0x0000FFF0, val;

            faces[F_UP] = (faces[F_UP]&0xFFFF000F) | ((faces[F_LEFT]&0x00FFF000)>>8);
            faces[F_LEFT] = (faces[F_LEFT]&0xFF000FFF) | ((faces[F_DOWN]&0xFFF00000)>>8);
            val = ((faces[F_RIGHT]&0x000000FF)<<24) | ((faces[F_RIGHT]&0xF0000000)>>8);     //roll bits [6-7-0 to 0-1-2]
            faces[F_DOWN] = (faces[F_DOWN]&0x000FFFFF) | val;
            val = (F_value>>8) | (F_value<<24); 
            faces[F_RIGHT] = (faces[F_RIGHT]&0x0FFFFF00) | val;
            break;
        }
        
        case B2: doMove(B, faces);
        case B:{
            faces[F_BACK] = (faces[F_BACK]>>8) | ((faces[F_BACK]&0xFF)<<24);

            uint_fast32_t F_value = (faces[F_UP]&0xFFF00000), val;

            faces[F_UP] = (faces[F_UP]&0x000FFFFF) | ((faces[F_RIGHT]&0x00FFF000)<<8);
            faces[F_RIGHT] = (faces[F_RIGHT]&0xFF000FFF) | ((faces[F_DOWN]&0x0000FFF0)<<8);
            val = ((faces[F_LEFT]&0x000000FF)<<8) | ((faces[F_LEFT]&0xF0000000)>>24);
            faces[F_DOWN] = (faces[F_DOWN]&0xFFFF000F) | val;
            val = (F_value>>24) | (F_value<<8);
            faces[F_LEFT] = (faces[F_LEFT]&0x0FFFFF00) | val;
            break;
        }

        case L2: doMove(L, faces);
        case L:{
            faces[F_LEFT] = (faces[F_LEFT]>>8) | ((faces[F_LEFT]&0xFF)<<24);

            uint_fast32_t F_value = (faces[F_UP]&0xF00000FF), val;

            val = ((faces[F_BACK]&0x00FF0000)>>16) | ((faces[F_BACK]&0x0000F000)<<16);
            faces[F_UP] = (faces[F_UP]&0x0FFFFF00) | val;
            val =  ((faces[F_DOWN]&0x000000FF)<<16) | ((faces[F_DOWN]&0xF0000000)>>16);
            faces[F_BACK] = (faces[F_BACK]&0xFF000FFF) | val;
            faces[F_DOWN] = (faces[F_DOWN]&0x0FFFFF00) | (faces[F_FRONT]&0xF00000FF);
            faces[F_FRONT] = (faces[F_FRONT]&0x0FFFFF00) | F_value;
            break;
        }

        case R2: doMove(R, faces);
        case R:{
            faces[F_RIGHT] = (faces[F_RIGHT]>>8) | ((faces[F_RIGHT]&0xFF)<<24);

            uint_fast32_t F_value = (faces[F_UP]&0x00FFF000), val;

            faces[F_UP] = (faces[F_UP]&0xFF000FFF) | (faces[F_FRONT]&0x00FFF000);
            faces[F_FRONT] = (faces[F_FRONT]&0xFF000FFF) | (faces[F_DOWN]&0x00FFF000);
            val = ((faces[F_BACK]&0x000000FF)<<16) | ((faces[F_BACK]&0xF0000000)>>16);
            faces[F_DOWN] = (faces[F_DOWN]&0xFF000FFF) | val;
            val = (F_value>>16) | (F_value<<16);
            faces[F_BACK] = (faces[F_BACK]&0x0FFFFF00) | val;
            break;
        }
    }
}

void doMoveList(FaceArray &faces, const std::vector<Move> &moveList){
    for(auto &m: moveList){
        doMove(m, faces);
    }
}

//an edge piece is "GOOD if it can be moved to its solved position without using quarter turns of the up or down faces
bool isGoodEdge(int fromFace, int fromCubieInd, int toFace, int toCubieInd){

    /* 
            0 A 0  <--U
            B   B
            0 A 0
            _____
    0 A 0 | 0 B 0 | 0 A 0 | 0 B 0
    A   A | B   B | A   A | B   B
    0 A 0 | 0 B 0 | 0 A 0 | 0 B 0
            _____
            0 A 0
            B   B
            0 A 0

    if an 'A' edge actually belongs in a 'B' position, then a quarter up/down turn is needed and hence the edge is bad
    and vice versa

    if 'A' edge belongs to 'A' position then edge is good
    */

    static bool A_edges[6][8] = {
        {0, 1, 0, 0, 0, 1, 0, 0}, {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1}, {0, 1, 0, 1, 0, 1, 0, 1}
    };

    return A_edges[fromFace][fromCubieInd] == A_edges[toFace][toCubieInd]; 
}

bool isAllEdgesGood(const FaceArray &faces, const Color centres[6]){
    //12 edges

    //F edges -> 4      [(1, 5), (3, 7), (5, 1), (7, 3)]
    //B edges -> 4      [(1, 1), (3, 7), (5, 5), (7, 3)]
    //edges in between -> 4     [(1, 7), (3, 1), (5, 3), (7, 5)]

    int i = 1, j = i, f = F_LEFT;
    int toFace, toCubieInd;

    for(auto face : {F_UP, F_RIGHT, F_DOWN, F_LEFT}){

        //F edges
        toFace = getFace(centres, getSquareColor(faces, F_FRONT, i));
        toCubieInd = getEdgeCubieIndex(centres, toFace, getSquareColor(faces, face, (i+4)%8));
        if(!isGoodEdge(F_FRONT, i, toFace, toCubieInd))
            return false;

        //B edges
        toFace = getFace(centres, getSquareColor(faces, F_BACK, i));
        toCubieInd = getEdgeCubieIndex(centres, toFace, getSquareColor(faces, face, j));
        if(!isGoodEdge(F_BACK, i, toFace, toCubieInd))
            return false;
        j = (j == i) ? (i+6)%8 : i+2;

        //between edges
        toFace = getFace(centres, getSquareColor(faces, f, i));
        toCubieInd = getEdgeCubieIndex(centres, toFace, getSquareColor(faces, face, (i+6)%8));
        if(!isGoodEdge(f, i, toFace, toCubieInd))
            return false;
        f = face;
        
        i += 2;
    }

    return true;
}

std::vector<Move> getStage1Moves(const FaceArray &faces, const Color centres[6]){       //should be done in 7 moves

    if(isAllEdgesGood(faces, centres))
        return std::vector<Move>();

    std::array<Move, 6> availableMoves{L, R, F, B, U, D};
    return doIDDFS(availableMoves, faces, centres, isAllEdgesGood);
}

//the cube is moved to a state such that all corners are correctly oriented. 
//ie, if green is the L face, then all 8 corner cubies have green or blue on the L and R faces
//Also, four of the edges are moved to the correct slice: The FU, FD, BU, BD edges are placed in the slice b/w L and R
//If this is not possible, get them all in the U-face in at most 4 moves.
bool isStage2Goal(const FaceArray &faces, const Color centres[6]){
    const Color &color_l = centres[F_LEFT], &color_r = centres[F_RIGHT];

    //left and right face check
    for(int i = 0; i <= 6; i+=2){ 
        Color c1 = getSquareColor(faces, F_LEFT, i), c2 = getSquareColor(faces, F_RIGHT, i);
        if(!((c1 == color_l || c1 == color_r) && (c2 == color_l || c2 == color_r)))
            return false;
    }

    const Color &color_f = centres[F_FRONT], &color_b = centres[F_BACK], &color_u = centres[F_UP], &color_d = centres[F_DOWN];

    //edges check
    for(auto &i: {1, 5}){
        Color c1 = getSquareColor(faces, F_UP, i), c2 = getSquareColor(faces, F_DOWN, i);
        if(!((c1 == color_u || c1 == color_d) && (c2 == color_u || c2 == color_d)))
            return false; 

        c1 = getSquareColor(faces, F_FRONT, i); c2 = getSquareColor(faces, F_BACK, i);
        if(!((c1 == color_f || c1 == color_b) && (c2 == color_f || c2 == color_b)))
            return false; 
    }

    return true;

}

std::vector<Move> getStage2Moves(const FaceArray &faces, const Color centres[6]){
    
    if(isStage2Goal(faces, centres))
        return std::vector<Move>();

    std::array<Move, 6> availableMoves{L, R, F, B, U2, D2};
    return doIDDFS(availableMoves, faces, centres, isStage2Goal);
}

//all corners are moved to the correct orbit, meaning that each corner can be moved to its home position with only 180-degree twists. 
//Also, each edge is at its home slice. Every face should only contain edge from it and opposite face
//one of 96 possible corner permutations
bool isStage3Goal(const FaceArray &faces, const Color centres[6]){

    const Color &color_u = centres[F_UP], &color_d = centres[F_DOWN], &color_f = centres[F_FRONT], 
                &color_b = centres[F_BACK], &color_l = centres[F_LEFT], &color_r = centres[F_RIGHT];

    for(auto &i: {1, 3, 5, 7}){
        Color c1 = getSquareColor(faces, F_UP, i), c2 = getSquareColor(faces, F_DOWN, i);
        if(!((c1 == color_u || c1 == color_d) && (c2 == color_u || c2 == color_d)))
            return false; 

        c1 = getSquareColor(faces, F_FRONT, i); c2 = getSquareColor(faces, F_BACK, i);
        if(!((c1 == color_f || c1 == color_b) && (c2 == color_f || c2 == color_b)))
            return false; 
        
        c1 = getSquareColor(faces, F_LEFT, i); c2 = getSquareColor(faces, F_RIGHT, i);
        if(!((c1 == color_l || c1 == color_r) && (c2 == color_l || c2 == color_r)))
            return false; 
    }

    return permutations.count(makePermutation(faces)) == 1;
}

std::vector<Move> getStage3Moves(const FaceArray &faces, const Color centres[6]){

    if(isStage3Goal(faces, centres))
        return std::vector<Move>();

    std::array<Move, 6> availableMoves{L, R, F2, B2, U2, D2};
    return doIDDFS(availableMoves, faces, centres, isStage3Goal);
}

bool isSolved(const FaceArray &faces, const Color centres[6]){
    for(int f = 0; f < 6; ++f){
        for(int i = 0; i < 8; ++i){
            if(getSquareColor(faces, f, i) != centres[f])
                return false;
        }
    }
    return true;
}

std::vector<Move> getStage4Moves(const FaceArray &faces, const Color centres[6]){

    if(isSolved(faces, centres))
        return std::vector<Move>();

    std::array<Move, 6> availableMoves{L2, R2, F2, B2, U2, D2};
    return doIDDFS(availableMoves, faces, centres, isSolved);
}