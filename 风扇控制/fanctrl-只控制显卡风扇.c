// Based on LGXfan created by Tord Lindstrom (pukko@home.se)
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/io.h>
#include <unistd.h>
//These can be found in  http://wiki.laptop.org/images/a/ab/KB3700-ds-01.pdf 
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
// For read_ec & write_ec command sequence see
// section "4.10.1.4 EC Command Program Sequence" in
// http://wiki.laptop.org/images/a/ab/KB3700-ds-01.pdf 
static int wait_ec(const uint32_t port, const uint32_t flag, const char value)//当port读出的信息为value时返回0，超时是返回1
{
	uint8_t data;
	int i;

	i = 0;
	data = inb(port);//inb()为关键函数，从I/O端口读取一个字节

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
	outb(EC_SC_READ_CMD, EC_SC);//写入字节，对应文档中的Write EC_CMD with 80h

	wait_ec(EC_SC, IBF, 0);//等待SCI转变为IBF即0
	outb(port, EC_DATA);//向EC_DATA中写入读取地址

	//wait_ec(EC_SC, EC_SC_IBF_FREE);
	wait_ec(EC_SC, OBF, 1);//等待SCI转变为OBF即1
	value = inb(EC_DATA);//将读取到的值赋给value

	return value;//返回读取信息
}

static void write_ec(const uint32_t port, const uint8_t value)
{
	wait_ec(EC_SC, IBF, 0);//等待EC
	outb(EC_SC_WRITE_CMD, EC_SC);//向82端口写入Weite EC命令

	wait_ec(EC_SC, IBF, 0);//等待SCI转变为IBF即0
	outb(port, EC_DATA);//向EC DATA写入需要写入的地址

	wait_ec(EC_SC, IBF, 0);//等待SCI变成IBF
	outb(value, EC_DATA);//向端口写入数据

	wait_ec(EC_SC, IBF, 0);//等待SCI转变成IBF即0

	return;
}

static void do_ec(const uint32_t cmd, const uint32_t port, const uint8_t value)//是用来测试用的，在test_fan中使用过
{
	wait_ec(EC_SC, IBF, 0);//和Write以及Read类似
	outb(cmd, EC_SC);

	wait_ec(EC_SC, IBF, 0);
	outb(port, EC_DATA);

	wait_ec(EC_SC, IBF, 0);
	outb(value, EC_DATA);

	wait_ec(EC_SC, IBF, 0);

	return;
}

static void dump_fan_config(void)
{
	printf("Dump FAN\n");
        int raw_duty = read_ec(0xCE);
        int val_duty = (int) ((double) raw_duty / 255.0 * 100.0);
	int raw_rpm = (read_ec(0xD0) << 8) + (read_ec(0xD1));
	int val_rpm;
	if (raw_rpm == 0)
		val_rpm = 0;
	else
		val_rpm = 2156220 / raw_rpm;
	printf("FAN Duty: %d%%\n", val_duty);
	printf("FAN RPMs: %d RPM\n", val_rpm);
	printf("CPU Temp: %d°C\n", read_ec(0x07));
}

static void test_fan_config(int duty_percentage)
{
	double v_d = ((double) duty_percentage) / 100.0 * 255.0;
	int v_i = (int) v_d;
	printf("Test FAN %d%% to %d\n", duty_percentage, v_i);
	//do_ec(0x99, 0x01, v_i);//控制CPU风扇
	do_ec(0x99, 0x02, v_i);//控制显卡风扇
	dump_fan_config();
}

int main(int argc, char *argv[])
{
	int Result;

	printf("Simple fan control utility for Clevo computer\n");
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
		else
		{
			test_fan_config(atoi(*argv));
		}
	}
	else
	{
		printf("ioperm() failed!\n");
		exit(1);
	}
	return 0;
}


