import os
import re
import signal
from pathlib import Path
from display import Display as d
from input_tab import INPUT as it
from input_tab import ERROR_TYPE as err_t

class SubprocessManager:

    def __init__(self, file, code, output):
        self.file          = file
        self.file_basename = os.path.splitext(file)[0]   # without extension
        self.code          = code
        self.output        = output
        self.input_folder  = os.path.dirname(os.path.abspath(__file__)) + '/input/'
        self.output_folder = os.path.dirname(os.path.abspath(__file__)) + '/output/'

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
        return it[self.file]['error']

    def err_type_expected(self):
        err_type = it[self.file]['error_type']
        return err_t[err_type]

    def err_nbline_expected(self):
        return it[self.file]['error_line']

    def err_output_expected(self):
        return "Error line " + str(self.err_nbline_expected()) + ": " + self.err_type_expected()

    def err_output_printed(self):
        lines = self.output.decode('ascii').split('\n')
        for line in lines:
            if re.search("^Error line (\d)+:\s", line) != None:
                return line
        return None

    def is_correct_err_output(self):
        return self.err_output_printed() == self.err_output_expected()

    def file_created(self):
        file = Path(self.input_folder + self.file_basename + '.cor')
        return file.is_file()

    def print_parsing_test_rslt(self):
        # if correct output printed and no file was created : OK
        if self.is_correct_err_output() and self.file_created() == False:
            d.print_ok()
        else:
            d.print_failure("KO")
            if self.is_correct_err_output() == False:
                print("-> Should return an error")
                print("   your output:    ", self.err_output_printed())
                print("   expected output:", self.err_output_expected())
            if self.file_created() == True:
                print("-> Should not create a file", self.file_basename + ".cor")


    def print_result(self):
        # if this test should return an error = parsing test
        if self.is_parsing_test():
            self.print_parsing_test_rslt()
        else:
            print("FILE TEST")
            # print_file_test_rslt(self.output)



