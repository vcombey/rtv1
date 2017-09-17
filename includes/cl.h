#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <OpenCL/opencl.h>

int		cl_init(struct s_cl *cl);
int		file_to_str(char *filename, char **source_str);
int		cl_load_program_from_source(struct s_cl *cl, char *source_str, cl_program *program);
int		cl_create_kernel_from_program(struct s_cl *cl, cl_program program, char *func_name,cl_kernel *kernel);
int		cl_create_buffer(struct s_cl *cl, int rights, size_t data_size, cl_mem *output);
int		cl_exec(struct s_cl *cl, size_t global, cl_kernel kernel);
int		cl_read_results(struct s_cl *cl, cl_mem output, size_t output_size, int *result);
