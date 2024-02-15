// Include kernels!
#include "kernels/conv-ws/conv.h"

static kcom_kernel_t *kernels[] = {
    &conv_kernel,
};

static kcom_perf_t kperf;

void main()
{
	kcom_kernel_t *kernel;
	uint8_t ker_idx = 0;

	kcom_init();


	kernel = kernels[ker_idx];
	uint8_t kernel_id = (ker_idx % (CGRA_KMEM_SIZE - 1)) + 1; // Must be between 1 and (KMEM_SIZE - 1).
	kernel->kmem[kernel_id] = kernel->kmem[1];                // By default the kernels come located with id = 1.

	kcom_load(kernel);

	for (uint16_t it_idx = 0; it_idx < 2; it_idx++)
	{
		/* Load (of inputs). */
		if (it_idx < 2)
		{
			kcom_newVCDfile();
			kcom_resetRand();
		}

		kernel->config();

		/* CGRA Execution */
		kcom_perfRecordIntrSet(&(kperf.time.cgra));
		kcom_perfRecordStart(&(kperf.time.cgra));
		kcom_launchKernel(kernel_id);
		kcom_waitingForIntr();
	}

	return 0;
}

