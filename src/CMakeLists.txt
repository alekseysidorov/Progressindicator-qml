project(client)


set(QML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/qml/indicator")

file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE FORMS "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
qt4_wrap_ui(UIS_H ${FORMS})

if(APPLE)
    # set how it shows up in the Info.plist file
    SET(MACOSX_BUNDLE_INFO_STRING "Demo")
    SET(MACOSX_BUNDLE_LONG_VERSION_STRING "1")
    SET(MACOSX_BUNDLE_BUNDLE_NAME "Indicator demo app")
    SET(MACOSX_BUNDLE_BUNDLE_VERSION "1")
endif()

# This project will generate library
add_executable(client WIN32 MACOSX_BUNDLE ${SRC} ${HDR} ${UIS_H} ${QML_DIR})

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    .
    ..
    ../3rdparty
    ${CMAKE_CURRENT_SOURCE_DIR}
)

update_compiler_flags(client)
target_link_libraries(client ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY})

install(TARGETS client
    RUNTIME DESTINATION ${BINDIR}
    LIBRARY DESTINATION ${LIBDIR}
    ARCHIVE DESTINATION ${LIBDIR}
    BUNDLE DESTINATION .
)
install(DIRECTORY ${QML_DIR} DESTINATION ${SHAREDIR}/qml)

if(CREATE_BUNDLE)
	set(APPS ${BUNDLE_PATH})
	list(APPEND DIRS
		${QT_LIBRARY_DIR}
		${CMAKE_INSTALL_PREFIX}/${LIBDIR}
	)
	if(WIN32)
		get_filename_component(_dir ${QT_QMAKE_EXECUTABLE} PATH)
		list(APPEND DIRS ${_dir})
	endif()

	list(APPEND QML_MODULES
		Qt
		QtDesktop
	)

	list(APPEND QT_PLUGINS
		bearer/qgenericbearer
		bearer/qnativewifibearer
		codecs/qcncodecs
		codecs/qjpcodecs
		codecs/qjpcodecs
		codecs/qkrcodecs
		codecs/qtwcodecs
		imageformats/qsvg
		imageformats/qgif
		imageformats/qjpeg
		imageformats/qico
		imageformats/qmng
		imageformats/qtga
		imageformats/qtiff
		iconengines/qsvgicon
	)

	deploy_qml_modules(${QML_MODULES})
	deploy_qt_plugins(${QT_PLUGINS})

	INSTALL(CODE "
		file(GLOB_RECURSE QTPLUGINS
			\"\${CMAKE_INSTALL_PREFIX}/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
		include(BundleUtilities)
		fixup_bundle(\"${APPS}\" \"\${QTPLUGINS}\" \"${DIRS}\")
		" COMPONENT Runtime)
endif()
