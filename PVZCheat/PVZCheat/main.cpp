#include <iostream>
#include <Windows.h>

#define SunAddress 0x755E0C//�����ַ  00400000+355E0C
#define ColdAddress 0x755E0C//��ȴ��ַ 00400000+355E0C
#define Invincible 0x54BA6D//�޵л�ַ  00400000+14BA6D
#define ZombieHP 0x54D0C4//��ɱ��ַ  00400000+14D0C4

void SunAdd(DWORD ProcessID);//��������
void CardCold(DWORD ProcessID);//������ȴ
void PlantsInvincibility(DWORD ProcessID);//ֲ���޵�
void PlantsSeckill(DWORD ProcessID);//ֲ����ɱ

int main()
{
	/*
	* ��DEMOʵ�����ĸ����ܣ�����ǰ�������û�ַ+ƫ��ʵ�֣���������ͨ���޸Ĵ��������߼�(�����ڴ���ע��)�ķ�ʽʵ�֡�
	* ���������ŵ�����ѧϰ�ο�����淶��Ϸ
	* ����:Addsser
	* QQȺ:723274680
	*/
	DWORD Pid;//��Ž���ID
	HWND hwnd=FindWindow(NULL,L"Plants vs. Zombies");//��ȡ����
	GetWindowThreadProcessId(hwnd,&Pid);//��ȡ����ID
	//���ܺ���
	//  SunAdd(Pid);
	//  CardCold(Pid);
	//  PlantsInvincibility(Pid);
	//  PlantsSeckill(Pid);
	//��Ҫ�����ĸ����ܽ������ŵ�����whileѭ������
	while (1)
	{
		//����������
		//��ʼ
		
		//����
	}
	return 0;
}

void SunAdd(DWORD ProcessID)
{
	DWORD MAXSUN = 0x2710;//�������ֵ
	DWORD SUNCURRUNTVALUE = 0x0;//Ŀǰ��ַ
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
	DWORD COLD = 0x1;//��������ֵ
	DWORD CARDCOLDVALUE = 0x0;
	DWORD CARDNUM=0x0;//��������
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
	char DATA[] = {0x00};//�޵д���
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
	WriteProcessMemory(handle, (LPVOID)Invincible, &DATA, sizeof(BYTE), 0);
	CloseHandle(handle);
}

void PlantsSeckill(DWORD ProcessID)
{
	char DATA[] = {0xC7,0x87,0xC8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90};//��ɱ����
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
	WriteProcessMemory(handle, (LPVOID)ZombieHP, &DATA, 11*sizeof(BYTE), 0);
	CloseHandle(handle);
}