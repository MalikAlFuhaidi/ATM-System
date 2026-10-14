# ATM System

A console-based Automated Teller Machine (ATM) application developed in C++.

## Features

- Client authentication using account numbers and PIN codes.
- Quick withdrawal with predefined amounts.
- Normal withdrawal.
- Deposit transactions with confirmation.
- Balance inquiry.
- File-based client data persistence.
- Console menus and navigation.
- Logout and return to the login screen.

## Technologies

- C++
- Standard C++ Library
- File handling with `fstream`
- Visual Studio 2022
- Git and GitHub

## Project Structure

```text
ATM-System/
├── .gitignore
├── README.md
├── ATM-System.sln
└── ATM-System/
    ├── ATM-System.cpp
    ├── ATM-System.vcxproj
    ├── ATM-System.vcxproj.filters
    ├── 0
    └── Clients.txt
```

## Build and Run

1. Open `ATM-System.sln` in Visual Studio 2022.
2. Select the `Debug` configuration and `x64` platform.
3. Build the solution using `Ctrl + Shift + B`.
4. Run the application using `Ctrl + F5`.
5. Sign in using a demo account configured in `Clients.txt`.

## Data Storage

Client records are stored in `Clients.txt`, with fields separated by `#//#`:

`AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance`

The application loads client information from the file and saves balance changes after confirmed transactions.

## Security Notice

This project is intended for learning and demonstration. PIN codes are stored in plain text, so the current implementation must not be used with real financial accounts or sensitive personal information.

Further improvements to input validation and transaction handling are planned.
