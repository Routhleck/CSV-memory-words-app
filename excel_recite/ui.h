#pragma once
#ifndef   UI
#define   UI
#include<graphics.h>
#include<vector>

using namespace std;
float Width = GetSystemMetrics(SM_CXSCREEN);
float Height = GetSystemMetrics(SM_CYSCREEN);
float uWidth = (Width / 1920)*1.2;
float uHeight = (Height / 1080)*1.2;

//��ť
struct button;

//��ʼ����ť
struct button* createButton(int x, int y, int width, int height, COLORREF color, const char* pText);

//��ť����
struct button* load = createButton(10 * uWidth, 10 * uHeight, 200 * uWidth, 50 * uHeight, 0xDEC4B0, "����csv");
struct button* save = createButton(10 * uWidth, 70 * uHeight, 200 * uWidth, 50 * uHeight, 0xDEC4B0, "�����ļ�");
struct button* exportFile = createButton(10 * uWidth, 130 * uHeight, 200 * uWidth, 50 * uHeight, 0xDEC4B0, "�����ļ�");
struct button* musicOn = createButton(10 * uWidth, 200 * uHeight, 200 * uWidth, 50 * uHeight, 0x3366ff, "��������");
struct button* start = createButton(10 * uWidth, 300 * uHeight, 200 * uWidth, 50 * uHeight, 0xFFFFE1, "��ʼ����");
struct button* reviewPlus = createButton(10 * uWidth, 360 * uHeight, 200 * uWidth, 50 * uHeight, 0xFFFFE1, "�Ż���ϰ");
struct button* review = createButton(10 * uWidth, 420 * uHeight, 200 * uWidth, 50 * uHeight, 0xFFFFE1, "��ϰ����");
struct button* chineseSwitch = createButton(10 * uWidth, 500 * uHeight, 200 * uWidth, 50 * uHeight, 0xFFFFE1, "������ʾ");
struct button* remember = createButton(10 * uWidth, 560 * uHeight, 200 * uWidth, 50 * uHeight, 0x32CD32, "��    ��");
struct button* forget = createButton(10 * uWidth, 620 * uHeight, 200 * uWidth, 50 * uHeight, 0x3C14DC, "��    ��");
struct button* undoMemory = createButton(250 * uWidth, 650 * uHeight, 200 * uWidth, 50 * uHeight, 0xACA600, "��������");
struct button* lastWord = createButton(470 * uWidth, 650 * uHeight, 200 * uWidth, 50 * uHeight, 0xACA600, "�ϸ�����");
struct button* undoMemoryLastWord = createButton(690 * uWidth, 650 * uHeight, 370 * uWidth, 50 * uHeight, 0xACA600, "�����ϸ����ʼ���");
struct button* textToSpeech = createButton(500 * uWidth, 190 * uHeight, 180 * uWidth, 65 * uHeight, 0xFFFFE1, "�� ��");

double fps();//fps����
void drawFps();//fps����
void drawButton(struct button* pB);//����ť
bool mouseInButton(struct button* pB, MOUSEMSG m);//�ж�����Ƿ��ڰ�ť��
bool clickButton(struct button* pB, MOUSEMSG m);//�ж��������ť
void drawAllButton(bool bool_start);//�������а�ť
void drawMain(bool bool_chinese, char* value0, char* value1, char* value2, int value3, int value4, char* refLastWord, char* refLastClass, char* refLastChinese, int bool_history, bool last);//������Ҫ����
void drawStatus(int wordAmount, int wordMemory, int wordNeedMemory, int wordRest, int wordMaster, bool bool_start);//��������
void drawStatusGraph(int wordAmount, int wordMemory, int wordNeedMemory, int wordRest, int wordMaster);//��������ͼ��
#endif 