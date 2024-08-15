# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    norm.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 10:11:09 by yetay             #+#    #+#              #
#    Updated: 2024/08/06 13:09:33 by welow            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

#!/usr/bin/env bash

# terminal colours
RESET="\033[0m";
RED="\033[1;31m";
GREEN="\033[1;32m";
BLUE="\033[1;34m";
RED="\033[1;31m";

echo
echo "$GREEN ==========CHECK LIBFT FILES========== $RESET";
find ./libft_42 -name "*.h" ! -exec norminette -R CheckDefine {} \;
find ./libft_42 -name "*.c" ! -exec norminette -R CheckDefine {} \;
echo


echo "$GREEN ==========CHECK ALL HEADER========== $RESET";
find ./include -name "*.h" ! -exec norminette -R CheckDefine {} \;
echo

echo "$GREEN ==========CHECK ALL SRC FILES========== $RESET";
find ./srcs -name "*.c" ! -exec norminette -R CheckForbiddenSourceHeader {} \;
echo

exit 0;
