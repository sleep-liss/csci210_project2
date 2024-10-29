


#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW

    if (pathName[0] == '\0') {
	    printf("MKDIR ERROR: no path provided\n");
	    return;
    }

    char dirName[128], baseName[65];
    struct NODE *parent = splitPath(pathName, baseName, dirName);

    if (parent == NULL) {
	    //printf("MKDIR ERROR: directory %s does not exist\n", dirName);
	    return;
    }

    //Does the child exist?
    struct NODE *existingChild = parent->childPtr;
    while (existingChild) {
	    if (strcmp(existingChild->name, baseName) == 0) {
		    printf("MKDIR ERROR: directory %s already exists\n", pathName);
		    return;
	    }
	    existingChild = existingChild->siblingPtr;
    }

    
    //creating & linking new dir node
    struct NODE *newDir = (struct NODE *)malloc(sizeof(struct NODE));
    if (newDir == NULL) {
	    printf("MKDIR ERROR: memory allocation failed\n");
	    return;
    }


    strcpy(newDir->name, baseName);
    newDir->fileType = 'D';
    newDir->parentPtr = parent;
    newDir->childPtr = NULL;
    newDir->siblingPtr = NULL;

    if (parent->childPtr == NULL) {
	    parent->childPtr = newDir;
    } else {
	    struct NODE *sibling = parent->childPtr;
	    while (sibling->siblingPtr != NULL) {
		    sibling = sibling->siblingPtr;
	    }
	    sibling->siblingPtr = newDir;
    }

      printf("MKDIR SUCCESS: node %s successfully created\n", pathName);
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // YOUR CODE HERE
    char tempPath[128];
    strcpy(tempPath, pathName);

    char *lastSlash = strrchr(tempPath, '/');
    if (lastSlash == NULL) {
	    strcpy(baseName, pathName);
	    strcpy(dirName, "");
	    return cwd;
    }

    *lastSlash = '\0';
    strcpy(baseName, lastSlash + 1);

    if (strlen(tempPath) == 0) {
	    strcpy(dirName, "/");
	    return root;
    } else {
	    strcpy(dirName, tempPath);
    }

    struct NODE *current = (dirName[0] == '/') ? root : cwd;
    char *token = strtok(dirName, "/");

    while (token != NULL) {
	    struct NODE *child = current->childPtr;
	    while (child != NULL) {
		    if (strcmp(child->name, token) == 0 && child->fileType == 'D') {
			    current = child;
			    break;
		    }
		    child = child->siblingPtr;
	    }
	    if (child == NULL) {
		    printf("ERROR: directory %s does not exist\n", token);
		    return NULL;
	    }

	    token = strtok(NULL, "/");
    }


    return current;
}
