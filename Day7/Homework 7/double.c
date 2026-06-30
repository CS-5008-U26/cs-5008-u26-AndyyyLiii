/* double.c
   The same program as single.c, but the first 20 cities from
   uscities.csv are stored in a generic
   doubly-linked list. Each city is a heap-allocated cityData, and each
   list node (dNode) holds a void* to one city plus a prev pointer to
   the node before it. The first line of the file is column names and
   is skipped.

   After loading, the program reads commands from the console:
     size     print how many nodes are in the list
     delete   read a number n, delete the n-th city (1 = first)
     reverse  reverse the order of the nodes in the list
     get      read a number n, move the n-th city to the front
     print    read a number n, print the first n cities
     anything else   stop the program
   History:
     Wenhao   June 2026   Created
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CITIES 20

/* cityData holds one row of the file: the city name and state, plus
   latitude, longitude and population. */
typedef struct {
    char city[64];
    char state_id[8];
    char state_name[64];
    double lat;
    double lng;
    long population;
} cityData;

/* doubleNode is one node of the generic doubly-linked list. data
   points at a cityData; next points at the following node; prev points
   at the node before it. */
typedef struct doubleNode {
    void *data;
    struct doubleNode *next;
    struct doubleNode *prev;
} dNode;

/* killNewline removes a trailing newline from a string, if present.
   fgets leaves the '\n' at the end of what it reads, so this trims it.
   Parameters:
     char *str   the string to trim (modified in place)
   Returns:
     void
   Usage:
     killNewline(line);
*/
void killNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/* stripQuotes removes the surrounding double quotes from a field, if it
   has them, by dropping the last quote and shifting the rest left.
   Parameters:
     char *str   the field to unquote (modified in place)
   Returns:
     void
   Usage:
     stripQuotes(token);
*/
void stripQuotes(char *str) {
    int len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        str[len - 1] = '\0';
        for (int i = 0; str[i] != '\0'; i++) {
            str[i] = str[i + 1];
        }
    }
}

/* makeCity splits one line on commas and fills a heap cityData. The
   columns used are: 0 city, 2 state_id, 3 state_name, 6 lat, 7 lng,
   8 population.
   Parameters:
     char *line   one data line of the file (header already skipped)
   Returns:
     cityData *   pointer to a newly allocated, filled-in cityData
   Usage:
     cityData *c = makeCity(line);
*/
cityData *makeCity(char *line) {
    cityData *c = malloc(sizeof(cityData));
    int col = 0;
    char *token = strtok(line, ",");
    while (token != NULL) {
        stripQuotes(token);
        if (col == 0) {
            strcpy(c->city, token);
        } else if (col == 2) {
            strcpy(c->state_id, token);
        } else if (col == 3) {
            strcpy(c->state_name, token);
        } else if (col == 6) {
            c->lat = atof(token);
        } else if (col == 7) {
            c->lng = atof(token);
        } else if (col == 8) {
            c->population = atol(token);
        }
        token = strtok(NULL, ",");
        col++;
    }
    return c;
}

