#ifndef BANKACC_H_1
#define BANKACC_H_1
class Bank {
	char name[30];
	char account[7];
	double debt;
public:
	Bank();
	Bank(const char *co, const char *ac, double db = 0.0);
	~Bank();
	void show() const;
	void deposit(const double money);
	void withdrawal(const double money);
};
#endif // !BANKACC_H_1
