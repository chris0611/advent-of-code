#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define BUFSIZE 256

int main(void)
{
	
	bool ***grid = NULL;		// Odd indicies represent negative coordinates..?
	char buffer[BUFSIZE] = {0};
	uint16_t X = 0;		// Size of grid in x y z directions
	uint16_t Y = 0;
	uint16_t Z = 1;

	while (fgets(buffer, BUFSIZE, stdin) != NULL) {
		++Y;
		if (grid == NULL) {
			// rewrite
			X = strlen(buffer)-1;
			grid = malloc(sizeof(bool**) * Z);
			for (uint8_t i = 0; i < Z; ++i) {
				grid[i] = malloc(sizeof(bool*)* Y);
				for (uint8_t j = 0; j < Y; ++j) {
					grid[i][j] = malloc(sizeof(bool) * X);
					for (uint8_t k = 0; k < X; ++k) {
						printf("%c ", buffer[k]);
						if (buffer[k] == '#') {
							grid[i][j][k] = true;
						} else {
							grid[i][j][k] = false;
						}			
					}
				}
			}
			printf("\n");
			/*	
			// bad method below
			Y = strlen(buffer)-1;
			grid = malloc(sizeof(bool**) * Y);
			for (uint8_t i = 0; i < Y; ++i) {
				grid[i] = malloc(sizeof(bool*) * X);
				for (uint8_t j = 0; j < X; ++j) {
					grid[i][j] = malloc(sizeof(bool) * Z);
					for (uint8_t k = 0; k < Z; ++k) {
						if (buffer[i] == '#') {
							grid[i][j][k] = true;
						} else {
							grid[i][j][k] = false;
						}
					}
				}
			}
			*/
		} else {
			/*
			// rewritten method
			uint8_t i;
			**temp = malloc(sizeof(bool*)*Y);
			for (i = 0; i < Y-1; ++i) {
				temp[i] = grid[0][i];	
			}
			

			// bad method below
			for (uint8_t i = 0; i < Y; ++i) {
				bool **temp = malloc(sizeof(bool*)*X);
				uint8_t j = 0;
				for (; j < X-1; ++j) {
					temp[j] = grid[i][j];
				}
				for (j = X-1; j < X; ++j) {
					temp[j] = malloc(sizeof(bool)*Z);
					if (buffer[i] == '#') {
						temp[j][0] = true;
					} else {
						temp[j][0] = false;
					}
				}
				free(grid[i]);
				grid[i] = temp;
			}			
		*/
		}
	}
	printf("Width:  %u\n", X);
	printf("Height: %u\n", Y);
	printf("Depth:  %u\n", Z);



	// Freeing used memory
	/*
	for (uint8_t i = 0; i < Y; ++i) {
		for (uint8_t j = 0; j < X; ++j) {
			if (grid[i][j][0]) {
				printf("# ");
			} else {
				printf(". ");
			}
			free(grid[i][j]);
		}
		printf("\n");
		free(grid[i]);
	}
	free(grid);
	*/
	return 0;
}
