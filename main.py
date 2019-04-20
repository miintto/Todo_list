from tkinter import *
from tkinter import ttk
from schedule import UserSchedule
import datetime as dt

model = UserSchedule()



class TkSchedule:
	def __init__(self, root):
		self.root = root
		self.run()

	def run(self):
		self.root.title('D-day Todo List')
		self.root.resizable(0, 0) 

		self.deadline = StringVar(self.root, value='')
		self.todo = StringVar(self.root, value='')
		self.memo = StringVar(self.root, value='')
		self.importance = IntVar()
		self.show = IntVar()
		self.show.set(0)

		self.frame1 = Frame(self.root, bd=2)
		self.frame1.pack()
		self.frame2 = Frame(self.frame1, bd=2, relief="sunken")
		self.frame3 = Frame(self.root, bd=2)
		self.frame3.pack()

		label_0 = Label(self.frame1, text = 'D-day Todo List', height=2)
		label_0.config(font=('', 20))
		label_0.grid(row=0, column=1, columnspan=3)
		label_blk0 = Label(self.frame1, text = '', width=5)
		label_blk0.grid(row=0, column=0)
		label_blk1 = Label(self.frame1, text = '', width=5)
		label_blk1.grid(row=0, column=4)
		buttun_1 = Button(self.frame1, text = '새로고침', command = self.clean_all)
		buttun_1.grid(row=1, column=3)

		style = ttk.Style()
		style.configure("Treeview", font=(None, 10), rowheight=36)
		self.Tree = ttk.Treeview(self.frame1, columns = ('#1', '#2'), show = 'headings', height=8)
		self.Tree.column('#1', width=180)
		self.Tree.heading('#1', text = '일정')
		self.Tree.column('#2', width=80)
		self.Tree.heading('#2', text = 'D-day')
		ScrBar = ttk.Scrollbar(self.frame1, orient="vertical", command = self.Tree.yview)
		ScrBar.grid(row=2, column=4, sticky='nsw')
		self.load_schedule()
		self.Tree.tag_configure('1', background='#FA8072')
		self.Tree.tag_configure('2', background='#FDB674')
		self.Tree.tag_configure('3', background='#FBEC82')
		self.Tree.grid(row=2, column=1, columnspan=3)

		buttun_0 = Button(self.frame1, text = '일정완료', command = self.complete_schedule)
		buttun_0.grid(row=3, column=1)
		buttun_1 = Button(self.frame1, text = 'info.', command = self.show_schedule)
		buttun_1.grid(row=3, column=2)
		buttun_1 = Button(self.frame1, text = '삭제', command = self.delelte_schedule)
		buttun_1.grid(row=3, column=3)

		self.toggle_button = ttk.Checkbutton(self.frame1, width=2, text='+', variable=self.show, style='Toolbutton', command=self.toggle)
		self.toggle_button.grid(row=4, column=4)
		
		label_1 = Label(self.frame2, text = '날짜 : ')
		label_1.grid(row=0, column=1, sticky='w')
		label_blk0 = Label(self.frame2, text = '', width=5)
		label_blk0.grid(row=0, column=0)
		label_blk1 = Label(self.frame2, text = '', width=5)
		label_blk1.grid(row=0, column=4)
		text_1 = Entry(self.frame2, width=20, textvariable = self.deadline)
		text_1.grid(row=1, column=1, columnspan=2)

		label_2 = Label(self.frame2, text = '제목 : ')
		label_2.grid(row=2, column=1, sticky='w')
		text_2 = Entry(self.frame2, width=20, textvariable = self.todo)
		text_2.grid(row=3, column=1, columnspan=2)

		label_3 = Label(self.frame2, text = '중요도 : ')
		label_3.grid(row=0, column=3, sticky='w')
		buttun_2 = Radiobutton(self.frame2, text = '높음', value = 1, variable = self.importance)
		buttun_2.grid(row=1, column=3)
		buttun_3 = Radiobutton(self.frame2, text = '중간', value = 2, variable = self.importance)
		buttun_3.grid(row=2, column=3)
		buttun_4 = Radiobutton(self.frame2, text = '낮음', value = 3, variable = self.importance)
		buttun_4.grid(row=3, column=3)

		label_4 = Label(self.frame2, text = '메모 : ')
		label_4.grid(row=4, column=1, sticky='w', columnspan=2)
		self.text_3 = Text(self.frame2, width=36, height=4)
		self.text_3.grid(row=5, column=1, columnspan=3)

		buttun_5 = Button(self.frame2, text = '등록', command = self.insert_schedule)
		buttun_5.grid(row=6, column=1, columnspan=3)

		label_5 = Label(self.frame3, text = ' Created  by  miintto  -  2019  -  D-day Todo List Scheduler ')
		label_5.pack()

		self.root.mainloop()

	def toggle(self):
		if bool(self.show.get()):
			self.frame2.grid(row=5, column=0, columnspan=5)
			self.toggle_button.configure(text='-')
		else:
			self.frame2.grid_remove()
			self.toggle_button.configure(text='+')


	def insert_schedule(self):
		new_date = self.deadline.get()
		new_todo = self.todo.get()
		new_importance = self.importance.get()
		memo = self.text_3.get('1.0', "end-1c")
		model.make_schedule(new_date, new_todo, new_importance, memo).save()
		self.clean_info()
		self.load_schedule()


	def load_schedule(self):
		self.clean_table()
		for _schedule in model.filter().get():
			d_day = (_schedule['deadline']-dt.datetime.now())
			if d_day.days<0:
				model.delete(_schedule['id'])
			elif d_day.days==0:
				self.Tree.insert('', 'end', 
								text = '', 
								values=(_schedule['todo'], str(d_day)[:-10]+' 시간', _schedule['id']), 
								tag=(_schedule['importance']))
			else:
				self.Tree.insert('', 'end', 
								text = '', 
								values=(_schedule['todo'], d_day.days, _schedule['id']), 
								tag=(_schedule['importance']))

	def clean_table(self):
		for line in self.Tree.get_children():
			self.Tree.delete(line)


	def clean_info(self):
		new_date = self.deadline.set('')
		new_todo = self.todo.set('')
		new_importance = self.importance.set(0)
		self.text_3.delete('1.0', "end-1c")


	def clean_all(self):
		self.load_schedule()
		self.clean_info()


	def show_schedule(self):
		tree_id = self.Tree.selection()
		selected_obj = self.Tree.item(tree_id)
		idx = selected_obj['values'][2]
		schedule = model.filter(id=idx).get()[0]
		deadline = schedule['deadline']
		todo = schedule['todo']
		importance = schedule['importance']
		memo = schedule['memo']
		self.deadline.set(deadline)
		self.todo.set(todo)
		self.importance.set(importance)
		self.text_3.delete('1.0', "end-1c")
		self.text_3.insert('1.0', memo)


	def complete_schedule(self):
		tree_id = self.Tree.selection()
		selected_obj = self.Tree.item(tree_id)
		idx = selected_obj['values'][2]
		model.update_importance(idx)
		self.load_schedule()


	def delelte_schedule(self):
		tree_id = self.Tree.selection()
		selected_obj = self.Tree.item(tree_id)
		idx = selected_obj['values'][2]
		model.delete(idx)
		self.load_schedule() 



if __name__ == '__main__':
	root = Tk()
	TkSchedule(root)