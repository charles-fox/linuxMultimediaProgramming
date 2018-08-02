//g++ -o audioout audioout.c -lasound 

//maybe need to disable pulse ot get access to soundcard not sure if using pulse emulation layer at this level
// systemctl --user stop pulseaudio.socket
// systemctl --user stop pulseaudio.service

#include <alsa/asoundlib.h>

int main()
{
	snd_pcm_t *pcm_handle;    /*handle for pulse code modulated device */     
	snd_pcm_stream_t stream = SND_PCM_STREAM_PLAYBACK;   /* streams can be playback or record. Here we test playback */
	snd_pcm_hw_params_t *hwparams;  /* structure used to store configuration parameters */
	  
	/* The most important ALSA interfaces to the PCM devices are the "plughw" and the "hw" interface. If you use the "plughw" interface, you need not care much about the sound hardware. If your soundcard does not support the sample rate or sample format you specify, your data will be automatically converted. This also applies to the access type and the number of channels. With the "hw" interface, you have to check whether your hardware supports the configuration you would like to use. */
	char *pcm_name; 		/* Name of the PCM device, like hw:0,0 */
	pcm_name = strdup("hw:1,0");

	snd_pcm_hw_params_alloca(&hwparams);     /* Allocate the snd_pcm_hw_params_t structure on the stack. */

	/* Open PCM. The last parameter of this function is the mode. */
	/* If this is set to 0, the standard mode is used. Possible   */
	/* other values are SND_PCM_NONBLOCK and SND_PCM_ASYNC.       */ 
	/* If SND_PCM_NONBLOCK is used, read / write access to the    */
	/* PCM device will return immediately. If SND_PCM_ASYNC is    */
	/* specified, SIGIO will be emitted whenever a period has     */
	/* been completely processed by the soundcard.                */
	if (snd_pcm_open(&pcm_handle, pcm_name, stream, 0) < 0) {
	  fprintf(stderr, "Error opening PCM device %s\n", pcm_name);
	  return(-1);
	}

	/*Before we can write PCM data to the soundcard, we have to specify access type, sample format, sample rate, number of channels, number of periods and period size. First, we initialize the hwparams structure with the full configuration space of the soundcard.*/

	/* Init hwparams with full configuration space */
	if (snd_pcm_hw_params_any(pcm_handle, hwparams) < 0) {
	  fprintf(stderr, "Can not configure this PCM device.\n");
	  return(-1);
	}


	/*Information about possible configurations can be obtained with a set of functions named
	  snd_pcm_hw_params_can_<capability>
	  snd_pcm_hw_params_is_<property>
	  snd_pcm_hw_params_get_<parameter>
	The availability of the most important parameters, namely access type, buffer size, number of channels, sample format, sample rate and number of periods, can be tested with a set of functions named
	  snd_pcm_hw_params_test_<parameter> 
	These query functions are especially important if the "hw" interface is used. The configuration space can be restricted to a certain configuration with a set of functions named
	  snd_pcm_hw_params_set_<parameter>
	For this example, we assume that the soundcard can be configured for stereo playback of 16 Bit Little Endian data, sampled at 44100 Hz. Accordingly, we restrict the configuration space to match this configuration:
	*/

	int rate = 44100; /* Sample rate */
	unsigned int exact_rate;   /* Sample rate returned by */
					  /* snd_pcm_hw_params_set_rate_near */ 
	int dir;          /* exact_rate == rate --> dir = 0 */
					  /* exact_rate < rate  --> dir = -1 */
					  /* exact_rate > rate  --> dir = 1 */
	int periods = 2;       /* Number of periods */
	snd_pcm_uframes_t periodsize = 8192; /* Periodsize (bytes) */

	/*
	The access type specifies the way in which multichannel data is stored in the buffer. For INTERLEAVED access, each frame in the buffer contains the consecutive sample data for the channels. For 16 Bit stereo data, this means that the buffer contains alternating words of sample data for the left and right channel. For NONINTERLEAVED access, each period contains first all sample data for the first channel followed by the sample data for the second channel and so on.
	*/

	/* Set access type. This can be either SND_PCM_ACCESS_RW_INTERLEAVED or SND_PCM_ACCESS_RW_NONINTERLEAVED.      */
	/* There are also access types for MMAPed */
	if (snd_pcm_hw_params_set_access(pcm_handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
	  fprintf(stderr, "Error setting access.\n");
	  return(-1);
	}

	/* Set sample format */
	if (snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_LE) < 0) {
	  fprintf(stderr, "Error setting format.\n");
	  return(-1);
	}

	/* Set sample rate. If the exact rate is not supported by the hardware, use nearest possible rate. */ 
	exact_rate = rate;
	if (snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, &exact_rate, 0) < 0) {
	  fprintf(stderr, "Error setting rate.\n");
	  return(-1);
	}
	if (rate != exact_rate) {
	  fprintf(stderr, "The rate %d Hz is not supported by your hardware.\n ==> Using %d Hz instead.\n", rate, exact_rate);
	}

	/* Set number of channels */
	if (snd_pcm_hw_params_set_channels(pcm_handle, hwparams, 2) < 0) {
	  fprintf(stderr, "Error setting channels.\n");
	  return(-1);
	}

	/* Set number of periods. Periods used to be called fragments. */ 
	if (snd_pcm_hw_params_set_periods(pcm_handle, hwparams, periods, 0) < 0) {
	  fprintf(stderr, "Error setting periods.\n");
	  return(-1);
	}

	/* The unit of the buffersize depends on the function. Sometimes it is given in bytes, sometimes the number of frames has to be specified. One frame is the sample data vector for all channels. For 16 Bit stereo data, one frame has a length of four bytes. */

	/* Set buffer size (in frames). The resulting latency is given by */
	/* latency = periodsize * periods / (rate * bytes_per_frame)     */
	if (snd_pcm_hw_params_set_buffer_size(pcm_handle, hwparams, (periodsize * periods)>>2) < 0) {
	  fprintf(stderr, "Error setting buffersize.\n");
	  return(-1);
	}

	/*
	If your hardware does not support a buffersize of 2^n, you can use the function snd_pcm_hw_params_set_buffer_size_near. This works similar to snd_pcm_hw_params_set_rate_near. Now we apply the configuration to the PCM device pointed to by pcm_handle. This will also prepare the PCM device.
	*/

	/* Apply HW parameter settings to */
	/* PCM device and prepare device  */
	if (snd_pcm_hw_params(pcm_handle, hwparams) < 0) {
	  fprintf(stderr, "Error setting HW params.\n");
	  return(-1);
	}

	printf("still ok\n");





	/* After the PCM device is configured, we can start writing PCM data to it. The first write access will start the PCM playback. For interleaved write access, we use the function */
	/* Write num_frames frames from buffer data to    */ 
	/* the PCM device pointed to by pcm_handle.       */
	/* Returns the number of frames actually written. */
