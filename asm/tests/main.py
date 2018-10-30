import os
import subprocess
import input_tab as it
from display import Display as d

asm_cmd = './asm'
input_folder = 'input/'
# input_files = sorted(os.listdir(input_folder))

def test_processing(file):
    try:
        print(asm_cmd + ' ' + input_folder + file)
        output = subprocess.check_output([asm_cmd + ' ' + input_folder + file], shell=True, stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as exc:
        print("Y'a un beans")
        # ft.manage_error_returns(file, exc.output, exc.returncode)
    # ft.print_rslt(filename, output)


def main():
    print(__file__)
    # For each file in 'input' folder
    # for file in input_files:
        # filename = os.path.splitext(file)[0]
        # d.print_noendl(file)
        # If the file does not exist in INPUT table.
        # if file not in it.INPUT:
            # print(d.WARNING + 'Data not found for this map' + d.ENDC)
        # else:
            # test_processing(file)

if __name__ == '__main__':
    main()
