#ifndef CUBE_OPTIONS_H
#define CUBE_OPTIONS_H

namespace cube {
    class Options {
	public:
		int fullscreen;
		int resolutionX;
		int resolutionY;
		int refreshRate;
		int antiAliasing;
		int renderDistance;
		int cpuPerformance;
		int soundVolume;
		int musicVolume;
		int cameraSpeed;
		int cameraSmoothness;
		int invertY;
		int language;
		int minTimeStep;
		int smallGUI;
		int vsync;
		int showRarity;
		float guiScale;
		float mapScale;
		int musicLoop;
		int antiAliasingSamples;
    };
}

#endif // CUBE_OPTIONS_H
