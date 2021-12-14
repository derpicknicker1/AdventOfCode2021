# :sparkles: :santa: AdventOfCode2021 :christmas_tree: :candle: 

Solutions for [Advent Of Code 2021](http://adventofcode.com/2021) written in **C**

The descriptions of the daily tasks are in the comments in the `*.c` files (see `src/`).

The `*.txt` files in `input/` contain the original input for the tasks.

`main.exe` does all tasks and prints all solutions. It uses the input files in `input/`.

Use GCC to build `main.c` with the makefile provided.

![C/C++ CI](https://github.com/derpicknicker1/AdventOfCode2021/workflows/C/C++%20CI/badge.svg)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/derpicknicker1/AdventOfCode2021)
![GitHub repo size](https://img.shields.io/github/repo-size/derpicknicker1/AdventOfCode2021)
## Stats
![](https://img.shields.io/badge/day%20📅-13-blue)
![](https://img.shields.io/badge/stars%20⭐-26-yellow)
![](https://img.shields.io/badge/days%20completed-13-red)
<!--- advent_readme_stars table --->
## 2021 Results

| Day | Part 1 | Part 2 |
| :---: | :---: | :---: |
| [Day 1](https://adventofcode.com/2021/day/1) | ⭐ | ⭐ |
| [Day 2](https://adventofcode.com/2021/day/2) | ⭐ | ⭐ |
| [Day 3](https://adventofcode.com/2021/day/3) | ⭐ | ⭐ |
| [Day 4](https://adventofcode.com/2021/day/4) | ⭐ | ⭐ |
| [Day 5](https://adventofcode.com/2021/day/5) | ⭐ | ⭐ |
| [Day 6](https://adventofcode.com/2021/day/6) | ⭐ | ⭐ |
| [Day 7](https://adventofcode.com/2021/day/7) | ⭐ | ⭐ |
| [Day 8](https://adventofcode.com/2021/day/8) | ⭐ | ⭐ |
| [Day 9](https://adventofcode.com/2021/day/9) | ⭐ | ⭐ |
| [Day 10](https://adventofcode.com/2021/day/10) | ⭐ | ⭐ |
| [Day 11](https://adventofcode.com/2021/day/11) | ⭐ | ⭐ |
| [Day 12](https://adventofcode.com/2021/day/12) | ⭐ | ⭐ |
| [Day 13](https://adventofcode.com/2021/day/13) | ⭐ | ⭐ |
<!--- advent_readme_stars table --->
## Building in SublimeText3 (Win)

* Install Mingw
* Add `C:\MinGW\bin` to PATH
* Symlink `mklink C:\MinGW\bin\make.exe C:\MinGW\bin\mingw32-make.exe`
* In SublimeText **Tools > Build System > New Build System...**
  * Add the following code (also found in _Make_AOC.sublime-build_)
    ```yaml
    {
      "shell_cmd": "make",
      "working_dir": "${folder}",
     
      "variants": 
      [
          {
              "name": "Run",
              "shell_cmd": "make && ${folder}/main.exe skip"
          },
          {
              "name": "Clean",
              "shell_cmd": "make clean"
          }
      ]
    }
    ```
  * Save to `C:\Users\[$user]\AppData\Roaming\Sublime Text 3\Packages\User`
* Select this Build System in **Tools > Build System**
* Build with <kbd>Ctrl</kbd> + <kbd>B</kbd>
  * <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>B</kbd> to choose variant (e.g _run_)

## Snippet
All solutions have the same base structure.

There is a snippet for SublimeText to generate this basic structure.

Just type `AOC` and hit <kbd>Tab</kbd> to insert the basic code.

To use it, place `AOC.sublime-snippet` in `C:\Users\<UserName>\AppData\Roaming\Sublime Text 3\Packages\User`

## GIT
Auto-generate a release with the workflow found in `.github/workflows/`
```
git tag -a v* -m "My_Msg"
git push --tags
```

## Main executeable
To solve puzzles, put the input data given by the calendar in a txt file for each day(e.g. `3.txt` for Day 3).

Place the txt files in an fodler called `input`. The folder must be under the same path as the main executeable.

The same can be done for the samples of each puzzle in a folder named `samples`.

run `main` to solve the puzzles with the data from `input` folder.

run `main sample` to solve the puzzles with the data from `samples` folder.
