# DESIGN Doc
## CS50 Group Project 
## Uhuru, Kelly, Megan, Tyler
## NOTE: All team members contributed to this document

# Initial ideas

# CREATING MODULE

Make a 9x9 of random numbers, and then remove numbers one by one (randomly).
After each removal, check if puzzle can be solved. 


# SOLVING MODULE

How to Solve: 

- Iterate through array once, and put coords of each number into a "known"/"given" array OR a "possibilities" array.
- Take the possibilities array
	- while (not solved)
		- at index
		- 	for each option {1..9}
		- 	make a move
		- 	check if grid is valid
				- if so, index ++;
				- if not, option++;

		BACKTRACKING: if move is made, and option is the last possible option (max), and grid is not valid, 
		then we go back a move and increment it (because we know that the last move is wrong.)

