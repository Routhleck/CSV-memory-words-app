#include "logic.h"
#include "ui.h"
#include<stdio.h>
#include <conio.h>
#include <thread>
#include <Mmsystem.h>
#include "textToSpeech.h"
#pragma comment(lib,"WinMM.Lib")
using namespace std;

int main() {
	initgraph(1280 * uWidth, 720 * uHeight);
	initgraph(1280 * uWidth, 720 * uHeight);
	setfillcolor(0xE16941);
	fillrectangle(0, 0, 1280 * uWidth, 720 * uHeight);
	bool bool_start = false;
	bool bool_end = false;
	bool bool_review = false;
	bool lerp = false;
	bool bool_chinese = false;
	bool bool_optimize = false;
	bool bool_stop = false;
	bool read = false;
	int amount = 0;
	int npos = 0;
	int correct = 0;
	int max_review = 0;
	int rate_i = 0;
	int wordAmount = 0;
	int wordMemory = 0;
	int wordNeedMemory = 0;
	int wordRest = 0;
	int wordMaster = 0;
	int temp1 = 0;
	int temp2 = 0;
	int startPos = 0;
	int lastPos = 0;
	float rate = 0;
	string rate_s;
	string ForgetTime;
	string ReviewTime;
	string path;
	string musicPath;
	string tempText;
	vector<Word> words;
	vector<Word> tempWords;
	vector<Word>::iterator iter;
	vector<int> history;

	thread thread_ttf(ttf, ref(tempText), ref(read));

	thread_ttf.detach();
	//自动读取文件
	logic::autoLoad(path, words, history);
	

	while (1)
	{
		BeginBatchDraw();
		setfillcolor(0xE16941);
		fillrectangle(0, 0, 1280 * uWidth, 720 * uHeight);
		//绘制按钮
		drawAllButton(bool_start);

		//性能数据统计
		//drawFps();

		//单词数据统计
		logic::calculateStatus(amount, tempWords, words, iter, wordAmount, wordMemory, wordNeedMemory, wordRest, wordMaster);
		drawStatus(wordAmount, wordMemory, wordNeedMemory, wordRest, wordMaster, bool_start);

		//统计图
		if (!words.empty()) {
			drawStatusGraph(wordAmount, wordMemory, wordNeedMemory, wordRest, wordMaster);
		}
		//开始记忆
		if (bool_start == true) {
			char* refWord = (char*)words[npos].TheWord.c_str();
			char* refClass = (char*)words[npos].WordClass.c_str();
			char* refChinese = (char*)words[npos].Chinese.c_str();
			int refForget = words[npos].ForgetTime;
			int refReview = words[npos].ReviewTime;
			char* refLastWord=0;
			char* refLastClass=0;
			char* refLastChinese=0;
			int bool_history=0;
			bool last;

			if (npos != startPos)
			{
				try
				{
					refLastWord = (char*)words[lastPos].TheWord.c_str();
					refLastClass = (char*)words[lastPos].WordClass.c_str();
					refLastChinese = (char*)words[lastPos].Chinese.c_str();
					bool_history = words[lastPos].History.back();
					last = true;
				}
				catch (const std::exception&)
				{

				}
				
				
			}
			else
				last = false;

			drawMain(bool_chinese, (char*)refWord, (char*)refClass, (char*)refChinese, refForget, refReview, refLastWord, refLastClass, refLastChinese, bool_history, last);
		}
		//本轮记忆完成
		if (bool_end == true) {
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(175 * uHeight, 85 * uWidth, "黑体");
			outtextxy(250 * uWidth, 250 * uHeight, "本轮学习完成");
		}

		//获取光标
		MOUSEMSG m = GetMouseMsg();

		//1加载文件
		if (clickButton(load, m))
		{
			logic::manualLoad(path, words, history);
		}

		//3保存文件
		if (clickButton(save, m))
		{
			logic::saveFile(words, path);
		}

		//4导出文件
		if (clickButton(exportFile, m))
		{
			logic::exportCsv(words, path);
		}

		//5开始记忆
		if (clickButton(start, m))
		{
			logic::clearHistory();
			logic::saveHistory(0);
			logic::startMemory(npos, words, iter, amount, bool_start, bool_end, bool_chinese, startPos);
			if (amount >= 0) {
				read = true;
				thread thread_ttf(ttf, ref(words[npos].TheWord), ref(read));
				thread_ttf.detach();
			}
		}

		//6复习本轮
		if (clickButton(review, m))
		{
			logic::clearHistory();
			logic::saveHistory(2);
			logic::reviewMemory(npos, words, iter, amount, bool_start, bool_end, bool_chinese, startPos);
			if (amount >= 0) {
				read = true;
				thread thread_ttf(ttf, ref(words[npos].TheWord), ref(read));
				thread_ttf.detach();
			}
		}

		//9音乐
		if (clickButton(musicOn, m)) {
			logic::playMusic(lerp, musicPath);
		}

		//13优化复习
		if (clickButton(reviewPlus, m)) {
			logic::clearHistory();
			logic::saveHistory(1);
			logic::reviewOptimize(npos, words, iter, amount, wordMaster, bool_start, bool_end, bool_chinese, bool_optimize);
			if (amount >= 0) {
				read = true;
				thread thread_ttf(ttf, ref(words[npos].TheWord), ref(read));
				thread_ttf.detach();
			}
		}

		//7记得
		if (bool_start) {
			if (clickButton(remember, m))
			{
				logic::saveHistory(3);
				logic::rememberWord(npos, words, bool_stop, bool_optimize, bool_start, bool_end, amount,lastPos);
				if (amount >= 0) {
					read = true;
					thread thread_ttf(ttf, ref(words[npos].TheWord), ref(read));
					thread_ttf.detach();
				}
			}

			//8遗忘
			if (clickButton(forget, m))
			{
				logic::saveHistory(4);
				logic::forgetWord(npos, words, bool_stop, bool_optimize, bool_start, bool_end, amount, lastPos);
				if (amount >= 0) {
					read = true;
					thread thread_ttf(ttf, ref(words[npos].TheWord), ref(read));
					thread_ttf.detach();
				}
			}

			//10撤销记忆
			if (clickButton(undoMemory, m)) {
				logic::saveHistory(5);
				logic::undo(bool_start, bool_end, words, npos);
			}

			//11上个单词
			if (clickButton(lastWord, m)) {
				logic::saveHistory(6);
				if (npos > 0)
					npos--;
			}

			//12上个单词撤销记忆
			if (clickButton(undoMemoryLastWord, m)) {
				if (npos > 0) {
					logic::saveHistory(7);
					npos--;
					logic::undo(bool_start, bool_end, words, npos);
				}
			}

			//14读音
			if (clickButton(textToSpeech, m)) {
				read = true;
				thread thread_ttf(ttf, ref(words[npos].TheWord), ref(read));
				thread_ttf.detach();
			}

			

			//中文释义开关
			if (clickButton(chineseSwitch, m)) {
				bool_chinese = !bool_chinese;
			}
		}
		else {
			//15加载历史
			if (clickButton(loadHistory, m)) {
				logic::readHistory(npos, words, iter, amount, bool_start, bool_end, bool_chinese, startPos, wordMaster, bool_optimize, lastPos, bool_stop);
			}
		}

		EndBatchDraw();
	}
	return 0;
}