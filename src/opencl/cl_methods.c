/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_methods.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/25 13:44:30 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <OpenCL/opencl.h>
#include "libft.h"
#include "private_cl.h"
#include "rt.h"

int		cl_init(struct s_cl *cl)
{
	int err;

	err = 0;
	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &cl->device_id, NULL);
	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to create a device group!\n");
		return (EXIT_FAILURE);
	}
	cl->context = clCreateContext(0, 1, &cl->device_id, NULL, NULL, &err);
	if (!cl->context)
	{
		printf("Error: Failed to create a compute context!\n");
		return (EXIT_FAILURE);
	}
	cl->commands = clCreateCommandQueue(cl->context, cl->device_id, 0, &err);
	if (!cl->commands)
	{
		printf("Error: Failed to create a command commands!\n");
		return (EXIT_FAILURE);
	}
	//printf("Init ok\n");
	return (EXIT_SUCCESS);
}

int		file_to_str(char *filename, char **source_str)
{
	size_t	max_source_size;
	FILE	*fp;
	size_t	source_size;

	max_source_size = 50000;
	fp = fopen(filename, "r");
	if (!fp)
	{
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}
	*source_str = ft_strnew(max_source_size);
	source_size = fread(*source_str, 1, max_source_size, fp);
	if (source_size == 0)
	{
		fprintf(stderr, "fread failed.\n");
		exit(1);
	}
	fclose(fp);
	//printf("File_to_str ok\n");
	return (EXIT_SUCCESS);
}

int		cl_load_program_from_source(struct s_cl *cl, char **source_str,\
		cl_program *program)
{
	int		err;
	size_t	len;
	char	buffer[5000000];

	err = 0;
	printf("cl_load_program_from_source enter\n");
	*program = clCreateProgramWithSource(cl->context, 1, (const char **)\
			source_str, NULL, &err);
	if (err || !*program)
	{
		printf("Error: Failed to create compute program!\n");
		return (EXIT_FAILURE);
	}
	err = clBuildProgram(*program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to build program executable!%d\n", err);
		clGetProgramBuildInfo(*program, cl->device_id, CL_PROGRAM_BUILD_LOG,\
				sizeof(buffer), buffer, &len);
		fprintf(stderr, "%s\n", buffer);
		exit(1);
	}
	//printf("cl_load_program_from_source ok\n");
	return (EXIT_SUCCESS);
}

int		cl_create_kernel_from_program(cl_program program, char *func_name,\
		cl_kernel *kernel)
{
	int	err;

	err = 0;
	*kernel = clCreateKernel(program, func_name, &err);
	if (!*kernel || err != CL_SUCCESS)
	{
		printf("Error: Failed to create compute kernel! \n");
		exit(1);
	}
	//printf("cl_create_kernel_from_program ok\n");
	return (EXIT_SUCCESS);
}