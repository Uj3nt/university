#include "string_.h"

#define COUNT_LETTERS 26
#define DIFFERENCE_CHAR 65
typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

BagOfWords _bag;
BagOfWords _bag2;

int compare_char(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

size_t strlen_v1(char *s) {
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

size_t strlen_v2(char *s) {
    int i = 0;
    while (*s != '\0') {
        i++;
        s++;
    }
    return i;
}

size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

char *find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}

char *findNonSpace(char *begin) {
    while (isspace(*begin) && *begin != '\0') {
        begin++;
    }
    return begin;
}

char *findSpace(char *begin) {
    while (!isspace(*begin) && *begin != '\0') {
        begin++;
    }
    return begin;
}

char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (isspace(*rbegin) && rbegin <= rend) {
        rbegin--;
    }
    return rbegin;
}

char *findSpaceReverse(char *rbegin, const char *rend) {
    while (!isspace(*rbegin) && rbegin != rend) {
        rbegin--;
    }
    return rbegin;
}

int strcmp(const char *lhs, const char *rhs) {
    while (*lhs && *rhs && *rhs == *lhs) {
        lhs++;
        rhs++;
    }

    return *lhs - *rhs;
}


int strncmp(const char *str1, const char *str2, size_t n) {
    char *end = str1 + n;
    int result = 0;

    for (; result == 0 && str1 != end && (*str1 || *str2); result = *(str1++) - *(str2++));

    return result;
}

char *copy(const char *beginSource, const char *endSource, char *beginDestination) {
    size_t size = endSource - beginSource;
    memcpy(beginDestination, beginSource, size);

    return beginDestination + size;
}

char *copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    while (beginSource <= endSource) {
        if (f(*beginSource)) {
            *beginDestination = *beginSource;
            beginDestination++;
        }

        beginSource++;
    }

    return beginDestination;
}

char *copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)) {
    while (rbeginSource != rendSource) {
        if (f(*rbeginSource)) {
            *beginDestination = *rbeginSource;
            beginDestination++;
        }

        rbeginSource--;
    }

    return beginDestination;
}


// string task1

char *getEndOfString(char *s) {
    return s + strlen_(s) - 1;
}

void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

// string task2

void removeExtraSpaces(char *beginSource, char *endSource, char *beginDestination) {
    while (beginSource != endSource) {
        if (!isspace(*beginSource) || !isspace(*(beginSource + 1))) {
            *beginDestination = *beginSource;
            beginDestination++;
        }

        beginSource++;
    }
    *beginDestination = '\0';
}

// string task3

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);

    if (*word->begin == '\0') {
        return 0;
    }
    word->end = findSpace(word->begin);

    return 1;
}

void digitToStartWord(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end, stringBuffer);
    *endStringBuffer = '\0';
    char *recPosition = copyIf(stringBuffer, endStringBuffer, word.begin, isdigit);
    copyIf(stringBuffer, endStringBuffer, recPosition, isalpha);
}

void digitToStart(char *beginString) {
    char *beginSearch = beginString;
    WordDescriptor word;
    while (getWord(beginSearch, &word)) {
        digitToStartWord(word);
        beginSearch = word.end;
    }
}

// task 4


char *digitReplaceSpace(char *s, char *prtWrite) {
    for (int i = 0; i < *s - 48; ++i) {
        *prtWrite = ' ';
        prtWrite++;
    }
    return prtWrite;
}

void digitsReplaceSpace(char *s) {
    char *ptrWrite = s;
    char *ptrRead = stringBuffer;
    char *endStringBuffer = copy(s, getEndOfString(s) + 1, ptrRead);

    while (ptrRead <= endStringBuffer) {
        if (isdigit(*ptrRead)) {
            ptrWrite = digitReplaceSpace(ptrRead, ptrWrite);
        } else {
            *ptrWrite = *ptrRead;
            ptrWrite++;
        }
        ptrRead++;
    }
    *ptrWrite = '\0';
}

// task 5

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);

    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};

    char *readPtr, *recPtr;

    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        char *endW1copy = copy(source, getEndOfString(source) + 1, stringBuffer);
        *endW1copy = '\0';
        readPtr = stringBuffer;
        recPtr = source;

    }

    while (*readPtr != '\0') {
        if (strncmp(readPtr, w1, w1Size) == 0) {
            copy(word2.begin, word2.end, recPtr);
            readPtr += w1Size;
            recPtr += w2Size;
        } else {
            *recPtr = *readPtr;
            readPtr++;
            recPtr++;
        }
    }

    *recPtr = '\0';
}

// task 6

int isSortWords(char *s) {
    WordDescriptor w1;
    WordDescriptor w2;

    while (getWord(s, &w1)) {
        if (getWord(w1.end, &w2)) {
            if (*w1.begin > *w2.begin) {
                return 0;
            }
        }
        s = w1.end;
    }

    return 1;
}

