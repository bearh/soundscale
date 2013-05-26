#include "defines.h"

// For basic notes.
// I want to use this for all text output so I can control how all output
// is dealt with (i.e, writing to file, not showing at all, etc)
int status_message(int status,char *message){
	char status_chars[] = "!*?-^C";
	char status_out;
	status_out = status_chars[status-1];
	printf("[%c] %s\n",status_out,message);
	return SUCCESS;
}


// Main deals with checking all the devices and arguments.
// It will call another function to do the actual work.
int main(int argc,char *argv[]){
	//variables
	int device_num = 0;
	int error = Pa_Initialize();
	int i = 0;
	int arg_data_count = 0;
	bool audio_get_list = false;
	bool input_wanted = false;
	int device_chosen = 0;
	const PaDeviceInfo *device_info;
	char user_select_device[8];
	PaStreamParameters input_stream_param;

	// Parse arguments
	if(argc >= 1){
		for(i = 0;i < argc;i++){
			if(arg_data_count == 0){
				// Prints a list of all audio devices.
				if(strcmp(argv[i],"-list") == 0){
					audio_get_list = true;
				}
				// Same as -list, but lets you select which one you use.
				if(strcmp(argv[i],"-input") == 0){
					audio_get_list = true;
					input_wanted = true;
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

	// Audio Device selection. This can be cleaned up.
	if(audio_get_list == true){
		printf("[*] Discovered %i Audio devices\n",device_num);
		for(i = 0; i < device_num;i++){
			device_info = Pa_GetDeviceInfo(i);
			printf("[*] [%i] %s \n",i,device_info->name);
		}
		if(input_wanted == true){
			printf("[*] Please select input: ");
			scanf("%s",user_select_device);
			if(atoi(user_select_device) < device_num && atoi(user_select_device) >= 0){
				device_chosen = atoi(user_select_device);
				input_stream_param.device = device_chosen;
			} else {
				// Maybe ask user?
				input_stream_param.device = device_chosen  = Pa_GetDefaultInputDevice();
			}
		} else if(input_wanted == false){
			return SUCCESS;
		}
	} else {
		if(device_chosen > 0 && device_chosen <= device_num){
			input_stream_param.device = device_chosen;
			
		} else {
			input_stream_param.device = Pa_GetDefaultInputDevice();
			if(input_stream_param.device == paNoDevice){
				status_message(stat_critical,"NO DEFAULT INPUT DEVICE, EXITING");
				return FAILURE;
			}
		}
	}
	status_message(stat_general,"Using device:");
	device_info = Pa_GetDeviceInfo(input_stream_param.device);
	status_message(stat_general,(char *)device_info->name);
	return SUCCESS;
}
