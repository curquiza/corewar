# Corewar

## ASM
_usage, all error types..._
## VM
_usage, how it works .._
## Visu
_usage ..._
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

- 3 pre-master branches will be used : `asm`, `vm` and `visu`.
- No direct push on these pre-master branches (and on `master` of course).
- For each feature, create a branch from `asm`/`vm`/`visu`. When the feature is finished, merge on the pre-master. Of course, if your feature has nothing to do with pre-master topic, create a branch from `master`.
- Pre-master branch (`asm`/`vm`/`visu`) can be merged on master only if all the work is totally completed = all tests green + norminette ok + documentation.
- Don't forget that 42 headers (for the norm) are git cancer. Add them only on your last commit, just before the final merge :)

### Break process
It's scientifically proven that playing Clash Royal once an hour will help to manage Corewar.
