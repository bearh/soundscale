#include "defines.h"

// For basic notes.
int status_message(int status,char *message){
	char status_chars[] = "!*?-^C";
	char status_out;
	status_out = status_chars[status-1];
	printf("[%c] %s\n",status_out,message);
	return SUCCESS;
}
int main(int argc,char *argv[]){
	//variables
	int device_num = 0;
	int error = Pa_Initialize();
	int i = 0;
	int arg_data_count = 0;
	bool audio_get_list = false;
	
	// Parse arguments
	if(argc >= 1){
		for(i = 0;i < argc;i++){
			if(arg_data_count == 0){
				if(strcmp(argv[i],"-list") == 0){
					audio_get_list = true;
				}

				
			} else {
				arg_data_count = arg_data_count-1;
			}
		}
	}

	/// Init
	status_message(stat_general,"SoundScale");
	status_message(stat_general,"Using PortAudio Version:");
	status_message(stat_general,(char *) Pa_GetVersionText());
	// Checks for PA and audio devices.
	if(error != paNoError){
		status_message(stat_critical,"PA DID NOT INITIALISE");
		return PA_INIT_FAIL;
	} else {
		status_message(stat_general,"PA INITIALIZED");
	}
	device_num = Pa_GetDeviceCount();
	if(device_num < 0){
		status_message(stat_critical,"ERROR - NO AUDIO DEVICES");
		return NO_AUDIO_DEVICES;
	} 

	// Audio Device selection. - Preformed if no device is selected;
	if(audio_get_list == true){
		printf("[*] Discovered %i Audio devices\n",device_num);
		const PaDeviceInfo *device_info;
		for(i = 0; i < device_num;i++){
		device_info = Pa_GetDeviceInfo(i);
		printf("[*] [%i] %s \n",i,device_info->name);
		}
	}


	return SUCCESS;
}
