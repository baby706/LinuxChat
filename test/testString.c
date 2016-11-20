#include <stdio.h>
#include <string.h>
int main(void)
{

	char str1[] = "abcd";
	char str2[] = "abcd";

	const char str3[] = "abcd";
	const char str4[] = "abcd";

	const char *str5 = "abcd";
	const char *str6 = "abcd";

	char *str7 = "abcd";
	char *str8 = "abcd";

	printf("%u",(str1 == str2 ));
    printf("%u",(str3 == str4 ));
	printf("%u",(str5 == str6 ));
	printf("%u",(str7 == str8 ));
 
 return 0;

}
