// Simple fan control utility for MSI WIND / LG X110 Netbooks on Linux
// by Jonas Diemer (diemer@gmx.de)
// Based on LGXfan created by Tord Lindstrom (pukko@home.se)

// Compile: "cc     kb3700_fanctrl.c   -o kb3700_fanctrl"
// Run as root.


#include <stdint.h>
#include <sys/io.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define EC_SC 0x66
#define EC_DATA 0x62


#define IBF 1
#define OBF 0
#define EC_SC_READ_CMD 0x80
#define EC_SC_WRITE_CMD 0x81
#define EC_SC_SCI_CMD 0x84

// EC addresses
#define EC_TEMP 0x68
#define EC_CURRENT_FAN_SPEED 0x71
#define EC_TEMP_THRESHOLDS_1 0x69
#define EC_FAN_SPEEDS_1 0x72

// Hysteresis: fan 1->0 8deg, fan 2->1 4 deg 3->2 4 deg
// "Good values": Fan speeds:   0  31  45  60  65  80  80  85
//                Temp thresh   0  50  59  64  76  80  85  93

// Not used fan values (leftovers from a second fan?)
#define EC_TEMP_THRESHOLDS_2 0x81
#define EC_FAN_SPEEDS_2 0x89

static int wait_ec(const uint32_t port, const uint32_t flag, const char value)
{
	uint8_t data;
	int i;

	i = 0;
	data = inb(port);

	while ( (((data >> flag)&0x1)!=value) && (i++ < 100)) {
		usleep(1000);
		data = inb(port);
	}
	if (i >= 100)
	{
		printf("wait_ec error on port 0x%x, data=0x%x, flag=0x%x, value=0x%x\n", port, data, flag, value);
		return 1;
	}

	return 0;
}

// For read_ec & write_ec command sequence see
// section "4.10.1.4 EC Command Program Sequence" in
// http://wiki.laptop.org/images/a/ab/KB3700-ds-01.pdf 
static uint8_t read_ec(const uint32_t port)
{
	uint8_t value;

	wait_ec(EC_SC, IBF, 0);
	outb(EC_SC_READ_CMD, EC_SC);
	wait_ec(EC_SC, IBF, 0);
	outb(port, EC_DATA);
	//wait_ec(EC_SC, EC_SC_IBF_FREE);
	wait_ec(EC_SC, OBF, 1);
	value = inb(EC_DATA);

	return value;
}

static void write_ec(const uint32_t port, const uint8_t value)
{
	wait_ec(EC_SC, IBF, 0);
	outb(EC_SC_WRITE_CMD, EC_SC);
	wait_ec(EC_SC, IBF, 0);
	outb(port, EC_DATA);
	wait_ec(EC_SC, IBF, 0);
	outb(value, EC_DATA);
	wait_ec(EC_SC, IBF, 0);

	return;
}


static void dump_all_regs(void)
{
	uint8_t val;
        int i;

	printf("EC reg dump:");
	for (i = 0x00; i <= 0xff; i++)
	{
		if ((i % 16) == 0)
		{
			printf("\n 0x%02x: ", i);
		}
		val = read_ec(i);
		printf("%02x ", val);
	}
}

static void dump_fan_config(void)
{
        int i;
	printf("CPU Temp: %d C\n", read_ec(EC_TEMP));
	printf("Current fan speed: %d %%\n", read_ec(EC_CURRENT_FAN_SPEED));
	printf("Temp thresholds (deg):");
	for (i = 0; i < 8; i++)
	{
		printf("%3d ", read_ec(EC_TEMP_THRESHOLDS_1 + i));
	}
	putchar('\n');
	printf("Fan speeds (%%):       ");
	for (i = 0; i < 8; i++)
	{
		printf("%3d ", read_ec(EC_FAN_SPEEDS_1 + i));
	}
	putchar('\n');
}


static void
reset_speeds(void)
{
        int i;
	// LG X110 bios defaults
	static const uint8_t defaults[] = {0x00, 0x28, 0x32, 0x3c, 0x41, 0x50, 0x50, 0x55};

	for (i = 0; i < sizeof(defaults) / sizeof(defaults[0]); i++)
	{
		write_ec(EC_FAN_SPEEDS_1 + i, defaults[i]);
	}
}


int main(int argc, char *argv[])
{
	int Result;

	printf("Simple fan control utility for MSI Wind and clones\n");
	printf("USE AT YOUR OWN RISK!!\n");
	//bResult = InitializeWinIo();
        Result = ioperm(0x62,1,1);
        Result += ioperm(0x66,1,1);

	// The arg parsing is very quick & dirty (ugly)
	if (Result==0)
	{
		argc--;
		argv++;

		if (argc <= 0)
		{
			dump_fan_config();
		}
		else //		if (argc > 0)
		{
			if (strcmp(argv[0], "-f") == 0)
			{
				argc--;
				argv++;
				if (argc > 0)
				{
					int i = 0;

					if (argc > 8) argc = 8;

					while (argc > i)
					{
						//					printf("Set fan speed to %d\n", atoi(argv[0]));
						write_ec(EC_FAN_SPEEDS_1 + i, atoi(argv[0]));
						argv++;
						i++;
					}
					printf("\nDone changing fan speeds, new settings follow\n\n");
					dump_fan_config();
				}
				else
				{
					printf("Give me at least one fan speed\n");
					printf("Usage: LGXfan -f <speed0> <speed1> ... <speed7>\n");
				}
			}
			else if (strcmp(argv[0], "-r") == 0)
			{
				printf("\nResetting values to those from EN021IL1.10I bios\n\n");
				reset_speeds();
				dump_fan_config();
			}
		} // if (argc > 0)
	}
	else
	{
		printf("ioperm() failed!\n");
		exit(1);
	}
	return 0;
}



