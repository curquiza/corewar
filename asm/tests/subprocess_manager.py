import re
import signal
from display import Display as d
from input_tab import INPUT as it
from input_tab import ERROR_TYPE as err_t

class SubprocessManager:

    def __init__(self, filename, code, output):
        self.filename = filename
        self.code     = code
        self.output   = output

    # == IF EXCEPTION RAISED ===================================================

    # if code < 0 -> signal (python convention)
    def print_exit_code_error(self):
        if self.code == -signal.SIGSEGV:
            d.print_failure('SEGFAULT')
        elif self.code == -signal.SIGABRT:
            d.print_failure('SIGABORT')
        elif self.code < 0 :
            d.print_failure('Signal caught (' + str(self.code) + ')')
        else:
            d.print_failure('Returned a wrong exit code (' + str(self.code) + ')')

    # ==========================================================================

    def is_parsing_test(self):
        return it[self.filename]['error']

    def error_msg_expected(self):
        err_type = it[self.filename]['error_type']
        return err_t[err_type]

    def error_line_expected(self):
        return it[self.filename]['error_line']

    def get_output_err_line(self):
        # m = re.search('*Error*\n', self.output)
        print("titi")
        # print(m.group(0))
        return ""

    def print_parsing_test_rslt(self):
        print("PARSING TEST")
        print("msg expected:" + self.error_msg_expected())
        print("line expected:" + str(self.error_line_expected()))
        self.get_output_err_line()


    def print_result(self):
        # if this test should return an error = parsing test
        if self.is_parsing_test():
            self.print_parsing_test_rslt()
        else:
            d.print_ok()
            # print_file_test_rslt(self.output)



