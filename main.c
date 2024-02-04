#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MIN_RANGE 8
#define MAX_RANGE 32
#define MAX_HEIGHT 45
#define MAX_WIDTH 85

typedef struct {
  unsigned width;
  unsigned height;
  char **matrix;
} Screen;

typedef struct {
  unsigned length;
  char *line;
} Line;

// screen
char **generate_screen();
char **populate_screen(Screen *screen);
void update_screen(Screen *screen);
void print_screen(Screen *screen);

// lines
Line generate_line();
Line *generate_lines();
char generate_char();

/*
 * MAIN
 */
int main(int argc, char *argv[]) {
  srand((unsigned int)time(NULL));

  char **matrix = generate_screen();
  Screen screen;
  screen.width = MAX_WIDTH;
  screen.height = MAX_HEIGHT;
  screen.matrix = matrix;

  Line *lines = (Line *)malloc(MAX_WIDTH * sizeof(Line));

  while (1) {
    printf("\033[H\033[J"); // temporary screen refresh
    update_screen(&screen);
    print_screen(&screen);
    sleep(1);
  }

  free(screen.matrix);

  return 0;
}

/*
 * DEFINITIONS
 */
void update_screen(Screen *screen) {
  for (unsigned i = 0; i < MAX_WIDTH; ++i) {
    Line line = generate_line();
    unsigned length =
        (line.length <= screen->height) ? line.length : screen->height;

    for (unsigned j = 0; j < length; ++j) {
      screen->matrix[j][i] = line.line[j];
    }
    free(line.line);
  }
}

char **generate_screen() {
  char **screen = (char **)malloc(MAX_HEIGHT * sizeof(char *));

  for (unsigned i = 0; i < MAX_HEIGHT; ++i) {
    screen[i] = (char *)malloc(MAX_WIDTH * sizeof(char));

    for (unsigned j = 0; j < MAX_WIDTH; ++j) {
      screen[i][j] = ' ';
    }
  }

  return screen;
}

void print_screen(Screen *screen) {
  for (unsigned i = 0; i < MAX_HEIGHT; ++i) {
    for (unsigned j = 0; j < MAX_WIDTH; ++j) {
      printf("%c", screen->matrix[i][j]);
    }
    printf("\n");
  }
}

char generate_char() {
  const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0"
                         "123456789!@#$%^&*()-_=+[]{}|;:'<>,.?";
  const int charsetSize = sizeof(charset) - 1;
  return charset[rand() % charsetSize];
}

Line generate_line() {
  // set random length withing (MIN_RANGE, MAX_RANGE)
  unsigned length = rand() % (MAX_RANGE - MIN_RANGE + 1) + MIN_RANGE;

  Line line;
  line.length = length;

  // generate random chars size of length
  line.line = (char *)malloc((length + 1) * sizeof(char));
  for (int i = 0; i < length; ++i) {
    line.line[i] = generate_char();
  }
  line.line[length] = '\0';

  return line;
}

Line *generate_lines() {
  Line *lines = (Line *)malloc(MAX_WIDTH * sizeof(Line));
  for (unsigned i = 0; i < MAX_WIDTH; ++i) {
    lines[i] = generate_line();
  }

  return lines;
}
