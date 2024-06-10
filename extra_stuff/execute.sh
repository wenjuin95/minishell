#!/bin/bash

# This script will execute the file you want to execute
file=$1

if [[ $file == "exit" ]]
then
	gcc -Wall -Wextra -Werror test_exit.c ../libft.a -fsanitize=address -g
elif [[ $file == "echo" ]]
then
	gcc -Wall -Wextra -Werror test_echo.c ../libft.a -fsanitize=address -g
elif [[ $file == "env" ]]
then
	gcc -Wall -Wextra -Werror test_env.c ../libft.a -fsanitize=address -g
elif [[ $file == "export" ]]
then
	gcc -Wall -Wextra -Werror test_export.c ../libft.a -fsanitize=address -g
elif [[ $file == "pwd" ]]
then
	gcc -Wall -Wextra -Werror test_pwd.c ../libft.a -fsanitize=address -g
elif [[ $file == "unset" ]]
then
	gcc -Wall -Wextra -Werror test_unset.c ../libft.a -fsanitize=address -g
elif [[ $file == "cd" ]]
then
	gcc -Wall -Wextra -Werror test_cd.c ../libft.a -fsanitize=address -g
else
	echo "File not found"
fi
 
