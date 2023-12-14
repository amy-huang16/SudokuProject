#include <algorithm>
#include <iostream> 
#include <time.h> 

using namespace std; 

class sudoku {
    public: 
        int counter = 0; 
        int board[9][9]; 

        bool solve(int, int);
        void fill(); 
        void print(); 

    private: 
        bool is_valid(int, int, int); 

}; 

void sudoku::fill(){
    // takes in input and puts them into board array 
    string input; 
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 3; j++){
            cin >> input; 
            replace(input.begin(), input.end(), '.', '0');
            board[i][3*j] = input[0] - '0'; 
            board[i][3*j+1] = input[1] - '0';
            board[i][3*j+2] = input[2] - '0';
        }
    }
}

void sudoku::print(){
    // prints out board 
    for(int k = 0; k < 3; k++){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                cout << board[3*k+i][3*j] << board[3*k+i][3*j+1] << board[3*k+i][3*j+2] << " ";
            }
            cout << endl; 
        }
        cout << endl; 
    }
}

bool sudoku::is_valid(int r, int c, int k){
    // check all the numbers in the same column 
    for(int i = 0; i < 9; i++){
        if(board[i][c] == k){ return false; }
    }
    
    // check all the numbers in the same row
    for(int j = 0; j < 9; j++){
        if(board[r][j] == k){ return false; }
    }
    
    // check all the numbers in the same box
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[(r/3)*3 + i][(c/3)*3 + j] == k){ return false; }
        }
    }

    return true; 
}

bool sudoku::solve(int r = 0, int c = 0){
    if(r == 9){ // if rows are exhausted, then done 
        return true; 
    } 
    else if (c == 9){ // if columns are exhausted, go to next row
        return solve(r+1, 0); 
    }
    else if (board[r][c] != 0){ // if space is already filled
        return solve(r, c+1); 
    }
    else{ // if space is empty
        for(int k = 1; k < 10; k++){ // for each possible number, 1 through 9
            if(is_valid(r, c, k)){
                board[r][c] = k; 
                counter++; 
                if(solve(r, c+1)){
                    return true; 
                }
                board[r][c] = 0; 
            }
        }
        return false; 
    }
}

int main(){
    clock_t start, end;
    sudoku game; 

    start = clock(); 

    game.fill(); 
    game.solve(); 
    game.print(); 

    end = clock();
    double run_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    cout << "Counter: " << game.counter << endl; 
    cout << "Time: " << run_time << " seconds" << endl; 

}