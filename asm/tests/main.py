# Lib
import os
import subprocess
from pathlib import Path
# Own files
import input_tab as it
from display import Display as d

dirpath = os.path.dirname(os.path.abspath(__file__))
input_path = dirpath + '/input/'
asm_bin = dirpath + '/../asm'

def test_processing(file):
    try:
        output = subprocess.check_output([asm_bin + ' ' + input_path + file], shell=True, stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as exc:
        # print("Y'a un beans")
        # print ("OUTPUT")
        # d.print_noendl(exc.output)
        print(exc.output)
        # print ("CODE")
        # d.print_noendl(exc.returncode)
    else:
        print("toto")
        print(output)
        # ft.manage_error_returns(file, exc.output, exc.returncode)
    # ft.print_rslt(filename, output)

def tests_loop():
    # For each file in 'input' folder
    input_files = sorted(os.listdir(input_path))
    for file in input_files:
        filename = os.path.splitext(file)[0]
        d.print_noendl(file + " : ")
        # If file does not exist in INPUT table.
        if file not in it.INPUT:
            print(d.WARNING + 'data not found for this file' + d.END)
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
