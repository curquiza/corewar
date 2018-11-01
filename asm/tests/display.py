import sys

class Display:

    HEADER    = '\033[95m'
    OKBLUE    = '\033[94m'
    OKGREEN   = '\033[92m'
    WARNING   = '\033[93m'
    FAIL      = '\033[91m'
    END       = '\033[0m'
    BOLD      = '\033[1m'
    UNDERLINE = '\033[4m'

    def print_noendl(str):
        print(str, end='', flush=True)
        # sys.stdout.write(str) # -> troubles with binary string

    def stderr_print(str):
        sys.stderr.write(str + '\n')
