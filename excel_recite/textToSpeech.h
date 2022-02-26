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

void ttf(string &word, bool &read);
void synthesizeSpeech(string &word);

#endif
