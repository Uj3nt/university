#include <assert.h>
#include "libs/string/task/string_.c"
#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)


void assertString(const char *expected, char *got, char const *fileName, char const *funcName, int line) {
    if (strcmp(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

void strlen_v1_test() {
    char a[] = "Hello";
    size_t res = strlen_v1(a);
    assert(res == 5);
}

void strlen_v2_test() {
    char a[] = "Hello";
    size_t res = strlen_v2(a);
    assert(res == 5);
}

void strlen_test() {
    char a[] = "Hello";
    size_t res = strlen_(a);
    assert(res == 5);
}

void strlen_tests() {
    strlen_v1_test();
    strlen_v2_test();
    strlen_test();
}

void find_test1() {
    char a[] = "Linus Torvalds";
    char ch = 'l';

    char *end = a + sizeof(a) - 1;
    char *res = find(a, end , ch);

    assert(*res == 'l');
}

void find_test2() {
    char a[] = "Moman Roroz";
    char ch = 'x';

    char *end = a + sizeof(a) - 1;
    char *res = find(a, end , ch);

    assert(res == end);
}

void find_tests() {
    find_test1();
    find_test2();
}

void findNonSpace_test1() {
    char a[] = "          Rust        ";
    char *res = findNonSpace(a);

    assert(*res == 'R');
}

void findNonSpace_test2() {
    char a[] = "   ";
    char *res = findNonSpace(a);
    char *end = a + sizeof(a) - 1;

    assert(res == end );
}

void findNonSpace_tests() {
    findNonSpace_test1();
    findNonSpace_test2();
}

void findSpace_test1() {
    char a[] = "Java";
    char *res = findSpace(a);
    char *end = a + sizeof(a) - 1;

    assert(res == end);
}

void findSpace_test2() {
    char a[] = "GL HF";
    char *res = findSpace(a);

    assert(res == a + 2);
}

void findSpace_tests() {
    findSpace_test1();
    findSpace_test2();
}


void findNonSpaseRevers_tests1() {
    char a[] = "1123";
    char *rbegin = a + sizeof(a) - 1;
    char *res = findNonSpaceReverse(rbegin, a);


    assert(res == rbegin);
}


void findNonSpaseRevers_tests2() {
    char a[] = "   ";
    char *rbegin = a + sizeof(a) - 1;
    char *res = findNonSpaceReverse(rbegin, a);


    assert(res == rbegin);
}

void  findNonSpaseRevers_tests() {
    findNonSpaseRevers_tests1();
    findNonSpaseRevers_tests2();
}

void findSpaseRevers_tests1() {
    char a[] = "ssss";
    char *rbegin = a + sizeof(a) - 1;
    char *res = findSpaceReverse( rbegin, a);

    assert(res == a);
}


void findSpaseRevers_tests2() {
    char a[] = "1  1";
    char *rbegin = a + sizeof(a) - 1;
    char *res = findSpaceReverse(rbegin, a);

    assert(res == (a + 2));
}

void  findSpaseRevers_tests() {
    findSpaseRevers_tests1();
    findSpaseRevers_tests2();
}

void strcmp_test1() {
    char a[] = "Java";
    char b[] = "JavaScript";
    int res = strcmp(a, b);
    assert(res < 0);
}

void strcmp_test2() {
    char a[] = "JavaS";
    char b[] = "JavaScript";
    int res = strcmp(b, a);
    assert(res > 0);
}

void strcmp_test3() {
    char a[] = "Java";
    char b[] = "Java";
    int res = strcmp(a, b);
    assert(res == 0);
}

void strcmp_tests() {
    strcmp_test1();
    strcmp_test2();
    strcmp_test3();
}
void copy_test1() {
    char a[5] = "TREE\0";
    char b[5] = "KKKD\0";
    char *end = a + sizeof(a) - 1;
    copy(a, end, b);

    assert(strcmp(a, b) == 0);
}

void copy_test2() {
    char a[5] = "\0";
    char b[5] = "\0";
    char *end = a + sizeof(a) - 1;
    copy(a, end, b);

    assert(strcmp(a, b) == 0);
}

void copy_test3() {
    char a[8] = "BYE BYE";
    char b[8] = "???";
    char *end = a + sizeof(a) - 1;
    copy(a, end, b);

    assert(strcmp(a, b) == 0);
}
void copy_tests() {
    copy_test1();
    copy_test2();
    copy_test3();
}

int isTwo(int x) {
    return x == 2 ? 1 : 0;
}

void copyIF_test1() {
    char a[] = {2, 2, 2, 0, 0};
    char b[5];
    char *end = copyIf(a, a + 5, b, isTwo);

    *end = '\0';

    assert(b[0] == 2);
    assert(b[1] == 2);
    assert(b[2] == 2);
    assert(strlen_(b) == 3);
}

void copyIF_test2() {
    char a[] = {1, 4, 6, 0, 0};
    char b[5];
    char *end = copyIf(a, a + 5, b, isTwo);

    *end = '\0';

    assert(strlen_(b) == 0);
}


void copyIF_tests() {
    copyIF_test1();
    copyIF_test2();
}


int isNotTwo(int x) {
    return x != 2 ? 1 : 0;
}

void copyIF_revers_test1() {
    char a[] = {1, 2, 3, 42, 2};
    char b[5];
    char *begin = copyIfReverse(a + 4, a, b, isNotTwo);

    *begin = '\0';

    assert(strlen_(b) == 2);
}

void copyIF_revers_test2() {

    char a[] = {2, 2, 2, 2, 2};
    char b[5];
    char *begin = copyIfReverse(a + 4, a, b, isNotTwo);

    *begin = '\0';

    assert(strlen_(b) == 0);
}

void copyIF_revers_tests() {
    copyIF_revers_test1();
    copyIF_revers_test2();
}

void string_tests() {
    strlen_tests();
    find_tests();
    findNonSpace_tests();
    findSpace_tests();
    findNonSpaseRevers_tests();
    findSpaseRevers_tests();
    strcmp_tests();
    copy_tests();
    copyIF_tests();
    copyIF_revers_tests();
}

void test_assertString() {
    char s[] = "321Hi";
    ASSERT_STRING("321Hi", s);
}

void test_deleteExtraSpase() {
    char s[] = "Hi      Men   ";
    removeExtraSpaces(s, getEndOfString(s), s);
    ASSERT_STRING("Hi Men", s);
}

void test_digitToStart() {
    char s[] = "d2d2 22dd 1ffs2";
    digitToStart(s);
    ASSERT_STRING("22dd 22dd 12ffs", s);
}

void test_digitsReplaceSpase() {
    char s[] = "a2a1a";
    digitsReplaceSpace(s);
    ASSERT_STRING("a  a a", s);
}

void test_replace() {
    char s[] = "zxc";
    char *w1 = "zxc";
    char *w2 = "bubuntu";
    replace(s, w1, w2);
    ASSERT_STRING("bubuntu", s);
}

void test_isSortedWords() {
    char s[] = "a b c";
    int res = isSortWords(s);
    assert(res == 1);

    char x[] = "simple apex donk";
    int res_2 = isSortWords(x);;
    assert(res_2 == 0);
}

int main() {
    test_isSortedWords();
    test_replace();
    test_digitToStart();
    test_digitsReplaceSpase();
    test_deleteExtraSpase();
    test_assertString();
    string_tests();
}
