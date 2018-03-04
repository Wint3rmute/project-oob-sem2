clear
g++ \
	-I .  \
	main.cpp \
       	headers/*.h \
	headers/skills/*.h \
	implementation/*.cpp \
	implementation/skills/*.cpp \
	utils/* \
	-lsfml-graphics -lsfml-window -lsfml-system \
	-o build/app \
	&& \
       ./build/app
