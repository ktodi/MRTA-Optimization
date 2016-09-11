#This is the master code which will
# run all the corresponding algorithm and insert the values 
# in a CSV file for analysis.
# This will generate N CSV files corresponding to the number of Robots/Tasks
# For each N it will generate output for K random input cost matrix
# Here N ranges from [10...100] with an interval of 10
# The k here is 25
import os
import sys
import xlsxwriter
import numpy
import time

# This will first compile all the Code and make executable for them
os.system("gcc Cost_matrix.c -lm -o Cost_matrix")
os.system("gcc robot_normalization.c -o robot_normalization")
os.system("gcc task_normalization.c -o task_normalization")
os.system("gcc Normalized_optimization.c -o Normalized_optimization")
os.system("gcc generate_rank.cpp -o generate_rank")
os.system("gcc stable_marriage.cpp -o stable_marriage")
os.system("gcc hungarian.c -o hungarian")	

# J loops over the N from 10...100 with difference of 10
# You can change these parameters according to the required results		
for j in range(10,110,10):
	
	# This generates CSV file for each J{N}
	workbook=xlsxwriter.Workbook('Algo_'+str(j)+'.xlsx')
	worksheet=workbook.add_worksheet()
	
	# The importance of out.txt here is to store N as  a temp variable to be accesed
	f = open('out.txt', 'w')
	worksheet.write('A1','Hungarian')
	worksheet.write('B1','Task_Algorithm')
	worksheet.write('C1','Robot_Algorithm')
	worksheet.write('D1','Stable_Marriage_Algorithm')
	owd=os.getcwd()
	
	# Here corresponding directories are formed to store input and output and fetch input
	os.system("mkdir Algorithm_"+str(j))
	os.chdir("Algorithm_"+str(j)+"/")
	os.system("mkdir Hungarian_input")
	os.system("mkdir Algorithm_input")
	os.system("mkdir Hungarian_output")
	os.system("mkdir Algorithm_output")
	os.system("mkdir Stable_Marriage_input")
	os.system("mkdir Stable_Marriage_output")
	os.chdir(owd)
	print>>f,"n=",j
	f.close()
	
	# I loops over the K. Here K is 25, so it will genrate 25 random output for particular N
	# You can change these parameters according to the required results
	for i in range(1,26):
		
		# These are system calls to run the executables with corresponding inputs and generate corresponding outputs
		os.system("./Cost_matrix < out.txt > Algorithm_"+str(j)+"/Hungarian_input/input_hungarian_"+str(j)+"_"+str(i)+".txt")
		os.system("./robot_normalization < Algorithm_"+str(j)+"/Hungarian_input/input_hungarian_"+str(j)+"_"+str(i)+".txt >Algorithm_"+str(j)+"/Algorithm_input/input_algorithm_robot_"+str(j)+"_"+str(i)+".txt")
		os.system("./generate_rank < Algorithm_"+str(j)+"/Hungarian_input/input_hungarian_"+str(j)+"_"+str(i)+".txt >Algorithm_"+str(j)+"/Stable_Marriage_input/Rank_Matrix_"+str(j)+"_"+str(i)+".txt")
		os.system("./task_normalization < Algorithm_"+str(j)+"/Hungarian_input/input_hungarian_"+str(j)+"_"+str(i)+".txt >Algorithm_"+str(j)+"/Algorithm_input/input_algorithm_task_"+str(j)+"_"+str(i)+".txt")
		os.system("./robot < Algorithm_"+str(j)+"/Algorithm_input/input_algorithm__robot"+str(j)+"_"+str(i)+".txt >Algorithm_"+str(j)+"/Algorithm_output/output_rob_algo_"+str(j)+"_"+str(i)+".txt")
		os.system("./robot < Algorithm_"+str(j)+"/Algorithm_input/input_algorithm_task_"+str(j)+"_"+str(i)+".txt >Algorithm_"+str(j)+"/Algorithm_output/output_task_algo_"+str(j)+"_"+str(i)+".txt")
		os.system("./stable_marriage < Algorithm_"+str(j)+"/Stable_Marriage_input/Rank_Matrix_"+str(j)+"_"+str(i)+".txt >Algorithm_"+str(j)+"/Stable_Marriage_output/Rank_output_"+str(j)+"_"+str(i)+".txt")
		os.system("./hungarian < Algorithm_"+str(j)+"/Hungarian_input/input_hungarian_"+str(j)+"_"+str(i)+".txt > Algorithm_"+str(j)+"/Hungarian_output/output_hungarian_"+str(j)+"_"+str(i)+".txt")
		
		# Here the ouput cost of all algorithms are inputted in CSV file 
		# for further analysis
		x=0
		input_file=open("Algorithm_"+str(j)+"/Hungarian_output/output_hungarian_"+str(j)+"_"+str(i)+".txt")
		for line in input_file:
				line = line.strip()
				for number in line.split():
						x+=1
						if x==5:
							a= numpy.float128(number)
							break
				break    			
		x=0
		input_file=open("Algorithm_"+str(j)+"/Algorithm_output/output_task_algo_"+str(j)+"_"+str(i)+".txt")
		for line in input_file:
				line = line.strip()
				for number in line.split():
						x+=1
						if x==5:
							b = numpy.float128(number)
							break
				break
		x=0
		input_file=open("Algorithm_"+str(j)+"/Algorithm_output/output_rob_algo_"+str(j)+"_"+str(i)+".txt")
		for line in input_file:
				line = line.strip()
				for number in line.split():
						x+=1
						if x==5:
							c = numpy.float128(number)
							break
				break
		x=0 
		input_file=open("Algorithm_"+str(j)+"/Stable_Marriage_output/Rank_output_"+str(j)+"_"+str(i)+".txt")
		for line in input_file:
				line = line.strip()
				for number in line.split():
						x+=1
						if x==5:
							d = numpy.float128(number)
							break
				break
		print a," ",b," ",c," ",d
		worksheet.write(i, 0, a)
		worksheet.write(i, 1, b)
		worksheet.write(i, 2, c)
		worksheet.write(i, 3, d)
		time.sleep(1)
	workbook.close()