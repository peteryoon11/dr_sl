// Copyright (C) 2016 David Reid. See included LICENSE file.

namespace drsl
{

/**
*   \brief                 Finds the first occurance of a character inside a string.
*   \param  str       [in] The string to look for the character in.
*   \param  character [in] The character to look for.
*   \param  strLength [in] The length in T's of the string, not including the null terminator.
*   \return                If the character is found, returns a pointer to that character. Otherwise, a NULL pointer is returned.
*/
template <typename T>
inline T * findfirst(T *str, char32_t character, size_t strLength = -1)
{
    T *temp = str;

    char32_t ch;
    while (strLength > 0 && (ch = nextchar(temp)) != '\0')
    {
        if (ch == character)
        {
            return str;
        }

        strLength -= temp - str;
        str = temp;
    }

    return NULL;
}

// Optimized cases.
#ifdef DRSL_ONLY_ASCII
inline const char * findfirst(const char *str, char32_t character)
{
    return ::strchr(str, character);
}
inline char * findfirst(char *str, char32_t character)
{
    return ::strchr(str, character);
}
#endif
inline const wchar_t * findfirst(const wchar_t *str, char32_t character)
{
    return ::wcschr(str, (wchar_t)character);
}
inline wchar_t * findfirst(wchar_t *str, char32_t character)
{
    return ::wcschr(str, (wchar_t)character);
}

template <typename T>
inline T * findfirst(const reference_string<T> &str, char32_t character)
{
    return findfirst(str.start, character, length(str));
}


/**
*   \brief                  Finds a string from within another string.
*   \param  str1       [in] The string to be scanned.
*   \param  str2       [in] The string to look for inside \c str1.
*   \param  str1Length [in] The length in T's of the first string, not including the null terminator.
*   \param  str2Length [in] The length in T's of the first string, not including the null terminator.
*   \return                 A pointer to the first occurance of \c str2; or NULL if the string is not found.
*/
template <typename T>
inline const T * findfirst(const T *str1, const T *str2, size_t str1Length = -1, size_t str2Length = -1)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    if (str2Length == 0 || *str2 == 0)
    {
        return str1;
    }

    // We need to know the length of the second string.
    if (str2Length == (size_t)-1)
    {
        str2Length = length(str2);
    }

    // Grab the first character of our second string.
    char32_t first_char = drsl::getchar(str2, 0);

    for ( ; (str1 = findfirst(str1, first_char, str1Length)) != NULL; nextchar(str1))
    {
        if (compare(str1, str2, str2Length) == 0)
        {
            return str1;
        }
    }

    return NULL;
}

// Optimized case.
inline const char * findfirst(const char *str1, const char *str2)
{
    // This function should work all the time.
    return ::strstr(str1, str2);
}
inline const wchar_t * findfirst(const wchar_t *str1, const wchar_t *str2)
{
    return ::wcsstr(str1, str2);
}


template <typename T>
inline T * findfirst(T *str1, const T *str2, size_t str1Length = -1, size_t str2Length = -1)
{
    return (T *)findfirst((const T *)str1, str2, str1Length, str2Length);
}

// Optimized case
inline char * findfirst(char *str1, const char *str2)
{
    // This function should work all the time.
    return ::strstr(str1, str2);
}
inline wchar_t * findfirst(wchar_t *str1, const wchar_t *str2)
{
    return ::wcsstr(str1, str2);
}


template <typename T>
inline T * findfirst(const reference_string<T> &str1, const reference_string<T> &str2)
{
    return findfirst(str1.start, str2.start, length(str1), length(str2));
}





/**
*   \brief                 Retrieves the first occurance of the specified character in a string.
*   \param  str       [in] The string to search.
*   \param  character [in] The character to look for.
*   \param  strLength [in] The length in T's of the string, not including the null terminator.
*   \return                A pointer in \c str to the fist occurance of the character.
*
*   \remarks
*       This function is functionally equivalent to findfirst(const T *, char32_t, size_t).
*/
template <typename T>
inline T * findfirstof(T *str, char32_t character, size_t strLength = -1)
{
    return drsl::findfirst(str, character, strLength);
}


/**
*   \brief                 Retrieves the first occurance in a string of any character contained in another string.
*   \param  str       [in] Null terminated string to search.
*   \param  charSet   [in] The set of characters to look for in \c str.
*   \param  strLength [in] The length in T's of the string, not including the null terminator.
*   \param  setLength [in] The length in T's of the character set string, not including the null terminator.
*   \return                A pointer in \c str to the first occurance of any character in \c charSet; or NULL if no characters are found.
*/
template <typename T>
inline const T * findfirstof(const T *str, const T *charSet, size_t strLength = -1, size_t setLength = -1)
{
    const T *temp = str;

    char32_t ch;
    while (strLength > 0 && (ch = nextchar(temp)) != '\0')
    {
        // Now we need to search through the character set and check if the character
        // is equal to any of those.
        const T *temp_set = charSet;

        // Stores the start of the next character.
        const T *start_of_ch2 = temp_set;

        size_t temp_length = setLength;
        char32_t ch2;
        while (temp_length > 0 && (ch2 = nextchar(temp_set)) != '\0')
        {
            if (ch2 == ch)
            {
                return str;
            }

            temp_length -= temp - str;
            start_of_ch2 = temp_set;
        }

        strLength -= temp - str;
        str = temp;
    }

    return NULL;
}

// Optimized cases.
#ifdef DRSL_ONLY_ASCII
inline const char * findfirstof(const char *str, const char *charSet)
{
    return ::strpbrk(str, charSet);
}
#endif
inline const wchar_t * findfirstof(const wchar_t *str, const wchar_t *charSet)
{
    return ::wcspbrk(str, charSet);
}

template <typename T>
inline T * findfirstof(T *str, const T *charSet, size_t strLength = -1, size_t setLength = -1)
{
    return (T *)findfirstof((const T *)str, charSet, strLength, setLength);
}

// Optimized cases.
#ifdef DRSL_ONLY_ASCII
inline char * findfirstof(char *str, const char *charSet)
{
    return ::strpbrk(str, charSet);
}
#endif
inline wchar_t * findfirstof(wchar_t *str, const wchar_t *charSet)
{
    return ::wcspbrk(str, charSet);
}

}