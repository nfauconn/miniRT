#include "/mnt/nfs/homes/nfauconn/Criterion/include/criterion/criterion.h"
// #include <unistd.h>
// #include <stdio.h>
// #include <criterion/criterion.h>
int	ft_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'));
}

Test (alnum, test1)
{
	cr_expect(ft_isalnum('a') == 1, "\'a\' est alphanumerique");
}
Test (alnum, test2)
{
	cr_expect(ft_isalnum('z') == 1, "\'a\' est alphanumerique");
}
Test (alnum, test3)
{
	cr_expect(ft_isalnum('A') == 1, "\'a\' est alphanumerique");
}
Test (alnum, test4)
{
	cr_expect(ft_isalnum('Z') == 1, "\'a\' est alphanumerique");
}
Test (alnum, test5)
{
	cr_expect(ft_isalnum('1') == 1, "\'a\' est alphanumerique");
}
Test (alnum, test6)
{
	cr_expect(ft_isalnum('0') == 1, "\'a\' est alphanumerique");
}
Test (alnum, test7)
{
	cr_expect(ft_isalnum(' ') == 0, "\' \' n'est pas alphanumerique");
}
Test (alnum, test8)
{
	cr_expect(ft_isalnum('-') == 0, "\' \' n'est pas alphanumerique");
}
Test (alnum, test9)
{
	cr_expect(ft_isalnum('\\') == 0, "\' \' n'est pas alphanumerique");
}
Test (alnum, test10)
{
	cr_expect(ft_isalnum('#') == 0, "\' \' n'est pas alphanumerique");
}

// int ft_strlen(char *str)
// {
// 	int	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// Test(strlen_tests, test1)
// { 
//    cr_expect(strlen("Test") == 4, "Expected \"Test\" to have a length of 4.");
// }

// Test(strlen_tests, test2)
// {
// 	cr_expect(strlen("Hello") == 4, "This will always fail, why did I add this?");
// }

// Test(ft_strlen_tests, test1)
// { 
//    cr_expect(ft_strlen("Test") == 4, "Expected \"Test\" to have a length of 4.");
// }

// Test(ft_strlen_tests, test2)
// {
// 	cr_expect(ft_strlen("Hello") == 4, "len of \"Hello\"");
// }

// Test(prototype1, test1)
// {
// 	cr_expect(strlen("Test") == 4, "Expected \"Test\" to have a length of 4.");
//     cr_expect(strlen("Hello") == 4, "This will always fail, why did I add this?");
//     cr_assert(strlen("") == 0);
// }