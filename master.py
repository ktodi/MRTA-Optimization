import os
import sys
import xlsxwriter
import numpy
import time

for j in range(10,110,10):
# j=10
	workbook=xlsxwriter.Workbook('Algo_'+str(j)+'.xlsx')
	worksheet=workbook.add_worksheet()
	f = open('out.txt', 'w')
	worksheet.write('A1','Hungarian')
	worksheet.write('B1','Task_Algorithm')
	worksheet.write('C1','Robot_Algorithm')
	worksheet.write('D1','Stable_Marriage_Algorithm')
	owd=os.getcwd()
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
	for i in range(1,26):
		# os.system("gcc random_generator.c -lm -o random_generator")	
		os.system("./random_generator < out.txt > Algorithm_"+str(j)+"/Hungarian_input/input_hungarian_"+str(j)+"_"+str(i)+".txt")
		os.system("./random_generator_normalize < Algorithm_"+str(j)+"/Hungarian_input/input_hungarian_"+str(j)+"_"+str(i)+".txt >Algorithm_"+str(j)+"/Algorithm_input/input_algorithm_"+str(j)+"_"+str(i)+".txt")
		os.system("./rank_maker < Algorithm_"+str(j)+"/Hungarian_input/input_hungarian_"+str(j)+"_"+str(i)+".txt >Algorithm_"+str(j)+"/Stable_Marriage_input/Rank_Matrix_"+str(j)+"_"+str(i)+".txt")
		os.system("./random_generator_normalize_task < Algorithm_"+str(j)+"/Hungarian_input/input_hungarian_"+str(j)+"_"+str(i)+".txt >Algorithm_"+str(j)+"/Algorithm_input/input_algorithm_task_"+str(j)+"_"+str(i)+".txt")
		os.system("./robot < Algorithm_"+str(j)+"/Algorithm_input/input_algorithm_"+str(j)+"_"+str(i)+".txt >Algorithm_"+str(j)+"/Algorithm_output/output_rob_algo_"+str(j)+"_"+str(i)+".txt")
		os.system("./robot < Algorithm_"+str(j)+"/Algorithm_input/input_algorithm_task_"+str(j)+"_"+str(i)+".txt >Algorithm_"+str(j)+"/Algorithm_output/output_rob_algo_task_"+str(j)+"_"+str(i)+".txt")
		os.system("./stable_marriage < Algorithm_"+str(j)+"/Stable_Marriage_input/Rank_Matrix_"+str(j)+"_"+str(i)+".txt >Algorithm_"+str(j)+"/Stable_Marriage_output/Rank_output_"+str(j)+"_"+str(i)+".txt")
		os.system("./hungarian < Algorithm_"+str(j)+"/Hungarian_input/input_hungarian_"+str(j)+"_"+str(i)+".txt > Algorithm_"+str(j)+"/Hungarian_output/output_hungarian_"+str(j)+"_"+str(i)+".txt")
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
		input_file=open("Algorithm_"+str(j)+"/Algorithm_output/output_rob_algo_"+str(j)+"_"+str(i)+".txt")
		for line in input_file:
				line = line.strip()
				for number in line.split():
						x+=1
						if x==5:
							b = numpy.float128(number)
							break
				break
		x=0
		input_file=open("Algorithm_"+str(j)+"/Algorithm_output/output_rob_algo_task_"+str(j)+"_"+str(i)+".txt")
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