cmake_minimum_required(VERSION 2.6)
project(AutopatcherServer)

IF(WIN32 AND NOT UNIX)
	SET(Autopatcher_SOURCE_DIR ${CMAKE_SOURCE_DIR}/DependentExtensions/Autopatcher)
	SET(AutopatcherPostgreRepository_SOURCE_DIR ${CMAKE_SOURCE_DIR}/DependentExtensions/Autopatcher/AutopatcherPostgreRepository)
	SET(BZip2_SOURCE_DIR ${CMAKE_SOURCE_DIR}/DependentExtensions/bzip2-1.0.6)
	SET(PostgreSQLInterface_SOURCE_DIR ${CMAKE_SOURCE_DIR}/DependentExtensions/PostgreSQLInterface)
	FILE(GLOB AUTOSRC "${Autopatcher_SOURCE_DIR}/AutopatcherServer.cpp" "${Autopatcher_SOURCE_DIR}/MemoryCompressor.cpp" "${Autopatcher_SOURCE_DIR}/CreatePatch.cpp" "${Autopatcher_SOURCE_DIR}/AutopatcherServer.h")
	FILE(GLOB BZSRC "${BZip2_SOURCE_DIR}/*.c" "${BZip2_SOURCE_DIR}/*.h")
	LIST(REMOVE_ITEM BZSRC "${BZip2_SOURCE_DIR}/dlltest.c" "${BZip2_SOURCE_DIR}/mk251.c" "${BZip2_SOURCE_DIR}/bzip2recover.c" 
	"${BZip2_SOURCE_DIR}/bzip2.c" "${BZip2_SOURCE_DIR}/unzcrash.c" "${BZip2_SOURCE_DIR}/spewG.c")
	SOURCE_GROUP(BZip FILES ${BZSRC})
	SOURCE_GROUP("Source Files" FILES ${AUTOSRC})   
	SOURCE_GROUP(Main "AutopatcherServerTest.cpp")
	include_directories(${RAKNETHEADERFILES} ./ ${AutopatcherPostgreRepository_SOURCE_DIR} ${PostgreSQLInterface_SOURCE_DIR} ${Autopatcher_SOURCE_DIR} ${BZip2_SOURCE_DIR} "C:\Program Files\PostgreSQL\9.4\include" ) 
	add_executable(AutopatcherServer_PostgreSQL "AutopatcherServerTest.cpp" ${CMAKE_SOURCE_DIR}/DependentExtensions/Autopatcher/AutopatcherPostgreRepository/AutopatcherPostgreRepository.cpp ${AUTOSRC} ${BZSRC} readme.txt 
	${CMAKE_SOURCE_DIR}/DependentExtensions/PostgreSQLInterface/PostgreSQLInterface.cpp)
	target_link_libraries(AutopatcherServer_PostgreSQL ${RAKNET_COMMON_LIBS} "C:\Program Files\PostgreSQL\9.4\lib\libpq.lib")
	VSUBFOLDER(AutopatcherServer_PostgreSQL "Samples/AutoPatcher/Server/PostgreSQL" AutopatcherPostgreRepository )
ELSE(WIN32 AND NOT UNIX)
	include_directories(${RAKNETHEADERFILES} ./ ${AutopatcherPostgreRepository_SOURCE_DIR} ${PostgreSQLInterface_SOURCE_DIR} ${Autopatcher_SOURCE_DIR}) 
	add_executable(AutopatcherServer_PostgreSQL "AutopatcherServerTest.cpp")
	target_link_libraries(AutopatcherServer_PostgreSQL ${RAKNET_COMMON_LIBS} LibAutopatcher AutopatcherPostgreRepository LibPostgreSQLInterface)
ENDIF(WIN32 AND NOT UNIX)







