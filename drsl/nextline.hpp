// Copyright (C) 2016 David Reid. See included LICENSE file.

#ifndef DRSL_NEXTLINE
#define DRSL_NEXTLINE

namespace drsl
{

/**
*   \brief             Retrieves the line that the specified string is positioned at and moves to the next one.
*   \param  line [out] The reference string that will recieve the line.
*   \param  str  [in]  The string to retrieve the line from.
*   \return            True if a line was retrieved; false otherwise.
*
*   \remarks
*       When this function returns a non-null value, the \c start elements of \c line is always set to \c str.
*       \par
*       The input string must be null terminated. The only time this function will return false is when the
*       string has no characters other than a null terminator. If this behaviour is not desireable, the
*       application will need to manually determine when nextline() should stop being called.
*       \par
*       The returned string will not contain the new-line delimiter.
*/
template <typename T>
inline bool nextline(reference_string<T> &line, T *&str)
{
    assert(str != NULL);

    if (*str == '\0')
    {
        return false;
    }

    line.start = str;

    // We need to loop through each character in the string and look for a carriage return
    // and new line character.
    T *temp = str;
    char32_t ch;
    while ((ch = nextchar(temp)) != '\0')
    {
        // We need to check for both "\r\n" and "\n" lines.
        if (ch == '\r')
        {
            // We will grab the next character. If this is equal to '\n', we have a new line.
            T *temp2 = temp;
            if (nextchar(temp2) == '\n')
            {
                // We have a new line. We will set the line and return.
                line.end = str;
                str = temp2;
                return true;
            }
        }
        else if (ch == '\n')
        {
            // We have a new line.
            line.end = str;
            str = temp;
            return true;
        }

        str = temp;
    }

    // If we've made it here, we're at the end of the string. Therefore, we
    // want to end this line and return.
    line.end = str;

    return true;
}


}

#endif // DRSL_NEXTLINE
