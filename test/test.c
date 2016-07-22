#include <stdio.h>
#include <string.h>
#include <strings.h>

const char* lookup(const char* path);

int main(void)
{   
    //name = "dsf";
    const char* line = "GET /hello.php?name=anatoliy HTTP/1.1";
    
    // check if method is of type GET
    if (strncmp(line, "GET ", 4) == 0)
    {
       printf("%c\n", line[1]);
    }
    
    char* haystack = strchr(line, '/');
    
    //char *haystack = "/ GET";
    printf("%s\n", haystack);
    
    char* needle = strchr(haystack, ' ');
    //char *needle = " GET";
    printf("%s\n", needle);
    
    char* http_version = needle;
    
    printf("%s\n", http_version);
    
    char* errchk = strchr(http_version + 1, ' ');
    
    printf("%s\n", errchk);
    
    char request[needle - haystack + 1];
    strncpy(request, haystack, needle - haystack);
    request[needle - haystack] = '\0';
    printf("%s\n", request);
    
    
    
    int a = sizeof(request);
    
    printf("***%i\n", a);
    
} 
    