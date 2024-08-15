# minishell_42
## readline
readline directory needs to be beside the minishell directory (not inside) to compile<br>
Download readline-8.2.tar.gz from [here](https://ftp.gnu.org/gnu/readline/) unzip readline-8.2.tar.gz, make sure the directory is named "readline-8.2", cd into it, run<br>
*./configure --prefix=$(pwd) && make && make install*

## References
[Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)<br>
[GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.html)

Scanner
* [Crafting Interpreters by Robert Nystrom](https://craftinginterpreters.com/scanning-on-demand.html)

Recursive descent parsing
* https://youtu.be/SToUyjAsaFk?si=Ut2mm_5lXMP2hk67

Overall parsing structure
* [Shell program Explained by hhp3](https://youtu.be/ubt-UjcQUYg?si=yezoPmA7HbBe0SjI)
* [Shell program more detail by hhp3](https://youtu.be/ZjzMdsTWF0U?si=fstp7_iMvtzMRSMn)

