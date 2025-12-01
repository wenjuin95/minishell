# minishell_42
Creating a simple shell that emulates Bash.

## Dependencies - readline
readline directory needs to be beside the minishell directory (not inside) to compile

Download readline-8.2.tar.gz from [here](https://ftp.gnu.org/gnu/readline/) unzip readline-8.2.tar.gz, make sure the directory is named "readline-8.2", cd into it, run
> *./configure --prefix=$(pwd) && make && make install*

## Features
- Prompt
- Pipes "|" - redirects output of a command to the input of another command
- Redirection
  - < - redirect input 
  - \> - redirect output (clears existing data in output file) 
  - \>\> - redirects output (appends data if data already exists in output file)
  - << - redirect input from a here document

## References
- [GNU Bash Manual][1]
- [Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)

### Parsing
- [Crafting Interpreters by Robert Nystrom](https://craftinginterpreters.com/scanning-on-demand.html) - Scanner
- [Recursive descent parsing](https://youtu.be/SToUyjAsaFk?si=Ut2mm_5lXMP2hk67)

### Overall parsing structure
* [Shell program Explained by hhp3](https://youtu.be/ubt-UjcQUYg?si=yezoPmA7HbBe0SjI)
* [Shell program more detail by hhp3](https://youtu.be/ZjzMdsTWF0U?si=fstp7_iMvtzMRSMn)

### Wildcard Expansion
- [How to list all files in a directory](https://www.youtube.com/watch?v=j9yL30R6npk)
- [Algorithm checking if string matches pattern](https://www.youtube.com/watch?v=3ZDZ-N0EPV0)

### Execution
- [Pipes and redirection](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)

[1]:https://www.gnu.org/software/bash/manual/bash.html 