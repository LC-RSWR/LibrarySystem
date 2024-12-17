#pragma once
/*图书馆管理系统*/
#include<iostream>
#include<string>
#include <cstring>
#include<ctime>
using namespace std;

//定义书籍结构体
struct Book {
	string bookId; //书号
	string title;  //书名
	string author; //作者
	int quantity;  //现存量
	int total;     //库存量
	float price;   //价格
	Book* next;    //指向下一本书的指针
};

//定义借阅者结构体
struct Borrower {
	string id;           //借阅者ID
	string password;     //密码
	int maxBooks;        //最大借书量
	int borrowedBooks;   //现已借书量
	float fine;          //罚款
	Book* borrowerBooks; //借阅者的书籍链表 
	time_t borrowTime;   //借书时间
	Borrower* next;      //指向下一个借阅者的指针
};

//定义图书管理员结构体
struct Librarian {
	string id;      //管理员账号
	string password;//密码
	Librarian* next;//指向下一个管理员的指针
};

//索引表，用于快速查找书籍
Book* indexTable[10] = { NULL };//0-9数字的索引表

//借阅者链表头指针
Borrower* borrowerHead = NULL;

//图书管理员链表头指针
Librarian* librarianHead = NULL;

//书籍链表头指针
Book* bookHead = NULL;

int StringToInt(const string& str) {//将字符串传换成整数
	int res = 0;
	for (int i = 0; i < str.length(); ++i) {
		char c = str[i];
		if (c < '0' || c > '9') break;
		res = res * 10 + (c - '0');
	}
	return res;
}

//添加书籍到链表
void AddBook()
{
	string bookId, title, author;
	int quantity, total;
	float price;
	cout << "请输入书籍编号：" << endl;
	cin >> bookId;
	cout << "请输入书籍名称：" << endl;
	cin.ignore();
	getline(cin, title);
	cout << "请输入书籍作者：" << endl;
	getline(cin, author);
	cout << "请输入书籍现存量：" << endl;
	cin >> quantity;
	cout << "请输入书籍库存量：" << endl;
	cin >> total;
	cout << "请输入书籍价格：" << endl;
	cin >> price;


	Book* newBook = new Book;
	newBook->bookId = bookId;
	newBook->title = title;
	newBook->author = author;
	newBook->quantity = quantity;
	newBook->total = total;
	newBook->price = price;
	newBook->next = NULL;

	// 添加到书籍链表
	if (bookHead == NULL) {
		bookHead = newBook;
	}
	else {
		Book* temp = bookHead;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newBook;
	}

	//添加到索引表
	int id = StringToInt(bookId.substr(0, 1));//使用substr函数
	if (indexTable[id] == NULL) {
		indexTable[id] = newBook;
	}
	else {
		Book* temp = indexTable[id];
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newBook;
	}
	cout << "书籍添加成功!" << endl;
}


//查找书籍
Book* findBookById(string& bookId)
{
	int id = StringToInt(bookId.substr(0, 1));
	Book* book = indexTable[id];
	while (book != NULL)
	{
		if (book->bookId == bookId)
		{
			return book;
		}
		book = book->next;
	}
	return NULL;
}

// 添加管理员
void AddLibrarian() {
	string id, password;
	cout << "请输入管理员ID：" << endl;
	cin >> id;
	cout << "请输入管理员密码：" << endl;
	cin.ignore();  // 清除输入缓冲区的换行符
	getline(cin, password);

	Librarian* newLibrarian = new Librarian;
	newLibrarian->id = id;
	newLibrarian->password = password;
	newLibrarian->next = NULL;

	if (librarianHead == NULL) {
		librarianHead = newLibrarian;
	}
	else {
		Librarian* temp = librarianHead;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newLibrarian;
	}

	cout << "添加管理员成功！" << endl;
}

// 查找管理员根据ID
Librarian* findLibrarianById(string id)
{
	Librarian* temp = librarianHead;
	while (temp != NULL) {
		if (temp->id == id) {
			return temp; // 找到管理员，返回指针
		}
		temp = temp->next;
	}
	return NULL; // 如果找不到管理员，返回NULL
}


// 管理员登录系统
bool LibrarianLogin(string id, string password)
{
	Librarian* librarian = findLibrarianById(id); // 查找管理员
	if (librarian && librarian->password == password) // 校验密码
	{
		cout << "登录成功！" << endl;
		return true;
	}
	else {
		cout << "登录失败，账号或密码错误。" << endl;
		return false;
	}
}



