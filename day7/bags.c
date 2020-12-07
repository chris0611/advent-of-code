#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#define BUFSIZE 1024
#define STRSIZE 256

typedef struct triple {
    unsigned int amt;
    char *pattern;
    char *color;
} triple;

typedef struct bag {
    char *pattern;      // what pattern does the bag have
    char *color;        // what color is the bag
    triple **bags;      // which bags can it contain
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

bag *search_bag(const char *p, const char *c, bag *arr[], const int len)
{
    if (len > 0) {
        for (int i = 0; i < len; i++) {
            if ((strcmp(p, arr[i]->pattern) == 0) && (strcmp(c, arr[i]->color) == 0)) {
                return arr[i];
            }
        }
    }
    return NULL;
}

triple *new_triple(int num, char *ptn, char *col)
{
    triple *n_trip = malloc(sizeof(*n_trip));
    n_trip->amt = num;
    n_trip->pattern = malloc(strlen(ptn)+1);
    n_trip->color = malloc(strlen(ptn)+1);

    size_t s_ptn = strlen(ptn);
    size_t s_col = strlen(col);

    strncpy(n_trip->pattern, ptn, s_ptn);
    strncpy(n_trip->color, col, s_col);

    return n_trip;
}

void new_bag(char *text, bag *arr[], int *len)
{
    bag *n_bag = malloc(sizeof(*n_bag));

    n_bag->bags = NULL;
    n_bag->gold = false;

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

        if (counter < 2) {
            if (counter == 0) {
                n_bag->pattern = malloc(STRSIZE);
                strncpy(n_bag->pattern, token, STRSIZE);
            }
            if (counter == 1) {
                n_bag->color = malloc(STRSIZE);
                strncpy(n_bag->color, token, STRSIZE);
            }
        } else if (counter >= 4) {
            if (counter % 4 == 0 && isdigit(token[0])) {
                contains_other_bags = true;
                tmp_count = atoi(token);
            } else if (contains_other_bags) {
                if (counter % 4 == 1) {
                    tmp_ptn = token;
                } else if (counter % 4 == 2) {
                    tmp_col = token; 
                    if (n_bag->bags == NULL) {
                        n_bag->bags = malloc(sizeof(triple*));
                        if (tmp_ptn != NULL && tmp_col != NULL) {
                            if (strcmp(tmp_ptn, "shiny") == 0 && strcmp(tmp_col, "gold") == 0)
                                n_bag->gold = true;
                            n_bag->bags[0] = new_triple(tmp_count, tmp_ptn, tmp_col);
                        }
                        triples++;
                    } else {
                        triples++;
                        triple **temp = realloc(n_bag->bags, sizeof(triple*) * triples);
                        assert(temp != NULL); // check reallocation was successful
                        n_bag->bags = temp;
                        if (tmp_ptn != NULL && tmp_col != NULL) {
                            if (strcmp(tmp_ptn, "shiny") == 0 && strcmp(tmp_col, "gold") == 0)
                                n_bag->gold = true;
                            n_bag->bags[triples-1] = new_triple(tmp_count, tmp_ptn, tmp_col);
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

bool search_gold(bag *initial, bag *b, bag *arr[], int len)
{
    // trying to find if a bag can contain at least one gold bag, OR a bag with that attribute

    if (b->len == 0)
        return false;
    for (int i = 0; i < b->len; i++) {
        if ((strcmp(b->bags[i]->pattern, "shiny") == 0) && (strcmp(b->bags[i]->color, "gold") == 0)) {
            initial->gold = true;
            b->gold = true;
            return true;
        }
        bag *temp = search_bag(b->bags[i]->pattern, b->bags[i]->color, arr, len);
        if (temp == NULL) {
            continue;
        }
        if (temp->gold || ((strcmp(temp->pattern, "shiny") == 0) && (strcmp(temp->color, "gold") == 0))) {
            initial->gold = true;
            b->gold = true;
            return true;
        }
        if(search_gold(initial, temp, arr, len)) {
            initial->gold = true;
            b->gold = true;
            return true;
        }
    }
    return false;
}
unsigned long product_bags_gold(bag *b, bag *arr[], const int len)
{
    unsigned long prod = 0;
    if (b->len == 0) {
        //printf("%s %s has no more bags within\n", b->pattern, b->color);
        return 1;
    } else {
        for (unsigned int i = 0; i < b->len; i++) {
            unsigned long amount = b->bags[i]->amt;
            bag *temp = search_bag(b->bags[i]->pattern, b->bags[i]->color, arr, len);
            prod += amount * product_bags_gold(temp, arr, len);
        }
        //printf("%s %s has %ld bags inside\n", b->pattern, b->color, prod);
    }
    return prod + 1;
}

unsigned long search_inside_gold(bag *b, bag *arr[], int len)
{
    unsigned long result = 0;
    //printf("%s %s\n", b->pattern, b->color);
    for (unsigned int i = 0; i < b->len; i++) {
        unsigned long amount = b->bags[i]->amt;
        //result += amount;
        bag *temp = search_bag(b->bags[i]->pattern, b->bags[i]->color, arr, len);
        //printf("%d %s %s bags\n", amount, temp->pattern, temp->color);
        result += amount * product_bags_gold(temp, arr, len);
    }
    return result;
}

int main(void)
{
    char buffer[BUFSIZE] = {0};
    bag *all_bags[BUFSIZE] = {0};
    int amount_bags = 0;
    unsigned long amount_gold = 0;
    unsigned long nested_in_gold = 0;

    while (fgets(buffer, BUFSIZE, stdin) != NULL) {
        char *text = malloc(BUFSIZE + 1);
        strncpy(text, buffer, BUFSIZE);   
        new_bag(text, all_bags, &amount_bags);
    }
    printf("Read in %d bags.\n", amount_bags);
    
    for (int i = 0; i < amount_bags; i++) {
        if ((strcmp(all_bags[i]->pattern, "shiny") == 0) && (strcmp(all_bags[i]->color, "gold") == 0)) {
            nested_in_gold = search_inside_gold(all_bags[i], all_bags, amount_bags);
        }

        if (all_bags[i]->gold) {
            amount_gold++;
        } else if (search_gold(all_bags[i], all_bags[i], all_bags, amount_bags)) {
            amount_gold++;
        }
    }

    printf("(Part 1) Amount of bags that can contain a shiny gold bag: %ld\n", amount_gold);
    printf("(Part 2) The shiny gold bag requires %ld bags within\n", nested_in_gold);



    // Gotta make sure all that memory is freed :D
    for (int i = 0; i < amount_bags; i++) {
        //printf("%d:  %s %s\nHas bags: %d\n", i, all_bags[i]->pattern, all_bags[i]->color, all_bags[i]->len);

        if (all_bags[i]->len > 0) {
            for (int j = 0; j < all_bags[i]->len; j++) {
                //printf(" -\t%d %s %s\n", all_bags[i]->bags[j]->amt, all_bags[i]->bags[j]->pattern, all_bags[i]->bags[j]->color);

                free(all_bags[i]->bags[j]->pattern);
                free(all_bags[i]->bags[j]->color);
                free(all_bags[i]->bags[j]);
            }
        }

        free(all_bags[i]->pattern);
        free(all_bags[i]->color);
        free(all_bags[i]->bags);
        free(all_bags[i]);
    } 

    return 0;
}
