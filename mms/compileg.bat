g++ -c trace.cpp ../Bitmap/*.cpp  -std=c++23 -g
g++ *.o -o driver.exe -g

move *.o obj
move *.exe bin