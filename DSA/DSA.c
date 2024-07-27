#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Goal {
    char title[50];
    char description[100];
    char deadline[20];
    int priority;
    struct Goal *next;
} Goal;

typedef struct HashTable {
    Goal *table[TABLE_SIZE];
} HashTable;

HashTable* create_table() {
    HashTable *hash_table = (HashTable*)malloc(sizeof(HashTable));
    for(int i = 0; i < TABLE_SIZE; i++) {
        hash_table->table[i] = NULL;
    }
    return hash_table;
}

unsigned int hash(const char *title) {
    unsigned int hash = 0;
    while (*title) {
        hash = (hash << 5) + *title++;
    }
    return hash % TABLE_SIZE;
}

Goal* create_goal(const char *title, const char *description, const char *deadline, int priority) {
    Goal *new_goal = (Goal*)malloc(sizeof(Goal));
    strcpy(new_goal->title, title);
    strcpy(new_goal->description, description);
    strcpy(new_goal->deadline, deadline);
    new_goal->priority = priority;
    new_goal->next = NULL;
    return new_goal;
}

void add_goal(HashTable *hash_table, Goal *goal) {
    unsigned int index = hash(goal->title);
    goal->next = hash_table->table[index];
    hash_table->table[index] = goal;
}

Goal* find_goal(HashTable *hash_table, const char *title) {
    unsigned int index = hash(title);
    Goal *current = hash_table->table[index];
    while (current && strcmp(current->title, title) != 0) {
        current = current->next;
    }
    return current;
}

void remove_goal(HashTable *hash_table, const char *title) {
    unsigned int index = hash(title);
    Goal *current = hash_table->table[index];
    Goal *prev = NULL;
    while (current && strcmp(current->title, title) != 0) {
        prev = current;
        current = current->next;
    }
    if (current) {
        if (prev) {
            prev->next = current->next;
        } else {
            hash_table->table[index] = current->next;
        }
        free(current);
    }
}

void update_goal(HashTable *hash_table, const char *title, const char *new_description, const char *new_deadline, int new_priority) {
    Goal *goal = find_goal(hash_table, title);
    if (goal) {
        strcpy(goal->description, new_description);
        strcpy(goal->deadline, new_deadline);
        goal->priority = new_priority;
    }
}

void display_goals(HashTable *hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Goal *current = hash_table->table[i];
        while (current) {
            printf("Title: %s, Description: %s, Deadline: %s, Priority: %d\n", current->title, current->description, current->deadline, current->priority);
            current = current->next;
        }
    }
}

int main() {
    HashTable *hash_table = create_table();

    add_goal(hash_table, create_goal("Exercise", "Daily morning exercise", "2024-12-31", 1));
    add_goal(hash_table, create_goal("Reading", "Read a book for 30 minutes", "2024-12-31", 2));
    
    display_goals(hash_table);

    update_goal(hash_table, "Exercise", "Daily morning exercise for 30 minutes", "2024-12-31", 1);
    printf("\nAfter update:\n");
    display_goals(hash_table);

    remove_goal(hash_table, "Reading");
    printf("\nAfter removal:\n");
    display_goals(hash_table);

    return 0;
}

