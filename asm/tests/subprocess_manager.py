import os
import re
import signal
import filecmp
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

    # == UTILS =================================================================

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

    def is_correct_file_output(self):
        file = self.file_basename + ".cor"
        return filecmp.cmp(self.output_folder + file, self.input_folder + file)

    def output_file_exists(self):
        file = Path(self.output_folder + self.file_basename + '.cor')
        return file.is_file()

    # == TEST WITH ERROR =======================================================

    def get_parsing_test_rslt(self):
        # if correct output printed and no file was created : OK
        if self.is_correct_err_output() and self.file_created() == False:
            d.print_success("OK")
            return 0
        else:
            d.print_failure("KO")
            if self.is_correct_err_output() == False:
                print("-> Should return an error")
                print("   your output:    ", self.err_output_printed())
                print("   expected output:", self.err_output_expected())
            if self.file_created() == True:
                print("-> Should not create a file", self.file_basename + ".cor")
            return 1

    # == TEST WITH FILE ========================================================

    def get_file_test_rslt(self):
        # if no error returned + file created + file ok : OK
        if self.err_output_printed() == None and self.file_created() and self.is_correct_file_output():
            d.print_success("OK")
            return 0
        else:
            d.print_failure("KO")
            if self.err_output_printed() != None:
                print("-> Should not return an error")
            if self.file_created() == False:
                print("-> Should create a file", self.file_basename + ".cor")
            elif self.is_correct_file_output() == False:
                print("-> Your output file (input/" + self.file_basename + ".cor) is different from the expected output (output/" + self.file_basename + ".cor)")
            return 1

    # == PROCESS A TEST ========================================================

    def get_result(self):
        # If this test should return an error = it's a parsing test
        if self.is_parsing_test():
            return self.get_parsing_test_rslt()
        # If this test should created a .cor file
        else:
            # Check if there is an expected output in 'output/' folder
            if self.output_file_exists():
                return self.get_file_test_rslt()
            else:
                d.print_warning("File " + self.file_basename + ".cor not found in output folder")
                return 1

    # == IF EXCEPTION RAISED ===================================================

    # If code < 0 -> signal (python convention)
    # If code = 1 or 255, it means the program returned 1 or -1 (typically when there is an error)
    def get_rslt_when_exception(self):
        if self.code == -signal.SIGSEGV:
            d.print_failure('SEGFAULT')
            return 1
        elif self.code == -signal.SIGABRT:
            d.print_failure('SIGABORT')
            return 1
        elif self.code < 0 :
            d.print_failure('Signal caught (' + str(self.code) + ')')
            return 1
        elif self.code == 1 or self.code == 255:
            return self.get_result()
        else:
            d.print_failure('Returned a wrong exit code (' + str(self.code) + ')')
            return 1


