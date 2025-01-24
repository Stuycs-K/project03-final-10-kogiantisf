DEFAULT: clean start_player clean
start_server: create_server
	./create_server
start_player: start_game
	./start_game
compile_player start_game: player.o client_server.o libraries.o pipe_networking.o
	gcc -o start_game player.o client_server.o libraries.o pipe_networking.o
compile_server create_server: server.o client_server.o semaphore.o logins.o libraries.o pipe_networking.o
	gcc -o create_server server.o client_server.o semaphore.o logins.o libraries.o pipe_networking.o
player.o: player.c
	gcc -c player.c
server.o: server.c
	gcc -c server.c
client_server.o: client_server.c
	gcc -c client_server.c
semaphore.o: semaphore.c
	gcc -c semaphore.c
logins.o: logins.c
	gcc -c logins.c
libraries.o: libraries.c
	gcc -c libraries.c
pipe_networking.o: pipe_networking.c
	gcc -c pipe_networking.c
clean:
	rm -f guest_storage.dat key_storage.dat create_server start_game public_pipe *.o
	



