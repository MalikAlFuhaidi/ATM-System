# ATM System

A console-based Automated Teller Machine (ATM) application developed in C++.

## Features

- Client authentication using account numbers and PIN codes.
- Quick withdrawal with predefined amounts.
- Normal withdrawal using positive amounts in multiples of five.
- Deposit transactions with positive amounts.
- Balance inquiry.
- Balance validation for withdrawal transactions.
- Transaction confirmation before updating account balances.
- File-based client data persistence using `Clients.txt`.
- Console menus, navigation, and logout.

## Technologies

- C++
- Standard C++ Library
- File handling with `fstream`
- Visual Studio 2022
- Git and GitHub

## Project Structure

- `ATM-System.sln` — Visual Studio solution.
- `ATM-System/ATM-System.cpp` — Application source code.
- `ATM-System/ATM-System.vcxproj` — C++ project configuration.
- `ATM-System/ATM-System.vcxproj.filters` — Visual Studio file filters.
- `ATM-System/Clients.txt` — Client records used by the application.
- `.gitignore` — Files excluded from Git tracking.

## Build and Run

1. Open `ATM-System.sln` in Visual Studio 2022.
2. Select the `Debug` configuration and `x64` platform.
3. Build the solution using `Ctrl + Shift + B`.
4. Run the application using `Ctrl + F5`.
5. Sign in using a demo account configured in `Clients.txt`.

## Data Storage

Client records are stored in `Clients.txt`, with fields separated by `#//#`:

`AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance`

The application loads client information from the file and saves updated balances after confirmed transactions.

## Amount Validation

- Normal withdrawals reject zero and negative amounts.
- Normal withdrawals require amounts that are multiples of five.
- Withdrawal amounts are checked against the available account balance.
- Deposits reject zero and negative amounts.
- Quick withdrawals are rejected when the selected amount exceeds the available balance.

Non-numeric console input validation is not included in this version and may be addressed in future projects.

## Security Notice

This project is intended for educational purposes. PIN codes are stored in plain text, so this implementation must not be used with real financial accounts or sensitive personal information.
