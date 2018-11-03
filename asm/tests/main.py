# Lib
import os
import subprocess
import sys
from pathlib import Path
# Own files
import input_tab as it
from display import Display as d
from subprocess_manager import SubprocessManager

dirpath = os.path.dirname(os.path.abspath(__file__))
input_path = dirpath + '/input/'
asm_bin = dirpath + '/../asm'

def test_processing(file):
    try:
        # shell=True : interpret command in shell
        # stderr=subprocess.STDOUT : stderr in stdout
        output = subprocess.check_output([asm_bin + ' ' + input_path + file], shell=True, stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as exc:
        spm = SubprocessManager(file, exc.returncode, exc.output)
        # print("rslt =", spm.get_rslt_when_exception())
        # return 1
        return spm.get_rslt_when_exception()
    else:
        spm = SubprocessManager(file, 0, output)
        return spm.get_result()

def tests_loop():
    # For each file in 'input' folder
    all_files = sorted(os.listdir(input_path))
    input_files = [f for f in all_files if f.endswith('.s')]
    fail_count = 0
    for file in input_files:
        d.print_filename(file)
        # If file does not exist in INPUT table
        if file not in it.INPUT:
            d.print_warning('Data not found in input table')
            fail_count += 1
        else:
            # print("test processing = ", test_processing(file))
            fail_count += test_processing(file)
    return 1 if fail_count != 0 else 0

def clean_input_folder():
    for file in os.listdir(input_path):
        if file.endswith(".cor"):
            os.remove(os.path.join(input_path, file))

def main():
    # Remove all .cor in input/
    clean_input_folder()
    # Check if file 'asm' exists
    asm_file = Path(asm_bin)
    if asm_file.is_file():
        return tests_loop()
    else:
        d.stderr_print("Error : binary 'asm' does not exist.")
        return 1

if __name__ == '__main__':
    exit_code = main()
    sys.exit(exit_code)
