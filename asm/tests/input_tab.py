# Each error message must (at least) contain this kind of line :
# Error line [line]: [message].
# ex : Error line 3: Wrong number of parameters for this intruction.
# This line will be compared. Give the error type and the line of the error in INPUT.

ERROR_TYPE = {
    'NO_NAME':              'Name was expected in the source file.',
    'NO_COMMENT':           'Comment was expected in the source file.',
    'NAME_TOO_LARGE':       'Name is too long.',
    'COMMENT_TOO_LARGE':    'Comment is too long.',
    'BAD_QUOTES' :          'Bad quoting.'
    # 'PARAM_NB':             'Wrong number of parameters for this intruction.'
}

INPUT = {
    'zork.s':       {'error': False, 'error_type': None, 'error_line': -1},
    'no_name.s':    {'error': True,  'error_type': 'NO_NAME', 'error_line': 0},
}
