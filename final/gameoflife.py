# Conway's Game of Life simulation in Python
#
# GENERAL RULES
#
# - Each cell in the grid has one of two states: Alive (occupied) or dead (empty)
# - Every cell interacts with its 8 neighbors (in theory it wraps around in both X and Y axis)
# - For each generation, the following transactions occur:
#   
#   1) Any live cell with FEWER than two live neighbors die, as if by underpopulation.
#   2) Any live cell with two or more live neighbors lives on to the next generation.
#   3) Any live cell with more than three live neighbors dies, as if by overpopulation.
#   4) Any dead cell with EXACTLY three live neighbors becomesa live cell, as if by reproduction.

from random import randrange

# Rows and cols size validation
rows = None
cols = None
rows_flag = False
cols_flag = False

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

  print(type(rows))

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

  print(type(cols))

print(rows, cols)

grid = [[randrange(2) for i in range(cols)] for j in range(rows)]

for i in grid:
  for j in i:
    print(j, end="")
  print()

# Remember the blur exercise, you can't update the grid and then check the next value!
# There must be a new grid that's udated based on the old version
# And then, the old grid is replaced by the new one
#
# TO-DO:
# - If cell is alive, check for survival or death
# - If cell is dead, check for birth
# - Check for animation libraries for Python