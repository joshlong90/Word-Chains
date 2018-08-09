// Written by Joshua Long
// Data Structures and Algorithms
// COMP9024 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "Graph.h"
#include "stack.h"
#include "queue.h"

#define MAX_WORD_LENGTH 20
#define FORMAT_STRING "%19s"
#define WORD_LIMIT 1000
#define LINE_LENGTH 1024


// Helper function used to determine order for qsort.
int compare(const void *str1, const void *str2) {
	return strcmp( *(char **)str1, *(char **)str2);
}
// Function reference.
// Sedgewick, R. (1998). Algorithms in C - Parts 1-4 (pp. 117).

// Prints out all (n_max) maximal paths of length (max_path).
void printPaths(int *visited, Graph g, int *n_max, 
	   int *max_path, char **words, int *max_paths, int n) {
    int p, u, v;
    for (p = 0; p < *n_max; p++) {
    	stack s;
        stack solution;
    	s = newStack();
        solution = newStack();
    	v = max_paths[p];
    	StackPush(s, v);
    	while (!(StackIsEmpty(s))) {
            v = StackPop(s);
            if (!StackIsEmpty(solution)) {
                while (topStack(solution) < v) {
                    StackPop(solution);
                }
            }
            StackPush(solution, v);
            if (heightStack(solution) >= *max_path) {
                StackPrint(solution, words);
            } else {
                for (u = v - 1; u >= 0; u--) {
                    if (visited[u] == visited[v] - 1) {
                        if (adjacent(g, u, v)) {
                            StackPush(s, u);
                        }
                    }
                }
            }
    	}
		dropStack(s);
    }
}

// USER INPUT FUNCTIONS.

// Scan input for a positive integer, returns -1 if none.
int readInt(void) {
   char line[LINE_LENGTH];
   int  n;

   fgets(line, LINE_LENGTH, stdin);
   if ( (sscanf(line, "%d", &n) != 1) || n <= 0 )
      return -1;
   else
      return n;
}
// Function reference.
// UNSW COMP9024 17s2 Assignment 1 - Taken from studentRecord.c

// Scans input and places strings in an array.
char **readWords(char **words, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("Enter word: ");
		words[i] = malloc(MAX_WORD_LENGTH * sizeof(*words[i]));
		scanf(FORMAT_STRING, words[i]);
	}
	return words;
}


////////////////////////////////////////////////////////////////////////////////

// GRAPH FORMATION FUNCTIONS (task 1)
// OVERALL COMPLEXITY ANALYSIS: O(n^2 * m)
// COMPLEXITY EXPLANATION: Based on complexity of the populateGraph function. 
//populateGraph contains a for loop within a for loop which both iterate through 
//n elements. The adjacentWord function is then called inside the loops. The 
//adjacentWord function has complexity O(m) as it iterates through each word 
//with a maximum length of (m).


// Helper function to the adjacentWord function.
// Function complexity: O(m) - Uses for loop to iterate through each character 
//of a word with maximum length (m).
int _adjacentWord(char *word1, char *word2, int l_word1, int l_word2) {
	int i;
	int j = 0;
	for (i = 0; i < l_word1; i++) {
		if (word1[i] == word2[j]) {
				j++;
		}
	}
	if (j == l_word2) {
		return 1;
	}
	return 0;
}

// Returns 1 if word1 and word2 can form a link, returns 0 otherwise.
// Function complexity: O(m) - Uses for loop to iterate through each
//character of a word with maximum length (m).
int adjacentWord(char *word1, char *word2, int l_word1, int l_word2) {
	if (l_word2 + 1 == l_word1) {
		return _adjacentWord(word1, word2, l_word1, l_word2);
	} else if (l_word2 == l_word1 + 1) {
		return _adjacentWord(word2, word1, l_word2, l_word1);
	} else if (l_word2 == l_word1) {
		int i;
		int j = 0;
		for (i = 0; i < l_word1; i++) {
			if (word1[i] == word2[i]) {
				j++;
			}
		}
		if (j >= l_word1 - 1) {
			return 1;
		}
	}
	return 0;
}

