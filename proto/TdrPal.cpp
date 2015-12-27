/* This file is generated by tdr. */
/* No manual modification is permitted. */

/* creation time: Thu Dec 03 16:03:11 2015 */
/* tdr version: 2.5.1, build at 20120623 */

#include "TdrPal.h"

namespace tsf4g_tdr
{


#if defined(_WIN32) || defined(_WIN64)
#if _MSC_VER < 1400
char* tdr_strtok(char *s, const char *delim, char **context)
{
    char* token = NULL;

    if (s == NULL)
    {
        s = *context;
    }

    s += strspn (s, delim);
    if ('\0' == *s)
    {
        *context = s;
        return NULL;
    }

    token = s;
    s = strpbrk(token, delim);
    if (NULL == s)
    {
        char* temp = token;
        while ('\0' != *temp)
        {
            temp++;
        }
        *context = temp;
    } else
    {
        *s = '\0';
        *context = s + 1;
    }

    return token;
}
#endif
#endif

}