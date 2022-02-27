#include"ui.h"
#include<string>
#include <chrono>
using namespace std;
using namespace std::chrono;

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
		else if (pB == reviewPlus)
			reviewPlus->color = 0xD7D7B9;
		else if (pB == textToSpeech)
			textToSpeech->color = 0xD7D7B9;
		else if (pB == loadHistory)
			loadHistory->color = 0xB69C88;

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
	else if (pB == reviewPlus)
		reviewPlus->color = 0xFFFFE1;
	else if (pB == textToSpeech)
		textToSpeech->color = 0xFFFFE1;
	else if (pB == loadHistory)
		loadHistory->color = 0xDEC4B0;
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

double fps() {
	static double fps = 0.0;
	static int frameCount = 0;
	static auto lastTime = system_clock::now();
	static auto curTime = system_clock::now();

	curTime = system_clock::now();

	auto duration = duration_cast<microseconds>(curTime - lastTime);
	double duration_s = double(duration.count()) * microseconds::period::num / microseconds::period::den;

	if (duration_s > 2)//2��֮��ʼͳ��FPS
	{
		fps = frameCount / duration_s;
		frameCount = 0;
		lastTime = curTime;
	}

	++frameCount;

	return fps;
}

void drawFps()
{
	TCHAR* c_fps = 0;
	_itoa((int)fps(), c_fps, 10);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20 * uHeight, 10 * uWidth, "����");
	outtextxy(200 * uWidth, 0 * uHeight, "FPS:");
	outtextxy(240 * uWidth, 0 * uHeight, c_fps);
}

//�������а�ť
void drawAllButton(bool bool_start) {

	
	drawButton(musicOn);
	if (bool_start) {
		drawButton(remember);
		drawButton(forget);
		drawButton(chineseSwitch);
		drawButton(undoMemory);
		drawButton(lastWord);
		drawButton(undoMemoryLastWord);
		drawButton(textToSpeech);
	}
	else {
		drawButton(load);
		drawButton(save);
		drawButton(exportFile);
		drawButton(loadHistory);
		drawButton(start);
		drawButton(review);
		drawButton(reviewPlus);
	}
}

//��ʼ����ʱ����
void drawMain(bool bool_chinese, char* value0, char* value1, char* value2, int value3, int value4, char* refLastWord, char* refLastClass, char* refLastChinese, int bool_history, bool last) {
	LPCSTR str[9];
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
	outtextxy(250 * uWidth, 270 * uHeight, str[0]);
	//���ô���
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(50 * uHeight, 30 * uWidth, "����");
	str[1] = value1;
	outtextxy(250 * uWidth, 400 * uHeight, str[1]);

	//��������
	if (bool_chinese == true) {
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(100 * uHeight, 50 * uWidth, "����");
		str[2] = value2;
		outtextxy(250 * uWidth, 450 * uHeight, str[2]);
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

	//�����ϸ�����
	//
	if (last) {
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(30 * uHeight, 15 * uWidth, "����");
		outtextxy(700 * uWidth, 190 * uHeight, "�ϸ�����:");

		//���õ���
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(30 * uHeight, 15 * uWidth, "����");
		str[6] = refLastWord;
		outtextxy(840 * uWidth, 190 * uHeight, str[6]);

		//���ô���
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(30 * uHeight, 15 * uWidth, "����");
		str[7] = refLastClass;
		outtextxy(840 * uWidth, 230 * uHeight, str[7]);

		//��������
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(30 * uHeight, 15 * uWidth, "����");
		str[8] = refLastChinese;
		outtextxy(900 * uWidth, 230 * uHeight, str[8]);

		//�����Ƿ����
		if (bool_history == 0) {
			settextcolor(GREEN);
			setbkmode(TRANSPARENT);
			settextstyle(30 * uHeight, 15 * uWidth, "����");
			outtextxy(730 * uWidth, 230 * uHeight, "�ǵ�");
		}
		else if (bool_history == 1) {
			settextcolor(RED);
			setbkmode(TRANSPARENT);
			settextstyle(30 * uHeight, 15 * uWidth, "����");
			outtextxy(730 * uWidth, 230 * uHeight, "����");
		}
	}
}

//��������
void drawStatus(int wordAmount, int wordMemory, int wordNeedMemory, int wordRest, int wordMaster, bool bool_start) {
	string temp0, temp1, temp2, temp3, temp4;
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
	outtextxy(250 * uWidth, 30 * uHeight, "��������:");
	outtextxy(390 * uWidth, 30 * uHeight, str[0]);

	outtextxy(250 * uWidth, 85 * uHeight, "�Ѽ���:");
	outtextxy(390 * uWidth, 85 * uHeight, str[1]);

	outtextxy(250 * uWidth, 190 * uHeight, "�������:");
	outtextxy(400 * uWidth, 190 * uHeight, str[2]);

	if (bool_start == true)
	{
		outtextxy(250 * uWidth, 230 * uHeight, "ѧϰʣ��:");
		outtextxy(400 * uWidth, 230 * uHeight, str[3]);
	}

	outtextxy(250 * uWidth, 135 * uHeight, "������:");
	outtextxy(390 * uWidth, 135 * uHeight, str[4]);
}

//��������ͳ��ͼ
void drawStatusGraph(int wordAmount, int wordMemory, int wordNeedMemory, int wordRest, int wordMaster) {
	float rateMemory = (float)wordMemory / (float)wordAmount;
	float rateMaster = (float)wordMaster / (float)wordAmount;
	setfillcolor(0x2079F4);
	setlinecolor(0x2079F4);
	fillrectangle(480 * uWidth, 20 * uHeight, 1250 * uWidth, 70 * uHeight);
	setfillcolor(0x988FF5);
	setlinecolor(0x988FF5);
	fillrectangle(480 * uWidth, 71 * uHeight, 480 * uWidth + rateMemory * 770 * uWidth, 120 * uHeight);
	setfillcolor(0x280284);
	setlinecolor(0x280284);
	fillrectangle(480 * uWidth, 121 * uHeight, 480 * uWidth + rateMaster * 770 * uWidth, 170 * uHeight);
}