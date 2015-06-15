rm output.txt
touch output.txt
for i in {1,2,4,8,16,32,64,128,256,512,1024}
do
	g++ new-boggle.cpp
	echo $i>>output.txt
	./a.out $i < words.txt >> output.txt;
	echo . >> output.txt 
done
