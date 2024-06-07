#!/bin/bash

# This script will execute the file you want to execute
file=$1

if [[ $file == "exit" ]]
then
	gcc -Wall -Wextra -Werror test_exit.c ../libft.a
elif [[ $file == "echo" ]]
then
	gcc -Wall -Wextra -Werror test_echo.c ../libft.a
elif [[ $file == "env" ]]
then
	gcc -Wall -Wextra -Werror test_env.c ../libft.a
elif [[ $file == "export" ]]
then
	gcc -Wall -Wextra -Werror test_export.c ../libft.a
elif [[ $file == "pwd" ]]
then
	gcc -Wall -Wextra -Werror test_pwd.c ../libft.a
elif [[ $file == "unset" ]]
then
	gcc -Wall -Wextra -Werror test_unset.c ../libft.a
elif [[ $file == "cd" ]]
then
	gcc -Wall -Wextra -Werror test_cd.c ../libft.a
else
	echo "File not found"
fi
 
