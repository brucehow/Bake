/* CITS2002 Project 2018
 * Names:	Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "targets.h"
#include "append.h"

TARGET *target_list = NULL;
TARGET *last_target = NULL;

// Track current target
TARGET *cur_target = NULL;

void add_dependecy(char *dependency) {
    if(cur_target->num == 0) {
        cur_target->dependencies = malloc(sizeof(char*));
        cur_target->dependencies[0] = malloc(sizeof(char) * strlen(dependency));
        cur_target->dependencies[0] = strdup(dependency);
        cur_target->num++;
    } else {
        cur_target->num++;
        cur_target->dependencies = realloc(cur_target->dependencies, cur_target->num * sizeof(char*));
        cur_target->dependencies[cur_target->num] = malloc(sizeof(char) * strlen(dependency));
        cur_target->dependencies[cur_target->num] = strdup(dependency);
    }
    printf("Dependency %i = %s\n", cur_target->num, dependency);
}

void process_target_def(char *word, char *ch) {
    // Store target definition in a new structure
    TARGET *new = malloc(sizeof(TARGET));
    if(new == NULL) {
        perror(__func__);
        exit(EXIT_FAILURE);
    }
    cur_target = new;
    last_target = new;
    new->target = strdup(word);

    // Exclude leading spaces
    while(isspace(*ch)) {
        ch++;
    }

    // Build dependency
    char *dependency = NULL;
    while(*ch != '\n') {
        if(!isspace(*ch)) {
            dependency = append(dependency, *ch);
        } else if(dependency != NULL) {
            add_dependecy(dependency);
            dependency = NULL;
        }
        ch++;
    }
    add_dependecy(dependency);
    free(dependency);
}
