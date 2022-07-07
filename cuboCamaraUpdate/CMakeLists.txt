project( cuboCamaraUpdate )

message( "Configuring main application - ${PROJECT_NAME} : " )

# OpenGL
find_package(OpenGL REQUIRED)

file(GLOB SOURCES "*.cpp" ${DEPENDENCY_DIR}/include/glad/glad/glad.c )
file(GLOB HEADERS "*.h" )
file(GLOB SHADERS "*.vert" "*.frag" "*.vs" "*.fs" )

include_directories( 
${DEPENDENCY_DIR}/include/glad/ 
${DEPENDENCY_DIR}/include/glfw/
${DEPENDENCY_DIR}/include/freeimage/
${DEPENDENCY_DIR}/include/glew
${DEPENDENCY_DIR}/include/glm
${DEPENDENCY_DIR}/include/freeglut

)

message( "\nBuild mode test is: ${CMAKE_BUILD_TYPE}" )

if ( CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("\nOpenGL_GLUT_GLFW_Program -- Debug mode ****************")
	link_directories(
	${DEPENDENCY_DIR}/lib/glad/Debug/
	${DEPENDENCY_DIR}/lib/glfw/Debug/
	${DEPENDENCY_DIR}/lib/freeglut/Debug/
	${DEPENDENCY_DIR}/lib/freeimage/Debug/
	${DEPENDENCY_DIR}/lib/glew/Debug/
	${DEPENDENCY_DIR}/lib/glm/Debug/
	)
else()
    message("\nOpenGL_GLUT_GLFW_Program -- Release mode ****************")
	link_directories(
	${DEPENDENCY_DIR}/lib/glad/Release/
	${DEPENDENCY_DIR}/lib/glfw/Release/
	${DEPENDENCY_DIR}/lib/freeglut/Release/
	${DEPENDENCY_DIR}/lib/freeimage/Release/
	${DEPENDENCY_DIR}/lib/glew/Release/
	${DEPENDENCY_DIR}/lib/glm/Release/
	)
endif ()
 
add_executable( ${PROJECT_NAME}  ${HEADERS} ${SOURCES} ${SHADERS} shader/shader.h cubo.h cubito.h transform.h plainCube.h rubiks.h solver.h stb_image.h animation.h camaraAnimations.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shader/vertexShader.txt ${CMAKE_CURRENT_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shader/fragmentShader.txt ${CMAKE_CURRENT_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shader/7.1.camera.vs ${CMAKE_CURRENT_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shader/7.1.camera.fs ${CMAKE_CURRENT_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shader/container.jpg ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/b11.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/b12.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/b13.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/b21.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/b22.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/b23.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/b31.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/b32.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/b33.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/f11.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/f12.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/f13.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/f21.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/f22.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/f23.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/f31.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/f32.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/f33.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/l11.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/l12.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/l13.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/l21.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/l22.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/l23.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/l31.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/l32.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/l33.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/r11.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/r12.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/r13.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/r21.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/r22.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/r23.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/r31.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/r32.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/r33.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/d11.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/d12.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/d13.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/d21.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/d22.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/d23.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/d31.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/d32.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/d33.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/u11.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/u12.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/u13.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/u21.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/u22.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/u23.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/u31.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/u32.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/u33.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

if ( CMAKE_BUILD_TYPE STREQUAL "Debug")
	if ( WIN32 )
	    message("\nOpenGL_GLUT_GLFW_Program -- Debug mode Windows ****************")
		target_link_libraries( ${PROJECT_NAME} 
						   opengl32
						   freeglut_staticd.lib
						   glad.lib
	                       glfw3.lib
						   glew32d.lib
						   FreeImaged.lib
						   glm_static.lib
						   
						    )
	else()
		message("\nOpenGL_GLUT_GLFW_Program -- Debug mode Linux ****************")
		target_link_libraries( ${PROJECT_NAME} 
						   ${OPENGL_LIBRARY}
							-lm
							-lGL
							-lGLU
							-lX11
							-lXi
							-lXxf86vm 
							-lXrandr 
							-pthread 
							-ldl
							-lm
						   libglad.a
	                       libglfw3.a
						   libGLEWd.a
						   libglut.a
						   libfreeimage.a
						   libglm_static.a
						    )

	endif()					    	
else()
	if ( WIN32 )
		message("\nOpenGL_GLUT_GLFW_Program -- Release mode Windows ****************")
		target_link_libraries( ${PROJECT_NAME} 
						   opengl32
						   freeglut_static.lib
						   glad.lib
	                       glfw3.lib
						   glew32.lib
						   FreeImage.lib
						   glm_static.lib
						    )
	else()
		message("\nOpenGL_GLUT_GLFW_Program -- Release mode Linux ****************")
		target_link_libraries( ${PROJECT_NAME} 
						  ${OPENGL_LIBRARY}
												    
							-lm
							-lGL
							-lGLU
							-lX11
							-lXi
							-lXxf86vm 
							-lXrandr 
							-pthread 
							-ldl
							-lm
						   libglad.a
	                       libglfw3.a
						   libGLEW.a
						   libglut.a
						   libfreeimage.a
						   libglm_static.a
							)

	endif()	
endif ()                      