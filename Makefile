CC = g++

all: bin/tp

bin/tp: obj/fila_aventureiros.o obj/fila_itens.o obj/fila_atributos.o obj/fila_encomendas.o obj/aventureiro.o obj/build_aventureiro.o obj/item.o obj/atributo.o obj/encomenda.o obj/main.o
	@mkdir -p bin
	$(CC) obj/fila_aventureiros.o obj/fila_itens.o obj/fila_atributos.o obj/aventureiro.o obj/fila_encomendas.o obj/build_aventureiro.o obj/item.o obj/atributo.o obj/encomenda.o obj/main.o -o bin/tp

obj/fila_aventureiros.o: src/fila_aventureiros.cpp include/fila_aventureiros.h include/aventureiro.h
	@mkdir -p obj
	$(CC) -Iinclude -c src/fila_aventureiros.cpp -o obj/fila_aventureiros.o

obj/fila_itens.o: src/fila_itens.cpp include/fila_itens.h include/item.h
	@mkdir -p obj
	$(CC) -Iinclude -c src/fila_itens.cpp -o obj/fila_itens.o

obj/fila_atributos.o:
	@mkdir -p obj
	$(CC) -Iinclude -c src/fila_atributos.cpp -o obj/fila_atributos.o

obj/fila_encomendas.o:
	@mkdir -p obj
	$(CC) -Iinclude -c src/fila_encomendas.cpp -o obj/fila_encomendas.o

obj/aventureiro.o: src/aventureiro.cpp include/aventureiro.h
	@mkdir -p obj
	$(CC) -Iinclude -c src/aventureiro.cpp -o obj/aventureiro.o

obj/build_aventureiro.o: src/build_aventureiro.cpp include/build_aventureiro.h include/aventureiro.h
	@mkdir -p obj
	$(CC) -Iinclude -c src/build_aventureiro.cpp -o obj/build_aventureiro.o

obj/item.o: src/item.cpp include/item.h
	@mkdir -p obj
	$(CC) -Iinclude -c src/item.cpp -o obj/item.o

obj/atributo.o:
	@mkdir -p obj
	$(CC) -Iinclude -c src/atributo.cpp -o obj/atributo.o

obj/encomenda.o:
	@mkdir -p obj
	$(CC) -Iinclude -c src/encomenda.cpp -o obj/encomenda.o

obj/main.o: src/main.cpp include/fila_aventureiros.h include/fila_itens.h include/build_aventureiro.h include/aventureiro.h
	@mkdir -p obj
	$(CC) -Iinclude -c src/main.cpp -o obj/main.o

clean:
	rm -f obj/*.o bin/tp

.PHONY: all clean