/* makeNode creates a dNode whose data field is the given city. Both
   next and prev start out NULL.
   Parameters:
     cityData *city   the city this node will hold
   Returns:
     dNode *   pointer to the new node
   Usage:
     dNode *node = makeNode(c);
*/
dNode *makeNode(cityData *city) {
    dNode *node = malloc(sizeof(dNode));
    node->data = city;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/* addFront adds node to the front of the list and returns the new head.
   The old head's prev is updated to point back at node.
   Parameters:
     dNode *list   the current head of the list
     dNode *node   the node to put in front
   Returns:
     dNode *   the new head of the list
   Usage:
     list = addFront(list, node);
*/
dNode *addFront(dNode *list, dNode *node) {
    node->prev = NULL;
    node->next = list;
    if (list != NULL) {
        list->prev = node;
    }
    return node;
}

/* addEnd adds node to the end of the list and returns the head. Used
   when loading the file so the cities stay in file order.
   Parameters:
     dNode *list   the current head of the list
     dNode *node   the node to put at the end
   Returns:
     dNode *   the head of the list
   Usage:
     list = addEnd(list, node);
*/
dNode *addEnd(dNode *list, dNode *node) {
    node->next = NULL;
    if (list == NULL) {
        node->prev = NULL;
        return node;
    }
    dNode *current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    node->prev = current;
    return list;
}

/* getNode returns a pointer to the n-th node, counting from 1, or NULL
   if n is out of range or the list is empty.
   Parameters:
     dNode *list   the head of the list
     int n         which node to get (1 = first)
   Returns:
     dNode *   the n-th node, or NULL
   Usage:
     dNode *node = getNode(list, n);
*/
dNode *getNode(dNode *list, int n) {
    dNode *current = list;
    int i = 1;
    while (current != NULL && i < n) {
        current = current->next;
        i++;
    }
    if (n < 1) {
        return NULL;
    }
    return current;
}

/* deleteNode removes the given node from the list, fixing the prev and
   next links of its neighbours, and frees the node (but not the city
   it points at). Returns the head, which may change if the head was
   deleted.
   Parameters:
     dNode *list     the head of the list
     dNode *target   the node to delete
   Returns:
     dNode *   the head of the list after the delete
   Usage:
     list = deleteNode(list, target);
*/
dNode *deleteNode(dNode *list, dNode *target) {
    if (list == NULL || target == NULL) {
        return list;
    }
    if (target->prev != NULL) {
        target->prev->next = target->next;
    }
    if (target->next != NULL) {
        target->next->prev = target->prev;
    }
    dNode *newHead = list;
    if (list == target) {
        newHead = target->next;
    }
    free(target);
    return newHead;
}

/* listLength counts the nodes in the list.
   Parameters:
     dNode *list   the head of the list
   Returns:
     int   the number of nodes
   Usage:
     int len = listLength(list);
*/
int listLength(dNode *list) {
    int count = 0;
    while (list != NULL) {
        count++;
        list = list->next;
    }
    return count;
}

/* reverseList reverses the order of the nodes by swapping each node's
   next and prev pointers, and returns the new head.
   Parameters:
     dNode *list   the head of the list
   Returns:
     dNode *   the new head after reversing
   Usage:
     list = reverseList(list);
*/
dNode *reverseList(dNode *list) {
    dNode *current = list;
    dNode *newHead = list;
    while (current != NULL) {
        dNode *next = current->next;
        current->next = current->prev;
        current->prev = next;
        newHead = current;
        current = next;
    }
    return newHead;
}

/* printCities prints the first n cities, one per line.
   Parameters:
     dNode *list   the head of the list
     int n         how many cities to print
   Returns:
     void
   Usage:
     printCities(list, n);
*/
void printCities(dNode *list, int n) {
    dNode *current = list;
    int i = 0;
    while (current != NULL && i < n) {
        cityData *c = (cityData *) current->data;
        printf("%s %s, population %ld\n", c->city, c->state_id, c->population);
        current = current->next;
        i++;
    }
}

/* main asks for the file name, skips the header, reads the first 20
   cities into a doubly-linked list, then runs the command loop.
   Parameters:
     void
   Returns:
     int   0 on success, 1 if the file could not be opened
   Usage:
     run the program and enter the path to uscities.csv
*/
int main() {
    char buffer[1000];

    printf("Enter the file name: ");
    fgets(buffer, 1000, stdin);
    killNewline(buffer);

    FILE *inFile = fopen(buffer, "r");
    if (inFile == NULL) {
        printf("Could not open file: %s\n", buffer);
        return 1;
    }

    dNode *list = NULL;
    int count = 0;
    char line[8000];

    /* skip the header line */
    fgets(line, 8000, inFile);

    /* read the first 20 cities into the list, in file order */
    while (fgets(line, 8000, inFile) != NULL && count < MAX_CITIES) {
        killNewline(line);
        cityData *c = makeCity(line);
        list = addEnd(list, makeNode(c));
        count++;
    }

    fclose(inFile);

    /* command loop */
    char command[64];
    while (1) {
        printf("size, delete, reverse, get, or print: ");
        if (scanf("%63s", command) != 1) {
            break;
        }

        if (strcmp(command, "size") == 0) {
            printf("Size is %d\n", listLength(list));
        } else if (strcmp(command, "delete") == 0) {
            int n;
            printf("Enter a number: ");
            scanf("%d", &n);
            dNode *target = getNode(list, n);
            if (target != NULL) {
                free(target->data);
                list = deleteNode(list, target);
            }
        } else if (strcmp(command, "reverse") == 0) {
            list = reverseList(list);
        } else if (strcmp(command, "get") == 0) {
            int n;
            printf("Enter a number: ");
            scanf("%d", &n);
            dNode *target = getNode(list, n);
            if (target != NULL) {
                cityData *c = (cityData *) target->data;
                list = deleteNode(list, target);
                list = addFront(list, makeNode(c));
            }
        } else if (strcmp(command, "print") == 0) {
            int n;
            printf("Enter a number: ");
            scanf("%d", &n);
            printCities(list, n);
        } else {
            break;
        }
    }

    return 0;
}