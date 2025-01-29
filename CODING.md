# Coding practices

https://clang.llvm.org/docs/ClangFormat.html

Details at `clang-format` [documentation](https://clang.llvm.org/docs/ClangFormat.html)

# setup clang-format
```bash
sudo apt-get install clang-format
clang-format -style=gnu -dump-config > .clang-format
```

## setup clang-format for vim using ALE plugin
Add the following configuration to your `.vimrc`
```bash
" Enable ALE
let g:ale_linters = {
\   'cpp': ['clang-format'],
\}

" Automatically fix files on save
let g:ale_fix_on_save = 1

" Specify the fixer to use for C++
let g:ale_fixers = {
\   'cpp': ['clang-format'],
\}
```
# GIT practices

Follow [naming conventions](https://github.com/naming-convention/naming-convention-guides/tree/master/git) when creating branches and commit messages.

## Pull request rules
1. All pull requests must be associated to a corresponding issue stating the reasons for it and the expected result
2. Add a comment with an overview of the changes made
3. One feature per pull request