//添加借阅者
void AddBorrower()
{
	string id, password;
	int maxBooks;
	cout << "请输入借阅者ID：" << endl;
	cin >> id;
	cout << "请输入借阅者密码：" << endl;
	cin.ignore();
	getline(cin, password);
	cout << "请输入最大借书数量：" << endl;
	cin >> maxBooks;

	Borrower* newBorrower = new Borrower;
	newBorrower->borrowerBooks = NULL;
	newBorrower->id = id;
	newBorrower->password = password;
	newBorrower->maxBooks = maxBooks;
	newBorrower->borrowedBooks = 0;
	newBorrower->fine = 0.0;
	newBorrower->next = NULL;

	if (borrowerHead == NULL)
	{
		borrowerHead = newBorrower;
	}
	else {
		Borrower* temp = borrowerHead;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newBorrower;
	}
	cout << "添加借阅者成功！" << endl;
}

//查找借阅者
Borrower* findBorrowerById(string& id)
{
	Borrower* borrower = borrowerHead;
	while (borrower != NULL)
	{
		if (borrower->id == id)
		{
			return borrower;
		}
		borrower = borrower->next;
	}
	return NULL;
}

//借书操作
void borrowBook()
{
	string bookId, borrowerId;
	cout << "请输入书籍编号：" << endl;
	cin >> bookId;
	cout << "请输入借阅者ID：" << endl;
	cin >> borrowerId;

	Book* book = findBookById(bookId);
	if (book == NULL || book->quantity <= 0)
	{
		cout << "没有现存的图书可以借出" << endl;
		return;
	}
	//减少书籍的现存量
	book->quantity--;
	//在借阅者链表中找到对应的借阅者，并将书籍添加到其借阅列表
	Borrower* borrower = findBorrowerById(borrowerId);
	if (borrower != NULL)
	{
		Book* newBorrowedBook = new Book;
		*newBorrowedBook = *book;//复制书籍信息
		newBorrowedBook->next = borrower->borrowerBooks;
		borrower->borrowerBooks = newBorrowedBook;
		time(&borrower->borrowTime);//记录借书时间
		borrower->borrowedBooks++; // 更新借阅者当前借书数量
	}
	else {
		cout << "借阅者不存在" << endl;
	}
	cout << "借阅成功！！！" << endl;
}

//还书操作
void returnBook()
{
	string bookId, borrowerId;
	cout << "请输入书籍编号：" << endl;
	cin >> bookId;
	cout << "请输入借阅者ID：" << endl;
	cin >> borrowerId;

	Borrower* borrower = findBorrowerById(borrowerId);
	if (borrower == NULL)
	{
		cout << "借阅者不存在" << endl;
		return;
	}
	Book* book = findBookById(bookId);
	if (book == NULL)
	{
		cout << "书籍不存在" << endl;
		return;
	}
	//在借阅者的书籍链表中找到对应的书籍，并移除
	Book** pp = &(borrower->borrowerBooks);
	while (*pp != NULL) {
		if ((*pp)->bookId == bookId)
		{
			Book* temp = *pp;
			*pp = (*pp)->next;
			delete temp;
			//增加书籍的现存量
			book->quantity++;
			//计算罚款
			time_t currentTime;
			time(&currentTime);
			double diff = difftime(currentTime, borrower->borrowTime);
			if (diff > 30 * 24 * 60 * 60) {
				//超过30天
				int dayOverdue = static_cast<int>(diff) / (24 * 60 * 60) - 30;
				borrower->fine += dayOverdue * 0.1;
			}
			cout << "还书成功！！！" << endl;
			return;
		}
		pp = &((*pp)->next);
	}
	cout << "该书无法找到" << endl;
}

// 显示所有书籍信息
void DisplayBooks() {
	cout << "显示所有书籍信息：" << endl;
	Book* tempBook = bookHead;
	while (tempBook != NULL) {
		cout << "书籍编号： " << tempBook->bookId << "，书籍名称： " << tempBook->title
			<< "，书籍作者： " << tempBook->author << "，书籍现存量：" << tempBook->quantity
			<< "，书籍库存量： " << tempBook->total << "，书籍价格：" << tempBook->price << endl;
		tempBook = tempBook->next;
	}
}

// 显示所有借阅者信息
void DisplayBorrowers() {
	cout << "显示所有借阅者信息：" << endl;
	Borrower* tempBorrower = borrowerHead;
	while (tempBorrower != NULL) {
		cout << "借阅者ID： " << tempBorrower->id << "，最大借书量： " << tempBorrower->maxBooks
			<< "，已借书量： " << tempBorrower->borrowedBooks
			<< "，罚款金额： " << tempBorrower->fine << endl;
		Book* tempBook = tempBorrower->borrowerBooks;
		while (tempBook != NULL) {
			cout << "  借阅书籍编号： " << tempBook->bookId << "，书名： " << tempBook->title << endl;
			tempBook = tempBook->next;
		}
		tempBorrower = tempBorrower->next;
	}
}

