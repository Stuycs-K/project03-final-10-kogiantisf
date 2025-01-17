DEFAULT: clean compile_server start_server
start_server: create_server
	./create_server
start_player: start_game
	./start_game
compile_player start_game: player.o pipe_networking.o
	gcc -o start_game player.o pipe_networking.o
compile_server create_server: server.o pipe_networking.o
	gcc -o create_server server.o pipe_networking.o
player.o: player.c
	gcc -c player.c
server.o: server.c
	gcc -c server.c
pipe_networking.o: pipe_networking.c
	gcc -c pipe_networking.c
clean:
	rm -f guest_storage.dat key_storage.dat create_server start_game WKP *.o
	



