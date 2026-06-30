/* single.c
   Reads the first 20 cities from uscities.csv into a generic
   singly-linked list. Each city is a heap-allocated cityData, and each
   list node (sNode) holds a void* to one city. The first line of the
   file is column names and is skipped.

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

/* singleNode is one node of the generic singly-linked list. data
   points at a cityData; next points at the following node. */
typedef struct singleNode {
    void *data;
    struct singleNode *next;
} sNode;

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

/* makeNode creates an sNode whose data field is the given city.
   Parameters:
     cityData *city   the city this node will hold
   Returns:
     sNode *   pointer to the new node
   Usage:
     sNode *node = makeNode(c);
*/
sNode *makeNode(cityData *city) {
    sNode *node = malloc(sizeof(sNode));
    node->data = city;
    node->next = NULL;
    return node;
}

/* addFront adds node to the front of the list and returns the new head.
   Parameters:
     sNode *list   the current head of the list
     sNode *node   the node to put in front
   Returns:
     sNode *   the new head of the list
   Usage:
     list = addFront(list, node);
*/
sNode *addFront(sNode *list, sNode *node) {
    node->next = list;
    return node;
}

/* addEnd adds node to the end of the list and returns the head. Used
   when loading the file so the cities stay in file order.
   Parameters:
     sNode *list   the current head of the list
     sNode *node   the node to put at the end
   Returns:
     sNode *   the head of the list
   Usage:
     list = addEnd(list, node);
*/
sNode *addEnd(sNode *list, sNode *node) {
    node->next = NULL;
    if (list == NULL) {
        return node;
    }
    sNode *current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return list;
}

/* getNode returns a pointer to the n-th node, counting from 1, or NULL
   if n is out of range or the list is empty.
   Parameters:
     sNode *list   the head of the list
     int n         which node to get (1 = first)
   Returns:
     sNode *   the n-th node, or NULL
   Usage:
     sNode *node = getNode(list, n);
*/
sNode *getNode(sNode *list, int n) {
    sNode *current = list;
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

/* deleteNode removes the given node from the list and frees the node
   (but not the city it points at, so the caller can keep it). Returns
   the head, which may change if the head was deleted.
   Parameters:
     sNode *list     the head of the list
     sNode *target   the node to delete
   Returns:
     sNode *   the head of the list after the delete
   Usage:
     list = deleteNode(list, target);
*/
sNode *deleteNode(sNode *list, sNode *target) {
    if (list == NULL || target == NULL) {
        return list;
    }
    if (list == target) {
        sNode *newHead = list->next;
        free(list);
        return newHead;
    }
    sNode *current = list;
    while (current->next != NULL && current->next != target) {
        current = current->next;
    }
    if (current->next == target) {
        current->next = target->next;
        free(target);
    }
    return list;
}

/* listLength counts the nodes in the list.
   Parameters:
     sNode *list   the head of the list
   Returns:
     int   the number of nodes
   Usage:
     int len = listLength(list);
*/
int listLength(sNode *list) {
    int count = 0;
    while (list != NULL) {
        count++;
        list = list->next;
    }
    return count;
}

/* reverseList reverses the order of the nodes and returns the new head.
   Parameters:
     sNode *list   the head of the list
   Returns:
     sNode *   the new head after reversing
   Usage:
     list = reverseList(list);
*/
sNode *reverseList(sNode *list) {
    sNode *prev = NULL;
    while (list != NULL) {
        sNode *next = list->next;
        list->next = prev;
        prev = list;
        list = next;
    }
    return prev;
}

/* printCities prints the first n cities, one per line.
   Parameters:
     sNode *list   the head of the list
     int n         how many cities to print
   Returns:
     void
   Usage:
     printCities(list, n);
*/
void printCities(sNode *list, int n) {
    sNode *current = list;
    int i = 0;
    while (current != NULL && i < n) {
        cityData *c = (cityData *) current->data;
        printf("%s %s, population %ld\n", c->city, c->state_id, c->population);
        current = current->next;
        i++;
    }
}

/* main asks for the file name, skips the header, reads the first 20
   cities into a singly-linked list, then runs the command loop.
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

    sNode *list = NULL;
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
            sNode *target = getNode(list, n);
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
            sNode *target = getNode(list, n);
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