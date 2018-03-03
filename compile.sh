clear
g++ main.cpp constants.h headers/*.h implementation/*.cpp -I . -lsfml-graphics -lsfml-window -lsfml-system -o build/app && ./build/app
