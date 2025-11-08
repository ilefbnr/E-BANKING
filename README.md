# E-Banking System in C

A simple command-line e-banking application written in C that allows users to manage bank accounts with basic operations.

## Features

- **Create Accounts**: Create new bank accounts with unique account numbers
- **View Accounts**: Display information for all accounts or specific accounts
- **Deposit Money**: Add funds to an account
- **Withdraw Money**: Withdraw funds with balance validation
- **Check Balance**: View the current balance of an account
- **Transaction History**: View all transactions for an account
- **Input Validation**: Comprehensive error handling for invalid operations

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

```
1. Create Account
   - Enter: John Doe
   - Creates account: ACC0000001000

2. Deposit Money
   - Account: ACC0000001000
   - Amount: 5000.00

3. Withdraw Money
   - Account: ACC0000001000
   - Amount: 1000.00

4. Check Balance
   - View current balance: 4000.00

5. View Transactions
   - See all transaction history
```

## Data Structures

### Account
```c
typedef struct {
    int id;
    char account_number[12];
    char holder_name[100];
    double balance;
    time_t created_date;
} Account;
```

### Transaction
```c
typedef struct {
    int id;
    char account_number[12];
    char transaction_type[20];
    double amount;
    time_t transaction_date;
} Transaction;
```

## Limitations

- Maximum 100 accounts (configurable in `account.h`)
- Maximum 1000 transactions (configurable in `account.h`)
- Data is stored in memory only (no persistent storage)
- Single-threaded operation
- No user authentication

## Future Enhancements

- File-based persistence (save/load accounts)
- Database integration
- User authentication and PIN protection
- Transfer between accounts
- Loan management
- Multi-threaded operations
- Interest calculation
- Overdraft facility

## Requirements

- GCC compiler (or any C99 compatible compiler)
- Make utility (optional, for using Makefile)
- Linux/Unix environment (or Windows with WSL/MinGW)

## Compilation Flags

- `-Wall`: Enable all warnings
- `-Wextra`: Enable extra warnings
- `-std=c99`: Use C99 standard
- `-I./include`: Include header files from include directory

## Author

Created as a demonstration of basic C programming concepts

## License

Free to use and modify
