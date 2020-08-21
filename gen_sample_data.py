import random

size_img = 56*56
f = open("sample_data_56","w+")
num_data = 8

for i in range(num_data):
	for j in range(size_img):
		x = random.randrange(256)
		string = str(x)+"\t"
		f.write(string)
	f.write("\n")