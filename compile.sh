clear
g++ \
	-I .  \
	main.cpp \
       	headers/*.h \
	implementation/*.cpp \
	utils/* \
	-lsfml-graphics -lsfml-window -lsfml-system \
	-o build/app \
	&& \
       ./build/app
