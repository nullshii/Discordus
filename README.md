Discordus
=========
Simle cross-platform gui app to set custom discord status.

### Todo:
- [DiscordRPCpp - Handle response properly](DiscordRPCpp/src/DiscordRPC.cpp)

![Preview](Assets/Preview.png)

# How to build
Requirements:
- CMake
- make
- gcc (or clang)
- g++ (or clang++)

1. Clone repository
```sh
git clone --recursive https://github.com/PureFoxCore/Discordus
cd Discordus
```
2. Create build directory
```sh
mkdir build
cd build
```
3. Configure CMake
```sh
cmake .. -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"
```
4. Compile
```sh
make -j`nproc`
```
5. Run
```sh
cd Discordus
./Discordus
```

Special thanks to:
- [glfw](https://github.com/glfw/glfw)
- [glad](https://github.com/Dav1dde)
- [imgui](https://github.com/ocornut/imgui)
- [imgui-filebrowser](https://github.com/AirGuanZ/imgui-filebrowser)
- [simpleini](https://github.com/brofield/simpleini/)
- [opensans](https://www.opensans.com/)
- [**discord-rpc**](https://github.com/discord/discord-rpc)