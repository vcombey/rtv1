#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <OpenCL/opencl.h>

struct 		s_cl
{
	size_t global;                      // global domain size for our calculation
	size_t local;                       // local domain size for our calculation

	cl_device_id device_id;             // compute device id
	cl_context context;                 // compute context
	cl_command_queue commands;          // compute command queue
}				t_cl;


int		cl_init(struct s_cl *cl)
{
	int err;                            // error code returned from api calls

	//	  // Connect to a compute device
	//
err = 0;
	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &cl->device_id, NULL);
	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to create a device group!\n");
		return EXIT_FAILURE;
	}

	// Create a compute context
	//
	cl->context = clCreateContext(0, 1, &cl->device_id, NULL, NULL, &err);
	if (!cl->context)
	{
		printf("Error: Failed to create a compute context!\n");
		return EXIT_FAILURE;
	}

	// Create a command commands
	//
	cl->commands = clCreateCommandQueue(cl->context, cl->device_id, 0, &err);
	if (!cl->commands)
	{
		printf("Error: Failed to create a command commands!\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int		file_to_str(char *filename, char **source_str)
{
	size_t	MAX_SOURCE_SIZE = 50000;
	FILE *fp;
	size_t source_size;

	fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}
	*source_str = ft_strnew(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);
	return (EXIT_SUCCESS);
}

int		cl_load_program_from_source(struct s_cl *cl, char *source_str, cl_program *program)
{
	int		err;

	err = 0;
		*program = clCreateProgramWithSource(cl->context, 1, (const char **) & source_str, NULL, &err);
		if (!*program)
		{
			printf("Error: Failed to create compute program!\n");
			return EXIT_FAILURE;
		}

		// Build the program executable
		//
		err = clBuildProgram(*program, 0, NULL, NULL, NULL, NULL);
		if (err != CL_SUCCESS)
		{
			size_t len;
			char buffer[2048];

			printf("Error: Failed to build program executable!\n");
			clGetProgramBuildInfo(*program, cl->device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
			printf("%s\n", buffer);
			exit(1);
		}
		return (EXIT_SUCCESS);
}

int		cl_create_kernel_from_program(struct s_cl *cl, cl_program program, char *func_name,cl_kernel *kernel)
{
	int	err;
	// Create the compute kernel in the program we wish to run
	//
	*kernel = clCreateKernel(program, func_name, &err);
	if (!*kernel || err != CL_SUCCESS)
	{
		printf("Error: Failed to create compute kernel! %s\n", getErrorString(err));

		exit(1);
	}
	return EXIT_SUCCESS;
}

int		cl_create_buffer(struct s_cl *cl, int rights, size_t data_size, cl_mem *output)
{
	*output = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY, data_size, NULL, NULL);
	if (!output)
	{
		printf("Error: Failed to allocate device memory!\n");
		exit(1);
	}
	return EXIT_SUCCESS;
}

int		cl_exec(struct s_cl *cl, size_t global, cl_kernel kernel)
{
	int	err;

	err = 0;
	err = clGetKernelWorkGroupInfo(kernel, cl->device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(cl->local), &cl->local, NULL);
	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to retrieve kernel work group info! %d\n", err);
		exit(1);
	}

	// Execute the kernel over the entire range of our 1d input data set
	// using the maximum number of work group items for this device
	//
	err = clEnqueueNDRangeKernel(cl->commands, kernel, 1, NULL, &global, &cl->local, 0, NULL, NULL);
	if (err)
	{
		printf("Error: Failed to execute kernel!\n");
		return EXIT_FAILURE;
	}
	clFinish(cl->commands);
	return (EXIT_SUCCESS);
}

int		cl_read_results(struct s_cl *cl, cl_mem output, size_t output_size, int *result)
{
	int	err;

	err = 0;
	err = clEnqueueReadBuffer( cl->commands, output, CL_TRUE, 0, output_size, &result, 0, NULL, NULL );
	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to read output array! %d\n", err);
		exit(1);
	}
	return (EXIT_SUCCESS);
}
