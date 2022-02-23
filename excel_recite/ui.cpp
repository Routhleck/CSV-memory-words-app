#include"ui.h"
#include<string>
using namespace std;

//��ť
struct button
{
	int x;
	int y;
	int width;
	int height;
	COLORREF color;
	char* pText;
};

//��ʼ����ť
struct button* createButton(int x, int y, int width, int height, COLORREF color, const char* pText)
{
	struct button* pB = (struct button*)malloc(sizeof(struct button));
	pB->x = x;
	pB->y = y;
	pB->width = width;
	pB->height = height;
	pB->color = color;
	pB->pText = (char*)malloc(strlen(pText) + 1);
	strcpy(pB->pText, pText);
	return pB;
}

//����ť
void drawButton(struct button* pB)
{
	setfillcolor(pB->color);
	settextstyle(35 * uWidth, 0 * uHeight, "����");
	setlinecolor(BLACK);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(pB->x, pB->y, pB->x + pB->width, pB->y + pB->height);
	outtextxy(pB->x + 30 * uWidth, pB->y + 10 * uHeight, pB->pText);
}
//�ж�����Ƿ��ڰ�ť��
bool mouseInButton(struct button* pB, MOUSEMSG m)
{
	if (pB->x < m.x && m.x <= pB->x + pB->width && pB->y < m.y && m.y <= pB->y + pB->height)
	{
		if (pB == load)
			load->color = 0xB69C88;
		else if (pB == chineseSwitch)
			chineseSwitch->color = 0xD7D7B9;
		else if (pB == save)
			save->color = 0xB69C88;
		else if (pB == exportFile)
			exportFile->color = 0xB69C88;
		else if (pB == musicOn)
			musicOn->color = 0x003399;
		else if (pB == start)
			start->color = 0xD7D7B9;
		else if (pB == review)
			review->color = 0xD7D7B9;
		else if (pB == remember)
			remember->color = 0x0AA50A;
		else if (pB == forget)
			forget->color = 0x0A00B4;
		else if (pB == undoMemory)
			undoMemory->color = 0x928700;
		else if (pB == lastWord)
			lastWord->color = 0x928700;
		else if (pB == undoMemoryLastWord)
			undoMemoryLastWord->color = 0x928700;

		return true;
	}
	if (pB == load)
		load->color = 0xDEC4B0;
	else if (pB == chineseSwitch)
		chineseSwitch->color = 0xFFFFE1;
	else if (pB == save)
		save->color = 0xDEC4B0;
	else if (pB == exportFile)
		exportFile->color = 0xDEC4B0;
	else if (pB == musicOn)
		musicOn->color = 0x3366ff;
	else if (pB == start)
		start->color = 0xFFFFE1;
	else if (pB == review)
		review->color = 0xFFFFE1;
	else if (pB == remember)
		remember->color = 0x32CD32;
	else if (pB == forget)
		forget->color = 0x3C14DC;
	else if (pB == undoMemory)
		undoMemory->color = 0xACA600;
	else if (pB == lastWord)
		lastWord->color = 0xACA600;
	else if (pB == undoMemoryLastWord)
		undoMemoryLastWord->color = 0xACA600;
	return false;
}
//�ж��������ť
bool clickButton(struct button* pB, MOUSEMSG m)
{
	if (mouseInButton(pB, m) && m.uMsg == WM_LBUTTONDOWN)
	{
		return true;
	}
	return false;

}

//�������а�ť
void drawAllButton() {
	drawButton(load);
	drawButton(save);
	drawButton(exportFile);
	drawButton(start);
	drawButton(review);
	drawButton(remember);
	drawButton(forget);
	drawButton(musicOn);
	drawButton(chineseSwitch);
	drawButton(undoMemory);
	drawButton(lastWord);
	drawButton(undoMemoryLastWord);
}

//��ʼ����ʱ����
void drawMain(bool bool_chinese,char* value0,char* value1,char* value2,int value3,int value4) {
	LPCSTR str[6];
	string ForgetTime;
	string ReviewTime;
	int correct = 0;
	float rate = 0;
	int rate_i = 0;
	std::string rate_s;
	//���õ���
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(140 * uHeight, 70 * uWidth, "����");
	str[0] = value0;
	outtextxy(250 * uWidth, 80 * uHeight, str[0]);
	//���ô���
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(50 * uHeight, 30 * uWidth, "����");
	str[1] = value1;
	outtextxy(250 * uWidth, 230 * uHeight, str[1]);

	//��������
	if (bool_chinese == true) {
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(100 * uHeight, 50 * uWidth, "����");
		str[2] = value2;
		outtextxy(250 * uWidth, 350 * uHeight, str[2]);
	}
	//������������
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30 * uHeight, 15 * uWidth, "����");
	outtextxy(370 * uWidth, 605 * uHeight, "��������:");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(40 * uHeight, 30 * uWidth, "����");
	ForgetTime = to_string(value3);
	str[3] = ForgetTime.c_str();
	outtextxy(520 * uWidth, 600 * uHeight, str[3]);

	//���ü������
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30 * uHeight, 15 * uWidth, "����");
	outtextxy(600 * uWidth, 605 * uHeight, "�������:");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(40 * uHeight, 30 * uWidth, "����");
	ReviewTime = to_string(value4);
	str[4] = ReviewTime.c_str();
	outtextxy(750 * uWidth, 600 * uHeight, str[4]);

	//����������
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30 * uHeight, 15 * uWidth, "����");
	outtextxy(870 * uWidth, 605 * uHeight, "������:");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(40 * uHeight, 30 * uWidth, "����");
	if (value4 == 0)
		correct = 1;
	else
		correct = value4;
	rate = (float)value3 / (float)correct;
	rate_i = rate * 100;
	rate_s = to_string(rate_i);
	str[5] = rate_s.c_str();
	outtextxy(1000 * uWidth, 600 * uHeight, str[5]);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30 * uHeight, 15 * uWidth, "����");
	outtextxy(1100 * uWidth, 605 * uHeight, "%");
}

//��������
void drawStatus(int wordAmount, int wordMemory, int wordNeedMemory, int wordRest, int wordMaster) {
	string temp0,temp1,temp2,temp3,temp4;
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30 * uHeight, 15 * uWidth, "����");
	LPCSTR str[5];
	temp0 = to_string(wordAmount);
	str[0] = temp0.c_str();

	temp1 = to_string(wordMemory);
	str[1] = temp1.c_str();

	temp2 = to_string(wordNeedMemory);
	str[2] = temp2.c_str();

	temp3 = to_string(wordRest);
	str[3] = temp3.c_str();

	temp4 = to_string(wordMaster);
	str[4] = temp4.c_str();
	outtextxy(250 * uWidth, 20 * uHeight, "��������:");
	outtextxy(390 * uWidth, 20 * uHeight, str[0]);

	outtextxy(480 * uWidth, 20 * uHeight, "�Ѽ���:");
	outtextxy(590 * uWidth, 20 * uHeight, str[1]);

	outtextxy(680 * uWidth, 20 * uHeight, "�������:");
	outtextxy(820 * uWidth, 20 * uHeight, str[2]);

	outtextxy(250 * uWidth, 50 * uHeight, "ѧϰʣ��:");
	outtextxy(390 * uWidth, 50 * uHeight, str[3]);

	outtextxy(480 * uWidth, 50 * uHeight, "������:");
	outtextxy(590 * uWidth, 50 * uHeight, str[4]);

}