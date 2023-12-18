g++ -c trace.cpp ../Bitmap/*.cpp  -std=c++23
g++ *.o -o driver.exe

move *.o obj
move *.exe bin