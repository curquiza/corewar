# Lib
import os
import subprocess
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
        spm.print_exit_code_error()
    else:
        spm = SubprocessManager(file, 0, output)
        spm.print_result()

def tests_loop():
    # For each file in 'input' folder
    input_files = sorted(os.listdir(input_path))
    for file in input_files:
        d.print_filename(file)
        # If file does not exist in INPUT table.
        if file not in it.INPUT:
            d.print_warning('Data not found for this file')
        else:
            test_processing(file)

def main():
    # Check if file 'asm' exists
    asm_file = Path(asm_bin)
    if asm_file.is_file():
        tests_loop()
    else:
        d.stderr_print("Error : binary 'asm' does not exist.")

if __name__ == '__main__':
    main()
