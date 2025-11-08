# 🏦 E-Banking System in C

A feature-rich command-line e-banking application written in C with role-based access control (User & Admin modes).

## ✨ Features

### 👤 User Mode
- **Create Accounts**: Create new bank accounts with unique account numbers (ACC001001, ACC001002, etc.)
- **View Account Info**: Display detailed information for your account
- **Deposit Money**: Add funds to your account with validation
- **Withdraw Money**: Withdraw funds with balance and validation checks
- **Check Balance**: View current balance in real-time
- **Transaction History**: View complete transaction history with timestamps

### 👨‍💼 Admin Mode (Protected by Authentication)
- **View All Accounts**: Display all bank accounts with status
- **Manage Accounts**: View, close, and reopen accounts
- **Admin Management**: Add new administrators to the system
- **Transaction Monitoring**: View transaction history for any account
- **Account Status Control**: Close accounts (requires zero balance) or reactivate closed accounts

### 🔒 Security Features
- Admin authentication system (username/password)
- Default admin credentials: `admin` / `admin123`
- Role-based access control
- Input validation and error handling

## Project Structure

```
ebank/
├── include/
│   └── account.h          # Header file with function declarations
├── src/
│   ├── main.c             # Main program with menu system
│   └── account.c          # Account management functions
├── Makefile               # Build configuration
└── README.md              # This file
```

## File Descriptions

### `include/account.h`
- Defines data structures for Account, Transaction, and Bank
- Declares all banking functions
- Sets constants for maximum values

### `src/account.c`
- Implements all banking operations
- Manages account creation and retrieval
- Handles deposits, withdrawals, and transactions
- Displays account information and history

### `src/main.c`
- Interactive menu system
- User input handling
- Command processing
- Input validation

## Compilation

### Using Make (Recommended)

```bash
# Build the project
make

# Run the application
make run

# Clean build files
make clean
```

### Manual Compilation

```bash
# Compile
gcc -Wall -Wextra -std=c99 -I./include -o ebank src/*.c

# Run
./ebank
```

## Usage

1. **Build the project**:
   ```bash
   make
   ```

2. **Run the application**:
   ```bash
   make run
   ```

3. **Follow the menu** to perform banking operations

### Example Workflow

#### User Mode:
```
1. Select "Mode Utilisateur" from main menu

2. Create Account
   - Enter: Alice Dupont
   - System creates: ACC001001

3. Deposit Money
   - Account: ACC001001
   - Amount: 5000.00 DT
   - New Balance: 5000.00 DT

4. Withdraw Money
   - Account: ACC001001
   - Amount: 1000.00 DT
   - New Balance: 4000.00 DT

5. View Transactions
   - See complete transaction history with dates
```

#### Admin Mode:
```
1. Select "Mode Administrateur"
2. Login with credentials (admin/admin123)
3. View all accounts in the system
4. Close/reopen accounts as needed
5. Add new administrators
```

## 📊 Data Structures

### Account
```c
typedef struct {
    int id;
    char account_number[12];
    char holder_name[100];
    double balance;
    time_t created_date;
    int is_active;  // 1 = active, 0 = closed
} Account;
```

### Transaction
```c
typedef struct {
    int id;
    char account_number[12];
    char transaction_type[20];  // "DEPOSIT" or "WITHDRAWAL"
    double amount;
    time_t transaction_date;
} Transaction;
```

### Admin Account
```c
typedef struct {
    char username[50];
    char password[50];
    int is_active;  // 1 = active, 0 = inactive
} Admin_account;
```

### Bank
```c
typedef struct {
    Account accounts[MAX_ACCOUNTS];
    int account_nb;
    Transaction transactions[MAX_TRANSACTIONS];
    int transaction_nb;
    Admin_account admins[MAX_ADMINS];
    int admin_count;
} Bank;
```

## ⚙️ System Configuration

### Current Limits (configurable in `account.h`)
- **Maximum Accounts**: 100
- **Maximum Transactions**: 1000
- **Maximum Admins**: 5
- **Account Number Format**: ACC + 6 digits (e.g., ACC001001)

### Technical Details
- Data stored in memory (no persistence between sessions)
- Single-threaded operation
- UTF-8 support for French characters
- Timestamps using system time

## 🚀 Future Enhancements

### Planned Features
- [ ] File-based persistence (save/load to JSON/CSV)
- [ ] Database integration (SQLite)
- [ ] User PIN/password protection for accounts
- [ ] Transfer money between accounts
- [ ] Account statements (PDF generation)
- [ ] Email notifications
- [ ] Interest calculation on savings
- [ ] Loan management system
- [ ] Multi-currency support
- [ ] Mobile app integration API

### Security Improvements
- [ ] Password hashing (bcrypt)
- [ ] Session management
- [ ] Login attempt limits
- [ ] Audit logs
- [ ] Two-factor authentication

## 📋 Requirements

- **Compiler**: GCC (or any C99 compatible compiler)
- **Build Tool**: Make utility (optional but recommended)
- **OS**: Linux/Unix environment (or Windows with WSL/MinGW)
- **Terminal**: UTF-8 support for proper character display

## 🔧 Compilation Flags

- `-Wall`: Enable all compiler warnings
- `-Wextra`: Enable extra warnings
- `-std=c99`: Use C99 standard
- `-I./include`: Include header files from include directory

## 🎯 Learning Objectives

This project demonstrates:
- **Data Structures**: structs, arrays, pointers
- **Memory Management**: Stack allocation, pointer arithmetic
- **File Organization**: Header/source file separation
- **Input Validation**: User input handling and validation
- **Role-Based Access**: Admin vs User permissions
- **Authentication**: Basic login system
- **Modular Design**: Separation of concerns

## 📝 Project Status

**Status**: ✅ Fully Functional

**Version**: 1.0.0

**Last Updated**: November 2025

## 👨‍💻 Author

Created by **Ilef** as a comprehensive C programming project demonstrating:
- System design and architecture
- Data structure implementation
- User interface design
- Security basics

## 📄 License

Free to use and modify for educational purposes.

## 🤝 Contributing

Feel free to fork this project and submit pull requests for:
- Bug fixes
- New features
- Documentation improvements
- Code optimizations

## 📞 Support

For questions or issues, please open an issue on GitHub.

---

**⭐ If you find this project useful, please give it a star!**
