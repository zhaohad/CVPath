# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/zhaohad/clion-2020.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/zhaohad/clion-2020.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhaohad/dev/demos/CppProjects/CVPath/005_MaskOperationsOnMatrices

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhaohad/dev/demos/CppProjects/CVPath/005_MaskOperationsOnMatrices/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/005_MaskOperationsOnMatrices.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/005_MaskOperationsOnMatrices.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/005_MaskOperationsOnMatrices.dir/flags.make

CMakeFiles/005_MaskOperationsOnMatrices.dir/main.cpp.o: CMakeFiles/005_MaskOperationsOnMatrices.dir/flags.make
CMakeFiles/005_MaskOperationsOnMatrices.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhaohad/dev/demos/CppProjects/CVPath/005_MaskOperationsOnMatrices/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/005_MaskOperationsOnMatrices.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/005_MaskOperationsOnMatrices.dir/main.cpp.o -c /home/zhaohad/dev/demos/CppProjects/CVPath/005_MaskOperationsOnMatrices/main.cpp

CMakeFiles/005_MaskOperationsOnMatrices.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/005_MaskOperationsOnMatrices.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhaohad/dev/demos/CppProjects/CVPath/005_MaskOperationsOnMatrices/main.cpp > CMakeFiles/005_MaskOperationsOnMatrices.dir/main.cpp.i

CMakeFiles/005_MaskOperationsOnMatrices.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/005_MaskOperationsOnMatrices.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhaohad/dev/demos/CppProjects/CVPath/005_MaskOperationsOnMatrices/main.cpp -o CMakeFiles/005_MaskOperationsOnMatrices.dir/main.cpp.s

# Object files for target 005_MaskOperationsOnMatrices
005_MaskOperationsOnMatrices_OBJECTS = \
"CMakeFiles/005_MaskOperationsOnMatrices.dir/main.cpp.o"

# External object files for target 005_MaskOperationsOnMatrices
005_MaskOperationsOnMatrices_EXTERNAL_OBJECTS =

005_MaskOperationsOnMatrices: CMakeFiles/005_MaskOperationsOnMatrices.dir/main.cpp.o
005_MaskOperationsOnMatrices: CMakeFiles/005_MaskOperationsOnMatrices.dir/build.make
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_gapi.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_stitching.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_aruco.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_barcode.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_bgsegm.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_bioinspired.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_ccalib.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_dnn_objdetect.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_dnn_superres.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_dpm.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_face.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_freetype.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_fuzzy.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_hfs.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_img_hash.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_intensity_transform.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_line_descriptor.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_mcc.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_quality.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_rapid.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_reg.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_rgbd.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_saliency.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_stereo.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_structured_light.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_superres.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_surface_matching.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_tracking.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_videostab.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_wechat_qrcode.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_xfeatures2d.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_xobjdetect.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_xphoto.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_shape.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_highgui.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_datasets.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_plot.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_text.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_ml.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_phase_unwrapping.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_optflow.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_ximgproc.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_video.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_videoio.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_dnn.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_imgcodecs.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_objdetect.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_calib3d.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_features2d.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_flann.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_photo.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_imgproc.so.4.5.2
005_MaskOperationsOnMatrices: /home/zhaohad/OpenCV/build/lib/libopencv_core.so.4.5.2
005_MaskOperationsOnMatrices: CMakeFiles/005_MaskOperationsOnMatrices.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhaohad/dev/demos/CppProjects/CVPath/005_MaskOperationsOnMatrices/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 005_MaskOperationsOnMatrices"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/005_MaskOperationsOnMatrices.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/005_MaskOperationsOnMatrices.dir/build: 005_MaskOperationsOnMatrices

.PHONY : CMakeFiles/005_MaskOperationsOnMatrices.dir/build

CMakeFiles/005_MaskOperationsOnMatrices.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/005_MaskOperationsOnMatrices.dir/cmake_clean.cmake
.PHONY : CMakeFiles/005_MaskOperationsOnMatrices.dir/clean

CMakeFiles/005_MaskOperationsOnMatrices.dir/depend:
	cd /home/zhaohad/dev/demos/CppProjects/CVPath/005_MaskOperationsOnMatrices/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhaohad/dev/demos/CppProjects/CVPath/005_MaskOperationsOnMatrices /home/zhaohad/dev/demos/CppProjects/CVPath/005_MaskOperationsOnMatrices /home/zhaohad/dev/demos/CppProjects/CVPath/005_MaskOperationsOnMatrices/cmake-build-debug /home/zhaohad/dev/demos/CppProjects/CVPath/005_MaskOperationsOnMatrices/cmake-build-debug /home/zhaohad/dev/demos/CppProjects/CVPath/005_MaskOperationsOnMatrices/cmake-build-debug/CMakeFiles/005_MaskOperationsOnMatrices.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/005_MaskOperationsOnMatrices.dir/depend

