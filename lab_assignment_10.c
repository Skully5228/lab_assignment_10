//Justin Rimmeli
//5299451

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    int count;
    struct Trie *children[26];
};

void insert(struct Trie **ppTrie, char *word) {
    if (*ppTrie == NULL) {
        *ppTrie = (struct Trie*) calloc(1, sizeof(struct Trie));
    }
    struct Trie *pTrie = *ppTrie;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            pTrie->children[index] = (struct Trie*) calloc(1, sizeof(struct Trie));
        }
        pTrie = pTrie->children[index];
    }
    pTrie->count++;
}

int numberOfOccurrences(struct Trie *pTrie, char *word) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            return 0;
        }
        pTrie = pTrie->children[index];
    }
    return pTrie->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie != NULL) {
        for (int i = 0; i < 26; i++) {
            if (pTrie->children[i] != NULL) {
                pTrie->children[i] = deallocateTrie(pTrie->children[i]);
            }
        }
        free(pTrie);
    }
    return NULL;
}

int main(void) {
    struct Trie *trie = NULL;
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int nWords = sizeof(pWords) / sizeof(char*);
    for (int i = 0; i < nWords; i++) {
        insert(&trie, pWords[i]);
    }
    for (int i = 0; i < nWords; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}
