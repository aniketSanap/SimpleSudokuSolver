#include <iostream>
#include <set>
#include <iterator>
#include <queue>

using namespace std;

class Cell {
    public:
        int value;
        set <int> potentialValues;

        void createSet() {      // Inserts all values as potential values for blank cells
            for(int i = 1; i <= 9; i++) {
                potentialValues.insert(i);
            }
        }
};

class Sudoku {
Cell sudoku[9][9];

public:
    void init();
    void createBoard();
    bool isComplete();
    void fillPositions();
    void printBoard();
    void printHorizontal();
    void checkRow(int);
    void checkColumn(int);
    void checkBlocks();
    void checkBlock(int, int);
    bool solve();
};

void Sudoku :: init() {     // Used to call createSet for every blank element
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sudoku[i][j].value == 0) {
                sudoku[i][j].createSet();
            }
        }
    }
}

bool Sudoku :: solve() {
    int x = 0;
    while(x < 81) {
        for(int i = 0; i < 9; i++) {
            checkRow(i);        // Checks all rows and discards irrelevant elements from potentialElements
        }
        for(int i = 0; i < 9; i++) {
        	checkColumn(i);     // Checks all columns and discards irrelevant elements from potentialElements
        }
        checkBlocks();      // Checks all blocks (3x3) and discards irrelevant elements from potentialElements
        fillPositions();        // Fills all newly found elements in their blank spots
        if(isComplete()) {
            return true;
        }
        x++;
    }
    return false;
}

void Sudoku :: fillPositions() {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sudoku[i][j].value == 0 && sudoku[i][j].potentialValues.size() == 1) {
                set<int> :: iterator itr;
                itr = sudoku[i][j].potentialValues.begin();
                sudoku[i][j].value = *itr;
            }
        }
    }
}

bool Sudoku :: isComplete() {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sudoku[i][j].value == 0) {
                return false;
            }
        }
    }
    return true;
}

void Sudoku :: createBoard() {
    cout<<"Enter the values for the sudoku board (0 for blank):"<<endl;
    int a;
    for(int i = 0; i < 9; i ++) {
        cout<<"Row #"<<i+1<<":"<<endl;
        for(int j = 0; j < 9; j++) {
            cin>>sudoku[i][j].value;
        }
    }
    init();
}

void Sudoku :: printBoard() {
    for(int i = 0; i < 9; i++) {
        if(i % 3 == 0)
            printHorizontal();
        for(int j = 0; j < 9; j++) {
            if(j % 3 == 0) {
                cout<<"|";
            }
            cout<<sudoku[i][j].value<<" ";
        }
        cout<<"|"<<endl;
    }
    printHorizontal();
}

void Sudoku :: printHorizontal() {      // Just for display purposes
    for(int i = 1; i < 10; i++) {
        if(i % 3 == 1) {
            cout<<"+";
        }
        cout<<"--";
    }
    cout<<"+"<<endl;
}

void Sudoku :: checkRow(int m) {
    queue<int> q;
    for(int i = 0; i < 9; i++) {
        if(sudoku[m][i].value != 0) {
            q.push(sudoku[m][i].value);     //Non empty cells are added into a queue
        }
    }
    while(q.size() > 0) {
        for(int i = 0; i < 9; i++) {
            if(sudoku[m][i].value == 0) {
                sudoku[m][i].potentialValues.erase(q.front());      // The elements of the queue are removed from all the potential elements of that row
            }
        }
        q.pop();
    }
}

void Sudoku :: checkColumn(int n) {
    queue<int> q;
    for(int i = 0; i < 9; i++) {
        if(sudoku[i][n].value != 0) {
            q.push(sudoku[i][n].value);     //Non empty cells are added into a queue
        }
    }
    while(q.size() > 0) {
        for(int i = 0; i < 9; i++) {
            if(sudoku[i][n].value == 0) {
                sudoku[i][n].potentialValues.erase(q.front());      // The elements of the queue are removed from all the potential elements of that column
            }
        }
        q.pop();
    }
}

void Sudoku :: checkBlocks() {
    for(int i = 0; i < 9; i = i + 3) {
        checkBlock(i, 0);
        checkBlock(i, 3);
        checkBlock(i, 6);
    }
}

void Sudoku :: checkBlock(int m, int n) {
    queue<int> q;
    for(int k = m; k < m + 3; k++) {
        for(int l = n; l < n + 3; l++) {
            if(sudoku[k][l].value != 0) {
                q.push(sudoku[k][l].value);     //Non empty cells are added into a queue
            }
        }
    }
    while(q.size() > 0) {
        for(int k = m; k < m + 3; k++) {
            for(int l = n; l < n + 3; l++) {
                if(sudoku[k][l].value == 0) {
                    sudoku[k][l].potentialValues.erase(q.front());      // The elements of the queue are removed from all the potential elements of that block
                }
            }
        }
        q.pop();
    }
}

int main() {
    Sudoku s;
    s.createBoard();
    if(s.solve())
        s.printBoard();
    else
        cout<<"Could not find solution"<<endl;
    return 0;
}

/*
Medium: Did not work :(

0 3 0 2 8 0 1 0 0
0 5 0 3 0 0 0 6 0
1 0 0 0 0 0 8 0 2
0 0 0 8 0 0 0 1 3
0 0 7 0 2 0 5 0 0
3 2 0 0 0 5 0 0 0
7 0 3 0 0 0 0 0 1
0 8 0 0 0 1 0 4 0
0 0 9 0 4 2 0 7 0

Easy:

4 0 2 0 1 3 5 0 0
0 0 1 2 0 5 0 0 3
0 0 0 8 0 9 0 0 6
7 0 0 0 0 0 1 4 9
0 0 8 9 0 4 3 0 0
3 9 4 0 0 0 0 0 5
8 0 0 3 0 7 0 0 0
6 0 0 4 0 2 9 0 0
0 0 7 1 9 0 8 0 4

Very easy:

9 0 2 0 0 5 4 0 3
1 0 0 0 6 3 0 2 5
5 0 8 4 0 7 0 6 0
0 2 6 3 0 9 0 0 1
0 5 7 0 1 0 2 9 0
0 9 0 6 7 0 5 3 0
2 4 0 5 3 0 6 0 0
7 0 5 2 0 0 3 0 4
0 8 0 0 4 1 9 5 0

*/
