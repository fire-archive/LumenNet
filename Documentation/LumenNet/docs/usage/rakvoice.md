---
title: "RakVoice"
excerpt: ""
---
[block:api-header]
{
  "type": "basic",
  "title": "Real time voice communication"
}
[/block]
RakVoice is a feature of RakNet that allows real time voice communication at a cost of only ~2200 bytes per second at 8000 16 bit samples per second. It uses Speex ([http://www.speex.org/](http://www.speex.org/)) to do the encoding. RakVoice is plugin class that makes it easier to encode, send, decode, and relay raw sound data.  
Note that RakVoice is not part of the RakNet core, so you'll need to add it to your project.  

To get an instance of RakVoice just allocate one with new, or have global object handy.  

RakVoice rakVoice;  

Since RakVoice is a plugin, you need to attach it to a peer.  

rakPeer->AttachPlugin(&rakVoice);  

initialize the class with the sample rate and the size of the buffer to process. A buffer size of 512 bytes is a reasonable value when using frequencies of 8000hz.  
The buffer size is the number of bytes to encode at a time, and the number of bytes returned by the decoder. This is normally the same size you want to lock the sound buffer by. Encoding will reduce the packet size by about 75%.  

rakVoice.Init(8000, 512);  

When data comes in on the sound buffer from the microphone, you should call SendFrame, passing the SystemAddress of the recipient system, and a pointer to the buffer to encode. Unlike normal API send calls, you cannot broadcast voice packets because each encoder and decoder is a matched pair. Therefore, you must always specify the SystemAddress so the sender knows which encoder to use. To broadcast, send it to everyone individually. Note that the size of the input buffer must match the buffer size we set earlier. For example:  

rakVoice.SendFrame(recipientSystemAddress, (char*)inputBuffer);  

In the other system, where data arrives, depending on the sound engine you are using, you'll probably have circular sound buffer, which you'll need to feed with the decoded data you receive from RakVoice. Every time your sound engine needs data to play, you should call ReceiveFrame. It will write a buffer of sound at the passed pointer, or just just silence if no new data was available. Once again, remember that the data returned has the same size you specified in Init (see above).  

rakVoice.ReceiveFrame((char*)outbufffer);  

The last point of note is that RakVoice requires all clients in a chat session to be aware of all other clients' connection states. The reasons for this are:

*   1\. You need to call SendFrame with a specific recipient for broadcasting.
*   2\. You may want to call CloseVoiceChannel, to stop communications with a particular system.

RakVoice only provides a means to encode and decode raw sound data, and means to communicate with the network. It does not include a mechanism to play or record sound. However, two samples are provived as an example on how to integrate with sound engines:  

_\Samples\RakVoiceFMOD_ - Provides an easy to use class to integrate RakVoice with the well known [FMOD](http://www.fmod.org/) sound engine.  
_\Samples\RakVoice_ - An example on how to integrate RakVoice with the free and open-source PortAudio sound engine.  

**The source to PortAudio ([http://www.portaudio.com/](http://www.portaudio.com/)) and Speex ([http://www.speex.org/](http://www.speex.org/)) are included in RakNet and can be found in the root directory for rebuilding on other platforms. These are independent open-source APIs and are not owned by me nor do I provide support for them. Please refer to the respective webpages for more information on these APIs and the included license agreements for them.**</td>