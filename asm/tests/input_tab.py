# Each error message must (at least) contain this kind of line :
# Error line [line]: [message].
# ex : Error line 3: Wrong number of parameters for this intruction.
# This line will be compared. Give the error type and the line of the error in INPUT.

ERROR_TYPE = {
    'NO_NAME':              'Name was expected in the source file.',
    'NO_COMMENT':           'Comment was expected in the source file.',
    'BAD_QUOTES' :          'Bad quoting.',
    'BIG_NAME' :		    'Name is too long.',
    'BIG_COMMENT' :		    'Comment is too long.',
    'INVALID_CHAR' :        'Invalid character.'

    # 'PARAM_NB':             'Wrong number of parameters for this intruction.'
}

INPUT = {
    # 'zork.s':       {'error': False, 'error_type': None, 'error_line': -1},
    'name.none.s':    {'error': True,  'error_type': 'NO_NAME', 'error_line': 1},
    'name.too_long.s':    {'error': True,  'error_type': 'BIG_NAME', 'error_line': 1},
    'name.bad_quoting.s':    {'error': True,  'error_type': 'BAD_QUOTES', 'error_line': 1},
    'name.bad_quoting.1.s':    {'error': True,  'error_type': 'BAD_QUOTES', 'error_line': 1},
    'name.bad_quoting.2.s':    {'error': True,  'error_type': 'BAD_QUOTES', 'error_line': 1},
    'name.instr_before.s':    {'error': True,  'error_type': 'NO_NAME', 'error_line': 3},
    'comment.none.s':    {'error': True,  'error_type': 'NO_COMMENT', 'error_line': 3},
    'comment.too_long.s':    {'error': True,  'error_type': 'BIG_COMMENT', 'error_line': 2},
    'comment.bad_quoting.s':    {'error': True,  'error_type': 'BAD_QUOTES', 'error_line': 2},
    'comment.bad_quoting.1.s':    {'error': True,  'error_type': 'BAD_QUOTES', 'error_line': 2},
    'comment.bad_quoting.2.s':    {'error': True,  'error_type': 'BAD_QUOTES', 'error_line': 2},
    'comment.instr_before.s':    {'error': True,  'error_type': 'NO_COMMENT', 'error_line': 2},
    'lexer.bad_char.s':    {'error': True,  'error_type': 'INVALID_CHAR', 'error_line': 4},
    'lexer.empty.s':    {'error': False,  'error_type': None, 'error_line': -1},
}
