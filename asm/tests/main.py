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
    # try:
        # output = subprocess.check_output([asm_bin + ' ' + input_path + file], shell=True, stderr=subprocess.STDOUT)
        # # output = subprocess.check_output(['./lem-in < parsing_wrong_tube_1.txt'], shell=True, stderr=subprocess.STDOUT)
    # except subprocess.CalledProcessError as exc:
        # print("OUTPUT")
        # print(exc.output)
        # print("CODE")
        # print(exc.returncode)
    # else:
        # print("Tout roule")
        # print(output)
    # shell=True : interpret command in shell
    # stderr=subprocess.STDOUT : stderr in stdout
    try:
        # output = subprocess.run(['./asm'], stderr=subprocess.STDOUT, check=True).stdout
        output = subprocess.check_output([asm_bin + ' ' + input_path + file], shell=True, stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as exc:
        print("OUTPUT")
        print(exc.output)
        print("CODE")
        print(exc.returncode)
    else:
        print("Tout roule")

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
