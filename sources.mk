# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/12 16:21:22 by iasonov           #+#    #+#              #
#    Updated: 2025/04/13 00:01:37 by iasonov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c \
	  src/debug.c \
		src/gc/application_gc.c \
		src/gc/parser_gc.c \
		src/parser/configuration_line_parser.c \
		src/parser/configuration_line_parser_utils.c \
		src/parser/file_parser.c \
		src/parser/parser_utils.c \
		src/validator/file_validator.c \
		src/validator/parser_validator.c \
