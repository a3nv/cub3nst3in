#include "../../includes/cub3d.h"

int get_map_size(t_game *g, int row, int *height, int *width)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    if( !g || !g->map || !g->map->data)
    {
        ft_putstr_fd("[WARN] get_map_size: no map or game struct\n", STDERR_FILENO);
        return (0);
    }
    while (g->map->data[i])
        i++;
    if( row >= i)
    {
        ft_putstr_fd("[WARN] get_map_size: row is out of bounds\n", STDERR_FILENO);
        return (0);
    }
    while (g->map->data[row][j])
        j++;
    *height = i;
    *width = j;
    return (1);
}

/// @brief Get Cell Safe (gcs) Get the character at the specified row and column in the map
/// without the thread of segfaulting if the row or column is out of bounds.
/// @param g the game struct
/// @param row the row of the character
/// @param col the column of the character
/// @return the character at the specified row and column, or ' ' if out of bounds
char gcs(t_game *g, int row, int col)
{
    int height;
    int width;

    if (!get_map_size(g, row, &height, &width))
        return (' ');
    if (row < 0 || col < 0 || row >= height || col >= width)
        return (' ');
    return (g->map->data[row][col]);
}

/// @brief check if the cells are adjacent to a '0' are either '1' or '0' and zero is not on the edge
/// @param g 
/// @param row  
/// @param col 
/// @param mapcheck 
/// @return saves values to pinters, retruns 1 if the cells are valid
/// @note The function checks if the cells are adjacent to a '0' are either
///  '1' or '0' and zero is not on the edge. Checks diagonally as well.
int check_zero_adjacent_cells(t_game *g, int row, int col)
{
    int width;
    int height;

    if (!get_map_size(g, row, &height, &width))
        return (0);
    if (row < 0 || col < 0 || row >= height || col >= width) // TODO: check whether the offsets correct
        return (0);
    if(row == 0 || col == 0 || row == height || col == width)
        return (0);
    if ((gcs(g, row - 1, col) == '1' || gcs(g, row - 1, col) == '0') 
        && (gcs(g, row + 1, col) == '1' || gcs(g, row + 1, col) == '0')
        && (gcs(g, row, col - 1) == '1' || gcs(g, row, col - 1) == '0')
        && (gcs(g, row, col + 1) == '1' || gcs(g, row, col + 1) == '0'))
        return (1);
    return (0);
}

/// @brief Check if the cells are valid
/// @param g the game struct
/// @param row the row of the cell
/// @param col the column of the cell
/// has been checked before
/// @return <int> 1 if the cell is valid, 0 if the cell is not valid
int is_cell_valid(t_game *g, int row, int col)
{
    if (g->map->data[row][col] == '1')
        return (1);
    else if (g->map->data[row][col] == ' ')
        return (1);
    else if (g->map->data[row][col] == '\n')
        return (1);
    else if (g->map->data[row][col] == '0')
        return (check_zero_adjacent_cells(g, row, col));
 //   debug("Symbol encoutered [%i][%i]<%c>\n", row, col, g->map->data[row][col]);
 //   error_exit("In func <are_cells_valid>: found unrecognized symbol in map\n", g);
    return (0);
}

/// @brief Ceck if the map is closed
/// @param g the game struct
/// @return <void> throws an error and exits if the map is not closed
/// @note The function checks if the map is closed by checking if the cells one by one
/// are valid. Valid cells are either '1' or '0' and zero is not on the edge and 
/// has around only '1' or '0' no ' ' or other char.
bool  check_enclosure(t_game *g)
{
    int col;
    int row;
    
    col = 0;
    row = 0;
    while(g->map->data[row] && g->map->data[row][col])
    {
        while(g->map->data[row][col])
        {
            if (!is_cell_valid(g, row, col))
            {
                debug("[NOTE] problematic symbol encoutered @map[%i][%i]: <%c>", row, col, g->map->data[row][col]);
                set_em(g, "Error: unclosed map\n", E);
                return (false);
            }
            col++;
        }
        row++;
        col = 0;
    }
    return (true);
}