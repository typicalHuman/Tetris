#include <limits.h>
#include <unistd.h>
#include "string_functions.h"

//Get file path by relative path in the project.
char* GetFilePath(const char* relativePath)
{
    char cwd[PATH_MAX];
    //define current project path
    char* file = getcwd(cwd, sizeof(cwd));
    //concat it with relative path
    strcat(file, relativePath);
    //replace \\ symbols to avoiding errors
    return str_replace(file, "\\", "/");
}