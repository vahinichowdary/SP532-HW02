To Compile:
        make (gcc -o hw2_vy hw2_vyerneni.c)

To Execute:
1) Printing file hierarchy starting with current directory:
        ./hw2_vy 

2) Printing file hierarchy starting with given directory name:
 	./hw2_vy ./(Directory Name)

3) Printing file hierarchy using path:
        ./hw2_vy (Path)

4) Printing all files in the hierarchy along with size, permissions, and last access time: 
        ./hw2_vy -S

5) Printing all files in the hierarchy starting with given directory name along with size, permissions, and last access time:
	./hw2_vy -S ./(Directory Name)

6) Printing all files in the hierarchy which are lessthan the given file size
        ./hw2_vy -s (size in bytes)
 
7) Printing only the files that contains the given string name along with the depth
        ./hw2_vy -f (string name) (depth)

8) Printing all the regular files in the hierarchy
        ./hw2_vy -t f

9) Printing all the directories in the hierarchy
	./hw2_vy -t d
	
10) Printing all the files based on the Combinations:
	./hw2_vy -S -s (size in bytes)
	./hw2_vy -s (size in bytes) -S
	./hw2_vy -s (size in bytes) -f (string name) (depth)
	./hw2_vy -f (string name) (depth) -s 1024 
	./hw2_vy -S -f (string name) (depth)
	./hw2_vy -f (string name) (depth) -S
	./hw2_vy -S -s (size in bytes) -f (string name) (depth)
	./hw2_vy -S -f j(string name) (depth) -s (size in bytes)
	./hw2_vy -f (string name) (depth) -s (size in bytes) -S
	./hw2_vy -f (string name) (depth) -S -s (size in bytes)
	./hw2 -s (size in bytes) -S -f (string name) (depth) 
	./hw2 -s (size in bytes) -S -f (string name) (depth)  	 
   
