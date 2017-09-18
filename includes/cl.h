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
	cl_command_queue commands;
	cl_kernel kernel;                   // compute kernel
	cl_mem output;                      // device memory used for the output array
	size_t			data_size;          // compute command queue
}				t_cl;

int		cl_init(struct s_cl *cl);
int		file_to_str(char *filename, char **source_str);
int		cl_load_program_from_source(struct s_cl *cl, char **source_str, cl_program *program);
int		cl_create_kernel_from_program(cl_program program, char *func_name,cl_kernel *kernel);
int		cl_create_buffer(struct s_cl *cl, int rights, size_t data_size, cl_mem *output);
int		cl_set_arg(cl_kernel kernel, size_t size, int *i, void *ptr);
int		cl_exec(struct s_cl *cl, size_t global, cl_kernel kernel);
int		cl_read_results(struct s_cl *cl, cl_mem output, size_t output_size, int *result);
