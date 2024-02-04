#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * DECLARATIONS
 */

#define MIN_RANGE 16
#define MAX_RANGE 32

#define MAX_WIDTH 10
#define MAX_HEIGHT 10

typedef struct {
  unsigned width;
  unsigned height;
  char **matrix;
} Screen;

// typedef struct {
//   unsigned length;
//   char *line;
// } Line;

char **generate_screen(const unsigned width, const unsigned height);
char **populate_screen(Screen *screen);
char *generate_line();
char generate_char();
// void draw_line(Line *line, Screen *screen);

void print_screen(Screen *screen);
/*
 * MAIN
 */
int main(int argc, char *argv[]) {
  srand((unsigned int)time(NULL));

  char **matrix = generate_screen(MAX_WIDTH, MAX_HEIGHT);
  Screen screen = {MAX_WIDTH, MAX_HEIGHT, matrix};

  // while (1) {
  print_screen(&screen);
  // }

  free(screen.matrix);

  return 0;
}

/*
 * DEFINITIONS
 */
char **generate_screen(const unsigned width, const unsigned height) {
  char **screen = (char **)malloc(width * sizeof(char *));

  for (unsigned i = 0; i < width; ++i) {
    screen[i] = (char *)malloc(height * sizeof(char));

    for (unsigned j = 0; j < height; ++j) {
      screen[i][j] = '#';
    }
  }

  return screen;
}

void print_screen(Screen *screen) {
  for (unsigned i = 0; i < screen->width; ++i) {
    for (unsigned j = 0; j < screen->height; ++j) {
      printf("%c", screen->matrix[i][j]);
    }
    printf("\n");
  }
}

char generate_char() {
  const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0"
                         "123456789!@#$%^&*()-_=+[]{}|;:'<>,.?/";
  const int charsetSize = sizeof(charset) - 1;
  return charset[rand() % charsetSize];
}

char *generate_line() {
  unsigned random_length = rand() % (32 - 16 + 1) + 16;
  char *line = (char *)malloc((random_length + 1) * sizeof(char));

  for (int i = 0; i < random_length; ++i) {
    line[i] = generate_char();
  }
  line[random_length] = '\0';

  return line;
}

// void draw_line(Line *line, Screen *screen) {}
