# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/12 16:21:22 by iasonov           #+#    #+#              #
#    Updated: 2025/06/02 21:48:40 by iasonov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c \
	  src/init.c \
	  src/debug.c \
	  src/action_handler.c \
	  src/move.c \
		src/gc/application_gc.c \
		src/gc/parser_gc.c \
		src/parser/configuration_file_parser.c \
		src/parser/configuration_file_parser_utils.c \
		src/parser/parser_configuration_line.c \
		src/parser/parser_utils_configuration_line.c \
		src/parser/parser_color.c \
		src/parser/parser_helpers.c \
		src/parser/parser_texture.c \
		src/validator/file_validator.c \
		src/validator/parser_validator.c \
		src/validator/map_validator.c \
		src/validator/map_enclosure_check.c \
		src/validator/map_validator_utils.c \
		src/renderer/init_render.c \
		src/renderer/camera_utils.c \
		src/renderer/raycaster.c \
		src/renderer/dda.c \
		src/renderer/render_utils.c \
		src/renderer/renderer.c \
