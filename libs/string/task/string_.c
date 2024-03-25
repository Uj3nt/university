#include "string_.h"

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;


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
        copy(source, getEndOfString(source) + 1, stringBuffer);
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

    while (getWord(s,&w1)) {
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
        bag->size = i;
    }

}

// task 8

int isPakindromeWorld(WordDescriptor *word) {
    int word_len = word->end - word->begin;
    for (int i = 0; i < word_len/2; ++i) {
        if ( *(word->begin + i) != *(word->end - i - 1) ) {
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

    while (getWord(BeginWord,&word)) {
        if (isPakindromeWorld(&word)) {
            counter++;
        }
        BeginWord = word.end;
    }
    return  counter;
}

// task 9

void *GetStringFrom2(char *s1, char *s2, char *res) {
    WordDescriptor word1, word2;
    int isW1Found, isW2Found;
    char *beginSearch1 = s1, *beginSearch2 = s2;
    char* WritePtr = res;

    while ((isW1Found = getWord(beginSearch1, &word1)), (isW2Found = getWord(beginSearch2, &word2)), isW1Found || isW2Found) {
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

    word->begin = findSpaceReverse(rbegin- 1, rend);

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
