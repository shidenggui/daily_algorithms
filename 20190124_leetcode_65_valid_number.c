/*
 * leading zeros
 * sign [optional] [+, -]
 * number1 -------
 * . [optional]  |--> at least have one part (use is_number flag to stimulate or)
 * number2 -------
 * e [optional]
 *   number [if has e, must have number part]
 * trailing zeros
 */
bool isNumber(char* s) {
    if (!s)
        return false;
    
    while (*s == ' ') s++;
    if (*s == '+' || *s == '-')
        s++;
    
    bool is_number = false;
    while (isdigit(*s)) {
        is_number = true;
        s++;
    }
    if (*s == '.')
        s++;
    while (isdigit(*s)) {
        is_number = true;
        s++;
    }
    if (!is_number)
        return false;
    if (*s == 'e') {
        s++;
        
        if (*s == '-' || *s == '+')
            s++;
        is_number = false;
        while (isdigit(*s)) {
            is_number = true;
            s++;
        }
    }
    while (*s == ' ') s++;
    return is_number && *s == '\0';
}