// task 7

void getBagOfWords(BagOfWords *bag, char *s) {
    char *readPtr = s;
    WordDescriptor word;
    for (int i = 0; getWord(readPtr, &word); i++) {
        bag->words[i].begin = word.begin;
        bag->words[i].end = word.end;
        bag->size = i + 1;
        readPtr = word.end;
    }

}

// task 8

int isPakindromeWorld(WordDescriptor *word) {
    int word_len = word->end - word->begin;
    for (int i = 0; i < word_len / 2; ++i) {
        if (*(word->begin + i) != *(word->end - i - 1)) {
            return 0;
        }
    }
    return 1;
}


int GetCountPalindromesInString(char *s) {
    replace(s, ",", " ");
    WordDescriptor word;
    char *BeginWord = s;
    int counter = 0;

    while (getWord(BeginWord, &word)) {
        if (isPakindromeWorld(&word)) {
            counter++;
        }
        BeginWord = word.end;
    }
    return counter;
}

// task 9

void *GetStringFrom2(char *s1, char *s2, char *res) {
    WordDescriptor word1, word2;
    int isW1Found, isW2Found;
    char *beginSearch1 = s1, *beginSearch2 = s2;
    char *WritePtr = res;

    while ((isW1Found = getWord(beginSearch1, &word1)), (isW2Found = getWord(beginSearch2, &word2)), isW1Found ||
                                                                                                     isW2Found) {
        if (isW1Found) {
            WritePtr = copy(word1.begin, word1.end, WritePtr);
            *WritePtr++ = ' ';
            beginSearch1 = word1.end;
        }

        if (isW2Found) {
            WritePtr = copy(word2.begin, word2.end, WritePtr);;
            *WritePtr++ = ' ';
            beginSearch2 = word2.end;
        }
    }
    *(--WritePtr) = '\0';
}

// task 10

int getWordReverse(char *rbegin, char *rend, WordDescriptor *word) {
    word->end = findNonSpaceReverse(rbegin, rend);

    if (word->end == rend)
        return 0;

    word->begin = findSpaceReverse(rbegin - 1, rend);

    return 1;
}

void getStringRevers(char *s) {
    WordDescriptor word;

    char *WritePtr = s;
    char *rend = stringBuffer;
    char *rbegin = copy(s, getEndOfString(s) + 1, stringBuffer);


    while (getWordReverse(rbegin, rend, &word)) {
        WritePtr = copy(word.begin, word.end, WritePtr);
        rbegin = word.begin;
        *WritePtr++ = ' ';
    }
    *(--WritePtr) = '\0';
    replace(s, "  ", " ");
}


// task 11

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;


int SymbolIn(char *begin, char *end, int ch) {
    while (begin != end && (toupper(*begin)) != toupper(ch))
        begin++;
    return begin != end;
}


WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w) {
    int isWordInString = getWord(s, w) == 1;

    if (isWordInString && !SymbolIn(w->begin, w->end, 'a')) {
        WordDescriptor copy_w;

        if (getWord(w->end, &copy_w) == 1) {
            if (SymbolIn(copy_w.begin, copy_w.end, 'a')) {
                return WORD_FOUND;
            } else {
                return getWordBeforeFirstWordWithA(w->end, w);
            }

        } else {
            return NOT_FOUND_A_WORD_WITH_A;
        }

    } else if (isWordInString) {
        return FIRST_WORD_WITH_A;
    } else {
        return EMPTY_STRING;
    }
}

// task 12
void wordDescriptorToString(WordDescriptor *word,char *string) {
    char *end = copy(word->begin, word->end, string);
    *end = '\0';
}


WordDescriptor lastWordInFirstStringInSecondString(char *s1, char *s2) {
    getBagOfWords(&_bag,s1 );
    getBagOfWords(&_bag2,s2 );

    for (int i = 0; i < _bag.size; ++i) {
        WordDescriptor word1 = _bag.words[_bag.size - i - 1];


        for (int j = 0; j < _bag2.size; ++j) {
            WordDescriptor word2 = _bag2.words[j];


            if (!strncmp(word1.begin, word2.begin,word1.end - word1.begin )) {
                return _bag.words[_bag.size - i - 1];
            }
        }
    }

    WordDescriptor res;
    char *res_s = "EMPTY";
    getWord(res_s, &res);
    return res;

}

// task 13

int UniqueWordsInString(char *s) {
    BagOfWords bag;
    getBagOfWords(&bag, s);

    for (int i = 0; i < bag.size; ++i) {
        for (int j = i + 1; j < bag.size; ++j) {
            int size_word_1 = bag.words[i].end - bag.words[i].begin;
            int size_word_2 = bag.words[j].end - bag.words[j].begin;
            int max_size_words = size_word_1 > size_word_2 ? size_word_1 : size_word_2;

            if (!strncmp(bag.words[i].begin, bag.words[j].begin, max_size_words)) {
                return 0;
            }
        }
    }
    return 1;
}

