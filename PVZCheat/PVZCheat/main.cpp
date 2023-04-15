#include <iostream>
#include <Windows.h>

#define SunAddress 0x755E0C//阳光基址  00400000+355E0C
#define ColdAddress 0x755E0C//冷却基址 00400000+355E0C
#define Invincible 0x54BA6D//无敌基址  00400000+14BA6D
#define ZombieHP 0x54D0C4//秒杀基址  00400000+14D0C4

void SunAdd(DWORD ProcessID);//阳光增加
void CardCold(DWORD ProcessID);//卡槽冷却
void PlantsInvincibility(DWORD ProcessID);//植物无敌
void PlantsSeckill(DWORD ProcessID);//植物秒杀

int main()
{
	/*
	* 此DEMO实现了四个功能，其中前两个是用基址+偏移实现，后两个是通过修改代码运行逻辑(类似于代码注入)的方式实现。
	* 仅供想入门的朋友学习参考，请规范游戏
	* 作者:Addsser
	* QQ群:723274680
	*/
	DWORD Pid;//存放进程ID
	HWND hwnd=FindWindow(NULL,L"Plants vs. Zombies");//获取窗口
	GetWindowThreadProcessId(hwnd,&Pid);//获取进程ID
	//功能函数
	//  SunAdd(Pid);
	//  CardCold(Pid);
	//  PlantsInvincibility(Pid);
	//  PlantsSeckill(Pid);
	//想要锁定哪个功能将函数放到下面while循环即可
	while (1)
	{
		//函数放这里
		//开始
		
		//结束
	}
	return 0;
}

void SunAdd(DWORD ProcessID)
{
	DWORD MAXSUN = 0x2710;//阳光最大值
	DWORD SUNCURRUNTVALUE = 0x0;//目前地址
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS,FALSE, ProcessID);
	ReadProcessMemory(handle,(LPVOID)SunAddress, &SUNCURRUNTVALUE,sizeof(int),0);
	SUNCURRUNTVALUE = SUNCURRUNTVALUE + 0x868;
	ReadProcessMemory(handle, (LPVOID)SUNCURRUNTVALUE, &SUNCURRUNTVALUE, sizeof(int), 0);
	SUNCURRUNTVALUE = SUNCURRUNTVALUE + 0x5578;
	WriteProcessMemory(handle, (LPVOID)SUNCURRUNTVALUE, &MAXSUN, sizeof(int), 0);
	CloseHandle(handle);
}
void CardCold(DWORD ProcessID)
{
	DWORD COLD = 0x1;//卡槽锁定值
	DWORD CARDCOLDVALUE = 0x0;
	DWORD CARDNUM=0x0;//卡槽数量
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
	ReadProcessMemory(handle, (LPVOID)ColdAddress, &CARDNUM, sizeof(int), 0);
	CARDNUM = CARDNUM + 0x868;
	ReadProcessMemory(handle, (LPVOID)CARDNUM, &CARDNUM, sizeof(int), 0);
	CARDNUM = CARDNUM + 0x15C;
	ReadProcessMemory(handle, (LPVOID)CARDNUM, &CARDNUM, sizeof(int), 0);
	CARDNUM = CARDNUM + 0x70 -0x4C;
	ReadProcessMemory(handle, (LPVOID)CARDNUM, &CARDNUM, sizeof(int), 0);
	for (int i=0;i< CARDNUM;i++)
	{
		ReadProcessMemory(handle, (LPVOID)ColdAddress, &CARDCOLDVALUE, sizeof(int), 0);
		CARDCOLDVALUE = CARDCOLDVALUE + 0x868;
		ReadProcessMemory(handle, (LPVOID)CARDCOLDVALUE, &CARDCOLDVALUE, sizeof(int), 0);
		CARDCOLDVALUE = CARDCOLDVALUE + 0x15C;
		ReadProcessMemory(handle, (LPVOID)CARDCOLDVALUE, &CARDCOLDVALUE, sizeof(int), 0);
		CARDCOLDVALUE = CARDCOLDVALUE + 0x70+i*0x50;
		WriteProcessMemory(handle, (LPVOID)CARDCOLDVALUE, &COLD, sizeof(int), 0);
	}
	CloseHandle(handle);
}

void PlantsInvincibility(DWORD ProcessID)
{
	char DATA[] = {0x00};//无敌代码
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
	WriteProcessMemory(handle, (LPVOID)Invincible, &DATA, sizeof(BYTE), 0);
	CloseHandle(handle);
}

void PlantsSeckill(DWORD ProcessID)
{
	char DATA[] = {0xC7,0x87,0xC8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90};//秒杀代码
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
	WriteProcessMemory(handle, (LPVOID)ZombieHP, &DATA, 11*sizeof(BYTE), 0);
	CloseHandle(handle);
}