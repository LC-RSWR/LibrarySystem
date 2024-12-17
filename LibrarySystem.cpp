// LibrarySystem.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "librarysystem.h"

//主函数
int main()
{
	int choice;
	do {
		cout << "***** 图书管理系统 *****" << endl;
		cout << "***** 1. 添加书籍  *****" << endl;
		cout << "***** 2. 添加借阅者 ****" << endl;
		cout << "***** 3. 借阅书籍  *****" << endl;
		cout << "***** 4. 归还书籍  *****" << endl;
		cout << "***** 5. 显示书籍信息 **" << endl;
		cout << "***** 6. 显示借阅者信息*" << endl;
		cout << "***** 7. 借阅者登录 ****" << endl;
		cout << "****  8. 查询图书信息 **" << endl;
		cout << "***** 9. 交罚款 ********" << endl;
		cout << "***** 10.修改图书信息 **" << endl;
		cout << "***** 11.图书排序 ******" << endl;
		cout << "***** 12.添加管理员 ******" << endl;
		cout << "***** 13.管理员登录 ******" << endl;
		cout << "***** 0. 退出      *****" << endl;
		cout << "请输入您的操作： ";
		cin >> choice;
		string bookId, borrowerId, id, password;

		switch (choice) {
		case 1:
			AddBook();
			break;
		case 2:
			AddBorrower();
			break;
		case 3:
			borrowBook();
			break;
		case 4:
			returnBook();
			break;
		case 5:
			DisplayBooks();
			break;
		case 6:
			DisplayBorrowers();
			break;
		case 7:
			cout << "请输入借阅者证号：";
			cin >> id;
			cout << "请输入密码：";
			cin >> password;
			BorrowerLogin(id, password);
			break;
		case 8:
			cout << "请输入书籍编号：";
			cin >> bookId;
			QueryBookInfo(bookId);
			break;
		case 9:
			cout << "请输入借阅者ID：";
			cin >> id;
			PayFine(id);
			break;
		case 10:
			cout << "请输入书籍编号：";
			cin >> bookId;
			ModifyBookInfo(bookId);
			break;
		case 11:
			SortBooks();
			DisplayBooks();
			break;
		case 12:
			AddLibrarian();
			break;
		case 13:
			cout << "请输入管理员ID号：";
			cin >> id;
			cout << "请输入密码：";
			cin >> password;
			LibrarianLogin(id, password);
			break;
		case 0:
			cout << "退出程序" << endl;
			break;
		default:
			cout << "无效的操作，请重试" << endl;
		}
	} while (choice != 0);

	// 释放链表内存
	FreeBookList();
	FreeBorrowerList();
	FreeLibrarianList();

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
