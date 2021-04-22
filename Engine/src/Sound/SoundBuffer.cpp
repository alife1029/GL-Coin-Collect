#include "Engine/Sound/SoundBuffer.h"
#include <sndfile/sndfile.h>
#include <AL/al.h>
#include <AL/alext.h>
#include <inttypes.h>
#include <algorithm>

namespace engine {

	SoundBuffer* SoundBuffer::m_Instance = nullptr;

	SoundBuffer* SoundBuffer::Get()
	{
		if (m_Instance == nullptr) 
			m_Instance = new SoundBuffer();
		
		return m_Instance;
	}

	uint32_t SoundBuffer::LoadSoundEffect(const std::string& fileName)
	{
		if (m_SoundEffects.count(fileName))
			return m_SoundEffects[fileName];

		ALenum err, format;
		ALuint buffer;
		SNDFILE* sndfile;
		SF_INFO sfinfo;
		short* membuf;
		sf_count_t numFrames;
		ALsizei numBytes;

		// Open audio file and check that it's usable
		sndfile = sf_open(fileName.c_str(), SFM_READ, &sfinfo);
		if (!sndfile)
		{
			printf("Could not open audio in %s: %s\n", fileName.c_str(), sf_strerror(sndfile));
			return 0;
		}
		if (sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
		{
			printf("Bad sample count in %s (%" PRId64 ")\n", fileName.c_str(), sfinfo.frames);
			sf_close(sndfile);
			return 0;
		}

		// Get the sound format and figure out the OpenAL format
		format = AL_NONE;
		if (sfinfo.channels == 1)
			format = AL_FORMAT_MONO16;
		else if (sfinfo.channels == 2)
			format = AL_FORMAT_STEREO16;
		else if (sfinfo.channels == 3 && sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			format = AL_FORMAT_BFORMAT2D_16;
		else if (sfinfo.channels == 4 && sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			format = AL_FORMAT_BFORMAT3D_16;
		
		if (!format)
		{
			printf("Unsupported channel count: %d\n", sfinfo.channels);
			sf_close(sndfile);
			return 0;
		}

		// Decode the whole audio file to a buffer
		membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));
		numFrames = sf_readf_short(sndfile, membuf, sfinfo.frames);
		if (numFrames < 1)
		{
			free(membuf);
			sf_close(sndfile);
			printf("Failed to read samples in %s (%" PRId64 ")\n", fileName.c_str(), numFrames);
			return 0;
		}
		numBytes = (ALsizei)(numFrames * sfinfo.channels) * (ALsizei)sizeof(short);

		// Buffer the audio data into a new buffer object, then free the data and close the file
		buffer = 0;
		alGenBuffers(1, &buffer);
		alBufferData(buffer, format, membuf, numBytes, sfinfo.samplerate);

		free(membuf);
		sf_close(sndfile);

		// Check if an error occured, and clean up if so
		err = alGetError();
		if (err != AL_NO_ERROR)
		{
			printf("OpenAL Error: %s\n", alGetString(err));
			if (buffer && alIsBuffer(buffer))
				alDeleteBuffers(1, &buffer);
			return 0;
		}

		m_SoundEffects[fileName] = buffer;

		return buffer;
	}

	SoundBuffer::SoundBuffer()
	{
		m_SoundEffects.clear();
	}

	SoundBuffer::~SoundBuffer()
	{
		std::for_each(m_SoundEffects.begin(), m_SoundEffects.end(),
			[](const std::pair<std::string, uint32_t>& p) {
				printf("{ %s,\t%d }\n", p.first.c_str(), p.second);
				alDeleteBuffers(1, &p.second);
			});

		m_SoundEffects.clear();
	}

}