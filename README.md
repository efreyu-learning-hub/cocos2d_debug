# cocos2dx-debug

## TODO add description

### How to add that dependency into your game project

- git submodule add git@github.com:efreyu-learning-hub/cocos2d_debug.git Classes/cocos2d_debug
- in your CMakeLists.txt after :
```cmake
set(GAME_SOURCE)
set(GAME_HEADER)
```
add
```cmake
add_subdirectory(Classes/cocos2d_debug) # add debug draw module
```
- in your CMakeLists.txt replace :
```cmake
target_link_libraries(${APP_NAME} cocos2d)
```
with
```cmake
initDebugModule()
target_link_libraries(${APP_NAME} cocos2d ${GENERIC_LIB})
```
- in your AppDelegate::applicationDidFinishLaunching() before main scene creation add:
```cpp
#ifdef IMGUI_ENABLED
    debugModule::ImGuiDebugLayer::initializeLayer();
#endif
```