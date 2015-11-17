/* File: main7.c
 *
 *  Exercise the strrev() and strrepl() functions.
 *
 * */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// These functions will be implemented in assembly:
//
void strrev(char *str) ;
int strrepl(char *str, int c, int (* isinsubset) (int c) ) ;


int isvowel (int c) {

   if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') 
      return 1 ;

   if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') 
      return 1 ;

   return 0 ;
}


int main() {
   char *str1, *str2, *str3, *str4, *str5 ;
   int r ;

   str1 = strdup("Hello World") ;
   strrev(str1) ;
   printf("str1 = \"%s\"\n", str1) ;
   free(str1) ;

   str2 = strdup("This is a very long string that will get reversed!") ;
   strrev(str2) ;
   printf("str2 = \"%s\"\n", str2) ;
   free(str2) ;

   str3 = strdup("able was I ere I saw elba") ;
   strrev(str3) ;
   printf("str3 = \"%s\"\n", str3) ;
   free(str3) ;

   printf("\n") ;

   str4 = NULL ;
   strrev(str4) ;
   printf("Calling strrev() with NULL did not crash!\n") ;

   str4 = strdup("1") ;
   strrev(str4) ;
   printf("str4 = \"%s\"\n", str4) ;
   free(str4) ;

   str5 = strdup("") ;
   strrev(str5) ;
   printf("Calling strrev() with empty string did not crash!\n") ;
   free(str5) ;

   printf("\n") ;

   str1 = strdup("ABC 123 779 Hello World") ;
   r = strrepl(str1, '#', &isdigit) ;
   printf("str1 = \"%s\"\n", str1) ;
   printf("%d chararcters were replaced\n", r) ;
   free(str1) ;

   printf("\n") ;

   str2 = strdup("ABC 123 779 Hello World") ;
   r = strrepl(str2, '@', &isxdigit) ;
   printf("str2 = \"%s\"\n", str2) ;
   printf("%d chararcters were replaced\n", r) ;
   free(str2) ;

   printf("\n") ;

   str3 = strdup("ABC 123 779 Hello World") ;
   r = strrepl(str3, '_', &isvowel) ;
   printf("str3 = \"%s\"\n", str3) ;
   printf("%d chararcters were replaced\n", r) ;
   free(str3) ;

   return 0 ;
}
