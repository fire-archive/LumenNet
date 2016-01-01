cmake_minimum_required(VERSION 2.6)
project(AutopatcherClientImgui)

IF(WIN32 AND NOT UNIX)
	#FINDD3D()
	#FINDSCALEGFX()
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CmakeIncludes")
	find_package(SDL2 REQUIRED)
	find_package(GLFW REQUIRED)
	include_directories(${SDL2_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/DependentExtensions/imgui )

	set(IMGUISRC 
	${CMAKE_SOURCE_DIR}/DependentExtensions/imgui/imgui.cpp
	${CMAKE_SOURCE_DIR}/DependentExtensions/imgui/imgui.h
	${CMAKE_SOURCE_DIR}/DependentExtensions/imgui/imgui_demo.cpp
	${CMAKE_SOURCE_DIR}/DependentExtensions/imgui/imgui_draw.cpp
	${CMAKE_SOURCE_DIR}/DependentExtensions/imgui/imgui_internal.h
	${CMAKE_SOURCE_DIR}/DependentExtensions/imgui/imconfig.h # (empty by default, user-editable)
	${CMAKE_SOURCE_DIR}/DependentExtensions/imgui/stb_rect_pack.h
	${CMAKE_SOURCE_DIR}/DependentExtensions/imgui/stb_textedit.h
	${CMAKE_SOURCE_DIR}/DependentExtensions/imgui/stb_truetype.h
	imgui_impl_sdl_gl3.cpp
	imgui_impl_sdl_gl3.h
	main.cpp
	${CMAKE_SOURCE_DIR}/DependentExtensions/glad/src/glad.c
	)

	include_directories(${RAKNETHEADERFILES} ${GLFW_INCLUDE_DIR}  ${CMAKE_SOURCE_DIR}/DependentExtensions/glad/include ${SDL2_INCLUDE_DIR} ./ ${CMAKE_SOURCE_DIR}/DependentExtensions/Autopatcher ${Autopatcher_SOURCE_DIR} ${BZip2_SOURCE_DIR} ${D3D_INCLUDE_DIR} ${SCALEGFX_INCLUDE_DIR} "${RakNet_SOURCE_DIR}/DependentExtensions/GFx3")
	FILE(GLOB GFXSRC GFxPlayerTinyD3D9.cpp "${RakNet_SOURCE_DIR}/DependentExtensions/GFx3/*.cpp" "${RakNet_SOURCE_DIR}/DependentExtensions/GFx3/*.h")
	FILE(GLOB AUTOSRC "${Autopatcher_SOURCE_DIR}/*.cpp" "${Autopatcher_SOURCE_DIR}/*.h")
	FILE(GLOB BZSRC "${BZip2_SOURCE_DIR}/*.c" "${BZip2_SOURCE_DIR}/*.h")
	LIST(REMOVE_ITEM BZSRC "${BZip2_SOURCE_DIR}/dlltest.c" "${BZip2_SOURCE_DIR}/mk251.c" "${BZip2_SOURCE_DIR}/bzip2recover.c")
	SOURCE_GROUP(BZip2 FILES ${BZSRC})
	SET(WRAPFILES "${Autopatcher_SOURCE_DIR}/MemoryCompressor.cpp" "${Autopatcher_SOURCE_DIR}/MemoryCompressor.h")
	LIST(REMOVE_ITEM AUTOSRC ${WRAPFILES})
	set(Client_Files  ${AUTOSRC})
	set(Main AutopatcherClientImguiImpl.cpp AutopatcherClientImguiImpl.h)
	set(BZip2Wrapper ${WRAPFILES})
	set(GFx3 ${GFXSRC})
	add_executable(AutopatcherClientImgui WIN32 ${Main} ${IMGUISRC} ${AUTOSRC} ${BZSRC} "readme.txt")
	target_link_libraries(AutopatcherClientImgui ${GLFW_LIBRARIES} ${RAKNET_COMMON_LIBS} ${SDL2_LIBRARY} ${D3D_LIBRARIES} version.lib winmm.lib imm32.lib ${SCALEGFX_DEBUG_LIBRARIES} ${SCALEGFX_LIBRARIES})
	VSUBFOLDER(AutopatcherClientImgui "Samples/AutoPatcher/Client" ${CMAKE_SOURCE_DIR}/DependentExtensions/imgui/)
ENDIF(WIN32 AND NOT UNIX)






