#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 255

int main() {
  // --- Open puzzle file ---
  FILE *puzzleFilePtr = fopen("./puzzle.txt", "r");
  if (puzzleFilePtr == NULL) {
    printf("Error: Unable to open puzzle file.\n");
    return 1;
  }

  char buffer[BUFFER_SIZE];

  // --- Parse grid dimensions ---
  int rows, cols;
  if (fgets(buffer, BUFFER_SIZE, puzzleFilePtr) != NULL) {
    sscanf(buffer, "size: %dx%d", &rows, &cols);
    printf("Rows: %d\nCols: %d\n", rows, cols);
  }

  // Maximum word length (grid dimension + 1 for null terminator)
  int maxWordLength = (rows > cols ? rows : cols) + 1;

  // --- Parse number of words ---
  int wordCount;
  if (fgets(buffer, BUFFER_SIZE, puzzleFilePtr) != NULL) {
    sscanf(buffer, "amount: %d", &wordCount);
    printf("Number of words: %d\n", wordCount);
  }

  // --- Parse the words list ---
  char words[wordCount][maxWordLength];
  if (fgets(buffer, BUFFER_SIZE, puzzleFilePtr) != NULL) {
    int wordIndex = 0;
    int charIndex = 0;
    char tempWord[maxWordLength];

    const int prefixLength = 7; // length of "words: "
    for (int i = prefixLength; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
      if (buffer[i] == ',') {
        tempWord[charIndex] = '\0';
        strcpy(words[wordIndex], tempWord);
        wordIndex++;
        charIndex = 0;
      } else {
        tempWord[charIndex] = buffer[i];
        charIndex++;
      }
    }
    // Copy the last word after final comma
    tempWord[charIndex] = '\0';
    strcpy(words[wordIndex], tempWord);
  }

  // --- Display parsed words ---
  printf("\nWords in puzzle:\n");
  for (int i = 0; i < wordCount; i++) {
    printf("%d: %s\n", i + 1, words[i]);
  }

  // --- Parse the grid ---
  char puzzle[rows][cols];
  int rowCount = 0;

  fgets(buffer, BUFFER_SIZE, puzzleFilePtr); // this reads the "grid:" line

  while (fgets(buffer, BUFFER_SIZE, puzzleFilePtr) != NULL && rowCount < rows) {
    int colCount = 0;
    for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
      if (buffer[i] != ' ') { // skip spaces
        puzzle[rowCount][colCount] = buffer[i];
        colCount++;
      }
    }
    rowCount++;
  }

  // --- Display the puzzle grid ---
  printf("\nPuzzle Grid:\n");
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      printf("%c ",
             puzzle[row][col]); // print each character followed by a space
    }
    printf("\n"); // move to the next row
  }

  // --- Close the file ---
  fclose(puzzleFilePtr);

  return 0;
}
