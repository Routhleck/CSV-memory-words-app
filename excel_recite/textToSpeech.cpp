#include "textToSpeech.h"

void ttf(string& word, bool& read, shared_ptr<Microsoft::CognitiveServices::Speech::SpeechConfig>& config)
{
	while (read) {
		try
		{
			synthesizeSpeech(word,read,config);
		}
		catch (exception e)
		{
			cout << e.what();
		}
		
	}
	return;
}

void setConfig(shared_ptr<Microsoft::CognitiveServices::Speech::SpeechConfig>& config) {
	config = SpeechConfig::FromSubscription("13d3c84bbadd4bd3a93a2f14e5101f27", "eastasia");
	// Note: if only language is set, the default voice of that language is chosen.
	config->SetSpeechSynthesisLanguage("en-US"); // e.g. "de-DE"
	// The voice setting will overwrite language setting.
	// The voice setting will not overwrite the voice element in input SSML.
	config->SetSpeechSynthesisVoiceName("en-US-JennyNeural");
}

void synthesizeSpeech(string& word,bool &read, shared_ptr<Microsoft::CognitiveServices::Speech::SpeechConfig>& config)
{
	auto synthesizer = SpeechSynthesizer::FromConfig(config);
	auto result = synthesizer->SpeakTextAsync(word).get();
	read = false;
}