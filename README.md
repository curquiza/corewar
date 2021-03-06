# Corewar

## Dependencies :
- gcc
- make
- ncures :  
  ```apt-get install libncurses5-dev libncursesw5-dev```
  or
  ```brew install ncurses```
  

## ASM
### Usage
```bash
./asm [file_name].s
or
./asm -a [file_name].s
```
The _a_ flag don't create a source file .cor but write to stdout an annotated version of the code.

### Tests part
#### Add a test
1) Add your input file (`.s`) in `asm/tests/input/` folder.
2) Complete `asm/tests/input_tab.py` file.
   * If needed, add an error type in `ERROR_TYPE` table, e.g. :
     ```bash
     'COMMENT_TOO_LARGE': 'Comment too large.'
     ```
   * In `INPUT` table, add the corresponding line to your test.  
     If no error is expected, e.g. :
     ```bash
     'zork.s': {'error': False, 'error_type': None, 'error_line': -1}
     ```  
     If an error is expected, specify the type (from `ERROR_TYPE` table) and the line number, e.g. :
     ```bash
     'zork.s': {'error': True, 'error_type': 'COMMENT_TOO_LARGE', 'error_line': 2}
     ```

3) If your test will create a `.cor` file, add the expected output file (`.cor`) in `asm/tests/output`, so that the script will compare with it.

#### Run the tests
``` bash
make -C asm
python3 asm/tests/main.py
```
## VM

```bash
./corewar [-dump N] [-zaz] [-visual] [-verbose 1|2] [-n N <champion>] <champion> ...
```
- dump N : dumps memory after N cycles then exits, where N is int >= 0
- zaz : displays like zaz VM (line of 64 bytes) for dump flag
- n N : forces champion's number to N, where N is int >= 0
- visual : displays a Ncurses visual
- verbose : verbose mode (1 : basic | 2 : all)

## Work process

### Want to take some notes ?
Go to `misc/notes/` and write your own notes.

### Want to write some small tests and keep a trace ?
Go to `misc/dumb_tests/` and add your repo.
If needed, add some file in gitignore file.

### Want to read/add some appendix ?
Got to `misc/appendix/`.

### Documentation
Don't forget to complete your documentation part when working ;)

### Git process

- 2 pre-master branches will be used : `asm` and `vm`.
- No direct push on these pre-master branches (and on `master` of course).
- For each feature, create a branch from `asm`/`vm`. When the feature is finished, merge on the pre-master. Of course, if your feature has nothing to do with pre-master topic, create a branch from `master`.
- Pre-master branch (`asm`/`vm`) can be merged on master only if all the work is totally completed = all tests green + norminette ok + documentation.
- Don't forget that 42 headers (for the norm) are git cancer. Add them only on your last commit, just before the final merge :)

### Break process
It's scientifically proven that playing Clash Royal once an hour will help to manage Corewar 😎
