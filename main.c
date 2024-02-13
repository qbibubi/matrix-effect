#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MIN_RANGE 8
#define MAX_RANGE 32
#define MAX_HEIGHT 45
#define MAX_WIDTH 85

typedef struct {
  int x, y;
} Vec2;

typedef struct {
  unsigned width;
  unsigned height;
  char **matrix;
} Screen;

typedef struct {
  unsigned length;
  char *line;
  Vec2 position;
} Line;

// screen
char **generate_screen();
char **populate_screen(Screen *screen);
void update_screen(Screen *screen, Line *lines);
void print_screen(Screen *screen, Line *lines);

// lines
char generate_char();
Line generate_line();
Line *generate_lines();

/*
 * MAIN
 */
int main(int argc, char *argv[]) {
  srand((unsigned int)time(NULL));

  char **matrix = generate_screen();
  Line *lines = generate_lines();
  Screen screen = {MAX_WIDTH, MAX_HEIGHT, matrix};

  while (1) {
    printf("\033[H\033[J"); // temporary screen refresh
    update_screen(&screen, lines);
    print_screen(&screen, lines);
    usleep(22000);
  }

  free(screen.matrix);

  return 0;
}

/*
 * DEFINITIONS
 */
void update_screen(Screen *screen, Line *lines) {
  for (unsigned i = 0; i < MAX_WIDTH; ++i) {
    lines[i] = generate_line();

    unsigned length =
        (lines[i].length <= screen->height) ? lines[i].length : screen->height;

    for (unsigned j = 0; j < length; ++j) {
      screen->matrix[j][i] = lines[i].line[j];
    }
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

void print_screen(Screen *screen, Line *lines) {
  for (unsigned i = 0; i < MAX_HEIGHT; ++i) {
    unsigned length = lines[i].length - 1;

    for (unsigned j = 0; j < MAX_WIDTH; ++j) {
      printf("\033[32m%c\033[0m", screen->matrix[i][j]);
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
  unsigned length = rand() % (MAX_RANGE - MIN_RANGE + 1) + MIN_RANGE;

  Line line = {length, (char *)malloc((length + 1) * sizeof(char)), {0, 0}};
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
