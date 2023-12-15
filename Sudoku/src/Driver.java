//This project generates a random, solvable sudoku 
//and provides a GUI that allows the user to:
// -type their own numbers
// -see the solution
// -and generate a new sudoku
// the algorithm to solve the sudoku comes from here: 
// https://youtu.be/mcXc8Mva2bA?si=MEoi6rpdf_bqlZqs

import java.util.Random;
public class Driver {

	private static final int GRID_SIZE = 9; //9X9 sudoku
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//test input
//		int[][] board = {
//				{7, 0, 2, 0, 5, 0, 6, 0, 0},
//				{0, 0, 0, 0, 0, 3, 0, 0, 0},
//				{1, 0, 0, 0, 0, 9, 5, 0, 0},
//				{8, 0, 0, 0, 0, 0, 0, 9, 0},
//				{0, 4, 3, 0, 0, 0, 7, 5, 0},
//				{0, 9, 0, 0, 0, 0, 0, 0, 8},
//				{0, 0, 9, 7, 0, 0, 0, 0, 5},
//				{0, 0, 0, 2, 0, 0, 0, 0, 0},
//				{0, 0, 7, 0, 4, 0, 2, 0, 3}
//				};
		
		
		generateBoard();
		
		}
	//prints the board to the console 
	//not used in driver but helpful for debugging 
	private static void printBoard(int[][] board) {
		for(int row = 0; row < GRID_SIZE; row++) {
			if(row % 3 == 0) { //these conditionals with the %3 separate the different subgrids
				System.out.println("-------------");
			}
			for(int column = 0; column < GRID_SIZE; column++) {
				if(column  % 3 == 0) { //separate subgrids 
					System.out.print("|");
				}
				System.out.print(board[row][column]);
			}
			System.out.println("|");
			
		}
	}
	
	private static boolean isNumberInRow(int[][] board, int number, int row) { //helper method for solveBoard
		for(int i = 0; i < GRID_SIZE; i++) {
			if(board[row][i] == number) {
				return true;
			}
		}
		return false;
	}
	
	private static boolean isNumberInColumn(int[][] board, int number, int column) { //helper method for solveBoard
		for(int i = 0; i < GRID_SIZE; i++) {
			if(board[i][column] == number) {
				return true;
			}
		}
		return false;
	}
	
	private static boolean isNumberInBox(int[][] board, int number, int row, int column) { //helper method for solveBoard
		int localBoxRow = row - row % 3;
		int localBoxColumn = column - column % 3;
		
		for(int i = localBoxRow; i < localBoxRow + 3; i++) {
			for(int j = localBoxColumn; j < localBoxColumn + 3; j++) {
				if(board[i][j] == number) {
					return true;
				}
			}
		}
		return false;
	}
	
	private static boolean isValidPlacement(int[][] board, int number, int row, int column){ //helper method for solveBoard
		return !isNumberInRow(board, number, row) &&
				!isNumberInColumn(board, number, column) &&
				!isNumberInBox(board, number, row, column);
	}
	
	public static boolean solveBoard(int[][] board) { //solves the board using backtracking and recursion
		for(int row = 0; row < GRID_SIZE; row++) { //go through each row
			for(int column = 0; column < GRID_SIZE; column++) { //each item in each row
				if(board[row][column] == 0) { //if the item is empty
					for(int num = 1; num <= GRID_SIZE; num++) { // check numbers 1-9 
						if(isValidPlacement(board, num, row, column)) {  //if the placement is valid
							board[row][column] = num; //set the item to the valid number 
							if(solveBoard(board)) { //repeat process using new board
								return true;
							}
							else { //if the algorithm put in an incorrect number
								board[row][column] = 0; //reset that number (backtracking!)
							}
						}
					}
					//if board is unsolvable 
					return false;
					
				}
			}
		}
		return true;
	}
	
	//similar to solveBoard
	//used to see if the board is solvable without solving it 
	private static boolean solveable(int[][] board) {
		//create a copy of the original board then go through the solving algorithm
		int[][] copy = new int[GRID_SIZE][GRID_SIZE]; 
		for(int i = 0; i < GRID_SIZE; i++) {
			copy[i] = board[i].clone();
		}
		for(int row = 0; row < GRID_SIZE; row++) {
			for(int column = 0; column < GRID_SIZE; column++) {
				if(copy[row][column] == 0) {
					for(int num = 1; num <= GRID_SIZE; num++) {
						if(isValidPlacement(copy, num, row, column)) {
							copy[row][column] = num;
							if(solveBoard(copy)) {
								return true;
							}
							else {
								copy[row][column] = 0;
							}
						}
					}
					return false;
				}
			}
		}
		return true;
	}

	//generates a random, solvable board
	// and creates a GUI with it 
	public static void generateBoard(){
		Random rd = new Random();
		int[][] board = new int[GRID_SIZE][GRID_SIZE]; 
		int count = 1;
		do{
			//creates a new board every iteration
			board = new int[GRID_SIZE][GRID_SIZE]; 
			
			for(int row = 0; row < GRID_SIZE; row++) { //go through each row and column
				for(int column = 0; column < GRID_SIZE; column++) {
					
					int num = rd.nextInt(1, 10); //fill with random number 1-9
					if(isValidPlacement(board, num, row, column)) { 
						board[row][column] = num;
					}
					else {
						board[row][column] = 0;
					}
				}
			}
			count++;
			
		} while(!solveable(board)); //iterate while the board is not solvable
		//create GUI with new board
		GUI gui = new GUI(board);
		gui.create();
	}
}
