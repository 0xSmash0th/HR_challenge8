#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define HASHSIZE 100000
//max possible entries

static struct pbEntry *phBook[HASHSIZE]; //hashtable


typedef struct pbEntry {
        char *name;
        char *phNum;
        struct pbEntry *next;
} PBENTRY;

PBENTRY *lookup(char *name);
PBENTRY *install(char *name, char *phNum);
unsigned hash(char *name);



// hash: form hash value for string s
unsigned hash(char *s){
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;//+ 0xaaaaaaaa * hashval;
    //printf("%x\n", hashval%HASHSIZE);
    return hashval % HASHSIZE;
}

// lookup: look for s in hashtab
PBENTRY *lookup(char *s){
    PBENTRY *phE;
    int cf = 0;
    for (phE = phBook[hash(s)]; phE != NULL; phE = phE->next){
/*    	if (cf > 0){
    		printf("collision found!\n");
    	}*/
    	cf++;
    	if(strcmp(s, phE->name) == 0){
    		//printf("phE name: %s\n", phE->name);
    		return phE; // found
    	}
    }
    return NULL; /* not found */
}

// install: put (name, defn) in hashtab
PBENTRY *install(char *name, char *phNum){
    PBENTRY *phE;
    PBENTRY *tmpNode;
    unsigned hashval;
    if ((phE = lookup(name)) == NULL) { // not found
        phE = (PBENTRY *) malloc(sizeof(*phE));
        if (phE == NULL || (phE->name = strdup(name)) == NULL)
        	return NULL;
        hashval = hash(name);
        phE->next = NULL; //if first entry set next to NULL
        tmpNode = phBook[hashval];
        if (tmpNode == NULL){
            phBook[hashval] = phE;
        }else{
        	while (tmpNode->next != NULL){
        		tmpNode = tmpNode->next;
        	}
        	tmpNode->next = phE;
        }

    }else{
    	free((void *) phE->phNum);
    }
    if ((phE->phNum = strdup(phNum)) == NULL){
    	return NULL;
    }
    return phE;
}

int main() {
    int n, i, phNumNL, ret;
    char s[BUFSIZ], *name, *phNum;
    PBENTRY * ans;
    //printf("phBook Size: %d\n", sizeof(phBook));
    memset(phBook, 0, sizeof(phBook)/sizeof(PBENTRY*));
    scanf("%d", &n);
    getchar();

    for (i = 0; i < n; i++){
        fgets(s, BUFSIZ, stdin);
        name = strtok(s, " ");
        phNum = strtok(NULL, " ");
        phNumNL = strcspn(phNum, "\n");
        phNum[phNumNL] = '\0';
        ans = install(name, phNum);

    }
    while ((ret = scanf("%s", s) ) == 1){
        ans = lookup(s);
        if (ans){
            printf("%s=%s\n", ans->name, ans->phNum);
        }else{
            printf("Not found\n");
        }
    }

    // Enter your code here. Read input from STDIN. Print output to STDOUT
    return 0;
}