//借阅者登录系统
bool BorrowerLogin(string id, string password)
{
	Borrower* borrower = findBorrowerById(id);
	if (borrower && borrower->password == password)
	{
		cout << "登录成功！" << endl;
		return true;
	}
	else {
		cout << "登录失败，证号或密码错误。" << endl;
		return false;
	}
}

//查询图书信息
void QueryBookInfo(string bookId)
{
	Book* book = findBookById(bookId);
	if (book)
	{
		cout << "书籍编号：" << book->bookId << "，书名：" << book->title
			<< "，作者：" << book->author << "，现存量：" << book->quantity
			<< "，库存量：" << book->total << "，价格：" << book->price << endl;
	}
	else
	{
		cout << "未找到书籍。" << endl;
	}
}

//修改图书信息
void ModifyBookInfo(string bookId)
{
	Book* book = findBookById(bookId);
	if (book)
	{
		cout << "请输入新的书籍名称：";
		cin.ignore();
		getline(cin, book->title);
		cout << "请输入新的书籍作者：";
		getline(cin, book->author);
		cout << "请输入新的书籍现存量：";
		cin >> book->quantity;
		cout << "请输入新的书籍库存量：";
		cin >> book->total;
		cout << "请输入新的书籍价格：";
		cin >> book->price;
		cout << "书籍信息修改成功！" << endl;
	}
	else
	{
		cout << "未找到书籍。" << endl;
	}
}

//交罚款
void PayFine(string id)
{
	Borrower* borrower = findBorrowerById(id);
	if (borrower && borrower->fine > 0) {
		cout << "请输入交罚款金额：";
		float payment;
		cin >> payment;
		if (payment >= borrower->fine)
		{
			borrower->fine = 0;
			cout << "罚款已缴纳，金额：" << payment << "元。" << endl;
		}
		else
		{
			cout << "缴纳金额不足。" << "欠款：" << borrower->fine << "元。" << endl;
		}
	}
	else {
		cout << "未找到借阅者或无罚款" << endl;
	}
}

// 交换两个书籍节点的数据
void swapNodes(Book* a, Book* b) {
	Book temp = *a;
	*a = *b;
	*b = temp;
}

//快速排序的分区函数，使用双指针法
Book* partition(Book* low, Book* high) {
	string pivot = high->bookId; //基准元素
	Book* i = low;
	Book* j = low;
	while (j != high) {
		if (j->bookId < pivot) {
			swapNodes(i, j);
			i = i->next;
		}
		j = j->next;
	}
	return i;
}

// 快速排序函数
void quickSortBooks(Book* low, Book* high) {
	if (low != high && low != NULL && high != NULL) {
		Book* pivot = partition(low, high);
		if (pivot != NULL && pivot->next != NULL) {
			quickSortBooks(low, pivot);
			quickSortBooks(pivot->next, high);
		}
	}
}

// 图书排序函数
void SortBooks() {
	if (bookHead != NULL && bookHead->next != NULL) {
		Book* tail = bookHead;
		while (tail->next != NULL) {
			tail = tail->next;
		}
		quickSortBooks(bookHead, tail);
	}
}

// 释放书籍链表内存
void FreeBookList() {
	Book* current = bookHead;
	while (current != NULL) {
		Book* temp = current;
		current = current->next;
		delete temp;
	}
	bookHead = NULL;
}

// 释放借阅者链表内存
void FreeBorrowerList() {
	Borrower* current = borrowerHead;
	while (current != NULL) {
		Borrower* temp = current;
		current = current->next;
		delete temp;
	}
	borrowerHead = NULL;
}

// 释放图书管理员链表内存
void FreeLibrarianList() {
	Librarian* current = librarianHead;
	while (current != NULL) {
		Librarian* temp = current;
		current = current->next;
		delete temp;
	}
	librarianHead = NULL;
}






/*
借阅者结构体：属性包含（1）借阅者证号 （2）密码 （3）最大借书数量

方法包括（1）借书 （2）还书 （3）查看用户账户 （4）查看借书数量 （5）登录系统

（5）查询图书信息 （6）交罚款（超过规定期限30天，每本书一天0.1元）

图书管理员结构体：属性包含（1）管理员帐号 （2）密码

方法包括（1）查询图书信息（2）修改图书信息 (3)排序（按照图书编号从小到大排序）

图书结构体：属性包含（1）书号（2）书名（3）数量（4）价格（5）现存量（6）库存量

题目是什么 做了什么 有哪些数据 数据之间的存储和关系 功能 排序：基本思想，程序调用调试 看是否一致 代码3题 */