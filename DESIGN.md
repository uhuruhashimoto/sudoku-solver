# DESIGN Doc
## CS50 Group Project 
## Uhuru, Kelly, Megan, Tyler

# Initial ideas

# Solving

## Solving Storage
- store crossword a matrix of integers, with known values at the 0th index of their array (all else null). 
- OR: store two matrixes of integers, with known values and 0's on one, and possibilities on the other

- for empty (0) positions, input {1..9} in to array to represent possibilities
- go through each row 
	- if a known number is in that row, remove it from all 0 arrays in that column
- go through each column
	- if a known number is in that column, remove it from all 0 arrays in that column
- go through each quadrant
	- if a known number is in that quadrant, remove it from all 0 arrays in that quadrant (already done rows and cols)


