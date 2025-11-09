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
- **💸 Transfer Money**: Transfer funds between accounts with validation (NEW)
- **📄 Account Statements**: Generate detailed account statements in text format (NEW)

### 👨‍💼 Admin Mode (Protected by Authentication)
- **View All Accounts**: Display all bank accounts with status
- **Manage Accounts**: View, close, and reopen accounts
- **Admin Management**: Add new administrators to the system
- **Transaction Monitoring**: View transaction history for any account
- **Account Status Control**: Close accounts (requires zero balance) or reactivate closed accounts
- **💰 Interest Calculation**: Apply 3% annual interest to accounts, prorated by days (NEW)
- **💾 Data Persistence**: Save/load all data to CSV files for persistence across sessions (NEW)

### 🔒 Security Features
- Admin authentication system (username/password)
- Default admin credentials: `admin` / `admin123`
- Role-based access control
- Input validation and error handling

## Project Structure

```
ebank/
├── include/
│   ├── account.h          # Header file with function declarations
│   └── persistence.h      # Persistence & financial operations (NEW)
├── src/
│   ├── main.c             # Main program with menu system
│   ├── account.c          # Account management functions
│   └── persistence.c      # CSV persistence & transfers (NEW)
├── data/                  # Auto-created directory for CSV files (NEW)
│   ├── accounts.csv       # Saved accounts
│   ├── transactions.csv   # Saved transactions
│   └── admins.csv         # Saved admin accounts
├── Makefile               # Build configuration
├── README.md              # This file
├── FEATURES.md            # Detailed feature documentation (NEW)
└── QUICKSTART.md          # Quick start guide (NEW)
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
- Auto-save/load data on startup/exit (NEW)

### `src/persistence.c` (NEW)
- CSV file operations (save/load)
- Money transfer between accounts
- Account statement generation
- Interest calculation and application

### `include/persistence.h` (NEW)
- Declares persistence functions
- Defines file paths and constants
- Financial operations prototypes

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
    char transaction_type[20];  // "DEPOSIT", "WITHDRAWAL", "TRANSFER_IN", "TRANSFER_OUT", "INTEREST"
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
- **Maximum Accounts**: 150 (increased)
- **Maximum Transactions**: 2000 (increased)
- **Maximum Admins**: 5
- **Account Number Format**: ACC + 6 digits (e.g., ACC001001)
- **Interest Rate**: 3% annual (0.03), prorated by days

### Technical Details
- **Data Persistence**: CSV files in `data/` directory
- **Auto-save**: On program exit
- **Auto-load**: On program startup
- Single-threaded operation
- UTF-8 support for French characters
- Timestamps using system time

## 🆕 New Features (Version 2.0)

### 1. 💾 CSV Persistence
- **Automatic saving** on exit
- **Automatic loading** on startup
- Three CSV files: `accounts.csv`, `transactions.csv`, `admins.csv`
- All data persists across sessions

### 2. 💸 Money Transfers
- Transfer between any two active accounts
- Validates both accounts exist and are active
- Checks sufficient balance
- Creates dual transactions (TRANSFER_OUT + TRANSFER_IN)
- Instant balance updates

### 3. 📄 Account Statements
- Generate formatted text reports
- Includes:
  - Account information
  - Complete transaction history
  - Current balance
  - Statement date
- Files named: `releve_ACC######.txt`

### 4. 💰 Interest Calculation
- 3% annual interest rate
- Prorated by number of days
- Formula: `interest = balance × 0.03 × (days/365)`
- Can apply to single account or all accounts
- Creates INTEREST transaction for tracking

## 🚀 Future Enhancements

### Completed Features ✅
- [x] File-based persistence (CSV format)
- [x] Transfer money between accounts
- [x] Account statements (text format)
- [x] Interest calculation on savings

### Planned Features
- [ ] Database integration (SQLite)
- [ ] User PIN/password protection for accounts
- [ ] PDF statement generation
- [ ] Email notifications
- [ ] Loan management system
- [ ] Multi-currency support
- [ ] Mobile app integration API
- [ ] Scheduled automatic interest application

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
- **Disk Space**: Minimal (~1MB for CSV files and statements)

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
- **File I/O**: CSV parsing and generation (NEW)
- **Financial Calculations**: Interest computation (NEW)
- **Data Persistence**: Save/load state management (NEW)

## 📝 Project Status

**Status**: ✅ Fully Functional with Advanced Features

**Version**: 2.0.0

**Last Updated**: November 9, 2025

### What's New in v2.0
- ✅ CSV-based data persistence
- ✅ Money transfer functionality
- ✅ Account statement generation
- ✅ Interest calculation system
- ✅ Auto-save/load on startup
- ✅ Enhanced documentation (FEATURES.md, QUICKSTART.md)

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

For questions or issues, please open an issue on GitHub: [E-BANKING Repository](https://github.com/ilefbnr/E-BANKING)

### 📚 Additional Documentation
- **FEATURES.md**: Detailed technical documentation of all features
- **QUICKSTART.md**: Quick start guide with test scenarios
- **.github/copilot-instructions.md**: Development guidelines

---

**⭐ If you find this project useful, please give it a star on [GitHub](https://github.com/ilefbnr/E-BANKING)!**