// task 14

int checkWordsInStringHaveCommonLetters(char *s) {
    getBagOfWords(&_bag, s);
    for (int i = 0; i < _bag.size; ++i) {
        WordDescriptor word = _bag.words[i];
        qsort(word.begin, word.end - word.begin, sizeof(char), compare_char);
    }

    for (int i = 0; i < _bag.size; ++i) {
        for (int j = i + 1; j < _bag.size; ++j) {
            int size_word_1 = _bag.words[i].end - _bag.words[i].begin;
            int size_word_2 = _bag.words[j].end - _bag.words[j].begin;
            int max_size_words = size_word_1 > size_word_2 ? size_word_1 : size_word_2;

            if (!strncmp(_bag.words[i].begin, _bag.words[j].begin, max_size_words)) {
                return 1;
            }
        }
    }
    return 0;
}

// task 15

int getSizeWord(WordDescriptor word) {
    return word.end - word.begin;
}

void GetStringWithoutLastWord(char *s,char *res) {
    char *writePtr = res;
    getBagOfWords(&_bag,s);
    WordDescriptor last_word = _bag.words[_bag.size - 1];

    int size_last_word  = getSizeWord(last_word);
    for (int i = 0; i < _bag.size - 1; ++i) {
        if (strncmp(_bag.words[i].begin, last_word.begin, size_last_word) != 0) {
            writePtr = copy(_bag.words[i].begin, _bag.words[i].end, writePtr);
            *(writePtr++) = ' ';
        }
    }
    *(--writePtr) = '\0';
}

// task 16

int ThisWordInBag(BagOfWords bag, WordDescriptor word) {
    for (int i = 0; i < bag.size; i++) {
        if (strncmp(word.begin, bag.words[i].begin, getSizeWord(word)) == 0) {
            return 1;
        }
    }
    return 0;
}

WordDescriptor GetWordBeforeUnionWord(char *s1, char *s2) {
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);

    for (int i = 0; i < _bag.size; ++i) {
        if (ThisWordInBag(_bag2, _bag.words[i])) {
            if (i != 0) {
                return  _bag.words[i  - 1];
            } else {
                continue;
            }
        }
    }
    WordDescriptor error_word = {NULL, NULL};
    return error_word;
}

// task 17

void DeletePalindromeInString(char *s) {
    char *ptrWrite = s;
    char *ptrRead = stringBuffer;
    copy(s, getEndOfString(s) + 1, ptrRead);

    getBagOfWords(&_bag, ptrRead);

    for (int i = 0; i < _bag.size; ++i) {
        if (!isPakindromeWorld(&_bag.words[i])) {
            ptrWrite = copy(_bag.words[i].begin, _bag.words[i].end, ptrWrite);
            *(ptrWrite++) = ' ';
        }
    }
    *(--ptrWrite) = '\0';
}

// 18 task

void addWordToLessString(char *s1, char *s2) {
    char *ptrWrite;

    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);

    int IsString1More = _bag.size > _bag2.size ? 1 : 0;
    size_t difSize = IsString1More ? _bag.size - _bag2.size : _bag2.size - _bag.size;

    if (IsString1More) {
        ptrWrite = _bag2.words[_bag2.size - 1].end;

        for (int i = 0; i < difSize; ++i) {
            *(ptrWrite++) = ' ';
            ptrWrite = copy(_bag.words[_bag2.size + i ].begin, _bag.words[_bag2.size + i].end, ptrWrite);
        }

    } else {
        ptrWrite = _bag.words[_bag.size - 1].end;

        for (int i = 0; i < difSize; ++i) {
            *(ptrWrite++) = ' ';
            ptrWrite = copy(_bag2.words[_bag.size + i].begin, _bag2.words[_bag.size + i].end, ptrWrite);
        }
    }

    *ptrWrite = '\0';

}

// task 19

int allSymbolsWordInString(char *s, char *word) {
    bitset letters_s = bitset_create(COUNT_LETTERS);
    bitset letters_word = bitset_create(COUNT_LETTERS);

    for (int i = 0; i < strlen_(s); ++i) {
        char symbol = toupper(s[i]);
        if (isalpha(symbol)) {
            bitset_insert(&letters_s, (symbol - DIFFERENCE_CHAR));
        }
    }

    for (int i = 0; i < strlen_(word); ++i) {
        char symbol = toupper(word[i]);
        if (isalpha(symbol)) {
            bitset_insert(&letters_word, (int) (symbol - DIFFERENCE_CHAR));
        }
    }

    bitset res = bitset_intersection(letters_s, letters_word);

    return bitset_isEqual(res, letters_word);
}

// replace v2.0

char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}





