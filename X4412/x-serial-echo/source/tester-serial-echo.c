#include <main.h>

int tester_serial_echo(int argc, char * argv[])
{
	u8_t buf = 0;

	/*
	 * Write topic information
	 */
	exynos4412_serial_write_string(3, "exynos4412 serial3 echo test, please type some character...\r\n");

	while(1)
	{
		if(exynos4412_serial_read(3, &buf, 1) == 1)
		{
			exynos4412_serial_write_string(3, "serial3 recv: [");
			exynos4412_serial_write(3, &buf, 1);
			exynos4412_serial_write_string(3, "]\r\n");
		}
	}

	return 0;
}
