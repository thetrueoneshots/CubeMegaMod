# CWSDK

Defines structures, functions, and callbacks for interacting with Cube World in C++.

Mods produced with CWSDK are for use with the [Cube World Mod Launcher](https://github.com/ChrisMiuchiz/Cube-World-Mod-Launcher).

 ## Getting started
 
Although modding Cube World, even with CWSDK, is not for the faint of heart, CWSDK provides common-use functionality to assist development and cooperation of mods. All projects which use CWSDK should be compiled using Visual Studio and Clang.

 1) Set up and install [Visual Studio 2019](https://visualstudio.microsoft.com/vs/).

 2) Configure it for Clang: https://devblogs.microsoft.com/cppblog/clang-llvm-support-in-visual-studio/

 3) Create a folder for your source code, and add:
 
	a) A [released snapshot](https://github.com/ChrisMiuchiz/CWSDK/releases) of CWSDK.
	
	b) A `main.cpp` for your code.
	
	c) A `CMakeLists.txt`. See [CommandsMod](https://github.com/ChrisMiuchiz/Cube-World-Commands-Mod/) for an example and a script which can auto-generate this for you in simpler projects.
	
 4) Open your project in Visual Studio using the `Open Folder` option. Configure Visual Studio to build with `x64-Clang-Release` according to [the page in step 2](https://devblogs.microsoft.com/cppblog/clang-llvm-support-in-visual-studio/).
 
 5) Include `cwsdk.h` from CWSDK to use its features.
 
 Note that you'll probably want to change the output from `Build + IntelliSense` to `Build only`.
 
 ## Basic mod structure
 
 You must create a class for your mod which inherits from `GenericMod` from cwsdk.h. To instantiate the class and provide it to the [Cube World Mod Launcher](https://github.com/ChrisMiuchiz/Cube-World-Mod-Launcher), you must export a function `MakeMod` which returns a pointer to a new instance of your mod. To utilize event handlers, override the appropriate virtual function.
 
 ```
 #include "CWSDK/cwsdk.h"

 class Mod : GenericMod {
	virtual int OnChat(std::wstring* message) override {
		// This will be called when the player sends a chat message
	}
	virtual void OnGameTick(cube::Game* game) override {
		// This will be called every frame
	}
	virtual void Initialize() override {
		// This will be called after your mod is loaded. CWSDK internals are initialized at this point, so it's safe to use CWBase() and CWOffset().
	}
 };
 
 EXPORT Mod* MakeMod() {
	return new Mod();
}
 ```
 
 ## Event Handlers
 
 To use an event handler, override them as per the example above.
 
 ---
 
 `virtual void Initialize()`
 
 Called after mod is loaded.
 
 Return values: None.
 
 
 ---
 
 `virtual int OnChat(std::wstring* message)`
 
 Called when the player sends a message.
 
 Return values: 
 
 0 - Normal behavior
 
 1 - Cancel message
 
 ---
 
  `virtual int OnCheckInventoryFull(cube::Creature* player, cube::Item* item)`
 
 Called when the game checks to see if a creature can carry more of an item.
 
 Return values: 
 
 0 - Normal behavior
 
 1 - Override, CAN carry more.
 
 2 - Override, CANNOT carry more.
 
 ---
 
  `virtual int OnP2PRequest(uint64_t steamID)`
 
 Called when a new Steam peer to peer request is made.
 
 Return values: 
 
 0 - Normal behavior
 
 1 - Force block request
 
 2 - Force accept request
 
 ---
 
 `virtual void OnGameTick(cube::Game* game)`
 
 Called (prior to) every frame.
 
 Return values: None.
 
 ---
 
 `virtual void OnZoneGenerated(cube::Zone* zone)`
 
 Called after a zone is generated. Note that zones belong to worlds, and there are two `cube::World` objects. One world belongs to `cube::Game`, and one world belongs to `cube::Game::Host`.
 
 Return values: None.
 
 ---
 
 `virtual void OnZoneDestroy(cube::Zone* zone)`
 
 Called before a zone is destroyed.
 
 Return values: None.
 
 ---
 
 `virtual int OnWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)`
 
 Called before a WindowProc callback is performed. See [Microsoft's documentation](https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms633573(v%3Dvs.85)).
 
 Return values:
 
 0 - Normal behavior
 
 1 - Cancel WindowProc
 
 ---
 
 `virtual void OnGetKeyboardState(BYTE* diKeys)`
 
 Called when GetDeviceState is called for the keyboard. See [Microsoft's documentation](https://docs.microsoft.com/en-us/previous-versions/windows/desktop/ee417897(v%3Dvs.85)). To modify a key state, modify the values in diKeys.
 
 Return values: None.
 
 ---
 
 `virtual void OnGetMouseState(DIMOUSESTATE* diMouse)`
 
 Called when GetDeviceState is called for the mouse. See [Microsoft's documentation](https://docs.microsoft.com/en-us/previous-versions/windows/desktop/ee417897(v%3Dvs.85)). To modify a mouse state, modify the values belonging to diMouse.
 
 Return values: None.
 
 ---
 
 ```virtual void OnPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags)```
 
 Called before Present is called on the game's IDXGISwapChain. See [Microsoft's documentation](https://docs.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiswapchain-present).
 
 Return values: None.
 
 ---
 
 ```virtual void OnCreatureArmorCalculated(cube::Creature* creature, float* armor)```
 
 Called after a creature's armor stat is calculated. To modify the result, modify the value pointed to by `armor`.
 
 Return values: None.
 
 ---
 
 ```virtual void OnCreatureCriticalCalculated(cube::Creature* creature, float* critical)```
 
 Called after a creature's critical stat is calculated. To modify the result, modify the value pointed to by `critical`.
 
 Return values: None.
 
 ---
 
 ```virtual void OnCreatureAttackPowerCalculated(cube::Creature* creature, float* power)```
 
 Called after a creature's attack power stat is calculated. To modify the result, modify the value pointed to by `power`.
 
 Return values: None.
 
 ---
 
 ```virtual void OnCreatureSpellPowerCalculated(cube::Creature* creature, float* power)```
 
 Called after a creature's spell power stat is calculated. To modify the result, modify the value pointed to by `power`.
 
 Return values: None.
 
 ---
 
 ```virtual void OnCreatureHasteCalculated(cube::Creature* creature, float* haste)```
 
 Called after a creature's haste stat is calculated. To modify the result, modify the value pointed to by `haste`.
 
 Return values: None.
 
 ---
 
 ```virtual void OnCreatureResistanceCalculated(cube::Creature* creature, float* resistance)```
 
 Called after a creature's haste stat is calculated. To modify the result, modify the value pointed to by `resistance`.
 
 Return values: None.
 
 ---
 
 ```virtual void OnCreatureRegenerationCalculated(cube::Creature* creature, float* regeneration)```
 
 Called after a creature's stamina regeneration stat is calculated. To modify the result, modify the value pointed to by `regeneration`.
 
 Return values: None.
 
 ---
 
 ```virtual void OnCreatureManaGenerationCalculated(cube::Creature* creature, float* manaGeneration)```
 
 Called after a creature's mana regeneration stat is calculated. To modify the result, modify the value pointed to by `manaGeneration`.
 
 Return values: None.
 
 ---
  
 ```virtual void OnChunkRemesh(cube::Zone* zone)```
 
 Called when a gfx::Chunk starts to be remeshed.
 
 Return values: None.
 
 ---
   
 ```virtual void OnChunkRemeshed(cube::Zone* zone)```
 
 Called when a gfx::Chunk is finished remeshing.
 
 Return values: None.
 
 ---
 
 ## Event Priorities
 
 Any event handler can have its priority set or changed at any time. An event handler with a higher priority gets called before those with a lower priority. The priority associated with any given event is named `{Event Handler}Priority`. For example, the priority for `OnChat` is `OnChatPriority`. The priority variables are of type `enum GenericMod::Priority` and there are 5 possible priorities:
 ```
 VeryHighPriority,
 HighPriority,
 NormalPriority,
 LowPriority,
 VeryLowPriority
```

 By default, all priorities are `NormalPriority`. 

 Setting a priority is simple. Here is an example of setting the priority of a mod's OnChat handler to be very low as soon as the mod is initialized:
 
 ```
 #include "CWSDK/cwsdk.h"
 class Mod : GenericMod {
	virtual void Initialize() override {
		OnChatPriority = VeryLowPriority;
	}
	virtual int OnChat(std::wstring* message) override {
		//I will be called after mods with low, normal, high, or very high priority.
		return 0;
	}
};
EXPORT Mod* MakeMod() {
	return new Mod();
}
```
 
 ## Data members and methods
 
 No documentation on these, and they are especially prone to change. Explore the source.
 
Special thanks
==============

```
Andoryuuta - Reverse engineering work and mapping structs. Much is based on his CWTCore.
matpow2 - Structs for the alpha that are still useful in the beta
ZaneYork - Fields and contributions to the mod loader and commandsmod
```