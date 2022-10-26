#include "../includes/RTv1.h"

/* the following functions are needed to invert a matrix.*/

/* function to remove a specified row and col from a matrix.
Returns a new matrix with 1 column and 1 row less*/
/*
	t_coords	padding; // (tm) - jsaarine CC0
*/
t_mtx	submatrix(t_mtx *mtx, t_coords index, uint32_t size)
{
	t_mtx		new_matrix;
	t_coords		old;
	t_coords		new;

	old.row = 0;
	new.row = 0;
	while (old.row <= size - 1)
	{
		if (old.row++ == index.row)
			continue ;
		old.col = 0;
		new.col = 0;
		while (old.col <= size - 1)
		{
			if (old.col++ == index.col)
				continue ;
			new_matrix.array[(size - 1) * new.row + new.col++] = \
				mtx->array[size * (old.row - 1) + (old.col - 1)];
		}
		new.row++;
	}
	return (new_matrix);
}

static t_fl	matrix_minors(t_mtx *mtx, t_coords index, uint32_t size)
{
	t_mtx	temp;
	t_fl	minor;

	temp = submatrix(mtx, index, size);
	minor = determinant(&temp, size - 1);
	return (minor);
}

static t_fl	matrix_cofactor(t_mtx *mtx, t_coords index, uint32_t size)
{
	t_fl	cofactor;
	t_fl	minor;

	minor = matrix_minors(mtx, index, size);
	if ((index.row + index.col) % 2 == 0)
		cofactor = minor;
	else
		cofactor = minor * -1;
	return (cofactor);
}

/* calculates the determinant of any sized matrix*/

t_fl	determinant(t_mtx *mtx, uint32_t size)
{
	t_fl		det;
	t_coords		index;

	index.col = 0;
	index.row = 0;
	det = 0;
	if (size == 2)
		det = (mtx->array[0] * mtx->array[2 * 1 + 1]) - \
		(mtx->array[2 * 0 + 1] * mtx->array[2 * 1 + 0]);
	else
	{
		while (index.col < size)
		{
			det = det + mtx->array[size * index.row + index.col] * \
			matrix_cofactor(mtx, index, size);
			index.col++;
		}
	}
	return (det);
}

/* matrix inversion - allows to reverse effects of matrix multiplication*/

void	matrix_inversion(t_mtx *mtx, uint32_t size)
{
	t_fl		det;
	t_mtx		temp;
	t_coords		i;

	det = determinant((t_mtx *)mtx, size);
	if (det == 0)
	{
		printf("det = %f\n", det);
		return ;
	}
	else
	{
		i.row = (uint32_t)(-1);
		while (++i.row < size)
		{
			i.col = (uint32_t)(-1);
			while (++i.col < size)
				temp.array[size * i.row + i.col] = \
					matrix_cofactor((t_mtx *)mtx, i, size) / det;
		}
		*mtx = transpose_matrix(&temp);
	}
}
