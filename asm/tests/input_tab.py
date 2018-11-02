# Each error message must (at least) contain this kind of line :
# Error line [line]: [message].
# ex : Error line 3: Wrong number of parameters for this intruction.
# This line will be compared. Give the error type and the line of the error in INPUT.

ERROR_TYPE = {
    'NO_NAME':              'No name found in the header.',
    'NO_COMMENT':           'No comment found in the header.',
    'NAME_TOO_LARGE':       'Name too large.',
    'COMMENT_TOO_LARGE':    'Comment too large.',
    'PARAM_NB':             'Wrong number of parameters for this intruction.'
}

INPUT = {
    'zork.s':       {'error': False, 'error_type': None,        'error_line': -1},
    'no_name.s':    {'error': True,  'error_type': 'NO_NAME', 'error_line': 0},
}
