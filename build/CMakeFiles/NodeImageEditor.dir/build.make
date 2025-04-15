# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mukulgupta/Documents/GitHub/node-based-image-processor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mukulgupta/Documents/GitHub/node-based-image-processor/build

# Include any dependencies generated for this target.
include CMakeFiles/NodeImageEditor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/NodeImageEditor.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/NodeImageEditor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NodeImageEditor.dir/flags.make

CMakeFiles/NodeImageEditor.dir/codegen:
.PHONY : CMakeFiles/NodeImageEditor.dir/codegen

CMakeFiles/NodeImageEditor.dir/src/main.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/main.cpp.o: /Users/mukulgupta/Documents/GitHub/node-based-image-processor/src/main.cpp
CMakeFiles/NodeImageEditor.dir/src/main.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mukulgupta/Documents/GitHub/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/main.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/main.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/main.cpp.o -c /Users/mukulgupta/Documents/GitHub/node-based-image-processor/src/main.cpp

CMakeFiles/NodeImageEditor.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mukulgupta/Documents/GitHub/node-based-image-processor/src/main.cpp > CMakeFiles/NodeImageEditor.dir/src/main.cpp.i

CMakeFiles/NodeImageEditor.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mukulgupta/Documents/GitHub/node-based-image-processor/src/main.cpp -o CMakeFiles/NodeImageEditor.dir/src/main.cpp.s

# Object files for target NodeImageEditor
NodeImageEditor_OBJECTS = \
"CMakeFiles/NodeImageEditor.dir/src/main.cpp.o"

# External object files for target NodeImageEditor
NodeImageEditor_EXTERNAL_OBJECTS =

NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/main.cpp.o
NodeImageEditor: CMakeFiles/NodeImageEditor.dir/build.make
NodeImageEditor: libglad.a
NodeImageEditor: libimgui.a
NodeImageEditor: external/imnodes/libimnodes.a
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_gapi.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_stitching.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_alphamat.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_aruco.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_bgsegm.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_bioinspired.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_ccalib.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_dnn_objdetect.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_dnn_superres.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_dpm.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_face.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_freetype.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_fuzzy.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_hfs.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_img_hash.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_intensity_transform.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_line_descriptor.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_mcc.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_quality.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_rapid.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_reg.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_rgbd.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_saliency.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_sfm.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_signal.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_stereo.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_structured_light.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_superres.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_surface_matching.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_tracking.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_videostab.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_viz.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_wechat_qrcode.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_xfeatures2d.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_xobjdetect.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_xphoto.4.11.0.dylib
NodeImageEditor: libimgui.a
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_shape.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_highgui.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_datasets.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_plot.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_text.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_ml.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_phase_unwrapping.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_optflow.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_ximgproc.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_video.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_videoio.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_imgcodecs.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_objdetect.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_calib3d.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_dnn.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_features2d.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_flann.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_photo.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_imgproc.4.11.0.dylib
NodeImageEditor: /opt/homebrew/Cellar/opencv/4.11.0_1/lib/libopencv_core.4.11.0.dylib
NodeImageEditor: CMakeFiles/NodeImageEditor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/mukulgupta/Documents/GitHub/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable NodeImageEditor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NodeImageEditor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NodeImageEditor.dir/build: NodeImageEditor
.PHONY : CMakeFiles/NodeImageEditor.dir/build

CMakeFiles/NodeImageEditor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NodeImageEditor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NodeImageEditor.dir/clean

CMakeFiles/NodeImageEditor.dir/depend:
	cd /Users/mukulgupta/Documents/GitHub/node-based-image-processor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mukulgupta/Documents/GitHub/node-based-image-processor /Users/mukulgupta/Documents/GitHub/node-based-image-processor /Users/mukulgupta/Documents/GitHub/node-based-image-processor/build /Users/mukulgupta/Documents/GitHub/node-based-image-processor/build /Users/mukulgupta/Documents/GitHub/node-based-image-processor/build/CMakeFiles/NodeImageEditor.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/NodeImageEditor.dir/depend

