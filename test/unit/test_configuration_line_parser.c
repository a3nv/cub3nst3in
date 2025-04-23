#include "../../includes/cub3d.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


Test(extract_rgb, ok)
{
	bool	res;
	t_game	*g;
	t_pair	*p;
	t_rgb	*rgb;

	rgb = malloc(sizeof *rgb);
	cr_assert_not_null(rgb, "malloc(rgb), failed");
	ft_bzero(rgb, sizeof *rgb);
	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	p = create_pair("SKIP", "100,200,255");
	cr_assert_not_null(p, "create_pair returned NULL");
	res = extract_rgb(g, p, rgb);
	cr_expect(rgb->r == 100, "Expected 100 but got %d", rgb->r);
	cr_expect(rgb->g == 200, "Expected 200 but got %d", rgb->g);
	cr_expect(rgb->b == 255, "Expected 255 but got %d", rgb->b);
	cr_expect(res == true);
	free_pair(p);
	free(rgb);
	free(g);
}

Test(extract_rgb, r_is_empty)
{
	bool	res;
	t_game	*g;
	t_pair	*p;
	t_rgb	*rgb;

	rgb = malloc(sizeof *rgb);
	cr_assert_not_null(rgb, "malloc(rgb), failed");
	ft_bzero(rgb, sizeof *rgb);
	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	p = create_pair("SKIP", "100,,255");
	cr_assert_not_null(p, "create_pair returned NULL");
	res = extract_rgb(g, p, rgb);
	cr_expect(res == false);
	free_pair(p);
	free(rgb);
	free(g);
}

Test(extract_rgb, g_is_empty)
{
	bool	res;
	t_game	*g;
	t_pair	*p;
	t_rgb	*rgb;

	rgb = malloc(sizeof *rgb);
	cr_assert_not_null(rgb, "malloc(rgb), failed");
	ft_bzero(rgb, sizeof *rgb);
	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	p = create_pair("SKIP", ",100,255");
	cr_assert_not_null(p, "create_pair returned NULL");
	res = extract_rgb(g, p, rgb);
	cr_expect(res == false);
	free_pair(p);
	free(rgb);
	free(g);
}

Test(extract_rgb, b_is_empty)
{
	bool	res;
	t_game	*g;
	t_pair	*p;
	t_rgb	*rgb;

	rgb = malloc(sizeof *rgb);
	cr_assert_not_null(rgb, "malloc(rgb), failed");
	ft_bzero(rgb, sizeof *rgb);
	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	p = create_pair("SKIP", "100,100,");
	cr_assert_not_null(p, "create_pair returned NULL");
	res = extract_rgb(g, p, rgb);
	cr_expect(res == false);
	free_pair(p);
	free(rgb);
	free(g);
}

Test(extract_rgb, few_color_channels)
{
	bool	res;
	t_game	*g;
	t_pair	*p;
	t_rgb	*rgb;

	rgb = malloc(sizeof *rgb);
	cr_assert_not_null(rgb, "malloc(rgb), failed");
	ft_bzero(rgb, sizeof *rgb);
	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	p = create_pair("SKIP", "100,100");
	cr_assert_not_null(p, "create_pair returned NULL");
	res = extract_rgb(g, p, rgb);
	cr_expect(res == false);
	free_pair(p);
	free(rgb);
	free(g);
}

Test(extract_rgb, to_many_color_channels)
{
	bool	res;
	t_game	*g;
	t_pair	*p;
	t_rgb	*rgb;

	rgb = malloc(sizeof *rgb);
	cr_assert_not_null(rgb, "malloc(rgb), failed");
	ft_bzero(rgb, sizeof *rgb);
	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	p = create_pair("SKIP", "100,100,255,0");
	cr_assert_not_null(p, "create_pair returned NULL");
	res = extract_rgb(g, p, rgb);
	cr_expect(res == false);
	free_pair(p);
	free(rgb);
	free(g);
}

Test(parse_texture_configuration, so_ok)
{
	bool	res;
	t_game	*g;
	char	*l;

	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	l = "SO /Users/janedoe/maps/wall.xpm"; 
	res = parse_texture_configuration(l, g);
	cr_expect(res == true);
	cr_assert_not_null(g->so_ptr, "so_ptr expected not null");
	cr_assert_null(g->no_ptr, "no_ptr expected null");
	cr_assert_null(g->we_ptr, "we_ptr expected null");
	cr_assert_null(g->ea_ptr, "ea_ptr expected null");
	cr_assert_str_eq(g->so_ptr, "/Users/janedoe/maps/wall.xpm", "so_ptr is incorrect");
	free(g);
}

