hepsi: derle calistir

derle:
	g++ -I ./include/ -o ./lib/HucreDugum.o -c ./src/HucreDugum.cpp
	g++ -I ./include/ -o ./lib/Matris.o -c ./src/Matris.cpp
	g++ -I ./include/ -o ./lib/MatrisDugum.o -c ./src/MatrisDugum.cpp
	g++ -I ./include/ -o ./lib/MatrisListesi.o -c ./src/MatrisListesi.cpp
	g++ -I ./include/ -o ./lib/Ekran.o -c ./src/Ekran.cpp
	g++ -I ./include/ -o ./bin/program.exe ./lib/HucreDugum.o ./lib/Matris.o ./lib/MatrisDugum.o ./lib/MatrisListesi.o ./lib/Ekran.o ./src/main.cpp

calistir:
	.\bin\program.exe
