def to_roman(number):
    """
    >>> all(to_arabic(to_roman(i)) == i for i in range(1, 4000))
    True
    """

    # we only allow int
    if not type(number) is int:
        raise TypeError('number must be an integer')

    if number >= 4000:
        raise ValueError('number is too big')

    result = ''
    letters = 'MDCLXVI'
    divisor = 1000
    pos = 0

    while number > 0:
        digit, number = divmod(number, divisor)
        if digit:
            if digit < 4:
                value = letters[pos] * digit
            elif digit == 4:
                value = letters[pos] + letters[pos-1]
            elif digit == 5:
                value = letters[pos-1]
            elif digit < 9:
                value = letters[pos-1] + letters[pos] * (digit - 5)
            else:
                value = letters[pos] + letters[pos-2]
            result += value

        divisor //= 10
        pos += 2

    return result


roman_to_arabic_table = {'I': 1,'V': 5,'X': 10,'L': 50,'C': 100,'D': 500,'M': 1000}

def to_arabic(roman):
    """
    >>> to_arabic('I')
    1
    >>> to_arabic('II')
    2
    >>> to_arabic('III')
    3
    >>> to_arabic('IV')
    4
    >>> to_arabic('V')
    5
    >>> to_arabic('VI')
    6
    >>> to_arabic('VII')
    7
    >>> to_arabic('VIII')
    8
    >>> to_arabic('IX')
    9
    >>> to_arabic('X')
    10
    >>> to_arabic('XIV')
    14
    >>> to_arabic('XV')
    15
    >>> to_arabic('XXXIX')
    39
    >>> to_arabic('XL')
    40
    """

    if len(roman) == 0:
        return 0

    result = prev_value = 0

    for char in reversed(roman.upper()):
        value = roman_to_arabic_table.get(char)
        if value is None:
            raise ValueError('Invalid letter "%s" found' % char)

        if prev_value > value:
            result -= value
        else:
            result += value
            prev_value = value

    return result
