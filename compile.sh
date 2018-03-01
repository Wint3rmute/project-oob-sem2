clear
g++ main.cpp headers/*.h implementation/*.cpp -I . -lsfml-graphics -lsfml-window -lsfml-system -o build/app && ./build/app
