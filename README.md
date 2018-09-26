# compilers

[canvas link](https://canvas.elte.hu/courses/1929)

## Contents of this repo

I create a branch for each practice lesson. brief summary for each class (including direct link to branch in headers):

### [Second practice](https://github.com/iarigby/compilers/tree/first-practice) 
> incorrectly named first-practice because that's when we first used the computers :grin:

I commited `first.l`, `lex.yy.cc` and `a.out` after each major change. when viewing each commit, you can clearly see how changes in first.l impacted the flex output.
#### Contents of the lesson
introduction to FLEX and regex
- capturing regex and assigning actions
- parsing an ip address
- even numbers exercise

Additionally I created helper scripts:
- `ex.sh` 
runs flex command on first.l file, then compiles with g++ and runs ./a.out file
- `git.sh`
stages all files (new and modified) for commit, then asks for commit message and creates the commit 
