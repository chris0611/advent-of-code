#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#define BUFSIZE 1024
#define STRSIZE 256
#define ATRSIZE 32

typedef struct triple {
    unsigned int amt;
    char *pattern;
    char *color;
} triple;

typedef struct bag {
    char *pattern;      // what pattern does the bag have
    char *color;        // what color is the bag
    triple *bags;       // which bags can it contain
    int len;            // how many triples
    bool gold;          // can it contain a gold bag
} bag;

char *strremove(char *str, const char *sub) {
    char *p, *q, *r;
    if ((q = r = strstr(str, sub)) != NULL) {
        size_t len = strlen(sub);
        while ((r = strstr(p = r + len, sub)) != NULL) {
            while (p < r)
                *q++ = *p++;
        }
        while ((*q++ = *p++) != '\0')
            continue;
    }
    return str;
}

bag *search_bag(const char *p, const char *c, bag *arr[], const int *len)
{
    if (*len > 0) {
        for (int i = 0; i < *len; i++) {
            if ((arr[i]->pattern == p) && (arr[i]->color == c)) {
                return arr[i];
            }
        }
    }
    return NULL;
}

triple *new_triple(int num, char *ptn, char *col)
{
    //printf("Creating a new triple with pattern '%s' and color '%s'\n", ptn, col);
    triple *n_trip = malloc(sizeof(*n_trip));
    n_trip->amt = num;
    n_trip->pattern = malloc(strlen(ptn));
    n_trip->color = malloc(strlen(ptn));
    strcpy(n_trip->pattern, ptn);
    strcpy(n_trip->color, col);
    return n_trip;
}

void new_bag(char *text, bag *arr[], int *len)
{
    bag *n_bag = malloc(sizeof(*n_bag));
    n_bag->bags = NULL;

    char *token;
    token = strtok(text, " ");
    unsigned int counter = 0;
    unsigned int triples = 0;
    bool contains_other_bags = false;
    int tmp_count = 0;
    char *tmp_ptn = NULL;
    char *tmp_col = NULL;

    while (token != NULL) {
        // remove unneeded parts of each token
        strremove(token, ".");
        strremove(token, ",");
        strremove(token, "\n");
        token[strlen(token)] = 0;

        if (counter < 2) {
            if (counter == 0) {
                n_bag->pattern = malloc(sizeof(token+1));
                strcpy(n_bag->pattern, token);
            }
            if (counter == 1) {
                n_bag->color = malloc(sizeof(token+1));
                strcpy(n_bag->color, token);
            }
        } else if (counter >= 4) {
            if (counter % 4 == 0 && isdigit(token[0])) {
                contains_other_bags = true;
                tmp_count = atoi(token);
            } else if (contains_other_bags) {
                if (counter % 4 == 1) {
                    tmp_ptn = token;
                } else if (counter % 4 == 2) {
                    //printf("Hello, there\n");
                    tmp_col = token; 
                    if (n_bag->bags == NULL) {
                        n_bag->bags = malloc(sizeof(triple));
                        if (tmp_ptn != NULL && tmp_col != NULL) {
                            n_bag->bags[0] = *new_triple(tmp_count, tmp_ptn, tmp_col);
                        }
                        triples++;
                    } else {
                        triples++;
                        triple *temp = realloc(n_bag->bags, sizeof(triple) * triples);
                        assert(temp != NULL); // check reallocation was successful
                        n_bag->bags = temp;
                        if (tmp_ptn != NULL && tmp_col != NULL) {
                            n_bag->bags[triples-1] = *new_triple(tmp_count, tmp_ptn, tmp_col);
                        }
                    }
                }
            }
        }

        token = strtok(NULL, " ");
        counter++;
    }
    n_bag->len = triples;
    arr[*len] = n_bag;
    *len += 1;
    free(text);
    free(token);
}

bool search_gold(bag *b)
{
    return false;
}


int main(void)
{
    char buffer[BUFSIZE] = {0};
    bag *all_bags[BUFSIZE] = {0};
    int amount_bags = 0;
    unsigned long amount_gold = 0;

    while (fgets(buffer, BUFSIZE, stdin) != NULL) {
        char *text = malloc(strlen(buffer));
        strcpy(text, buffer);   
        new_bag(text, all_bags, &amount_bags);
    }

    for (int i = 0; i < amount_bags; i++) {
        printf("%d:  %s %s\nHas bags: %d\n", i, all_bags[i]->pattern, all_bags[i]->color, all_bags[i]->len);
        free(all_bags[i]->pattern);
        free(all_bags[i]->color);
        free(all_bags[i]);
    } 
    printf("(Part 1) Amount of bags that can contain a shiny gold bag: %ld\n", amount_gold);

    return 0;
}
