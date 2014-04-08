
#include <iostream>
#include <vector>

using namespace std;

struct Pair {
    int i;
    int j;
    
    Pair(int i, int j) : i(i), j(j) {}
    Pair() {};
    
};

bool operator!=(const Pair& lhs, const Pair& rhs)
{
    return lhs.i != rhs.i || lhs.j != rhs.j;
}

typedef std::vector<std::vector<int>> matrix;

std::vector<Pair> getJumpFromPositions(const matrix & gameBoard, const Pair & spacePos, Pair & lastJump) {
    std::vector<Pair> returnVector;
    Pair horse;
    for(int i = -2; i < 3; i +=4) {
        for(int j = -1; j < 2; j += 2) {
            horse.i = spacePos.i + i;
            horse.j = spacePos.j + j;
            if(horse != lastJump && horse.i >= 0 && horse.i < 5 && horse.j >= 0 && horse.j < 5) {
                returnVector.push_back(horse);
            }
            
            horse.i = spacePos.i + j;
            horse.j = spacePos.j + i;
            if(horse != lastJump && horse.i >= 0 && horse.i < 5 && horse.j >= 0 && horse.j < 5) {
                returnVector.push_back(horse);
            }
        }
    }
    return returnVector;
}

int calculate(matrix gameBoard, const matrix & finishedGame, Pair spacePos, Pair jump, int steps) {
    gameBoard[spacePos.i][spacePos.j] = gameBoard[jump.i][jump.j];
    gameBoard[jump.i][jump.j] = -1;
    Pair lastJump = spacePos;
    spacePos = jump;
    if(gameBoard == finishedGame)
    {
        return steps;
    }
    
    if (steps == 10) {
        return 11;
    }
    
    std::vector<Pair> horsesToJump = getJumpFromPositions(gameBoard, spacePos, lastJump);
    
    int best = 11, next;
    for(Pair jumpingHorse : horsesToJump) {
        next = calculate(gameBoard, finishedGame, spacePos, jumpingHorse, steps + 1);
        if(next < best) {
            best = next;
        }
    }
    
    return best;
}

int calculate(matrix & gameBoard) {
    matrix finishedGame =   {{1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1},
        {0, 0, -1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0}};
    
    Pair spacePos;
    for(int i = 0; i < gameBoard.size(); i++) {
        for (int j = 0; j < gameBoard[0].size(); j++) {
            if(gameBoard[i][j] == -1) {
                spacePos.i = i;
                spacePos.j = j;
                return calculate(gameBoard, finishedGame, spacePos, spacePos, 0);
            }
        }
    }
    return -1;
}

int main(int argc, const char * argv[])
{
    int input, steps;
    char line[7];

    scanf ("%i\n", &input);
    
    for(int i = 0; i < input; i++) {
        matrix gameBoard;
        for(int lineNr = 0; lineNr < 5; lineNr++) {
            std::vector<int> boardLine;
            fgets (line, 7, stdin);
            //scanf("%[^\n]s", line);
            for(int j = 0; j < 5; j++) {
                char c = line[j];
                if(c == ' ') {
                    boardLine.push_back(-1);
                } else {
                    boardLine.push_back(c - '0');
                }
            }
            gameBoard.push_back(boardLine);
        }
        
        steps = calculate(gameBoard);
        if(steps == 11) {
            printf("Unsolvable in less than %i move(s).\n", steps);
        } else {
            printf("Solvable in %i move(s).\n", steps);
        }
    }
    
    return 0;
}

