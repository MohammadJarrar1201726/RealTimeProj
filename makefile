

files:
	gcc main.c  -o main 
	gcc team.c  -o team
	gcc player.c   -o player



run:
	./main 


clean:
	rm -f main 
	rm -f player
	rm -f team


