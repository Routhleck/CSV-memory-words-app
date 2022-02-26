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

//按钮
struct button;

//初始化按钮
struct button* createButton(int x, int y, int width, int height, COLORREF color, const char* pText);

//按钮设置
struct button* load = createButton(10 * uWidth, 10 * uHeight, 200 * uWidth, 50 * uHeight, 0xDEC4B0, "加载csv");
struct button* save = createButton(10 * uWidth, 70 * uHeight, 200 * uWidth, 50 * uHeight, 0xDEC4B0, "保存文件");
struct button* exportFile = createButton(10 * uWidth, 130 * uHeight, 200 * uWidth, 50 * uHeight, 0xDEC4B0, "导出文件");
struct button* musicOn = createButton(10 * uWidth, 200 * uHeight, 200 * uWidth, 50 * uHeight, 0x3366ff, "振作起来");
struct button* start = createButton(10 * uWidth, 300 * uHeight, 200 * uWidth, 50 * uHeight, 0xFFFFE1, "开始记忆");
struct button* reviewPlus = createButton(10 * uWidth, 360 * uHeight, 200 * uWidth, 50 * uHeight, 0xFFFFE1, "优化复习");
struct button* review = createButton(10 * uWidth, 420 * uHeight, 200 * uWidth, 50 * uHeight, 0xFFFFE1, "复习本轮");
struct button* chineseSwitch = createButton(10 * uWidth, 500 * uHeight, 200 * uWidth, 50 * uHeight, 0xFFFFE1, "释义显示");
struct button* remember = createButton(10 * uWidth, 560 * uHeight, 200 * uWidth, 50 * uHeight, 0x32CD32, "记    得");
struct button* forget = createButton(10 * uWidth, 620 * uHeight, 200 * uWidth, 50 * uHeight, 0x3C14DC, "遗    忘");
struct button* undoMemory = createButton(250 * uWidth, 650 * uHeight, 200 * uWidth, 50 * uHeight, 0xACA600, "撤销记忆");
struct button* lastWord = createButton(470 * uWidth, 650 * uHeight, 200 * uWidth, 50 * uHeight, 0xACA600, "上个单词");
struct button* undoMemoryLastWord = createButton(690 * uWidth, 650 * uHeight, 370 * uWidth, 50 * uHeight, 0xACA600, "撤销上个单词记忆");
struct button* textToSpeech = createButton(500 * uWidth, 190 * uHeight, 180 * uWidth, 65 * uHeight, 0xFFFFE1, "读 音");

double fps();//fps计算
void drawFps();//fps绘制
void drawButton(struct button* pB);//画按钮
bool mouseInButton(struct button* pB, MOUSEMSG m);//判断鼠标是否在按钮中
bool clickButton(struct button* pB, MOUSEMSG m);//判断鼠标点击按钮
void drawAllButton(bool bool_start);//绘制所有按钮
void drawMain(bool bool_chinese, char* value0, char* value1, char* value2, int value3, int value4, char* refLastWord, char* refLastClass, char* refLastChinese, int bool_history, bool last);//绘制主要内容
void drawStatus(int wordAmount, int wordMemory, int wordNeedMemory, int wordRest, int wordMaster, bool bool_start);//绘制数据
void drawStatusGraph(int wordAmount, int wordMemory, int wordNeedMemory, int wordRest, int wordMaster);//绘制数据图表
#endif 