Test(parse_texture_configuration, no_ok)
{
	bool	res;
	t_game	*g;
	char	*l;

	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	l = "NO /Users/janedoe/maps/wall.xpm"; 
	res = parse_texture_configuration(l, g);
	cr_expect(res == true);
	cr_assert_not_null(g->no_ptr, "no_ptr expected not null");
	cr_assert_null(g->so_ptr, "so_ptr expected null");
	cr_assert_null(g->we_ptr, "we_ptr expected null");
	cr_assert_null(g->ea_ptr, "ea_ptr expected null");
	cr_assert_str_eq(g->no_ptr, "/Users/janedoe/maps/wall.xpm", "no_ptr is incorrect");
	free(g);
}

Test(parse_texture_configuration, we_ok)
{
	bool	res;
	t_game	*g;
	char	*l;

	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	l = "WE /Users/janedoe/maps/wall.xpm"; 
	res = parse_texture_configuration(l, g);
	cr_expect(res == true);
	cr_assert_not_null(g->we_ptr, "we_ptr expected not null");
	cr_assert_null(g->so_ptr, "so_ptr expected null");
	cr_assert_null(g->no_ptr, "no_ptr expected null");
	cr_assert_null(g->ea_ptr, "ea_ptr expected null");
	cr_assert_str_eq(g->we_ptr, "/Users/janedoe/maps/wall.xpm", "we_ptr is incorrect");
	free(g);
}

Test(parse_texture_configuration, ea_ok)
{
	bool	res;
	t_game	*g;
	char	*l;

	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	l = "EA /Users/janedoe/maps/wall.xpm"; 
	res = parse_texture_configuration(l, g);
	cr_expect(res == true);
	cr_assert_not_null(g->ea_ptr, "ea_ptr expected not null");
	cr_assert_null(g->so_ptr, "so_ptr expected null");
	cr_assert_null(g->no_ptr, "no_ptr expected null");
	cr_assert_null(g->we_ptr, "we_ptr expected null");
	cr_assert_str_eq(g->ea_ptr, "/Users/janedoe/maps/wall.xpm", "ea_ptr is incorrect");
	free(g);
}

Test(parse_texture_configuration, incorrect_ideantifier)
{
	bool	res;
	t_game	*g;
	char	*l;

	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	l = "WW /Users/janedoe/maps/wall.xpm"; 
	res = parse_texture_configuration(l, g);
	cr_expect(res == false);
	cr_assert_null(g->ea_ptr, "ea_ptr expected null");
	cr_assert_null(g->so_ptr, "so_ptr expected null");
	cr_assert_null(g->no_ptr, "no_ptr expected null");
	cr_assert_null(g->we_ptr, "we_ptr expected null");
	cr_assert_str_eq(g->error_message, "Unknown configuration identifier\n", "Incorrect error message");
	free(g);
}

Test(parse_color_configuration, incorrect_ideantifier)
{
	bool	res;
	t_game	*g;

	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	res = parse_color_configuration("T 191,111,23", g);
	cr_expect(res == false);
	free(g);
}

Test(parse_color_configuration, ok_exceeding_range)
{
	bool	res;
	t_game	*g;

	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	res = parse_color_configuration("F 191,111,23222", g);
	cr_expect(res == true);
	cr_assert_null(g->ceiling);
	cr_expect(g->floor->r == 191, "incorrect r");
	cr_expect(g->floor->g == 111, "incorrect g");
	cr_expect(g->floor->b == 23222, "incorrect b");
	free(g);
}

Test(parse_color_configuration, ok_negative_color)
{
	bool	res;
	t_game	*g;

	g = malloc(sizeof *g);
	cr_assert_not_null(g, "malloc(g) failed");
	ft_bzero(g, sizeof *g);
	res = parse_color_configuration("C 191,-111,23", g);
	cr_log_info("Before testing 1");
	cr_expect(res == true);
	cr_assert_null(g->floor);
	cr_expect(g->ceiling->r == 191, "incorrect r");
	cr_expect(g->ceiling->g == -111, "incorrect g");
	cr_expect(g->ceiling->b == 23, "incorrect b");
	free(g);
}
