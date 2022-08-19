/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c		                                      :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/8/19 12:06:35 by pshandy            #+#    #+#             */
/*   Updated: 2022/8/19 12:06:36 by pshandy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{

	pars_arg_check(argc, argv);

	// -------------- Must have ---------------
	t_cub cub;
	cub.params.so.img = NULL;
	cub.params.no.img = NULL;
	cub.params.we.img = NULL;
	cub.params.ea.img = NULL;
	cub.params.ce_rgb = NULL;
	cub.params.fl_rgb = NULL;
	cub.map.matrix = NULL;
	cub.mlx = mlx_init();
	// -------------- Must have ---------------

	int ret = pars_read_cfg(argv[1], &cub);

	if (ret != 0)
	{
		printf("Fail. %s\n", argv[1]);
		pars_free_all(&cub);
		pars_exit_with_error(ret);
	}

	printf("Success.\n");

	// for (int i = 0; i < cub.map.rows; i++) {
	// 	for (int j = 0; j < cub.map.cols; j++) {
	// 		printf("%d\t", cub.map.matrix[i][j]);
	// 	}
	// 	printf("\n");
	// }

	printf("X: %d, Y: %d\n", cub.map.pl_x, cub.map.pl_y);
	printf("Rows: %d, Cols: %d\n", cub.map.rows, cub.map.cols);

	printf("%d\n", cub.params.so.width);

	printf("Floor RGB: %d, %d, %d\n", cub.params.fl_rgb[0], cub.params.fl_rgb[1], cub.params.fl_rgb[2]);
	printf("Ceilling RGB: %d, %d, %d\n", cub.params.ce_rgb[0], cub.params.ce_rgb[1], cub.params.ce_rgb[2]);

	pars_free_all(&cub); //free mem for map & textures

}
