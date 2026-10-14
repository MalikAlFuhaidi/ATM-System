# ATM System

[![MIT License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

A console-based Automated Teller Machine (ATM) application built with C++. The project supports client authentication, deposits, withdrawals, and balance inquiry. It uses a text file for client data persistence and demonstrates procedural programming, file handling, input validation, and modular application design.

## Features

### Client Authentication

- Login using an account number and PIN code.
- Validate client credentials against records stored in `Clients.txt`.
- Display an error message when the supplied credentials are invalid.
- Logout and return to the login screen.

### ATM Transactions

- Deposit funds into the authenticated client's account.
- Reject zero and negative deposit amounts.
- Perform normal withdrawals using positive amounts that are multiples of five.
- Check the available balance before completing withdrawals.
- Perform quick withdrawals using predefined amounts: 20, 50, 100, 200, 400, 600, 800, and 1000.
- Reject quick withdrawal requests that exceed the available balance.
- Request confirmation before applying balance changes.
- Display the updated account balance after successful transactions.

### Balance Inquiry

- Display the current client's account balance.
- Show the available balance on the quick withdrawal screen.

### File Handling

- Load client records from `Clients.txt`.
- Convert file lines into client records and serialize records back to text.
- Save updated account balances to the client data file.

## Technologies Used

- **Language:** C++
- **IDE:** Microsoft Visual Studio 2022
- **Data Storage:** Text-file persistence using C++ file streams.
- **Core Concepts:** Structures, vectors, functions, enums, string manipulation, loops, and file handling.
- **Version Control:** Git and GitHub.

## Data Storage

The application uses `Clients.txt` to store client account information, including:

- Account number
- PIN code
- Client name
- Phone number
- Account balance

Records use `#//#` as the field separator:

`AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance`

The application loads client information from this file and saves balance changes after confirmed transactions.

## Build and Run

1. Install Microsoft Visual Studio 2022 with the **Desktop development with C++** workload.
2. Open `ATM-System.sln` in Visual Studio.
3. Select the `Debug` configuration and `x64` platform.
4. Build the solution using **Build > Build Solution**, or press `Ctrl + Shift + B`.
5. Run the application using `Ctrl + F5`.
6. Sign in using a test account configured in `Clients.txt`.

Make sure `Clients.txt` is available in the application's working directory.

## Project Structure

```text
ATM-System/
├── .gitignore
├── LICENSE
├── README.md
├── ATM-System.sln
└── ATM-System/
    ├── 0
    ├── ATM-System.cpp
    ├── ATM-System.vcxproj
    ├── ATM-System.vcxproj.filters
    └── Clients.txt
```

## Important Security Note

This project is intended for educational purposes and is not suitable for real banking operations. Client PIN codes are stored in plain text, and the application does not provide production-grade authentication or security.

Do not use real account credentials or sensitive personal information in this project.

## Future Improvements

- Improve handling of non-numeric console input.
- Replace plain-text PIN storage with secure password hashing.
- Remove existing compiler warnings.
- Add transaction history and audit logging.
- Replace text-file storage with a database.
- Add automated tests for deposit and withdrawal operations.

## License

This project is licensed under the [MIT License](LICENSE). You are free to use, modify, and distribute the software subject to the terms of the license.
