#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * DECLARATIONS
 */

#define MIN_RANGE 16
#define MAX_RANGE 32

#define MAX_WIDTH 109
#define MAX_HEIGHT 102

typedef struct {
  unsigned width;
  unsigned height;
  char **matrix;
} Screen;

typedef struct {
  unsigned length;
  char *line;
} Line;

char **generate_screen(const unsigned width, const unsigned height);
char *generate_line();
char generate_char();

// draws a line on the screen
void draw_line(Line *line, Screen *screen);

/*
 * MAIN
 */
int main(int argc, char *argv[]) {
  srand((unsigned int)time(NULL));
  char **screen = generate_screen(MAX_WIDTH, MAX_HEIGHT);

  while (1) {
    // print the matrix effect
  }

  return 0;
}

/*
 * DEFINITIONS
 */
char **generate_screen(const unsigned width, const unsigned height) {
  char **screen = (char **)malloc(width * sizeof(char));

  for (unsigned i = 0; i < width; ++i) {
    screen[i] = (char *)malloc(height * sizeof(char));
  }

  return screen;
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

void draw_line(Line *line, Screen *screen) {}
