import datetime as dt
from datamodel import DataModel


class UserSchedule(DataModel):
	def __init__(self):
		pass


	def make_schedule(self, date, todo, importance, memo=''):
		self.deadline = self._check_datetime(date)
		self.todo = todo
		self.importance = importance
		self.memo = memo
		return self

	def _check_datetime(self, date):
		try:
			if len(date)==10:
				date+=' 00:00:00'
			if len(date)==16:
				date+=':00'
			datetime = dt.datetime.strptime(date, "%Y-%m-%d %H:%M:%S")
			return datetime
		except:
			try:
				return self.smart_datetime(date)
			except:
				return None


	def smart_datetime(self, text):
		new_date = self._smart_date(text)
		new_hour, new_second = self._smart_time(text)
		return dt.datetime.combine(new_date, new_hour)+new_second


	def _smart_date(self, text):
		if '오늘' in text:
			date = dt.date.today()
			new_date = date

		elif '모레' in text:
			date = dt.date.today()
			new_date = (date+dt.timedelta(2))

		elif ('내일' in text) | ('낼' in text):
			date = dt.date.today()
			new_date = (date+dt.timedelta(1))

		elif '이번주' in text:
			dtime = dt.datetime.today()
			weekdays = {'월':0, '화':1, '수':2, '목':3, '금':4, '토':5, '일':6}
			if '요일' in text:
				wk = text[text.index('요일')-1]
			elif '욜' in text:
				wk = text[text.index('욜')-1]
			else:
				for wk_key in weekdays.keys():
					if text.find(wk_key)>-1:
						wk = wk_key
						break
			while (dtime.weekday() != weekdays[wk]):
				dtime += dt.timedelta(1)
			new_date = dtime.date()

		elif ('다다음주' in text)|('다담주' in text):
			dtime = dt.datetime.today()
			dtime += dt.timedelta(8)
			weekdays = {'월':0, '화':1, '수':2, '목':3, '금':4, '토':5, '일':6}
			if '요일' in text:
				wk = text[text.index('요일')-1]
			elif '욜' in text:
				wk = text[text.index('욜')-1]
			else:
				for wk_key in weekdays.keys():
					if text.find(wk_key)>-1:
						wk = wk_key
						break
			while (dtime.weekday() != 6):
				dtime += dt.timedelta(1)
			while (dtime.weekday() != weekdays[wk]):
				dtime += dt.timedelta(1)
			new_date = dtime.date()

		elif ('다음주' in text)|('담주' in text):
			dtime = dt.datetime.today()
			dtime += dt.timedelta(1)
			weekdays = {'월':0, '화':1, '수':2, '목':3, '금':4, '토':5, '일':6}
			if '요일' in text:
				wk = text[text.index('요일')-1]
			elif '욜' in text:
				wk = text[text.index('욜')-1]
			else:
				for wk_key in weekdays.keys():
					if text.find(wk_key)>-1:
						wk = wk_key
						break
			while (dtime.weekday() != 6):
				dtime += dt.timedelta(1)
			while (dtime.weekday() != weekdays[wk]):
				dtime += dt.timedelta(1)
			new_date = dtime.date()

		return new_date

	def _smart_time(self, text):
		new_hour = dt.time(0, 0)
		new_second = dt.timedelta(0)
		if '시' in text:
			idx = text.index('시')
			try:
				h = int(text[idx-2:idx])
			except:
				h = int(text[idx-1:idx])
			if ('오전' not in text) & (h<12):
				h+=12
			new_hour = dt.time(h)
		if '반' in text:
			new_second = dt.timedelta(0, 60*30)
		return new_hour, new_second