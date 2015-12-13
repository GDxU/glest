cmake -E make_directory build
cd build
cmake .. -G"Visual Studio 12" -DCMAKE_PREFIX_PATH="C:/Program Files (x86)/OpenAL 1.1 SDK"
cd ..