//	snd_pcm_sframes_t snd_pcm_writei(pcm_handle, data, num_frames);
	/* For noninterleaved access, we would have to use the function */
	/* Write num_frames frames from buffer data to    */ 
	/* the PCM device pointed to by pcm_handle.       */ 
	/* Returns the number of frames actually written. */
//	snd_pcm_sframes_t snd_pcm_writen(pcm_handle, data, num_frames);
	/*After the PCM playback is started, we have to make sure that our application sends enough data to the soundcard buffer. Otherwise, a buffer underrun will occur. After such an underrun has occured, snd_pcm_prepare should be called. A simple stereo saw wave could be generated this way:*/

	unsigned char *data;
	int pcmreturn, l1, l2;
	short s1, s2;
	int frames;

	data = (unsigned char *)malloc(periodsize);
	frames = periodsize >> 2;
	for(l1 = 0; l1 < 100; l1++) {
	  for(l2 = 0; l2 < frames; l2++) {
		s1 = (l2 % 128) * 100 - 5000;  
		s2 = (l2 % 256) * 100 - 5000;  
		data[4*l2] = (unsigned char)s1;
		data[4*l2+1] = s1 >> 8;
		data[4*l2+2] = (unsigned char)s2;
		data[4*l2+3] = s2 >> 8;
	  }
	  while ((pcmreturn = snd_pcm_writei(pcm_handle, data, frames)) < 0) {
		snd_pcm_prepare(pcm_handle);
		fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>>>>\n");
	  }
	}

	/*If we want to stop playback, we can either use snd_pcm_drop or snd_pcm_drain. The first function will immediately stop the playback and drop pending frames. The latter function will stop after pending frames have been played.*/

	/* Stop PCM device and drop pending frames */
	snd_pcm_drop(pcm_handle);



}

