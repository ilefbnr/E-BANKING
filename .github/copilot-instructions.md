# E-Banking System in C - Project Instructions

## Project Overview
A simple command-line e-banking application written in C for basic account and transaction management.

## Project Structure
```
ebank/
├── include/
│   └── account.h
├── src/
│   ├── main.c
│   └── account.c
├── Makefile
└── README.md
```

## Key Components

### account.h (Header File)
- Data structures: Account, Transaction, Bank
- Function declarations for all banking operations
- Constants and definitions

### account.c (Implementation)
- Core banking functions:
  - Account creation and management
  - Deposit and withdrawal operations
  - Transaction recording
  - Balance queries

### main.c (Main Program)
- Interactive menu-driven interface
- User input handling
- Command processing

## Build Instructions

```bash
make        # Build the project
make run    # Build and run
make clean  # Clean build files
```

## Features Implemented
- ✓ Create bank accounts
- ✓ View account information
- ✓ Deposit money
- ✓ Withdraw money with validation
- ✓ Check balance
- ✓ View transaction history
- ✓ Display all accounts

## Technical Details
- Language: C (C99 standard)
- Compilation: GCC with flags: -Wall -Wextra -std=c99
- Memory: In-memory storage (no persistence)
- Maximum accounts: 100
- Maximum transactions: 1000

## Testing Considerations
- Input validation for amounts (must be positive)
- Balance validation for withdrawals (insufficient funds check)
- Error handling for account not found scenarios
- Buffer overflow prevention with fgets
- Input buffer cleanup after scanf

## Next Steps for Enhancement
1. Add file persistence (read/write to files)
2. Implement user authentication
3. Add transfer between accounts feature
4. Create database integration
5. Add multi-threaded support for concurrent operations
