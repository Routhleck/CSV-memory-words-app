#pragma once
#ifndef   TEXTTOSPEECH
#define   TEXTTOSPEECH
#include <iostream>
#include <fstream>
#include <string>
#include <speechapi_cxx.h>
#include <Windows.h>

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

void ttf(string& word, bool& read, shared_ptr<Microsoft::CognitiveServices::Speech::SpeechConfig>& config);
void setConfig(shared_ptr<Microsoft::CognitiveServices::Speech::SpeechConfig>& config);
void synthesizeSpeech(string& word,bool& read, shared_ptr<Microsoft::CognitiveServices::Speech::SpeechConfig>& config);

#endif
