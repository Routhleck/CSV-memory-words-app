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

	
	initgraph(1280*uWidth, 720*uHeight);
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
	float rate = 0;
	string rate_s;
	string ForgetTime;
	string ReviewTime;
	string path;
	string musicPath;
	string tempText;
	LPCSTR str[6];
	vector<Word> words;
	vector<Word> tempWords;
	vector<Word>::iterator iter;
	vector<int> history;

	thread thread_ttf(ttf,ref(tempText),ref(read));
	
	thread_ttf.detach();
	//�Զ���ȡ�ļ�
	logic::autoLoad(path, words, history);
	
	while (1) 
	{
		BeginBatchDraw();
		setfillcolor(0xE16941);
		fillrectangle(0, 0, 1280 * uWidth, 720 * uHeight);
		//���ư�ť
		drawAllButton(bool_start);

		//��������ͳ��
		//drawFps();

		//��������ͳ��
		logic::calculateStatus(amount,tempWords,words,iter,wordAmount,wordMemory,wordNeedMemory,wordRest,wordMaster);
		drawStatus(wordAmount, wordMemory, wordNeedMemory, wordRest, wordMaster,bool_start);

		//ͳ��ͼ
		if (!words.empty()) {
			drawStatusGraph(wordAmount, wordMemory, wordNeedMemory, wordRest, wordMaster);
		}
		//��ʼ����
		if (bool_start == true) {
			char* refWord = (char*)words[npos].TheWord.c_str();
			char* refClass = (char*)words[npos].WordClass.c_str();
			char* refChinese = (char*)words[npos].Chinese.c_str();
			int refForget = words[npos].ForgetTime;
			int refReview = words[npos].ReviewTime;
			char* refLastWord;
			char* refLastClass;
			char* refLastChinese;
			int bool_history;
			bool last;
			
			if (npos != startPos)
			{
				refLastWord = (char*)words[npos - 1].TheWord.c_str();
				refLastClass = (char*)words[npos - 1].WordClass.c_str();
				refLastChinese = (char*)words[npos - 1].Chinese.c_str();
				bool_history = words[npos - 1].History.back();
				last = true;
			}
			else
				last = false;

			drawMain(bool_chinese, (char*)refWord, (char*)refClass, (char*)refChinese, refForget, refReview,refLastWord,refLastClass,refLastChinese,bool_history,last);
		}
		//���ּ������
		if (bool_end == true) {
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(175 * uHeight, 85 * uWidth, "����");
			outtextxy(250 * uWidth, 250 * uHeight, "����ѧϰ���");
		}
		
		//��ȡ���
		MOUSEMSG m = GetMouseMsg();

		//1�����ļ�
		if (clickButton(load, m))
		{
			logic::manualLoad(path, words, history);
		}


		//3�����ļ�
		if (clickButton(save, m))
		{
			logic::saveFile(words, path);
		}

		//4�����ļ�
		if (clickButton(exportFile, m))
		{
			logic::exportCsv(words, path);
		}

		//5��ʼ����
		if (clickButton(start, m))
		{
			logic::startMemory(npos, words, iter, amount, bool_start, bool_end, bool_chinese,startPos);
			read = true;
			thread thread_ttf(ttf, ref(words[npos].TheWord), ref(read));
			thread_ttf.detach();
		}

		//6��ϰ����
		if (clickButton(review, m))
		{
			logic::reviewMemory(npos, words, iter, amount, bool_start, bool_end, bool_chinese,startPos);
			read = true;
			thread thread_ttf(ttf, ref(words[npos].TheWord), ref(read));
			thread_ttf.detach();
		}

		//9����
		if (clickButton(musicOn, m)) {
			logic::playMusic(lerp, musicPath);
		}

		//13�Ż���ϰ
		if (clickButton(reviewPlus, m)) {
			logic::reviewOptimize(npos, words, iter, amount, wordMaster, bool_start, bool_end, bool_chinese, bool_optimize);
			read = true;
			thread thread_ttf(ttf, ref(words[npos].TheWord), ref(read));
			thread_ttf.detach();
		}

		//7�ǵ�
		if (bool_start) {
			if (clickButton(remember, m))
			{
				logic::rememberWord(npos, words, bool_stop, bool_optimize, bool_start, bool_end, amount);
				if (amount >= 0) {
					read = true;
					thread thread_ttf(ttf, ref(words[npos].TheWord), ref(read));
					thread_ttf.detach();
				}
			}

			//8����
			if (clickButton(forget, m))
			{
				logic::forgetWord(npos, words, bool_stop, bool_optimize, bool_start, bool_end, amount);
				read = true;
				thread thread_ttf(ttf, ref(words[npos].TheWord), ref(read));
				thread_ttf.detach();
			}



			//10��������
			if (clickButton(undoMemory, m)) {
				logic::undo(bool_start, bool_end, words, npos);
			}

			//11�ϸ�����
			if (clickButton(lastWord, m)) {
				if (npos > 0)
					npos--;
			}

			//12�ϸ����ʳ�������
			if (clickButton(undoMemoryLastWord, m)) {
				if (npos > 0)
					npos--;
				logic::undo(bool_start, bool_end, words, npos);
			}



			//14����
			if (clickButton(textToSpeech, m)) {
				read = true;
				thread thread_ttf(ttf, ref(words[npos].TheWord), ref(read));
				thread_ttf.detach();


			}
			//�������忪��
			if (clickButton(chineseSwitch, m)) {
				bool_chinese = !bool_chinese;
			}
		}
		EndBatchDraw();
	}
	return 0;
}

