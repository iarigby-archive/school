import csv
import json
from subprocess import PIPE, Popen
from datetime import datetime

traceroute = {"date": "20181007", "system": "linux", "traces": []}
ping = {"date": "20181007", "system": "linux", "pings": []}

nr_of_sites = 10

class Counter:
	def __init__(self):
		self.i = nr_of_sites*2
		self.t1 = datetime.now()
		self.t2 = datetime.now()
		self.diffs = []

	def update(self):
		self.i = self.i - 1
		self.t2 = datetime.now()
		diff = self.t2 - self.t1
		self.diffs.append(diff.seconds)
		self.t1 = self.t2		
		
	def remaining(self):
		if self.diffs != []:
			return round(self.i*sum(self.diffs)/len(self.diffs)/60, 2)
		return 0
		

def get_lines():
	res = []
	with open("top-1m.csv", "r") as in_file:
		lines = in_file.readlines()
		filtered = lines[:nr_of_sites] + lines[-nr_of_sites:]		
		reader = csv.reader(filtered, delimiter=',')
		for row in reader:
			res.append(row[1])
	return res

websites = get_lines()

def get_output(command, website):
	p = Popen(command + [website], stdout=PIPE)
	p.wait()
	out, err = p.communicate()
	return {"target": website, "output": out.decode("UTF-8")}

pcounter = Counter()

for website in websites:
	pcounter.update()
	print(f"pinging {website} ... \t{pcounter.i} left\t{pcounter.remaining()} minutes remaining".expandtabs(10))
	ping["pings"].append(get_output("ping -c 10".split(" "), website))	
	
tcounter = Counter()
for website in websites:
	tcounter.update()
	print(f"tracing {website} ... \t{tcounter.i} left\t{tcounter.remaining()} minutes remaining".expandtabs(10))
	traceroute["traces"].append(get_output(["traceroute"], website))

with open("traceroute.json", "w") as write_file:
	json.dump(traceroute, write_file)

with open("ping.json", "w") as write_file:
	json.dump(ping, write_file)

with open("times.json", "w") as write_file:
	json.dump({"pings": pcounter.diffs, "traceroute": tcounter.diffs} , write_file)