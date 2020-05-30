#include <stdio.h>
#include <string.h>
#include <CL/cl.h>

//the CLC program as a string (this is not C. It is CLC).
const char rot13_cl[] = "\
__kernel void rot13 \
    (   __global    const   char* in	\
    ,   __global            char* out	\
    )					\
{					\
    const uint index = get_global_id(0); \
    char c=in[index];			\
    if (c<'A' || c>'z' || (c>'Z' && c<'a')) \
	{ \
        out[index] = in[index];		\
    } else 				\
	{				\
        if (c>'m' || (c>'M' && c<'a')) 	\
		{			\
	    	out[index] = in[index]-13; \
		} else 			   \
		{			   \
		    out[index] = in[index]+13; \
		}  \
    }	\
} \
";

void rot13 (char *buf)
{
    int index=0;
    char c=buf[index];
    while (c!=0) {
        if (c<'A' || c>'z' || (c>'Z' && c<'a')) {
            buf[index] = buf[index];
        } else {
            if (c>'m' || (c>'M' && c<'a')) {
	        buf[index] = buf[index]-13;
	    } else {
	        buf[index] = buf[index]+13;
	    }
        }
	c=buf[++index];
    }
}

int main() {
	char buf[]="Hello, World!";
	size_t srcsize, worksize=strlen(buf);
	
	cl_int error;
	cl_platform_id platform;
	cl_device_id device;
	cl_uint platforms, devices;

	error=clGetPlatformIDs(1, &platform, &platforms);
	error=clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, &devices);
	cl_context_properties properties[]={
		CL_CONTEXT_PLATFORM, (cl_context_properties)platform,
		0};
	cl_context context=clCreateContext(properties, 1, &device, NULL, NULL, &error);
	cl_command_queue cq = clCreateCommandQueue(context, device, 0, &error);
	
	rot13(buf);	// scramble using the CPU
	puts(buf);	// Just to demonstrate the plaintext is destroyed

	const char *src=rot13_cl;
	srcsize=strlen(rot13_cl);

	const char *srcptr[]={src};
	cl_program prog=clCreateProgramWithSource(context,
		1, srcptr, &srcsize, &error);
	error=clBuildProgram(prog, 0, NULL, "", NULL, NULL);  //compile

	cl_mem mem1, mem2;  // Allocate memory for the kernel to work with
	mem1=clCreateBuffer(context, CL_MEM_READ_ONLY, worksize, NULL, &error);
	mem2=clCreateBuffer(context, CL_MEM_WRITE_ONLY, worksize, NULL, &error);
	
	// get a handle and map parameters for the kernel
	cl_kernel k_rot13=clCreateKernel(prog, "rot13", &error);
	clSetKernelArg(k_rot13, 0, sizeof(mem1), &mem1);
	clSetKernelArg(k_rot13, 1, sizeof(mem2), &mem2);

	// Target buffer just so we show we got the data from OpenCL
	char buf2[sizeof buf];
	buf2[0]='?';
	buf2[worksize]=0;

	// Send input data to OpenCL (async, don't alter the buffer!)
	error=clEnqueueWriteBuffer(cq, mem1, CL_FALSE, 0, worksize, buf, 0, NULL, NULL);
	// Perform the operation
	error=clEnqueueNDRangeKernel(cq, k_rot13, 1, NULL, &worksize, &worksize, 0, NULL, NULL);
	// Read the result back into buf2
	error=clEnqueueReadBuffer(cq, mem2, CL_FALSE, 0, worksize, buf2, 0, NULL, NULL);
	error=clFinish(cq); //wait for completion
	puts(buf2); //output the result
}
