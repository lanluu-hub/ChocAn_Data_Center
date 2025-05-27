PRAGMA foreign_keys = ON;

-- Drop existing tables
DROP TABLE IF EXISTS ServiceLogs;
DROP TABLE IF EXISTS Reports;
DROP TABLE IF EXISTS Users;
DROP TABLE IF EXISTS Members;
DROP TABLE IF EXISTS Services;

-- Create Users table (only for system users)
CREATE TABLE Users (
    user_id INTEGER PRIMARY KEY,
    username TEXT NOT NULL UNIQUE,
    password_hash TEXT NOT NULL,
    email TEXT UNIQUE,
    user_type TEXT NOT NULL CHECK (user_type IN ('Provider', 'Operator', 'Manager')),
    created_at TEXT DEFAULT CURRENT_TIMESTAMP
);

-- Create Members table (completely separate)
CREATE TABLE Members (
    member_id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    address TEXT NOT NULL,
    city TEXT NOT NULL,
    state TEXT NOT NULL,
    zip_code TEXT NOT NULL,
    status TEXT NOT NULL CHECK (status IN ('Active', 'Suspended'))
);

-- Create Services table
CREATE TABLE Services (
    service_code TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    fee REAL NOT NULL CHECK (fee >= 0)
);

-- Create ServiceLogs table
CREATE TABLE ServiceLogs (
    log_id INTEGER PRIMARY KEY AUTOINCREMENT,
    date_of_service TEXT NOT NULL,
    timestamp_recorded TEXT NOT NULL,
    provider_id INTEGER NOT NULL,
    member_id INTEGER NOT NULL,
    service_code INTEGER NOT NULL,
    comments TEXT,
    FOREIGN KEY (provider_id) REFERENCES Providers(provider_id),
    FOREIGN KEY (member_id) REFERENCES Members(member_id),
    FOREIGN KEY (service_code) REFERENCES Services(service_code)
);

-- Create Reports table
CREATE TABLE Reports (
    report_id INTEGER PRIMARY KEY AUTOINCREMENT,
    report_type TEXT NOT NULL CHECK (report_type IN ('Member', 'Provider', 'Summary', 'EFT')),
    generated_date TEXT NOT NULL,
    content TEXT NOT NULL
);
