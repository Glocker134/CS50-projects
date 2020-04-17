# Conway's Game of Life simulation in Python
#
# GENERAL RULES
#
# - Each cell in the grid has one of two states: Alive (occupied) or dead (empty)
# - Every cell interacts with its 8 neighbors (in theory it wraps around in both X and Y axis)
# - For each generation, the following transactions occur:
#   
#   1) Any live cell with FEWER than two live neighbors die, as if by underpopulation.
#   2) Any live cell with two live neighbors lives on to the next generation.
#   3) Any live cell with more than three live neighbors dies, as if by overpopulation.
#   4) Any dead cell with EXACTLY three live neighbors becomesa live cell, as if by reproduction.
#
# TO-DO:
# - Check for animation libraries for Python

import random
from copy import copy

def main():
  game_of_life()

# Game algorithm
def game_of_life():

  rows = None
  cols = None
  rows_flag = False
  cols_flag = False
  
  # Rows size validation
  while (type(rows) != int):
    rows = input("Number of rows: ")
    for x in rows:
      if ord(x) >= 48 and ord(x) <= 57:
        rows_flag = True
      else:
        rows_flag = False
        break
    
    if rows_flag == True:
      rows = int(rows)
    else:
      print("Error - Expecting a number.")

  # Cols size validation
  while (type(cols) != int):
    cols = input("Number of cols: ")
    for x in cols:
      if ord(x) >= 48 and ord(x) <= 57:
        cols_flag = True
      else:
        cols_flag = False
        break

    if cols_flag == True:
      cols = int(cols)
    else:
      print("Error - Expecting a number.")

  print(f"The grid will be of the following size: {rows} x {cols}.")

  grid = grid_init(rows, cols)

  print_grid(grid)
  
  generation = 1 
  cont = input(f"This is generation {generation}. Press enter to create next generation...")

  while cont.lower() != "q":
    grid_copy = copy(grid)
    for i in range(rows):
      for j in range(cols):
        neighbors = check_neighbors(grid_copy, i, j, rows, cols)
        if grid_copy[i][j] == 0 and neighbors == 3:
          grid[i][j] = 1
        elif grid_copy[i][j] == 1 and (neighbors < 2 or neighbors >= 3):
          grid[i][j] = 0
        else:
          grid[i][j] = grid_copy[i][j]
    
    print_grid(grid)
    generation += 1
    cont = input(f"This is generation {generation}. Press enter to continue, or type 'q' to exit...")

# Checking how many living neighbors the value at grid[i][j] has
def check_neighbors(grid, i, j, rows, cols):
  neighbors = 0
  for x in range(i-1, i+2):
    for y in range(j-1, j+2):
      neighbors += grid[x%rows][y%cols]
  neighbors -= grid[i][j]
  return neighbors

#Grid initialization
def grid_init(rows, cols):
  # Receiving seed value
  seed = input("Please type a seed. Leave empty for a random value based on time: ")
  if seed == "":
    seed = None
  
  random.seed(seed)

  grid = [[random.randrange(2) for i in range(cols)] for j in range(rows)]

  return grid

# Printing the grid
def print_grid(grid):
  for i in grid:
    for j in i:
      print(j, end="")
    print()


main()
