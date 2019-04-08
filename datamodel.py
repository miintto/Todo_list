import os
import csv
import shutil
import datetime as dt


custum_dir = os.path.expanduser('~')
db_url = custum_dir+'/db'
if not os.path.isdir(db_url):
	os.makedirs(db_url)


class DataModel:
	def __init__(self):
		self.initialize()


	def initialize(self):
		self.deadline = None
		self.todo = None
		self.importance = None
		self.memo = None


	def filter(self, **kwargs):
		db_list = []
		try:
			f = open(db_url+'/user_schedule.csv', 'r')
		except:
			f = open(db_url+'/user_schedule.csv', 'w', newline='')
			f.close()
			f = open(db_url+'/user_schedule.csv', 'r')
		rdr = csv.reader(f)
		for line in rdr:
			db_dict = dict()
			db_dict['id'] = int(line[0])
			db_dict['deadline'] = dt.datetime.strptime(line[1], "%Y-%m-%d %H:%M:%S")
			db_dict['todo'] = line[2]
			db_dict['importance'] = int(line[3])
			db_dict['memo'] = line[4]
			db_list.append(db_dict)
				
		self.db_filted_list = []
		for _dict in db_list:
			boolen = 1
			for key, val in  kwargs.items():
				boolen *= (_dict[key]==val)
			if boolen:
				self.db_filted_list.append(_dict)
			self.db_filted_list.sort(key = lambda x:x['deadline'])
		return self


	def get(self):
		return self.db_filted_list


	def save(self):
		with open(db_url+'/user_schedule.csv', 'r') as f:
			rdr = csv.reader(f)
			for line in rdr:
				last_line = line
			try:
				idx = int(last_line[0])
			except:
				idx = 0	
		if self.deadline!=None:
			with open(db_url+'/user_schedule.csv', 'a', newline='') as f:
				wrt = csv.writer(f)
				wrt.writerow([idx+1, self.deadline, self.todo, self.importance, self.memo])


	def delete(self, idx):
		with open(db_url+'/user_schedule.csv', 'r', newline='') as f, open(db_url+'/user_schedule_bkup.csv', 'w', newline='') as g:
			rdr = csv.reader(f)
			wrt = csv.writer(g)
			for line in rdr:
				if line[0]!=str(idx):
					wrt.writerow(line)
		shutil.move(db_url+'/user_schedule_bkup.csv', db_url+'/user_schedule.csv')


	def update_importance(self, idx):
		pass