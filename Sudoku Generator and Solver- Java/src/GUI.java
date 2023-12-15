//this is my first time doing a GUI with only java
//so a great learning experience!!

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Graphics;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class GUI implements ActionListener{
	
	private JFrame frame = new JFrame();
	private JTextField[][] grid;
	private JButton solve = new JButton("solve");
	private JButton generate = new JButton("generate");
	
	private int[][] board;
	public GUI(int[][] board){ //constructor 
		this.board = board;
	}
	
	
	public void create() { //creates the GUI
		frame.setTitle("Sudoku");
		frame.setSize(500, 400);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(new BorderLayout());
		grid = new JTextField[9][9]; //2-D array of text fields
        JPanel panel = new JPanel(new GridLayout(9, 9, 1, 1));
        //iterates through each number in the board and puts them in the GUI
        //if the number is a zero, it is a blank
        for (int i = 0; i < 9; i++) { 
            for (int j = 0; j < 9; j++) {
            	int num = board[i][j];
            	String nums = String.valueOf(num);
            	if(num == 0 ) {
            		grid[i][j] = new JTextField();
            	}
            	else {
            		grid[i][j] = new JTextField(nums);
            	}
                grid[i][j].setHorizontalAlignment(JTextField.CENTER);
                panel.add(grid[i][j]);
                
            }
        }
        //creates the button actions
        solve.addActionListener(this);
        generate.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) { //delete old frame and replace with new one 
            	Driver driver = new Driver();
            	frame.dispose();
        		driver.generateBoard();
        		
            }
        });
        //add everything to the frame
        frame.add(panel, BorderLayout.CENTER);
        frame.add(solve, BorderLayout.SOUTH);
        frame.add(generate, BorderLayout.NORTH);
         
        
        
        frame.setLocationRelativeTo(null);
        //frame.repaint();
		frame.setVisible(true);
	}
	
	

	@Override
	public void actionPerformed(ActionEvent e) { //for the solve button
		// TODO Auto-generated method stub
		Driver driver = new Driver();
		driver.solveBoard(board); //solves the board and remakes the frame
		create();
	}
} 
	