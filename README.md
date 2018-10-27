# Corewar

## Work process

### Want to take some notes ?
Go to `misc/notes/` and write your own notes.

### Want to write some small tests and keep a trace ?
Go to `misc/dumb_tests/` and add your repo.
If needed, add some file in gitignore file.

### Want to read/add some appendix ?
Got to `misc/appendix/`.

### Git process

- 3 pre-master branches are used : `asm`, `vm` and `visu`
- No direct push on those pre-master branches (and on `master` of course).
- For each feature, create a branch from `asm`/`vm`/`visu`, and when the feature is finished, merge on the pre-master. Of course, if your feature has no link with pre-master topic, create a branche from `master`.
- Pre-master branch (`asm`/`vm`/`visu`) can be merged on master only if all the work is totally completed = all tests green + norminette ok.
- Don't forget that 42 headers in files are git cancer. Put them on your last commit just before the final merge :)