// Iterates through all pairs of words, creates edge if they're adjacent.
// Function complexity: O(n^2 * m) - contains a for loop within a for loop
//which both iterate through n elements. The adjacentWord function is then
//called inside the loops which has complexity O(m) (see above functions).
void populateGraph(Graph g, char **words, int n) {
	assert(g != NULL);

	int i, j;
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			int l_word1 = strlen(words[i]);
			int l_word2 = strlen(words[j]);
			if (adjacentWord(words[i], words[j], l_word1, l_word2)) {
				Edge e;
				e.v = i;
				e.w = j;
				insertEdge(g, e);
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////////////

// MAXIMAL CHAIN LENGTH FUNCTIONS (task 2)
// OVERALL COMPLEXITY ANALYSIS: O(2^n)
// COMPLEXITY EXPLANATION: Based on complexity of the pathCrawler function.
//The pathCrawler function in the worst case scenario (i.e. each word is 
//adjacent to every word that is later in the alphabet) would be required to
//check 2^n - 1 possible paths.

//POSSIBLE PATHS PROOF:
//let n be the number of vertices.
//let Tn be the number of possible paths with n vertices.
//We find that Tn = 2(Tn-1) + 1

//Tn = 2(Tn-1) + 1
//   = 2(2(Tn-2) + 1) + 1
//   = 2^2(Tn-2) + 2^1 + 2^0
//   = 2^k(Tn-k) + 2^k-1 + 2^k-2 + ... 2^1 + 2^0

//let k = n
//Tn = 2^n(T0) + 2^n-1 + 2^n-2 + ... 2^1 + 2^0
//   = 2^n-1 + 2^n-2 + ... 2^1 + 2^0
//   = (1 - 2^n) / (1 - 2)    (using sum of finite geometric series formula)
//   = 2^n - 1


// Conducts a breadth first search records longest paths.
// Function complexity = O(2^n) - In the worst case scenario, each word will be
//adjacent to every word that is later in the alphabet. This would mean that
//there are 2^n - 1 possible paths to explore (including chains of length 1 that
//do not use any edges).
void pathCrawler(Graph g, int *visited, int n) {
    assert(g != NULL);
    
    int i, j, v;
    for (i = 0; i < n; i++) {
    	visited[i] = -1;
    }
    for (i = 0; i < n; i++) {
        if (visited[i] == -1) {
            queue q;
            q = newQueue();
            QueueEnqueue(q, i);
            visited[i] = 1;
            while (!(QueueIsEmpty(q))) {
                v = QueueDequeue(q);
                for (j = v; j < n; j++) {
                    if (adjacentNode(g, v, j)) {
                        if (visited[j] < visited[v] + 1) {
                            visited[j] = visited[v] + 1;
                        }
                        QueueEnqueue(q, j);
                    }
                }
            }
            dropQueue(q);
        }
    }
}

// finds the end node of each maximal chain and stores in max paths.
// Function complexity = O(n) - Uses for loop to iterate through n elements all
//operations within a for loop can be executed with O(1) time complexity.
int *maximalChain(int *visited, int n, int *n_max, int *max_path) {
    int i;
    *max_path = 0;
    *n_max = 0;
    for (i = 0; i < n; i++) {
        if (visited[i] > *max_path) {
            *max_path = visited[i];
            *n_max = 1;
        } else if (visited[i] == *max_path) {
            (*n_max)++;
        }
    }
    int *max_paths = malloc(*n_max * sizeof(int));
    int p = 0;
    for (i = 0; i < n; i++) {
        if (visited[i] == *max_path) {
            max_paths[p] = i;
            p++;
        }
    }
    return max_paths;
}


////////////////////////////////////////////////////////////////////////////////

// MAIN PROGRAM.

int main(void) {
	// Taking input and placing words into sorted array.
	printf("Enter a number: ");
	int n = readInt();
	if (n < 1 || n > WORD_LIMIT)
		exit(EXIT_SUCCESS);
	char **words = malloc(n * sizeof(*words));
	assert(words != NULL);
	words = readWords(words, n);
	qsort(words, n, sizeof(char *), compare);
	
	// TASK 1
	// GRAPH FORMATION: Complexity Analysis O(n^2 + m)
	Graph g = newGraph(n);
	populateGraph(g, words, n);

	// TASK 2
	// MAXIMAL CHAIN LENGTH: Complexity Analysis O(n^2)
	int *visited = malloc(n * sizeof(int));
    int *max_paths;
    int *n_max = malloc(sizeof(int));
    int *max_path = malloc(sizeof(int));
    
    pathCrawler(g, visited, n);
    max_paths = maximalChain(visited, n, n_max, max_path);

    // Print output.
	showEdges(g, words);
    printf("\nMaximum chain length: %d", visited[max_paths[0]]);
    printf("\nMaximal chains:\n");
    printPaths(visited, g, n_max, max_path, words, max_paths, n);

    // Free all stored variables in heap.
    int i;
    for (i = 0; i < n; i++) {
    	free(words[i]);
    }

    free(words);
    free(visited);
    free(n_max);
    free(max_path);
    free(max_paths);
	return 0;
}
